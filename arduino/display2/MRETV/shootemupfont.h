
#ifndef _shootemup_font_
#define _shootemup_font_

const unsigned char shootemupfont [(128+16)*8]  PROGMEM = {
0,
0,
0,
0,
0,
0,
0,
0,

0,
0,
0,
0,
0,
0,
0,
0,

0,
0,
1,
1,
0,
0,
0,
1,

0,
1,
3,
3,
1,
0,
1,
2,

1,
3,
6,
7,
3,
1,
2,
1,//4,

3,
7,
13,
15,
7,
2,
4,
2,//8,

7,
15,
26,
31,
15,
5,
8,
5,//16,

14,
31,
53,
63,
31,
10,
17,
10,//32,


28,
62,
107,
127,
62,
20,
34,
65,

56,
124,
214,
254,
124,
40,
68,
130,

112,
248,
172,
252,
248,
80,
136,
4,

224,
240,
88,
248,
240,
160,
16,
8,

192,
224,
176,
240,
224,
64,
32,
64,//16,

128,
192,
96,
224,
192,
128,
64,
128,//32,

0,
128,
192,
192,
128,
0,
128,
0,//64,

0,
0,
128,
128,
0,
0,
0,
0,//128,


 
  0b10000000,//16
  0b10000000,
  0b10000000,
  0b10000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,

  0b00000000,//17
  0b00000000,
  0b10000000,
  0b10000000,
  0b10000000,
  0b10000000,
  0b00000000,
  0b00000000,

  0b00000000,//18
  0b00000000,
  0b00000000,
  0b00000000,
  0b10000000,
  0b10000000,
  0b10000000,
  0b10000000,

  0b00000000,//19
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b10000000,
  0b10000000,

  0b10000000,//20
  0b10000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
 
  0b00000000,//21
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,//22
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,//23
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,//24
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,//25
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,//26
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,//27
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,//28
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,//29
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,//30
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,//31
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,//32 Space
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,//33 Exclamation !
  0b01100000,
  0b01100000,
  0b01100000,
  0b01100000,
  0b00000000,
  0b00000000,
  0b01100000,
  0b00000000,//34 Quotes "
  0b01010000,
  0b01010000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,//35 Number #
  0b00000000,
  0b01010000,
  0b11111000,
  0b01010000,
  0b11111000,
  0b01010000,
  0b00000000,
  0b00000000,//36 Dollars $
  0b01110000,
  0b10100000,
  0b10100000,
  0b01110000,
  0b00101000,
  0b00101000,
  0b01110000,
  0b00000000,//37 Percent %
  0b01000000,
  0b10101000,
  0b01010000,
  0b00100000,
  0b01010000,
  0b10101000,
  0b00010000,
  0b00000000,//38 Ampersand &
  0b00100000,
  0b01010000,
  0b10100000,
  0b01000000,
  0b10101000,
  0b10010000,
  0b01101000,
  0b00000000,//39 Single Quote '
  0b01000000,
  0b01000000,
  0b01000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,//40 Left Parenthesis (
  0b00010000,
  0b00100000,
  0b01000000,	
  0b01000000,
  0b01000000,
  0b00100000,
  0b00010000,
  0b00000000,//41 Right Parenthesis )
  0b01000000,
  0b00100000,
  0b00010000,
  0b00010000,
  0b00010000,
  0b00100000,
  0b01000000,
  0b00000000,//42 Star *
  0b00010000,
  0b00111000,
  0b00010000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,//43 Plus +
  0b00000000,
  0b00100000,
  0b00100000,
  0b11111000,
  0b00100000,
  0b00100000,
  0b00000000,
  0b00000000,//44 Comma ,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00010000,
  0b00010000,
  0b00000000,//45 Minus -
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b11111000,
  0b00000000,
  0b00000000,
  0b00000000,//46 Period .
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00010000,
  0b00000000,// 47 Backslash /
  0b00000000,
  0b00001000,
  0b00010000,
  0b00100000,
  0b01000000,
  0b10000000,
  0b00000000,
  0b00000000,// 48 Zero
  0b01110000,
  0b10001000,
  0b10011000,
  0b10101000,
  0b11001000,
  0b10001000,
  0b01110000,
  0b00000000,//49 One
  0b00100000,
  0b01100000,
  0b00100000,
  0b00100000,
  0b00100000,
  0b00100000,
  0b01110000,  
  0b00000000,//50 two
  0b01110000,
  0b10001000,
  0b00001000,
  0b00010000,
  0b00100000,
  0b01000000,
  0b11111000,
  0b00000000,//51 Three
  0b11111000,
  0b00010000,
  0b00100000,
  0b00010000,
  0b00001000,
  0b10001000,
  0b01110000,
  0b00000000,//52 Four
  0b00010000,
  0b00110000,
  0b01010000,
  0b10010000,
  0b11111000,
  0b00010000,
  0b00010000,
  0b00000000,//53 Five
  0b11111000,
  0b10000000,
  0b11110000,
  0b00001000,
  0b00001000,
  0b10001000,
  0b01110000,
  0b00000000,//54 Six
  0b01000000,
  0b10000000,
  0b10000000,
  0b11110000,
  0b10001000,
  0b10001000,
  0b01110000,
  0b00000000,//55 Seven
  0b11111000,
  0b00001000,
  0b00010000,
  0b00100000,
  0b01000000,
  0b10000000,
  0b10000000,
  0b00000000,//56 Eight
  0b01110000,
  0b10001000,
  0b10001000,
  0b01110000,
  0b10001000,
  0b10001000,
  0b01110000,
  0b00000000,//57 Nine
  0b01110000,
  0b10001000,
  0b10001000,
  0b01111000,
  0b00001000,
  0b00001000,
  0b00010000,
  0b00000000,//58 :
  0b00000000,
  0b00000000,
  0b00100000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00100000,
  0b00000000,//59 ;
  0b00000000,
  0b00000000,
  0b00100000,
  0b00000000,
  0b00000000,
  0b00100000,
  0b00100000,
  0b00000000,//60 <
  0b00000000,
  0b00011000,
  0b01100000,
  0b10000000,
  0b01100000,
  0b00011000,
  0b00000000,
  0b00000000,//61 =
  0b00000000,
  0b00000000,
  0b01111000,
  0b00000000,
  0b01111000,
  0b00000000,
  0b00000000,
  0b00000000,//62 >
  0b00000000,
  0b11000000,
  0b00110000,
  0b00001000,
  0b00110000,
  0b11000000,
  0b00000000,
  0b00000000,//63 ?
  0b00110000,
  0b01001000,
  0b00010000,
  0b00100000,
  0b00100000,
  0b00000000,
  0b00100000,
  0b00000000,//64 @
  0b01110000,
  0b10001000,
  0b10111000,
  0b10101000,
  0b10010000,
  0b10001000,
  0b01110000,
  0b00000000,//65 A
  0b01110000,
  0b10001000,
  0b10001000,
  0b10001000,
  0b11111000,
  0b10001000,
  0b10001000,
  0b00000000,//B
  0b11110000,
  0b10001000,
  0b10001000,
  0b11110000,
  0b10001000,
  0b10001000,
  0b11110000,
  0b00000000,//C
  0b01110000,
  0b10001000,
  0b10000000,
  0b10000000,
  0b10000000,
  0b10001000,
  0b01110000,
  0b00000000,//D
  0b11110000,
  0b10001000,
  0b10001000,
  0b10001000,
  0b10001000,
  0b10001000,
  0b11110000,
  0b00000000,//E
  0b11111000,
  0b10000000,
  0b10000000,
  0b11111000,
  0b10000000,
  0b10000000,
  0b11111000,
  0b00000000,//F
  0b11111000,
  0b10000000,
  0b10000000,
  0b11111000,
  0b10000000,
  0b10000000,
  0b10000000,
  0b00000000,//G
  0b01110000,
  0b10001000,
  0b10000000,
  0b10011000,
  0b10001000,
  0b10001000,
  0b01110000,
  0b00000000,//H
  0b10001000,
  0b10001000,
  0b10001000,
  0b11111000,
  0b10001000,
  0b10001000,
  0b10001000,
  0b00000000,//I
  0b01110000,
  0b00100000,
  0b00100000,
  0b00100000,
  0b00100000,
  0b00100000,
  0b01110000,
  0b00000000,//J
  0b00111000,
  0b00010000,
  0b00010000,
  0b00010000,
  0b00010000,
  0b10010000,
  0b01100000,
  0b00000000,//K
  0b10001000,
  0b10010000,
  0b10100000,
  0b11000000,
  0b10100000,
  0b10010000,
  0b10001000,
  0b00000000,//L
  0b10000000,
  0b10000000,
  0b10000000,
  0b10000000,
  0b10000000,
  0b10000000,
  0b11111000,
  0b00000000,//M
  0b10001000,
  0b11011000,
  0b10101000,
  0b10101000,
  0b10001000,
  0b10001000,
  0b10001000,
  0b00000000,//N
  0b10001000,
  0b10001000,
  0b11001000,
  0b10101000,
  0b10011000,
  0b10001000,
  0b10001000,
  0b00000000,//O
  0b01110000,
  0b10001000,
  0b10001000,
  0b10001000,
  0b10001000,
  0b10001000,
  0b01110000,
  0b00000000,//P
  0b11110000,
  0b10001000,
  0b10001000,
  0b11110000,
  0b10000000,
  0b10000000,
  0b10000000,
  0b00000000,//Q
  0b01110000,
  0b10001000,
  0b10001000,
  0b10001000,
  0b10101000,
  0b10010000,
  0b01101000,
  0b00000000,//R
  0b11110000,
  0b10001000,
  0b10001000,
  0b11110000,
  0b10100000,
  0b10010000,
  0b10001000,
  0b00000000,//S
  0b01111000,
  0b10000000,
  0b10000000,
  0b01110000,
  0b00001000,
  0b00001000,
  0b11110000,
  0b00000000,//T
  0b11111000,
  0b00100000,
  0b00100000,
  0b00100000,
  0b00100000,
  0b00100000,
  0b00100000,
  0b00000000,//U
  0b10001000,
  0b10001000,
  0b10001000,
  0b10001000,
  0b10001000,
  0b10001000,
  0b01110000,
  0b00000000,//V
  0b10001000,
  0b10001000,
  0b10001000,
  0b10001000,
  0b10001000,
  0b01010000,
  0b00100000,
  0b00000000,//W
  0b10001000,
  0b10001000,
  0b10001000,
  0b10101000,
  0b10101000,
  0b10101000,
  0b01010000,
  0b00000000,//X
  0b10001000,
  0b10001000,
  0b01010000,
  0b00100000,
  0b01010000,
  0b10001000,
  0b10001000,
  0b00000000,//Y
  0b10001000,
  0b10001000,
  0b10001000,
  0b01010000,
  0b00100000,
  0b00100000,
  0b00100000,
  0b00000000,//Z
  0b11111000,
  0b00001000,
  0b00010000,
  0b00100000,
  0b01000000,
  0b10000000,
  0b11111000,
  0b00000000,//91 [
  0b11100000,
  0b10000000,
  0b10000000,
  0b10000000,
  0b10000000,
  0b10000000,
  0b11100000,
  0b00000000,//92 (backslash)
  0b00000000,
  0b10000000,
  0b01000000,
  0b00100000,
  0b00010000,
  0b00001000,
  0b00000000,
  0b00000000,//93 ]
  0b00111000,
  0b00001000,
  0b00001000,
  0b00001000,
  0b00001000,
  0b00001000,
  0b00111000,
  0b00000000,//94 ^
  0b00100000,
  0b01010000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,//95 _
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b11111000,
  0b00000000,//96 `
  0b10000000,
  0b01000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,//97 a
  0b00000000,
  0b01100000,
  0b00010000,
  0b01110000,
  0b10010000,
  0b01100000,
  0b00000000,
  0b00000000,//98 b
  0b10000000,
  0b10000000,
  0b11100000,
  0b10010000,
  0b10010000,
  0b11100000,
  0b00000000,
  0b00000000,//99 c
  0b00000000,
  0b00000000,
  0b01110000,
  0b10000000,
  0b10000000,
  0b01110000,
  0b00000000,
  0b00000000,// 100 d
  0b00010000,
  0b00010000,
  0b01110000,
  0b10010000,
  0b10010000,
  0b01110000,
  0b00000000,
  0b00000000,//101 e
  0b00000000,
  0b01100000,
  0b10010000,
  0b11110000,
  0b10000000,
  0b01110000,
  0b00000000,
  0b00000000,//102 f
  0b00110000,
  0b01000000,
  0b11100000,
  0b01000000,
  0b01000000,
  0b01000000,
  0b00000000,
  0b00000000,//103 g
  0b00000000,
  0b01100000,
  0b10010000,
  0b01110000,
  0b00010000,
  0b00010000,
  0b01100000,
  0b00000000,//104 h
  0b10000000,
  0b10000000,
  0b11100000,
  0b10010000,
  0b10010000,
  0b10010000,
  0b00000000,
  0b00000000,//105 i
  0b00000000,
  0b00100000,
  0b00000000,
  0b00100000,
  0b00100000,
  0b00100000,
  0b00000000,
  0b00000000,//106 j
  0b00000000,
  0b00010000,
  0b00000000,
  0b00010000,
  0b00010000,
  0b00010000,
  0b01100000,
  0b00000000,//107 k
  0b10000000,
  0b10010000,
  0b10100000,
  0b11000000,
  0b10100000,
  0b10010000,
  0b00000000,
  0b00000000,//108 l
  0b00100000,
  0b00100000,
  0b00100000,
  0b00100000,
  0b00100000,
  0b00100000,
  0b00000000,
  0b00000000,//109 m
  0b00000000,
  0b00000000,
  0b01010000,
  0b10101000,
  0b10101000,
  0b10101000,
  0b00000000,
  0b00000000,//110 n
  0b00000000,
  0b00000000,
  0b01100000,
  0b10010000,
  0b10010000,
  0b10010000,
  0b00000000,
  0b00000000,//111 o
  0b00000000,
  0b00000000,
  0b01100000,
  0b10010000,
  0b10010000,
  0b01100000,
  0b00000000,
  0b00000000,//112 p
  0b00000000,
  0b00000000,
  0b01100000,
  0b10010000,
  0b11110000,
  0b10000000,
  0b10000000,
  0b00000000,//113 q
  0b00000000,
  0b00000000,
  0b01100000,
  0b10010000,
  0b11110000,
  0b00010000,
  0b00010000,
  0b00000000,//114 r
  0b00000000,
  0b00000000,
  0b10111000,
  0b01000000,
  0b01000000,
  0b01000000,
  0b00000000,
  0b00000000,//115 s
  0b00000000,
  0b00000000,
  0b01110000,
  0b01000000,
  0b00010000,
  0b01110000,
  0b00000000,
  0b00000000,//116 t
  0b01000000,
  0b01000000,
  0b11100000,
  0b01000000,
  0b01000000,
  0b01000000,
  0b00000000,
  0b00000000,// 117u
  0b00000000,
  0b00000000,
  0b10010000,
  0b10010000,
  0b10010000,
  0b01100000,
  0b00000000,
  0b00000000,//118 v
  0b00000000,
  0b00000000,
  0b10001000,
  0b10001000,
  0b01010000,
  0b00100000,
  0b00000000,
  0b00000000,//119 w
  0b00000000,
  0b00000000,
  0b10101000,
  0b10101000,
  0b01010000,
  0b01010000,
  0b00000000,
  0b00000000,//120 x
  0b00000000,
  0b00000000,
  0b10010000,
  0b01100000,
  0b01100000,
  0b10010000,
  0b00000000,
  0b00000000,//121 y
  0b00000000,
  0b00000000,
  0b10010000,
  0b10010000,
  0b01100000,
  0b01000000,
  0b10000000,
  0b00000000,//122 z
  0b00000000,
  0b00000000,
  0b11110000,
  0b00100000,
  0b01000000,
  0b11110000,
  0b00000000,
  0b00000000,//123 {
  0b00100000,
  0b01000000,
  0b01000000,
  0b10000000,
  0b01000000,
  0b01000000,
  0b00100000,
  0b00000000,//124 |
  0b00100000,
  0b00100000,
  0b00100000,
  0b00100000,
  0b00100000,
  0b00100000,
  0b00100000,
  0b00000000,//125 }
  0b00100000,
  0b00010000,
  0b00010000,
  0b00001000,
  0b00010000,	
  0b00010000,
  0b00100000,
  0b00000000,//126 ~
  0b00000000,
  0b00000000,
  0b01000000,
  0b10101000,
  0b00010000,
  0b00000000,
  0b00000000,
  0b00000000,//127 DEL
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
 0, //128gun
0,
0,
0,
0,
0,
0,
0,

0,
0,
0,
0,
0,
1,
1,
1,

0,
0,
0,
0,
1,
3,
3,
2,

0,
0,
0,
0,
3,
7,
6,
4,

0,
1,
1,
1,
7,
15,
12,
8,

0,
3,
3,
3,
15,
31,
24,
16,

0,
6,
6,
6,
31,
63,
48,
32,

0,
12,
12,
12,
63,
127,
97,
64,


0,
24,
24,
24,
126,
255,
195,
129,

0,
48,
48,
48,
252,
254,
134,
2,

0,
96,
96,
96,
248,
252,
12,
4,

0,
192,
192,
192,
240,
248,
24,
8,

0,
128,
128,
128,
224,
240,
48,
16,

0,
0,
0,
0,
192,
224,
96,
32,

0,
0,
0,
0,
128,
192,
192,
64,

0,
0,
0,
0,
0,
128,
128,
128

};
#endif
