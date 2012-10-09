// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef robohead_H_
#define robohead_H_
#include "Arduino.h"
#include <math.h>
//Custom includes
#include <Servo.h>
extern bool avgFirstRun;
//extern Servo myServo;
extern Servo headMover;
//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//Defines and Prototypes
/********* PIN DESCRIPTION *********/
//Sonar pins
#define ECHOPIN 2                            // Pin to receive echo pulse
#define TRIGPIN 3                            // Pin to send trigger pulse
//RGB Led pins
#define RGBRED 5
#define RGBGREEN 6
#define RGBBLUE 9
//Normal leds
#define LEDLEFT 11
#define LEDRIGHT 12
//Microphones pins
#define MICLEFT A0
#define MICRIGHT A1
//Servo pin
#define SERVO 10

/********* PROTOTYPES *********/
//rgb.ino
void setupRGB(int, int, int);
void setRGBComponent(int, int);
//sensors.ino
int getDistanceSonar(void);
int getDistanceIR(void);
int* micAveraging(void);
void computeMicDifference(void);
//output.ino
void triggerSound(int);
//utils.ino
int multiMap(int,int*,int*,uint8_t);
//Do not add code below this line
#endif /* robohead_H_ */
