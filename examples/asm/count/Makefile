all: deploy

deploy: bin2mon
	../../upload.py count.mon

bin2mon: build
	bintomon -l 0x0000 -r 0x0000 -b 4 -c 0x00 count.bin > count.mon

build: compile
	ld65 -C ../../build.cfg -o count.bin count.o

compile:	clean
	ca65 count.s

clean:
	$(RM) *.o *.bin *.mon
