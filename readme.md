# Eater One

Extensions to the Ben Eaters C6502 Breadboard to add a Keyboard and Display.

ROM includes Wozmon by Steve Wozniak, TinyBasic by Tom Pittman and MS Basic by Bill Gates.

RAM has been expanded to support 31K.

The Keyboard is using an Arduino ATMega328p chip and PS2Advanced library to connect a PS2 compatible keyboard.  The keyboard software can be changed to support other keyboards instead of US.

The Display is using an Arduino ATMega328p chip and TVOut library to composite video to a monitor.  It supports 21 x 12 characters.

The Serial Interface is an Arduino Nano to provide access to the keyboard so you can upload programs into memory.

## WozMon

This is the original 256 bytes Woz Monitor application used on the Apple 1.  It has been slightly modified (and now larger than 256b) to use the Keyboard and Display hardware but same code and functionality.  This is loaded on reset.

Here is a guide on how to use it: [WozMon Guide](https://www.sbprojects.net/projects/apple1/wozmon.php)

## TinyBasic

To run tinybasic from WozMon, type `9000 R`

You can find the user manual for TinyBasic here: [TinyBasic User Manual](http://www.ittybittycomputers.com/IttyBitty/TinyBasic/TBuserMan.htm)

## MS Basic

To run Microsoft Basic from Bill Gates, type `A000 R`

This will run the OSI 6502 BASIC Version 1.0 REV 3.2 from 1977

This doesn't support any graphics.  It's similar to the Apple 1.  Sample games are included in the `examples` folder that were grabbed from Jeff Tanter's repository.

## Upload Utility

A python script can be used to upload programs into memory using the Arduino Nano.  You can upload both Assembly Code to WozMon or Basic code to TinyBasic.   Example applications are provided.

## Hardware Modifications

the following hardare modifications were made to Ben Eaters Breadboard.

Remove the IRQ interrupt wire from the C6522 to C6502.  We will poll the interrupt flag and reset it manually in the code, instead of leverage the Interrupt Vectors for both the Keyboard and Display.

Add a new 74LS08 Quad AND gate chip to expand the memory from 16k to 31k.  The Address for the C6522 was moved from $6000 to $7C00.  AND the address pins 10 and 11.  AND the address pins 12 and 13.  Then AND the outputs of these together and connect this to CS1 of the C6522 chip.

This will detect when the address is $7CXX range and enable the controller.

0111 | 11xx | xxxx | xxxx
 7   |  C   |  X   |  X

Remove the RAM Output Enable (OEb) connection to Address Pin 14 and connect it to Ground.  This removes the original restriction on memory to 16k at address MAX of $4000.  Because of the original design with enabling the RAM chip only on clock enabled, this seems to prevent any conflicts with the C6522 chip.

Add 2 ATMega328p chips and connect the 8 input lines to one and 8 output lines to the other.  All communication is using ASCII.  Also, another pin is used to trigger an interrupt on the C6522 to inform when a key was pressed or the display is ready.

Add an Arduino Nano and connect the pins D2 and D3 to the Keyboard Arduino pins D11 and D12.  This leverages SoftSerial library to deliver ascii from a laptop/desktop computer through the Nano, and to the keyboard.  It acts as if it was typing on the keyboard.

You will find the 3 arduino projects for display, keyboard and io in the `arduino` folder.  You will need to burn these to the 2 chips for the keyboard and display.  The io sketch should be uploaded to the Arduino Nano.




