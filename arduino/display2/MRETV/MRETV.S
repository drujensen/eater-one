// MasteRasterExtendedTransmissionVision 2  2015 11 16 Creative Commons ShareAlike License 3.0
// Avr (8 bit timer) interupt routine
// I am rather proud of this bit of code - William Howard Mackenzie Parker
// beleive the code not the comments whmp

#include <avr/io.h>
#define SERIALBUFSIZEMASK 15
#include "MrEtvextensions.h"

#ifndef fontheight 
#define fontheight 8  
#endif

#undef __SFR_OFFSET
#define __SFR_OFFSET 0       

#define MasterRaster  0
#define CharSet 2
#define CharSetIndex 4 
#define RasterIndex 6 
#define LineCount 8
 #define  RasterCount 10
 #define FnHSync 11
 #define ScreenWidth 12
 #define ScreenTop 13
 #define ScreenBottom 14 
#define ScreenCenter 15
#define ScreenMode 16
#define CharRaster 17

#ifdef countframes
#define FrameCount 18
#define FrameHigh 20
#define mainsize 22
#else
#define mainsize 18
#endif

#define audiosize mainsize
#ifdef dualaudio
#define haveaudio
#define audiodatar mainsize
#define audioindexr mainsize +2
#define audiodata mainsize +4
#define audioindex mainsize +6
#undef audiosize
#define audiosize mainsize+8
#endif

#ifdef interlacedaudio
#define haveaudio
#define audiodata mainsize 
#define audioindex mainsize +2
#undef audiosize
#define audiosize mainsize+4
#endif

#ifdef monoaudio
#define haveaudio
#define audiodata mainsize 
#define audioindex mainsize +2
#undef audiosize
#define audiosize mainsize+4
#endif

#define gopsize audiosize
#ifdef graphicsengine
 #define nextgop audiosize
 #define graphicsoperations audiosize+1
 #undef gopsize
#define gopsize audiosize+3
#endif

#define fpsize gopsize
#ifdef firmwareps2port
#define fpbuf 0 + gopsize    // ps/2 port 
#define fpcount 11
#define fpin 12	
#define fpout 13 
#define keysendcount 14
#define keysend 15
#undef fpsize
#define fpsize gopsize+16
 #define keybuf fpsize  // raw keys
#define keycount 4
#define keyin 5
#define keyout 6
 #define keysize 7 
#undef fpsize
#define fpsize gopsize+23
#endif

#define fssize fpsize
#ifdef firmwareserialport
#define havepserial
#define buf  fpsize  // serial and/or ascii stream
#define sync SERIALBUFSIZEMASK+1
 #define datum SERIALBUFSIZEMASK+2
#define count SERIALBUFSIZEMASK+3
#define fsin SERIALBUFSIZEMASK+4	
#define fsout SERIALBUFSIZEMASK+5
#undef fssize
#define fssize fpsize+SERIALBUFSIZEMASK+6
#define sout fssize
#define soutcount fssize+ 1
#undef fsoutsize
#define fsoutsize fssize+2
#endif



#ifdef firmwaremultiport
#define havepserial
#define fpbuf gopsize    // ps/2 port 
#define fpcount 11
#define fpin 12	
#define fpout 13 
#define keysendcount 14
#define keysend 15
#undef fpsize
#define fpsize gopsize+16
 #define keybuf fpsize  // raw keys
#define keycount 4
#define keyin 5
#define keyout 6
 #define keysize fpsize +7 

#undef fssize
#define buf  keysize  // serial and/or ascii stream
#define sync SERIALBUFSIZEMASK+1
 #define datum SERIALBUFSIZEMASK+2
#define count SERIALBUFSIZEMASK+3
#define fsin SERIALBUFSIZEMASK+4	
#define fsout SERIALBUFSIZEMASK+5
#define fssize keysize+SERIALBUFSIZEMASK+6
#define sout fssize
#define soutcount fssize+ 1
#undef fsoutsize
#define fsoutsize fssize+2
#endif

#define translatekeysize fsoutsize
#ifdef translatekeys
#define speckey fsoutsize  // ctrl sft ect
#define fjin fsoutsize +1  // fake joystick num lock caps lock
#undef translatekeysize 
#define translatekeysize fsoutsize +2
#endif

 #define fakejoy2size translatekeysize 

#ifdef fakejoy2
#define f2jin translatekeysize  // 
#undef fakejoy2size 
#define fakejoy2size translatekeysize+1
#endif


.global TIMER2_COMPB_vect                
.type   TIMER2_COMPB_vect, @function
.global TIMER2_COMPA_vect                
.type   TIMER2_COMPA_vect, @function
.global TIMER2_OVF_vect                
.type   TIMER2_OVF_vect, @function
//************************************************************************************************

TIMER2_COMPB_vect:
PUSH  R19         
in r19,TCNT0 //   sync phase
sts FnHSync+Video,r19 // save phase for timing check
pop r19 // because it varies at powerup/reset. I blaim Heisenberg
reti
//**********************************************************************************************************

TIMER2_COMPA_vect:
TIMER2_OVF_vect:


PUSH  R19         
in    R19,SREG            
PUSH  R19           // stash status
in r19,TCNT0 // stumble into  sync (interupt does not split multi cycle opcodes)
sbrs r19,1   // fewer wasted cycles then sleeping.
rjmp 1f		
1:sbrs r19,1
rjmp 1f		
1:sbrs r19,0
rjmp 1f
1:
lds r19,FnHSync+Video         //get sync 
out PORTD,R19          // sync started
#ifdef  __AVR_ATmega2560__
#ifndef haveaudio
#ifndef havepserial
NOP  // stretch sync
#endif
#endif
#endif

push r27         
push r26        
push r0        
push r1        
push r31         
push r30          
push r29        
push r28         
push r18         

#ifdef dualaudio
lds r30,Video+audioindex         
lds r31,Video+audioindex+1        
LPM r18,Z+           //3       
LPM r19,Z
push r19           //3       
movw r28,r30
lds r30,Video+audioindexr         
lds r31,Video+audioindexr+1        
LPM r19,Z+           //3       
out OCR0A,r18        //2
out OCR0B,r19        //2
LPM r18,Z           //3   check reset audio    
push r18
sts Video+audioindexr,r30         
sts Video+audioindexr+1,r31        
506:
sts Video+audioindex,r28         
sts Video+audioindex+1,r29        
#endif

#ifdef interlacedaudio
lds r30,Video+audioindex         
lds r31,Video+audioindex+1        
LPM r18,Z+           //3       
LPM r19,Z+           //3       
out OCR0A,r18        //2
out OCR0B,r19        //2
sts Video+audioindex,r30         
sts Video+audioindex+1,r31        
LPM r18,Z+           //3   check reset audio    
push r18
#endif

#ifdef monoaudio
lds r30,Video+audioindex         
lds r31,Video+audioindex+1        
LPM r18,Z+           //3       
out OCR0A,r18        //2
out OCR0B,r18        //2
sts Video+audioindex,r30         
sts Video+audioindex+1,r31        
LPM r18,Z+           //3   check reset audio    
push r18
#endif
3001:
clr r1               // need a few zeros
#ifdef havepserial
#ifdef  __AVR_ATmega2560__
in r19,PINE
#else
in r19,PIND       // // fix 2560 here
#endif
PUSH  R19           // stash port to ensure true timming for serial
#else
PUSH  R19           // keep timming .
pop R19
#endif

// ********* count lines 
lds r30,LineCount+Video         
lds r31,LineCount+Video+1        
adiw r30,1            // inc line count
cpi r31,1         // are we 263?
brne 1263f        
cpi r30,8        
brne 1263f        
clr  r30         // yes so back to 0
clr r31        
1263:    // end of if line 263
sts LineCount+Video,r30          // store line count
sts LineCount+Video+1,r31        

// *********** set up this frame on  line 0

tst r30          // are we 0  
brne  1011f        
tst r31
brne 1011f
// set pointers to  top line of screen
lds r28,Video+MasterRaster       // y= asci  pointrer
lds r29,Video+MasterRaster+1     
sts Video+RasterIndex,r28          // store current state
sts Video+RasterIndex+1,r29        
clr r19         
sts RasterCount+Video,r19        // first raster 
sts CharRaster+Video,r19     // first raster of font char   
//count frames

lds r31,FnHSync+Video  //flip the framebit
ldi r19,_BV(0)
eor r31,r19     
sts FnHSync+Video,r31        

#ifdef countframes
lds r26,FrameCount+Video        
lds r27,FrameCount+Video+1        
adiw r26,1        
brcc 1f     
lds r28,FrameHigh+Video        
lds r29,FrameHigh+Video+1        
adiw r28,1        
sts FrameHigh+Video,r28        
sts FrameHigh+Video+1,r29        
1:
sts FrameCount+Video,r26        
sts FrameCount+Video+1,r27    
#endif   

lds r28,Video+CharSet         //x= char set start
lds r29,Video+CharSet+1  
andi r31,1
brne 88f
adiw r28,1
88:
sts Video+CharSetIndex,r28         //x= char set start
sts Video+CharSetIndex+1 ,r29 

1011:
1258:
cpi r30,248         // are we 248 
breq  1249f        
cpi r30,251           //are we 251 
brne  1252f        
1249:
lds r31,FnHSync+Video  //flip the sink, similar to tipping a cow
ldi r19,_BV(2)
eor r31,r19     
sts FnHSync+Video,r31        
1252:              
//*********** start geting  current state, want to use as many cycles in front porch as we can

 lds r31,ScreenTop+Video     
lds r0,ScreenBottom+Video     
lds r26,Video+CharSet         //not interlace use char set
lds r27,Video+CharSet+1     
lds r29,Video+RasterIndex+1        
lds r28,Video+RasterIndex           // y= ascii pointer

// *********** end horiz sync 
lds r18,FnHSync+Video  // end the sink
ldi r19,_BV(2) 
eor r18,r19     
out PORTD,r18          // sync ended 

//  ***** are we 'on scren'  // above or below visable screen we ouput nothing, sync was all
cp r30,r31           //are we at or above screen top 
brlo  148f        
cp r30,r0       //  above screen bottom?
brsh 148f       // not time to render

lds r18,ScreenCenter+Video
andi r18,7      // delay to set horz sync width and/or center left right a few pixels
breq 52f        
dec r18        // due our finest control here for dual use!
breq 52f        
dec r18        // due our finest control here for dual use!
breq 52f        
dec r18        // due our finest control here for dual use!
breq 52f        
dec r18        // due our finest control here for dual use!
breq 52f        
dec r18        // due our finest control here for dual use!
breq 52f        
dec r18        // due our finest control here for dual use!
breq 52f        
dec r18        // due our finest control here for dual use!
breq 52f        // keep delay consistant...

52:
48: 

lds r0,ScreenWidth+Video    
lds r19,RasterCount+Video      
lds r31,CharRaster+Video        
lds r30,ScreenMode+Video 
sts UDR0,r1          //start output nulls to keep timing on conditional code
ldi r18, (1<<TXEN0)
sts UCSR0B,r18
  lds r18,UBRR0    
   tst r18    // low bit slow mode
 breq 770f     // fast mode
jmp 1778f     // go to slow mode
148:   
jmp 1148f   // go off screen
770:
sts UDR0,r1         //  another byte gives us a little less than 32 clocks total for set up
mov r18,r30 
tst r30
brne 778f
lds r26,Video+CharSetIndex         //not interlace use char set
lds r27,Video+CharSetIndex+1  
inc r30  // need to be a 1 now to inc charaster...
778:
add r26,r31          //now add the  char line offset
adc r27,r1         // r1 is a 0  
inc r19 // pre calc next line since there is a centering delay (probably)
cp r19,r30 //char height r30 
brne 1f
clr r19
inc r31  // raster line of character
tst r18
brne 1f
inc r31  // raster line of character
1:
andi r31,fontheight-1  // ?-1 lines a char
sts RasterCount+Video,r19   

    40: 
LDS     r19,UCSR0A  // check 
sbrs r19, UDRE0   
rjmp 40b        
sts UDR0,r1 
sts CharRaster+Video,r31   // ready for next time... except maybe text index

141:
   lds r18,ScreenCenter+Video          // delay to center by chars 
   lsr r18
lsr r18          // delay to center by chars top 5 bits
lsr r18          // delay to center by chars 
breq 42f        

    40: 
LDS     r19,UCSR0A  // check 
sbrs r19, UDRE0   
rjmp 40b        
sts UDR0,r1         //  
 41: dec r18        
  brne 40b        
    42: 
  40:
   LDS     r18,UCSR0A     // last one outside the loop is best entry into time critical loop
   sbrs r18,UDRE0
     rjmp 40b        
 sts UDR0,r1           //  a little less than 32 clocks ahead again.
   LDS r18,ScreenWidth+Video          // chars per line

// have to read ascii, look up char PROGMEM, (auto) index raster line of char, output 8 pix, and count loops in 16 clocks...  
2: 
ld r19,Y+      //2 next char to remder
ldi r30,fontheight        //1
mul r19,r30        //2 char val *fontheight is now in r0-r1
movw r30,r26        //1 get ascii table start
add r30,r0         //1 add off set
adc r31,r1          //1 we are set up for next char
LPM r19,Z           //3       
sts 0xc6,r19        //2
dec r18        //1
brne 2b        //2 
//Done with exactly 16 clocks !

98:    
rjmp 98f   //turn off with slow code

1778: // from fast render
cpi r18,3 // longer ticks and we dont need another delay byte...
brge 777f
sts UDR0,r1         //  another byte gives us  64 or more clocks total for set up
777:

mov r18,r30 
tst r30
brne 778f
lds r26,Video+CharSetIndex         //not interlace use char set
lds r27,Video+CharSetIndex+1  
inc r30  // need to be a 1 now to inc charaster...
778:
add r26,r31          //now add the  char line offset
adc r27,r1         // r1 is a 0  
inc r19 // pre calc next line since there is a centering delay (probably)
cp r19,r30 //char height r30 
brne 1f
clr r19
inc r31  // raster line of character
tst r18
brne 1f
inc r31  // raster line of character
1:
andi r31,fontheight-1  // 8 lines a char
sts CharRaster+Video,r31   // ready for next time... except maybe text index
sts RasterCount+Video,r19   
141:
   lds r18,ScreenCenter+Video          // delay to center by chars 
   lsr r18
lsr r18          // delay to center by chars top 5 bits
lsr r18          // delay to center by chars 
breq 42f        

    40: 
LDS     r19,UCSR0A  // check 
sbrs r19, UDRE0   
rjmp 40b        
sts UDR0,r1         //  
 41: dec r18        
  brne 40b        
    42: 

LDS r18,ScreenWidth+Video          // chars per line
2: 
ld r19,Y+      //2 next char to remder
ldi r30,fontheight        //1
mul r19,r30        //2 char val *fontheight is now in r0-r1
movw r30,r26        //1 get ascii table start
add r30,r0         //1 add off set
adc r31,r1          //1 we are set up for next char
40: 
LDS     r19,0xc0    // wait added for wide pixels and fast cpu
sbrs r19,5     
rjmp 40b        
LPM r19,Z           //3       
sts 0xc6,r19        //2
dec r18        //1
brne 2b        //2 


98:    
clr r1         // will turn off tx after all data is sent
STS UCSR0B,r1       
lds r19,RasterCount+Video        
lds r31,CharRaster+Video        
or r19,r31 //raster 0 of char raster 0 next time, so move text index
brne 150f
sts Video+RasterIndex,r28           
sts Video+RasterIndex+1,r29           
jmp 150f

1148:
// interupt our interupt at screen top -2, screen bottom, and screen bottom +1
breq  147f         // line after screen data is screen bottom, branch to user int.
inc r0     // screen bottom+1
cp r30,r0      
breq  147f         // screen bottom+1
dec r31     // line before screen data starts
dec r31     // line before screen data starts
cp r30,r31      
brne 1f     
147: 
push r25         // preserve reg that c may trash
push r24          //can i force a c function to preserve all?
push r23        
push r22        
push r21        
push r20        
call RasterInt    
pop r20        
pop r21        
pop r22        
pop r23        
pop r24        
pop r25        
1: 

150:        
#ifdef firmwareps2port
1003:
in r30,SPSR
sbrs r30,SPIF
rjmp 1004f
; Read received data and return
in r19,SPDR
ldi r30, lo8(Video+fpbuf)   // ps2 port structure
ldi r31, hi8(Video+fpbuf)
movw r28,r30 // copy pointer
ldd r18,z+fpin  //next  in location in bufer
add r28,r18  // add the offset
adc r29,r1
st Y,r19   // store byte
inc r18  // move offset
cpi r18,11// wrap the circulure buffer?
brne 1006f
clr r18
1006:
std z+fpin,r18 // update in position
ldd r28,z+fpcount  
adiw r28,8 // 8 bits in
std z+fpcount,r28
1004:
#endif

#ifdef firmwaremultiport
pop r0 // our stashed serial port read
lds r30,LineCount+Video
lsr r30
brcs 1024f
  1003:  // ps/2 port ***************************************************8
in r30,SPSR  // are 8 bits ready?
sbrs r30,SPIF
rjmp 1004f  // no , nothin to do
; Read received data and return
in r19,SPDR
ldi r30, lo8(Video+fpbuf)  // ps/2 connector 
ldi r31, hi8(Video+fpbuf)
movw r28,r30
ldd r18,z+fpin  //next  in location in bufer
add r28,r18  // add the offset
adc r29,r1
st Y,r19   // store byte
inc r18  // move offset
cpi r18,11// wrap the circulure buffer?
brne 1006f
clr r18
1006:
std z+fpin,r18 // update in position
ldd r28,z+fpcount  
adiw r28,8 // 8 bits in
std z+fpcount,r28
rjmp 1004f

1024:  // Serial port ***************************************************88
ldi r30, lo8(Video+buf)   // PIND bit 0
ldi r31, hi8(Video+buf)// 2400 baud 
1025:
ldD r18,Z+sync         
tst r18 // is serial active? 
brpl 1011f // neg means waiting for stop bit of last byte
sbrc r0,0  // bit set will be the stop bit
clr r18  // swe can get new byte now
rjmp 1002f
1011:
brne 1001f // yes goto active serial handling
sbrc r0,0  // bit clear is a start bit!
rjmp 1002f // goto exiting no start bit
ldi r18,7+32// shift linecntr trick, mark hi bit for timing comp at 4800 baud (.3048 bits - rasterline)
rjmp  1002f // we are set up to receive a byte goto exiting	
1001: // active serial data handling
lsr r18 // count lines into serial byte
brne 110f // can't leave shfter empty or we quit active serial
ldi r18,16// setting high eventualy helps timming comp
110:
brcs 1002f // not time for a bit goto exiting
ldd r19,Z+datum  // current byte
lsr r19  // check if its last bit
sbrc r0,0  // get a bit    // fix 2560 here
ori r19,128   // setum if ya gutum
brcc 1003f //goto new bit- the previous two instructions did not touch carry flag
ldd r18,Z+count //space available in bufer
dec r18
brmi 1015f // no room ...to the bit bucket with it
std Z+count,r18 // update count
movw r28,r30
ldd r18,z+fsin  //next  in location in bufer
add r28,r18  // add the offset
adc r29,r1
st Y,r19   // store byte
inc r18  // move offset
andi r18,SERIALBUFSIZEMASK  // wrap the circulure buffer
std z+fsin,r18 // update in position
1015:
ldi r18,128  // mark wait for stop bit 
std z+datum,r18  // ready for next byte
rjmp 1002f // goto exiting byte done , serial count is 0 we are waiting for a new byte to start
1003: // new bit
std z+datum,r19  // current byte
lsl r18 // back up our timming comp 1
lsl r18 // back up our timming comp 1
ori r18,3// count for next byte  , skip 2 sample 3rd , hi bit slides in to skip bit 11 for timming comp
1002: // exiting
std z+sync,r18 //  save state
1004:
9999:

#ifndef noserialsend
       // else do serial send ***********************************************8
	   lds r31,soutcount+Video
	   	  subi r31,1
	  breq 510f // nothing to send go check ps2 port
brhc 511f // not bit time just store count
 	   lds r28,OCR2B 
	ldi r19,65  //6.51 lines /bit =2400 baud
	   add r28,r19
	   andi r28,127
501:
cpi r31,0x9f // start bit low
	   brne 501f 
	   ldi r28,1 
		  sts OCR2B,r28
 	  	   rjmp 901f
501:
	   cpi r31,0xf // stop bit 
	   brne 501f 
 		   rjmp 952f
1024: rjmp 1024f		   
501:		   
  502:
lds r30, TCNT2
	   cp r30,r28
	   brlo 502b
900: 
lds r1, sout+Video // set bit
	   ror r1
	   sts sout+Video,r1
	   brcc 901f
952:
	   ldi r18,_BV(COM2B1)+_BV(COM2B0)+_BV(WGM21) //high on match, ctc
	   rjmp 910f
901:
		ldi r18,_BV(COM2B1)+_BV(WGM21) //low on match, ctc
910:	
   sts TCCR2A,r18
 andi r31,0xf5 //wait 6 lines, keep top nibble 
 sts OCR2B,r28
 cpi r28,60  // roll over? soon
 brlo 511f
 inc r31 // extra line
 511:
 sts soutcount+Video,r31
510:
1024:
#endif

#endif //fakeserialport

#ifdef firmwareserialport
pop r0 // our stashed serial port read
lds r30,LineCount+Video
lsr r30
brcs 1024f  // go do serial port
// room here for some thing ?
rjmp 1004f
1024:  // Serial port ***************************************************88
ldi r30, lo8(Video+buf)   // PIND bit 0
ldi r31, hi8(Video+buf)// 2400 baud 
1025:
ldD r18,Z+sync         
tst r18 // is serial active? 
brpl 1011f // neg means waiting for stop bit of last byte
sbrc r0,0  // bit set will be the stop bit
clr r18  // swe can get new byte now
rjmp 1002f
1011:
brne 1001f // yes goto active serial handling
sbrc r0,0  // bit clear is a start bit!    // 2560 here
rjmp 1002f // goto exiting no start bit
ldi r18,7+32// shift linecntr trick, mark hi bit for timing comp at 4800 baud (.3048 bits - rasterline)
rjmp  1002f // we are set up to receive a byte goto exiting	
1001: // active serial data handling
lsr r18 // count lines into serial byte
brne 110f // can't leave shfter empty or we quit active serial
ldi r18,16// setting high eventualy helps timming comp
110:
brcs 1002f // not time for a bit goto exiting
ldd r19,Z+datum  // current byte
lsr r19  // check if its last bit
sbrc r0,0  // get a bit   
ori r19,128   // setum if ya gutum
brcc 1003f //goto new bit- the previous two instructions did not touch carry flag
ldd r18,Z+count //space available in bufer
dec r18
brmi 1015f // no room ...to the bit bucket with it
std Z+count,r18 // update count
movw r28,r30
ldd r18,z+fsin  //next  in location in bufer
add r28,r18  // add the offset
adc r29,r1
st Y,r19   // store byte
inc r18  // move offset
andi r18,SERIALBUFSIZEMASK  // wrap the circulure buffer
std z+fsin,r18 // update in position
1015:
ldi r18,128  // mark wait for stop bit 
std z+datum,r18  // ready for next byte
rjmp 1002f // goto exiting byte done , serial count is 0 we are waiting for a new byte to start
1003: // new bit
std z+datum,r19  // current byte
lsl r18 // back up our timming comp 1
lsl r18 // back up our timming comp 1
ori r18,3// count for next byte  , skip 2 sample 3rd , hi bit slides in to skip bit 11 for timming comp
1002: // exiting
std z+sync,r18 //  save state
1004:
9999:

#ifndef noserialsend
       // else do serial send ***********************************************8
	   lds r31,soutcount+Video
	   	  subi r31,1
	  breq 510f // nothing to send go check ps2 port
brhc 511f // not bit time just store count
 	   lds r28,OCR2B 
	ldi r19,65  //6.51 lines /bit =2400 baud
	   add r28,r19
	   andi r28,127
501:
cpi r31,0x9f // start bit low
	   brne 501f 
	   ldi r28,1 
		  sts OCR2B,r28
 	  	   rjmp 901f
501:
	   cpi r31,0xf // stop bit 
	   brne 501f 
 		   rjmp 952f
1024: rjmp 1024f		   
501:		   
  502:
lds r30, TCNT2
	   cp r30,r28
	   brlo 502b
900: 
lds r1, sout+Video // set bit
	   ror r1
	   sts sout+Video,r1
	   brcc 901f
952:
	   ldi r18,_BV(COM2B1)+_BV(COM2B0)+_BV(WGM21) //high on match, ctc
	   rjmp 910f
901:
		ldi r18,_BV(COM2B1)+_BV(WGM21) //low on match, ctc
910:	
   sts TCCR2A,r18
 andi r31,0xf5 //wait 6 lines, keep top nibble 
 sts OCR2B,r28
 cpi r28,60  // roll over? soon
 brlo 511f
 inc r31 // extra line
 511:
 sts soutcount+Video,r31
510:
1024:
#endif

#endif //fakeserialport

// this is broken again so don't tell anyone its here and it will never be compiled in ... fix it again after release
#ifdef halfrateaudio  // repeat each sample twice
lds r30,LineCount+Video
lsr r30
brcc 1999f
lds r30, Video+FnHSync
sbrc r30,4
rjmp 1999f  // not half rate.
pop r18  // trash reset check
#ifdef dualaudio
lds r30,Video+audioindex       // get index  
lds r31,Video+audioindex+1        
LD r18,-Z           //3       repeat this byte
sts Video+audioindex,r30         
sts Video+audioindex+1,r31        
lds r30,Video+audioindexr         // and for other chanel
lds r31,Video+audioindexr+1        
LD r19,-Z           //3       
sts Video+audioindexr,r30         
sts Video+audioindexr+1,r31        
506:

#endif
#ifdef interlacedaudio
lds r30,Video+audioindex         
lds r31,Video+audioindex+1        
LD r18,-Z           //3    two bytes  back 
LD r18,-Z           //3       
sts Video+audioindex,r30         
sts Video+audioindex+1,r31        
#endif
#ifdef monoaudio
lds r30,Video+audioindex         
lds r31,Video+audioindex+1        
LD r18, -Z 
sts Video+audioindex,r30         
sts Video+audioindex+1,r31        
#endif
1999:
#else  //halfrateaudio

//************** Audio !
#ifdef dualaudio
pop r18
tst r18 
brne 370f
lds r28,Video+audiodatar     
lds r29,Video+audiodatar+1     
sts Video+audioindexr,r28          // store current state
sts Video+audioindexr+1,r29       
370:
pop r18
tst r18 
brne 370f
lds r28,Video+audiodata     
lds r29,Video+audiodata+1     
sts Video+audioindex,r28          // store current state
sts Video+audioindex+1,r29       
370:
505:
#endif

#ifdef interlacedaudio
pop r18
tst r18 
brne 370f
lds r28,Video+audiodata     
lds r29,Video+audiodata+1     
sts Video+audioindex,r28          // store current state
sts Video+audioindex+1,r29       
370:
#endif

#ifdef monoaudio
pop r18
tst r18 
brne 370f
lds r28,Video+audiodata     
lds r29,Video+audiodata+1     
sts Video+audioindex,r28          // store current state
sts Video+audioindex+1,r29       
370:
#endif

2001:
#endif //halfrateaudio

#ifdef graphicsengine
lds r28,LineCount+Video    // operate on proper line     
lds r18,Video+nextgop
cp r18,r28
brne 300f // not our line. leave pointer where it was. we are done
lds r30,Video+graphicsoperations       // the instruction list  
lds r31,Video+graphicsoperations+1        
ld r19,Z+      // our OPERATION MAP         
tst r19
breq 399f // nothin to do but keep in sync 8 bits dont make 264 .
brpl 301f // bit 7 UBRR0
ld r18,Z+     // char width         
sts UBRR0,r18
301:
lsr r19 //bit 0 
brcc 302f 
ld r18,Z+     // text index         
sts Video+RasterIndex,r18
ld r18,Z+ 
sts Video+RasterIndex+1,r18
302: // bit 1
lsr r19
brcc 303f
ld r18,Z+              
sts Video+CharSet,r18
ld r18,Z+              
sts Video+CharSet+1,r18
303: // bit 2
lsr r19
brcc 304f
ld r18,Z+              
sts ScreenWidth+Video,r18
304:  // bit 3
lsr r19
brcc 305f
ld r18,Z+              
sts ScreenMode+Video,r18
305:  // bit 4
lsr r19
brcc 306f
ld r18,Z+              
sts ScreenTop+Video,r18              
ld r18,Z+              
sts ScreenBottom+Video,r18
306: // bit 5 screen center
lsr r19
brcc 307f
ld r18,Z+  //  instruction bitmap               
sts ScreenCenter+Video,r18
307: // bit 6 reset the graphicsoperations list !!!
lsr r19
brcc 399f
ld r18,Z+  //  instruction bitmap               
ld r19,Z+  //  instruction bitmap               
movw r30,R18
399:
ld r18,Z+      // our target          
sts Video+nextgop,r18
sts Video+graphicsoperations,r30
sts Video+graphicsoperations+1,r31
300:
#endif
#ifdef noserialsendextra
       // else do serial send ***********************************************8
	   lds r31,soutcount+Video
	   	  subi r31,1
	  breq 510f // nothing to send go check ps2 port
brhc 511f // not bit time just store count
 	   lds r28,OCR2B 
	ldi r19,65  //6.51 lines /bit =2400 baud
	   add r28,r19
	   andi r28,127
501:
cpi r31,0x9f // start bit low
	   brne 501f 
	   ldi r28,1 
		  sts OCR2B,r28
 	  	   rjmp 901f
501:
	   cpi r31,0xf // stop bit 
	   brne 501f 
 		   rjmp 952f
1024: rjmp 1024f		   
501:		   
  502:
lds r30, TCNT2
	   cp r30,r28
	   brlo 502b
900: 
lds r1, sout+Video // set bit
	   ror r1
	   sts sout+Video,r1
	   brcc 901f
952:
	   ldi r18,_BV(COM2B1)+_BV(COM2B0)+_BV(WGM21) //high on match, ctc
	   rjmp 910f
901:
		ldi r18,_BV(COM2B1)+_BV(WGM21) //low on match, ctc
910:	
   sts TCCR2A,r18
 andi r31,0xf5 //wait 6 lines, keep top nibble 
 sts OCR2B,r28
 cpi r28,60  // roll over? soon
 brlo 511f
 inc r31 // extra line
 511:
 sts soutcount+Video,r31
510:
1024:
#endif

pop r18        
pop r28        
pop r29        
pop r30        
pop r31        
pop r1        
pop r0        

151: 
pop r26        
pop r27        
pop r19        
OUT       SREG,R19        
 pop r19        
 
reti     //
