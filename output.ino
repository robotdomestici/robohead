#include "robohead.h"

/*
 * Set a single color component of the RGB Led
 */
void setRGBComponent(int color, int value) {
	analogWrite(color, value);
}
/*
 * Set RGB Led values
 */
void setupRGB(int r, int g, int b) {
	analogWrite(RGBRED, r);
	analogWrite(RGBGREEN, g);
	analogWrite(RGBBLUE, b);
}

/*
 * Light the LED and move the Servo
 */
void triggerSound(int direction) {
	int mic, degrees;
	mic = (direction == 0) ? LEDLEFT : LEDRIGHT;
	//light on
	digitalWrite(mic, HIGH);
	//Serial.print("*************GIRA A ");
	//Serial.print(direction);
	//Serial.println();
	//head position: center
	delay(200);
	headMover.write(90);
	delay(400);
	degrees = (direction == 0) ? 0 : 179;
	//turn head where called
	headMover.write(degrees);
	delay(400);
	//led off
	digitalWrite(mic, LOW);
}
