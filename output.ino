#include "robohead.h"

//set a single color component of the RGB Led
void setRGBComponent(int color, int value) {
  analogWrite(color,value);
}
//set values of the RGB Led
void setupRGB(int r,int g, int b) {
  analogWrite(RGBRED, r);
  analogWrite(RGBGREEN, g);
  analogWrite(RGBBLUE, b);
}

//light the LED and move the Servo
void triggerSound(int direction) {
	//lights the right for 2 seconds LED
	digitalWrite(direction,1);
	delay(2000);
	digitalWrite(direction,0);


}
