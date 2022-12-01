#include "MNMkrWiFi1010RGBLEDLib.h"
#include <MNTimerLib.h>

MNMkrWiFi1010RGBLEDLib::MNMkrWiFi1010RGBLEDLib()
{
}
void MNMkrWiFi1010RGBLEDLib::Init()
{
	if ( m_bInitialised == false )
	{
		m_bInitialised = true;
	    // Set up LED Pins
	    WiFiDrv::pinMode ( m_iRedPin,    OUTPUT );
	    WiFiDrv::pinMode ( m_iGreenPin,  OUTPUT );
	    WiFiDrv::pinMode ( m_iBluePin,   OUTPUT );
		m_bFlash = false;
	}
}
/// <summary>
/// Sets the colour of the MKR builtin RGB LED and optionally the flash time (in 1/10 sec increments)
/// </summary>
/// <param name="theColour">the RGB type colour to be used
/// <param name="FlashTime">the flash time in 1/10 sec intervals, 0 implies permanently on
/// <returns>callback function address</returns>
void MNMkrWiFi1010RGBLEDLib::SetLEDColour ( MNMkrWiFi1010RGBLEDLib::eColour theColour,	uint32_t flashTime )
{
	Init();
	m_LastColour = theColour;
    WiFiDrv::analogWrite ( m_iRedPin,   RGB_RED ( theColour ) );
    WiFiDrv::analogWrite ( m_iGreenPin, RGB_GREEN ( theColour ) );
    WiFiDrv::analogWrite ( m_iBluePin,  RGB_BLUE ( theColour ) );
	TheTimer.RemoveCallBack ( (MNTimerClass*)this, (aMemberFunction)&MNMkrWiFi1010RGBLEDLib::Flash );

	if ( flashTime > 0 )
	{
		m_OnOff = 0;
		if ( !TheTimer.AddCallBack ( (MNTimerClass*)this, (aMemberFunction)&MNMkrWiFi1010RGBLEDLib::Flash, flashTime / 10 * 2000 ) )
		{
			Serial.println ( F ( "Unable to add callback " ) );
		}
	}
}
/// <summary>
/// timer callback routine to make the MKR builtin RGB LED Flash
/// </summary>
/// <returns>nothing</returns>
void MNMkrWiFi1010RGBLEDLib::Flash ()
{
	uint32_t Colour;

	m_OnOff = !m_OnOff;
	if 	( m_OnOff )
	{
		Colour = m_LastColour;
	}
	else
	{
		Colour = BLACK;
	}
    WiFiDrv::analogWrite ( m_iRedPin,   RGB_RED ( Colour ) );
    WiFiDrv::analogWrite ( m_iGreenPin, RGB_GREEN ( Colour ) );
    WiFiDrv::analogWrite ( m_iBluePin,  RGB_BLUE ( Colour ) );	
}
MNMkrWiFi1010RGBLEDLib	TheMKR_RGB_LED;