#ifndef MrEtv_extensions_
#define MrEtv_extensions_
// MasteRasterExtendedTransmissionVision 2  2015 11 16  WHMP Creative Commons ShareAlike License 3.0
// Configuration file for compile time options for both library and sketch
// beleive the code not the comments whmp

// If you are unfamilar with using '#define' see the note at the end of this file.

// Master Defines for MRETV examples and general use

  #define default_extensions

 //#define TestPattern 
 //#define bounce
 //#define Arudion
 //#define ScreenTool
 //#define Ponguino
 //#define KeyboardTool
 //#define ShootEmUp
 //#define DiodeCalibration
 //#define mirrorchess 
 
 //#define MySketch          // mysketch master define
 
#ifdef MySketch            // mysketch define group 
 #define firmwaremultiport // keyboard and serial
 #define translatekeys     // no raw keyup/down track fake joy stick on arrow keys Rctrl
 #define mergstreams       // add keyboard to serial rx stream 
 #define fontheight 8      // normal fonts 
 #define monoaudio         // sound
//#define countframes      // for timming functions
//#define dualaudio        // stereo
//#define fakejoy2         // track fake joy2 on wasd keys Lctrl 
//#define graphicsengine   // automagic graphics 
#endif

// Default Extensions are a good choice for most sketches
// do not change the defaults, use 'MySketch' above instead
#ifdef default_extensions   
 #define firmwaremultiport
 #define translatekeys 
 #define mergstreams 
 #define fontheight 8  
 #define monoaudio   
 #define screenscrools 
 #warning default ext
#endif


/************* MasteRasterExtendedTransmissionVision  Extension choices*****************************
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
 * 
 * 
 ***********************************************************/

// define groups for MRETV examples

#ifdef Arudion
 #ifdef __AVR_ATmega168__
  #define firmwareps2port  // room for more samples on smaller chip
 #else 
  #define firmwaremultiport
 #endif
  #define dualaudio    
  #define userextension   background()
  #define translatekeys 
  #define mergstreams // ignored on 168
  #define fontheight 4
 #warning MRETV debug info - Arudion extensions used
#endif
 
#ifdef DiodeCalibration
 #define firmwaremultiport
 #define translatekeys 
 #define mergstreams 
 #define userextension   background()
 #define fontheight 8  
 #define graphicsengine
 #define countframes
 #define monoaudio   
 #define ADC_SAMPLECOUNT 50 // sample heavily
#warning MRETV debug info - DiodeCalibration extensions used
#endif

#ifdef ShootEmUp
 #define firmwaremultiport
 #define mergstreams 
 #define dualaudio   
 #define translatekeys 
 #define fontheight 8  
 #define fakejoy2
 #define graphicsengine
 #define countframes
#warning MRETV debug info - ShootEmUp extensions used
#endif
 
#ifdef ScreenTool
 #define firmwaremultiport
 #define mergstreams 
 #define dualaudio   
 #define translatekeys 
 #define fontheight 8  
 #define graphicsengine
 #define countframes
#warning MRETV debug info - ScreenTool extensions used
#endif
 
 
#ifdef KeyboardTool
 #define firmwaremultiport
 #define mergstreams 
 #define userextension   background()
 #define translatekeys 
 #define fontheight 8  
 #define fakejoy2
 #define countframes
#warning MRETV debug info - KeyboardTool extensions used
#endif
 

#ifdef Ponguino
 #define monoaudio   
 #define firmwaremultiport  
 #define mergstreams  
 #define userextension   background()
 #define translatekeys 
 #define fontheight 1  
 #define fakejoy2
 #define ADC_SAMPLECOUNT 1  //fast update
#warning MRETV debug info - Ponguino extensions used
#endif

#ifdef mirrorchess
 #define firmwareps2port    
 #define monoaudio   
 #define userextension   background()
 #define translatekeys 
 #define fontheight 8
 #define countframes
 #define graphicsengine 
#warning MRETV - mirrorchess extensions used
#endif

#ifdef TestPattern
  #define fontheight 16  
 #warning MRETV debug info - TestPattern extensions used
#endif
  
#ifdef bounce
 #define firmwaremultiport    
 #define mergstreams 
 #define translatekeys 
 #define fontheight 4  
#warning MRETV debug info - bounce extensions used
#endif

 #endif // #ifndef MrEtv_extensions_


/*********** ABOUT THE USE OF DEFINES IN MRETV.extensions *******
 * 
 * From a line containing '#define name' the compiler remebers name has been defined.
 * This can be used to decide what parts of the source code to use and what parts to 
 * skip with an #ifdef #endif pair.
 * 
 *   #define twins
 * 
 *   feedkid(1);
 *   #ifdef twins
 *   feedkid(1);
 *   #endif
 * 
 * This is how defines like '#define countframes' are used internaly in MRETV. Defines are 
 * also nested to make groups of defines. 
 * 
 *   //#define rain
 *   #define sun
 * 
 *   #ifdef rain
 *   #define boots
 *   #define coat
 *   #endif
 * 
 *   #ifdef sun
 *   #define sunblock
 *   #endif
 * 
 * This is how the master defines like '#define ScreenTool' are used in this file. For your own sketches
 * use the '#define mysketch'  (and update the group of defines just below it if neccessary.) It  is 
 * suitable for most uses without change. 
 * 
 ******************************************************/
