# MNMkrWiFi1010RGBLEDLib

Arduino library to use either built in RGB LED on Mkr WiFi 1010 or an external RGB LED

Defines a RGB macro to create a colour value and defines an enum to describe a number of preset colours for ease of use and RGBType to hold value

Supports a flash option that in turn uses the MNTimer library


NB The built in RGB LED on the Mkr WiFi 1010 uses three pins to control the colour. I have note that some boards use pins 25,26,27 for the Red, Green and Blue control respectively whilst others have red and green inverted. I have not found a way to identify which is been implemented. If you find that red and green are inverted then change
