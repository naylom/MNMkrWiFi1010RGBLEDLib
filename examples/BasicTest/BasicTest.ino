//#define MKR_RGB_INVERT
#include <MNRGBLEDBaseLib.h>
/*

Example for library showing how to use built in Mkr Wifi 1010 RGB LED and an external LED

NB Some MKR wifi boards have red and green pins on built in LED inverted. There appears no way to detect this in code. If you find that the red and green colours are inverted
then uncomment the first line with the #define. The library will then compensate. Note the #define must occur before the #include

*/
constexpr 	auto 			FLASHTIME 		= 10;					// every 2 seconds, ie 1 = 1/5 second
const int	iRedPin              	= A4;
const int 	iGreenPin            	= A5;
const int 	iBluePin            	= A6; 

// create instance
CRGBLED myLED ( iRedPin, iGreenPin, iBluePin );

void setup() 
{	
}

void loop()
{
	myLED.SetLEDColour ( MNRGBLEDBaseLib::eColour::WHITE );
	TheMKR_RGB_LED.SetLEDColour ( MNRGBLEDBaseLib::eColour::WHITE );
	delay ( 3000 );
	myLED.SetLEDColour ( MNRGBLEDBaseLib::eColour::RED, FLASHTIME );
	TheMKR_RGB_LED.SetLEDColour ( MNRGBLEDBaseLib::eColour::RED, FLASHTIME );
	delay ( 6000 );
	myLED.SetLEDColour ( MNRGBLEDBaseLib::eColour::GREEN, FLASHTIME );
	TheMKR_RGB_LED.SetLEDColour ( MNRGBLEDBaseLib::eColour::GREEN, FLASHTIME );
	delay ( 6000 );
	myLED.SetLEDColour ( MNRGBLEDBaseLib::eColour::BLUE, FLASHTIME );
	TheMKR_RGB_LED.SetLEDColour ( MNRGBLEDBaseLib::eColour::BLUE, FLASHTIME );
	delay ( 6000 );	

	
}