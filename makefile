build_dir = ./build
source_dir = ./src
bootsector_dir = $(source_dir)/boot
kernel_dir = $(source_dir)/kernel
driver_dir = $(source_dir)/driver
header_dir = $(source_dir)/headers

nasm = nasm
nasm_flags = -f bin
cc = gcc
ccflags = -m32 -ffreestanding -fno-pie -nostdlib
ld = ld
ldflags = -m elf_i386 -Ttext 0x1000 --oformat binary

bootsector_src = boot.asm
kernel_src = $(kernel_dir)/*.c

C_SOURCES = $(wildcard $(kernel_dir)/*.c $(driver_dir)/*.c)
C_HEADERS = $(wildcard $(header_dir)/*/*.h)
C_OBJ = $(patsubst %.c, %.o, $(C_SOURCES))

qemu = qemu-system-i386 
drive = hd1
qemu_flags = -m 512
qemu_drive = -drive file=fat:rw:$(drive)

# ---- MAKE RULES ----

all: $(build_dir) os run

run:
	$(qemu) $(build_dir)/os-image

$(build_dir):
	mkdir -p $(build_dir)

os: kernel bootsector 
	cat $(build_dir)/bootsector.bin $(build_dir)/kernel.bin > $(build_dir)/os-image

bootsector:
	cd $(bootsector_dir) && $(nasm) $(bootsector_src) $(nasm_flags) -o $@.bin && cd ../..
	mv $(bootsector_dir)/$@.bin $(build_dir)/

kernel: boot2kernel.o ${C_OBJ}
	$(ld) $(ldflags) -o $@.bin $^ 
	rm $^
	mv $@.bin $(build_dir)/

%.o: %.c $(C_HEADERS) # generic C compilation rule
	$(cc) $(ccflags) -c $< -o $@

boot2kernel.o: $(kernel_dir)/boot2kernel.asm
	$(nasm) $(kernel_dir)/boot2kernel.asm -f elf -o boot2kernel.o

clean:
	rm -rf $(build_dir)/* ;
	rm -rf ./*.o;
	rm -rf $(source_dir)/*/*.o

debug:
	@ if ! od -t x1 -A n $(build_dir)/kernel.bin; then \
		echo 'Run "make kernel" to build a binary first!'; \
	fi
