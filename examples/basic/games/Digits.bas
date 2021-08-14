10 PRINT TAB(33);"DIGITS"
20 PRINT TAB(15);"CREATIVE COMPUTING  MORRISTOWN, NEW JERSEY"
30 PRINT:PRINT:PRINT
210 PRINT "THIS IS A GAME OF GUESSING."
215 PRINT
220 PRINT "FOR INSTRUCTIONS, TYPE '1', ELSE TYPE '0'";
230 INPUT E
240 IF E=0 THEN 360
250 PRINT
260 PRINT "PLEASE TAKE A PIECE OF PAPER AND WRITE DOWN"
270 PRINT "THE DIGITS '0', '1', OR '2' THIRTY TIMES AT RANDOM."
280 PRINT "ARRANGE THEM IN THREE LINES OF TEN DIGITS EACH."
290 PRINT "I WILL ASK FOR THEM TEN AT A TIME."
300 PRINT "I WILL ALWAYS GUESS THEM FIRST AND THEN LOOK AT YOUR"
310 PRINT "NEXT NUMBER TO SEE IF I WAS RIGHT. BY PURE LUCK,"
320 PRINT "I OUGHT TO BE RIGHT TEN TIMES. BUT I HOPE TO DO BETTER"
330 PRINT "THAN THAT *****"
340 PRINT:PRINT
360 READ A,B,C
370 DATA 0,1,3
380 DIM M(26,2),K(2,2),L(8,2)
400 FOR I=0 TO 26: FOR J=0 TO 2: M(I,J)=1: NEXT J: NEXT I
410 FOR I=0 TO 2: FOR J=0 TO 2: K(I,J)=9: NEXT J: NEXT I
420 FOR I=0 TO 8: FOR J=0 TO 2: L(I,J)=3: NEXT J: NEXT I
450 L(0,0)=2: L(4,1)=2: L(8,2)=2
480 Z=26: Z1=8: Z2=2
510 X=0
520 FOR T=1 TO 3
530 PRINT
540 PRINT "TEN NUMBERS, PLEASE";
550 INPUT N(1),N(2),N(3),N(4),N(5),N(6),N(7),N(8),N(9),N(10)
560 FOR I=1 TO 10
570 W=N(I)-1
580 IF W=SGN(W) THEN 620
590 PRINT "ONLY USE THE DIGITS '0', '1', OR '2'."
600 PRINT "LET'S TRY AGAIN.":GOTO 530
620 NEXT I
630 PRINT: PRINT "MY GUESS","YOUR NO.","RESULT","NO. RIGHT":PRINT
660 FOR U=1 TO 10
670 N=N(U): S=0
690 FOR J=0 TO 2
700 S1=A*K(Z2,J)+B*L(Z1,J)+C*M(Z,J)
710 IF S>S1 THEN 760
720 IF S<S1 THEN 740
730 IF RND(1)<.5 THEN 760
740 S=S1: G=J
760 NEXT J
770 PRINT "  ";G,"   ";N(U),
780 IF G=N(U) THEN 810
790 PRINT " WRONG",X
800 GOTO 880
810 X=X+1
820 PRINT " RIGHT",X
830 M(Z,N)=M(Z,N)+1
840 L(Z1,N)=L(Z1,N)+1
850 K(Z2,N)=K(Z2,N)+1
860 Z=Z-INT(Z/9)*9
870 Z=3*Z+N(U)
880 Z1=Z-INT(Z/9)*9
890 Z2=N(U)
900 NEXT U
910 NEXT T
920 PRINT
930 IF X>10 THEN 980
940 IF X<10 THEN 1010
950 PRINT "I GUESSED EXACTLY 1/3 OF YOUR NUMBERS."
960 PRINT "IT'S A TIE GAME."
970 GOTO 1030
980 PRINT "I GUESSED MORE THAN 1/3 OF YOUR NUMBERS."
990 PRINT "I WIN.": FOR Q=1 TO 10: PRINT CHR$(7);: NEXT Q
1000 GOTO 1030
1010 PRINT "I GUESSED LESS THAN 1/3 OF YOUR NUMBERS."
1020 PRINT "YOU BEAT ME.  CONGRATULATIONS *****"
1030 PRINT
1040 INPUT "DO YOU WANT TO TRY AGAIN (1 FOR YES, 0 FOR NO)";
1060 INPUT X
1070 IF X=1 THEN 400
1080 PRINT:PRINT "THANKS FOR THE GAME."
1090 END
