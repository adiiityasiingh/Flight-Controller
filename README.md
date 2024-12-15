# Flight-Controller

![IMG-20241208-WA0014](https://github.com/user-attachments/assets/1a0d5809-0d89-47df-b9db-349669224b2f)

# 1. Introduction
This Arduino sketch provides a flight controller for an X quadcopter based on an Arduino Uno board and the MPU6050 sensor.

Basically, this automation routine is an implementation of a digital PID with a refresh rate of 250Hz. The method used to calculate PID coefficients is Ziegler Nichols method. The frame of the quadcopter is based on the F450.

(i) Currently under active development.

# 2. Requirements
- 1 x 450 size frame with integrated power distribution board
- 4 x 1000kV motor / 10x4.5 props / ESC combo
- 1 x 3S / 2200mAh / 20C lipo
- 1 x Arduino Uno or Funduino Uno
- 1 x MPU-6050 gyro / accelerometer
- 1 x Flysky FS-i6 6-CH TX Transmitter
- 1 x 2S/3S lipo battery charger

# 3. Mapping
```
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
```
 # 4. Configuration
 ## 4.1 Remote configuration
By default, this sketch uses the mode 2 for RF remote, according to the following picture:


The channel mapping is then:

| Channel  | Command |
| -------- | ------- |
| 1        |   ROLL  |
| 2        |  PITCH  |
| 3        |THROTTLE |
| 4        |   YAW   |

	     	
To change the channel mapping, update the function configureChannelMapping according to your needs:
```c
void configureChannelMapping() {
    mode_mapping[YAW]      = CHANNEL4;
    mode_mapping[PITCH]    = CHANNEL2;
    mode_mapping[ROLL]     = CHANNEL1;
    mode_mapping[THROTTLE] = CHANNEL3;
}
```
## 4.2 PID tuning
The default PID coeffcient values might work for an F450-like quadcopter. However, you can tune them in the global variable declaration section:
```c
// PID coefficients
float Kp[3] = {4.0, 1.3, 1.3};    // P coefficients in that order : Yaw, Pitch, Roll
float Ki[3] = {0.02, 0.04, 0.04}; // I coefficients in that order : Yaw, Pitch, Roll
float Kd[3] = {0, 18, 18};        // D coefficients in that order : Yaw, Pitch, Roll
```
# 5. Quadcopter orientation
```
 Front
(1) (2)     x
  \ /     z ↑
   X       \|
  / \       +----→ y
(3) (4)
```
- Motor 1: front left - clockwise
- Motor 2: front right - counter-clockwise
- Motor 3: rear left - clockwise
- Motor 4: rear left - counter-clockwise

![68747470733a2f2f7777772e666972656469792e66722f696d616765732f61727469636c65732f64726f6e65362f72656d6f74655f6d6f6465732e6a7067](https://github.com/user-attachments/assets/b657de5b-1e29-4744-a4d7-b99086c08ce2)


- Left wing up implies a positive roll
- Nose up implies a positive pitch
- Nose right implies a positive yaw
  <br><br>
  The MPU6050 must be oriented as following:

- X axis: roll
- Y axis: pitch
- Z axis: yaw

# 6. Start/Stop
This sketch comes with a safety process: to start the quadcopter, move the left stick of the remote in the bottom left corner. Then move it back in center position.

To stop the quadcopter, move the left stick in the bottom right corner.

![start_stop](https://github.com/user-attachments/assets/4af27849-496e-4ba7-b603-0a56d5e5ade7)


# 7. Debug
If you need to print debug messages, make sure to init Serial at 57600 bauds:
```c
void setup() {
  Serial.begin(57600);
  // ...
}

void loop() {
  Serial.println(measures[ROLL]);
  // ...
}
```
