/* anon.c: Implementation of page for non-disk image (a.k.a. anonymous page). */

#include "vm/vm.h"
#include "devices/disk.h"

size_t disk_slice_size = PGSIZE/DISK_SECTOR_SIZE;

/* DO NOT MODIFY BELOW LINE */
static struct disk *swap_disk;
static bool anon_swap_in (struct page *page, void *kva);
static bool anon_swap_out (struct page *page);
static void anon_destroy (struct page *page);

/* DO NOT MODIFY this struct */
static const struct page_operations anon_ops = {
	.swap_in = anon_swap_in,
	.swap_out = anon_swap_out,
	.destroy = anon_destroy,
	.type = VM_ANON,
};

/* Initialize the data for anonymous pages */
void
vm_anon_init (void) {
	/* TODO: Set up the swap_disk. */
	swap_disk = disk_get(1,1);
	disk_sector_t dsize = disk_size(swap_disk) / disk_slice_size;
	swap_table = bitmap_create(dsize);
}


/* Initialize the file mapping */
bool
anon_initializer (struct page *page, enum vm_type type, void *kva) {
	/* Set up the handler */
	page->operations = &anon_ops;

	struct anon_page *anon_page = &page->anon;
}

/* Swap in the page by read contents from the swap disk. */
static bool
anon_swap_in (struct page *page, void *kva) {
	struct anon_page *anon_page = &page->anon;
	// TODO: 디스크에 read시 해당 위치에 값이 없을 수도 있음.
	size_t index = anon_page->index;
	for(int i = 0; i < disk_slice_size; i++){
		disk_read(swap_disk, index * disk_slice_size + i, kva + i * DISK_SECTOR_SIZE);
	}
	bitmap_set(swap_table,index,0);
	anon_page->index = -1;
	return true;
}

/* Swap out the page by writing contents to the swap disk. */
static bool
anon_swap_out (struct page *page) {
	struct anon_page *anon_page = &page->anon;
	size_t index = bitmap_scan(swap_table, 0, 1, false);
	if(index == BITMAP_ERROR){
		return false;
	}
	for(int i = 0; i < disk_slice_size; i++){
		disk_write(swap_disk, index * disk_slice_size + i, page->frame->kva + i * DISK_SECTOR_SIZE);
	}
	bitmap_set(swap_table, index, 1);
	pml4_set_dirty(thread_current()->pml4, page->va, false);
	pml4_clear_page(thread_current()->pml4, page->va);
	anon_page->index = index;
	page->frame = NULL;
	return true;
}

/* Destroy the anonymous page. PAGE will be freed by the caller. */
static void
anon_destroy (struct page *page) {
	struct anon_page *anon_page = &page->anon;
}