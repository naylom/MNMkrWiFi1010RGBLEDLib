// Base Library to control RGB LED
//
//
// M. Naylor - November 2022
//
// Also uses the MNTimerLib library for flash functionality
#pragma once
#include <Arduino.h>
/*
    Some Mkr wifi 1010 boards have the built in LED red and green pins inverted, so if MKR_RGB_INVERT is defined the
   code will compensate
*/
#define RGB( R, G, B )                                                                                                 \
	( ( ( R & 0xff ) << 16 ) | ( ( G & 0xff ) << 8 ) |                                                                 \
	  ( B &                                                                                                            \
	    0xff ) )  // takes three values each 0 - 255 to determine strength of RGB colour ands returns a combined value
#define RGB_RED( RGBValue ) ( ( RGBValue & 0xff0000 ) >> 16 )   // extracts RED value from RGB value
#define RGB_GREEN( RGBValue ) ( ( RGBValue & 0x00ff00 ) >> 8 )  // extracts GREEN value from RGB value
#define RGB_BLUE( RGBValue ) ( RGBValue & 0x0000ff )            // extract BLUE value from RGB Value
typedef uint32_t RGBType;

class MNRGBLEDBaseLib
{
private:
	bool m_bFlash = false;
	uint8_t m_OnOff = 0;
	const uint8_t m_maxRed;
	const uint8_t m_maxGreen;
	const uint8_t m_maxBlue;
	RGBType m_LastColour;

	void Flash ();

public:
	enum eColour : RGBType
	{
		BLACK = RGB ( 0, 0, 0 ),
		RED = RGB ( 255, 0, 0 ),
		GREEN = RGB ( 0, 255, 0 ),
		BLUE = RGB ( 0, 0, 255 ),
		CYAN = RGB ( 0, 255, 255 ),
		MAGENTA = RGB ( 255, 0, 255 ),
		YELLOW = RGB ( 255, 255, 0 ),
		WHITE = RGB ( 255, 255, 255 ),
		DARK_MAGENTA = RGB ( 128, 0, 128 ),
		GRAY = RGB ( 128, 128, 128 ),
		DARK_RED = RGB ( 128, 0, 0 ),
		DARK_GREEN = RGB ( 0, 128, 0 ),
		DARK_BLUE = RGB ( 0, 0, 128 ),
		DARK_YELLOW = RGB ( 128, 128, 0 ),
		DARK_CYAN = RGB ( 0, 128, 128 )
	};

	MNRGBLEDBaseLib ( uint8_t maxRed = 255, uint8_t maxGreen = 255, uint8_t maxBlue = 255 )
	    : m_maxRed ( maxRed ), m_maxGreen ( maxGreen ), m_maxBlue ( maxBlue ) {};
	void SetLEDColour ( RGBType theColour, uint32_t flashTime = 0 );
	virtual void InitDevice () = 0;
	virtual void SetDeviceRed ( uint8_t strength ) = 0;
	virtual void SetDeviceGreen ( uint8_t strength ) = 0;
	virtual void SetDeviceBlue ( uint8_t strength ) = 0;
};

// derived class using 3 analog pins to control RGB led
class CRGBLED : public MNRGBLEDBaseLib
{
public:
	using MNRGBLEDBaseLib::MNRGBLEDBaseLib;

private:
	const int m_iRedPin;
	const int m_iGreenPin;
	const int m_iBluePin;

public:
	CRGBLED ( const int iRedPin,
	          const int iGreenPin,
	          const int iBluePin,
	          uint8_t maxRed = 255,
	          uint8_t maxGreen = 255,
	          uint8_t maxBlue = 255 )
	    : MNRGBLEDBaseLib ( maxRed, maxGreen, maxBlue ), m_iRedPin ( iRedPin ), m_iGreenPin ( iGreenPin ),
	      m_iBluePin ( iBluePin ) {};
	void InitDevice ();
	void SetDeviceRed ( uint8_t strength );
	void SetDeviceGreen ( uint8_t strength );
	void SetDeviceBlue ( uint8_t strength );
};
#ifdef ARDUINO_ARCH_SAMD
#include <utility/wifi_drv.h>
#include <WiFiNINA.h>

// derived class to control built in RGB LED on MKR WiFi 1010
class CMkrWiFi1010RGBLED : public MNRGBLEDBaseLib
{
public:
	using MNRGBLEDBaseLib::MNRGBLEDBaseLib;

private:
	int m_iMkrRedPin = 26;
	int m_iMkrGreenPin = 25;
	int m_iMkrBluePin = 27;

public:
	CMkrWiFi1010RGBLED () {};
	void InitDevice ();
	void Invert ();
	void SetDeviceRed ( uint8_t strength );
	void SetDeviceGreen ( uint8_t strength );
	void SetDeviceBlue ( uint8_t strength );
};


extern CMkrWiFi1010RGBLED TheMKR_RGB_LED;

#endif

// CPCA9685RGBLED is compiled only when the Adafruit PWM Servo Driver library is present.
#if __has_include( <Adafruit_PWMServoDriver.h>)
#include <Adafruit_PWMServoDriver.h>

/**
 * @brief Drives an RGB LED connected to three channels of a shared PCA9685 PWM controller.
 * @details The caller owns the Adafruit_PWMServoDriver and must have called
 *          begin() on it (and confirmed the device is present) before calling
 *          InitDevice() on this object. Each 8-bit colour component received
 *          from the base class is scaled to the 12-bit PCA9685 range (0-4095).
 */
class CPCA9685RGBLED : public MNRGBLEDBaseLib
{
public:
	/**
	 * @brief Constructs the PCA9685-backed RGB LED driver.
	 * @param driver       Reference to the caller-owned, already-initialised
	 *                     Adafruit_PWMServoDriver. Must outlive this object.
	 * @param redChannel   PCA9685 channel number (0-15) wired to the red LED pin.
	 * @param greenChannel PCA9685 channel number (0-15) wired to the green LED pin.
	 * @param blueChannel  PCA9685 channel number (0-15) wired to the blue LED pin.
	 * @param commonAnode  True if the LED has a common anode (output LOW = on);
	 *                     false (default) for common cathode (output HIGH = on).
	 *                     The PCA9685 defaults to totem-pole output, so common
	 *                     cathode is the typical wiring without hardware changes.
	 * @param maxRed       Calibration cap for the red channel (0-255), default 255.
	 * @param maxGreen     Calibration cap for the green channel (0-255), default 255.
	 * @param maxBlue      Calibration cap for the blue channel (0-255), default 255.
	 */
	CPCA9685RGBLED ( Adafruit_PWMServoDriver& driver,
	                 uint8_t redChannel,
	                 uint8_t greenChannel,
	                 uint8_t blueChannel,
	                 bool commonAnode = false,
	                 uint8_t maxRed = 255,
	                 uint8_t maxGreen = 255,
	                 uint8_t maxBlue = 255 );

	/**
	 * @brief Marks the driver as ready and sets all three channels to off.
	 * @details Asserts that the driver has not already been initialised via this
	 *          method. The caller must have successfully called
	 *          Adafruit_PWMServoDriver::begin() before calling this.
	 */
	void InitDevice () override;

	void SetDeviceRed ( uint8_t strength ) override;
	void SetDeviceGreen ( uint8_t strength ) override;
	void SetDeviceBlue ( uint8_t strength ) override;

private:
	Adafruit_PWMServoDriver& _driver;  // reference to the caller-owned PCA9685 driver
	const uint8_t _redCh;              // PCA9685 channel for the red LED pin
	const uint8_t _greenCh;            // PCA9685 channel for the green LED pin
	const uint8_t _blueCh;             // PCA9685 channel for the blue LED pin
	const bool _commonAnode;           // true = common anode (invert PWM polarity)
	bool _initialized;                 // true after InitDevice() has been called
};

#endif  // __has_include(<Adafruit_PWMServoDriver.h>)
