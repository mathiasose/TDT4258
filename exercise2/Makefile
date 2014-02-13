# Example Makefile
#
# Exercise 2, TDT4258

CC=arm-none-eabi-gcc
LD=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

CFLAGS=-mcpu=cortex-m3 -mthumb -g -std=c99 -Wall
LDFLAGS=-mcpu=cortex-m3 -mthumb -g -lgcc -lc -lcs3 -lcs3unhosted -lefm32gg -Llib
ASFLAGS=-mcpu=cortex-m3 -mthumb -g
LINKERSCRIPT=lib/efm32gg.ld

exe/main.bin: exe/main.elf
	${OBJCOPY} -O binary $< $@

exe/main.elf: build/main.o build/timer.o build/dac.o build/gpio.o build/interrupt_handlers.o
	${LD} -T ${LINKERSCRIPT} $^ -o $@ ${LDFLAGS} 

build/%.o : src/%.c
	${CC} ${CFLAGS} -c $< -o $@

.PHONY: upload
upload:
	-eACommander.sh -r --address 0x00000000 -f "exe/main.bin" -r

.PHONY: clean
clean:
	-rm -rf build/*.o exe/*.elf exe/*.bin *.hex

.PHONY: run
run:
	make
	make upload
