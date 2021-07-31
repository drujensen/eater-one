all: deploy

deploy: build
	minipro -p AT28C256 -w eatermon.bin

build: compile
	ld65 -C build.cfg -o eatermon.bin eatermon.o tinybasic.o

compile:	clean
	ca65 eatermon.s
	ca65 --feature labels_without_colons tinybasic.s

clean:
	$(RM) *.o *.bin
