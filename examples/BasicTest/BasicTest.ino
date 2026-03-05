#define MKR_RGB_INVERT
#include <MNRGBLEDBaseLib.h>
/*

Example for library showing how to use built in Mkr Wifi 1010 RGB LED and an external LED

NB Some MKR wifi boards have red and green pins on built in LED inverted. There appears no way to detect this in code. If you find that the red and green colours are inverted
then call the Invert() function in the setup. The library will then compensate.

*/
constexpr 	auto 			FLASHTIME 		= 10;					// every 2 seconds, ie 1 = 1/5 second
const int	iRedPin              	= 6;	// Should be pwm pins it you want 24 bit colour
const int 	iGreenPin            	= 7;
const int 	iBluePin            	= 8; 

// create instance of external rgb led
// such leds often have different strengths of brightness between the three colours. The size of the reisstir used for each led can compensate. If however this is not enough the library allows  a max strength value to be set for each colour. 
// This is then used to scale any SETLEDColour colours. By default the max value for a red green or blue colour is 255. If the respective max strength is set to say 200 then any request to set the colour from 0 to 255 will be scaled to 0 to 200, 
// ie 255 will actually generate 200 and 66 generate 66 * 200 / 255. If no max strengths are set there is no scaling and the full range is used.

CRGBLED myLED ( iRedPin, iGreenPin, iBluePin, 255, 127, 64 );		// sets max red to 255, max green to 127 and max blue to 64

void setup() 
{	
	// Optionally switch red and green signals for those MKR boards that need it.
	TheMKR_RGB_LED.Invert();
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