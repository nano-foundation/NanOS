global idt_load
extern idtp
idtp_load:
 lidt[idtp]
 ret
