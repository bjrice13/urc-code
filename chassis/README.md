# drive

# Dependencies:
- roboteq_driver (http://wiki.ros.org/roboteq_driver)
- *Note: roboteq_driver requires serial (https://github.com/wjwwood/serial.git)*
        *and aparantly python got renamed to python2.7 or python3 in Ubuntu 20.04,*
        *so if you use 20.04, * `sudo apt-get install python-is-python3`
        *Also: roboteq was using Python 2, so you must fix the file *
        `./roboteq_driver/mbs/genc` to have the following Python 3 lines:
        
        
 ```python
 #!/usr/bin/env python

from sys import argv

print ("const char* ", argv[1], "[] = {")
with open(argv[2]) as f:
    for line in f.readlines():
        print ('  "', line.strip(), '",')
print ("  0")
print ("};")
```

Author: Brandon Rice

Description: This package contains the code necessary to drive
the chassis of the 2019-2020 Sun Devil Robotics Club Mock Mars
Rover.


Use: To use, make sure both RoboteQ motor controllers and a
primary joystick are plugged into the microcontroller/laptop
running ROS. The tested configuration is one motor controller
and the joystick in the USB hub, plugged into one USB port.
The other motor controller is plugged into a remaining USB
port.

Then, simply run the teleop.launch file. This will set up two
Serial objects, one to /dev/ttyACM0 (the first recognized
motor controller) and one to /dev/ttyACM1 (the second motor
controller). The core method that is ran is Chassis::update(),
which manages a subscriber node on the topic /j0 (the joystick
input information) and sends the left and right axes data to
the correct RoboteQ serial commands (!G) for a tank/differential
drive scheme.

See chassis.h for more information.


Debugging: If the motor controllers and axes are inverted (left
stick controls the right motors), try reversing the USB ports
that the motor controllers are plugged into.
