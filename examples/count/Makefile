all: deploy

deploy: build
	hexdump -C count.bin

build: compile
	ld65 -C build.cfg -o count.bin count.o

compile:	clean
	ca65 count.s

clean:
	$(RM) *.o *.bin
