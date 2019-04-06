#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();
// Variable set up
const int player1button = 12; //Assign variable name to input pin
const int player2button = 11; //Assign variable name to input pin
int value=0; // The four digit value that will be sent to the display
int player1score=0; // Player 1's score
int player2score=0; // Player 2's score

void setup() {
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
pinMode(13, OUTPUT); //Built in LED
pinMode(player1button, INPUT); //Push button 1
digitalWrite(player1button, INPUT_PULLUP); //Enable pull up resistor on Pin 12
pinMode(player2button, INPUT); // Push button 2
digitalWrite(player2button, INPUT_PULLUP); //Enable pull up resistor on Pin 11
matrix.begin(0x70);
}

void loop() {
int buttonState1 = digitalRead(player1button); //Read and store state of push button 1
int buttonState2 = digitalRead(player2button); // Read and store state of push button 2


 if (buttonState1 != 1) {;  // If pin 12 is not high, then button is pressed...
    player1score++; //Increment button score
    delay(300); // Short delay for button debounce
  }

//Identical to button 1 immediately above, just for button 2
 if (buttonState2 != 1) {;  // If pin 11 is not high, then button is pressed...
    player2score++;
    delay(300); // Short delay for button debounce
  }

//value = (player1score*100)+(player2score); // Multiply player 1's number by 100 and put both numbers into a four digit integer
//matrix.print(value); // Print the value
matrix.writeDigitNum(2, 1); // Enable (1) the colon separator LED (digit 2)

/*
if (value < 10) { // If value < 10, add three leading zeroes
matrix.writeDigitNum(0, 0);
matrix.writeDigitNum(1, 0);
matrix.writeDigitNum(3, 0);
}
else if (value < 100) { // Continue adding leading zeroes...
matrix.writeDigitNum(0, 0);
matrix.writeDigitNum(1, 0);
}
else if (value < 1000) { // Continue adding leading zeroes...
matrix.writeDigitNum(0, 0);
}
else {  
}
*/


if (player1score > 9){
matrix.writeDigitNum(0, 1);
matrix.writeDigitNum(1, player1score-10);
}
else {
matrix.writeDigitRaw(0, 0);
matrix.writeDigitNum(1, player1score);
}
if (player2score > 9){
matrix.writeDigitNum(3, 1);
matrix.writeDigitNum(4, player2score-10);  
}
else {
matrix.writeDigitRaw(3, 0);
matrix.writeDigitNum(4, player2score);
}

matrix.writeDisplay(); // I guess this writes everything to the display

if  ((player1score > 11) || (player2score > 11)) { // Once a player exceeds 11 then reset to zero to start a new game
player1score=0;
player2score=0;
}
else {
}

}
