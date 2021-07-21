rm -f a.out eatermon.o rom.bin
ca65 eatermon.s
ld65 -C build.cfg eatermon.o
minipro -p AT28C256 -w rom.bin
