#include "mButton.h"
#include "LiquidCrystalFast.h"
#include "BigCharacters.h"
#include <EEPROM.h>
#include <avr/pgmspace.h>

/*  
 *  Filename: GhettoVaper.ino 
 * 
 *  Modified from the GhettoVape III code:https://github.com/jcloiacon/ghettovape-III by Julian Loiacono (see also https://www.youtube.com/watch?v=wXBiAZ-3UqU)
 *  
 *  Fixes:
 *  
 *    Custom Characters
 *    
 *    Replaced #define with const
 *    
 *   
 *  Adds:
 *  
 *    Temperature control (°C/°F)
 *    Power control
 *    Coil resistance
 *    Coil Materials and TCRs
 *    Inverts button S2
 *    Custom CHaracters
 *    
 *    Compiler defines:
 *      - Switch inversion
 *      - Testing with DFRobot LCD shield
 *      
 *  Problems:
 * 
 *    1. You have to wait for the Arduino to boot, before each vape
 *    2. Can modify switch S1 to be a toggle switch, so Arduino is always on and then S2 still controls the vape, with a hold, but multiple switches select the "mode select" mode
 *  
 *  To do: 
 *  
 *    Share compiler defs across files
 *    Welcome message - not just a bkank scren
 *    Adjust temp with tcrs
 *    Set temp control on toggle
 *    Predefine EE settings, for a new install
 *    Reset EE setings
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

// Switch S2 behaviour - do not change here - see mButton.h
//#define __S2_To_HIGH__
//#define __S2_To_LOW__  // default to this, as original
//#define __MULTI_PUSH_S2__

// Testing with DFRobot 1602 display
#define __Using_DFRobot_1602_LCD__

// Constants

// Pins
const int fetPin                   = 11;
const int lcd_backlight            = 2;
#if defined (__Using_DFRobot_1602_LCD__)
const int secondButton             = 12;  // For DR Robot 16x02 display
const int batteryPin               = A3;  // For DR Robot 16x02 display
#else
const int secondButton             = 10;  // Original
const int batteryPin               = A0;  // Original
#endif
const int coilVoltageDropPin       = A1;  // Voltage across FET, when FET goes directly to ground - otherwise it is the voltage across the FET and the measuring resistance
const int currentMeasurePin        = A2;
const float currentMeasureR        = 0.5;  //Ohms - Resistance of current measuring resistor

// State Engine states
const int kSTATE_BAT               = 0;
const int kSTATE_COIL              = 1;
const int kSTATE_POWER             = 2;
const int kSTATE_RESISTANCE        = 3;
const int kSTATE_MATERIAL          = 4;
const int kSTATE_TEMPERATURE       = 5;
const int kSTATE_TEMPERATURE_UNITS = 6;
const int kSTATE_VOLTAGEDROP       = 7;
const int kSTATE_READER            = 8;
const int kSTATE_ADDRESS           = 9;
const int kSTATE_DEFAULTS          = 11;
const int kSTATE_CONTROL_TYPE      = 10;
const int kNumStates               = 12;              

// Special states, that are not part of the round robbin states:
const int kSTATE_SURE              = 101;


// Coil Materials
const int kMaterial_SS304          = 0;
const int kMaterial_SS316          = 1;
const int kMaterial_SS317          = 2;
const int kMaterial_SS430          = 3;
const int kMaterial_Ni200          = 4;
const int kMaterial_Ti             = 5;
const int kMaterial_Tungsten       = 6;
const int kMaterial_NiFe30         = 7;
const int kMaterial_Kanthal_A1     = 8;
const int kMaterial_Kanthal_A      = 9;

// Coil Materials TCR
const float kCoeff_SS304           = 0.00105;
const float kCoeff_SS316           = 0.00094;
const float kCoeff_SS317           = 0.00088;
const float kCoeff_SS430           = 0.00138;
const float kCoeff_Ni200           = 0.006;
const float kCoeff_Ti              = 0.0035;
const float kCoeff_Tungsten        = 0.0045;
const float kCoeff_NiFe30          = 0.0032;
const float kCoeff_Kanthal_A1      = 0.000002;  // A1/APM
const float kCoeff_Kanthal_A       = 0.000053;  // A/AE/AF/D

const int kNumMaterials            = 10;    

const float kTCRs[kNumMaterials] = 
{
  kCoeff_SS304, 
  kCoeff_SS316, 
  kCoeff_SS317, 
  kCoeff_SS430, 
  kCoeff_Ni200, 
  kCoeff_Ti, 
  kCoeff_Tungsten, 
  kCoeff_NiFe30, 
  kCoeff_Kanthal_A1, 
  kCoeff_Kanthal_A 
};

// Amplication of current measurment
const float kAmplifier_Factor      = 1;  // For the instrumentation amplifier - to be set later

// Temperature Units
const int kTemperatureUnits_F      = 0; 
const int kTemperatureUnits_C      = 1; 
const int kTemperatureUnits_K      = 2; 

// Control Tyoe
const int kVoltageControl          = 0; 
const int kPowerControl            = 1; 
const int kTemperatureControl      = 2; 

// Program Modes
const int kPM_Juice                = 0;
const int kPM_Fresh                = 1;
const int kPM_SpeedRead            = 2;
const int kPM_Diag_VoltRead        = 3;
const int kPM_Diag_BatVoltRead_EE  = 4;
const int kPM_Diag_FETVoltRead_EE  = 5;
const int kPM_Diag_CurVoltRead_EE  = 6;

const char speedMessage[] = {"Vape on it!!!"}; // use this form

// EEPROM addresses
const int EE_programAddress             =  0;
const int EE_voltageAddress             =  2;
const int EE_resistanceAddress          =  4;
const int EE_powerAddress               =  6;
const int EE_coilVoltageDropAddress     =  8;
const int EE_programVoltageDropAddress  = 10;
const int EE_batteryVoltageDropAddress  = 12;
//const int EE_programMaterialAddress     = 14;   // not needed as we have EE_material address
const int EE_materialAddress            = 16;
const int EE_temperatureAddress         = 18;
const int EE_temperatureUnitsAddress    = 20;
const int EE_defaultsAddress            = 22;
const int EE_defaultsSureAddress        = 24;
const int EE_controlTypeAddress         = 26;
const int EE_currentMeasureAddress      = 28;


const float minResistance = 0.0;
const float maxResistance = 2.0;
const int   numResistanceSteps = 20;
const float stepResistanceWeight = (maxResistance - minResistance)/numResistanceSteps;
const float minPower = 0.0;
const float maxPower = 70.0;
const int   numPowerSteps = 70;
const float stepPowerWeight = (maxPower - minPower)/numPowerSteps; 
const float minTemperature = 0.0;
const float maxTemperature = 500.0;
const int   numTemperatureSteps = 50;
const int   numTemperatureUnitsSteps = 3;  // °C, °F and K
const float stepTemperatureWeight = (maxTemperature - minTemperature)/numTemperatureSteps; 
const float minVoltage = 1.0;
const float maxVoltage = 4.2;
const int   numVoltageSteps = 20;
const float stepVoltageWeight = (maxVoltage - minVoltage)/numVoltageSteps;
// Progs are the number of sub settings for a particular function (or State)
const int   numProgs = 7;      // Used to cycle (wrap around) Progs
const int   numVoltageDropProgs = 4;      // Used to cycle (wrap around) VoltageDropProgs
const int   numMaterialProgs = kNumMaterials;      // Used to cycle (wrap around) MaterialProgs
const int   numDefaultsSteps = 2;
const int   numDefaultsSureSteps = 2;
const int   numControlTypeSteps = 3;

const int interval = 100;

// Variables

int strPos = 0;
int desiredVoltage = 0; // For safety - We can assign a stored value, from EEPROM, later if we want
int state = 0; 
int wpm = 350;
int readPeriod = 60000 / wpm; //period in ms
char thisWord[30];
int wordLoc;
long startTime = 0;

// For timing
unsigned long lastMillis = 0;

// initialize the library with the numbers of the interface pins
#if defined (__Using_DFRobot_1602_LCD__)
LiquidCrystalFast lcd(8, 255,  9,  4,  5,  6, 7);   // For DFRobot 1602 shield
#else
LiquidCrystalFast lcd(9,  8,  7,  6,  5, 4, 3);   // Original GhettoVape III wiring
#endif
// LCD pins:          RS  RW  EN  D4 D5  D6 D7

// Create a button
MomentaryButton button(secondButton);


void setup() {

  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);

  // Turn on the backlight
  pinMode(lcd_backlight, OUTPUT);
  analogWrite(lcd_backlight, 255);

  // Set up analogue input pins:
  pinMode(batteryPin, INPUT);
  pinMode(coilVoltageDropPin, INPUT);
  pinMode(currentMeasurePin, INPUT);

  button.setup();            // set as INPUT, set HIGH (need to change this to LOW, for modified schematic)
  button.setThreshold(300);  // 1 sec between short and long hold

  // assigns each segment a write number
  // There was a problem drawing the "C" in "JUICE" with the original version
  // However, only eight custom characters can be assigned, therefore 0=8 and 1=9 - so there are two characters too many
  // As nothing uses character "0" (apart from "8" - the blank) - forget this
  // A blank (8) is already defined by space, or use character 254
  // the block can be replaced by other custom characters, to give stylised, or use character 255
  lcd.createChar(0, LT);
  lcd.createChar(1, UB);
  lcd.createChar(2, RT);
  lcd.createChar(3, LL);
  lcd.createChar(4, LB);
  lcd.createChar(5, LR);
  lcd.createChar(6, MB);
  //lcd.createChar(7, block);
  //lcd.createChar(8, blank);
  //lcd.createChar(9, cross);
  lcd.createChar(7, cross);
}

void loop() {

#if defined (__S2_To_HIGH__)
  // For push S2 to HIGH
  if(digitalRead(secondButton)) {      // if S2 is held
#elif defined (__MULTI_PUSH_S2__)
  // For multi-push S2
  if(!digitalRead(secondButton)) {   // if S2 is clicked five times
#else
  // For push S2 to LOW - default, as original
  if(!digitalRead(secondButton)) {   // if S2 is held
#endif
    stateMachine();
  }
  else {                             // if S2 does not meet the if


    // Read the voltage across the coil
    EEPROM.write(EE_batteryVoltageDropAddress,analogRead(batteryPin));  // store the analogue read
    EEPROM.write(EE_coilVoltageDropAddress,analogRead(coilVoltageDropPin));  // store the analogue read
    EEPROM.write(EE_currentMeasureAddress,analogRead(currentMeasurePin));  // store the analogue read

    switch (EEPROM.read(EE_controlTypeAddress))
    {
      case (kVoltageControl):
      {
        float EEVoltage = EEPROM.read(EE_voltageAddress)*stepVoltageWeight;
        float batteryVoltage = analogRead(batteryPin)*5.25/1024;

//      float coilVoltage = (minVoltage + EEVoltage);
//      float voltageProportion = coilVoltage/batteryVoltage;
//      desiredVoltage = VoltageProportion*255;
        desiredVoltage = (minVoltage + (EEVoltage))*255/(batteryVoltage);
        if (minVoltage + EEVoltage > batteryVoltage)  // if there isn't sufficient battery life...
          desiredVoltage = 255;                                                                                // then just supply the maximum      
        break;
      }
      case (kPowerControl):
      {
        // For power
        float resistanceOfCoil = minResistance + EEPROM.read(EE_resistanceAddress)*stepResistanceWeight;
        float currentInCoil = (analogRead(currentMeasurePin)*5.25)/(1024*kAmplifier_Factor*currentMeasureR);
        float powerInCoil = currentInCoil*currentInCoil*resistanceOfCoil;
        float desiredPower = minPower + EEPROM.read(EE_powerAddress)*stepPowerWeight;
        
        // For power control - auto adjust
        if (powerInCoil != desiredPower) {
          float newPower = desiredPower-powerInCoil;
          float voltageChange = sqrt(newPower*resistanceOfCoil);
        }

        float coilVoltage = sqrt(desiredPower*resistanceOfCoil);
        float batteryVoltage = analogRead(batteryPin)*5.25/1024;
//      float voltageProportion =  coilVoltage/batteryVoltage;
//      desiredVoltage = VoltageProportion*255;
        desiredVoltage = coilVoltage/batteryVoltage*255;  // This needs to be between 0-255 - does minVoltage play a part?
        // Do we want to change the voltage in EE, to this new desired voltage?
        // Probably not, as we can rely on the above calculations. And we don't want to mess the users settings.
        // However, if we do set the EEVoltage then the code can then skip to the voltage control section, 
        // but will make code slower, as it will then have to run through the voltage control code as well.
        break;
      }
      case (kTemperatureControl): // this could be dangerous if no voltage sensing pin (i.e. the currentMeasurePin) is connected!!!
      {
        // For temperature control, using TCR
        float resistanceOfCoil = minResistance + EEPROM.read(EE_resistanceAddress)*stepResistanceWeight;
        float currentInCoil = (analogRead(currentMeasurePin)*5.25)/(1024*kAmplifier_Factor*currentMeasureR);
        float resistanceOfVapingCoil =  ((EEPROM.read(EE_batteryVoltageDropAddress) - EEPROM.read(EE_coilVoltageDropAddress))*5.25* currentInCoil)/1024;
        float resistanceOfVapingCoilDelta = resistanceOfVapingCoil - resistanceOfCoil;
        float temperatureOfCoil = 23 + (resistanceOfVapingCoilDelta/kTCRs[EEPROM.read(EE_materialAddress)]);
        float desiredTemperature = minTemperature + EEPROM.read(EE_temperatureAddress)*stepTemperatureWeight;
        
        if (temperatureOfCoil != desiredTemperature) {
          float deltaTemperature = desiredTemperature - temperatureOfCoil;
          if (deltaTemperature < 0)
            desiredVoltage--;  // just decrease the DAC by one - doesn't really matter what the real voltage is
          else if (deltaTemperature > 0)
            desiredVoltage++;   // just increase the DAC by one - doesn't really matter what the real voltage is
          // However, what value are we increasing desiredVoltage from exactly?
          // Should it be made to start from:
          //      the last used value, which was used when using voltage control?
          //      a minimum point, say 1V?
          // What value does desiredVoltage have when first switched on? If we assign zero in the declaration then fine
          // Should we remember the last used voltage in EEPROM? 
        }
        break;
      }

      analogWrite(fetPin, desiredVoltage);                                                                   // Activate PWM to trigger NFET
    }
    
    switch(EEPROM.read(EE_programAddress))
    {
      case(kPM_Juice):
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

      case(kPM_Fresh):
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

      case(kPM_SpeedRead):
      {
        speedRead();
        break;
      }
      
      // Display the ADC and voltages of the battery and FET
      case(kPM_Diag_VoltRead):
      {
        if (millis()-lastMillis>1000){
          lastMillis=millis();
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("BAT ");
          lcd.print(analogRead(batteryPin));
          lcd.setCursor(8,0);
          lcd.print(analogRead(batteryPin)*5.2/1024);
          lcd.setCursor(0,1);
          lcd.print("FET ");
          lcd.print(analogRead(coilVoltageDropPin));
          lcd.setCursor(8,1);
          lcd.print(analogRead(coilVoltageDropPin)*5.2/1024);
        }
        break;
      }

      // Display the voltage and EE storage for battery
      case(kPM_Diag_BatVoltRead_EE):
      {
        if (millis()-lastMillis>1000){
          lastMillis=millis();
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("BAT ");
          lcd.print(analogRead(batteryPin));
          lcd.setCursor(8,0);
          lcd.print(analogRead(batteryPin)*5.2/1024);
          lcd.setCursor(0,1);
          lcd.print("EEB ");
          lcd.print(EEPROM.read(EE_batteryVoltageDropAddress));
          lcd.setCursor(8,1);
          lcd.print(EEPROM.read(EE_batteryVoltageDropAddress)*5.2/1024);
        }
        break;
      }
      
      // Display the voltage and EE storage for the FET
      case(kPM_Diag_FETVoltRead_EE):
      {
        if (millis()-lastMillis>1000){
          lastMillis=millis();
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("FET ");
          lcd.print(analogRead(coilVoltageDropPin));
          lcd.setCursor(8,0);
          lcd.print(analogRead(coilVoltageDropPin)*5.2/1024);
          lcd.setCursor(0,1);
          lcd.print("EEF ");
          lcd.print(EEPROM.read(EE_coilVoltageDropAddress));
          lcd.setCursor(8,1);
          lcd.print(EEPROM.read(EE_coilVoltageDropAddress)*5.2/1024);
        }
        break;
      }
      
      // Display the voltage and EE storage for the current measuring resistance
      case(kPM_Diag_CurVoltRead_EE):   
      {
        if (millis()-lastMillis>1000){
          lastMillis=millis();
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("CUR ");
          lcd.print(analogRead(currentMeasurePin));
          lcd.setCursor(8,0);
          lcd.print(analogRead(currentMeasurePin)*5.2/1024);
          lcd.setCursor(0,1);
          lcd.print("EEC ");
          lcd.print(EEPROM.read(EE_currentMeasureAddress));
          lcd.setCursor(8,1);
          lcd.print(EEPROM.read(EE_currentMeasureAddress)*5.2/1024);
        }
        break;
      }
    }
  }
}


void stateMachine(){
  while(digitalRead(secondButton));
  delay(50);

  while(true){
    switch(state) 
    {
      case(kSTATE_BAT):  // show battery voltage
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Battery Voltage:");
        lcd.setCursor(0,1);
        lcd.print(analogRead(batteryPin)*5.2/1024);
        lcd.print(" V");
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
        {
          EEPROM.write(EE_powerAddress, (EEPROM.read(EE_powerAddress)+1)%numPowerSteps);
          // Calculate the voltage required
          float voltsForPower = sqrt((minPower + EEPROM.read(EE_powerAddress)*stepPowerWeight)*(minResistance + EEPROM.read(EE_resistanceAddress)*stepResistanceWeight));
          EEPROM.write(EE_voltageAddress, (voltsForPower-minVoltage)/stepVoltageWeight);
        }
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
//        lcd.print((char)244); // Ohm symbol (Omega)
        lcd.print(" \364"); // Ohm symbol (Omega) octal (244 in decimal)
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
        lcd.print("Coil Material:");
        lcd.setCursor(0,1);
        switch(EEPROM.read(EE_materialAddress))
        {
          case(kMaterial_SS304):
            lcd.print("SS 304");
            break;
          case(kMaterial_SS316):
            lcd.print("SS 316");
            break;
          case(kMaterial_SS317):
            lcd.print("SS 317");
            break;
          case(kMaterial_SS430):
            lcd.print("SS 430");
            break;
          case(kMaterial_Ni200):
            lcd.print("Ni200");
            break;
          case(kMaterial_Ti):
            lcd.print("Ti");
            break;
          case(kMaterial_Tungsten):
            lcd.print("Tungsten");
            break;
          case(kMaterial_NiFe30):
            lcd.print("NiFe30");
            break;
          case(kMaterial_Kanthal_A1):
            lcd.print("Kanthal A/APM");
            break;
          case(kMaterial_Kanthal_A):
            lcd.print("Kanthal A/AE+F/D");
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

      case(kSTATE_TEMPERATURE):  // adjust temperature
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Coil Temperature:");
        lcd.setCursor(0,1);
        switch (EEPROM.read(EE_temperatureUnitsAddress))
        {
          case(kTemperatureUnits_F):
          {
            lcd.print(((minTemperature + EEPROM.read(EE_temperatureAddress)*stepTemperatureWeight)*1.8) + 32);
            lcd.print(" \337F"); 
            break;
          }  
          case(kTemperatureUnits_C):
          {
            lcd.print(minTemperature + EEPROM.read(EE_temperatureAddress)*stepTemperatureWeight);
            lcd.print(" \337C"); // degree symbol (Omega) octal (244 in decimal)
            break;                  
          }
          case(kTemperatureUnits_K):
          {
            lcd.print((minTemperature + EEPROM.read(EE_temperatureAddress)*stepTemperatureWeight)+273.15);
            lcd.print(" K"); // degree symbol (Omega) octal (244 in decimal)   
            break;               
          }
        }
        button.check();
        if(button.wasClicked())
          EEPROM.write(EE_temperatureAddress, (EEPROM.read(EE_temperatureAddress)+1)%numTemperatureSteps);
        if(button.wasHeld())
//          state = 4;
          state++;
        break;
      }

      case(kSTATE_TEMPERATURE_UNITS):  // adjust temperature units
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Temperature in:");
        lcd.setCursor(0,1);
        switch (EEPROM.read(EE_temperatureUnitsAddress))
        {
          case(kTemperatureUnits_F):
          {
            lcd.print(" \337F"); // 0 = Fahrenheit
            break;
          }
          case(kTemperatureUnits_C):
          {
            lcd.print(" \337C"); // 1 = Centigrade
            break;
          }
          case(kTemperatureUnits_K):
          {
            lcd.print(" K");     // 2 = Kelvin    
            break;
                          
          }
        }
        button.check();
        if(button.wasClicked())
          EEPROM.write(EE_temperatureUnitsAddress, (EEPROM.read(EE_temperatureUnitsAddress)+1)%numTemperatureUnitsSteps);
        if(button.wasHeld())
//          state = 4;
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
            lcd.print("FET Voltage:");
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
            lcd.print("Coil Voltage:");
            lcd.setCursor(0,1);
            lcd.print((EEPROM.read(EE_batteryVoltageDropAddress)-EEPROM.read(EE_coilVoltageDropAddress))*5.2/1024);
            lcd.print(" V");
            break;
          }
          
          case(3):
          {
            //   Print power through coil
            int batteryVoltageDrop = EEPROM.read(EE_batteryVoltageDropAddress);
            int coilVoltageDrop = EEPROM.read(EE_coilVoltageDropAddress);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Coil Power:");
            lcd.setCursor(0,1);
//            lcd.print((((EEPROM.read(EE_batteryVoltageDropAddress)-EEPROM.read(EE_coilVoltageDropAddress))*5.2/1024)*((EEPROM.read(EE_batteryVoltageDropAddress)-EEPROM.read(EE_coilVoltageDropAddress))*5.2/1024))/(minResistance + EEPROM.read(EE_resistanceAddress)*stepResistanceWeight));
            lcd.print((((batteryVoltageDrop-coilVoltageDrop)*5.2/1024)*((batteryVoltageDrop-coilVoltageDrop)*5.2/1024))/(minResistance + EEPROM.read(EE_resistanceAddress)*stepResistanceWeight)); // slightly faster
            lcd.print(" W");
            break;
          }
          
          case(4):
          {
            //   Print voltage at current measuring resistance
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Current Volt:");
            lcd.setCursor(0,1);
            lcd.print(EEPROM.read(EE_currentMeasureAddress)*5.2/1024);
            lcd.print(" V");
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
          case(kPM_Juice):
            lcd.print("JUICE");            // Display JUICE in custom characters
            break;
          case(kPM_Fresh):
            lcd.print("FRESH");            // Display FRESH in custom characters
            break;
          case(kPM_SpeedRead):             // Display the message
            lcd.print("SpeedRead");
            break;
          case(kPM_Diag_VoltRead):         // Display the ADC and voltages of the battery and FET
            lcd.print("Diag V");
            break;
          case(kPM_Diag_BatVoltRead_EE):   // Display the voltage and EE storage for battery
            lcd.print("Diag V EE BAT");
            break;
          case(kPM_Diag_FETVoltRead_EE):   // Display the voltage and EE storage for the FET
            lcd.print("Diag V EE FET");
            break;
          case(kPM_Diag_CurVoltRead_EE):   // Display the voltage and EE storage for the current measuring resistance
            lcd.print("Diag V EE CUR");
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
          state++;;
        break;
      }

      case(kSTATE_DEFAULTS):
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Reset defaults?");
        lcd.setCursor(0,1);
        if (EEPROM.read(EE_defaultsAddress))
          lcd.print("YES"); // 1 = YES
        else
          lcd.print("NO"); // 0 = NO
        button.check();
        if(button.wasClicked())
          EEPROM.write(EE_defaultsAddress, (EEPROM.read(EE_defaultsAddress)+1)%numDefaultsSteps);
        if(button.wasHeld()) {
          if (EEPROM.read(EE_defaultsAddress)) {
            state = kSTATE_SURE;
          }
          else
            state++;
        }
        break;
      }

      case(kSTATE_CONTROL_TYPE):  // adjust temperature units
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Control by:");
        lcd.setCursor(0,1);
        switch (EEPROM.read(EE_controlTypeAddress))
        {
          case(kVoltageControl):
          {
            lcd.print("Voltage"); 
            break;
          }
          case(kPowerControl):
          {
            lcd.print("Power"); // 1 = Centigrade
            break;
          }
          case(kTemperatureControl):
          {
            lcd.print("Temperature");     // 2 = Kelvin    
            break;
                          
          }
        }
        button.check();
        if(button.wasClicked())
          EEPROM.write(EE_controlTypeAddress, (EEPROM.read(EE_controlTypeAddress)+1)%numControlTypeSteps);
        if(button.wasHeld())
//          state = 4;
          state++;
        break;
      }

      
     case(kSTATE_SURE):
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Are you sure?");
        lcd.setCursor(0,1);
        if (EEPROM.read(EE_defaultsSureAddress))
          lcd.print("YES"); // 1 = YES
        else
          lcd.print("NO"); // 0 = NO
        button.check();
        if(button.wasClicked())
          EEPROM.write(EE_defaultsSureAddress, (EEPROM.read(EE_defaultsSureAddress)+1)%numDefaultsSureSteps);
        if(button.wasHeld()) {
          if (EEPROM.read(EE_defaultsSureAddress)) {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Resetting...");
            delay(300);
            EE_Presets();
          }
          else
            EEPROM.write(EE_defaultsSureAddress, 0); //Reset back to zero/NO - else you are presents with "Yes" at the next "Are you sure?"
          state = 0;  // go back to state 0
        }
        break;
      }
    }

    if (state >= kNumStates && state < 99) {
      state= 0;
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

void EE_Presets(){
  EEPROM.write(EE_programAddress, 0);  // Prints "JUICE" by default
  EEPROM.write(EE_voltageAddress, 0);
  EEPROM.write(EE_resistanceAddress, 0);  // should default to 1 Ohm or 0.5 Ohm, or what?
  EEPROM.write(EE_powerAddress, 0);       // should default to 30 W, for safety?
  EEPROM.write(EE_coilVoltageDropAddress, 0);
  EEPROM.write(EE_programVoltageDropAddress, 0);
  EEPROM.write(EE_batteryVoltageDropAddress, 0);
//  EEPROM.write(EE_programMaterialAddress, kMaterial_SS316);  // not needed as we have EE_material address
  EEPROM.write(EE_materialAddress, kMaterial_SS316);  // default SS 316
  EEPROM.write(EE_temperatureAddress, 0);
  EEPROM.write(EE_temperatureUnitsAddress, kTemperatureUnits_C);  // default to °C
  EEPROM.write(EE_defaultsAddress, 0);  // default to "Do not reset"
  EEPROM.write(EE_defaultsSureAddress, 0);  // default to "No I am not sure"
  EEPROM.write(EE_controlTypeAddress, 0);  // default to voltage control
  EEPROM.write(EE_currentMeasureAddress, 0);  // default to voltage control
}

