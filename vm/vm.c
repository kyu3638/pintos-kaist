/* vm.c: Generic interface for virtual memory objects. */

#include "threads/malloc.h"
#include "vm/vm.h"
#include "vm/inspect.h"
#include <string.h>
#include "hash.h"
#include "threads/vaddr.h"
#include <stdlib.h>
#include "userprog/process.h"

/* Initializes the virtual memory subsystem by invoking each subsystem's
 * intialize codes. */
void vm_init(void)
{
	vm_anon_init();
	vm_file_init();
#ifdef EFILESYS /* For project 4 */
	pagecache_init();
#endif
	register_inspect_intr();
	/* DO NOT MODIFY UPPER LINES. */
	/* TODO: Your code goes here. */
	list_init(&frame_list);
	lock_init(&frame_lock);
}

/* Get the type of the page. This function is useful if you want to know the
 * type of the page after it will be initialized.
 * This function is fully implemented now. */
enum vm_type
page_get_type(struct page *page)
{
	int ty = VM_TYPE(page->operations->type);
	switch (ty)
	{
	case VM_UNINIT:
		return VM_TYPE(page->uninit.type);
	default:
		return ty;
	}
}

/* Helpers */
static struct frame *vm_get_victim(void);
static bool vm_do_claim_page(struct page *page);
static struct frame *vm_evict_frame(void);

/* Create the pending page object with initializer. If you want to create a
 * page, do not create it directly and make it through this function or
 * `vm_alloc_page`. */
bool vm_alloc_page_with_initializer(enum vm_type type, void *upage, bool writable,
									vm_initializer *init, void *aux)
{

	ASSERT(VM_TYPE(type) != VM_UNINIT)

	struct supplemental_page_table *spt = &thread_current()->spt;
	/* Check wheter the upage is already occupied or not. */
	if (spt_find_page(spt, upage) == NULL)
	{
		/* TODO: Create the page, fetch the initialier according to the VM type,
		 * TODO: and then create "uninit" page struct by calling uninit_new. You
		 * TODO: should modify the field after calling the uninit_new. */
		/* TODO: Insert the page into the spt. */
		struct page *new_page = (struct page *)malloc(sizeof(struct page));
		if (new_page == NULL)
		{
			return false;
		}
		switch (VM_TYPE(type))
		{
		case VM_ANON:
			uninit_new(new_page, upage, init, type, aux, anon_initializer);
			break;
		case VM_FILE:
			uninit_new(new_page, upage, init, type, aux, file_backed_initializer);
			break;
		}
		new_page->writable = writable;
		/* TODO: Insert the page into the spt. */
		return spt_insert_page(spt, new_page);
	}
err:
	return false;
}

/* Find VA from spt and return page. On error, return NULL. */
struct page *
spt_find_page(struct supplemental_page_table *spt UNUSED, void *va UNUSED)
{
	/* TODO: Fill this function. */
	struct page page;
	page.va = pg_round_down(va);
	struct hash_elem *h = hash_find(&spt->vm, &page.h_elem);
	if (h == NULL)
	{
		return NULL;
	}
	return hash_entry(h, struct page, h_elem);
}

/* Insert PAGE into spt with validation. */
bool spt_insert_page(struct supplemental_page_table *spt UNUSED,
					 struct page *page UNUSED)
{
	int succ = false;
	/* TODO: Fill this function. */
	if (hash_insert(&spt->vm, &page->h_elem) == NULL)
	{
		succ = true;
	}
	return succ;
}

void spt_remove_page(struct supplemental_page_table *spt, struct page *page)
{
	vm_dealloc_page(page);
	return true;
}

/* Get the struct frame, that will be evicted. */
static struct frame *vm_get_victim(void)
{
	struct list_elem *victim_elem;
	struct frame *victim;
	lock_acquire(&frame_lock);
	while (true)
	{
		victim_elem = list_pop_front(&frame_list);
		victim = list_entry(victim_elem, struct frame, frame_elem);

		if (!pml4_is_accessed(thread_current()->pml4, victim->page->va))
			break;

		pml4_set_accessed(thread_current()->pml4, victim->page->va, 0);
		list_push_back(&frame_list, victim_elem);
	}
	lock_release(&frame_lock);
	return victim;
}

/* Evict one page and return the corresponding frame.
 * Return NULL on error.*/
static struct frame *
vm_evict_frame(void)
{
	struct frame *victim UNUSED = vm_get_victim();
	/* TODO: swap out the victim and return the evicted frame. */
	swap_out(victim->page);
	victim->page = NULL;
	memset(victim->kva, 0, PGSIZE);
	return victim;
}

/* palloc() and get frame. If there is no available page, evict the page
 * and return it. This always return valid address. That is, if the user pool
 * memory is full, this function evicts the frame to get the available memory
 * space.*/
static struct frame *
vm_get_frame(void)
{
	struct frame *frame = (struct frame *)malloc(sizeof(struct frame));
	frame->kva = palloc_get_page(PAL_USER);
	if (frame->kva == NULL)
	{
		frame = vm_evict_frame();
	}
	/* TODO: Fill this function. */
	frame->page = NULL;
	lock_acquire(&frame_lock);
	list_push_back(&frame_list, &frame->frame_elem);
	lock_release(&frame_lock);
	ASSERT(frame != NULL);
	ASSERT(frame->page == NULL);
	return frame;
}

/* Growing the stack. */
static void
vm_stack_growth(void *addr UNUSED)
{
	addr = pg_round_down(addr);
	while (addr < thread_current()->stack_bottom)
	{
		vm_alloc_page(VM_ANON, addr, 1);
		vm_claim_page(addr);
		addr += PGSIZE;
	}
}

/* Handle the fault on write_protected page */
static bool
vm_handle_wp(struct page *page UNUSED)
{
	void *parent_kva = page->frame->kva;
	page->frame->kva = palloc_get_page(PAL_USER);

	memcpy(page->frame->kva, parent_kva, PGSIZE);
	if (!pml4_set_page(thread_current()->pml4, page->va, page->frame->kva, page->copy_writable))
		palloc_free_page(page->frame->kva);
	return true;
}

/* Return true on success */
bool vm_try_handle_fault(struct intr_frame *f UNUSED, void *addr UNUSED, bool user UNUSED, bool write UNUSED, bool not_present UNUSED)
{
	struct supplemental_page_table *spt UNUSED = &thread_current()->spt;
	struct page *page = NULL;
	/* TODO: Validate the fault */
	/* TODO: Your code goes here */
	if (is_kernel_vaddr(addr) || !addr)
	{
		return false;
	}
	page = spt_find_page(spt, addr);
	if (page == NULL)
	{
		void *rsp = !user ? thread_current()->tf.rsp : f->rsp;
		if (rsp - (1 << 3) <= addr && addr <= thread_current()->stack_bottom)
		{
			vm_stack_growth(addr);
			thread_current()->stack_bottom = pg_round_down(addr);
			return true;
		}
	}
	else
	{
		if (write && !page->writable)
			return false;
		if (write && page->copy_writable)
			return vm_handle_wp(page);
		vm_do_claim_page(page);
		return true;
	}
	return false;
}

/* Free the page.
 * DO NOT MODIFY THIS FUNCTION. */
void vm_dealloc_page(struct page *page)
{
	destroy(page);
	free(page);
}

/* Claim the page that allocate on VA. */
bool vm_claim_page(void *va UNUSED)
{
	struct page *page = spt_find_page(&thread_current()->spt, va);
	if (page == NULL)
	{
		return false;
	}
	return vm_do_claim_page(page);
}

/* Claim the PAGE and set up the mmu. */
static bool
vm_do_claim_page(struct page *page)
{
	struct frame *frame = vm_get_frame();
	/* Set links */
	if (frame == NULL)
	{
		return false;
	}
	frame->page = page;
	page->frame = frame;

	/* TODO: Insert page table entry to map page's VA to frame's PA. */
	if (install_page(page->va, frame->kva, page->writable))
	{
		return swap_in(page, frame->kva);
	}
	return false;
}

/* Initialize new supplemental page table */
void supplemental_page_table_init(struct supplemental_page_table *spt UNUSED)
{
	hash_init(&spt->vm, vm_hash_func, vm_less_func, NULL);
}

/* Copy supplemental page table from src to dst */
bool supplemental_page_table_copy(struct supplemental_page_table *dst UNUSED,
								  struct supplemental_page_table *src UNUSED)
{

	struct hash_iterator i;
	hash_first(&i, &src->vm);
	while (hash_next(&i))
	{
		struct page *tmp_page = hash_entry(hash_cur(&i), struct page, h_elem);
		struct page *cpy_page = NULL;
		switch (VM_TYPE(tmp_page->operations->type))
		{
		case VM_UNINIT:
		{
			struct info *aux = (struct info *)malloc(sizeof(struct info));
			memcpy(aux, tmp_page->uninit.aux, sizeof(struct info));
			aux->file = file_duplicate(aux->file);
			if (!vm_alloc_page_with_initializer(VM_ANON, tmp_page->va, tmp_page->writable, tmp_page->uninit.init, aux))
				free(aux);
			break;
		}
		case VM_ANON:
		{
			vm_alloc_page(VM_ANON, tmp_page->va, tmp_page->writable);
			cpy_page = spt_find_page(dst, tmp_page->va);
			if (!cpy_page)
				return false;

			cpy_page->copy_writable = tmp_page->writable;
			struct frame *cpy_frame = malloc(sizeof(struct frame));
			cpy_page->frame = cpy_frame;
			cpy_frame->page = cpy_page;
			cpy_frame->kva = tmp_page->frame->kva;

			struct thread *t = thread_current();

			lock_acquire(&frame_lock);
			list_push_back(&frame_list, &cpy_frame->frame_elem);
			lock_release(&frame_lock);

			if (!pml4_set_page(t->pml4, cpy_page->va, cpy_frame->kva, 0))
			{
				free(cpy_frame);
				return false;
			}
			swap_in(cpy_page, cpy_frame->kva);
			break;
		}
		}
	}
	return true;
}
void spt_dealloc(struct hash_elem *e, void *aux)
{
	struct page *page = hash_entry(e, struct page, h_elem);
	ASSERT(is_user_vaddr(page->va));
	ASSERT(is_kernel_vaddr(page));
	free(page);
}
/* Free the resource hold by the supplemental page table */
void supplemental_page_table_kill(struct supplemental_page_table *spt UNUSED)
{
	/* TODO: Destroy all the supplemental_page_table hold by thread and
	 * TODO: writeback all the modified contents to the storage. */
	if (!hash_empty(&spt->vm))
	{
		struct hash_iterator i;
		struct frame *frame;
		hash_first(&i, &spt->vm);
		while (hash_next(&i))
		{
			struct page *target = hash_entry(hash_cur(&i), struct page, h_elem);
			frame = target->frame;
			// file-backed file인 경우
			if (target->operations->type == VM_FILE)
			{
				do_munmap(target->va);
			}
		}
		hash_destroy(&spt->vm, spt_dealloc);
		free(frame);
	}
}

static unsigned vm_hash_func(const struct hash_elem *e, void *aux)
{
	struct page *curpage = hash_entry(e, struct page, h_elem);
	return hash_int(curpage->va);
}

static bool vm_less_func(const struct hash_elem *a, const struct hash_elem *b)
{
	struct page *comp_a = hash_entry(a, struct page, h_elem);
	struct page *comp_b = hash_entry(b, struct page, h_elem);

	return comp_a->va < comp_b->va;
}