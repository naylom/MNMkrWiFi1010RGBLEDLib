#include "MNRGBLEDBaseLib.h"
#include <MNTimerLib.h>

MNRGBLEDBaseLib::MNRGBLEDBaseLib()
{
	m_bFlash 	= false;
}
/// <summary>
/// Sets the colour of the LED and optionally the flash time (in 1/10 sec increments)
/// </summary>
/// <param name="theColour">the RGB type colour to be used
/// <param name="FlashTime">the flash time in 1/10 sec intervals, 0 implies permanently on
/// <returns>callback function address</returns>
void MNRGBLEDBaseLib::SetLEDColour ( RGBType theColour, uint32_t flashTime )
{
	m_LastColour = theColour;
    SetDeviceRed ( RGB_RED ( theColour ) );
    SetDeviceGreen ( RGB_GREEN ( theColour ) );
    SetDeviceBlue ( RGB_BLUE ( theColour ) );
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
	if 	( m_OnOff )
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
CRGBLED::CRGBLED( const int iRedPin, const int iGreenPin, const int iBluePin )
{
	m_iRedPin	=  iRedPin;
	m_iGreenPin	=  iGreenPin;
	m_iBluePin	=  iBluePin;
}
void CRGBLED::InitDevice()
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
/* If we are compiling on MKR WiFI 1010 with built in RGB LED the create derived class to control in and declare an instance as there is only one such LED */
#ifdef ARDUINO_ARCH_SAMD
const static int 	m_iMkrRedPin              	= 25;
const static int 	m_iMkrGreenPin            	= 26;
const static int 	m_iMkrBluePin				= 27; 

void CMkrWiFi1010RGBLED::InitDevice()
{
	WiFiDrv::pinMode ( m_iMkrRedPin,    OUTPUT );
	WiFiDrv::pinMode ( m_iMkrGreenPin,  OUTPUT );
	WiFiDrv::pinMode ( m_iMkrBluePin,   OUTPUT );
}
void 	CMkrWiFi1010RGBLED::SetDeviceRed ( uint8_t strength )
{
	WiFiDrv::analogWrite ( m_iMkrRedPin, strength );
}
void    CMkrWiFi1010RGBLED::SetDeviceGreen ( uint8_t strength )
{
	WiFiDrv::analogWrite ( m_iMkrGreenPin, strength );
}
void    CMkrWiFi1010RGBLED::SetDeviceBlue ( uint8_t strength )
{
	WiFiDrv::analogWrite ( m_iMkrBluePin, strength );
}
CMkrWiFi1010RGBLED	TheMKR_RGB_LED;
#endif