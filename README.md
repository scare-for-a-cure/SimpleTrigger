# SimpleTrigger
Simple Trigger handler using arduino

We want to try and use the octobanger standard when using the arduino

Trigger pin : 11

Relay 1-8 : pins 2-9


Examples:


**ch_1 time(1000) / standby time (1000) / motion detector. 

In this scenario, the affect is on for one second after the motion sensor is triggered, then off for one second, then if it is still seeing motion it will trigger on for 1 second again, and repeating until motion stops.

This affect is good, for things like misters, that you want to pulse while a group is still going through the effect.



**ch_1 time (1000) / standby time (60000) / motion sensor

In this scenario the affect is triggered for one second, but then wont be triggered again for 60 seconds.

This affect is good for wanting an affect to only trigger once, and waiting for the group to leave without triggering it again. typically for a quick jump scare style effect, or for triggering another device controller.
