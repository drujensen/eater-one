// MasteRasterExtendedTransmissionVision 2  2015 11 16 Creative Commons ShareAlike License 3.0
// objects and internal interupt interupt
// beleive the code not the comments whmp

#include <avr/pgmspace.h>
#include "MrETV.h"


#ifdef userextension
 extern void userextension;
#endif
 MasteRasterExtendedTransmissionVision_Stereo_Gop_PS2_2400n81 Video;

RasterPort Screen;
#ifdef haveaudio
volatile uchar alcount=0;
#ifdef havestereo
volatile uchar arcount=0;
#endif
#endif

extern void RasterInt() asm ("RasterInt"); // make these match when munged up ?
void RasterInt(){// user interupt called at screen top -1, screen bottom, and screen bottom +1
// keep it short we have way less than 1000 cycles maybe less than 500...er maybe more than 500 but ...

 if ( Video.LineCount== Video.ScreenBottom){ //as soon as dispolay stop run some services
  #ifdef haveaudio
  // do some audio stuff
    if(alcount){
      if(alcount!=255)alcount--;
    }
    else  Video.audiodata=silent;
#ifdef havestereo
 if(arcount){
      if(arcount!=255)arcount--;
    }
    else  Video.audiodatar=silent;
#endif
#endif
 #ifdef haveps2  //do some keyboard stuff
  uchar a;
#ifdef havesp  // merge to serial stream.
#ifdef mergstreams  // merge to serial stream.
Video.key2S(); 
#endif
#endif
#ifdef  __AVR_ATmega2560__
#define mhelp _BV(4)
#else
#define mhelp _BV(1)
#endif

    if(Video.fpcount>10){ // decode byte into keyboard raw stream
	if(Video.keycount<4){ //is there room ?
	      Video.writeK(Video.getraw(Video.fpout));
      Video.fpout=(Video.fpout+1)&7;
      Video.fpcount-=11;
	  }
    }
      else{
      if(Video.fpcount){ // partial byte in bit buffer
         if(!(PCIFR)){ // clocks been quiet for a frame. Time to 'help' the hardware.
		 Video.fpcount=8; // don't ever wait forever ...
             while( !(SPSR&_BV(SPIF)) && Video.fpcount ){ // toggle clock till we get a full byte 
            DDRB|=mhelp; // out to low
           DDRB&=~mhelp; // let float high
             // DDRB=0; // 
                   Video.fpcount--; // a little delay, and some saftey
      }
  
          Video.fpbuf[Video.fpin]=SPDR; // get and place the bits 
          a=Video.getraw(Video.fpout); // get the decoded byte
          Video.fpbuf[9]=a<<6; // put into  byte 7
          Video.fpbuf[10]=a>>2; // for proper roll over
          Video.fpcount=11; // setup port handler 
          Video.fpin=0;    // to roll over after
          Video.fpout=7; // last data  in byte 7
        }
       #ifdef  __AVR_ATmega2560__

else PCIFR=_BV(PCIF0); // clear the 'clocks been busy' bit
#else
else PCIFR=_BV(PCIF0); // clear the 'clocks been busy' bit 
#endif
 		      } 
    }
  if(Video.keysendcount)Video.writekey(Video.keysend);
 #endif
 } 
  
else{ // let the user do something the other two slots screen top-1 and screenbottom+1
#ifdef userextension
 userextension;
#endif
//room to grow
}
}

unsigned char strtemp[12]; 
const unsigned char keycode[]  PROGMEM ={
       0x00     , // 00
              0x00     , // 01  F9
              0x00     , // 02
              0x00     , // 03  F5
              0x00     , // 04  F3
              0x00     , // 05  F1
              0x00     , // 06  F2
              0x00     , // 07  F12
              0x00     , // 08
              0x00     , // 09  F10
              0x00     , // 0A  F8
              0x00     , // 0B  F6
              0x00     , // 0C  F4
              0x09     , // 0D  TAB
              '`'     , // 0E  ` or ~
              0x00     , // 0F

              0x00     , // 10
              0x00     , // 11  Left ALT
              0x00     , // 12  Left SHIFT
              0x00     , // 13
              0x00     , // 14  Left Ctrl
              'q'     , // 15  Q
              '1'     , // 16  1 or !
              0x00     , // 17
              0x00     , // 18
              0x00     , // 19
              'z'     , // 1A  Z
              's'     , // 1B  S
              'a'     , // 1C  A
              'w'     , // 1D  W
              '2'     , // 1E  2 or @
              0x00     , // 1F

              0x00     , // 20
              'c'     , // 21  C
              'x'     , // 22  X
              'd'     , // 23  D
              'e'     , // 24  E
              '4'     , // 25  4 or 0x
              '3'     , // 26  3 or #
              0x00     , // 27
              0x00     , // 28
              ' '     , // 29  Space
              'v'     , // 2A  V
              'f'     , // 2B  F
              't'     , // 2C  T
              'r'     , // 2D  R
              '5'     , // 2E  5 or %
              0x00     , // 2F

              0x00     , // 30
              'n'     , // 31  N
              'b'     , // 32  B
              'h'     , // 33  H
              'g'     , // 34  G
              'y'     , // 35  Y
              '6'     , // 36  6 or ^
              0x00     , // 37
              0x00     , // 38
              0x00     , // 39
              'm'     , // 3A  M
              'j'     , // 3B  J
              'u'     , // 3C  U
              '7'     , // 3D  7 or &
              '8'     , // 3E  8 or *
              0x00     , // 3F

              0x00     , // 40
              ','     , // 41  , or <
              'k'     , // 42  K
              'i'     , // 43  I
              'o'     , // 44  O
              '0'     , // 45  0 or )
              '9'     , // 46  9 or (
              0x00     , // 47
              0x00     , // 48
              '.'     , // 49  . or >
              '/'     , // 4A  / or ?
              'l'     , // 4B  L
              ';'     , // 4C  ; or :
              'p'     , // 4D  P
              '-'     , // 4E  - or _
              0x00     , // 4F

              0x00     , // 50
              0x00     , // 51
              0x27     , // 52  '' or ""
              0x00     , // 53
              '['     , // 54  [ or {
              '='     , // 55  = OR +
              0x00     , // 56
              0x00     , // 57
              0x00     , // 58  Caps Lock
              0x00     , // 59  Right Shift
              0x0D     , // 5A  Enter
              ']'     , // 5B  ] or }
              0x00     , // 5C
              '\\'     , // 5D  \ or |
              0x0a     , // 5E // to make a cr lf 
              0x5b     , // 5F

              0x00     , // 60
              0x00     , // 61
              0x00     , // 62
              0x00     , // 63
              0x00     , // 64
              0x00     , // 65
              0x08     , // 66  Backspace
              0x00     , // 67
              0x00     , // 68
              '1'     , // 69  NUM - 1 or END
              0x00     , // 6A
              0x44     , // 6B  NUM - 4 or LEFT
              '7'     , // 6C  NUM - 7 or HOME
              0x00     , // 6D
              0x00     , // 6E
              0x00     , // 6F

              '0'     , // 70  NUM - 0 or INS
              '.'     , // 71  NUM - . or DEL
             0x42     , // 72  NUM - 2 or DOWN
              '5'     , // 73  NUM - 5
              0x43     , // 74  NUM - 6 or RIGHT
              0x41     , // 75  NUM - 8 or UP
              0x1B     , // 76  ESC
              0x00     , // 77  NUM LOCK
              0x00     , // 78  F11
              '+'     , // 79  NUM - + (Plus)
              '3'     , // 7A  NUM 3 or PAGE DOWN
              '-'     , // 7B  NUM - - (Minus)
              '*'     , // 7C  NUM - *
              '9'     , // 7D  NUM - 9 or PAGE UP
              0x7e     , // 7E  SCROLL LOCK
              0x00     , // 7F

              0x00     , // 80
              0x00     , // 81
              0x00     , // 82
              0x00     , // 83  F7
              0x00     , // 84
              0x00     , // 85
              0x00     , // 86
              0x00     , // 87
              0x00     , // 88
              0x00     , // 89
              0x00     , // 8A
              0x00     , // 8B
              0x00     , // 8C
              0x00     , // 8D
              0x00     , // 8E
              0x00      // 8F
			  };

const unsigned char sftcode[]  PROGMEM ={
        0x00     , // 00
              0x00     , // 01  F9
              0x00     , // 02
              0x00     , // 03  F5
              0x00     , // 04  F3
              0x00     , // 05  F1
              0x00     , // 06  F2
              0x00     , // 07  F12
              0x00     , // 08
              0x00     , // 09  F10
              0x00     , // 0A  F8
              0x00     , // 0B  F6
              0x00     , // 0C  F4
              0x09     , // 0D  TAB
              '~'     , // 0E  ` or ~
              0x00     , // 0F

              0x00     , // 10
              0x00     , // 11  Left ALT
              0x00     , // 12  Left SHIFT
              0x00     , // 13
              0x00     , // 14  Left Ctrl
              'Q'     , // 15  Q
              '!'     , // 16  1 or !
              0x00     , // 17
              0x00     , // 18
              0x00     , // 19
              'Z'     , // 1A  Z
              'S'     , // 1B  S
              'A'     , // 1C  A
              'W'     , // 1D  W
              '@'     , // 1E  2 or @
              0x00     , // 1F

              0x00     , // 20
              'C'     , // 21  C
              'X'     , // 22  X
              'D'     , // 23  D
              'E'     , // 24  E
              '$'     , // 25  4 or $
              '#'     , // 26  3 or #
              0x00     , // 27
              0x00     , // 28
              ' '     , // 29  Space
              'V'     , // 2A  V
              'F'     , // 2B  F
              'T'     , // 2C  T
              'R'     , // 2D  R
              '%'     , // 2E  5 or %
              0x00     , // 2F

              0x00     , // 30
              'N'     , // 31  N
              'B'     , // 32  B
              'H'     , // 33  H
              'G'     , // 34  G
              'Y'     , // 35  Y
              '^'     , // 36  6 or ^
              0x00     , // 37
              0x00     , // 38
              0x00     , // 39
              'M'     , // 3A  M
              'J'     , // 3B  J
              'U'     , // 3C  U
              '&'     , // 3D  7 or &
              '*'     , // 3E  8 or *
              0x00     , // 3F

              0x00     , // 40
              '<'     , // 41  , or <
              'K'     , // 42  K
              'I'     , // 43  I
              'O'     , // 44  O
              ')'     , // 45  0 or )
              '('     , // 46  9 or (
              0x00     , // 47
              0x00     , // 48
              '>'     , // 49  > or .
              '?'     , // 4A  / or ?
              'L'     , // 4B  L
              ':'     , // 4C  , // or :
              'P'     , // 4D  P
              '_'     , // 4E  - or _
              0x00     , // 4F

              0x00     , // 50
              0x00     , // 51
              0x22     , // 52  '' or ""
              0x00     , // 53
              '{'     , // 54  [ or {
              '+'     , // 55  = OR +
              0x00     , // 56
              0x00     , // 57
              0x00     , // 58  Caps Lock
              0x01     , // 59  Right Shift
              0x0D     , // 5A  Enter
              '}'     , // 5B  ] or }
              0x00     , // 5C
              '|'     , // 5D  \ or |
              0x00     , // 5E
              0x5b     , // 5F // for escape 1b 5b sequence....

              0x00     , // 60
              0x00     , // 61
              0x00     , // 62
              0x00     , // 63
              0x00     , // 64
              0x00     , // 65
              0x08     , // 66  Backspace
              0x00     , // 67
              0x00     , // 68
              '1'     , // 69  NUM - 1 or END
              0x00     , // 6A
              '4'     , // 6B  NUM - 4 or LEFT
              '7'     , // 6C  NUM - 7 or HOME
              0x00     , // 6D
              0x00     , // 6E
              0x00     , // 6F

              '0'     , // 70  NUM - 0 or INS
              '.'     , // 71  NUM - . or DEL
              '2'     , // 72  NUM - 2 or DOWN
              '5'     , // 73  NUM - 5
              '6'     , // 74  NUM - 6 or RIGHT
              '8'     , // 75  NUM - 8 or UP
              0x1B     , // 76  ESC
              0x00     , // 77  NUM LOCK
              0x00     , // 78  F11
              '+'     , // 79  NUM - + (Plus)
              '3'     , // 7A  NUM 3 or PAGE DOWN
              '-'     , // 7B  NUM - - (Minus)
              '*'     , // 7C  NUM - *
              '9'     , // 7D  NUM - 9 or PAGE UP
              0x7e     , // 7E  SCROLL LOCK
              0x00     , // 7F

              0x00     , // 80
              0x00     , // 81
              0x00     , // 82
              0x00     , // 83  F7
              0x00     , // 84
              0x00     , // 85
              0x00     , // 86
              0x00     , // 87
              0x00     , // 88
              0x00     , // 89
              0x00     , // 8A
              0x00     , // 8B
              0x00     , // 8C
              0x00     , // 8D
              0x00     , // 8E
              0x00     // 8F
			  };


#ifdef graphicsengine
volatile uchar nullgopl[]={  255,flag_gopreset ,gop_int(nullgopl)   }; 
#endif
const unsigned char silent[]  PROGMEM = {128,128,128,128,0};
 