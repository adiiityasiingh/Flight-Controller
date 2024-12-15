# Flight-Controller
# 1. Introduction
This Arduino sketch provides a flight controller for an X quadcopter based on an Arduino Uno board and the MPU6050 sensor.

Basically, this automation routine is an implementation of a digital PID with a refresh rate of 250Hz. The method used to calculate PID coefficients is Ziegler Nichols method. The frame of the quadcopter is based on the F450.

(i) Currently under active development.

# 2. Mapping
       +-------------------------+
       |        MPU-6050         |
       |                         |
       | 3V3  SDA  SCL  GND  INT |
       +--+----+----+----+----+--+
          |    |    |    |
          |    |    |    |
+---------+----+----+----+----------------+
|        3.3V  A4   A5  GND               |
|                                         |
|                                         |
|                 Arduino Uno             |
|                                         |
| #4   #5   #6   #7   #8   #9  #10   #11  |
+--+----+----+----+----+----+----+----+---+
   |    |    |    |    |    |    |    |
  (M1) (M2) (M3) (M4)  |    |    |    |
                       |    |    |    |  
                       |    |    |    |
                    +--+----+----+----+---+
                    | C1   C2   C3   C4   |
                    |                     |
                    |     RF Receiver     |
                    +---------------------+
  
Legend:
Mx: Motor X
Cx: Receiver channel x
The channel mapping is then:

Channel	Command
1	ROLL
2	PITCH
3	THROTTLE
4	YAW
To change the channel mapping, update the function configureChannelMapping according to your needs:
void configureChannelMapping() {
    mode_mapping[YAW]      = CHANNEL4;
    mode_mapping[PITCH]    = CHANNEL2;
    mode_mapping[ROLL]     = CHANNEL1;
    mode_mapping[THROTTLE] = CHANNEL3;
}

# 3. Start/Stop
This sketch comes with a safety process: to start the quadcopter, move the left stick of the remote in the bottom left corner. Then move it back in center position.

To stop the quadcopter, move the left stick in the bottom right corner.
