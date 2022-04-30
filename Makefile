all: deploy

deploy: build
	minipro -p AT28C256 -w bin/eatermon.bin

build: compile
	ld65 -C build.cfg -m eatermon.map -o bin/eatermon.bin obj/wozmon.o obj/jmon.o obj/msbasic.o

compile:	clean jmon
	ca65 -o obj/wozmon.o src/wozmon.s
#	ca65 --feature labels_without_colons -o obj/tinybasic.o src/tinybasic.s
	ca65 -D osi src/msbasic/msbasic.s -o obj/msbasic.o

jmon:	src/jmon/jmon.s src/jmon/disasm.s src/jmon/miniasm.s src/jmon/trace.s src/jmon/info.s src/jmon/memtest4.s
	ca65 -D SBC -g -l jmon.lst src/jmon/jmon.s -o obj/jmon.o

clean:
	$(RM) obj/* bin/* *.map *.lst
