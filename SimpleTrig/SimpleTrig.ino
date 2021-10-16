/*
This is a simpe trigger program, meant to read a sensor and start a signal for a given amount of time.

this is to replace using a pico-boo just to trigger a timed event


Developed by: James Manley

*/

//LIBRARIES
#include <RBD_Timer.h>  // https://github.com/alextaujenis/RBD_Timer
#include <RBD_button.h> // https://github.com/alextaujenis/RBD_Button

#define ttl HIGH // define wether the signal to the relay board is high or low
#define sig LOW // define whether the trigger pin is looking for a high or low signal to signify as on.


//timers
RBD::Timer standby(30000);
RBD::Timer ch1_Time(5000);

///^ Define system above ^///
//////////////////////////////////////////////////////////
/// V leave below code alone V ///

//inputs
// the input button is being defined within the setup loop due to changes in how it is handled bnased on the configuration settings.

//outputs
int LED_Armed = 13 ; // define the built in LED as the arming led for ststua updates
int ch_1 = 2; // define channel 1 pin

//global variables
int ledState = LOW;



void setup(){
  Serial.begin(9600);
  Serial.println("Begin Initialization");

  pinMode(ch_1, OUTPUT);
  digitalWrite(ch_1, !ttl);
  ch1_Time.onExpired();
  
  if(sig == HIGH){   /// the button event by default is looking for a pull to ground signal, this will changer it to a pull to high.
    RBD::Button trig(11, false); // button is defined here witht he internal pull up turned off for a high signal
    trig.invertReading();
  }
  else{
    RBD::Button trig(11); // if button is the normal pull to ground, then call it as normal
  }
  
  standby.restart();
  
}



void loop(){
   if(standby.isActive()){ // this script handles the flashing of the armed led to go progressively faster as it gets ready to arm.
    led.setTimeout( map(standby.getPercentValue(), 0, 100, 1000, 50)) ;
    if(led.onRestart()){
      ledState = !ledState;
      digitalWrite(LED_Armed, ledState);
    }
  }
  
  if(standby.onExpired()){
    Serial.println("Standby time has elapsed");
    digitalWrite(LED_Armed, HIGH);
  } 
 
  
  if(standby.isExpired() && trig.onPressed()){
    Serial.println("Button pressed, sequence started");
    digitalWrite(ch_1, ttl);
    ch1_Time.restart();
  }

  if(ch1_Time.onExpired()){
    digitalWrite(ch_1, !ttl);
  }

  
}
