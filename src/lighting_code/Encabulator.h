// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Encabulator.h
//
// This is a collection of classes to support the LumiGeek hardware and other 
// sensors on the TurBull Encabulator board
//
// Think of the Encabulator as several Arduino-compatible shields on 
// the same I2C bus on a single circuit board.   
//
// Authors: John Parts Taylor and JoeJoe Martin, March 12, 2013
// ---------------------------------------------------------------------------

#ifndef Encabulator_h
#define Encabulator_h

// #define USE_I2C_REV5_INSTEAD_OF_WIRE	// Comment this out to use the TWI/Wire library

#ifdef USE_I2C_REV5_INSTEAD_OF_WIRE
#include <I2C.h>
#else 
#include <Wire.h>
#endif

#include <Arduino.h>
#include <inttypes.h>
#include "EncabulatorDefines.h"

// ---------------------------------------------------------------------------
// Abstract Class: LumiGeekShield
// ---------------------------------------------------------------------------

class LumiGeekShield
{
	public:
		LumiGeekShield(uint8_t  i2cAddress);
		void blackout();
		void testPattern();
    protected:
        int _i2cAddress;  // NOTE: tried to use uint8_t but got an ambiguous compiler error.  Weird.
};


// ---------------------------------------------------------------------------
// Abstract Class: RGB4XStrip
// Since there are two of this shield on the board, this was left abstract.
// The subclasses get instantiated with their individual i2c addresseses.
// ---------------------------------------------------------------------------

class RGB4XStrip : public LumiGeekShield
{
	public:
		RGB4XStrip(uint8_t addr) : LumiGeekShield(addr) {
			_i2cAddress = addr;
		};
		void jumpHeaderToRGB(uint8_t header, uint8_t r, uint8_t g, uint8_t b);
		void fadeHeaderToRGB(uint8_t header, uint8_t r, uint8_t g, uint8_t b, uint8_t speed);
		void autoJumpHeaderBetweenRGBs(uint8_t header, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed);
		void autoFadeHeaderBetweenRGBs(uint8_t header, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed);
		void autoFadeHeaderToRandomRGBs(uint8_t header, uint8_t speed);
};


// ---------------------------------------------------------------------------
// Class: RGB4XStripA
// For the first 4X shield on the left of the board with headers A1-A4.
// The I2C address is hardcoded into the superclass abstract constructor call.
// ---------------------------------------------------------------------------

class RGB4XStripA : public RGB4XStrip
{
	public:
		RGB4XStripA() : RGB4XStrip(LG_RGB_4X_A) {};
};


// ---------------------------------------------------------------------------
// Class: RGB4XStripB
// For the second 4X shield on the left of the board with headers B1-B4.
// The I2C address is hardcoded into the superclass abstract constructor call.
// ---------------------------------------------------------------------------

class RGB4XStripB : public RGB4XStrip
{
	public:
		RGB4XStripB() : RGB4XStrip(LG_RGB_4X_B) {};
};


// ---------------------------------------------------------------------------
// Class: Addr1XMultiTool
// Used to control various types of Addressable LED products.  See defines file. 
// The I2C address is hardcoded into the abstract superclass constructor call.
// Since this is a 1X board, the header parameter is ommitted from these helper methods
// ---------------------------------------------------------------------------

class Addr1XMultiTool : public LumiGeekShield
{
	public:
		Addr1XMultiTool() : LumiGeekShield(LG_ADDR_1X) {};   
	//	Addr1XMultiTool() : LumiGeekShield(0x54) {};   // THIS IS JUST FOR TESTING ON THE LUMIGEEK HEADLIGHT
	//	Addr1XMultiTool() : LumiGeekShield(0x52) {};   // THIS IS JUST FOR TESTING ON THE LUMIGEEK ADDR1X
		void setMode(uint8_t mode);
		void drawGradient(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t length);
		void drawComet(uint8_t r, uint8_t g, uint8_t b, uint8_t cometLength, uint8_t tailLength, uint8_t speed);
		void drawFrame(uint8_t pixelCount, uint8_t pixelRGBs[]);
		void drawBigFrame(uint16_t pixelCount, uint8_t pixelRGBs[]);
		void shiftBufferOnce(uint8_t direction, uint8_t length);
		void autoShiftBuffer(uint8_t direction, uint8_t length, uint8_t speed);
};


// ---------------------------------------------------------------------------
// Class: DMX1XUniverse
// Used to generate and repeatedly transmit a DMX universe framebuffer.
// The I2C address is hardcoded into the abstract superclass constructor call.
// Since this is a 1X board, the header parameter is ommitted from these helper methods.
// ---------------------------------------------------------------------------

class DMX1XUniverse : public LumiGeekShield
{
	public:
		DMX1XUniverse() : LumiGeekShield(LG_DMX_1X) {};
		void setDataStartingAtAddressWithRGB(uint8_t address, uint8_t r, uint8_t g, uint8_t b);
		void setEntireUniverse(uint8_t universe[]);  // does not work with the Wire library... only with modified I2C Rev5 library
};



// ---------------------------------------------------------------------------
// Class: XYZHelper
// This is a rudiemntary helper class for the KXTI9-1001 accelerometer by Kionix.
// It is initialized with a call to begin().  
// Calling updateValues() will fetch the twos-compliment of the raw x, y,and z values
// This is a very robust accelerometer chip and direct I2C calls can access features
// such as tap-detection and filtering that are not exposed in this simple helper class.
// ---------------------------------------------------------------------------

class XYZHelper
{
    private:
		int16_t _x;
		int16_t _y;
		int16_t _z;
		bool _initialized;
	protected: 
		void writeRegister(uint8_t reg, uint8_t data);
		uint8_t readRegister(uint8_t reg);
		int16_t combineBytes(uint8_t tempLow, uint8_t tempHigh);
	public:
		XYZHelper() {
			_initialized = false;
		};
		void begin();
		void update();
		int16_t x();
		int16_t y();
		int16_t z();
};


// ---------------------------------------------------------------------------
// Class: DACHelper
// Helper class to send a 12-bit value to an MCP4725 DAC by Microchip.  
// The I2C address of the DAC hardcoded into the abstract superclass constructor call.
// ---------------------------------------------------------------------------

class DACHelper
{
	public:
		void write(uint16_t value);
};


// ---------------------------------------------------------------------------
// Class: TemperatureHelper
// Helper class to get a 13-bit temperature value from the ADT7410 by Analog Devices
// The I2C address of the temperature sensor is hardcoded into the abstract superclass constructor call.
// ---------------------------------------------------------------------------

class TemperatureHelper 
{
	public:
		float getFahrenheit();
		float getCelsius();
};


// ---------------------------------------------------------------------------
// Class: EEPROMHelper
// Rudimentary helper class to read and write bytes to persistent memory with the 24LC512 by Microchip.
// There are more advanced libraries and/or sample code for this EEPROM that support pages and more.
// The I2C address of the EEPROM is hardcoded into the abstract superclass constructor call.
// Note that the I2C Rev5 library will not work with this EEPROM because of the 16-bit address incompatibility with the read() call
// However, it does work with the TWI/Wire library.
// ---------------------------------------------------------------------------

class EEPROMHelper
{
	public:
		uint8_t writeAddress(uint16_t address, uint8_t byte);
		uint8_t readAddress(uint16_t address);
};


// ---------------------------------------------------------------------------
// Class: TurBullEncabulator
// One shield to rule them all!!!
// ---------------------------------------------------------------------------

class TurBullEncabulator 
{
	private:
		static bool _verbose;
	public: 
		TurBullEncabulator() {};
		DACHelper dac;
		XYZHelper accelerometer;
		TemperatureHelper temperature;
		EEPROMHelper eeprom;
		
		Addr1XMultiTool addressable;
		DMX1XUniverse dmx;
		RGB4XStripA stripBankA;
		RGB4XStripB stripBankB;		
		
		void upUpDownDownLeftRightLeftRightBA();
		void setVerbose(bool b);
		
		void testPattern();
		void blackout();
};


extern TurBullEncabulator Encabulator;

#endif