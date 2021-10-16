//LIBRARIES
#include <RBD_Timer.h>  // https://github.com/alextaujenis/RBD_Timer

#define ttl HIGH // define wether the signal to the relay board is high or low

//outputs
int ch_1 = 2; // define channel 1 pin

//inputs
//int trigger = 11 ; 

//button
EBD::Button trig = 11;

//timers
RBD::Timer standby(30000);
RBD::Timer ch1_Time(5000);

void setup(){
  Serial.begin(9600);
  Serial.println("Begin Initialization");

  pinMode(ch_1, OUTPUT);
  digitalWrite(ch_1, !ttl);
  ch1_Time.onExpired();
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
