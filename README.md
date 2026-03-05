# MNMkrWiFi1010RGBLEDLib

Arduino library to use either built in RGB LED on Mkr WiFi 1010 or an external RGB LED

Defines a RGB macro to create a colour value and defines an enum to describe a number of preset colours for ease of use and RGBType to hold value

Supports a flash option that in turn uses the MNTimer library

External rgb leds sometimes suffer from different colour leds being often different strength. The size of resistor used can implact this. If after resistror selection this is still a problem the library has an option feature to limit the strength of individual colours. 
When creating the external LED a max value can optionally be set per colour. When a subsequent call to set the colour is made, each of the red, green and blue components is scaled by the respective max strength.

NB The built in RGB LED on the Mkr WiFi 1010 uses three pins to control the colour. I have noted that some boards use pins 25,26,27 for the Red, Green and Blue control respectively whilst others have red and green inverted. I have not found a way to identify which has been implemented and code around this. If you find that red and green are inverted then call The Invert function as shown in the example


