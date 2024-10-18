This is a simple proto type magnetic loop antenna automatically tune project.
The code can be edit and build with Adunino.

There are somethings that I tried to implemented: 
  1) This stepper motor controller, after some search , finnaly I choose the motor driver chip TMC2209, It has the special function named "sensorless stall detection", which is definitely good 
for Vaccume capacitor because we have no good method to add the physical position limit sensor.
  2) The SWR meter. I use SI5351 act as the signal source and 2 AD8307 chips act as the forard and revese power meter to calculate the SWR.  
