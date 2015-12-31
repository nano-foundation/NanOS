#include "common.h"

void kbd_install();
void kbd_handler(struct regs* r);
char kbd_get();
char* kbd_read();
