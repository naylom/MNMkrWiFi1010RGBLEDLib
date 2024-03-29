// Base Library to control RGB LED
//
//
// M. Naylor - November 2022
//
// Also uses the MNTimerLib library for flash functionality
#pragma once
#include <arduino.h>
/*
	Some Mkr wifi 1010 boards have the built in LED red and green pins inverted, so if MKR_RGB_INVERT is defined the code will compensate
*/
#define RGB( R, G, B )		  ( ( ( R & 0xff ) << 16 ) | ( ( G & 0xff ) << 8 ) | ( B & 0xff ) ) // takes three values each 0 - 255 to determine strength of RGB colour ands returns a combined value
#define RGB_RED( RGBValue )	  ( ( RGBValue & 0xff0000 ) >> 16 )									// extracts RED value from RGB value
#define RGB_GREEN( RGBValue ) ( ( RGBValue & 0x00ff00 ) >> 8 )									// extracts GREEN value from RGB value
#define RGB_BLUE( RGBValue )  ( RGBValue & 0x0000ff )											// extract BLUE value from RGB Value
typedef uint32_t RGBType;

class MNRGBLEDBaseLib
{
	private:
		bool		  m_bFlash = false;
		uint8_t		  m_OnOff  = 0;
		const uint8_t m_maxRed;
		const uint8_t m_maxGreen;
		const uint8_t m_maxBlue;
		RGBType		  m_LastColour;

		void		  Flash ();

	public:
		enum eColour : RGBType {
			BLACK		 = RGB ( 0, 0, 0 ),
			RED			 = RGB ( 255, 0, 0 ),
			GREEN		 = RGB ( 0, 255, 0 ),
			BLUE		 = RGB ( 0, 0, 255 ),
			CYAN		 = RGB ( 0, 255, 255 ),
			MAGENTA		 = RGB ( 255, 0, 255 ),
			YELLOW		 = RGB ( 255, 255, 0 ),
			WHITE		 = RGB ( 255, 255, 255 ),
			DARK_MAGENTA = RGB ( 128, 0, 128 ),
			GRAY		 = RGB ( 128, 128, 128 ),
			DARK_RED	 = RGB ( 128, 0, 0 ),
			DARK_GREEN	 = RGB ( 0, 128, 0 ),
			DARK_BLUE	 = RGB ( 0, 0, 128 ),
			DARK_YELLOW	 = RGB ( 128, 128, 0 ),
			DARK_CYAN	 = RGB ( 0, 128, 128 )
		};

		MNRGBLEDBaseLib ( uint8_t maxRed = 255, uint8_t maxGreen = 255, uint8_t maxBlue = 255 ) : m_maxRed ( maxRed ), m_maxGreen ( maxGreen ), m_maxBlue ( maxBlue ) {};
		void		 SetLEDColour ( RGBType theColour, uint32_t flashTime = 0 );
		virtual void InitDevice ()						 = 0;
		virtual void SetDeviceRed ( uint8_t strength )	 = 0;
		virtual void SetDeviceGreen ( uint8_t strength ) = 0;
		virtual void SetDeviceBlue ( uint8_t strength )	 = 0;
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
		CRGBLED ( const int iRedPin, const int iGreenPin, const int iBluePin, uint8_t maxRed = 255, uint8_t maxGreen = 255, uint8_t maxBlue = 255 ) : MNRGBLEDBaseLib ( maxRed, maxGreen, maxBlue ), m_iRedPin (iRedPin), m_iGreenPin ( iGreenPin ), m_iBluePin ( iBluePin ) {};
		void InitDevice ();
		void SetDeviceRed ( uint8_t strength );
		void SetDeviceGreen ( uint8_t strength );
		void SetDeviceBlue ( uint8_t strength );
};
#ifdef ARDUINO_ARCH_SAMD
	#include <WiFiNINA.h>
	#include <utility/wifi_drv.h>

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
		CMkrWiFi1010RGBLED (){};
		void InitDevice ();
		void Invert();
		void SetDeviceRed ( uint8_t strength );
		void SetDeviceGreen ( uint8_t strength );
		void SetDeviceBlue ( uint8_t strength );
};


extern CMkrWiFi1010RGBLED TheMKR_RGB_LED;

#endif
