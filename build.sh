#nasm -f elf32 kernel.asm -o kasm.o
gcc -m32 -c kernel.c -o kc.o -ffreestanding
gcc -m32 -c system.c -o system.o -ffreestanding
gcc -m32 -c keyboard.c -o keyboard.o
ld -m elf_i386 -T link.ld -o Kess/boot/kernel.bin *.o
# qemu -kernel Kess/boot/kernel.bin
grub-mkrescue -o KessOS.iso Kess/


