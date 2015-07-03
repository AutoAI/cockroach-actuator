# baja-actuator 
This is an arduino project that interfaces with DriveAI-Platform and actuates the vehicle accordint to the commands passed to it via serial. 

It will be expecting the following over serial:
* acceleration information: `float [-1, 1]`
* steering information: `float [-1, 1]`

It will provide other useful information to the Platform about the vehicle's state. Things such as: `vehicle speed`.
