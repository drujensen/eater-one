all: deploy

deploy: build
	minipro -p AT28C256 -w bin/eatermon.bin

build: compile
	ld65 -C build.cfg -m eatermon.map -o bin/eatermon.bin obj/wozmon.o obj/jmon.o obj/msbasic.o

compile:	clean
	ca65 -l wozmon.lst -o obj/wozmon.o src/wozmon.s
	ca65 -D osi -l basic.lst -o obj/msbasic.o src/msbasic/msbasic.s
#	ca65 --feature labels_without_colons -o obj/tinybasic.o src/tinybasic.s
	ca65 -D SBC -l jmon.lst -o obj/jmon.o src/jmon/jmon.s

clean:
	$(RM) obj/* bin/* *.map *.lst
