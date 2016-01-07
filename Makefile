CC = i686-elf-gcc
CFLAGS= -Wall -Werror -nostdlib -nostdinc -fno-builtin -fno-stack-protector
LDFLAGS=-Tlink.ld
ASFLAGS=-felf

SOURCES = boot.o main.o terminal.o common.o gdt.o lgdt.o idt.o lidt.o lisr.o isr.o lirq.o irq.o kbd.o kheap.o

all: $(SOURCES) link

link:
	i686-elf-ld $(LDFLAGS) *.o -o NanOS.bin $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<

clean:
	rm -rvf *.o
