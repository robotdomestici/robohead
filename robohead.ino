/*
 * robohead.ino
 * Controller for Robot Head - Main file
 * Based on Arduino Nano 328 16Mhz
 * Rev. 0.1 07/10/2012
 * Walter Mollica <walter.mollica@robot-domestici.it>
 */

#include "robohead.h"
int DRED, DGREEN, DBLUE;
int i,j,k;
bool avgFirstRun;
Servo headMover;
/********* SETUP FUNCTION *********/
void setup()
{
	DRED = 0; DGREEN = 0; DBLUE = 0;
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
	  setupRGB(DRED,DGREEN,DBLUE);
	  //servo initial config
	  headMover.attach(SERVO);
}
/********* CUSTOM FUNCTIONS *********/

/********* LOOP FUNCTION *********/
int *curAvg; int redBr;
void loop()
{
curAvg = micAveraging();
redBr = (analogRead(MICLEFT)*1.3>curAvg[0]) ? 255 : 0;
setRGBComponent(RGBRED, (int)redBr);
Serial.print(curAvg[0]);
Serial.print("  ");
Serial.print(redBr);
Serial.println();

}


