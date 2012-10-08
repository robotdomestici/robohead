#include "robohead.h"

//get the distance (cm) from a SRF05
int getDistanceSonar(){
  digitalWrite(TRIGPIN, LOW);                   // Set the trigger pin to low for 2uS
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);                  // Send a 10uS high to trigger ranging
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);                   // Send pin low again
  int pulse = pulseIn(ECHOPIN, HIGH);        // Read in times pulse
   return (pulse/58);
}

int getDistanceIR() {
return 0;
}
//calculates the moving average of the microphone 0L 1R
int micStore[2]; int thisValue; int toStore[2]; int movAvg[2]; int sampleCount, ij; int lastValue[2], firstValue[2];
int* micAveraging() {
	if (avgFirstRun) {
		micStore[0]=micStore[1]=0;
		firstValue[0] = log(pow((analogRead(MICLEFT)-512),2));
		firstValue[1] = log(pow((analogRead(MICRIGHT)-512),2));
	//get the first 300 samples
	 for(ij=0; ij<300; ij++){
			//thisValue = analogRead(MICLEFT);
			micStore[0] += log(pow((analogRead(MICLEFT)-512),2));
			micStore[1] += log(pow((analogRead(MICRIGHT)-512),2));
			delayMicroseconds(15);
		}
	 avgFirstRun = false;
	}
    lastValue[0] = log(pow((analogRead(MICLEFT)-512),2));
    lastValue[1] = log(pow((analogRead(MICRIGHT)-512),2));
    //calculate the average
	toStore[0] =  log(pow((analogRead(MICLEFT)-512),2));
	toStore[1] =  log(pow((analogRead(MICRIGHT)-512),2));

	//stores the average
	movAvg[0] = micStore[0] /302; 	movAvg[1] = micStore[1] /302;

	//rude approximation
	micStore[0] += toStore[0] - movAvg[0]; 	micStore[1] += toStore[1] - movAvg[1];

	//stores the average
	//movAvg[0] = micStore[0] /302; 	movAvg[1] = micStore[1] /302;

    return movAvg;
}
