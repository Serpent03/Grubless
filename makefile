build_dir = ./build
source_dir = ./src

nasm = nasm
nasm_flags = -f bin
asm_sources = boot.asm

qemu = qemu-system-i386 
drive = hd0
qemu_flags = -m 512
qemu_drive = -drive file=fat:rw:$(drive)

all: kernel
	$(qemu) $(build_dir)/kernel.bin $(qemu_flags)

kernel: $(sources)
	cd $(source_dir) && $(nasm) $(asm_sources) $(nasm_flags) -o kernel.bin && cd ..
	mv $(source_dir)/kernel.bin $(build_dir)/

clean:
	rm $(build_dir)/kernel.bin

debug:
	@ if ! od -t x1 -A n $(build_dir)/kernel.bin; then \
		echo 'Run "make kernel" to build a binary first!'; \
	fi
