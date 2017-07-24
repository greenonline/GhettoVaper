#include "mButton.h"
#include "LiquidCrystalFast.h"
#include <EEPROM.h>
#include <avr/pgmspace.h>


/*
 
 The circuit:
 See : http://i.imgur.com/6NgEkOm.jpg
 
 * Switch between +3.7v and 5V boost converter
 * Switch between GND and pin 10
 * Resistor between pin 10 and +5v
 
 * LCD RS pin to digital pin 9
 * LCD WR pin to digital pin 8
 * LCD Enable pin to digital pin 7
 * LCD D4 pin to digital pin 6
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 4
 * LCD D7 pin to digital pin 3
 * 10K potentiometer:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 */

// include the library code:

#define fetPin        11
#define lcd_backlight 2
#define secondButton  10
#define batteryPin    A0

#define STATE_BAT     0
#define STATE_COIL    1
#define STATE_READER  2
#define STATE_ADDRESS 3 

// initialize the library with the numbers of the interface pins
LiquidCrystalFast lcd(9,  8,  7,  6,  5, 4, 3);
// LCD pins:          RS  RW  EN  D4 D5  D6 D7
MomentaryButton button(secondButton);

const char speedMessage[] = {"We the people of the United States, in order to form a more perfect union, establish justice, insure domestic tranquility, provide for the common defense, promote the general welfare, and secure the blessings of liberty to ourselves and our posterity, do ordain and establish this Constitution for the United States of America."}; // use this form

#define EE_voltageAddress 0
#define EE_programAddress 2
#define numStates 3
#define minVoltage 1.0
#define maxVoltage 4.2
#define numSteps 20
#define stepWeight (maxVoltage - minVoltage)/numSteps
#define numProgs 3
#define interval 100

int strPos = 0;
int desiredVoltage;
int state = 0; 
int wpm = 350;
int readPeriod = 60000 / wpm; //period in ms
char thisWord[30];
int wordLoc;
long startTime = 0;


///BIG CHARACTER SHIZ

// the 8 arrays that form each segment of the custom numbers
byte LT[8] = 
{
  B00111,
  B01111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte UB[8] =
{
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte RT[8] =
{
  B11100,
  B11110,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte LL[8] =
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B01111,
  B00111
};
byte LB[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111
};
byte LR[8] =
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11110,
  B11100
};
byte MB[8] =
{
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
};
byte block[8] =
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte blank[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

byte cross[8] =
{
  B11100,
  B11110,
  B11110,
  B01111,
  B01111,
  B01111,
  B00111,
  B00111,
};


void customJ(int location)
{ // uses segments to build the number 0
  lcd.setCursor(location,0); // set cursor to column 0, line 0 (first row)
  lcd.write(8);  // call each segment to create
  lcd.write(8);  // bottom half of the number
  lcd.write(2);
  lcd.setCursor(location, 1); // set cursor to colum 0, line 1 (second row)
  lcd.write(3);  // call each segment to create
  lcd.write(4);  // bottom half of the number
  lcd.write(5);
}

void customU(int location)
{
  lcd.setCursor(location,0);
  lcd.write(2);
  lcd.write(8);
  lcd.write(2);
  lcd.setCursor(location,1);
  lcd.write(3);
  lcd.write(4);  
  lcd.write(5);
}

void customI(int location)
{
  lcd.setCursor(location,0);
  lcd.write(8);
  lcd.write(7);
  lcd.write(8);
  lcd.setCursor(location, 1);
  lcd.write(8);
  lcd.write(7);
  lcd.write(8);
}

void customC(int location)
{
  lcd.setCursor(location,0);
  lcd.write(7);
  lcd.write(1);
  lcd.write(1);
  lcd.setCursor(location, 1);
  lcd.write(3);
  lcd.write(4);
  lcd.write(4); 
}

void customE(int location)
{
  lcd.setCursor(location,0);
  lcd.write(7);
  lcd.write(6);
  //lcd.write(6);
  lcd.setCursor(location, 1);
  lcd.write(7);
  lcd.write(4);
  //lcd.write(4);
}

void customF(int location)
{
  lcd.setCursor(location,0);
  lcd.write(7);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(location, 1);
  lcd.write(3);
  //lcd.write();
  //lcd.write(4);
}

void customR(int location)
{
  lcd.setCursor(location,0);
  lcd.write(7);
  lcd.write(6);
  lcd.write(7);
  lcd.setCursor(location, 1);
  lcd.write(3);
  lcd.write(8);
  lcd.write(9);
}

void customS(int location)
{
  lcd.setCursor(location,0);
  lcd.write(7);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(location, 1);
  lcd.write(4);
  lcd.write(4);
  lcd.write(5);
}

void customH(int location)
{
  lcd.setCursor(location,0);
  lcd.write(2);
  lcd.write(4);
  lcd.write(2);
  lcd.setCursor(location,1);
  lcd.write(3);
  lcd.write(8);  
  lcd.write(5);
}

//END BIG CHARACTER SHIZ

void setup() {

  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);

  // Turn on the backlight
  pinMode(lcd_backlight, OUTPUT);
  analogWrite(lcd_backlight, 255);

  button.setup(); // set as INPUT, set HIGH
  button.setThreshold(300); //1 sec between short and long hold

  // assignes each segment a write number
  lcd.createChar(0,LT);
  lcd.createChar(1,UB);
  lcd.createChar(2,RT);
  lcd.createChar(3,LL);
  lcd.createChar(4,LB);
  lcd.createChar(5,LR);
  lcd.createChar(6,MB);
  lcd.createChar(7,block);
  lcd.createChar(8,blank);
  lcd.createChar(9,cross);

}

void loop() {
  if(!digitalRead(secondButton)){
    stateMachine();
  }
  else{
    desiredVoltage = (minVoltage + EEPROM.read(EE_voltageAddress)*stepWeight)*255/(analogRead(batteryPin)*5.25/1024);
    if(minVoltage + EEPROM.read(EE_voltageAddress)*stepWeight > analogRead(batteryPin)*5.25/1024)
      desiredVoltage = 255;
    analogWrite(fetPin, desiredVoltage);

    switch(EEPROM.read(EE_programAddress)){
      case(0):
      //JUICE
      do{
        customJ(0);    // displays custom 0 on the LCD
        delay(interval);
        customU(4);
        delay(interval);
        customI(7);
        delay(interval);
        customC(10);
        delay(interval);
        customE(14);
        delay(interval);
        lcd.clear();
        delay(interval);

      }
      while(true);
      break;

      case(1):
      do{
        customF(0);    // displays custom 0 on the LCD
        customR(3);
        customE(7);
        customS(10);
        customH(13);
        delay(interval);
        lcd.clear(); 
        delay(interval);
      }
      while(true);
      break;


      case(2):
      speedRead();
      break;
    }
  }
}

void stateMachine(){
  while(digitalRead(secondButton));
  delay(50);

  while(true){
    switch(state){

      case(0):
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Battery Voltage:");
      lcd.setCursor(0,1);
      lcd.print(analogRead(batteryPin)*5.2/1024);
      lcd.print(" volts");
      button.check();
      if(button.wasHeld())
        state = 1;
      break;

      case(1):
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Coil Voltage:");
      lcd.setCursor(0,1);
      lcd.print(minVoltage + EEPROM.read(EE_voltageAddress)*stepWeight);
      lcd.print(" volts");
      button.check();
      if(button.wasClicked())
        EEPROM.write(EE_voltageAddress, (EEPROM.read(EE_voltageAddress)+1)%numSteps);
      if(button.wasHeld())
        state = 2;
      break;

      case(2):
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("LCD Program:");
      lcd.setCursor(0,1);
      switch(EEPROM.read(EE_programAddress)){
        case(0):
        lcd.print("JUICE");
        break;
        case(1):
        lcd.print("FRESH");
        break;
        case(2):
        lcd.print("SpeedRead");
        break;
      }

      button.check();
      if(button.wasClicked())
        EEPROM.write(EE_programAddress, (EEPROM.read(EE_programAddress)+1)%numProgs);
      if(button.wasHeld())
        state = 3;
      break;

      case(3):
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("lets fuck");
      button.check();
      if(button.wasHeld())
        state = 0;
      break;
    }

    delay(30); 
  }
}

void speedRead(){
  int i;
  strPos = 0;
  while(speedMessage[strPos] != '\0'){
    for(i = 0; speedMessage[strPos] != ' ' && speedMessage[strPos] != '\0'; i++){
      thisWord[i] = speedMessage[strPos++];
    }
    strPos++;
    thisWord[i] = '\0';
    lcd.clear();
    lcd.setCursor(4-i/5,0);
    lcd.print(thisWord);
    if (thisWord[i-1] == '.'  || thisWord[i-1] == ',')
      delay(250);
    else
      delay(100);
  }
}

