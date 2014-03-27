# Makefile simplifying dev process

.PHONY: init build test

init:
	ptxdist images
	ptxdist test flash-all

build:
	ptxdist clean game
	ptxdist clean driver-gamepad
	ptxdist go
	ptxdist image root.romfs
	ptxdist test flash-rootfs

test:
	make build
	miniterm.py -b 115200 -p /dev/ttyS0
