#include "terminal.h"
#include "idt.h"
#include "isr.h"
#include "irq.h"
#include "gdt.h"
#include "kbd.h"
#include "kheap.h"

int main(struct multiboot *multiboot_ptr){
  char c = 'n';
  terminal_init(1, 15);
  terminal_write_on_line("NanOS version 0.0.2", 0, 12, 15);
}
