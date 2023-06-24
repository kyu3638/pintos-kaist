#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/palloc.h"
#include "threads/loader.h"
#include "userprog/gdt.h"
#include "threads/init.h"
#include "threads/flags.h"
#include "intrinsic.h"
#include "filesys/filesys.h"
#include "user/syscall.h"
#include "threads/vaddr.h"
#include "threads/synch.h"
#include "filesys/file.h"
#include "userprog/process.h"
#include <string.h>
#include "vm/vm.h"

void syscall_entry(void);
void syscall_handler(struct intr_frame *);
struct page *check_address(void *addr);
int process_add_file(struct file *f);
struct file *process_get_file(int fd);
void *mmap (void *addr, size_t length, int writable, int fd, off_t offset);
void munmap (void *addr);

/* System call.
 *
 * Previously system call services was handled by the interrupt handler
 * (e.g. int 0x80 in linux). However, in x86-64, the manufacturer supplies
 * efficient path for requesting the system call, the `syscall` instruction.
 *
 * The syscall instruction works by reading the values from the the Model
 * Specific Register (MSR). For the details, see the manual. */

#define MSR_STAR 0xc0000081         /* Segment selector msr */
#define MSR_LSTAR 0xc0000082        /* Long mode SYSCALL target */
#define MSR_SYSCALL_MASK 0xc0000084 /* Mask for the eflags */

void syscall_init(void)
{
   write_msr(MSR_STAR, ((uint64_t)SEL_UCSEG - 0x10) << 48 |
                           ((uint64_t)SEL_KCSEG) << 32);
   write_msr(MSR_LSTAR, (uint64_t)syscall_entry);

   /* The interrupt service rountine should not serve any interrupts
    * until the syscall_entry swaps the userland stack to the kernel
    * mode stack. Therefore, we masked the FLAG_FL. */
   write_msr(MSR_SYSCALL_MASK,
             FLAG_IF | FLAG_TF | FLAG_DF | FLAG_IOPL | FLAG_AC | FLAG_NT);
   lock_init(&filesys_lock);
}

/* The main system call interface */
void syscall_handler(struct intr_frame *f UNUSED)
{
   // TODO: Your implementation goes here.
   check_address(f->rsp);
   struct thread *cur = thread_current();
   int syscall_num = f->R.rax;
   switch (syscall_num)
   {
   case SYS_HALT: /* Halt the operating system. */
      halt();
      break;
   case SYS_EXIT: /* Terminate this process. */
      exit(f->R.rdi);
      break;
   case SYS_FORK: /* Clone current process. */
      memcpy(&cur->tf, f, sizeof(struct intr_frame));
      f->R.rax = fork(f->R.rdi);
      break;
   case SYS_EXEC: /* Switch current process. */
      f->R.rax = exec(f->R.rdi);
      break;
   case SYS_WAIT: /* Wait for a child process to die. */
      f->R.rax = wait(f->R.rdi);
      break;
   case SYS_CREATE: /* Create a file. */
      f->R.rax = create(f->R.rdi, f->R.rsi);
      break;
   case SYS_REMOVE: /* Delete a file. */
      f->R.rax = remove(f->R.rdi);
      break;
   case SYS_OPEN: /* Open a file. */
      f->R.rax = open(f->R.rdi);
      break;
   case SYS_FILESIZE: /* Obtain a file's size. */
      f->R.rax = filesize(f->R.rdi);
      break;
   case SYS_READ: /* Read from a file. */
      f->R.rax = read(f->R.rdi, f->R.rsi, f->R.rdx);
      break;
   case SYS_WRITE: /* Write to a file. */
      f->R.rax = write(f->R.rdi, f->R.rsi, f->R.rdx);
      break;
   case SYS_SEEK: /* Change position in a file. */
      seek(f->R.rdi, f->R.rsi);
      break;
   case SYS_TELL: /* Report current position in a file. */
      f->R.rax = tell(f->R.rdi);
      break;
   case SYS_CLOSE: /* Close a file. */
      close(f->R.rdi);
      break;
   case SYS_MMAP:
      f->R.rax = mmap(f->R.rdi, f->R.rsi, f->R.rdx, f->R.r10, f->R.r8);
      break;
   case SYS_MUNMAP:
      munmap(f->R.rdi);
      break;
   default:
      thread_exit();
   }
}

/*
power_off()를 호출해서 Pintos를 종료합니다. (power_off()는 src/include/threads/init.h에 선언되어 있음.)
*/
void halt(void)
{
   power_off();
}
/*
현재 동작중인 유저 프로그램을 종료합니다. 커널에 상태를 리턴하면서 종료합니다.
만약 부모 프로세스가 현재 유저 프로그램의 종료를 기다리던 중이라면,
그 말은 종료되면서 리턴될 그 상태를 기다린다는 것 입니다.
관례적으로, 상태 = 0 은 성공을 뜻하고 0 이 아닌 값들은 에러를 뜻 합니다.
*/
void exit(int status)
{
   struct thread *cur = thread_current();
   cur->exit_flag = status;
   printf("%s: exit(%d)\n", cur->name, status);
   thread_exit();
}
/*
위의 함수는 file(첫 번째 인자)를 이름으로 하고 크기가 initial_size(두 번째 인자)인 새로운 파일을 생성합니다.
*/
bool create(const char *file, unsigned initial_size)
{
   check_address(file);
   return filesys_create(file, initial_size);
}

/*
위의 함수는 file(첫 번째)라는 이름을 가진 파일을 삭제합니다.
성공적으로 삭제했다면 true를 반환하고, 그렇지 않으면 false를 반환합니다.
파일은 열려있는지 닫혀있는지 여부와 관계없이 삭제될 수 있고,
파일을 삭제하는 것이 그 파일을 닫았다는 것을 의미하지는 않습니다.
*/
bool remove(const char *file)
{
   check_address(file);
   return filesys_remove(file);
}

/*
THREAD_NAME이라는 이름을 가진 현재 프로세스의 복제본인 새 프로세스를 만듭니다
피호출자(callee) 저장 레지스터인 %RBX, %RSP, %RBP와 %R12 - %R15를 제외한 레지스터 값을 복제할 필요가 없습니다.
 자식 프로세스의 pid를 반환해야 합니다.
*/
pid_t fork(const char *thread_name)
{
   struct thread *cur = thread_current();
   return process_fork(thread_name, &cur->tf);
}
/*
현재의 프로세스가 cmd_line에서 이름이 주어지는 실행가능한 프로세스로 변경됩니다. 이때 주어진 인자들을 전달합니다.
성공적으로 진행된다면 어떤 것도 반환하지 않습니다.
*/
int exec(const char *cmd_line)
{
   char *fn_copy;
   tid_t tid;

   fn_copy = palloc_get_page(PAL_ZERO);
   if (fn_copy == NULL)
      return TID_ERROR;
   strlcpy(fn_copy, cmd_line, PGSIZE);
   tid = process_exec(fn_copy);
   if (tid == -1)
   {
      return -1;
   }
   palloc_free_page(fn_copy);
   return tid;
}
/*
자식 프로세스 (pid) 를 기다려서 자식의 종료 상태(exit status)를 가져옵니다.
만약 pid (자식 프로세스)가 아직 살아있으면, 종료 될 때 까지 기다립니다.
종료가 되면 그 프로세스가 exit 함수로 전달해준 상태(exit status)를 반환합니다.
*/
int wait(pid_t pid)
{
   return process_wait(pid);
}
/*
file(첫 번째 인자)이라는 이름을 가진 파일을 엽니다. 해당 파일이 성공적으로 열렸다면,
파일 식별자로 불리는 비음수 정수(0또는 양수)를 반환하고, 실패했다면 -1를 반환합니다.
*/
int open(const char *file)
{
   check_address(file);
   struct file *open_file = filesys_open(file);
   if (open_file == NULL)
   {
      return -1;
   }
   int fd = process_add_file(open_file);
   if (fd == -1)
   {
      file_close(open_file);
   }
   return fd;
}
/*
fd(첫 번째 인자)로서 열려 있는 파일의 크기가 몇 바이트인지 반환합니다.
*/
int filesize(int fd)
{

   struct file *find_file = process_get_file(fd);
   if (find_file == NULL)
      return -1;
   return file_length(find_file);
}
/*
buffer 안에 fd 로 열려있는 파일로부터 size 바이트를 읽습니다.
실제로 읽어낸 바이트의 수 를 반환합니다 (파일 끝에서 시도하면 0).
파일이 읽어질 수 없었다면 -1을 반환합니다.
*/
int read(int fd, void *buffer, unsigned size)
{
   check_valid_buffer(buffer, size, 1);
   int file_size;
   char *read_buffer = buffer;
   if (fd == 0)
   {
      char key;
      for (file_size = 0; file_size < size; file_size++)
      {
         key = input_getc();
         *read_buffer++ = key;
         if (key == '\0')
         {
            break;
         }
      }
   }
   else if (fd == 1)
   {
      return -1;
   }
   else
   {
      struct file *read_file = process_get_file(fd);
      if (read_file == NULL)
      {
         return -1;
      }
      lock_acquire(&filesys_lock);
      file_size = file_read(read_file, buffer, size);
      lock_release(&filesys_lock);
   }
   return file_size;
}
/*
buffer로부터 open file fd로 size 바이트를 적어줍니다.
실제로 적힌 바이트의 수를 반환해주고,
일부 바이트가 적히지 못했다면 size보다 더 작은 바이트 수가 반환될 수 있습니다.
*/
int write(int fd, const void *buffer, unsigned size)
{
   check_valid_buffer(buffer, size, 0);
   int file_size;
   if (fd == STDOUT_FILENO)
   {
      putbuf(buffer, size);
      file_size = size;
   }
   else if (fd == STDIN_FILENO)
   {
      return -1;
   }
   else
   {
      struct file *file = process_get_file(fd);
      if(file == NULL){
         return -1;
      }
      lock_acquire(&filesys_lock);
      file_size = file_write(file, buffer, size);
      lock_release(&filesys_lock);
   }
   return file_size;
}

/*
open file fd에서 읽거나 쓸 다음 바이트를 position으로 변경합니다.
position은 파일 시작부터 바이트 단위로 표시됩니다.
(따라서 position 0은 파일의 시작을 의미합니다).
*/
void seek(int fd, unsigned position)
{
   /*
   Changes the next byte to be read or written in open file fd to position.
   Use void file_seek(struct file *file, off_t new_pos).
   */
   struct file *seek_file = process_get_file(fd);
   if (fd < 2)
   {
      return;
   }
   return file_seek(seek_file, position);
}
/*
열려진 파일 fd에서 읽히거나 써질 다음 바이트의 위치를 반환합니다.
파일의 시작지점부터 몇바이트인지로 표현됩니다.
*/
unsigned tell(int fd)
{
   // Use off_t file_tell(struct file *file).
   struct file *tell_file = process_get_file(fd);
   return file_tell(tell_file);
}
/*
파일 식별자 fd를 닫습니다. 프로세스를 나가거나 종료하는 것은 묵시적으로 그 프로세스의 열려있는 파일 식별자들을 닫습니다.
마치 각 파일 식별자에 대해 이 함수가 호출된 것과 같습니다.
*/
void close(int fd)
{
   struct file *close_file = process_get_file(fd);
   if (close_file == NULL)
   {
      return -1;
   }
   process_close_file(fd);
   return file_close(close_file);
}
/*
주소 값이 유저 영역 주소 값인지 확인
유저 영역을 벗어난 영역일 경우 프로세스 종료(exit(-1)
*/
struct page *check_address(void *addr)
{
   struct thread *curr = thread_current();
#ifdef VM
   if (is_kernel_vaddr(addr) || !addr)
   {
      exit(-1);
   }
   struct page *page = NULL;
   page = spt_find_page(&thread_current()->spt, addr);
   if(page == NULL){
      exit(-1);
   }
   return page;
#else
   if (!is_user_vaddr(addr) || is_kernel_vaddr(addr) || pml4_get_page(curr->pml4, addr) == NULL)
   {
      exit(-1);
   }
#endif
}

void check_valid_buffer(void *buffer, unsigned size, bool to_write)
{
   for (char i = 0; i < size; i++)
   {
      struct page *page = check_address(buffer + i);
      if(to_write == true && page->writable == false){
         exit(-1);
      }
   }
}
void *mmap (void *addr, size_t length, int writable, int fd, off_t offset){

   if(offset % PGSIZE != 0){
		return NULL;
	}
	if(pg_round_down(addr)!= addr || is_kernel_vaddr(addr) || addr == NULL || (long long)length <= 0){
		return NULL;
	}
	
	if(spt_find_page(&thread_current()->spt, addr)){
		return NULL;
	}
	
	if(fd < FD_MIN){
		exit(-1);
	}

	struct file * target = process_get_file(fd);
	if (target == NULL){
		return NULL;
	}
   return do_mmap(addr, length, writable, target, offset);
}
void munmap (void *addr){
   if(is_kernel_vaddr(addr) || !addr){
      // TODO: @@@@ 혹시 모를 찝찝함.....
      exit(-1);
   }
   do_munmap(addr);
}