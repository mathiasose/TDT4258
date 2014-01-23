# Makefile Group 13
#
# Exercise 1, TDT4258

LD=arm-none-eabi-gcc
AS=arm-none-eabi-as
OBJCOPY=arm-none-eabi-objcopy

LDFLAGS=-nostdlib
ASFLAGS=-mcpu=cortex-m3 -mthumb -g

LINKERSCRIPT=efm32gg.ld

exe/main.bin : build/main.elf
	${OBJCOPY} -j .text -O binary $< $@

build/main.elf : build/main.o 
	${LD} -T ${LINKERSCRIPT} $^ -o $@ ${LDFLAGS} 

build/ex1.o : src/main.s
	${AS} ${ASFLAGS} $< -o $@

.PHONY : upload
upload :
	-eACommander.sh -r --address 0x00000000 -f "exe/main.bin" -r

.PHONY : clean
clean :
	-rm -rf *.o *.elf *.bin *.hex
