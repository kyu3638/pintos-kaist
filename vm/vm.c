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
static struct frame *
vm_get_victim(void)
{
	struct frame *victim = NULL;
	/* TODO: The policy for eviction is up to you. */

	return victim;
}

/* Evict one page and return the corresponding frame.
 * Return NULL on error.*/
static struct frame *
vm_evict_frame(void)
{
	struct frame *victim UNUSED = vm_get_victim();
	/* TODO: swap out the victim and return the evicted frame. */

	return NULL;
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
		PANIC("todo");
	}
	/* TODO: Fill this function. */
	frame->page = NULL;
	ASSERT(frame != NULL);
	ASSERT(frame->page == NULL);
	return frame;
}

/* Growing the stack. */
static void
vm_stack_growth(void *addr UNUSED)
{
	addr = pg_round_down(addr);
	while(addr < thread_current()->stack_bottom){
		vm_alloc_page(VM_ANON, addr, 1);
		vm_claim_page(addr);
		addr += PGSIZE;
	}
}

/* Handle the fault on write_protected page */
static bool
vm_handle_wp(struct page *page UNUSED)
{
	
}

/* Return true on success */
bool vm_try_handle_fault(struct intr_frame *f UNUSED, void *addr UNUSED, bool user UNUSED, bool write UNUSED, bool not_present UNUSED)
{
	struct supplemental_page_table *spt UNUSED = &thread_current()->spt;
	struct page *page = NULL;
	/* TODO: Validate the fault */
	/* TODO: Your code goes here */
	if (is_kernel_vaddr(addr) || !not_present)
	{
		return false;
	}
	page = spt_find_page(spt, addr);
	if(page == NULL){
		if(addr < USER_STACK && addr >= USER_STACK-(1<<20) && f->rsp - (1<<3) <= addr && addr <= thread_current()->stack_bottom){
			vm_stack_growth(addr);
			thread_current()->stack_bottom = pg_round_down(addr);
			return true;
		}
	}
	else{
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
	/* TODO: Fill this function */
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
	bool succ = false;
	struct hash_iterator i;
   	hash_first (&i, &src->vm);
   	while (hash_next (&i))
   	{
   		struct page *page = hash_entry (hash_cur (&i), struct page, h_elem);
		if(page->uninit.aux != NULL){
			// TODO: @@@@ 혹시 모를 찝찝함.....
			struct info *aux = (struct info*)malloc(sizeof(struct info));
			memcpy(aux, page->uninit.aux, sizeof(struct info));
			vm_alloc_page_with_initializer(page->uninit.type, page->va, page->writable, page->uninit.init, aux);
		}
		else{
			vm_alloc_page_with_initializer(page->uninit.type, page->va, page->writable, page->uninit.init, page->uninit.aux);
		}
		struct page *child_page = spt_find_page(dst, page->va);
		if(page->frame != NULL){
			succ = vm_do_claim_page(child_page);
			if(!succ){
				return false;
			}
			memcpy(child_page->frame->kva, page->frame->kva, PGSIZE);
		}
		// switch (page_get_type(page)){

		// case VM_UNINIT:
		// {
		// 	struct info *aux = malloc(sizeof(struct info));
		// 	memcpy(aux, page->uninit.aux, sizeof(struct info));
		// 	vm_alloc_page_with_initializer(page->uninit.type, page->va, page->writable, page->uninit.init, aux);
		// 	struct page *child_page = spt_find_page(dst, page->va);
		// 	succ = vm_do_claim_page(child_page);
		// 	if(!succ){
		// 		return false;
		// 	}
		// 	if(page->frame != NULL){
		// 		memcpy(child_page->frame->kva, page->frame->kva, PGSIZE);
		// 	}
		// 	break;
		// }
		// case VM_ANON:
		// 	break;

		// case VM_FILE:

		// 	break;

		// default:
		// 	break;
		// }
   	// }
	}
	return succ;
}

/* Free the resource hold by the supplemental page table */
void supplemental_page_table_kill(struct supplemental_page_table *spt UNUSED)
{
	/* TODO: Destroy all the supplemental_page_table hold by thread and
	 * TODO: writeback all the modified contents to the storage. */
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