# ---- MAKE DIR AND OBJECTS ----

build_dir = $(PWD)/build
source_dir = $(PWD)/src
bootsector_dir = $(source_dir)/boot
kernel_dir = $(source_dir)/kernel
driver_dir = $(source_dir)/driver
header_dir = $(source_dir)/headers

nasm = nasm
nasm_flags = -f bin
cc = gcc
ccflags = -m32 -ffreestanding -fno-pie -nostdlib -fno-stack-protector -fno-builtin -nostdinc -Wall -I.
ld = ld
ldflags = -m elf_i386

bootsector_src = boot.asm
kernel_src = $(kernel_dir)/*.c

C_SOURCES = $(wildcard $(kernel_dir)/*.c $(kernel_dir)/*/*.c $(driver_dir)/*.c $(driver_dir)/*/*.c)
ASM_SOURCES = $(wildcard $(kernel_dir)/*/*.asm $(driver_dir)/*/*.asm)
C_HEADERS = $(wildcard $(header_dir)/*/*.h)
C_OBJ = $(patsubst %.c, %.o, $(C_SOURCES))
ASM_OBJ = $(patsubst %.asm, %.o, $(ASM_SOURCES))
LD_SOURCE = $(source_dir)/linker.ld

qemu = qemu-system-x86_64
debug = -s -S # gdb
boot_drive = -hda $(build_dir)/grubless.img -boot a
drive = hd1
qemu_flags = -m 512
qemu_drive = -drive file=fat:rw:$(drive)

FAT12 = mkfs.fat -F 12
BLOCK_SIZE = 512
SECTORS = 2880
IMAGE_LABEL = "GRUBLESS"

# ---- MAKE RULES ----

all: $(build_dir) os drive

run:
	$(qemu) $(boot_drive)

run_debug:
	$(qemu) $(boot_drive) $(debug)

$(build_dir):
	mkdir -p $(build_dir)

os: kernel bootsector 
	cat $(build_dir)/bootsector.bin $(build_dir)/kernel.bin > $(build_dir)/os-image

drive:
	dd if=/dev/zero of=$(build_dir)/grubless.img bs=$(BLOCK_SIZE) count=$(SECTORS)
	$(FAT12) -n $(IMAGE_LABEL) $(build_dir)/grubless.img
	dd if=$(build_dir)/bootsector.bin of=$(build_dir)/grubless.img conv=notrunc
# this copies the bootloader into the main FAT12 disk.
	mcopy -i $(build_dir)/grubless.img $(build_dir)/kernel.bin "::kernel.bin"

bootsector:
	cd $(bootsector_dir) && $(nasm) $(bootsector_src) $(nasm_flags) -o $@.bin && cd ../..
	mv $(bootsector_dir)/$@.bin $(build_dir)/

# it is important that boot2kernel is linked first.
kernel: boot2kernel.o $(C_OBJ) $(ASM_OBJ)
	cd $(build_dir)\
	&& $(ld) $(ldflags) -T $(LD_SOURCE) -o $@.bin boot2kernel.o *.o \
	&& rm *.o \
	&& cd $(pwd)

%.o: %.c $(C_HEADERS) # generic C compilation rule
	$(cc) $(ccflags) -c $< -o $@
	mv $@ $(build_dir)

%.o: %.asm $(C_HEADERS) #generic ASM compilation rule
	$(nasm) $< -f elf32 -o $@
	mv $@ $(build_dir)

boot2kernel.o: $(kernel_dir)/boot2kernel.asm
	$(nasm) $(kernel_dir)/boot2kernel.asm -f elf -o boot2kernel.o
	mv $@ $(build_dir)

clean:
	rm -rf $(build_dir)/* ;
	rm -rf ./*.o;
	rm -rf $(source_dir)/*/*.o