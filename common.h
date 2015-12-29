#ifdef COMMON_H
#define COMMON_H

typedef unsigned int u32int;
typedef int s32int;
typedef unsigned short u16int;
typedef short s16int;
typedef unsigned char u8int;
typedef char s8int;

struct regs{
  unsigned int gs, fs, ds, es;
  unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
  unsigned int int_no, error_code;
  unsigned int eip, cs, eflags, useresp, ss;
}

void outb(u16int port, u8int value);
u8int inb(u16int port);
u16int inw(u16int port);

void memcpy(u8int *dest, u8int val, u32int len );
void memset(u8int *dest, u8int val, u32int len );

int strcmp(char *str1, char *str2);
char *strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *src);

#endif
