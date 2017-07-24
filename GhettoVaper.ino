#include "mButton.h"
#include "LiquidCrystalFast.h"
#include "BigCharacters.h"
#include <EEPROM.h>
#include <avr/pgmspace.h>

/* Problems:
 * 
 * 1. You have to wait for the Arduino to boot, before each vape
 * 2. Need to be able to select coil resistance, R_coil
 * 3. You can't measure the power yet - need to read voltage below coil, on A1 and then P=(A0-A1)*(A0-A1)/R_Coil
 * 
 * 
 * Can modify switch S1 to be a toggle switch, so Arduino is always on and then S2 still controls the vape, with a hold, but multiple switches select the "mode select" mode
 */

 /* Changes:
  *  S2 push to high
  *  Added defines
  */
 
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

// Switch S2 behaviour

#define __S2_To_HIGH__
//#define __S2_To_LOW__  // default to this, as original
//#define __MULTI_PUSH_S2__


// Pins
const int fetPin             = 11;
const int lcd_backlight       = 2;
const int secondButton       = 10;
const int batteryPin         = A0;
const int coilVoltageDropPin = A1;

// State Engine states
const int kSTATE_BAT          = 0;
const int kSTATE_COIL         = 1;
const int kSTATE_POWER        = 2;
const int kSTATE_RESISTANCE   = 3;
const int kSTATE_MATERIAL     = 4;
const int kSTATE_VOLTAGEDROP  = 5;
const int kSTATE_READER       = 6;
const int kSTATE_ADDRESS      = 7;

// Coil Materials
const int kMaterial_SS316 = 0;
const int kMaterial_Ni    = 1;
const int kMaterial_Ti    = 2;


// initialize the library with the numbers of the interface pins
LiquidCrystalFast lcd(9,  8,  7,  6,  5, 4, 3);
// LCD pins:          RS  RW  EN  D4 D5  D6 D7
MomentaryButton button(secondButton);

const char speedMessage[] = {"Vape on it!!!"}; // use this form

// EEPROM addresses
const int EE_voltageAddress = 0;
const int EE_programAddress = 2;
const int EE_resistanceAddress = 4;
const int EE_powerAddress = 6;
const int EE_coilVoltageDropAddress = 8;
const int EE_batteryVoltageDropAddress = 10;
const int EE_programVoltageDropAddress = 12;
const int EE_programMaterialAddress = 14;
const int EE_materialAddress = 16;


//const int numStates = 8;                 // not used
const int minResistance = 0.0;
const int maxResistance = 2.0;
const int numResistanceSteps = 20;
const int stepResistanceWeight = (maxResistance - minResistance)/numResistanceSteps;
const int minPower = 0.0;
const int maxPower = 2.0;
const int numPowerSteps = 20;
const int stepPowerWeight = (maxPower - minPower)/numResistanceSteps;
const int minVoltage = 1.0;
const int maxVoltage = 4.2;
const int numVoltageSteps = 20;
const int stepVoltageWeight = (maxVoltage - minVoltage)/numVoltageSteps;
const int numProgs = 3;
const int numVoltageDropProgs = 4;
const int numMaterialProgs = 3;
const int interval = 100;

int strPos = 0;
int desiredVoltage;
int state = 0; 
int wpm = 350;
int readPeriod = 60000 / wpm; //period in ms
char thisWord[30];
int wordLoc;
long startTime = 0;




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

//#if defined (__S2_To_LOW__)
// For push S2 to LOW
//  if(!digitalRead(secondButton)){   // if S2 is held
//    stateMachine();
//  }
//  else{                             // if S2 is not held

#if defined (__S2_To_HIGH__)
// For push S2 to HIGH
if(digitalRead(secondButton)){      // if S2 is held
#elif defined (__MULTI_PUSH_S2__)
// For multi-push S2
if(!digitalRead(secondButton)){   // if S2 is clicked five times
#else
// For push S2 to LOW - default, as original
  if(!digitalRead(secondButton)){   // if S2 is held
#endif
    stateMachine();
  }
  else {                             // if S2 does not meet the if
    desiredVoltage = (minVoltage + EEPROM.read(EE_voltageAddress)*stepVoltageWeight)*255/(analogRead(batteryPin)*5.25/1024);
    if(minVoltage + EEPROM.read(EE_voltageAddress)*stepVoltageWeight > analogRead(batteryPin)*5.25/1024)
      desiredVoltage = 255;
    analogWrite(fetPin, desiredVoltage);
    EEPROM.write(EE_batteryVoltageDropAddress,analogRead(batteryPin));  // store the analogue read
    EEPROM.write(EE_coilVoltageDropAddress,analogRead(coilVoltageDropPin));  // store the analogue read
    
    switch(EEPROM.read(EE_programAddress))
    {
      case(0):
      {
        //JUICE
        do 
        {
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
      }

      case(1):
      {
        do 
        {
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
      }

      case(2):
      {
        speedRead();
        break;
      }
    }
  }
}

void stateMachine(){
  while(digitalRead(secondButton));
  delay(50);

  while(true){
    switch(state){

      case(kSTATE_BAT):  // show battery voltage
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Battery Voltage:");
        lcd.setCursor(0,1);
        lcd.print(analogRead(batteryPin)*5.2/1024);
        lcd.print(" volts");
        button.check();
        if(button.wasHeld())
//          state = 1;
          state++;
        break;
      }

      case(kSTATE_COIL):  // adjust coil voltage
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Coil Voltage:");
        lcd.setCursor(0,1);
        lcd.print(minVoltage + EEPROM.read(EE_voltageAddress)*stepVoltageWeight);
        lcd.print(" V");
        button.check();
        if(button.wasClicked())
          EEPROM.write(EE_voltageAddress, (EEPROM.read(EE_voltageAddress)+1)%numVoltageSteps);
        if(button.wasHeld())
//          state = 2;
          state++;
        break;
      }

      case(kSTATE_POWER):  // adjust power
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Power:");
        lcd.setCursor(0,1);
        lcd.print(minPower + EEPROM.read(EE_powerAddress)*stepPowerWeight);
        lcd.print(" W");
        button.check();
        if(button.wasClicked())
          EEPROM.write(EE_powerAddress, (EEPROM.read(EE_powerAddress)+1)%numPowerSteps);
        if(button.wasHeld())
//          state = 3;
          state++;
        break;
      }

      case(kSTATE_RESISTANCE):  // adjust coil resistance
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Coil Resistance:");
        lcd.setCursor(0,1);
        lcd.print(minResistance + EEPROM.read(EE_resistanceAddress)*stepResistanceWeight);
//        lcd.print(" ohm");
        lcd.print(132); // Ohm symbol (Omega)
        button.check();
        if(button.wasClicked())
          EEPROM.write(EE_resistanceAddress, (EEPROM.read(EE_resistanceAddress)+1)%numResistanceSteps);
        if(button.wasHeld())
//          state = 4;
          state++;
        break;
      }

      case(kSTATE_MATERIAL):  // adjust material
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("LCD Program:");
        lcd.setCursor(0,1);
        switch(EEPROM.read(EE_materialAddress))
        {
          case(kMaterial_SS316):
            lcd.print("SS 316");
            break;
          case(kMaterial_Ni):
            lcd.print("Ni");
            break;
          case(kMaterial_Ti):
            lcd.print("Ti");
            break;
        }

        button.check();
        if(button.wasClicked())
          EEPROM.write(EE_materialAddress, (EEPROM.read(EE_materialAddress)+1)%numMaterialProgs);
        if(button.wasHeld())
//          state = 5;
          state++;
        break;
      }

      case(kSTATE_VOLTAGEDROP):  // show coil voltage drop and power
      {
        // Use state machine to show:
        switch(EEPROM.read(EE_programVoltageDropAddress)){
          case(0):
          {
        //   Print Battery Voltage when vaping
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Battery Voltage:");
            lcd.setCursor(0,1);
            lcd.print(EEPROM.read(EE_batteryVoltageDropAddress)*5.2/1024);
            lcd.print(" V");
            break;
          }
          
          case(1):
          {
            //   Print Voltage below coil
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Coil Voltage:");
            lcd.setCursor(0,1);
            lcd.print(EEPROM.read(EE_coilVoltageDropAddress)*5.2/1024);
            lcd.print(" V");
            break;
          }
          
          case(2):
          {
            //   Print  Voltage Drop across coil
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Coil Voltage Drop:");
            lcd.setCursor(0,1);
            lcd.print((EEPROM.read(EE_batteryVoltageDropAddress)-EEPROM.read(EE_coilVoltageDropAddress))*5.2/1024);
            lcd.print(" V");
            break;
          }
          
          case(3):
          {
            //   Print power through coil
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Coil Power:");
            lcd.setCursor(0,1);
            lcd.print((((EEPROM.read(EE_batteryVoltageDropAddress)-EEPROM.read(EE_coilVoltageDropAddress))*5.2/1024)*((EEPROM.read(EE_batteryVoltageDropAddress)-EEPROM.read(EE_coilVoltageDropAddress))*5.2/1024))/(minResistance + EEPROM.read(EE_resistanceAddress)*stepResistanceWeight));
            lcd.print(" W");
            break;
          }
        }
       
        button.check();
        if(button.wasClicked())
          EEPROM.write(EE_programVoltageDropAddress, (EEPROM.read(EE_programVoltageDropAddress)+1)%numVoltageDropProgs);
        if(button.wasHeld())
//          state = 6;
          state++;
        break;
      }

      case(kSTATE_READER):
      {
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
//          state = 7;
          state++;
        break;
      }

      case(kSTATE_ADDRESS):
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("lets roll");
        button.check();
        if(button.wasHeld())
          state = 0;
        break;
      }
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

