#include "MNRGBLEDBaseLib.h"

#include <assert.h>
#include <MNTimerLib.h>

/// <summary>
/// Sets the colour of the LED and optionally the flash time (in 1/10 sec increments)
/// </summary>
/// <param name="theColour">the RGB type colour to be used
/// <param name="FlashTime">the flash time in 1/10 sec intervals, 0 implies permanently on
/// <returns>callback function address</returns>
void MNRGBLEDBaseLib::SetLEDColour ( RGBType theColour, uint32_t flashTime )
{
	m_LastColour = theColour;
	SetDeviceRed ( RGB_RED ( theColour ) * m_maxRed / 255 );
	SetDeviceGreen ( RGB_GREEN ( theColour ) * m_maxGreen / 255 );
	SetDeviceBlue ( RGB_BLUE ( theColour ) * m_maxBlue / 255 );
	if ( m_bFlash )
	{
		TheTimer.RemoveCallBack ( (MNTimerClass*)this, (aMemberFunction)&MNRGBLEDBaseLib::Flash );
		m_bFlash = false;
	}

	if ( flashTime > 0 )
	{
		m_bFlash = true;
		m_OnOff = 0;
		TheTimer.AddCallBack ( (MNTimerClass*)this, (aMemberFunction)&MNRGBLEDBaseLib::Flash, flashTime / 10 * 2000 );
	}
}

/// <summary>
/// timer callback routine to make the MKR builtin RGB LED Flash
/// </summary>
/// <returns>nothing</returns>
void MNRGBLEDBaseLib::Flash ()
{
	RGBType theColour;

	m_OnOff = !m_OnOff;
	if ( m_OnOff )
	{
		theColour = m_LastColour;
	}
	else
	{
		theColour = BLACK;
	}
	SetDeviceRed ( RGB_RED ( theColour ) );
	SetDeviceGreen ( RGB_GREEN ( theColour ) );
	SetDeviceBlue ( RGB_BLUE ( theColour ) );
}

/*
        CRGBLED derived class for 3 analog pin RGBs, note you need to create an instance  to use this class
*/

void CRGBLED::InitDevice ()
{
	pinMode ( m_iRedPin, OUTPUT );
	pinMode ( m_iGreenPin, OUTPUT );
	pinMode ( m_iBluePin, OUTPUT );
}

void CRGBLED::SetDeviceRed ( uint8_t strength )
{
	analogWrite ( m_iRedPin, strength );
}

void CRGBLED::SetDeviceGreen ( uint8_t strength )
{
	analogWrite ( m_iGreenPin, strength );
}

void CRGBLED::SetDeviceBlue ( uint8_t strength )
{
	analogWrite ( m_iBluePin, strength );
}

/* If we are compiling on MKR WiFI 1010 with built in RGB LED the create derived class to control in and declare an
 * instance as there is only one such LED */

#ifdef ARDUINO_ARCH_SAMD
/*
    #ifdef MKR_RGB_INVERT
const static int m_iMkrRedPin	= 25;
const static int m_iMkrGreenPin = 26;
const static int m_iMkrBluePin	= 27;
     #else
const static int m_iMkrRedPin	= 26;
const static int m_iMkrGreenPin = 25;
const static int m_iMkrBluePin	= 27;
     #endif
*/
void CMkrWiFi1010RGBLED::InitDevice ()
{
	WiFiDrv::pinMode ( m_iMkrRedPin, OUTPUT );
	WiFiDrv::pinMode ( m_iMkrGreenPin, OUTPUT );
	WiFiDrv::pinMode ( m_iMkrBluePin, OUTPUT );
}

void CMkrWiFi1010RGBLED::Invert ()
{
	m_iMkrRedPin = 25;
	m_iMkrGreenPin = 26;
}

void CMkrWiFi1010RGBLED::SetDeviceRed ( uint8_t strength )
{
	WiFiDrv::analogWrite ( m_iMkrRedPin, strength );
}

void CMkrWiFi1010RGBLED::SetDeviceGreen ( uint8_t strength )
{
	WiFiDrv::analogWrite ( m_iMkrGreenPin, strength );
}

void CMkrWiFi1010RGBLED::SetDeviceBlue ( uint8_t strength )
{
	WiFiDrv::analogWrite ( m_iMkrBluePin, strength );
}
CMkrWiFi1010RGBLED TheMKR_RGB_LED;
#endif

#if __has_include( <Adafruit_PWMServoDriver.h>)
#include <Adafruit_PWMServoDriver.h>

// Scale an 8-bit colour component (0-255) to a 12-bit PCA9685 level (0-4095).
static inline uint16_t scaleToPca9685 ( uint8_t strength )
{
	return static_cast<uint16_t> ( strength ) * 4095U / 255U;
}

CPCA9685RGBLED::CPCA9685RGBLED ( Adafruit_PWMServoDriver& driver,
                                 uint8_t redChannel,
                                 uint8_t greenChannel,
                                 uint8_t blueChannel,
                                 bool commonAnode,
                                 uint8_t maxRed,
                                 uint8_t maxGreen,
                                 uint8_t maxBlue )
    : MNRGBLEDBaseLib ( maxRed, maxGreen, maxBlue ), _driver ( driver ), _redCh ( redChannel ),
      _greenCh ( greenChannel ), _blueCh ( blueChannel ), _commonAnode ( commonAnode ), _initialized ( false )
{
}

/**
 * @brief Marks the driver as ready and sets all three channels to off.
 * @details The Adafruit_PWMServoDriver::begin() must have been called and returned
 *          true before this method is invoked. Asserts against double-initialisation.
 */
void CPCA9685RGBLED::InitDevice ()
{
	assert ( !_initialized );  // guard against double-initialisation
	_driver.setPin ( _redCh,   0, _commonAnode );
	_driver.setPin ( _greenCh, 0, _commonAnode );
	_driver.setPin ( _blueCh,  0, _commonAnode );
	_initialized = true;
}

void CPCA9685RGBLED::SetDeviceRed ( uint8_t strength )
{
	assert ( _initialized );
	_driver.setPin ( _redCh, scaleToPca9685 ( strength ), _commonAnode );
}

void CPCA9685RGBLED::SetDeviceGreen ( uint8_t strength )
{
	assert ( _initialized );
	_driver.setPin ( _greenCh, scaleToPca9685 ( strength ), _commonAnode );
}

void CPCA9685RGBLED::SetDeviceBlue ( uint8_t strength )
{
	assert ( _initialized );
	_driver.setPin ( _blueCh, scaleToPca9685 ( strength ), _commonAnode );
}

#endif  // __has_include(<Adafruit_PWMServoDriver.h>)