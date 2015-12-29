#ifdef IDT_H
#define IDT_H

#include "common.h"

struct idt_entry{
  unsigned short base_lo;
  unsigned short sel;
  unsigned char always0;
  unsigned char flags;
  unsigned short base_hi;
}__attribute__((packed));

struct idt_ptr{
  unsigned short limit;
  u32int base;
}__attribute__((packed));

extern void idt_load();
void idt_install();
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);

#endif
