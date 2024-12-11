/*
 * This is a 6 channel nrf24l01 transmitter and receiver code.
 * There are 6 outputs in the receiver end, of which 2 outputs are for led(on/off) and the remaining 4 outputs are for 4 leds with brigtness control.
 * 
 * To know more refer the below links:
 *  https://youtu.be/Pd7rus79j_4
 *  https://dhirajkushwaha.com/elekkrypt
 *  
 */
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

// declaring where the leds are connected in Arduino
int led01 = 2; // Led 01
int led02 = 4; // Led 02 

int led03 = 5; // Led 03 (with brightness control)
int led04 = 6; // Led 04 (with brightness control)
int led05 = 9; // Led 05 (with brightness control)
int led06 = 10; // Led 06 (with brightness control)

RF24 radio(7,8);
const byte address[] = "node1";

void setup() {
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.startListening();
  
  pinMode(led01, OUTPUT);
  pinMode(led02, OUTPUT);
  pinMode(led03, OUTPUT);
  pinMode(led04, OUTPUT);
  pinMode(led05, OUTPUT);
  pinMode(led06, OUTPUT);  

    
  Serial.begin(9600);
}

struct datapack{
  bool toggleSwitch01 ;
  bool toggleSwitch02 ;
  
  int joystickLeft_x ;
  int joystickLeft_y ;

  int joystickRight_x ;
  int joystickRight_y ;  
};
datapack data;

void loop() {
  while(radio.available()){
    radio.read(&data, sizeof(data));

    digitalWrite(led01, data.toggleSwitch01);
    digitalWrite(led02, data.toggleSwitch02);

    analogWrite(led03, data.joystickLeft_x);
    analogWrite(led04, data.joystickLeft_y);

    analogWrite(led05, data.joystickRight_x);
    analogWrite(led06, data.joystickRight_y);

  }
}
