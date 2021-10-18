/*
This is a simpe trigger program, meant to read a sensor and start a signal for a given amount of time. Meant to replace using a pico-boo just to trigger a timed event

This sketch can also be used as a template for making other programs following the same pin out and libraries.

Developed by: James Manley
contact: jamesmanley1992@gmail.com

Pinout Plan:
[0/1] TX/RX
[2-9] Relay 1-8
[11] Input Trigger
[13] Arming Status LED

*/


//LIBRARIES
#include <RBD_Timer.h>  // https://github.com/alextaujenis/RBD_Timer
#include <RBD_button.h> // https://github.com/alextaujenis/RBD_Button

////////////////////////////////////////////////////////////////
/// V Define System Below V ///

#define ttl HIGH // define wether the signal to the relay board is high or low

//timers
RBD::Timer standby(30000); // standby time is the amount of time after the affect stops before it can be run again.
RBD::Timer ch1_Time(5000); // the amount of time you want Ch_1 to be high before being set Low.


///^ Define system above ^///
//////////////////////////////////////////////////////////
/// V leave code Below alone V ///

//inputs
RBD::Button Trig(11);  // the trigger should be a pull to ground signal 

//outputs
int LED_Armed = 13 ; // define the built in LED as the arming led for ststua updates
int ch_1 = 2; // define channel 1 pin
 // these channels arent used in this simple program but they are lsited for reference if using this as a template
//int ch_2 = 3;
//int ch_3 = 4;
//int ch_4 = 5;
//int ch_5 = 6;
//int ch_6 = 7;
//int ch_7 = 8;
//int ch_8 = 9;


//global variables
int ledState = LOW; // used to keep track of the state of the arming LED, could also be used to make a relay follow the sequence.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////
///V- Sub Functions -V ///
//////////////////////////

void ArmBlink(){ // this script handles the flashing of the Built-In led to go progressively faster as it gets ready to arm. then leaves it on once ready
    if(standby.isActive()){ // while standby timer is active, continue flashing LED faster
    led.setTimeout( map(standby.getPercentValue(), 0, 100, 1000, 50)) ;
    if(led.onRestart()){
      ledState = !ledState;
      digitalWrite(LED_Armed, ledState);
    }
  }
  
  if(standby.onExpired()){ // once the standby timer has elapsed turn the Armed LED on
    Serial.println("Standby time has elapsed");
    Serial.println("System is Armed");
    ledState = HIGH;
    digitalWrite(LED_Armed, HIGH);
  }

  if(standby.isStopped()){ // while the program is executing turn the LED off.
    ledState = LOW;
    digitalWrite(LED_Armed, HIGH);
  } 
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////
///V-Main Functions-V///
//////////////////////// 

void setup(){
  Serial.begin(9600);
  Serial.println("Begin Initialization");

  pinMode(ch_1, OUTPUT);
  digitalWrite(ch_1, !ttl);
  ch1_Time.onExpired(); // declare the timer here to clear the .onExpired value before starting the main loop
  
  pinMode(Led_Armed, OUTPUT); // declaring the pin as an output helps make the built in led shine brighter
  
  standby.restart();
  
}

void loop(){
  
  if(standby.isExpired() && trig.onPressed()){ //what actions should be taken once the button is pressed, and the standby period has elapsed
    Serial.println("Button pressed, sequence started");
    digitalWrite(ch_1, ttl);
    ch1_Time.restart();
    standby.stop(); // while the event is happening, the standby timer is turned off to keep the arming LED off.
  }
  
///^ INPUT BASED EVENTS GO ABOVE ^///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///V TIMING BASED EVENTS GO BELOW V///

  ArmBlink(); // handles blinking led for arming status update
  
  if(ch1_Time.onExpired()){ // the first time after the timer expires this code will execute, but then it wont execute again until the timer is reset.
    Serial.println("Ch_1 turned off");
    digitalWrite(ch_1, !ttl);
    standby.restart(); // once the last step of the event has completed, start the standby timer, with blinking led
    Serial.println("Affect is finished, entering standby mode");
  }
}
