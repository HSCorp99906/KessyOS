all:
	./build.sh
	sudo dd bs=4M if=KessOS.iso of=/dev/sdb
	sudo qemu-system-x86_64 -hdb /dev/sdb
