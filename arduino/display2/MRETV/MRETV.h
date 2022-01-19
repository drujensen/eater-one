// MasteRasterExtendedTransmissionVision 2  2015 11 16  Creative Commons ShareAlike License 3.0
// object definitions and helper defines
// beleive the code not the comments whmp

#ifndef MrEtv_h
#define MrEtv_h
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <math.h>
#include <avr/EEPROM.h>
typedef unsigned char  uchar ;
typedef  unsigned int uint;
#define SERIALBUFSIZEMASK 15
#define SERIALBUFSIZE 16
#define SERIALCNT (SERIALBUFSIZE-serialcount)
#ifdef  __AVR_ATmega2560__
#define mclock _BV(1)
#define mdata _BV(2)
#else
#define mclock _BV(5)
#define mdata _BV(3)
#endif

#include "MrEtvextensions.h"   // customise the object 


extern unsigned char strtemp[]; 
extern  const unsigned char   *  const sounds[] PROGMEM;
extern const unsigned char silent []  PROGMEM;
extern const unsigned char keycode []  PROGMEM;
extern const unsigned char sftcode []  PROGMEM;
extern volatile uchar nullgopl[];

#ifndef ADC_SAMPLECOUNT 
#define ADC_SAMPLECOUNT 10  // max  64 so we dont ovf
#endif

#ifndef fontheight 
#define fontheight 8  
#endif

#define ADC_START (_BV(ADEN)|_BV(ADPS1)|_BV(ADPS2)|_BV(ADPS0)|_BV(ADSC)) // enable+ set best clock+ start
#define ADC_11V (_BV(REFS0)|_BV(REFS1) )// internal 1.1 v ref
#define ADC_5V (_BV(REFS0) ) //vcc as ref

#define key_lwin _BV(0)
#define key_rwin _BV(1)
#define key_lalt _BV(2)
#define key_ralt _BV(3)
#define key_lsft _BV(4)
#define key_rsft _BV(5)
#define key_lctr _BV(6)
#define key_rctr _BV(7)
#define key_sftlock _BV(7)
#define key_numlock _BV(6)
#define key_ESCNEXT _BV(5)

#define key_sft ((Video.speckey&(key_lsft|key_rsft))||(key_sftlock&Video.fjin))
#define key_alt (Video.speckey&(key_lalt|key_ralt))
#define key_win (Video.speckey&(key_lwin|key_rwin))
#define key_ctr (Video.speckey&(key_lctr|key_rctr))
#define key_nlock (key_numlock&Video.fjin)
#define ESCNEXT (key_ESCNEXT&fjin)  // only use inside MRETV

#define flag_gopcharwidth _BV(7) // 1 byte 
#define flag_gopindex _BV(0) // set text index . two byte address
#define flag_gopcharset _BV(1) // set char set. two byte progmem address
#define flag_gopscreenwidth _BV(2) // 1 byte
#define flag_gopcharheight _BV(3) // 1 byte
#define flag_goptopbottom _BV(4) // two bytes top bottom
#define flag_gopcenter _BV(5) // set up screen 1 byte center
#define flag_gopreset _BV(6)  //  reset graphics operations list. two byte address  (realy a jump instruction)

#define gop_int(x) ((uchar)(((int)x)&0xff)),((uchar)(((int)x)>>8))  // make two byte entry

#ifdef graphicsengine
#define setgoplist(x) cli();Video.nextgop=*x;Video.graphicsoperations=x+1;sei();
#else
#define setgoplist(x)  
#endif


#define rjdown (jin&1)
#define rjup (jin&8)
#define rjleft (jin&2)
#define rjright (jin&4)
#define rjbutton (jin&16)
#define rjall (jin&31) 

#define fjdown (Video.fjin&1)
#define fjup (Video.fjin&8)
#define fjleft (Video.fjin&2)
#define fjright (Video.fjin&4)
#define fjbutton (Video.fjin&16)
#define fjall (Video.fjin&31) 

#define f2jdown (Video.f2jin&1)
#define f2jup (Video.f2jin&8)
#define f2jleft (Video.f2jin&2)
#define f2jright (Video.f2jin&4)
#define f2jbutton (Video.f2jin&16)
#define f2jall (Video.f2jin&31) 

class MasteRasterExtendedTransmissionVision_Stereo_Gop_PS2_2400n81  {   // a rose by any other name
public:
  volatile uchar  *MasterRaster,*CharSet,*CharSetIndex,*RasterIndex;
    volatile uint LineCount;
  volatile uchar RasterCount,FnHSync,ScreenWidth,ScreenTop,ScreenBottom,
  ScreenCenter,ScreenMode,CharRaster;
#ifdef countframes
volatile uint FrameCount, FrameHigh;
#endif

  #ifdef dualaudio
 #define haveaudio
  #define havestereo

 const unsigned char * audiodatar,*audioindexr,*audiodata,*audioindex;
#endif

#ifdef interlacedaudio
 #define haveaudio
 #define havestereo
const unsigned char *audiodata,*audioindex;
#endif

#ifdef monoaudio
 #define haveaudio

const unsigned char *audiodata,*audioindex;
#endif

#ifdef graphicsengine
  volatile uchar nextgop, *graphicsoperations;
#endif

#ifdef firmwareps2port
#define haveps2
volatile uchar fpbuf[11];
  volatile uchar fpcount,fpin,fpout,keysendcount,keysend;
volatile uchar keybuf[4];
  volatile uchar keycount,keyin, keyout;
#endif

#define fssize fpsize
#ifdef firmwareserialport
#define havesp
volatile uchar buf[SERIALBUFSIZEMASK+1];
  volatile uchar sync,datum,count,fsin, fsout;

 volatile char sout, soutcount;
#endif
#ifdef firmwaremultiport
#define havesp
#define haveps2

volatile uchar fpbuf[11];

  volatile uchar fpcount,fpin,fpout,keysendcount,keysend;
volatile uchar keybuf[4];
volatile uchar keycount,keyin, keyout;
volatile uchar buf[SERIALBUFSIZEMASK+1];
volatile uchar sync,datum,count,fsin, fsout;
 volatile char sout, soutcount;
#endif


 #ifdef translatekeys
 volatile uchar speckey,fjin;
#endif
 #ifdef fakejoy2
volatile uchar f2jin; 
#endif

 
 void setup() { // only called once to initialize system
  cli();
#ifdef  __AVR_ATmega2560__
 PORTG=0;
  DDRG=_BV(5);  
PORTE=0;
  DDRE=0;   // using bit E0 input for soft serial rx
TCCR3A=0; // stop
  TCCR3B=0;// stop
  TCCR3C=0; // stop
#endif
   DDRC=0;
 PORTC=0;
  DDRD=0;  // all in
 PORTD=0;// all pull up off
  DDRD|=_BV(6)+_BV(5)+_BV(3)+_BV(1)+_BV(2);  //left,right  out + video outs+firmwareserial out
  PORTD&=~(_BV(6)+_BV(5));// low
#ifdef  __AVR_ATmega2560__
 PORTG=0;
  DDRG=_BV(5);  // audio
   DDRB|=_BV(7); // audio out
   DDRB&=~(_BV(0)+_BV(3)+_BV(2)+_BV(1))+_BV(4); // spi and help all in
PORTB=_BV(0)+_BV(3)+_BV(2)+_BV(1)+_BV(4);//_BV(0)+_BV(4)+;// pull ups on
#else
   DDRB&=_BV(0);
    DDRB&=~(_BV(0)+_BV(3)+_BV(2)+_BV(1))+_BV(4); // spi and help all in
PORTB=_BV(5)+_BV(3)+_BV(2)+_BV(1)+_BV(4);//_BV(0)+_BV(4)+;// pull ups on
 #endif
 #ifdef havesp
  datum=128; // a must or our first serial byte is Fnmjsoid up.
 count=16; // count of EMPTY space left, 0 = full !
 fsin=0;
fsout=0;
sync=0;
 soutcount=1;  // nothing to serial send. ????1???
 #endif

#ifdef haveps2
// the PS/2 port
fpcount=0;  
fpin=0;
 fpout=0;
  SPCR=0;
  SPCR=_BV(SPE)+_BV(DORD)+_BV(CPOL);
write2key(0xff);
 #endif
  TCCR0A=0; // stop
  TCCR2A=0;// stop
  TCCR0B=0; // stop
  TCCR2B=0;// stop
  TCNT2=0; // sync audio for easy missing update fix
  TCNT0=203; 
  TCCR2B =  _BV(CS21); // clocks*16, start timmer
  TCCR0B=_BV(CS00);// clocks, start timmer
TCCR2A = 0;
  OCR2A = 127; // ctc val
  OCR2B = 127; //  investigate interupt phaseing  
 TIMSK2 = _BV(OCIE2B);
TCCR2A = _BV(WGM21);
 uchar a;
 sei();
 for (a=0;a<200;a++){
FnHSync=80;
while(FnHSync==80);
if(((FnHSync&3)==0)||((FnHSync&3)==3) )TCNT0=a; // need a different stumble for these so avoid them
FnHSync=80;
	}
  cli();
   TIMSK2 = 0;
TCCR2A = 0;
  PCMSK2=0; // monitor clock line only
  PCMSK1=0; // monitor clock line only
 #ifdef  __AVR_ATmega2560__
 PCMSK0=_BV(PCINT4); // monitor clock line
#else
  PCMSK0=_BV(PCINT1); // monitor clock line
 #endif
 PCICR=0; // don't interupt
#ifdef countframes
FrameCount=0;
  FrameHigh=0;
   #endif
  } 


 void begin(const unsigned char* CharBase,volatile uchar * textbuf,uchar lines, uchar cols,uchar top,uchar left,uchar mode)
{
if(!CharSet&&!MasterRaster)setup();
  cli();
  TWCR=0;
  TIMSK0=0;
  TIMSK1=0;
  TIMSK2=0;
 #ifdef  __AVR_ATmega2560__
  TIMSK3=0;
  TIMSK4=0;
  TIMSK5=0;
  UCSR1B=0;
  UCSR2B=0;
  UCSR3B=0;
   #endif
#ifdef graphicsengine
 graphicsoperations=nullgopl+1;
   nextgop=*nullgopl;
#endif
#ifdef haveaudio
  audiodata=silent;
  audioindex=silent;
#ifdef havestereo
   audiodatar=silent;
 audioindexr=silent;
#endif
#endif
CharSet=(uchar *)CharBase;
CharSetIndex=(uchar *)CharBase;
MasterRaster=textbuf;
ScreenWidth=cols;
ScreenCenter=(left);
ScreenTop=top;
ScreenMode=mode&0x1f; // lower 5 cnaracter hight, upper 3 bits pixel width
  ScreenBottom=top+lines;
LineCount = 0;
CharRaster=0; 
FnHSync =0b00000000; // bitwise 0
 TCCR2A = _BV(WGM21);
  OCR2A = 127;
   TIMSK2 = _BV(OCIE2A);
   UCSR0B = _BV(TXEN0);
  UCSR0C = _BV(UMSEL01) | _BV(UMSEL00);
  UBRR0=((mode&0xE0)>>5);
    TCCR0A= _BV(WGM00) | _BV(WGM01)| _BV(COM0A1) | _BV(COM0B1) ; // clear on match better to charge extra then discharge on missed update update 
    TIFR2=_BV(OCF2B)+_BV(OCF2A)+_BV(TOV2);// clear any pending interupts
 sei();
}

void begin(const unsigned char* CharBase,char * textbuf,uchar lines, uchar cols,uchar top,uchar left,uchar mode){
 begin( CharBase,(volatile uchar *) textbuf,lines,  cols, top, left, mode);
}

void on(){  TIMSK2 = _BV(OCIE2A);}
void off(){  TIMSK2 = 0;}

// portd is heavily used by MRETV so only write to it using these routines
// reads can be done normaly
void bitsetPORTD(uchar bits){   
FnHSync|=bits;
}
void bitclearPORTD(uchar bits){
FnHSync&=~bits;
}

#ifdef havesp
char forceS(char a){  // force data into serial buf;
    while(datum&1); // high the last 3 scan lines of incomming char, avoid missed update !
    if(count){
      buf[fsin++]=a;
      fsin&=SERIALBUFSIZEMASK;
      count--;
      return(0);
    }
    return(a);
  }

  char readS(){  // read from serial buffer 2400 baud  in
    uchar a;
 
	if(count>=16)return(0);
   {
      a=buf[fsout++];
      fsout&=SERIALBUFSIZEMASK;
      while(datum&1); // high the last 3 scan lines of incomming char, avoid missed update !
      count++;
    }
    return(a);
  }

  void writeS(char a){ // write out serial port 2400 baud out
    while(soutcount!=1); // busy?
    while(LineCount!=ScreenBottom); // do off screen ???
   	sout=a;
   soutcount=0xa0;
  }
  
  void stringS(const  char * b){
    char a; // write out serial port 2400 baud out
    while((a=*b++))writeS(a);
      }
void stringS(const unsigned char * b){
    stringS((const char * )b);
          }
#ifdef translatekeys
 uchar key2S(){  // ps2 port data merg to serial buf, called durring interupts
    char a ;
//if(key_numlock&fjin)   writeS(a);
 if(count){  // room in serial buf
      if((a=read())){
        forceS(a);
		return(1);
		}
    }
 return(0);
 }
#endif
#endif
#ifdef haveps2
  char writeK(char a){  // place data into key buf;
    if(keycount<4){
      keybuf[keyin++]=a;
      keyin&=3;
      keycount++;
      return(0);
    }
    return(a);
  }

  char readK(){  // read from key buffer
    char a=0;
    if(keycount){
      a=keybuf[keyout++];
      keyout&=3;
      keycount--;
    }
    return(a);
  }
  #ifdef translatekeys

  uchar read(){ //filtered  read (shaken but not not stirred) keyboard stream
      uchar b;
    if(!keycount)return(0); // aint got none
    b=keybuf[keyout];   // a key code , or part of
    switch(b){
    case 0x5a:  //return into cr lf
	    keybuf[keyout]=0x5e;   //  to make this an crlf sequence will get found next, translates to 0a in look up
     return(0x0d);

  case 0xe0:  // escaped char   ******************************************************
      if (keycount<2)return(0); // need more to see if we are escape key up.
  if(keybuf[(keyout+1)&3]==0xf0) {//key up
    keycount-=1;        // we kill the escape only now
      keyout=(keyout+1)&3;  
	 fjin|=key_ESCNEXT; // next char is escaped
 return(0);	
}   
	  else  { // send  1b 5b sequence
     keybuf[keyout]=0x5f;   //  to make this an escape sequence will get found next, translates to 5b in look up
     return(0x1b);
}
    case 0xf0: // a key up  *********************************************************
      if (keycount<2)return(0); // need rest of key up
      b=keybuf[(keyout+1)&3]; // the kind of key up
      keycount-=2;       
      keyout=(keyout+2)&3; 
      switch(b){
      case 0x11:        
        speckey&=~key_lalt;        
        break;
      case 0x14:        
        speckey&=~key_lctr;        
        break;
      case 0x12:        
        speckey&=~key_lsft;        
  #ifdef fakejoy2
    f2jin&=~16;        
#endif         
 break;
      case 0x59:        
        speckey&=~key_rsft;        
        fjin&=~16;        
        break;
      case 0x58:            
        fjin^=key_sftlock;  
        updateleds();    
        break;
      case 0x77:            
        fjin^=key_numlock;    
        updateleds();  
        break;
		if(ESCNEXT){
     case 0x75:      
          fjin&=~8;      
          break;
        case 0x72:      
          fjin&=~1;      
          break;
        case 0x74:       
          fjin&=~4;      
          break; 
        case 0x6b:      
          fjin&=~2;      
          break;
		  }
  #ifdef fakejoy2
        case 0x1d:      
          f2jin&=~8;      
          break;
        case 0x1c:      
          f2jin&=~2;      
          break;
        case 0x1b:       
          f2jin&=~1;      
          break; 
        case 0x23:      
          f2jin&=~4;      
          break;
  #endif
      case 0x27:      
          speckey&=~key_rwin;      
          break;
        case 0x1f:      
          speckey&=~key_lwin;      
          break;
 }
      return(0);

      // NORMALISH CHARACTERS
    case 0x11:      
      speckey|=key_lalt;      
      break;
    case 0x14:      
      speckey|=key_lctr;      
      break;
    case 0x12:      
      speckey|=key_lsft;     
 #ifdef fakejoy2
     f2jin|=16;      
 #endif
    break;
    case 0x59:        
      speckey|=key_rsft;    
      fjin|=16;      
      break;
  
if(ESCNEXT){

case 0x75:      
        fjin|=8;      
          break;
      case 0x72:      
        fjin|=1;      
       break;
      case 0x74:       
        fjin|=4;      
          break;
      case 0x6b:      
        fjin|=2;      
         break;  
   }
 #ifdef fakejoy2
case 0x1d:      
          f2jin|=8;      
          break;
        case 0x1c:      
          f2jin|=2;      
          break;
        case 0x1b:       
          f2jin|=1;      
          break; 
        case 0x23:      
          f2jin|=4;      
          break;
  #endif
   case 0x27:      
        speckey|=key_rwin;      
        break;
      case 0x1f:      
        speckey|=key_lwin;      
        break;

    }   
    keyout=(keyout+1)&3; // inc + bound for next time
if(b==0x5f)fjin|=key_ESCNEXT;// next char is escaped
else if(b==0xf0);// next char is still escaped key up
else  fjin&=~key_ESCNEXT; // not any more
  keycount-=1;
	if(b>0x8f)return(0);
    if(((speckey&(key_lsft|key_rsft))||(key_sftlock&fjin)))      return ( pgm_read_byte(&(sftcode[b])  )); // shifted character
    return ( pgm_read_byte(&(keycode[b])  )); // plain char
  }
  #endif
     char getraw(char index ){ // find a 8 bit needle in the 11 bit haystasck.
    switch(index){ // get byte and skidadle
    case 0: // bits 1-8
       return( ( fpbuf[0]>>1)|( fpbuf[1]<<7)  );
    case 1: // bits 12-19
       return( ( fpbuf[1]>>4)|( fpbuf[2]<<4)  );
    case 2: // bits 23-30
       return( ( fpbuf[2]>>7)|( fpbuf[3]<<1)  );
    case 3: // bits 34-41
      return( ( fpbuf[4]>>2)|( fpbuf[5]<<6)  );
    case 4: // bits 45-52
       return( ( fpbuf[5]>>5)|( fpbuf[6]<<3)  );
    case 5: // bits 56-63
       return( fpbuf[7]);
    case 6: // bits 67-74
       return( ( fpbuf[8]>>3)|( fpbuf[9]<<5)  );
    case 7: // bits 78-85
      return( ( fpbuf[9]>>6)|( fpbuf[10]<<2)  );
    }
     return( ( fpbuf[9]>>6)|( fpbuf[10]<<2)  );
 }
/**
 *#ifdef  __AVR_ATmega2560__
 *#define mclock _BV(1)
 *#define mdata _BV(2)
 *#else
 *#define mclock _BV(5)
 *#define mdata _BV(3)
 *#endif

 */
 
  char writekey(uchar datum){
    uint a;
    volatile uchar b,c;
     SPCR=0; 
 keysendcount=0;
    DDRB|=mclock+mdata;//32+mdata/*8*/;  //32 clock  8 data
    PORTB=mclock;//8;  // clock low
    c=1; // odd parity calc
    for(b=0;b<8;b++)if(datum&_BV(b))c++; 
    PORTB=0;
    for(a=0;a<10;a++);
    PORTB=mclock;//32;
    DDRB=mdata/*8*/;
      a=8000;
    while(PINB&mclock/*32*/)if(!a--)return(1); // wait for clock
    if( TIFR2&(_BV(OCF2A)+_BV(TOV2))) { // line wrap?
TIFR2=_BV(OCF2A)+_BV(TOV2); //clear int and inc count  to suppress glitches 
LineCount++;
PORTD|=_BV(2);
}
if(TCNT2>15)PORTD&=~_BV(2);
 while(!(PINB&mclock/*32*/))if(!a--)return(2); // wait for end of clock

    for(b=0;b<8;b++){
      if(datum&_BV(b))PORTB=mdata/*8*/;
      else PORTB=0;
      a=1000;
      while(PINB&mclock/*32*/)if(!a--)return(mclock/*32*/+b); // wait for clock
 if( TIFR2&(_BV(OCF2A)+_BV(TOV2))) { // line wrap?
TIFR2=_BV(OCF2A)+_BV(TOV2); //clear int and inc count  to suppress glitches 
LineCount++;
PORTD|=_BV(2);
}
if(TCNT2>15)PORTD&=~_BV(2);

     while(!(PINB&mclock/*32*/))if(!a--)return(mclock/*32*/+b); // wait for end of clock
 }
    if(c&_BV(0))PORTB=mdata/*8*/; 
    else PORTB=0;
    a=1000;
    while(PINB&mclock/*32*/)if(!a--)return(10); // wait for clock
 if( TIFR2&(_BV(OCF2A)+_BV(TOV2))) { // line wrap?
TIFR2=_BV(OCF2A)+_BV(TOV2); //clear int and inc count  to suppress glitches 
LineCount++;
PORTD|=_BV(2);
}
if(TCNT2>15)PORTD&=~_BV(2);

   while(!(PINB&mclock/*32*/))if(!a--)return(10); // wait for end of clock
     PORTB=mdata/*8*/;
    a=1000;
    while(PINB&mclock/*32*/)if(!a--)return(11); // wait for clock
 if( TIFR2&(_BV(OCF2A)+_BV(TOV2))) { // line wrap?
TIFR2=_BV(OCF2A)+_BV(TOV2); //clear int and inc count  to suppress glitches 
LineCount++;
PORTD|=_BV(2);
}
if(TCNT2>15)PORTD&=~_BV(2);

   while(!(PINB&mclock/*32*/))if(!a--)return(11); // wait for end of clock
  #ifdef  __AVR_ATmega2560__
   DDRB=_BV(0)+_BV(7);
#else
   DDRB=_BV(0);
#endif
   fpcount=0;
    fpin=0;
    fpout=0;
    SPCR=_BV(SPE)+_BV(DORD)+_BV(CPOL);
     return(0);
  }
char write2key(uchar datum){
      cli();
    SPCR=0; 
    datum=raw2key(datum); 
    DDRB=_BV(0);
  #ifdef  __AVR_ATmega2560__
    DDRB=_BV(0)+_BV(7);
#else
   DDRB=_BV(0);
#endif
  fpcount=0;
    fpin=0;
    fpout=0;
    SPCR=_BV(SPE)+_BV(DORD)+_BV(CPOL);
  LineCount+=12;
  sei();
    return(datum);
  }
 char raw2key(uchar datum){
    uint a;
    volatile uchar b,c;
    DDRB|=mclock/*32*/+mdata/*8*/;  //32 clock  8 data
    PORTB=mdata/*8*/;  // clock low
    c=1; // odd parity calc
    for(b=0;b<8;b++)if(datum&_BV(b))c++; 
    PORTB=0;
    for(a=0;a<10;a++);
    PORTB=mclock/*32*/;
    DDRB=mdata/*8*/;
    a=8000;
    while(PINB&mclock/*32*/)if(!a--)return(1); // wait for clock
    while(!(PINB&mclock/*32*/))if(!a--)return(2); // wait for end of clock

    for(b=0;b<8;b++){
      if(datum&_BV(b))PORTB=mdata/*8*/;
      else PORTB=0;
      a=1000;
      while(PINB&mclock/*32*/)if(!a--)return(mclock/*32*/+b); // wait for clock
      while(!(PINB&mclock/*32*/))if(!a--)return(mclock/*32*/+b); // wait for end of clock
    }

    // bit 9 parity 
    if(c&_BV(0))PORTB=mdata/*8*/; 
    else PORTB=0;
    a=1000;
    while(PINB&mclock/*32*/)if(!a--)return(10); // wait for clock
    while(!(PINB&mclock/*32*/))if(!a--)return(10); // wait for end of clock
    // bit 10 stop bit
    PORTB=mdata/*8*/;
    a=1000;
    while(PINB&mclock/*32*/)if(!a--)return(11); // wait for clock
    while(!(PINB&mclock/*32*/))if(!a--)return(11); // wait for end of clock
    return(0);
  }

  char leds(char l){ 
  #ifdef NOKEYLEDS
  return(1);
#else
     volatile int a=3000;
    if(!write2key(0xed)){
      while(a--);  // some responce time
     return( write2key(l&7));
   }
    return(98);
#endif 
 }
  char keyrate(char l){
    volatile uint a=3000;
    if(!write2key(0xf3)){
      while(a--);  // some responce time
      return(write2key(l));
    }
    return(1);
  }
char EnableDataReporting(){ return(write2key(0xF4)); } // Let mouse talk
char SetRemoteMode(){ return(write2key(0xF0)); } // report only when asked
char SetStreamMode(){ return(write2key(0xEA)); } // report as needed
char  ReadData(){ return(write2key(0xEB)); }  // ask for report

  #ifdef translatekeys
 void updateleds(){
    char a=0;
    if(fjin&key_sftlock)a+=4;   
    if (fjin&key_numlock)a+=2;
    leds(a);
  }
  #endif
#endif

} 
;


extern   MasteRasterExtendedTransmissionVision_Stereo_Gop_PS2_2400n81 Video;
// these need to be after structure definition.
#ifdef haveaudio
extern volatile uchar arcount,alcount;
//setaudio sets from banks of sounds[]
#define setaudior(x,y) ({ Video.audiodatar= (const unsigned char*)pgm_read_word(&(sounds[x]));arcount=y;})
#define setaudiol(x,y) ({ Video.audiodata= (const unsigned char*)pgm_read_word(&(sounds[x]));alcount=y;})
#define setaudio(x,y) ({Video.audiodata= (const unsigned char*)pgm_read_word(&(sounds[x]));alcount=y;})

//sample plays the specified sound sample.
#define ssampler(x,y) ({ Video.audiodatar= (const unsigned char*)x;arcount=y;})
#define ssamplel(x,y) ({ Video.audiodata= (const unsigned char*)x;alcount=y;})
#define ssample(x,y) ({Video.audiodata= (const unsigned char*)x;alcount=y;})
#else

// prevent errors with empty defines
#define setaudior(x,y) 
#define setaudiol(x,y)
#define ssampler(x,y) 
#define ssamplel(x,y) 
#define ssample(x,y) 

#endif


#define gop_middleout for(a=0;a<50;a++){Video.MasterRaster[a]=Video.MasterRaster[a+10];Video.MasterRaster[110-a]=Video.MasterRaster[100-a];}
#define gop_bottomup {char a;for(a=0;a<100;a++)Video.MasterRaster[a]=Video.MasterRaster[a+10];}
#define gop_topdowm {char a;for(a=0;a<100;a++)Video.MasterRaster[110-a]=Video.MasterRaster[100-a];}
#define gop_outsidesin for(a=50;a>0;a--){Video.MasterRaster[a+10]=Video.MasterRaster[a];Video.MasterRaster[100-a]=Video.MasterRaster[110-a];}

#define gop_rightleft {char a, b,c;for(a=0;a<11;a++){c=Video.MasterRaster[a*10];for(b=0;b<9;b++)Video.MasterRaster[(a*10)+b]=Video.MasterRaster[(a*10)+b+1];Video.MasterRaster[(a*10)+b]=c;}}

#define gop_leftright {char a, b,c;for(a=0;a<11;a++){c=Video.MasterRaster[(a*10)+9];for(b=9;b>0;b--)Video.MasterRaster[(a*10)+b]=Video.MasterRaster[(a*10)+b-1];Video.MasterRaster[(a*10)+b]=c;}}


// USE THIS MACRO FOR FIXXED STRINGS  it saves memory RAM

//#define screen_progstr(line,col,x) Screen.putprogstr(line,col,PSTR(x))
//#define screenprogstr(x) Screen.putprogstr(PSTR(x))
#define Screen_progstr(line,col,x) Screen.putprogstr(line,col,PSTR(x))
#define Screenprogstr(x) Screen.putprogstr(PSTR(x))


#define rp_OutOfBounds _BV(0)

class RasterPort {
public:
union {// current screen location
uint curloc;
volatile uchar * poke;
} ;

uint end; // limit of screen
uchar esc,flags; // not much for now
char width; // calculation width, gop can make the real width dynamic

void set(uchar rows, uchar cols){  // store our params
width =cols;
poke=Video.MasterRaster;
end=(uint)Video.MasterRaster+(rows*cols);
esc=0;}

void begin(const unsigned char* CharBase,volatile uchar * textbuf,uchar lines, uchar cols,uchar top,uchar left,uchar mode)
{
Video.begin(CharBase,textbuf,lines, cols,top,left,mode);
set(lines/8,cols);
}
void begin(const unsigned char* CharBase,char * textbuf,uchar lines, uchar cols,uchar top,uchar left,uchar mode){
 begin( CharBase,(volatile uchar *) textbuf,lines,  cols,top, left, mode);
}

void setcurloc(uint loc){  //  set absolute location
 curloc=loc;
 lbound(); // just in case
ubound(); // just in case
 }
 
uint setcurloc(uchar line, uint col){  //  line col to location
 curloc=col+(line* width)+(uint)Video.MasterRaster;
lbound(); // just in case
ubound(); // just in case
return(curloc);
 }
 
uint skip(char sk){  //  advance and return position.
int t;
if(sk){
 t=curloc;
t+=sk;
curloc=(uint)t;
 ubound(); 
 }
 return(curloc);
 }
 
void write(uchar a){
 *poke++=a; // place it
ubound();
}

void write(uchar line, uint col, uchar c) {  // locate and place
  setcurloc(line, col);
write(c);
}

void lbound(){ // backwards seldome
while(poke<Video.MasterRaster){curloc+=width;flags&=rp_OutOfBounds;}
}

void ubound(){ 
while(curloc>=end){
curloc-=width;
flags&=rp_OutOfBounds;
#ifdef screenscrools
scroll();
#endif
}
}
void bound(){ // put  a ring on it
lbound();
ubound();
}

void scroll(){
volatile uchar * a;
for (a=Video.MasterRaster;((uint)a)<(end-width);a++)*a=*(a+width); // move all up 1 line
for (;((uint)a)<end;a++)*a=32; // and clear
}
void scrollline2(uchar line){
uchar a;
setcurloc(line,0); //locate
 for(a=0;a<(width-1);a++)
 {
 *poke=*(poke+1);
 poke++;//move
 }
 *poke='.';
}

void scrollline(uchar line,uchar dir){
uchar a;
 if(dir){
setcurloc(line,width-1); //locate
 for(a=(width-1);a>0;a--)
 {
 *poke=*(poke-1);
 poke++;//move
 }
}
else{
setcurloc(line,0); //locate
 for(a=0;a<(width-1);a++)
 {
 *poke=*(poke+1);
 poke++;//move
 }
 }
}

void scrolllineleft(uchar line){
uchar a;
 setcurloc(line,0); //locate
 for(a=0;a<(width-1);a++)
 {
 *poke=*(poke+1);
 poke++;//move
 }
 }

void scrolllineright(uchar line){
uchar a;
 setcurloc(line,width-1); //locate
 for(a=(width-1);a>0;a--)
 {
 *poke=*(poke-1);
 poke--;//move
 }
}

void putprogstr(uchar line, uint col,const char *str){ //place PROGRAM string ,funny name because of 'screen_progstr' macro
setcurloc(line,col); //locate
putprogstr( str);
}

void putprogstr(const char *str){ //place PROGRAM string ,funny name because of 'screen_progstr' macro
  uchar in;
while( (in=pgm_read_byte(str++)))write(in); //get , check, place
}

void progcharl(const unsigned char *str,uchar len){ //place PROGRAM string ,funny name because of 'screen_progstr' macro
 while(len--)write(pgm_read_byte(str++)); //check, get , place
}
void progcharl(uchar line, uint col,const unsigned char *str,uchar len){ //place PROGRAM string ,funny name because of 'screen_progstr' macro
 setcurloc(line,col); //locate
progcharl(str,len);
}

void str(unsigned char* c) {
  while(*c) write((uchar)*c++); //check, place
}


void str(uchar line, uint col, unsigned char* c) {
setcurloc(line,col); //locate
  str(c); //place
}


void hex(uchar c)
{
  uchar h;
   h= c>>4;
  if(h<10)h=h+'0';
  else h=h+'A'-10;
  write(h);
 h= c&15;
  if(h<10)h=h+'0';
  else h=h+'A'-10;
  write(h);
}

void hex(uchar line, uint col,uchar c)
{
setcurloc(line,col); //locate
 hex(c);
}

void hexint(uint i)
{
  hex(i>>8);
  hex(i&0xff);
  }
void hexint(uchar line, uint col,uint i)
{
setcurloc(line,col); //locate
 hexint(i);
}
/*
char *  udec(uchar line, uint col,uint d)
{
char *t;
str(t=udec( line,  col, d));
return(t);
}
*/
// return pointer to str 
unsigned char *  udec(uchar line, uint col,uint d) // return pointer to str 
{
setcurloc(line,col); //locate
 return(udec(d));
}

unsigned char *  udec(uint d)
{
unsigned char *t;
str(t=qudec(  d));
return(t);
}

unsigned char * qudec(uint d) // return pointer to str since we have it.
{
uchar a=10;
 strtemp[11]=0;
do{strtemp[a--]=d%10+'0';d/=10;}while(d);
 // str(&strtemp[++a]);
  return(&strtemp[++a]);
  }
  
unsigned char *  dec(uchar line, uint col,int d) // place and return pointer to str 
{
setcurloc(line,col); //locate
 return(dec(d));
}

unsigned char *  dec(uint d)
{
unsigned char *t;
str(t=qdec( d));
return(t);
}

unsigned char * qdec(int d) // return pointer to str since we have it.
{
uchar a=10,sign=0;
if(d<0) {sign=1;d*=-1;}   // repeat ourselves so we can return string.
 strtemp[11]=0;
do {strtemp[a--]=d%10+'0';d/=10;}while(d);
  if(sign)strtemp[a--]='-';
  //str(&strtemp[++a]);
  return(&strtemp[++a]);
  }


unsigned char *  bin(uchar b)
{
unsigned char *t;
str(t=qbin(  b));
return(t);
}

unsigned char * qbin(uchar b) // return pointer to str since we have it.
{
uchar a;
for (a=0;a<8;a++)strtemp[a]=(b&_BV(7-a)?'1':'0');
 strtemp[a]=0;
   //str(strtemp);
   return(strtemp);
  }

unsigned char *  bin(uchar line, uint col,uchar d) // return pointer to str 
{
setcurloc(line,col); //locate
 return(bin(d));
}

uchar get(uchar line, uint col) {
 uchar * peek;
peek=(uchar*)(col+(line* width)+(uint)Video.MasterRaster);
 return( *peek);
}

uchar get() { // get character at current location  and advance current location.
 uchar  peek;
peek=*poke++;
ubound();
 return( peek);
}

void fill(uchar b,int count){ // set characters, do not change cur loc if count is negative
int t;
if(count<0){t=curloc;count*=-1;}
else t=-1;
while(count--)write(b);
if(t>=0)
curloc=t;
}


void fill(uchar line, uint col,uchar b,int count){ // set location ,set characters, do not change cur loc if count is negative
setcurloc( line,  col);
fill(b,count);
}


void fill(uchar c)
{
poke=Video.MasterRaster;
while((uint)poke<end)*poke++=c;
poke=Video.MasterRaster;
}

void fillrow(uchar line,uchar c)
{char a;
 setcurloc(line,0); //locate
for (a=0;a<width;a++)write(c); 
 }
 
void fillcol(uint col,uchar c)
{
char a,height;
height=(end-(uint)Video.MasterRaster)/width;
for (a=0;a<height;a++)write(a,col,c); 
}

void rect(uchar row,uint col, uchar wi, uchar hi,char c)
{
  uchar a,b;
  for(a=row;a<row+hi;a++)
    for(b=col;b<col+wi;b++)
      write(a,b,c);
}

void frame(uchar row,uint col, uchar wi, uchar hi,char c)
{
  uchar a;
  for(a=row;a<(row+hi);a++){
    write(a,col,c);
    write(a,col+wi-1,c);
  }
    for(a=col;a<(wi+col);a++){
    write(row,a,c);
    write(row+hi-1,a,c);
  }
}

uchar upper(uchar a){
if((a>='a')&&(a<='z')) return(a+'A'-'a');
return(a);
}

uchar lower(uchar a){
if((a>='A')&&(a<='Z') )return(a+'a'-'A');
return(a);
}

void render(uchar a){
  int b;
   if(!esc)if(a==0x1b){
  esc=1; // first char of an esc seq
    return; 
  } 
  if(esc==1){
    esc++; // 2 =checking second...
    if(a!=0x5b){  // fail to be an full esc seq
render(0x1b); // hmmm could be a /t /r /n  ect...
      esc=0;
    }
    else {
    return;
    } // 3 = 2 chars of esc seq.. 
  }
 if(esc==2){
 switch (a){ 
        case 0x41:      
         curloc-=width;
lbound();      
        break;
        case 0x42:      
               curloc+=width;  
ubound();    
    break;
        case 0x43:       
         curloc++;  
ubound();    
          break; 
        case 0x44:      
        curloc--;
lbound();      
          break;
}
esc=0;
//  write('0');
return;
 }

  if(a<32){
    switch (a){ 
    case 13://carrage return
	curloc-=(uint)Video.MasterRaster; //offset into screen 
      curloc=(curloc/ width)* width; //start of line
    curloc+=(uint)Video.MasterRaster; // back to normal
      break;
    case 10:  //linefeed
      curloc=curloc+ width;
     ubound();
      break;
    case  8: //backspace
      if(curloc>0){
        curloc--;
		lbound();
        }
      break;
    case  9: //tab
	curloc-=(uint)Video.MasterRaster; //offset into screen 
   b=curloc%width;// collum
     b=((b/5)+1)*5; // next tab(5)
       curloc=b+((curloc/width)*width)+(uint)Video.MasterRaster;
      break;
    default:
      write(a);
    }

  }
  else if(a<126) write(a);
  else{
  }
  }

#ifdef countframes
unsigned char * time(uchar line, uint col) // 12 hr +am pm ... must be zeroed ever 24 hrs not done here....
{
setcurloc(line,col); //locate
return(time());
}
unsigned char * time() // 12 hr +am pm ... must be zeroed ever 24 hrs not done here....
{
unsigned char *t;
str(t=qtime());
return(t);
}
unsigned char * qtime()  // 12 hr +am pm ... must be zeroed ever 24 hrs not done here....
{
  uchar tmp,pm=0;
  uint clock;
  double clocks;
   clocks=Video.FrameHigh;
  clocks*=65536.0;
  clocks+=Video.FrameCount;  //2 ints to float for the weird timming
  tmp=fmod(clocks,(59.1856))/.591856; // 100ths of a sec
     strtemp[9]=(tmp/10)+'0';
  strtemp[10]=(tmp%10)+'0';
  strtemp[11]=0;

 clocks=(clocks-fmod(clocks,59.1856)+1)/(59.1856); //secs
if(clocks>12.0*60.0*60.00*59.1856) {clocks-=12.0*60.0*60.00*59.1856; pm=1;} // PM
clock=clocks; // uint for intiger math
tmp=(clock%60); // secs
strtemp[6]=(tmp/10)+'0';
  strtemp[7]=(tmp%10)+'0';
  strtemp[8]=':';

 clock=clock/60; 
tmp=(clock%60);//mins
  strtemp[3]=(tmp/10)+'0';
  strtemp[4]=(tmp%10)+'0';
  strtemp[5]=':';

  clock=clock/60;
  tmp=clock+(pm*12);// hrs
   strtemp[0]=(tmp/10)+'0';
  strtemp[1]=(tmp%10)+'0';
  strtemp[2]=':';
   return(strtemp);
}

#endif

};

extern RasterPort Screen;

 #endif

