#include "robohead.h"

/*
 * Read a microphone - value is zero-level set
 */
int readMic(int pin){
	return abs((analogRead(pin) - 511));
}
/*
 * Get distance (cm) from a SRF05 -- http://www.robot-electronics.co.uk/htm/arduino_examples.htm
 */
int getDistanceSonar() {
	digitalWrite(TRIGPIN, LOW); // Set the trigger pin to low for 2uS
	delayMicroseconds(2);
	digitalWrite(TRIGPIN, HIGH); // Send a 10uS high to trigger ranging
	delayMicroseconds(10);
	digitalWrite(TRIGPIN, LOW); // Send pin low again
	int pulse = pulseIn(ECHOPIN, HIGH); // Read in times pulse
	return (pulse / 58);
}
/*
 * Get distance from a Sharp 2D120X IR Ranger
 */
int getDistanceIR() {
	return 0;
}

/*
 * Calculate the moving average of the microphone 0L 1R
 */
long micStore[2];
//int thisValue;
int toStore[2];
int movAvg[2];
int sampleCount, ij;
int lastValue[2], firstValue[2];
int* micAveraging() {
	if (avgFirstRun) {
		micStore[0] = micStore[1] = 0;
		//get the first 300 samples
		for (ij = 0; ij < 150; ij++) {
			Serial.println("FIRST RUN");
			micStore[0] += readMic(MICLEFT);
			micStore[1] += readMic(MICRIGHT);
            //wait some time
			delayMicroseconds(5);
		}
		avgFirstRun = false;
	}
	//stores
	micStore[0] += readMic(MICLEFT);
	micStore[1] += readMic(MICRIGHT);
    //rude approximation
	micStore[0] -= micStore[0]/150;
	micStore[1] -= micStore[1]/150;
    //ready to be sent back
	movAvg[0] = micStore[0] / 150;
	movAvg[1] = micStore[1] / 150;
    //return the array
	return movAvg;
}
/*
 * Detect loud sounds and pull a trigger
 */
int *micBuffer;
float iRep[2];
long smS[2] = { 0, 0 };
int c;
void computeMicDifference() {
	//call the mobileaveraging function
	micBuffer = micAveraging();
	//set the ratios
	for (c = 0; c < 15; c++) {
		smS[0] += readMic(MICLEFT);
		smS[1] += readMic(MICRIGHT);
	}
	iRep[0] = (smS[0] / 15) / micBuffer[0];
	iRep[1] = (smS[1] / 15) / micBuffer[1];

	 /*Serial.print(smS[0]/15);
	 Serial.println();
	 Serial.print("   ");
	 Serial.print(smS[1]/30);
	 Serial.print("  AND  ");
	 Serial.print(micBuffer[0]);
	 Serial.print("   ");
	 Serial.print(micBuffer[1]);
	 Serial.print("  AND  ");
	 Serial.print(iRep[0]);
	 Serial.print("   ");
	 Serial.print(iRep[1]);
	 Serial.println();*/

	smS[0] = 0;
	smS[1] = 0;
	if ((iRep[0] - iRep[1]) > 2) {
		triggerSound(0);
		Serial.println("************************GIRO SX");
		delay(500);

	} else if ((iRep[1] - iRep[0]) > 2) {
		triggerSound(1);
		Serial.println("************************GIRO DX");
		delay(500);

	}
}
