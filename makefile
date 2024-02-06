build_dir = ./build
source_dir = ./src


nasm = nasm
nasm_flags = -f bin
asm_sources = $(source_dir)/boot.asm

qemu = qemu-system-i386 

all: kernel move
	$(qemu) $(build_dir)/kernel.bin

move:
	cp kernel.bin $(build_dir)

kernel: $(sources)
	$(nasm) $(asm_sources) $(nasm_flags) -o kernel.bin

clean:
	rm kernel.bin
	rm $(build_dir)/kernel.bin

debug:
	od -t x1 -A n kernel.bin
