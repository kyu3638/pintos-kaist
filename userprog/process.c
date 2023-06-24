/* ELF 바이너리(=ELF 실행파일)들을 로드하고 프로세스를 실행합니다
 * ELF: ELF는 많은 운영체제에서 목적 파일, 공유 라이브러리, 그리고 실행 파일들을 위해 사용되는 파일 포맷*/
#include "userprog/process.h"
#include <debug.h>
#include <inttypes.h>
#include <round.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userprog/gdt.h"
#include "userprog/tss.h"
#include "filesys/directory.h"
#include "filesys/file.h"
#include "filesys/filesys.h"
#include "threads/flags.h"
#include "threads/init.h"
#include "threads/interrupt.h"
#include "threads/palloc.h"
#include "threads/thread.h"
#include "threads/mmu.h"
#include "userprog/syscall.h"
#include "threads/vaddr.h"
#include "intrinsic.h"
#include "threads/synch.h"
#ifdef VM
#include "vm/vm.h"
#endif

static void process_cleanup(void);
static bool load(const char *file_name, struct intr_frame *if_);
static void initd(void *f_name);
static void __do_fork(void *);
void argument_stack(char **parse, int count, void **rsp);
int process_add_file(struct file *f);
struct file *process_get_file(int fd);
void process_close_file(int fd);
void remove_child_process(struct thread *cp);
struct thread *get_child_process(int pid);

/* General process initializer for initd and other process. */
static void
process_init(void)
{
	struct thread *current = thread_current();
}

/* Starts the first userland program, called "initd", loaded from FILE_NAME.
 * The new thread may be scheduled (and may even exit)
 * before process_create_initd() returns. Returns the initd's
 * thread id, or TID_ERROR if the thread cannot be created.
 * Notice that THIS SHOULD BE CALLED ONCE. */
tid_t process_create_initd(const char *file_name)
{
	char *fn_copy;
	tid_t tid;

	/* Make a copy of FILE_NAME.
	 * Otherwise there's a race between the caller and load(). */
	fn_copy = palloc_get_page(0);
	if (fn_copy == NULL)
		return TID_ERROR;
	strlcpy(fn_copy, file_name, PGSIZE);

	/* Create a new thread to execute FILE_NAME. */
	char *save_ptr;
	char *file_title = strtok_r(file_name, " ", &save_ptr);
	tid = thread_create(file_title, PRI_DEFAULT, initd, fn_copy);
	if (tid == TID_ERROR)
		palloc_free_page(fn_copy);
	return tid;
}

/* A thread function that launches first user process. */
static void
initd(void *f_name)
{
#ifdef VM
	supplemental_page_table_init(&thread_current()->spt);
#endif

	process_init();

	if (process_exec(f_name) < 0)
		PANIC("Fail to launch initd\n");
	NOT_REACHED();
}

/* Clones the current process as `name`. Returns the new process's thread id, or
 * TID_ERROR if the thread cannot be created. */
tid_t process_fork(const char *name, struct intr_frame *if_ UNUSED)
{

	// project 2 : system call
	/* Clone current thread to new thread.*/
	struct thread *cur = thread_current();
	memcpy(&thread_current()->parent_if, if_, sizeof(struct intr_frame));
	tid_t tid = thread_create(name, PRI_DEFAULT, __do_fork, cur);

	if (tid == TID_ERROR)
	{
		return TID_ERROR;
	}
	struct thread *child = get_child_process(tid); // child_list안에서 만들어진 child thread를 찾음

	sema_down(&child->load_sema); // 자식이 메모리에 load 될때까지 기다림(blocked)

	if (child->exit_flag == -1)
	{
		return TID_ERROR;
	}
	return tid;
}

#ifndef VM
/* Duplicate the parent's address space by passing this function to the
 * pml4_for_each. This is only for the project 2. */
static bool
duplicate_pte(uint64_t *pte, void *va, void *aux)
{
	struct thread *current = thread_current();
	struct thread *parent = (struct thread *)aux;
	void *parent_page;
	void *newpage;
	bool writable;

	/* 1. TODO: If the parent_page is kernel page, then return immediately. */
	if (is_kernel_vaddr(va))
	{
		return true;
	}
	/* 2. Resolve VA from the parent's page map level 4. */
	parent_page = pml4_get_page(parent->pml4, va);
	if (parent_page == NULL)
	{
		return false;
	}
	/* 3. TODO: Allocate new PAL_USER page for the child and set result to
	 *    TODO: NEWPAGE. */
	newpage = palloc_get_page(PAL_USER);
	if (newpage == NULL)
	{
		return false;
	}
	/* 4. TODO: Duplicate parent's page to the new page and
	 *    TODO: check whether parent's page is writable or not (set WRITABLE
	 *    TODO: according to the result). */
	memcpy(newpage, parent_page, PGSIZE);
	writable = is_writable(pte);
	/* 5. Add new page to child's page table at address VA with WRITABLE
	 *    permission. */
	if (!pml4_set_page(current->pml4, va, newpage, writable))
	{
		/* 6. TODO: if fail to insert page, do error handling. */
		palloc_free_page(newpage);
		return false;
	}
	return true;
}
#endif

static void
__do_fork(void *aux)
{

	struct intr_frame if_;
	struct thread *parent = (struct thread *)aux;
	struct thread *current = thread_current();
	current->parent = parent;
	struct intr_frame *parent_if = &parent->parent_if;
	bool succ = true;

	/* 1. Read the cpu context to local stack. */
	memcpy(&if_, parent_if, sizeof(struct intr_frame));

	/* 2. Duplicate PT */
	current->pml4 = pml4_create();
	if (current->pml4 == NULL)
		goto error;

	process_activate(current);
#ifdef VM
	supplemental_page_table_init(&current->spt);
	if (!supplemental_page_table_copy(&current->spt, &parent->spt))
		goto error;
#else
	if (!pml4_for_each(parent->pml4, duplicate_pte, parent))
		goto error;
#endif

	if (parent->next_fd == FD_MAX)
		goto error;

	for (int i = 0; i < FD_MAX; i++)
	{
		struct file *file = parent->fdt[i];
		if (file == NULL)
			continue;
		struct file *new_file;
		if (file > FD_MIN)
			new_file = file_duplicate(file);
		else
			new_file = file;
		current->fdt[i] = new_file;
	}
	if_.R.rax = 0;
	current->next_fd = parent->next_fd;
	process_init();
	sema_up(&current->load_sema);
	/* Finally, switch to the newly created process. */
	if (succ)
		do_iret(&if_);
error:
	current->exit_flag = TID_ERROR;
	sema_up(&current->load_sema);
	thread_exit();
}
struct thread *get_child_process(int pid)
{
	struct thread *par = thread_current();
	struct list_elem *current_elem;

	if (list_empty(&par->child_list))
		return NULL;

	for (current_elem = list_front(&par->child_list); current_elem != list_tail(&par->child_list); current_elem = list_next(current_elem))
	{
		if (list_entry(current_elem, struct thread, child_elem)->tid == pid)
		{
			return list_entry(current_elem, struct thread, child_elem);
		}
	}
	return NULL;
}

/* Switch the current execution context to the f_name.
 * Returns -1 on fail. */
int process_exec(void *f_name)
{
	char *file_name = f_name;
	bool success;
	struct thread *cur = thread_current();

	// intr_frame 권한설정
	struct intr_frame _if;
	_if.ds = _if.es = _if.ss = SEL_UDSEG;
	_if.cs = SEL_UCSEG;
	_if.eflags = FLAG_IF | FLAG_MBS;

	/* We first kill the current context */
	process_cleanup();

#ifdef VM
	supplemental_page_table_init(&cur->spt);
#endif

	// for argument parsing
	char *parse[128];
	int count = 0;

	char *token;
	char *save_ptr; // 분리된 문자열 중 남는 부분의 시작주소
	token = strtok_r(file_name, " ", &save_ptr);
	while (token != NULL)
	{
		parse[count] = token;
		token = strtok_r(NULL, " ", &save_ptr);
		count++;
	}

	/* And then load the binary */
	success = load(file_name, &_if);

	/* If load failed, quit. */
	if (!success)
	{
		palloc_free_page(file_name);
		return -1;
	}

	argument_stack(parse, count, &_if.rsp);
	_if.R.rdi = count;
	_if.R.rsi = _if.rsp + 8;

	palloc_free_page(file_name);

	/* Start switched process. */
	do_iret(&_if);
	NOT_REACHED();
}

void argument_stack(char **parse, int count, void **rsp)
{
	// Save argument strings (character by character)
	int parse_len;
	char parse_char;
	for (int i = count - 1; i >= 0; i--)
	{
		parse_len = strlen(parse[i]);
		for (int j = parse_len; j >= 0; j--)
		{
			parse_char = parse[i][j];
			(*rsp)--;
			**(char **)rsp = parse_char; // 1 byte
		}
		parse[i] = *(char **)rsp;
	}
	uint64_t pad = (int)*rsp % 8;
	for (int k = 0; k < pad; k++)
	{
		(*rsp)--;
		**(uint8_t **)rsp = 0;
	}
	(*rsp) -= 8;
	**(char ***)rsp = 0;
	for (int i = count - 1; i >= 0; i--)
	{
		(*rsp) -= 8;
		**(char ***)rsp = parse[i];
	}
	(*rsp) -= 8;
	**(void ***)rsp = 0;
}

int process_add_file(struct file *f)
{

	struct thread *cur = thread_current();
	// 파일 객체(struct file)를 가리키는 포인터를 File Descriptor 테이블에 추가
	cur->fdt[cur->next_fd] = f;

	// 다음 File Descriptor 값 1 증가
	cur->next_fd++;
	// 추가된 파일 객체의 File Descriptor 반환
	return cur->next_fd - 1;
}

struct file *process_get_file(int fd)
{
	struct thread *cur = thread_current();
	if (fd < FD_MIN || fd >= FD_MAX)
	{
		return NULL;
	}
	return cur->fdt[fd];
}
void process_close_file(int fd)
{
	struct thread *cur = thread_current();
	if (fd < FD_MIN || fd >= FD_MAX)
	{
		return;
	}
	cur->fdt[fd] = NULL;
}
void remove_child_process(struct thread *cp)
{
	list_remove(&cp->child_elem);
	palloc_free_page(cp);
}

/* Waits for thread TID to die and returns its exit status.  If
 * it was terminated by the kernel (i.e. killed due to an
 * exception), returns -1.  If TID is invalid or if it was not a
 * child of the calling process, or if process_wait() has already
 * been successfully called for the given TID, returns -1
 * immediately, without waiting.
 *
 * This function will be implemented in problem 2-2.  For now, it
 * does nothing. */
int process_wait(tid_t child_tid UNUSED)
{
	struct thread *child_thread = get_child_process(child_tid);
	if (child_thread == NULL)
		return -1;

	sema_down(&child_thread->exit_sema);
	int child_exit_flag = child_thread->exit_flag;
	list_remove(&child_thread->child_elem);
	sema_up(&child_thread->free_sema);

	return child_exit_flag;
}

/* Exit the process. This function is called by thread_exit (). */
void process_exit(void)
{
	struct thread *cur = thread_current();
	for (int i = FD_MIN; i < FD_MAX; i++)
		close(i);
	palloc_free_multiple(cur->fdt, 3);
	cur->fdt = NULL;
	file_close(cur->running_file);
	sema_up(&cur->exit_sema);
	sema_down(&cur->free_sema);
	process_cleanup(); // pml4를 날림(이 함수를 call 한 thread의 pml4)
}

/* Free the current process's resources. */
static void
process_cleanup(void)
{
	struct thread *curr = thread_current();

#ifdef VM
	supplemental_page_table_kill(&curr->spt);
#endif

	uint64_t *pml4;
	/* Destroy the current process's page directory and switch back
	 * to the kernel-only page directory. */
	pml4 = curr->pml4;
	if (pml4 != NULL)
	{
		/* Correct ordering here is crucial.  We must set
		 * cur->pagedir to NULL before switching page directories,
		 * so that a timer interrupt can't switch back to the
		 * process page directory.  We must activate the base page
		 * directory before destroying the process's page
		 * directory, or our active page directory will be one
		 * that's been freed (and cleared). */
		curr->pml4 = NULL;
		pml4_activate(NULL);
		pml4_destroy(pml4);
	}
}

/* Sets up the CPU for running user code in the nest thread.
 * This function is called on every context switch. */
void process_activate(struct thread *next)
{
	/* Activate thread's page tables. */
	pml4_activate(next->pml4);

	/* Set thread's kernel stack for use in processing interrupts. */
	tss_update(next);
}

/* We load ELF binaries.  The following definitions are taken
 * from the ELF specification, [ELF1], more-or-less verbatim.  */

/* ELF types.  See [ELF1] 1-2. */
#define EI_NIDENT 16

#define PT_NULL 0			/* Ignore. */
#define PT_LOAD 1			/* Loadable segment. */
#define PT_DYNAMIC 2		/* Dynamic linking info. */
#define PT_INTERP 3			/* Name of dynamic loader. */
#define PT_NOTE 4			/* Auxiliary info. */
#define PT_SHLIB 5			/* Reserved. */
#define PT_PHDR 6			/* Program header table. */
#define PT_STACK 0x6474e551 /* Stack segment. */

#define PF_X 1 /* Executable. */
#define PF_W 2 /* Writable. */
#define PF_R 4 /* Readable. */

/* Executable header.  See [ELF1] 1-4 to 1-8.
 * This appears at the very beginning of an ELF binary. */
struct ELF64_hdr
{
	unsigned char e_ident[EI_NIDENT];
	uint16_t e_type;
	uint16_t e_machine;
	uint32_t e_version;
	uint64_t e_entry;
	uint64_t e_phoff;
	uint64_t e_shoff;
	uint32_t e_flags;
	uint16_t e_ehsize;
	uint16_t e_phentsize;
	uint16_t e_phnum;
	uint16_t e_shentsize;
	uint16_t e_shnum;
	uint16_t e_shstrndx;
};

struct ELF64_PHDR
{
	uint32_t p_type;
	uint32_t p_flags;
	uint64_t p_offset;
	uint64_t p_vaddr;
	uint64_t p_paddr;
	uint64_t p_filesz;
	uint64_t p_memsz;
	uint64_t p_align;
};

/* Abbreviations */
#define ELF ELF64_hdr
#define Phdr ELF64_PHDR

static bool setup_stack(struct intr_frame *if_);
static bool validate_segment(const struct Phdr *, struct file *);
static bool load_segment(struct file *file, off_t ofs, uint8_t *upage,
						 uint32_t read_bytes, uint32_t zero_bytes,
						 bool writable);

/* Loads an ELF executable from FILE_NAME into the current thread.
 * Stores the executable's entry point into *RIP
 * and its initial stack pointer into *RSP.
 * Returns true if successful, false otherwise. */
static bool
load(const char *file_name, struct intr_frame *if_)
{
	struct thread *t = thread_current();
	struct ELF ehdr;
	struct file *file = NULL;
	off_t file_ofs;
	bool success = false;
	int i;

	/* Allocate and activate page directory. */
	t->pml4 = pml4_create();
	if (t->pml4 == NULL)
		goto done;
	process_activate(thread_current());

	/* Open executable file. */
	lock_acquire(&filesys_lock);
	file = filesys_open(file_name);
	if (file == NULL)
	{
		lock_release(&filesys_lock);
		printf("load: %s: open failed\n", file_name);
		goto done;
	}

	t->running_file = file;
	file_deny_write(file);
	lock_release(&filesys_lock);

	/* Read and verify executable header. */
	if (file_read(file, &ehdr, sizeof ehdr) != sizeof ehdr || memcmp(ehdr.e_ident, "\177ELF\2\1\1", 7) || ehdr.e_type != 2 || ehdr.e_machine != 0x3E // amd64
		|| ehdr.e_version != 1 || ehdr.e_phentsize != sizeof(struct Phdr) || ehdr.e_phnum > 1024)
	{
		printf("load: %s: error loading executable\n", file_name);
		goto done;
	}

	/* Read program headers. */
	file_ofs = ehdr.e_phoff;
	for (i = 0; i < ehdr.e_phnum; i++)
	{
		struct Phdr phdr;

		if (file_ofs < 0 || file_ofs > file_length(file))
			goto done;
		file_seek(file, file_ofs);

		if (file_read(file, &phdr, sizeof phdr) != sizeof phdr)
			goto done;
		file_ofs += sizeof phdr;
		switch (phdr.p_type)
		{
		case PT_NULL:
		case PT_NOTE:
		case PT_PHDR:
		case PT_STACK:
		default:
			/* Ignore this segment. */
			break;
		case PT_DYNAMIC:
		case PT_INTERP:
		case PT_SHLIB:
			goto done;
		case PT_LOAD:
			if (validate_segment(&phdr, file))
			{
				bool writable = (phdr.p_flags & PF_W) != 0;
				uint64_t file_page = phdr.p_offset & ~PGMASK;
				uint64_t mem_page = phdr.p_vaddr & ~PGMASK;
				uint64_t page_offset = phdr.p_vaddr & PGMASK;
				uint32_t read_bytes, zero_bytes;
				if (phdr.p_filesz > 0)
				{
					/* Normal segment.
					 * Read initial part from disk and zero the rest. */
					read_bytes = page_offset + phdr.p_filesz;
					zero_bytes = (ROUND_UP(page_offset + phdr.p_memsz, PGSIZE) - read_bytes);
				}
				else
				{
					/* Entirely zero.
					 * Don't read anything from disk. */
					read_bytes = 0;
					zero_bytes = ROUND_UP(page_offset + phdr.p_memsz, PGSIZE);
				}
				if (!load_segment(file, file_page, (void *)mem_page,
								  read_bytes, zero_bytes, writable))
					goto done;
			}
			else
				goto done;
			break;
		}
	}

	/* Set up stack. */
	if (!setup_stack(if_))
		goto done;

	/* Start address. */
	if_->rip = ehdr.e_entry;

	/* TODO: Your code goes here.
	 * TODO: Implement argument passing (see project2/argument_passing.html). */

	success = true;

done:
	/* We arrive here whether the load is successful or not. */
	// file_close (file);
	return success;
}

/* Checks whether PHDR describes a valid, loadable segment in
 * FILE and returns true if so, false otherwise. */
static bool
validate_segment(const struct Phdr *phdr, struct file *file)
{
	/* p_offset and p_vaddr must have the same page offset. */
	if ((phdr->p_offset & PGMASK) != (phdr->p_vaddr & PGMASK))
		return false;

	/* p_offset must point within FILE. */
	if (phdr->p_offset > (uint64_t)file_length(file))
		return false;

	/* p_memsz must be at least as big as p_filesz. */
	if (phdr->p_memsz < phdr->p_filesz)
		return false;

	/* The segment must not be empty. */
	if (phdr->p_memsz == 0)
		return false;

	/* The virtual memory region must both start and end within the
	   user address space range. */
	if (!is_user_vaddr((void *)phdr->p_vaddr))
		return false;
	if (!is_user_vaddr((void *)(phdr->p_vaddr + phdr->p_memsz)))
		return false;

	/* The region cannot "wrap around" across the kernel virtual
	   address space. */
	if (phdr->p_vaddr + phdr->p_memsz < phdr->p_vaddr)
		return false;

	/* Disallow mapping page 0.
	   Not only is it a bad idea to map page 0, but if we allowed
	   it then user code that passed a null pointer to system calls
	   could quite likely panic the kernel by way of null pointer
	   assertions in memcpy(), etc. */
	if (phdr->p_vaddr < PGSIZE)
		return false;

	/* It's okay. */
	return true;
}

bool install_page(void *upage, void *kpage, bool writable)
{
	struct thread *t = thread_current();

	/* Verify that there's not already a page at that virtual
	 * address, then map our page there. */
	return (pml4_get_page(t->pml4, upage) == NULL && pml4_set_page(t->pml4, upage, kpage, writable));
}

#ifndef VM
/* Codes of this block will be ONLY USED DURING project 2.
 * If you want to implement the function for whole project 2, implement it
 * outside of #ifndef macro. */

/* load() helpers. */

/* Loads a segment starting at offset OFS in FILE at address
 * UPAGE.  In total, READ_BYTES + ZERO_BYTES bytes of virtual
 * memory are initialized, as follows:
 *
 * - READ_BYTES bytes at UPAGE must be read from FILE
 * starting at offset OFS.
 *
 * - ZERO_BYTES bytes at UPAGE + READ_BYTES must be zeroed.
 *
 * The pages initialized by this function must be writable by the
 * user process if WRITABLE is true, read-only otherwise.
 *
 * Return true if successful, false if a memory allocation error
 * or disk read error occurs. */
static bool
load_segment(struct file *file, off_t ofs, uint8_t *upage,
			 uint32_t read_bytes, uint32_t zero_bytes, bool writable)
{
	ASSERT((read_bytes + zero_bytes) % PGSIZE == 0);
	ASSERT(pg_ofs(upage) == 0);
	ASSERT(ofs % PGSIZE == 0);

	file_seek(file, ofs);
	while (read_bytes > 0 || zero_bytes > 0)
	{
		/* Do calculate how to fill this page.
		 * We will read PAGE_READ_BYTES bytes from FILE
		 * and zero the final PAGE_ZERO_BYTES bytes. */
		size_t page_read_bytes = read_bytes < PGSIZE ? read_bytes : PGSIZE;
		size_t page_zero_bytes = PGSIZE - page_read_bytes;

		/* Get a page of memory. */
		uint8_t *kpage = palloc_get_page(PAL_USER);
		if (kpage == NULL)
			return false;

		/* Load this page. */
		if (file_read(file, kpage, page_read_bytes) != (int)page_read_bytes)
		{
			palloc_free_page(kpage);
			return false;
		}
		memset(kpage + page_read_bytes, 0, page_zero_bytes);

		/* Add the page to the process's address space. */
		if (!install_page(upage, kpage, writable))
		{
			printf("fail\n");
			palloc_free_page(kpage);
			return false;
		}

		/* Advance. */
		read_bytes -= page_read_bytes;
		zero_bytes -= page_zero_bytes;
		upage += PGSIZE;
	}
	return true;
}

/* Create a minimal stack by mapping a zeroed page at the USER_STACK */
static bool
setup_stack(struct intr_frame *if_)
{
	uint8_t *kpage;
	bool success = false;

	kpage = palloc_get_page(PAL_USER | PAL_ZERO);
	if (kpage != NULL)
	{
		success = install_page(((uint8_t *)USER_STACK) - PGSIZE, kpage, true);
		if (success)
			if_->rsp = USER_STACK;
		else
			palloc_free_page(kpage);
	}
	return success;
}

/* Adds a mapping from user virtual address UPAGE to kernel
 * virtual address KPAGE to the page table.
 * If WRITABLE is true, the user process may modify the page;
 * otherwise, it is read-only.
 * UPAGE must not already be mapped.
 * KPAGE should probably be a page obtained from the user pool
 * with palloc_get_page().
 * Returns true on success, false if UPAGE is already mapped or
 * if memory allocation fails. */
#else
/* From here, codes will be used after project 3.
 * If you want to implement the function for only project 2, implement it on the
 * upper block. */

static bool
lazy_load_segment(struct page *page, void *aux)
{
	/* project 3 virtual memory */
	struct frame *load_frame = page->frame;
	struct info *file_info = (struct info *)aux;

	/* TODO: This called when the first page fault occurs on address VA. */
	/* TODO: VA is available when calling this function. */
	struct file *file = ((struct info *)aux)->file;
	off_t offset = ((struct info *)aux)->offset;
	size_t page_read_bytes = ((struct info *)aux)->read_bytes;
	size_t page_zero_bytes = PGSIZE - page_read_bytes;

	//TODO: add gunhee Ego
	uint8_t* kva = page->frame->kva;
	if (kva == NULL){
		free(page);
		return false;
	}
	
	if (file_read_at(file, load_frame->kva, page_read_bytes,offset) != (int)page_read_bytes)
	{
		free(page);
		return false;
	}

	memset(load_frame->kva + page_read_bytes, 0, page_zero_bytes);
	return true;
}

/* Loads a segment starting at offset OFS in FILE at address
 * UPAGE.  In total, READ_BYTES + ZERO_BYTES bytes of virtual
 * memory are initialized, as follows:
 *
 * - READ_BYTES bytes at UPAGE must be read from FILE
 * starting at offset OFS.
 *
 * - ZERO_BYTES bytes at UPAGE + READ_BYTES must be zeroed.
 *
 * The pages initialized by this function must be writable by the
 * user process if WRITABLE is true, read-only otherwise.
 *
 * Return true if successful, false if a memory allocation error
 * or disk read error occurs. */
static bool
load_segment(struct file *file, off_t ofs, uint8_t *upage,
			 uint32_t read_bytes, uint32_t zero_bytes, bool writable)
{
	ASSERT((read_bytes + zero_bytes) % PGSIZE == 0);
	ASSERT(pg_ofs(upage) == 0);
	ASSERT(ofs % PGSIZE == 0);

	while (read_bytes > 0 || zero_bytes > 0)
	{
		/* Do calculate how to fill this page.
		 * We will read PAGE_READ_BYTES bytes from FILE
		 * and zero the final PAGE_ZERO_BYTES bytes. */
		size_t page_read_bytes = read_bytes < PGSIZE ? read_bytes : PGSIZE;
		size_t page_zero_bytes = PGSIZE - page_read_bytes;

		/* project 3 virtual memory */
		struct info *file_info = (struct info *)malloc(sizeof(struct info));
		file_info->file = file;
		file_info->offset = ofs;
		file_info->read_bytes = page_read_bytes;

		/* TODO: Set up aux to pass information to the lazy_load_segment. */
		void *aux = file_info;

		if (!vm_alloc_page_with_initializer(VM_ANON, upage,
											writable, lazy_load_segment, file_info))
			return false;

		/* Advance. */
		read_bytes -= page_read_bytes;
		zero_bytes -= page_zero_bytes;
		upage += PGSIZE;
		ofs += page_read_bytes;
	}
	return true;
}

/* Create a PAGE of stack at the USER_STACK. Return true on success. */
static bool
setup_stack(struct intr_frame *if_)
{
	bool success = false;
	void *stack_bottom = (void *)(((uint8_t *)USER_STACK) - PGSIZE);

	/* TODO: Map the stack on stack_bottom and claim the page immediately.
	 * TODO: If success, set the rsp accordingly.
	 * TODO: You should mark the page is stack. */
	/* TODO: Your code goes here */
	/* project 3 virtual memory */
	success = vm_alloc_page(VM_ANON, stack_bottom, true);
	if (success)
	{
		struct page *pg = spt_find_page(&thread_current()->spt, stack_bottom);

		if (vm_claim_page(stack_bottom)){
			if_->rsp = (uintptr_t)USER_STACK;
			thread_current()->stack_bottom = stack_bottom;
		}
	}

	return success;
}

#endif /* VM */
