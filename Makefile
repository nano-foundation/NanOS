CC = gcc
CFLAGS=  -nostdlib -nostdinc -fno-builtin -fno-stack-protector -lm -c
LDFLAGS=-Tlink.ld
ASFLAGS=-felf

SOURCES = boot.o main.o terminal.o common.o gdt.o lgdt.o idt.o lidt.o lisr.o isr.o lirq.o irq.o kbd.o kheap.o

all: $(SOURCES) link

c.o:
	$(CC) $< $(CFLAGS)

link:
	ld $(LDFLAGS) *.o -o NanOS.bin $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<

clean:
	rm -rvf *.o
