#ifdef GDT_H
#define GDT_H

#include "common.h"


struct gdt_entry{
  u16int limit_low;
  u16int base_low;
  u8int base_middle;
  u8int access;
  u8int base_high;
}__attribute__((packed));

struct gdt_ptr{
  u16int limit;
  u32int base;
}__attribute__((packed));

struct gdt_entry gdt[3];
struct gdt_ptr gp;

extern void gdt_flush();
void gdt_install();

void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);

#endif
