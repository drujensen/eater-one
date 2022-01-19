// MasteRasterExtendedTransmissionVision 2 2015 11 16 WHMP
// Read Me for instalation and software interface

// version two is updated for Arduino 1.6.6

Instalation

Close ALL Arduino windows
Copy the MRETV folder to Arduino\libraries
Copy the MRETV-examples folder to Arduino\examples

About MrEtv.extensions

MRETV uses the special file 'Arduino\libraries\MRETV\MRETVextensions.h' to coordinate optimization 
between the MRETV library and your sketch. The 'default_extensions' are used to compile some of 
the MRETV examples like 'SoftwareInterfaceExample' , others require you to simply uncomment 
the example sketch name you wish to compile (and comment out default_extensions.) You compile your 
own sketches the same way using the 'default_extensions' or the 'mysketch' prototype provided.

************** Note for the INSTRUCTABLE. ****************

For the SoftwareInterfaceExample and HelloWorld sketches use '#define default_extensions' in MRETV.extensions.
You do not need to read any further right now, you can go back to the Instructable.

// ********* MRETV SOFTWARE INTERFACE ********

This is it for a programming manual sofar, if you are programming with MRETV contact me with questions at 
MrE@telus.net with MRETV in the subject line. 

**** The Basics ****
 
MRETV uses a Video object and possibly a Screen object. They come from including the 'MRETV.h' .

The Video object deals with signal generation and extensions and is always available.
The Screen object handles text functions and is available after Screen.begin() .

After using Screen.begin() to start video output, see below, you place information onto the screen.
Some of that information is usualy text in the form of strings. Default behaviour is for preset strings
to use RAM (and program memory) so alot of strings use up alot of RAM. Use these two macros to stop 
preset strings from using RAM. Note the two different names. 

Screen_progstr(line,col,string)  // put preset string on screen at a location
Screenprogstr(string)  // put preset string on screen at curent location
usage:  screen_progstr(0,0,"Hello World "); 
        screenprogstr("I eat therefore I am");

The Screen object displays other types of information as well.

Screen.dec(uchar line, uint col,int d) // put a decimal number on screen 
Screen.hex(uchar c) //  put a decimal number on screen 
Screen.str(char* c)   // put a standard RAM string on screen.
Screen.str(line,col,string)  // most output functions have two versions

That covers all you really need to know to display data.


****  Screen functions ****

//If you do not need to use Screen.functions using Video.begin() instead saves a few bytes. 
// Create a screen and start video output
void Screen.begin(const unsigned char* CharBase,volatile uchar * textbuf,uchar lines, uchar cols,uchar top,uchar left,uchar mode)

parameters:
	CharBase - a pointer to the character shape data in program memory
	textbuf - a pointer to a RAM array of characters to display. Textbuf must be 
cols x ( lines /( fontheight x pixelheight) ) bytes in size. Almost always 
pixelheight is 1 and font height is 8 so the textbuf size = cols x lines / 8. 
    lines - total scan lines to display
	cols - total columns to display (each column = 8 pixels)
	top - scan line to start display
	left - pixel count to start display
	mode - pixel size ( bits 0-4 height 5-7 width ) 0 height is experimental interlace.

// display functions
Screen_progstr(line,col,string)  // put preset string on screen at a location
Screenprogstr(string)  // put preset string on screen at curent location
void Screen.write(uchar a)   // place a character in the current location and  advance location
void Screen.write(uchar line, uint col, uchar c)    // set location then write() character
void Screen.render(uchar a) //place character even non printable. (big function I need help with)
void Screen.str(char* c)  
void Screen.str(uchar line, uint col, char* c)  
void Screen.hex(uchar c)
void Screen.hex(uchar line, uint col,uchar c)
void Screen.hexint(uint i)
void Screen.hexint(uchar line, uint col,uint i)
char * Screen.udec(uchar line, uint col,uint d) // return pointer to str 
char * Screen.udec(uint d) // return pointer to str since we have it.
char * Screen.dec(uchar line, uint col,int d) // return pointer to str 
char * Screen.dec(int d) // return pointer to str since we have it.
char * Screen.bin(uchar b) // return pointer to str since we have it.
char * Screen.bin(uchar line, uint col,uchar d) // return pointer to str 

//clear a feild before over printing 
void Screen.fill(uchar c) // fill the screen
void Screen.fill(uchar b,int count)  // set characters, do not change current location if count is negative
void Screen.fill(uchar line, uint col,uchar b,int count)  // set location ,set characters, do not change cur loc 
again if count is negative

//shape functions
void Screen.fillrow(uchar line,uchar c) // fill a row
void Screen.fillcol(uint col,uchar c)   // fill a column
void Screen.rect(uchar row,uint col, uchar wi, uchar hi,char c)
void Screen.frame(uchar row,uint col, uchar wi, uchar hi,char c)

// screen utility functions
void Screen.setcurloc(uint loc)   //  set absolute location
uint Screen.setcurloc(uchar line, uint col)   //  line col to location
uint Screen.skip(char sk)   //  advance and return position.
void Screen.bound()  // put curloc on screen
void Screen.scroll() // move screen up 1 text line
uchar Screen.get()   // get character at current location  and advance current location.
uchar Screen.get(uchar line, uint col) // set current location and return the character there, no advance
uchar Screen.upper(uchar a)  //make uppercase
uchar Screen.lower(uchar a) //make uower case
char * Screen.time()  // 12 hr +am pm ... must be zeroed ever 24 hrs not done here....
void Screen.set(uchar rows, uchar cols)   // change our params, These are set by Screen.begin(  so this function is seldom used.

// strings from program memory NOT created with Screen_progstr / Screenprogstr
void Screen.putprogstr(uchar line, uint col, char *str)  //place PROGRAM string ,funny name because of 'screen_progstr' macro
void Screen.putprogstr(char *str)  //place PROGRAM string ,funny name because of 'screen_progstr' macro

//formating for other output
char * Screen.qtime()  // return pointer to str, do not put on screen
char * Screen.qudec(int d) // return pointer to str, do not put on screen
char * Screen.qdec(int d) // return pointer to str, do not put on screen
char * Screen.qbin(int d) // return pointer to str, do not put on screen

**** Screen properties ****

uchar * Screen.poke; // pointer to curloc
uint Screen.curloc;  // current location cast as an intiger
uint Screen.end; // limit of screen cast as an intiger
char Screen.width; // calculated width from begin(), the real width may be dynamic

Note the two forms used in order to overload the function. Both save Ram by putting strings
only in program memory. It you do not use them text will use alot of RAM.

 screen_progstr(line,col,string) 
 screenprogstr(string) 

usage:  screen_progstr(0,0,"Hello World "); 
        screenprogstr("I eat therefore I am");

**** Video functions **** 

// To use Screen.functions you must use Screen.begin() instead, (the Video.functions work in both cases)
// Start video output , Video.begin() saves a few bytes
void Video.begin(const unsigned char * CharBase,volatile uchar * textbuf,uchar lines, uchar cols, uchar top, uchar left, uchar mode)

parameters:
	CharBase - a pointer to the character shape data in program memory
	textbuf - a pointer to an array of characters to display. Textbuf must be 
cols x ( lines /( fontheight x pixelheight) ) bytes in size. Almost always 
pixelheight is 1 and font height is 8 so the textbuf size = cols x lines / 8. 
    lines - total scan lines to display
	cols - total columns to display (each column = 8 pixels)
	top - scan line to start display
	left - pixel count to start display
	mode - pixel size ( bits 0-4 height 5-7 width ) 0 height is experimental interlace.

void off(); // stop all MRETV activity and CPU use
void on();  // restart MRETV , only after an off()

// software serial port functions 2400 8 N 1 
char Video.readS()   // read from serial buffer 
void Video.writeS(char a)  // write out serial 
void Video.stringS(const char * b) // write out serial 

//keyboard functions
char Video.readK()   // read from key buffer
uchar Video.read()  //filtered  read (shaken but not not stirred) from keyboard stream
char Video.write2key(uchar datum)  // write out on the PS/2 port
char Video.leds(char l)   // bits 0 1 2
char Video.keyrate(char l)   // as per ps/2 keyboard specs

// mouse functions
char Video.EnableDataReporting()// Let mouse talk
char Video.SetRemoteMode()// report only when asked
char Video.SetStreamMode() // report as needed
char Video.ReadData()  // ask for report

// special utility functions for PORTD
void Video.bitsetPORTD(uchar bits)  // portd is heavily used by MRETV so only write to it using these routines
void Video.bitclearPORTD(uchar bits)// reads can be done normaly

**** Video properties ****

uint Video.LineCount;  // raster line on screen currently being drawn
uchar Video.ScreenWidth,.ScreenTop,.ScreenBottom, .ScreenCenter; // active screen area
uchar Video.ScreenMode; // pixel size ( bits 0-4 height 5-7 width ) 0 height is experimental interlace.
uint Video.FrameCount, Video.FrameHigh;  // if extension selected frame=262 rasterlines = painting one screen
const unsigned char *Video.audiodatar,*Video.audiodata;
uchar Video.speckey,Video.fjin;
uchar Video.f2jin; 
uchar Video.arcount, Video.alcount

(hardware register) UBRR0  //is realtime pixel width 


MRETV defines

// USE THIS MACRO FOR FIXXED STRINGS  it saves memory RAM

#define screen_progstr(line,col,string) 
#define screenprogstr(string) 

//  Sound, For optimum auditory excitation use SLUG SOUND ENHANCERS

//play from array of samples        sounds[];
#define setaudior(sound index,duration) 
#define setaudiol(sound index,duration) 
#define setaudio(sound index,duration) 
//plays the specified sound sample.
#define ssampler(sample,duration) 
#define ssamplel(sample,duration) 
#define ssample(sample,duration) 


#define ADC_START  // enable+ set best clock+ start
#define ADC_11V // internal 1.1 v ref
#define ADC_5V _ //VCC as ref

//Key defines - true means down

#define key_lwin 
#define key_rwin
#define key_lalt 
#define key_ralt 
#define key_lsft 
#define key_rsft 
#define key_lctr 
#define key_rctr 
#define key_sftlock 
#define key_numlock 


#define key_sft 
#define key_alt 
#define key_win 
#define key_ctr 
#define key_nlock 

//Joystick defines

#define rjdown 
#define rjup 
#define rjleft 
#define rjright 
#define rjbutton 
#define rjall 

#define fjdown 
#define fjup 
#define fjleft 
#define fjright 
#define fjbutton 
#define fjall  

#define f2jdown 
#define f2jup 
#define f2jleft 
#define f2jright 
#define f2jbutton 
#define f2jall 

//The virtual graphics processor defines

#define flag_gopcharwidth 
#define flag_gopindex  // set text index . two byte address
#define flag_gopcharset // set char set. two byte progmem address
#define flag_gopscreenwidth 
#define flag_gopcharheight 
#define flag_goptopbottom  // two bytes top bottom
#define flag_gopcenter 
#define flag_gopreset  //  reset graphics operations list. two byte address  (really a jump instruction)

#define gop_int(int) // macro to make 2 byte graphics operations list entry
#define setgoplist(goplist *) // safely set a graphics operations list

************* MasteRasterExtendedTransmissionVision  Extension choices*****************************
 * 
 ***************  define only 1 firmware port configuration or none           ***
 * #define firmwareserialport  // 2400 baud 8n1
 * #define firmwareps2port    //keyboard/mouse port (ps2 serial protocol)
 * #define firmwaremultiport     // both
 * 
 ***************  define only 1  audio type         ***
 * #define noaudio  // no audio, don't need to use it for now 
 * #define interlacedaudio  // 1  stream stereo - fewerclocks but less versatile
 * #define monoaudio   // 1 mono stream
 * #define dualaudio    // 2 stream stereo
 * 
 ************* use any or all *********
 * #define userextension   background() // function to call at screentop-2 and screen bottom +1..KEEP IT SHORT or video can glitch! 
 * #define countframes // used for acurate timming , exposed as  -    volatile uint Video.FrameCount, Video.FrameHigh;
 * #define graphicsengine // used for many menus, special effects, improves overall performance and memory use.
 * #define translatekeys // unless you WANT to deal with raw keyboard data. also you get a virtual joy stick. up/down/right/left/rightshift
 * #define mergstreams // merge ps2 bufer into serial buffer  
 * #define screenscrools //   writes to the last character of a screen can  roll your display automagicaly 
 * #define fakejoy2   //  a second virtual joystick (w/a/s/z/leftshift) - sometimes it takes 2 .
 * 
 ************* the ability to overide some defaults *********
 * #define ADC_SAMPLECOUNT 10  // default 10,  max  64 so we dont ovf
 * #define NOKEYLEDS                //  if leds cause problems, don't use them 
 * #define fontheight 8       // powers of two only. 1 2 4 8 16 32 ... default 8
 * #define noserialsend             // no software serial Tx on pin 3 
 * #define halfrateaudio       // play each sample point twice
 * 
 ***********************************************************/
