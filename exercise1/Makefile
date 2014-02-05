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
	mkdir -p exe
	${OBJCOPY} -j .text -O binary $< $@

build/main.elf : build/main.o
	mkdir -p build
	${LD} -T ${LINKERSCRIPT} $^ -o $@ ${LDFLAGS} 

build/main.o : src/main.s
	mkdir -p build
	${AS} ${ASFLAGS} $< -o $@

.PHONY : upload
upload :
	-eACommander.sh -r --address 0x00000000 -f "exe/main.bin" -r

.PHONY : clean
clean :
	-rm -rf build/ exe/

.PHONY : run
run :
	make
	make upload
