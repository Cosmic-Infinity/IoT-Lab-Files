this project works alongside VJoy driver to emulate gyroscope input of joysticks.
Infact, it can have upto 3-axis of control (2 used in this case) to control more aspects of the game than just direction.

Check status of working in
vJoySerialFeeder > Program > Game Controller > Properties

The code is compliant with ADXL345 accelerometer. 
Yes, although we say gyroscope, we actually use an accelerometer in this application, since the accelerometers give us a 
constant state update in all 3 axes (the type required in say, a racing game's left right tilt), 
unlike gyroscope which gives us the instantaneous change if the device changes it's orientation.