#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

// declaring where the toggle switches are connected in Arduino
int toggleSwitch01pin = 3;
int toggleSwitch02pin = A7;

// declaring where the leftHandside joystick is connected
int joystickLeft_VRxPin = A0;
int joystickLeft_VRyPin = A1;

// declaring where the rightHandside joystick is connected
int joystickRight_VRxPin = A2;
int joystickRight_VRyPin = A3;

RF24 radio(7,8);
const byte address[] = "node1";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.stopListening();
  Serial.begin(250000);
  pinMode(toggleSwitch01pin, INPUT);
  pinMode(toggleSwitch02pin, INPUT);

}

struct datapack{
  int toggleSwitch01 ;
  int toggleSwitch02 ;
  
  int joystickLeft_x ;
  int joystickLeft_y ;

  int joystickRight_x ;
  int joystickRight_y ;  
};
datapack data;

void loop() {
  data.toggleSwitch01 = map(analogRead(toggleSwitch01pin),0, 1023,0,255);
  data.toggleSwitch02 = map(analogRead(toggleSwitch02pin),0, 1023,0,255);

  data.joystickLeft_x = map(analogRead(joystickLeft_VRxPin), 0, 1023,0,255);
  data.joystickLeft_y = map(analogRead(joystickLeft_VRyPin), 0, 1023,0,255);

  data.joystickRight_x = map(analogRead(joystickRight_VRxPin) , 0, 1023,0,255); 
  data.joystickRight_y = map(analogRead(joystickRight_VRyPin) , 0, 1023,0,255);
  
  radio.write(&data, sizeof(data));
  Serial.print(data.joystickRight_x);
  Serial.print(" ");
  Serial.print(data.joystickRight_y);
  Serial.print(" ");
  Serial.print(data.toggleSwitch02);
  Serial.print(" ");
}
