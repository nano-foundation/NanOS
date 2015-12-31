#ifdef TERHMINAL_H
#define TERHMINAL_H

#include "common.h"

u16int *videomem;
u8int attributeByte;
u16int attribute;
u8int cursor_y; u8int cursor_x;

void terminal_init(int backcolor, int forecolor);
void terminal_attrib(int backcolor, int forecolor);
void terminal_put(char c);
void terminal_clear();
void terminal_write(char *c);
void terminal_write_on_line(char *c, int line, int backcolor, int forecolor);
void terminal_write_hex(u32int n);
void terminal_write_dec(u32int n);
void terminal_clear();

#endif
