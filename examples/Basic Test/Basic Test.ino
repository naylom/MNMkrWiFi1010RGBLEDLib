#include <MNMkrWiFi1010RGBLEDLib.h>

constexpr 	auto 			FLASHTIME 		= 10;					// every 2 seconds, ie 1 = 1/5 second
void setup() 
{	
}

void loop()
{
	TheMKR_RGB_LED.SetLEDColour( MNMkrWiFi1010RGBLEDLib::WHITE );
	delay ( 1000 );
	TheMKR_RGB_LED.SetLEDColour ( MNMkrWiFi1010RGBLEDLib::eColour::GREEN, FLASHTIME );
	delay ( 6000 );
}