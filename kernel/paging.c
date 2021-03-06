#include <paging.h>
#include <arch/x86/kheap.h>
#include <panic.h>
#include <libk/printf.h>

// The kernel's page directory
page_directory_t *kernel_directory=0;

// The current page directory
page_directory_t *current_directory=0;

// A bitset of freames - used or free
uint32_t *frames;
uint32_t nframes;

// Defined in kheap.c
extern uint32_t placement_address;
extern heap_t *kheap;

// Macros used in the bitset algorithms
#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

// Static function to set a bit int the frames bitset
static void set_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr/0x1000;
	uint32_t idx = INDEX_FROM_BIT(frame);
	uint32_t off = OFFSET_FROM_BIT(frame);
	frames[idx] |= (0x1 << off);
}

static void clear_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr/0x1000;
	uint32_t idx = INDEX_FROM_BIT(frame);
	uint32_t off = OFFSET_FROM_BIT(frame);
	frames[idx] &= ~(0x1 << off);
}

static uint32_t test_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr/0x1000;
	uint32_t idx = INDEX_FROM_BIT(frame);
	uint32_t off = OFFSET_FROM_BIT(frame);
	return (frames[idx] & (0x1 << off));
}

static uint32_t first_frame()
{
	uint32_t i, j;
	for (i = 0; i < INDEX_FROM_BIT(nframes); ++i)
	{
		if (frames[i] != 0xFFFFFFFF) // nothing free, exit early
			for (j = 0; j < 32; ++j)
			{
				uint32_t toTest = 0x1 << j;
				if(!(frames[i]&toTest))
					return i*4*8+j;
			}
	}
}

// Function to allocate frame
void alloc_frame(page_t *page, int is_kernel, int is_writeable)
{
	if (page->frame != 0)
		return; // Frame was allocate for this page
	else
	{
		uint32_t idx = first_frame(); // index of the first frame
		if(idx == (uint32_t)-1)
			panic("No free frames!");

		set_frame(idx*0x1000); // block frame
		page->present = 1;
		page->rw = (is_writeable)?1:0;
		page->user = (is_kernel)?0:1;
		page->frame = idx;
	}
}

void free_frame(page_t *page)
{
	uint32_t frame;
	if(!(frame = page->frame))
		return; // Frame for this page not allocated
	else
	{
		clear_frame(frame);
		page->frame = 0x0;
	}
}

void init_paging()
{
    //For start our memsize = 16Mib
	uint32_t mem_end_page = 0x1000000;

	nframes = mem_end_page / 0x1000;
	frames = (uint32_t*)kmalloc(INDEX_FROM_BIT(nframes));
	memset(frames, 0, INDEX_FROM_BIT(nframes));

	//Create page directory
	kernel_directory = (page_directory_t*)kmalloc_a(sizeof(page_directory_t));
	memset(kernel_directory, 0, sizeof(page_directory_t));
	current_directory = kernel_directory;

    /**
      * Map some pages in the kernel heap area.
      * Here we call get_page but not alloc_frame. This causes page_table_t's
      * to be created where necessary. We can't allocate frames yet because they need
      * to be identity mapped first below, and yet we can't increase placement_addres
      * between identity mapping and enabling the heap.
      */
    int i = 0;
    for(i = KHEAP_START; i < KHEAP_START + KHEAP_MIN_SIZE; i += PAGE_SIZE)
        get_page(i, 1, kernel_directory);

    // We should place heap_t structure before we turn paging on
    uint32_t kheap_addr = kmalloc(sizeof(heap_t));

	/**
	 * Теперь нам необходимо тождественно отобразить
	 * адреса виртуальной памяти на адреса физической памяти,
	 * чтобы мы могли прозрачно обращаться к физической памяти,
	 * как будто страничная адресация не включена.
	 * Обратите внимание что мы специально используем здесь
	 * цикл while, т.к. внутри тела цикла значение переменной
	 * placement_address изменяется при вызове kmalloc().
	 */
    i = 0;
	while (i < placement_address)
	{
		// Kernel source not avaliable for write in user space
		alloc_frame( get_page(i, 1, kernel_directory),0,0);
		i += 0x1000;
	}

    // Now allocate those pages we mapped earlier
    for(i = KHEAP_START; i < KHEAP_START + KHEAP_MIN_SIZE; i += PAGE_SIZE)
        alloc_frame( get_page(i, 0, kernel_directory), 0, 0 );

    // Before we enable paging, we must register our page fault handler
	register_interrupt_handler(14, page_fault);

    // Enable paging
	switch_page_directory(kernel_directory);

    // Initialise the kernel heap.
    kheap = create_heap(kheap_addr, KHEAP_START, KHEAP_START + KHEAP_MIN_SIZE, 0xCFFFF000, 0, 0);
}

void switch_page_directory(page_directory_t *dir)
{
	current_directory = dir;
	__asm__ volatile ("mov %0, %%cr3"::"r"(&dir->tablesPhysical));
	uint32_t cr0;
	__asm__ volatile ("mov %%cr0, %0": "=r"(cr0));
	cr0 |= 0x80000000; // ВКЛ
	__asm__ volatile ("mov %0, %%cr0":: "r"(cr0));
}

page_t *get_page(uint32_t address, int make, page_directory_t *dir)
{
	// Make index from address 
	address /= 0x1000;
	// Search table containing index
	uint32_t table_idx = address / 1024;
	if (dir->tables[table_idx]) // Если таблица уже создана
		return &dir->tables[table_idx]->pages[address%1024];
	else if(make)
	{
		uint32_t tmp;
		dir->tables[table_idx] = (page_table_t*)kmalloc_ap(sizeof(page_table_t), &tmp);
		memset(dir->tables[table_idx], 0, 0x1000);
		dir->tablesPhysical[table_idx] = tmp | 0x7; // PRESENT, RW, US
		return &dir->tables[table_idx]->pages[address%1024];
	}
	else
		return 0;
}

void page_fault(registers_t regs)
{
	// Произошло прерывание page fault
	// Адрес по которому произошло прерывание содержится в регистре CR2
	uint32_t faulting_address;
	__asm__ volatile ("mov %%cr2, %0" : "=r"(faulting_address));

	// Код ошибки сообщит нам подробности произошедшего
	int present = !(regs.err_code & 0x1);	// Page not present
	int rw = regs.err_code & 0x2;			// Write operation ?
	int us = regs.err_code & 0x4;			// Processor was in user-mode?
	int reserved = regs.err_code & 0x8;		// Overwritten CPU reserved bits
	int id = regs.err_code & 0x10;			// Caused by an instruction

	// Error message
	printf("Page fault! (");
	if (present) printf("present ");
	if (rw) printf("read-only ");
	if (us) printf("user-mode ");
	if (reserved) printf("reserved ");
	printf(") at 0x%x\n", faulting_address);
	panic("Page fault");
}
