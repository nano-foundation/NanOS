#include "terminal.h"

void terminal_init(int backcolor, int forecolor)
{
   // The VGA framebuffer starts at 0xB8000.
   videomem = (u16int *)0xB8000;
   // Stores the cursor position.
   cursor_x = 0;
   cursor_y = 0;

   attributeByte = (backcolor << 4) | (forecolor & 0x0F);
   attribute = attributeByte << 8;

   terminal_clear();
}

void terminal_attrib(int backcolor, int forecolor)
{
   attributeByte = (backcolor << 4) | (forecolor & 0x0F);
   attribute = attributeByte << 8;
}

static void move_cursor()
{
    u16int cursorLocation = cursor_y * 80 + cursor_x;
    outb(0x3D4, 14);
    outb(0x3D5, cursorLocation >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, cursorLocation);
}

static void scroll()
{
    u16int blank = 0x20 /* space */ | attribute;
    if(cursor_y >= 25)
    {
        int i;
        for (i = 0*80; i < 24*80; i++)
        {
            videomem[i] = videomem[i+80];
        }
        for (i = 24*80; i < 25*80; i++)
        {
            videomem[i] = blank;
        }

        cursor_y = 24;
    }
}

void terminal_put(char c)
{
    u16int *location;
    if (c == 0x08 && cursor_x)
    {
        cursor_x--;
    }
    else if (c == 0x09)
    {
        cursor_x = (cursor_x+8) & ~(8-1);
    }

    else if (c == '\r')
    {
        cursor_x = 0;
    }

    else if (c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }
    else if(c >= ' ')
    {
        location = videomem + (cursor_y*80 + cursor_x);
        *location = c | attribute;
        cursor_x++;
    }

    if (cursor_x >= 80)
    {
        cursor_x = 0;
        cursor_y ++;
    }
    scroll();
    move_cursor();

}

void terminal_clear()
{

    u16int blank = 0x20 /* space */ | attribute;

    int i;
    for (i = 0; i < 80*25; i++)
    {
        videomem[i] = blank;
    }
    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}

void terminal_write(char *c)
{
    int i = 0;
    while (c[i])
    {
        terminal_put(c[i++]);
    }
}

void terminal_write_on_line(char *c, int line, int backcolor, int forecolor)
{
   int i;

   u16int tmp_attrib = attribute;
   u8int tmp_attribbyte = attributeByte;

   cursor_y = line;
   cursor_x = 0;

   attributeByte = (backcolor << 4) | (forecolor & 0x0F);
   attribute = attributeByte << 8;

   terminal_write(c);

   for(i = cursor_x; i < 80; i++)
     terminal_put(' ');

   cursor_y = line + 1;
   cursor_x = 0;

   attributeByte = tmp_attribbyte;
   attribute = tmp_attrib;

   move_cursor();
}

void terminal_write_hex(u32int n)
{
    s32int tmp;

    terminal_write("0x");
    char noZeroes = 1;

    int i;
    for (i = 28; i > 0; i -= 4)
    {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && noZeroes != 0)
        {
            continue;
        }

        if (tmp >= 0xA)
        {
            noZeroes = 0;
            terminal_put (tmp-0xA+'a' );
        }
        else
        {
            noZeroes = 0;
            terminal_put( tmp+'0' );
        }
    }

    tmp = n & 0xF;
    if (tmp >= 0xA)
    {
        terminal_put (tmp-0xA+'a');
    }
    else
    {
        terminal_put (tmp+'0');
    }
}

void terminal_write_dec(u32int n)
{
    if (n == 0)
    {
      terminal_put('0');
        return;
    }

    s32int acc = n;
    char c[32];
    int i = 0;
    while (acc > 0)
    {
        c[i] = '0' + acc%10; 	// Puts inverse number in *c
        acc /= 10;
        i++;
    }
    c[i] = 0;

    char c2[32];
    c2[i--] = 0;
    int j = 0;
    while(i >= 0)
    {
        c2[i--] = c[j++];  	// Inverses the number to make it fine.
    }
    terminal_write(c2);
}
