#include "ISR.h"
#include "IDT.h"


const char* exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};


void isr_install() {
    set_idt_gate(0, (uint32)isr0);
    set_idt_gate(1, (uint32)isr1);
    set_idt_gate(2, (uint32)isr2);
    set_idt_gate(3, (uint32)isr3);
    set_idt_gate(4, (uint32)isr4);
    set_idt_gate(5, (uint32)isr5);
    set_idt_gate(6, (uint32)isr6);
    set_idt_gate(7, (uint32)isr7);
    set_idt_gate(8, (uint32)isr8);
    set_idt_gate(9, (uint32)isr9);
    set_idt_gate(10, (uint32)isr10);
    set_idt_gate(11, (uint32)isr11);
    set_idt_gate(12, (uint32)isr12);
    set_idt_gate(13, (uint32)isr13);
    set_idt_gate(14, (uint32)isr14);
    set_idt_gate(15, (uint32)isr15);
    set_idt_gate(16, (uint32)isr16);
    set_idt_gate(17, (uint32)isr17);
    set_idt_gate(18, (uint32)isr18);
    set_idt_gate(19, (uint32)isr19);
    set_idt_gate(20, (uint32)isr20);
    set_idt_gate(21, (uint32)isr21);
    set_idt_gate(22, (uint32)isr22);
    set_idt_gate(23, (uint32)isr23);
    set_idt_gate(24, (uint32)isr24);
    set_idt_gate(25, (uint32)isr25);
    set_idt_gate(26, (uint32)isr26);
    set_idt_gate(27, (uint32)isr27);
    set_idt_gate(28, (uint32)isr28);
    set_idt_gate(29, (uint32)isr29);
    set_idt_gate(30, (uint32)isr30);
    set_idt_gate(31, (uint32)isr31);

    set_idt(); // Load with ASM
}

/*Handlers*/
void isr0()
{
    kprint(exception_messages[0], 0);
    asm("hlt");    
}
void isr1()
{
    kprint(exception_messages[1], 0);    
    asm("hlt");
}
void isr2()
{
    kprint(exception_messages[2], 0);    
    asm("hlt");
}
void isr3()
{
    kprint(exception_messages[3], 0);    
    asm("hlt");
}
void isr4()
{
    kprint(exception_messages[4], 0);    
    asm("hlt");
}
void isr5()
{
    kprint(exception_messages[5], 0);    
    asm("hlt");
}
void isr6()
{
    kprint(exception_messages[6], 0);    
    asm("hlt");
}
void isr7()
{
    kprint(exception_messages[7], 0);    
    asm("hlt");
}
void isr8()
{
    kprint(exception_messages[8], 0);    
    asm("hlt");
}
void isr9()
{
    kprint(exception_messages[9], 0);    
    asm("hlt");
}
void isr10()
{
    kprint(exception_messages[10], 0);    
    asm("hlt");
}

void isr11()
{
    kprint(exception_messages[11], 0);    
    asm("hlt");
}
void isr12()
{
    kprint(exception_messages[12], 0);    
    asm("hlt");
}
void isr13()
{
    kprint(exception_messages[13], 0);    
    asm("hlt");
}
void isr14()
{
    kprint(exception_messages[14], 0);    
    asm("hlt");
}
void isr15()
{
    kprint(exception_messages[15], 0);    
    asm("hlt");
}
void isr16()
{
    kprint(exception_messages[16], 0);    
    asm("hlt");
}
void isr17()
{
    kprint(exception_messages[17], 0);    
    asm("hlt");
}
void isr18()
{
    kprint(exception_messages[18], 0);    
    asm("hlt");
}
void isr19()
{
    kprint(exception_messages[19], 0);    
    asm("hlt");
}
void isr20()
{
    kprint(exception_messages[20], 0);    
    asm("hlt");
}
void isr21()
{
    kprint(exception_messages[21], 0);    
    asm("hlt");
}
void isr22()
{
    kprint(exception_messages[22], 0);    
    asm("hlt");
}
void isr23()
{
    kprint(exception_messages[23], 0);    
    asm("hlt");
}
void isr24()
{
    kprint(exception_messages[24], 0);    
    asm("hlt");
}
void isr25()
{
    kprint(exception_messages[25], 0);    
    asm("hlt");
}
void isr26()
{
    kprint(exception_messages[26], 0);    
    asm("hlt");
}
void isr27()
{
    kprint(exception_messages[27], 0);    
    asm("hlt");
}
void isr28()
{
    kprint(exception_messages[28], 0);    
    asm("hlt");
}
void isr29()
{
    kprint(exception_messages[29], 0);    
    asm("hlt");
}
void isr30()
{
    kprint(exception_messages[30], 0);    
    asm("hlt");
}
void isr31()
{
    kprint(exception_messages[31], 0);    
    asm("hlt");
}


/*End Handlers*/

