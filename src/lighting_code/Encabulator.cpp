// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Encabulator.cpp
// Classes to support Turbull Encabulator hardware on Arduino
//
// Think of the TurBull Encabulator as several shields on the same I2C bus on
// a single circuit board.   
//
// Authors: John Parts Taylor and JoeJoe Martin, March 12, 2013
// ---------------------------------------------------------------------------

#include "EncabulatorDefines.h"
#include "Encabulator.h"

// ---------------------------------------------------------------------------
// Methods for LumiGeekShield
// Calls the superclass constructor with the appropriate I2C address
// ---------------------------------------------------------------------------

LumiGeekShield::LumiGeekShield(uint8_t i2cAddress) {
	_i2cAddress = i2cAddress;
}

void LumiGeekShield::blackout() {
#ifdef USE_I2C_REV5_INSTEAD_OF_WIRE
	I2c.write(_i2cAddress,LG_GLOBAL_CMD_BLACKOUT);
#else
	Wire.beginTransmission(_i2cAddress);
	Wire.write(LG_GLOBAL_CMD_BLACKOUT);
	Wire.endTransmission();
#endif
	delay(6);
}

void LumiGeekShield::testPattern() {
#ifdef USE_I2C_REV5_INSTEAD_OF_WIRE
	I2c.write(_i2cAddress,LG_GLOBAL_CMD_TEST_PATTERN);
#else
	Wire.beginTransmission(_i2cAddress);
	Wire.write(LG_GLOBAL_CMD_TEST_PATTERN);
	Wire.endTransmission();
#endif
	delay(6);
}

// ---------------------------------------------------------------------------
// Methods for RGB4XStrip
// ---------------------------------------------------------------------------

void RGB4XStrip::jumpHeaderToRGB(uint8_t header, uint8_t r, uint8_t g, uint8_t b) {
	// ASSERT: header >= 1 && header <= 4
#ifdef USE_I2C_REV5_INSTEAD_OF_WIRE
	uint8_t params[4];
	params[0] = header; // hardcode the header number... this is only a 1X addressable shield
	params[1] = r;
	params[2] = g;
	params[3] = b;
	I2c.write(_i2cAddress,LG_RGB_4X_CMD_JUMP_TO,params,5);
#else	
	Wire.beginTransmission(_i2cAddress);
	Wire.write(LG_RGB_4X_CMD_JUMP_TO);
	Wire.write(header);
	Wire.write(r);
	Wire.write(g);
	Wire.write(b);
	Wire.endTransmission();
#endif
    delay(6);
}
		
void RGB4XStrip::fadeHeaderToRGB(uint8_t header, uint8_t r, uint8_t g, uint8_t b, uint8_t speed) {
	// ASSERT: header >= 1 && header <= 4
	// ASSERT: speed is within some range?
#ifdef USE_I2C_REV5_INSTEAD_OF_WIRE
	uint8_t params[5];
	params[0] = header; // hardcode the header number... this is only a 1X addressable shield
	params[1] = r;
	params[2] = g;
	params[3] = b;
	params[4] = speed;
	I2c.write(_i2cAddress,LG_RGB_4X_CMD_FADE_TO,params,5);
#else	
    Wire.beginTransmission(_i2cAddress);
	Wire.write(LG_RGB_4X_CMD_FADE_TO);
	Wire.write(header);
	Wire.write(r);
	Wire.write(g);
	Wire.write(b);
	Wire.write(speed);	
	Wire.endTransmission();
#endif
    delay(6);	
}

void RGB4XStrip::autoJumpHeaderBetweenRGBs(uint8_t header, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed) {
	// ASSERT: header >= 1 && header <= 4
	// ASSERT: speed is within some range?
#ifdef USE_I2C_REV5_INSTEAD_OF_WIRE
	uint8_t params[8];
	params[0] = header; // hardcode the header number... this is only a 1X addressable shield
	params[1] = r1;
	params[2] = g1;
	params[3] = b1;
	params[4] = r2;
	params[5] = g2;
	params[6] = b2;
	params[7] = speed;
	I2c.write(_i2cAddress,LG_RGB_4X_CMD_AUTO_JUMP,params,8);
#else	
	Wire.beginTransmission(_i2cAddress);
	Wire.write(LG_RGB_4X_CMD_AUTO_JUMP);
	Wire.write(header);
	Wire.write(r1);
	Wire.write(g1);
	Wire.write(b1);
	Wire.write(r2);
	Wire.write(g2);
	Wire.write(b2);
	Wire.write(speed);	
	Wire.endTransmission();
#endif
    delay(6);
}

void RGB4XStrip::autoFadeHeaderBetweenRGBs(uint8_t header, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed) {
	// ASSERT: header >= 1 && header <= 4
	// ASSERT: speed is within some range?
#ifdef USE_I2C_REV5_INSTEAD_OF_WIRE
	uint8_t params[8];
	params[0] = header; // hardcode the header number... this is only a 1X addressable shield
	params[1] = r1;
	params[2] = g1;
	params[3] = b1;
	params[4] = r2;
	params[5] = g2;
	params[6] = b2;
	params[7] = speed;
	I2c.write(_i2cAddress,LG_RGB_4X_CMD_AUTO_FADE,params,8);
#else	
	Wire.beginTransmission(_i2cAddress);
	Wire.write(LG_RGB_4X_CMD_AUTO_FADE);
	Wire.write(header);
	Wire.write(r1);
	Wire.write(g1);
	Wire.write(b1);
	Wire.write(r2);
	Wire.write(g2);
	Wire.write(b2);
	Wire.write(speed);	
	Wire.endTransmission();
#endif
    delay(6);
}

void RGB4XStrip::autoFadeHeaderToRandomRGBs(uint8_t header, uint8_t speed) {
	// ASSERT: header >= 1 && header <= 4
	// ASSERT: speed is within some range?
#ifdef USE_I2C_REV5_INSTEAD_OF_WIRE
	uint8_t params[2];
	params[0] = header; // hardcode the header number... this is only a 1X addressable shield
	params[1] = speed;
	I2c.write(_i2cAddress,LG_RGB_4X_CMD_AUTO_RANDOM,params,2);
#else	
	Wire.beginTransmission(_i2cAddress);
	Wire.write(LG_RGB_4X_CMD_AUTO_RANDOM);
	Wire.write(header);
	Wire.write(speed);	
	Wire.endTransmission();
#endif
    delay(6);
}


// ---------------------------------------------------------------------------
// Methods for Addr1XMultiTool
// ---------------------------------------------------------------------------

void Addr1XMultiTool::setMode(uint8_t mode) {
	// ASSERT: more >= 1 && mode <= 3
	// TODO: document that mode = 1 is WS2811, mode = 2 is WS2801, mode = 3 is ???
#ifdef USE_I2C_REV5_INSTEAD_OF_WIRE
	uint8_t params[2];
	params[0] = 1; // hardcode the header number... this is only a 1X addressable shield
	params[1] = mode;
	I2c.write(_i2cAddress,LG_ADDR_1X_CMD_SET_STRIP_MODE,params,2);
#else	
	Wire.beginTransmission(_i2cAddress);
	Wire.write(LG_ADDR_1X_CMD_SET_STRIP_MODE);
	Wire.write(1);  // hardcode the header number... this is only a 1X addressable shield
	Wire.write(mode);	
	Wire.endTransmission();
#endif
    delay(5);
}

void Addr1XMultiTool::drawGradient(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t length) {
#ifdef USE_I2C_REV5_INSTEAD_OF_WIRE
	uint8_t params[8];
	params[0] = 1; // hardcode the header number... this is only a 1X addressable shield
	params[1] = r1;
	params[2] = g1;
	params[3] = b1;
	params[4] = r1;
	params[5] = g2;
	params[6] = b2;
	params[7] = length;
	I2c.write(_i2cAddress,LG_ADDR_1X_CMD_GRADIENT,params,8);
#else	
	Wire.beginTransmission(_i2cAddress);
	Wire.write(LG_ADDR_1X_CMD_GRADIENT);
	Wire.write(1);  // hardcode the header number... this is only a 1X addressable shield
	Wire.write(r1);	
	Wire.write(g1);	
	Wire.write(b1);	
	Wire.write(r2);	
	Wire.write(g2);	
	Wire.write(b2);	
	Wire.write(length);	
	Wire.endTransmission();
#endif
    delay(5);
}

void Addr1XMultiTool::drawComet(uint8_t r, uint8_t g, uint8_t b, uint8_t cometLength, uint8_t tailLength, uint8_t speed) {
#ifdef USE_I2C_REV5_INSTEAD_OF_WIRE
	uint8_t params[7];
	params[0] = 1; // hardcode the header number... this is only a 1X addressable shield
	params[1] = r;
	params[2] = g;
	params[3] = b;
	params[4] = cometLength;
	params[5] = tailLength;
	params[6] = speed;
	I2c.write(_i2cAddress,LG_ADDR_1X_CMD_COMET_CHASE,params,7);
#else	
	Wire.beginTransmission(_i2cAddress);
	Wire.write(LG_ADDR_1X_CMD_COMET_CHASE);
	Wire.write(1);  // hardcode the header number... this is only a 1X addressable shield
	Wire.write(r);	
	Wire.write(g);	
	Wire.write(b);	
	Wire.write(cometLength);	
	Wire.write(tailLength);	
	Wire.write(speed);	
	Wire.endTransmission();
#endif
    delay(5);
}

void Addr1XMultiTool::shiftBufferOnce(uint8_t direction, uint8_t length) {
#ifdef USE_I2C_REV5_INSTEAD_OF_WIRE
	uint8_t params[3];
	params[0] = 1; // hardcode the header number... this is only a 1X addressable shield
	params[1] = direction;
	params[2] = length;
	I2c.write(_i2cAddress,LG_ADDR_1X_CMD_SHIFT_BUFFER_ONCE,params,3);
#else	
	Wire.beginTransmission(_i2cAddress);
	Wire.write(LG_ADDR_1X_CMD_SHIFT_BUFFER_ONCE);
	Wire.write(1);  // hardcode the header number... this is only a 1X addressable shield
	Wire.write(direction);	
	Wire.write(length);
	Wire.endTransmission();
#endif
    delay(5);
}

void Addr1XMultiTool::autoShiftBuffer(uint8_t direction, uint8_t speed, uint8_t length) {	
#ifdef USE_I2C_REV5_INSTEAD_OF_WIRE
	uint8_t params[4];
	params[0] = 1; // hardcode the header number... this is only a 1X addressable shield
	params[1] = direction;
	params[2] = speed;
	params[3] = length;
	I2c.write(_i2cAddress,LG_ADDR_1X_CMD_AUTOSHIFT_BUFFER,params,4); 
#else	
	Wire.beginTransmission(_i2cAddress);
	Wire.write(LG_ADDR_1X_CMD_AUTOSHIFT_BUFFER);
	Wire.write(1);  // hardcode the header number... this is only a 1X addressable shield
	Wire.write(direction);	
	Wire.write(speed);	     // JOEJOE: Remember to swap the length and speed in the headlight and 1X as well.
	Wire.write(length);		
	Wire.endTransmission();
#endif
    delay(5);
}

void Addr1XMultiTool::drawFrame(uint8_t pixelCount, uint8_t pixelRGBs[]) {

    // KNOWN ISSUE: There is an out-of-the-box 32-byte limit on the buffer in the I2C Rev5 library. 
	// This can easily be overridden up to a maximum 256 bytes (85 pixels) by editing the MAX_BUFFER_SIZE.
	// Note that this cannot be set above the 256 byte limit without some heavier lifting to accomodate a
	// length larger than uint8_t will allow for.
	
	// SOLUTION:  Modify the I2C library
	// You need to change the data types in a few places to uint16_t in the I2C Rev5 library.
	// In particular, you need to change the bufferIndex, numberBytes, and the for loop iterator
	// in the write() method that takes an array. This is a much easier workaround than modifying Wire.
	// You can then set the MAX_BUFFER_SIZE higher than 256 but watch your SRAM limits (2k on Uno).

#ifdef USE_I2C_REV5_INSTEAD_OF_WIRE
	I2c.write(_i2cAddress,LG_ADDR_1X_CMD_FRAME,--pixelRGBs,pixelCount * 3);  // HACK: I fake the header number param with the '--' on the pointer    
#else
    Wire.beginTransmission(_i2cAddress);
    Wire.write(LG_ADDR_1X_CMD_FRAME);
    Wire.write(1); // hardcode the header number... this is only a 1X addressable shield
    for (int i = 0 ; i < pixelCount  ; i++) {  // TODO: Verify the BRG vs. RGB with JJ
	    Wire.write(pixelRGBs[i * 3 + 0]);  // write blue
	    Wire.write(pixelRGBs[i * 3 + 1]);  // write red
	    Wire.write(pixelRGBs[i * 3 + 2]);  // write green
    } 
    Wire.endTransmission();
#endif
    delay(5);
}


// ---------------------------------------------------------------------------
// Methods for DMX1XUniverse
// ---------------------------------------------------------------------------

void DMX1XUniverse::setDataStartingAtAddressWithRGB(uint8_t address, uint8_t r, uint8_t g, uint8_t b) {
	// TO-DO: assert that address >= 1 && address <= 509 		
#ifdef USE_I2C_REV5_INSTEAD_OF_WIRE
	uint8_t params[4];
	params[0] = address; // Remember that the DMX on the Encabulator does not want a header number
	params[1] = r;
	params[2] = g;
	params[3] = b;
	I2c.write(_i2cAddress,LG_DMX_1X_CMD_SET_BYTES_FROM_ADDR,params,4);
#else	
	Serial.print(address);
	Serial.print("-");
	Serial.print(r);
	Serial.print("-");
	Serial.print(g);
	Serial.print("-");
	Serial.println(b);
	Wire.beginTransmission(_i2cAddress);
	Wire.write(LG_DMX_1X_CMD_SET_BYTES_FROM_ADDR);
	// Wire.write(1);  // The DMX on the Encabulator does not want a header number
	Wire.write(address);	
	Wire.write(r);	
	Wire.write(g);	
	Wire.write(b);	
	Wire.endTransmission();
#endif
    delay(15);
}

void DMX1XUniverse::setEntireUniverse(uint8_t universe[]) {
#ifdef USE_I2C_REV5_INSTEAD_OF_WIRE
	// the MAX_BUFFER_LENGTH and some data types need to be modified in the I2C Rev5 library for this to work properly
	// see the frame method in the Addressable 1X class for more info
#else	
	// KNOWN ISSUE:  This is not possible due to the single byte index/buffer limitations in the Wire library.
#endif
    delay(10);
}



// ---------------------------------------------------------------------------
// Methods for XYZHelper
// ---------------------------------------------------------------------------

void XYZHelper::begin() {
	writeRegister(0x1d,0xCD);		// RESET
	delay(100);
	writeRegister(0x1b,0);
	writeRegister(0x1b,0b01000000);	// CTRL_REG1  12-bit setting
	writeRegister(0x1c,0); 			// CTRL_REG2  (slow data rate for TDTE, no tilt)
	writeRegister(0x1e,0);
	writeRegister(0x1f,0);			// INT_CTRL_REG1
	writeRegister(0x20,0);			// INT_CTRL_REG3
	writeRegister(0x1b,0xc4); 		// CTRL_REG1   12-bit operating mode, interrupts for new accl data off, +/- 2g, TDTE (directional tap) on 
	_initialized = true;
}

void XYZHelper::writeRegister(uint8_t reg, uint8_t data) {
#ifdef USE_I2C_REV5_INSTEAD_OF_WIRE
  I2c.write((uint8_t) XYZ,reg,data);
#else	
  Wire.beginTransmission(XYZ);    
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
#endif
}
		
uint8_t XYZHelper::readRegister(uint8_t reg) {

  uint8_t result = 0;

#ifdef USE_I2C_REV5_INSTEAD_OF_WIRE
  uint8_t inbound[1];
  I2c.read((uint8_t) XYZ,reg,1,inbound);
  result = inbound[0];
#else	
  Wire.beginTransmission(XYZ);    
  Wire.write(reg);  
  Wire.write(0);
  Wire.endTransmission();
  delay(1); 

  // read one byte from I2C bus

  Wire.requestFrom(XYZ,1);
  if(Wire.available()) {
	result = Wire.read();
  }
#endif

  return(result);
}

int16_t XYZHelper::combineBytes(uint8_t tempLow, uint8_t tempHigh) {
	int16_t r = (((tempHigh << 4) + (((tempLow & 0xf0) >> 4) & 0x0f)));	
	return (r > 2048) ? r = -(4096-r) : r;
}

int16_t XYZHelper::x() {
	if (! _initialized) begin(); 
	return combineBytes(readRegister(0x86),readRegister(0x87));
}

int16_t XYZHelper::y() {
	if (! _initialized) begin();  
	return combineBytes(readRegister(0x88),readRegister(0x89));
}

int16_t XYZHelper::z() {
	if (! _initialized) begin();  
	return combineBytes(readRegister(0x8A),readRegister(0x8B));
}


// ---------------------------------------------------------------------------
// Methods for DACHelper
// ---------------------------------------------------------------------------

void DACHelper::write(uint16_t value) {
	uint8_t tempLow=0, tempHigh=0;

	tempLow = (value & 0x00ff);
	tempHigh = (value & 0x0f00) >> 8;	// shift the high bits over for our 12-bit DAC

#ifdef USE_I2C_REV5_INSTEAD_OF_WIRE
	I2c.write((uint8_t) DAC,tempHigh,tempLow);
#else	
	Wire.beginTransmission(DAC);    
	Wire.write(tempHigh);  
	Wire.write(tempLow);  
	Wire.endTransmission();
#endif

}


// ---------------------------------------------------------------------------
// Methods for TemperatureHelper
// ---------------------------------------------------------------------------

float TemperatureHelper::getFahrenheit() {
	return getCelsius() * 9/5 + 32;
	
}

float TemperatureHelper::getCelsius() {
	uint8_t tempLow, tempHigh;
	bool tempNegative;
		
	uint16_t tempResult = 0;  
	float celsiusResult = 0;
	
	//default config register settings are for continuous conversion, 13-bit value, so we'll just use those

#ifdef USE_I2C_REV5_INSTEAD_OF_WIRE
    uint8_t inbound[2];
	I2c.read(TEMPSENSOR,0x0,2,inbound);
	tempHigh = inbound[0];
	tempLow = inbound[1];
#else	
	Wire.beginTransmission(TEMPSENSOR);    
	Wire.write(0x0);
	Wire.endTransmission();

	// read two bytes

	Wire.requestFrom(TEMPSENSOR,2);
	if (Wire.available()) tempHigh = Wire.read();
	if (Wire.available()) tempLow = Wire.read();
#endif

	tempNegative = (tempHigh & 0x80) ? 1 : 0;
	tempHigh = (tempHigh & 0x7f);
	tempLow = (tempLow & 0b11111000) >> 3;
	
	tempResult = (tempLow & 0x1f) + (tempHigh << 5);

	// convert result to decimal celsius
	
	if(! tempNegative) {
		celsiusResult = (float) tempResult / 16;
	} else {
		tempResult = tempResult + 0x1000;
		celsiusResult = ((float) tempResult - 8192) / 16;
	}

	return celsiusResult;
}


// ---------------------------------------------------------------------------
// Methods for EEPROMHelper
// ---------------------------------------------------------------------------

uint8_t EEPROMHelper::writeAddress(uint16_t address, uint8_t data) {
	uint8_t tempHigh = (uint8_t) ((address & 0xff00) >> 8);
	uint8_t tempLow = (address & 0xff);
#ifdef USE_I2C_REV5_INSTEAD_OF_WIRE
	uint8_t params[2];
	params[0] = tempLow;   // This is an ugly hack because of how I2C Rev5 does a write() with registers and doesn't support 16-bit addresses.
	params[1] = data;
	I2c.write(EEPROM,tempHigh,params,2);
#else	
  Wire.beginTransmission(EEPROM);
  Wire.write(tempHigh); 	// write MSB
  Wire.write(tempLow); // write LSB
  Wire.write(data);
  Wire.endTransmission();
#endif
  delay(5);
}

uint8_t EEPROMHelper::readAddress(uint16_t address) {
	uint8_t tempHigh = (uint8_t) ((address & 0xff00) >> 8);
	uint8_t tempLow = (address & 0xff);
	uint8_t result = 0;
#ifdef USE_I2C_REV5_INSTEAD_OF_WIRE
    // TODO: Determine if we can actually use the Rev5 I2C library to send two bytes as params for a read
    // For now, it does not look possible with this library without adding a new read method to pass in two bytes before reading.  
	uint8_t foo[1];
	I2c.read16(EEPROM,tempHigh,tempLow,1,foo);   // this is an ugly workaround for now
	result = foo[0];
#else	
	Wire.beginTransmission(EEPROM);
	Wire.write(tempHigh); 	// write MSB
	Wire.write(tempLow); 	// write LSB
	Wire.endTransmission();
	// read one result byte
	Wire.requestFrom(EEPROM,1);
	if (Wire.available()) { 
		result = Wire.read();
	}
#endif
  return result;
}



// ---------------------------------------------------------------------------
// Static Method: Encabulator::begin()
// For starting the I2C communication in master mode
// ---------------------------------------------------------------------------

void TurBullEncabulator::testPattern() {
	// call for each
	dmx.testPattern();
	addressable.testPattern();
	stripBankA.testPattern();
	stripBankB.testPattern();
}

void TurBullEncabulator::blackout() {
	// call for each
	dmx.blackout();
	addressable.blackout();
	stripBankA.blackout();
	stripBankB.blackout();
}

void TurBullEncabulator::upUpDownDownLeftRightLeftRightBA() {

#ifdef USE_I2C_REV5_INSTEAD_OF_WIRE
	I2c.begin();	
	I2c.setSpeed(1);
#else
 	Wire.begin();
#endif
	
	dac = DACHelper();
	accelerometer = XYZHelper();
	temperature = TemperatureHelper();
	eeprom = EEPROMHelper();
	
	addressable = Addr1XMultiTool();
	dmx = DMX1XUniverse();
	stripBankA = RGB4XStripA();
	stripBankB = RGB4XStripB();
}

bool TurBullEncabulator::_verbose = false;

void TurBullEncabulator::setVerbose(bool b) {
	if (b) {
		_verbose = true;
		Serial.begin(9600);
		Serial.println("TurBull Encabulator has been initialized.  All your bulls are belong to us.");
	} else {
		_verbose = false;
		// close serial port?
	}
}

// ---------------------------------------------------------------------------
// Preinstantiate
// ---------------------------------------------------------------------------

TurBullEncabulator Encabulator = TurBullEncabulator();


