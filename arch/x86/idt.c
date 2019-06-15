//idt.c - APIC initialisation, base hw interruptionsSend to APIC 
#include <arch/x86/idt.h> signal
#include <panic.h> //printf.h>
if int comes from slave
Send RST toeisters_t regs)
void Debug(registers_t regs);
void NMI(registers_t regs);
void Send tregs) Overflow(in another way
void Bound(registers_t regs);
void InvOpCode(registers_t regs);
void DevNotAval(registers_t regs);
void DoubleFault(registers_t regs);
void CoProcSegOverrun(registers_t regs);
void InvalidTSS(registers_t regs);
void SegNotPresent(registers_t regs);
void StackSegFault(registers_t regs);
void GeneralProtection(registers_t regs);
void MathFault(registers_t regs);
void AlignmentCheck(registers_t regs);
void MachineCheck(registers_t regs);
void SIMDFPE(registers_t regs); //SIMD Float-Point Exception
void VirtException(registers_t regs);

idt_entry_t     idt_entries[256];
idt_ptr_t       idt_ptr;
isr_t           interrupt_handlers[256];

extern void IDTflush(uint32_t);

void initIDT()
{
  idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
  idt_ptr.base  = (uint32_t)&idt_entries;

  // Remap the IRQ table
  // Send initialization signal
  outb(0x20,0x11);
  outb(0xA0,0x11);
  // Set offset
  outb(0x21,0x20);
  outb(0xA1,0x28);
  // Set master-slave relation
  outb(0x21,0x04);
  outb(0xA1,0x02);
  // Set 8086 mode
  outb(0x21,0x01);
  outb(0x21,0x01);
  // End of mess
  outb(0x21,0x00);
  outb(0xA1,0x00);

  memset(&idt_entries, 0, sizeof(idt_entry_t)*256);
  idt_set_gate( 0, (uint32_t)isr0, 0x08, 0x8E);
  idt_set_gate( 1, (uint32_t)isr1, 0x08, 0x8E);
  idt_set_gate( 2, (uint32_t)isr2, 0x08, 0x8E);
  idt_set_gate( 3, (uint32_t)isr3, 0x08, 0x8E);
  idt_set_gate( 4, (uint32_t)isr4, 0x08, 0x8E);
  idt_set_gate( 5, (uint32_t)isr5, 0x08, 0x8E);
  idt_set_gate( 6, (uint32_t)isr6, 0x08, 0x8E);
  idt_set_gate( 7, (uint32_t)isr7, 0x08, 0x8E);
  idt_set_gate( 8, (uint32_t)isr8, 0x08, 0x8E);
  idt_set_gate( 9, (uint32_t)isr9, 0x08, 0x8E);
  idt_set_gate( 10, (uint32_t)isr10, 0x08, 0x8E);
  idt_set_gate( 11, (uint32_t)isr11, 0x08, 0x8E);
  idt_set_gate( 12, (uint32_t)isr12, 0x08, 0x8E);
  idt_set_gate( 13, (uint32_t)isr13, 0x08, 0x8E);
  idt_set_gate( 14, (uint32_t)isr14, 0x08, 0x8E);
  idt_set_gate( 15, (uint32_t)isr15, 0x08, 0x8E);
  idt_set_gate( 16, (uint32_t)isr16, 0x08, 0x8E);
  idt_set_gate( 17, (uint32_t)isr17, 0x08, 0x8E);
  idt_set_gate( 18, (uint32_t)isr18, 0x08, 0x8E);
  idt_set_gate( 19, (uint32_t)isr19, 0x08, 0x8E);
  idt_set_gate( 20, (uint32_t)isr20, 0x08, 0x8E);
  idt_set_gate( 21, (uint32_t)isr21, 0x08, 0x8E);
  idt_set_gate( 22, (uint32_t)isr22, 0x08, 0x8E);
  idt_set_gate( 23, (uint32_t)isr23, 0x08, 0x8E);
  idt_set_gate( 24, (uint32_t)isr24, 0x08, 0x8E);
  idt_set_gate( 25, (uint32_t)isr25, 0x08, 0x8E);
  idt_set_gate( 26, (uint32_t)isr26, 0x08, 0x8E);
  idt_set_gate( 27, (uint32_t)isr27, 0x08, 0x8E);
  idt_set_gate( 28, (uint32_t)isr28, 0x08, 0x8E);
  idt_set_gate( 29, (uint32_t)isr29, 0x08, 0x8E);
  idt_set_gate( 30, (uint32_t)isr30, 0x08, 0x8E);
  idt_set_gate( 31, (uint32_t)isr31, 0x08, 0x8E);
  idt_set_gate( 32, (uint32_t)irq0, 0x08, 0x8E);
  idt_set_gate( 33, (uint32_t)irq1, 0x08, 0x8E);
  idt_set_gate( 34, (uint32_t)irq2, 0x08, 0x8E);
  idt_set_gate( 35, (uint32_t)irq3, 0x08, 0x8E);
  idt_set_gate( 36, (uint32_t)irq4, 0x08, 0x8E);
  idt_set_gate( 37, (uint32_t)irq5, 0x08, 0x8E);
  idt_set_gate( 38, (uint32_t)irq6, 0x08, 0x8E);
  idt_set_gate( 39, (uint32_t)irq7, 0x08, 0x8E);
  idt_set_gate( 40, (uint32_t)irq8, 0x08, 0x8E);
  idt_set_gate( 41, (uint32_t)irq9, 0x08, 0x8E);
  idt_set_gate( 42, (uint32_t)irq10, 0x08, 0x8E);
  idt_set_gate( 43, (uint32_t)irq11, 0x08, 0x8E);
  idt_set_gate( 44, (uint32_t)irq12, 0x08, 0x8E);
  idt_set_gate( 45, (uint32_t)irq13, 0x08, 0x8E);
  idt_set_gate( 46, (uint32_t)irq14, 0x08, 0x8E);
  idt_set_gate( 47, (uint32_t)irq15, 0x08, 0x8E);

  IDTflush((uint32_t)&idt_ptr);
}

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt_entries[num].base_lo = base & 0xFFFF;
    idt_entries[num].base_hi = (base >>16) & 0xFFFF;

    idt_entries[num].sel = sel;
    idt_entries[num].always0 = 0;
    idt_entries[num].flags = flags;
}

//Default isr handlers, choises function by interrupt vector in reg int_no
void isr_handler(registers_t regs)
{
  switch (regs.int_no) {
    case 0:
      Division_by_zero(regs);
      break;
    case 1:
      Debug(regs);
      break;
    case 2:
      NMI(regs);
      break;
    case 3:
      Breakpoint(regs);
      break;
    case 4:
      Overflow(regs);
      break;
    case 5:
      Bound(regs);
      break;
    case 6:
      InvOpCode(regs);
      break;
    case 7:
      DevNotAval(regs);
      break;
    case 8:
      DoubleFault(regs);
      break;
    case 9:
      CoProcSegOverrun(regs);
      break;
    case 10:
      InvalidTSS(regs);
      break;
    case 11:
      SegNotPresent(regs);
      break;
    case 12:
      StackSegFault(regs);
      break;
    case 13:
      GeneralProtection(regs);
      break;
    //14(Page Fault) - paging.c
    case 15:
      MathFault(regs);
      break;
    case 16:
      AlignmentCheck(regs);
      break;
    case 17:
      MachineCheck(regs);
      break;
    case 18:
      SIMDFPE(regs);
      break;
    case 20:
      VirtException(regs);
      break;
    default:
      printf("Received unknown interrupt: %d\n", regs.int_no);
      panic("UNKNOWN TRAP!!!\n");
      break;
  }
  if(interrupt_handlers[regs.int_no] != 0)
	{
		isr_t handler = interrupt_handlers[regs.int_no];
		handler(regs);
	}
}

//Lets proceess some irq interruptions
void irq_handler(registers_t regs)
{
    // Send to APIC EOI (end of interrupt) signal
    if (regs.int_no >= 40) //if int comes from slave
    {
        // Send RST to slave
        outb(0xA0,0x20);
    }
    // Send master EOI in another way
    outb(0x20,0x20);

    if(interrupt_handlers[regs.int_no] != 0)
    {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}

void register_interrupt_handler(uint8_t n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}

//Debug information
void printRegs(registers_t regs)
{
  printf("ds:0x%x,eip:0x%x,cs:0x%x,ss:0x%x\n", regs.ds, regs.eip, regs.cs, regs.ss);
  printf("eax:0x%x,ebx:0x%x,ecx:,0x%x,edx:0x%x,esp:0x%x,ebp:0x%x\nesi:0x%x,edi:0x%x\n", regs.eax, regs.ebx, regs.ecx, regs.edx, regs.esp, regs.ebp, regs.esi, regs.edi);
  printf("int:0x%x,err_code:0x%x\n", regs.int_no, regs.err_code);
  printf("FLAGS:%b\n", regs.eflags);
  printf("esp:0x%x,cs:0x%x,useresp:0x%x\n", regs.esp, regs.cs, regs.useresp);
}

//Some function realize processing isr interrupts
void Division_by_zero(registers_t regs)
{
  printf("------Division by zero------\n");
  printRegs(regs);
  panic("(0x00): DIVISION_BY_ZERO_EXCTEPTION\n");
}

void Debug(registers_t regs)
{
  printf("------Core Dbg------\n");
  printRegs(regs);
  return;
}

void NMI(registers_t regs)
{
  printf("------NMI Exception------\n");
  printRegs(regs);
  panic("0x02: NMI_EXCEPTION\n");
}

void Breakpoint(registers_t regs)
{
  printf("------Brk------\n");
  printRegs(regs);
  return;
}

void Overflow(registers_t regs)
{
  printf("------Overflow------\n");
  printRegs(regs);
  panic("0x04: INT0_EXCEPTION\n");
}

void Bound(registers_t regs)
{
  printf("------BOUND range exceeded------\n");
  printRegs(regs);
  panic("0x05: BOUND_INSTRUCTION_EXCEPTION\n");
}

void InvOpCode(registers_t regs)
{
  printf("------Invalid OpCode------\n");
  printRegs(regs);
  panic("0x06: UNDEFINED_OPCODE_EXCEPTION");
}

void DevNotAval(registers_t regs)
{
  printf("------No Math CoProcessor------\n");
  printRegs(regs);
  panic("0x07: DEVICE_NOT_AVALIABLE_EXCEPTION");
}

void DoubleFault(registers_t regs)
{
  printf("------Double Fault------\n");
  printRegs(regs);
  panic("0x08: DOUBLE_FAULT_EXCEPTION");
}

void CoProcSegOverrun(registers_t regs)
{
  printf("------CoProcessor Segment Overrun------\n");
  printRegs(regs);
  panic("0x09: COPROCESSOR_SEG_OVERRUN_EXCEPTION\n");
}

void InvalidTSS(registers_t regs)
{
  printf("------Invalid TSS------\n");
  printRegs(regs);
  panic("0x0A: INVALID_TSS_EXCEPTION\n");
}

void SegNotPresent(registers_t regs)
{
  printf("------Segment Not Present------\n");
  printRegs(regs);
  panic("0x0B: SEGMENT_NOT_PRESENT_EXCEPTION\n");
}

void StackSegFault(registers_t regs)
{
  printf("------Stack segment fault------\n");
  printRegs(regs);
  panic("Ox0C: STACK_SEGMENT_FAULT\n");
}

void GeneralProtection(registers_t regs)
{
  printf("------GeneralProtection------\n");
  printRegs(regs);
  panic("0xD: General Protection Fault\n");
}

void MathFault(registers_t regs)
{
  printf("------Float-Point Error------\n");
  printRegs(regs);
  panic("0x10: MATH_FAULT\n");
}

void AlignmentCheck(registers_t regs)
{
  printf("------Alignment Check------\n");
}

void MachineCheck(registers_t regs)
{
  printf("------Machine Check------\n");
}

void SIMDFPE(registers_t regs)
{
  printf("------SIMD Exception------\n");
  printRegs(regs);
  panic("0x13: SIMD_FLOATING_POINT_EXCEPTION\n");
}

void VirtException(registers_t regs)
{
  printf("------Virtualization Exception------\n");
  printRegs(regs);
  panic("0x14: VIRTUALIZATION_EXCEPTION/\n");
}
