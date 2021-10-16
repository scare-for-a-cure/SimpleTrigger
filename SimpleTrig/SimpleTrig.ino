/*
This is a simpe trigger program, meant to read a sensor and start a signal for a given amount of time.

this is to replace using a picoboo just to trigger a timed event


Developed by: James Manley

*/




//LIBRARIES
#include <RBD_Timer.h>  // https://github.com/alextaujenis/RBD_Timer

#define ttl HIGH // define wether the signal to the relay board is high or low
#define sig LOW // define whether the trigger pin is looking for a high or low signal to signify as on.


//timers
RBD::Timer standby(30000);
RBD::Timer ch1_Time(5000);

///^ Define system above ^///
//////////////////////////////////////////////////////////
/// V leave below code alone V ///


//outputs
int ch_1 = 2; // define channel 1 pin

//inputs
//int trigger = 11 ; 




void setup(){
  Serial.begin(9600);
  Serial.println("Begin Initialization");

  pinMode(ch_1, OUTPUT);
  digitalWrite(ch_1, !ttl);
  ch1_Time.onExpired();
  
  pinMode(trigger, INPUT);
  if(sig == HIGH){   /// the button event by default is looking for a pull to ground signal, this will changer it to a pull to high.
    RBD::Button trig(11, false); // button is defined here witht he internal pull up turned off for a high signal
    trig.invertReading();
  }
  else{
    RBD::Button trig(11, false); // if button is the normal pull to ground, then call it as normal
  }
  
  standby.restart();
  
}



void loop(){
//  if(standby.isExpired() && digitalRead(trigger)){
    if(standby.isExpired() && trig.onPressed()){
    digitalWrite(ch_1, ttl);
    ch1_Time.restart();
  }

  if(ch1_Time.onExpired()){
    digitalWrite(ch_1, !ttl);
  }

  
}
