# baja-actuator 
This is an arduino project that interfaces with DriveAI-Platform and actuates the vehicle accordint to the commands passed to it via serial. 

It will be expecting the following over serial:
*One encoded byte per update: `0xTTRRRRRR`
Wherein the first two bits marked *T* will address which control is being modified, and the six *R* bits that follow are used to set the selected control from 0-63, unsigned.

It will provide other useful information to the Platform about the vehicle's state. Things such as: `vehicle speed`.
