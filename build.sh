cd bootloader
make Link
dd if=/dev/zero of=../drive.img bs=4K count=1
dd if=bloader.bin of=../drive.img conv=notrunc
cd ..
make Run