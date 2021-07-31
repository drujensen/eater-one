all: deploy

deploy: build
	hexdump -C hello.bin

build: compile
	ld65 -C build.cfg -o hello.bin hello.o

compile:	clean
	ca65 hello.s

clean:
	$(RM) *.o *.bin
