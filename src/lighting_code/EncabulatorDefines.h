// ----------------------------------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// EncabulatorDefines.h
// A header file containing the I2C addresses and commands for each subsystem on the board.
//
// Think of the TurBull Encabulator as several shields on the same I2C bus on
// a single circuit board.   
//
// Authors: John Parts Taylor and JoeJoe Martin, March 12, 2013
// ----------------------------------------------------------------------------------------------------

#ifndef EncabulatorDefines_h
#define EncabulatorDefines_h

// ----------------------------------------------------------------------------------------------------
// I2C bus addresses in Arduino-friendly 7-bit notation

#define EEPROM 0x50			// 512kbit EEPROM 			24LC512 by Microchip
#define TEMPSENSOR 0x48		// Temperature Sensor 		ADT7410 by Analog Devices
#define DAC 0x62			// 12-bit DAC 				MCP4725 by Microchip
#define XYZ 0x0F			// 3-Axis Acclerometer 		KXTI9-1001 by Kionix
	
#define LG_RGB_4X_A 0x51	// 12V RGB Strip Shield		RGB 4X Shield by LumiGeek
#define LG_RGB_4X_B 0x52	// 12V RGB Strip Shield		RGB 4X Shield by LumiGeek
#define LG_ADDR_1X 0x53		// Addressable  MultiTool  	Addr 1X Shield by LumiGeek
#define LG_DMX_1X 0x54		// DMX Universe Generator	DMX 1X Shield by LumiGeek



// ----------------------------------------------------------------------------------------------------
// LumiGeek Global Commands
// Any of our shields on the TurBull Encabulator respond to these global I2C commands

#define LG_GLOBAL_CMD_BLACKOUT 0xAA
#define LG_GLOBAL_CMD_TEST_PATTERN 0xBB 



// ----------------------------------------------------------------------------------------------------
// LumiGeek 4X RGB Strip Commands 
// There are four headers on each of the two I2C shields on the TurBull Encabulator

// See the comments for the parameters that should be sent immediately after any given command

#define LG_RGB_4X_CMD_JUMP_TO 0x21				// 0x21 Header R G B  
#define LG_RGB_4X_CMD_FADE_TO 0x22				// 0x22 Header R G B Speed

// TODO: Verify these commands with JoeJoe:
 
#define LG_RGB_4X_CMD_AUTO_FADE 0x23			// 0x23 Header R1 G1 B1 R2 G2 B2 Speed
#define LG_RGB_4X_CMD_AUTO_JUMP 0x24			// 0x24 Header R1 G1 B1 R2 G2 B2 Speed
#define LG_RGB_4X_CMD_AUTO_RANDOM 0x25			// 0x25 Header Speed  



// ----------------------------------------------------------------------------------------------------
// LumiGeek 1X Addressable Strip MultiTool Commands
// There is just single header for the addressable shield on the TurBull Encabulator.  
// Always set header = 1 in the I2C commands.

// You can set the type of addressable strip to be driven by this shield.  
// The default is WS2811, used in the strip that arrived with the TurBull Encabulator.
// StripMode: 1 = WS2811  e.g. http://adafruit.com/products/1138
//       	  2 = WS2801  e.g. http://sparkfun.com/products/11272, http://sparkfun.com/products/11020, http://adafruit.com/products/322, http://adafruit.com/products/738
//            3 = LPD8806 e.g. http://adafruit.com/products/306

#define LG_ADDR_1X_CMD_SET_STRIP_MODE 0x58		// 0x58 Header StripMode 

// Here are some generative macros, limited for now to 256 pixels by the length byte

#define LG_ADDR_1X_CMD_GRADIENT 0x51			// 0x51 Header R1 G1 B1 R2 G2 B1 Length 
#define LG_ADDR_1X_CMD_COMET_CHASE 0x55			// 0x55 Header R G B LengthOfComet LengthOfTail Speed 

// Here is how to clock in raw RGB pixel data. Unlike the generative macros, the frame command can handle more than 256 pixels.
// Issues concerning power and voltage drop on long runs of strip will likely crop up before hitting any pixel limit on the I2C bus.
// The strip driver chips themselves may have limitations.  Please see their respective datasheets. (i.e. WS2811 appears to have a 1024 pixel limit)

#define LG_ADDR_1X_CMD_FRAME 0x53				// 0x51 Header R1 G1 B1 ... RN GN BN

// Now that you have pixel data in our 1024 buffer on the shield, you can rotate or autorotate portions of the buffer
// The length of the buffer "wrap around" effect is limited to 256

#define LG_ADDR_1X_CMD_SHIFT_BUFFER_ONCE 0x56	// 0x56 Header Direction(0=left,1=right) BufferLengthForWrap
#define LG_ADDR_1X_CMD_AUTOSHIFT_BUFFER 0x57	// 0x57 Header Direction(0=left,1=right) BufferLengthForWrap Speed



// ----------------------------------------------------------------------------------------------------
// LumiGeek 1X DMX Driver Commands 
// There is just single header for the DMX shield on the Encabulator.  
// Always set header = 1 in the I2C commands.

#define LG_DMX_1X_CMD_SET_BYTES_FROM_ADDR 0x41	// 0x41 Header BaseAddress [R1 G1 B1 ... RN GN BN]
#define LG_DMX_1X_CMD_SET_ENTIRE_UNIVERSE 0x42	// 0x42 Header [512 bytes of DMX data]



// ----------------------------------------------------------------------------------------------------
// "Light is not so much something that reveals, as it is itself the revelation." – James Turrell
// ----------------------------------------------------------------------------------------------------

#endif





