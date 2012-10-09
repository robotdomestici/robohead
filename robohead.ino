/*
 * robohead.ino
 * Controller for Robot Head - Main file
 * Based on Arduino Nano 328 16Mhz
 * Rev. 0.1 07/10/2012
 * Walter Mollica <walter.mollica@robot-domestici.it>
 */

#include "robohead.h"
int DRED, DGREEN, DBLUE;
int i, j, k;
bool avgFirstRun;
Servo headMover;
/********* SETUP FUNCTION *********/
void setup() {
	DRED = 0;
	DGREEN = 0;
	DBLUE = 0;
	Serial.begin(9600); //start serial
	//Ultrasound pins IO - SRF05 Trig/Echo sep. mode
	pinMode(ECHOPIN, INPUT);
	pinMode(TRIGPIN, OUTPUT);
	//RGB Led IO - common cathode
	pinMode(RGBRED, OUTPUT);
	pinMode(RGBGREEN, OUTPUT);
	pinMode(RGBBLUE, OUTPUT);
	//MIC IO - elec. 300x amplified
	pinMode(MICLEFT, INPUT);
	//first run of the averaging: true
	avgFirstRun = true;
	//initial RGB Led setup
	setupRGB(DRED, DGREEN, DBLUE);
	//servo initial config
	//headMover.write(90);
	headMover.attach(SERVO);
	//configure the Sharp 2D120X
	  int out[] = {150,140,130,120,110,100, 90, 80, 70, 60, 50, 40, 30, 20};
	  int in[]  = { 90, 97,105,113,124,134,147,164,185,218,255,317,408,506};
	 // cm = multiMap(val, in, out, 14);
}
/********* CUSTOM FUNCTIONS *********/

/********* LOOP FUNCTION *********/
int *curAvg;
int redBr;
void loop() {
	//curAvg = micAveraging();
	//redBr = (abs(analogRead(MICLEFT)) * 1.3 > curAvg[0]) ? 255 : 0;
	//setRGBComponent(RGBRED, (int) redBr);
	//Serial.println(log(pow((analogRead(MICLEFT) - 512),2)));
	//Serial.println(abs(analogRead(MICLEFT) - 511));
	computeMicDifference();
	/*headMover.write(0);

delay(500);
headMover.write(179);
delay(500);*/
/*int pos;
for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees
{                                  // in steps of 1 degree
  headMover.write(pos);              // tell servo to go to position in variable 'pos'
  delay(15);                       // waits 15ms for the servo to reach the position
}
for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees
{
	headMover.write(pos);              // tell servo to go to position in variable 'pos'
  delay(15);                       // waits 15ms for the servo to reach the position
}*/
	/*Serial.print(curAvg[0]);
	Serial.print("  ");
	Serial.print(redBr);
	Serial.println();*/

}

