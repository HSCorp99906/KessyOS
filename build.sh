#nasm -f elf32 kernel.asm -o kasm.o
gcc -m32 -c kernel.c -o obj/kc.o -ffreestanding
gcc -m32 -c system.c -o obj/system.o -ffreestanding
gcc -m32 -c keyboard.c -o obj/keyboard.o -ffreestanding
gcc -m32 -c _kernel_utils/IDT.c -o obj/IDT.o -ffreestanding
gcc -m32 -c _kernel_utils/util.c -o obj/util.o -ffreestanding
gcc -m32 -c _kernel_utils/ISR.c -o obj/ISR.o -ffreestanding
ld -m elf_i386 -T link.ld -o Kess/boot/kernel.bin obj/*.o
# qemu -kernel Kess/boot/kernel.bin
grub-mkrescue -o KessOS.iso Kess/


