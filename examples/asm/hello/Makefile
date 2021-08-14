all: deploy

deploy: bin2mon
	../../upload.py hello.mon

bin2mon: build
	bintomon -l 0x0000 -r 0x0200 -b 4 -c 0x00 hello.bin > hello.mon

build: compile
	ld65 -C ../../build.cfg -o hello.bin hello.o

compile:	clean
	ca65 hello.s

clean:
	$(RM) *.o *.bin
