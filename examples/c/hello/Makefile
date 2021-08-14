all: deploy

deploy: bin2mon
	../../upload.py hello.mon

bin2mon: build
	bintomon -l 0x0000 -r 0x1000 -b 4 -c 0x00 hello.bin > hello.mon

build: compile
	ld65 -C ../../build.cfg -o hello.bin hello.o lib.o none.lib

compile:	clean
	cc65 -O -t none hello.c
	ca65 -t none lib.s
	ca65 -t none hello.s

clean:
	$(RM) *.o *.bin
