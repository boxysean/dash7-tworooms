/*
AC Light Control
 
 Updated by Robert Twomey <rtwomey@u.washington.edu>
 
 Changed zero-crossing detection to look for RISING edge rather
 than falling.  (originally it was only chopping the negative half
 of the AC wave form). 
 
 Also changed the dim_check() to turn on the Triac, leaving it on 
 until the zero_cross_detect() turn's it off.
 
 Adapted from sketch by Ryan McLaughlin <ryanjmclaughlin@gmail.com>
 http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1230333861/30
 
 */

#include <TimerOne.h>           // Avaiable from http://www.arduino.cc/playground/Code/Timer1

volatile int i[4]= { 0, 0, 0, 0 };               // Variable to use as a counter
volatile boolean zero_cross[4]= { 0, 0, 0, 0 };  // Boolean to store a "switch" to tell us if we have crossed zero

//int AC_pin[4] = { 3, 5, 6, 9 };                // Output to Opto Triacint dim = 0;                    // Dimming level (0-128)  0 = on, 128 = 0ff
int AC_pin[4] = { 9, 6, 5, 3 };                // Output to Opto Triacint dim = 0;                    // Dimming level (0-128)  0 = on, 128 = 0ff
int dim[4] = { 0, 0, 0, 0 };                     // Dimming level (0-128)  0 = on, 128 = 0ff
int inc[4] = { 1, 1, 1, 1 };                      // counting up or down, 1=up, -1=down

int freqStep = 65;    // This is the delay-per-brightness step in microseconds.
// It is calculated based on the frequency of your voltage supply (50Hz or 60Hz)
// and the number of brightness steps you want. 
// 
// The only tricky part is that the chopper circuit chops the AC wave twice per
// cycle, once on the positive half and once at the negative half. This meeans
// the chopping happens at 120Hz for a 60Hz supply or 100Hz for a 50Hz supply. 

// To calculate freqStep you divide the length of one full half-wave of the power
// cycle (in microseconds) by the number of brightness steps. 
//
// (1000000 uS / 120 Hz) / 128 brightness steps = 65 uS / brightness step
//
// 1000000 us / 120 Hz = 8333 uS, length of one half-wave.

void setup() {                                      // Begin setup
  for (int j = 0; j < 4; j++) {
    pinMode(AC_pin[j], OUTPUT);
  }
  attachInterrupt(0, zero_cross_detect, RISING);   // Attach an Interupt to Pin 2 (interupt 0) for Zero Cross Detection
  Timer1.initialize(freqStep);                      // Initialize TimerOne library for the freq we need
  Timer1.attachInterrupt(dim_check, freqStep);      
  // Use the TimerOne Library to attach an interrupt
  // to the function we use to check to see if it is 
  // the right time to fire the triac.  This function 
  // will now run every freqStep in microseconds.                                            
}

void zero_cross_detect() {    
  for (int j = 0; j < 4; j++) {
    zero_cross[j] = true;
    i[j] = 0;
    digitalWrite(AC_pin[j], LOW);
  }
}                                 

// Turn on the TRIAC at the appropriate time
void dim_check() {                   
  for (int j = 0; j < 4; j++) {
    if(zero_cross[j] == true) {              
      if(i[j]>=dim[j]) {                     
        digitalWrite(AC_pin[j], HIGH); // turn on light       
        i[j]=0;  // reset time step counter                         
        zero_cross[j] = false; //reset zero cross detection
      } 
      else {
        i[j]++; // increment time step counter                     
      }
    }
  }                                  
}                    

int counter = 0;

int nWave = 32;
byte wave[] = { 3,7,11,15,19,23,27,31,35,39,43,47,51,55,59,63,67,71,75,79,83,87,91,95,99,103,107,111,115,119,123,127 };

int nOrder = 100;
byte order[] = { 0,1,3,0,2,0,1,3,1,2,3,1,2,1,2,1,2,3,0,3,1,3,0,1,0,3,1,0,1,2,3,1,3,0,2,3,1,3,1,3,1,3,2,0,3,2,1,0,2,0,2,3,0,3,1,2,1,2,3,2,3,1,0,2,3,0,3,2,0,1,2,0,3,1,0,2,1,0,1,0,3,1,0,2,1,3,1,2,1,3,1,2,1,0,1,3,0,3,1,2 };

int orderIdx = 0;

void loop() {
  for (int j = 0; j < nOrder; j++) {
    for (int k = 0; k < nWave; k++) {
      dim[order[j]] = wave[k];
      delay(18);
    }
  }
}


