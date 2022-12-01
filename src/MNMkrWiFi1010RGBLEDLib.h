// Library to control RGB LED on MKR wifi 1010 - 
// At time of writing this is the only board with this built LED, and therefore should not work on other Arduino MKR boards
//
// M. Naylor - November 2022
//
// This uese the WiFiNINA and related utility/wifi_drv libraries
// Also uses the MNTimerLib library
#pragma once
#include <WiFiNINA.h>
#include <utility/wifi_drv.h>

#define RGB( R, G, B )      ( ( ( R & 0xff ) << 16 ) | ( ( G & 0xff ) << 8 ) | ( B & 0xff ) )   // takes three values each 0 - 255 to determine strength of RGB colour ands returns a combined value
#define RGB_RED( RGBValue )     ( ( RGBValue & 0xff0000 ) >> 16 )                               // extracts RED value from RGB value
#define RGB_GREEN( RGBValue )   ( ( RGBValue & 0x00ff00 ) >> 8 )                                // extracts GREEN value from RGB value
#define RGB_BLUE( RGBValue )    ( RGBValue & 0x0000ff )                                         // extract BLUE value from RGB Value

class MNMkrWiFi1010RGBLEDLib
{
private:
    const static int 	m_iRedPin              	= 26;
    const static int 	m_iGreenPin            	= 25;
    const static int 	m_iBluePin            	= 27;    
	bool				m_bFlash 				= false;	
	uint8_t				m_OnOff					= 0;
	uint32_t			m_LastColour;
    bool                m_bInitialised          = false;
	void 				Flash ();
	void                Init();
public:   
    enum  eColour { 
					BLACK           = RGB (   0,   0,   0 ), 
                    RED             = RGB ( 255,   0,   0 ), 
                    GREEN           = RGB (   0, 255,   0 ), 
                    BLUE            = RGB (   0,   0, 255 ),
                    CYAN            = RGB (   0, 255, 255 ),
                    MAGENTA         = RGB ( 255,   0, 255 ),
                    YELLOW          = RGB ( 255, 255,   0 ),   
                    WHITE           = RGB ( 255, 255, 255 ),
                    DARK_MAGENTA    = RGB ( 128,   0, 128 ),
                    GRAY            = RGB ( 128, 128, 128 ),
                    DARK_RED        = RGB ( 128,   0,   0 ),
                    DARK_GREEN      = RGB (   0, 128,   0 ),
                    DARK_BLUE       = RGB (   0,   0, 128 ),
                    DARK_YELLOW     = RGB ( 128, 128,   0 ),
                    DARK_CYAN       = RGB (   0, 128, 128 )
                   };
    				MNMkrWiFi1010RGBLEDLib();			
    void 			SetLEDColour ( MNMkrWiFi1010RGBLEDLib::eColour theColour, uint32_t flashTime = 0 );

};
extern MNMkrWiFi1010RGBLEDLib	TheMKR_RGB_LED;