# Grubless

Grubless is an attempt at recreating a basic, 32-bit general purpose OS from scratch using nothing more than x86 assembly(nasm) and C.

## Pre-Requisites

- GCC
- Netwide assembler(nasm) `sudo apt-get install nasm`
- qemu(x86) `sudo apt-get install qemu-system-x86`
- Make
- mcopy `sudo apt install mtools`
- mkfs.fat `sudo apt install dosfstools`

## Installation

Clone the repository onto your local machine using git:

```bash
git clone https://github.com/Serpent03/grubless.git
```

To run the operating system, use `make all` to build the operating system image. If you do not want to build again, then use `make run` to run the already built binary.

## How does it work?

There are two "phases" of the operating system booting up: the initial boot, and then loading the kernel. Accordingly, the files for operations in both the bootup and kernel phases can be found inside `source/boot` and `source/kernel` respectively.

The reason that boot and kernel are different phases has to do with the fact that during bootup, an instruction size of only 16-bit is available to us.

All function addresses, BIOS routines, and operands are constrained to this size. This effectively means that we are constrained to about 2^16(or 65536), or more commonly: 64KB of RAM. 

That's not a lot - especially for writing an OS. To make up for this deficiency, we have to switch to a 32-bit instruction size, which allows us 2^32 various different memory locations: a whopping 4GB of RAM(doesn't seem like much nowadays does it?)

Unfortunately, this switch to 32-bit means that functions, routines, etc. of 16-bit instruction size are all inaccessible, so we have to write a lot of stuff from scratch - all of which goes inside the `src/kernel` folder.

For more details, check out the [wiki](https://github.com/Serpent03/Grubless/wiki)!

## Roadmap(in no certain order)

- [ ] APIC integration
- [ ] Working stdio library(printf, scanf, ..)
- [ ] File system and disk drivers(FAT12, FAT16, ..)
- [ ] Network stack(TCP/ICP, ..)
- [ ] Process scheduler
- [ ] Paging
