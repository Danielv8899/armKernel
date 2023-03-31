CC=arm-linux-gnueabihf-gcc
LD=arm-linux-gnueabihf-ld

CFLAGS=-ansi -pedantic -Wall -Wextra -march=armv6 -msoft-float -fPIC -mapcs-frame
LDFLAGS=-N -Ttext=0x10000

kernel.elf: bootstrap.o kernel.o

.PHONY: clean

clean:
	$(RM) *.elf *.o

.SUFFIXES: .s .o .elf

.s.o:
	$(CC) $(CFLAGS) -o $@ -c $^

.o.elf:
	$(LD) $(LDFLAGS) -o $@ $^