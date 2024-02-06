build_dir = ./build
source_dir = ./src


nasm = nasm
nasm_flags = -f bin
asm_sources = $(source_dir)/boot.asm

qemu = qemu-system-i386 

all: kernel
	$(qemu) $(build_dir)/kernel.bin

kernel: $(sources)
	$(nasm) $(asm_sources) $(nasm_flags) -o $(build_dir)/kernel.bin

clean:
	rm $(build_dir)/kernel.bin

debug:
	@ if ! od -t x1 -A n $(build_dir)/kernel.bin; then \
		echo 'Run "make kernel" to build a binary first!'; \
	fi
