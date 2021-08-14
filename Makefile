all: deploy

deploy: build
	minipro -p AT28C256 -w bin/eatermon.bin

build: compile
	ld65 -C build.cfg -o bin/eatermon.bin obj/wozmon.o obj/tinybasic.o obj/msbasic.o

compile:	clean
	ca65 -o obj/wozmon.o src/wozmon.s
	ca65 --feature labels_without_colons -o obj/tinybasic.o src/tinybasic.s
	ca65 -D osi src/msbasic/msbasic.s -o obj/msbasic.o

clean:
	$(RM) obj/* bin/*
