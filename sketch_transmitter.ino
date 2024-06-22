//Transmitter Code (Glove) - Mert Arduino and Tech

#include <SPI.h>                      //the communication interface with the modem
#include "RF24.h"                     //the library which helps us to control the radio modem

int msg[5]; //Total number of data to be sent (data package)

//define the flex sensor input pins
int flex_5 = A5;
int flex_4 = A4;
int flex_3 = A3;
int flex_2 = A2;
int flex_1 = A1;

//define variables for flex sensor values
int flex_5_val;
int flex_4_val;
int flex_3_val;
int flex_2_val;
int flex_1_val;

RF24 radio(9,10);                     //9 and 10 are a digital pin numbers to which signals CE and CSN are connected.
const int flexPin = A5;			// Pin connected to voltage divider output                                      
const uint64_t pipe = 0xE8E8F0F0E1LL; //the address of the modem, that will receive data from Arduino.
const float VCC = 5;			// voltage at Ardunio 5V line
const float R_DIV = 47000.0;	// resistor used to create a voltage divider
const float flatResistance = 25000.0;	// resistance when flat
const float bendResistance = 100000.0;	// resistance at 90 deg

void setup(void){
  
  Serial.begin(9600);
  pinMode(flexPin, INPUT);
  radio.begin();                      //it activates the modem.
  radio.openWritingPipe(pipe);        //sets the address of the receiver to which the program will send data.
}

void loop(void){
	// Read the ADC, and calculate voltage and resistance from it
	int ADCflex = analogRead(flexPin);
	float Vflex = ADCflex * VCC / 1023.0;
	float Rflex = R_DIV * (VCC / Vflex - 1.0);
	Serial.println("Resistance: " + String(Rflex) + " ohms");

	// Use the calculated resistance to estimate the sensor's bend angle:
	float angle = map(Rflex, flatResistance, bendResistance, 0, 90.0);
	Serial.println("Bend: " + String(angle) + " degrees");
	Serial.println();

	delay(500);
  flex_5_val = analogRead(flex_5); 
  flex_5_val = map(flex_5_val, 630, 730, 80, 20);
  
  flex_4_val = analogRead(flex_4);
  flex_4_val = map(flex_4_val, 520, 710, 70, 175);
 //
  //flex_3_val = analogRead(flex_3);
  //flex_3_val = map(flex_3_val, 510, 680, 140, 10);
 //
  //flex_2_val = analogRead(flex_2);
  //flex_2_val = map(flex_2_val, 580, 715, 90, 175);
  //
  //flex_1_val = analogRead(flex_1);
  //flex_1_val = map(flex_1_val, 550, 700, 90, 175);
  
  msg[2] = flex_4_val;
  msg[1] = flex_5_val;
  //msg[3] = flex_3_val;
  //msg[4] = flex_2_val;
  //msg[5] = flex_1_val;
  radio.write(msg, sizeof(msg));
}

