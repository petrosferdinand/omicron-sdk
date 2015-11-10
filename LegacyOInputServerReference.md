<p><b>Last revision:</b> ver. 0.6<font color='#ff0000'> (The contents of this document are deprecated and / or need revision)</font></p>

#summary Documentation of OInputServer and NetService datagrams.
#sidebar Sidebar

# Introduction #

## Connecting ##
  1. Open a tcp connection on port 27000 to the computer running oinputserver.
  1. Send a string specifiying the port you'd like to receive data on. For example:  "data\_on,27001 " You can replace 27001 with the port number of your choice.
  1. Close the tcp connection
  1. Open a udp connection to the port you previously specified (27001 in this example)
  1. Start listening for packets and parse them as they arrive

## Datagram Structure ##
Datagrams are a string of the following format: '{Service Type}:{Event Type},{Source ID},{Param1},...,{ParamN} '

The number of parameters depends on the service type. Event Type is not always used so make sure to check the documentation for the device you want to use. Note the trailing space at the end of the datagram. Source ID is a unique identifier for that touch, rigid body, controller, etc. Service and event types are described below.

### Service Types ###

Each service type is defined as follows:

0: Pointer

1: Mocap

2: Keyboard

3: Controller

4: Ui

5: Generic

6: NeuroSky

The current enumeration is found in include/omega/Service.h


### Event Types ###

Each event type is defined by an enumeration. (See include/omega/Event.h)

0: Select

1: Toggle

2: ChangeValue

3: Update

4: Move

5: Down

6: Trace

7: Untrace

8: Click

9: DoubleClick

10: MoveLeft

11: MoveRight

12: MoveUp

13: MoveDown

14: Zoom

15: SplitStart

16: SplitEnd

17: Split

18: RotateStart

19: RotateEnd

20: Rotate

21: Null


## Pointer Datagram ##

There are three kinds of pointer datagrams: mouse, touch point, and touch gesture.

### <u> Mouse </u> ###
'0:{Event Type},{Source ID},{X Position},{Y Position} '


### <u> Touch Point </u> ###
'0:{Event Type},{Source ID},{X Position},{Y Position},{X Width},{Y Width} '

### <u> Touch Gestures </u> ###
Touch gestures parameters depend on the event type. See Event ID Types below for a listing of all event types.

#### Touch Down / Move / Up / Click / Move ####
This applies for Click, DoubleClick, MoveRight, MoveUp, MoveLeft, and MoveDown.

'0:{Event Type},{X Position},{Y Position} '

#### SplitStart / SplitEnd ####
Denotes the beginning or end of a two finger split/zoom gesture and lists the coordinates of each finger. X3 and Y3 are the midpoints of position 1 and 2.

'0:{Event Type},{Source ID},{X3 Position},{Y3 Position},{X2 Position},{Y2 Position},{X1 Position},{Y1 Position} '

#### Split ####
A two finger split/zoom gesture. Lists the coordinates of each finger, delta distance, and delta ratio. X3 and Y3 are the midpoints of position 1 and 2.

'0:{Event Type},{Source ID},{X3 Position},{Y3 Position},{X2 Position},{Y2 Position},{X1 Position},{Y1 Position},{Delta distance},{Delta ratio} '

#### Rotate Start/End ####
Denotes the start/end of a two finger rotation gesture. One finger (anchor) is stationary while the other rotates around it. The X,Y position is the center of rotation/anchor.

'0:{Event Type},{X Position},{Y Position},{Anchor X},{Anchor Y},{Rotating X},{Rotating Y} '

#### Rotate ####
A two finger rotation gesture. One finger (anchor) is stationary while the other rotates around it. The X,Y position is the center of rotation/anchor. Angle is in radians.

'0:{Event Type},{Source ID},{X Position},{Y Position},{Anchor X},{Anchor Y},{Rotating X},{Rotating Y},{Angle} '


## Mocap Datagram ##

'1:{Source ID},{X Position},{Y Position},{Z Position},{X},{Y},{Z},{W} '

The position origin is dependent on the origin of the tracking system that is used. X, Y, Z, W is a quaternion that gives the orientation of the object.

## Controller Datagram ##

Controller datagrams depend of the controller type: Xbox 360, PS3, Wiimote.

Controller Type ID:

0: Xbox 360

1: PS3 Sixaxis

2: Wiimote

3: Wii Nunchuk

4: Wii MotionPlus


### Xbox 360 Datagram ###

'3:{Source ID},0,{Left analog left/right},{Left analog up/down},{Right analog left/right},{Right analog up/down},{Triggers},A,B,X,Y,LB,RB,Back,Start,LA,RA,0,0,0,0,0,DPAD,0,0 '

Analog stick values range from -1000 to 1000 where negative is left or up. Thus a value of 1000 would represent an analog stick moved fully to the right or down.

The trigger value ranges from -1000 to 1000. In this case, pressing the left trigger will set the value from 0 to 1000, the right trigger will set the value from 0 to -1000. Not pressing the triggers or fully pressing down on both will result in a value of 0.

The button fields (A,B,X,Y,LB,RB,Back,Start,LA,RA) will either be 0 (not pressed) or 1 (pressed). LA and LR stand for the left/right analog trigger buttons.

The DPAD values are as follows:
  * Negative: Not pressed
  * 0: Up
  * 4500: Up-Right
  * 9000: Right
  * 13500: Right-Down
  * 18000: Down
  * 22500: Left-Down
  * 27000: Left
  * 31500: Up-Left

### PS3 Sixaxis Datagram ###

**Note:** PS3 controller support requires MotioninJoy.

'3:{Source ID},1,{Left analog left/right},{Left analog up/down},{Right analog left/right},{Right analog up/down},{Triggers},Cross,Circle,Square,Triangle,L1,[R1](https://code.google.com/p/omicron-sdk/source/detail?r=1),Select,Start,L3,[R3](https://code.google.com/p/omicron-sdk/source/detail?r=3),PS Button,Up,Down,DPAD,Roll,Pitch '

Analog stick values range from -1000 to 1000 where negative is left or up. Thus a value of 1000 would represent an analog stick moved fully to the right or down.

The trigger value ranges from -1000 to 1000. In this case, pressing the left trigger will set the value from 0 to 1000, the right trigger will set the value from 0 to -1000. Not pressing the triggers or fully pressing down on both will result in a value of 0.

The button fields (Cross,Circle,Square,Triangle,L1,[R1](https://code.google.com/p/omicron-sdk/source/detail?r=1),Select,Start,L3,[R3](https://code.google.com/p/omicron-sdk/source/detail?r=3),PS Button,Up,Down) will either be 0 (not pressed) or 1 (pressed). L3 and [R3](https://code.google.com/p/omicron-sdk/source/detail?r=3) are the analog stick buttons.

The DPAD values are as follows. **Note:** This is different from the Xbox:
  * Negative: Not pressed
  * 0: Up
  * 4500: **No data**
  * 9000: Down
  * 13500: Left-Down
  * 18000: Left
  * 22500: **No data**
  * 27000: Right
  * 31500: Up-Right

The Roll value range from -1000 to 1000. Where positive is tilting to left.

The Roll value range from -1000 to 1000. Where positive is tilting to up toward the player.

### Wiimote Datagram ###

Wiimote integration is provided by WiiYourself! by gl.tter

'3:{Source ID},2,Battery,Acceleration X,Acceleration Y,Acceleration Z,A,B,Plus,Home,Minus,One,Two,Up,Down,Left,Right,IR Mode,IR0 valid,IR0 X, IR0 Y,IR1 valid,IR1 X, IR1 Y,IR2 valid,IR2 X, IR2 Y,IR3 valid,IR3 X, IR3 Y '

Battery is the approximate battery percent ranging from 0 to 100.

Acceleration values are integers where 1000 is the force of gravity. X represents motion to the left and right (right+). Y represents motion forward and back (forward+). Z represents motion up and down (down+). Thus an acceleration value of 0,0,1000 represents a Wiimote on a flat surface with the buttons facing up.

The button fields (A,B,Plus,Home,Minus,One,Two,Up,Down,Left,Right) will either be 0 (not pressed) or 1 (pressed).

IR Mode - The type of data being sent:
  * 0 - Off (No IR sources detected)
  * 1 - Basic (Sending IR dot positions)
  * 2 - Extended (Basic data + size) **Currently giving basic data only**
  * 5 - Full (Extented data + blob bounding box) **Not currently supported**

Each of the IR data is the x,y position of the dot from 0 - 1000. A dot a 0,0 indicates the Wiimote sees an IR dot at the lower left corner of it's field of view - thus the Wiimote pointing to the upper right of the sensor bar. Likewise pointing to the lower left of the sensor bar would have a dot near 1000,1000.

The IR valid fields are either 0 or 1. Each IR point should only be used when the corresponding valid flag is 1.

### Wii Nunchuk Datagram ###

'3:{Source ID},3,Analog X,Analog Y,Acceleration X,Acceleration Y,Acceleration Z,C,Z '

Analog stick values range from -1000 to 1000 where negative is left or up. Thus a value of 1000 would represent an analog stick moved fully to the right or down.

Acceleration values are integers where 1000 is the force of gravity. X represents motion to the left and right (right+). Y represents motion forward and back (forward+). Z represents motion up and down (down+). Thus an acceleration value of 0,0,1000 represents a Wiimote on a flat surface with the buttons facing up.

The button fields (C,Z) will either be 0 (not pressed) or 1 (pressed).

### Wii MotionPlus Datagram ###

'3:{Source ID},4,Yaw,Pitch,Roll '

Pitch, Roll, and Yaw represent the acceleration data from the Wii MotionPlus extension.

### NeuroSky ThinkGear Datagram ###

'6:{Source ID},signal,attention,meditation,delta,lowAlpha,highAlpha,lowBeta,highBeta,lowGamma,highGamma,blink '

Signal: The quality of the signal from the device. 0 is optimal, 1-199 is poor, 200 is no signal.
Attention/Meditation: Ranges from 0-100.
The other EEG waves can range from 0 to approximately 3,000,000 based on brain activity.
Blink is typically from 0 to approximately 255. Typically normal activity is below 100 while blinking is above 100 based on how hard you blink.