all: deploy

deploy: build
	minipro -p AT28C256 -w rom.bin

build: compile
	ld65 -C build.cfg -o eatermon.bin eatermon.o

compile:	clean
	ca65 eatermon.s

clean:
	$(RM) *.o *.bin
