/* file.c: Implementation of memory backed file object (mmaped object). */

#include "vm/vm.h"
#include "userprog/process.h"

static bool file_backed_swap_in (struct page *page, void *kva);
static bool file_backed_swap_out (struct page *page);
static void file_backed_destroy (struct page *page);

/* DO NOT MODIFY this struct */
static const struct page_operations file_ops = {
	.swap_in = file_backed_swap_in,
	.swap_out = file_backed_swap_out,
	.destroy = file_backed_destroy,
	.type = VM_FILE,
};

/* The initializer of file vm */
void
vm_file_init (void) {
}

/* Initialize the file backed page */
bool
file_backed_initializer (struct page *page, enum vm_type type, void *kva) {
	struct info *aux = (struct info *)page->uninit.aux;
	/* Set up the handler */
	page->operations = &file_ops;

	struct file_page *file_page = &page->file;
	
}

/* Swap in the page by read contents from the file. */
static bool
file_backed_swap_in (struct page *page, void *kva) {
	struct file_page *file_page UNUSED = &page->file;

	struct file *file = file_page->file;
	off_t ofs = file_page->offset;
	size_t read_bytes = file_page->read_bytes;
	size_t zero_bytes = PGSIZE - read_bytes;

	if(file_read_at(file,kva,read_bytes,ofs) != (int) read_bytes){
		return false;
	}
	memset(kva + read_bytes, 0, zero_bytes);
	return true;
}

/* Swap out the page by writeback contents to the file. */
static bool
file_backed_swap_out (struct page *page) {
	struct file_page *file_page UNUSED = &page->file;

	struct info *info = (struct info*)page->uninit.aux;
	file_page->offset = ((struct info*)page->uninit.aux)->offset;
	file_page->file = ((struct info*)page->uninit.aux)->file;
	file_page->read_bytes = ((struct info*)page->uninit.aux)->read_bytes;

	if(pml4_is_dirty(thread_current()->pml4, page->va)){
		lock_acquire(&filesys_lock);
		file_write_at(info->file, page->va, info->read_bytes, info->offset);
		lock_release(&filesys_lock);
		pml4_set_dirty(thread_current()->pml4, page->va, false);
	}
	pml4_clear_page(thread_current()->pml4,page->va);
	return true;
}

/* Destory the file backed page. PAGE will be freed by the caller. */
static void
file_backed_destroy (struct page *page) {
	struct file_page *file_page UNUSED = &page->file;
	free(page->frame);
}

static bool lazy_mmap(struct page *page, void *aux) {
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
	uint8_t *kva = page->frame->kva;
	if (kva == NULL){
		free(page);
		return false;
	}
	
	if (file_read_at(file, load_frame->kva, page_read_bytes, offset) != (int)page_read_bytes)
	{
		free(page);
		free(file_info);
		return false;
	}
	memset(load_frame->kva + page_read_bytes, 0, page_zero_bytes);

	return true;
}

/* Do the mmap */
void *
do_mmap (void *addr, size_t length, int writable, struct file *file, off_t offset) {

	struct file *reopen_file = file_reopen(file);
	size_t file_size = (size_t) file_length(reopen_file);
	void *init_addr = addr;
	size_t read_bytes = file_size >= length ? length : file_size;
	size_t zero_bytes = (PGSIZE - (read_bytes % PGSIZE)) % PGSIZE;

	while (read_bytes > 0 || zero_bytes > 0)
	{
		/* Do calculate how to fill this page.
		 * We will read PAGE_READ_BYTES bytes from FILE
		 * and zero the final PAGE_ZERO_BYTES bytes. */
		size_t page_read_bytes = read_bytes < PGSIZE ? read_bytes : PGSIZE;
		size_t page_zero_bytes = PGSIZE - page_read_bytes;

		/* project 3 virtual memory */
		struct info *file_info = (struct info *)malloc(sizeof(struct info));
		file_info->file = reopen_file;
		file_info->offset = offset;
		file_info->read_bytes = page_read_bytes;

		/* TODO: Set up aux to pass information to the lazy_load_segment. */

		if (!vm_alloc_page_with_initializer(VM_FILE, addr, writable, lazy_mmap, file_info)){
			free(file_info);
			return false;
		}

		/* Advance. */
		read_bytes -= page_read_bytes;
		zero_bytes -= page_zero_bytes;
		addr += PGSIZE;
		offset += page_read_bytes;
	}
	return init_addr;
}

/* Do the munmap */
void
do_munmap (void *addr) {
	struct thread *cur = thread_current();
	struct page *page = spt_find_page(&cur->spt, addr);
	if(page == NULL){
		return;
	}
	while(page != NULL){
		struct info* info = (struct info*)page->uninit.aux;
		if(pml4_is_dirty(cur->pml4, addr)){
			lock_acquire(&filesys_lock);
			file_write_at(info->file, addr, info->read_bytes, info->offset);
			lock_release(&filesys_lock);
			pml4_set_dirty(cur->pml4, addr, 0);
		}
		pml4_clear_page(cur->pml4, page->va);
		addr += PGSIZE;
		page = spt_find_page(&cur->spt, addr);
	}
}