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

/*
Your Connections from TFT_ILI9163C to an Uno (Through a Level Shifter)

 LED to 3.3V
 SCK to D13
 SDA to D11
 A0 to D8
 RST to D9
 CS to D10
 GND to GND
 VCC to 3.3V 
 */

//#include <stdlib.h>   // for dtostrf()
#include <EEPROM.h>
#include <avr/pgmspace.h>

// Use config file instead of this:
/*
// ******************** DEFINES - START ********************
// Test
//#define __Debug__ // This should normally be commented out
#define __Use_MMButton__ // Use new version - This should normally be uncommented out (i.e. normally do NOT comment out)
// MButton is the default - however MButton can only be used with pull down buttons 


// Select which LCD you are using - 1602 is the default
// Testing with DFRobot 1602 display (default standard 1602 shield)
//#define __Use_DFRobot_1602_LCD__
//#define __Use_TFT_ILI9163C_Extended_Char_LCD__ // for 0.96" colour display
#define __Use_SSD1306_LCD__  // For SSD1306 128x32 0.91"
//#define __Use_1602_LCD__

// Checks for multiple display compiler defines
#if defined (__Use_DFRobot_1602_LCD__) && defined (__Use_TFT_ILI9163C_Extended_Char_LCD__)
#error Oops!  You have defined both __Use_DFRobot_1602_LCD__ and __Use_TFT_ILI9163C_Extended_Char_LCD__. You can only define one. Which display are you using??
#endif
#if defined (__Use_DFRobot_1602_LCD__) && defined (__Use_SSD1306_LCD__)
#error Oops!  You have defined both __Use_DFRobot_1602_LCD__ and __Use_SSD1306_LCD__. You can only define one. Which display are you using??
#endif
#if defined (__Use_SSD1306_LCD__) && defined (__Use_TFT_ILI9163C_Extended_Char_LCD__)
#error Oops!  You have defined both __Use_SSD1306_LCD__ and __Use_TFT_ILI9163C_Extended_Char_LCD__. You can only define one. Which display are you using??
#endif

// Switch S2 behaviour
#define __S2_To_HIGH__
//#define __S2_To_LOW__  // default to this, as original
//#define __MULTI_PUSH_S2__
#if defined (__S2_To_HIGH__) && defined(__S2_To_LOW__)
#error Oops!  You have defined both __S2_To_HIGH__ and __S2_To_LOW__. You can only define one. Does your button pull up or pull down? Or, to put it another way, do you want you input to be pulled down, or pulled up?
#endif

// Using which font?
//#define __Use_Font_u8g2_font_6x10_mf__  // only this font overwrites correctly
//#define __Use_Font_u8g2_font_6x10_tf__
//#define __Use_Font_u8g2_font_ncenB08_tr__
//#define __Use_Font_u8g2_font_ncenB14_tr__
//#define __Use_Font_u8g2_font_unifont_t_symbols__
#define __Use_Font_u8g2_font_pxplusibmvga8_m_all__  // this font works fine 8x16


// Define message
// Use Star Wars text
#define __Use_Star_wars__

// ******************** DEFINES - END **********************
*/
#include "config.h"

#if defined (__Use_MMButton__)
#include "MMButton.h"
#else
#include "MButton.h"
#endif


#if defined (__Use_DFRobot_1602_LCD__)
#include <LiquidCrystalFast.h>
#include "BigCharacters.h"
#elif defined (__Use_TFT_ILI9163C_Extended_Char_LCD__)
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C_Extended_Char.h>
#elif defined (__Use_SSD1306_LCD__)
#include <Arduino.h>
//#include <U8g2lib.h>  //not required, we are using SSD1306_Extended_Char
#include <SSD1306_Extended_Char.h>
//#ifdef U8X8_HAVE_HW_SPI
//#include <SPI.h>
//#endif
//#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
//#endif
//#include <SSD1306_Extended_Char.h>
#elif defined (__Use_SSD1306_OLED_HW_I2C_FULL_LCD__)
#include <SSD1306_OLED_HW_I2C_FULL.h>
#elif defined (__Use_Small_SSD1306_LCD__)
#include <Small_SSD1306.h>
#elif defined (__Use_Small_SSD1306_LCD_Print_8x16__)
#include <Small_SSD1306_Print_8x16.h>
#elif defined (__Use_Small_SSD1306_LCD_Print_8x16_lib__)
#include <Small_SSD1306_Print_8x16_lib.h>
#elif defined (__Use_1602_LCD__)
#include "LiquidCrystalFast.h"
#include "BigCharacters.h"
#else
#include "LiquidCrystalFast.h"
#include "BigCharacters.h"
#endif

 
#if defined (__Use_TFT_ILI9163C_Extended_Char_LCD__)
// All wiring required, for TFT_ILI9163C, only 3 defines for hardware SPI on 328P
#define __DC 9
#define __CS 10
// MOSI --> (SDA) --> D11
#define __RST 12
// SCLK --> (SCK) --> D13

// Color definitions for TFT_ILI9163C
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0  
#define WHITE   0xFFFF

// TextSize = 1 gives display 20 characters wide, 14 characters high
// TextSize = 2 gives display 10 characters wide, 7 characters high
// TextSize = 3 gives display 7 characters wide, 4 characters high
const int kTextSize = 1;
#endif

/* Redundant
#if defined (__Use_DFRobot_1602_LCD__)
const int kScreenWidth = 16;
#elif defined (__Use_TFT_ILI9163C_Extended_Char_LCD__)
const int kScreenWidth = 20;
#elif defined (__Use_SSD1306_LCD__)
const int kScreenWidth = 20;  //SSD1306???
#elif defined (__Use_1602_LCD__)
const int kScreenWidth = 16;
#else
const int kScreenWidth = 16;
#endif
*/

// For TFT_ILI9163C 1.44" 128x128
// TextSize = 1 gives display 20 characters wide, 14 characters high
// TextSize = 2 gives display 10 characters wide, 7 characters high
// TextSize = 3 gives display 7 characters wide, 4 characters high

// For 0.91" 128x32
// TextSize = 6x10 gives display 20 characters wide, 3 characters high
// TextSize = 16x16 gives display 8 characters wide, 2 characters high
// TextSize = 8x16 gives display 16 characters wide, 2 characters high - ???

// Constants

// Pins
const int fetPin                   = 11;

#if !defined (__Use_TFT_ILI9163C_Extended_Char_LCD__)
const int lcd_backlight            = 2;
#endif

#if defined (__Use_DFRobot_1602_LCD__)
const int secondButton             = 12;  // For DR Robot 16x02 display
const int batteryPin               = A3;  // For DR Robot 16x02 display - Originally A0, but DR Robot uses A0 to return key presses
const int kLCDWidth                = 16;  // Width in characters
const int kLCDHeight               = 2;   // Height in characters
#elif defined (__Use_TFT_ILI9163C_Extended_Char_LCD__)
const int secondButton             = 6;   // For TFT_ILI9163C
const int batteryPin               = A0;  // Original
const int kLCDWidth                = 20;  // Width in characters
const int kLCDHeight               = 14;  // Height in characters
#elif defined (__Use_SSD1306_LCD__)
const int secondButton             = 12;   // For SSD1306 128x32 0.91" // For testing in conjuction with DFRobot shield, use same second button
//const int secondButton             = 6;   // For SSD1306 128x32 0.91"
const int batteryPin               = A3;  // Originally A0
#if defined (__Use_Font_u8g2_font_6x10_tf__) || defined (__Use_Font_u8g2_font_6x10_mf__)
const int kLCDWidth                = 20;  // Width in characters, for u8g2_font_6x10_tf and u8g2_font_ncenB08_tr
const int kLCDHeight               = 3;  // Height in characters, for u8g2_font_6x10_tf and u8g2_font_ncenB08_tr
#elif defined (__Use_Font_u8g2_font_ncenB08_tr__)
const int kLCDWidth                = 10;  // Width in characters, for u8g2_font_6x10_tf and u8g2_font_ncenB08_tr
const int kLCDHeight               = 2;  // Height in characters, for u8g2_font_6x10_tf and u8g2_font_ncenB08_tr
#elif defined (__Use_Font_u8g2_font_ncenB14_tr__)
const int kLCDWidth                = 8;  // Width in characters, for u8g2_font_6x10_tf and u8g2_font_ncenB08_tr
const int kLCDHeight               = 1;  // Height in characters, for u8g2_font_6x10_tf and u8g2_font_ncenB08_tr
#elif defined (__Use_Font_u8g2_font_unifont_t_symbols__)
const int kLCDWidth                = 8;  // Width in characters, for u8g2_font_6x10_tf and u8g2_font_ncenB08_tr
const int kLCDHeight               = 2;  // Height in characters, for u8g2_font_6x10_tf and u8g2_font_ncenB08_tr
#elif defined (__Use_Font_u8g2_font_pxplusibmvga8_m_all__)
const int kLCDWidth                = 16;  // Width in characters, for u8g2_font_6x10_tf and u8g2_font_ncenB08_tr
const int kLCDHeight               = 2;  // Height in characters, for u8g2_font_6x10_tf and u8g2_font_ncenB08_tr
#else
const int kLCDWidth                = 16;  // Width in characters, for u8g2_font_6x10_tf and u8g2_font_ncenB08_tr
const int kLCDHeight               = 3;  // Height in characters, for u8g2_font_6x10_tf and u8g2_font_ncenB08_tr
#endif
#elif defined (__Use_SSD1306_OLED_HW_I2C_FULL_LCD__)
const int secondButton             = 12;   // For SSD1306 128x32 0.91" // For testing in conjuction with DFRobot shield, use same second button
//const int secondButton             = 6;   // For SSD1306 128x32 0.91"
const int batteryPin               = A3;  // Originally A0
const int kLCDWidth                = 16;
const int kLCDHeight               = 2;
#elif defined (__Use_Small_SSD1306_LCD__)
const int secondButton             = 12;   // For SSD1306 128x32 0.91" // For testing in conjuction with DFRobot shield, use same second button
//const int secondButton             = 6;   // For SSD1306 128x32 0.91"
const int batteryPin               = A3;  // Originally A0
const int kLCDWidth                = 16;
const int kLCDHeight               = 4;  // With 6x8 characters
#elif defined (__Use_Small_SSD1306_LCD_Print_8x16__) || defined (__Use_Small_SSD1306_LCD_Print_8x16_lib__)
const int secondButton             = 12;   // For SSD1306 128x32 0.91" // For testing in conjuction with DFRobot shield, use same second button
//const int secondButton             = 6;   // For SSD1306 128x32 0.91"
const int batteryPin               = A3;  // Originally A0
const int kLCDWidth                = 16;
const int kLCDHeight               = 2;  // With 8x16 characters
#elif defined (__Use_1602_LCD__)
const int secondButton             = 10;  // Original
const int batteryPin               = A0;  // Original
const int kLCDWidth                = 16;
const int kLCDHeight               = 2;
#else
const int secondButton             = 10;  // Original
const int batteryPin               = A0;  // Original
const int kLCDWidth                = 16;
const int kLCDHeight               = 2;
#endif

const int coilVoltageDropPin       = A1;  // Voltage across FET, when FET goes directly to ground - otherwise it is the voltage across the FET and the measuring resistance
const int currentMeasurePin        = A2;
const float kCurrentMeasureR       = 0.5;  //Ohms - Resistance of current measuring resistor
const float kRoomTemperature       = 23.0;

// State Engine states
const int kSTATE_BATTERY_VOLTAGE   = 0;
const int kSTATE_COIL_VOLTAGE      = 1;
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

const int kNumMaterials            = 10; 

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

const int kNumTemperatureUnits     = 3;    

// Control Tyoe
const int kVoltageControl          = 0; 
const int kPowerControl            = 1; 
const int kTemperatureControl      = 2; 

const int kNumControlTypes         = 3;    

// Program Modes
const int kPM_Juice                = 0;
const int kPM_Fresh                = 1;
const int kPM_SpeedRead            = 2;
const int kPM_Diag_VoltRead        = 3;
const int kPM_Diag_BatVoltRead_EE  = 4;
const int kPM_Diag_FETVoltRead_EE  = 5;
const int kPM_Diag_CurVoltRead_EE  = 6;

const int kNumProgramModes         = 7;    

// Diagnostic - Voltage Drop Program Modes
const int kVDPM_Header             = 0;
const int kVDPM_Batt               = 1;
const int kVDPM_FET                = 2;
const int kVDPM_Coil               = 3;
const int kVDPM_CoilPower          = 4;
const int kVDPM_CurrentReadVoltage = 5;

const int kNumVDPModes             = 6;    

#if defined (__Use_Star_wars__)
const char speedMessage[] = {"It is a period of civil war. Rebel spaceships, striking from a hidden base, have won their first victory against the evil Galactic Empire.\
 During the battle, Rebel spies managed to steal secret plans to the Empire's ultimate weapon, the DEATH STAR, an armored space station with enough power to destroy an entire planet.\
 Pursued by the Empire's sinister agents, Princess Leia races home aboard her starship, custodian of the stolen plans that can save her people and restore freedom to the galaxy....\0"}; 
#else
const char speedMessage[] = {"Vape on it!!! yeah\0"}; // default scrolling text
#endif

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
//const int EE_voltage4PowerAddress       = 30;
//const int EE_voltage4TemperatureAddress = 32;

// Units min, max and steps
const float minResistance = 0.0;
const float maxResistance = 2.0;
const int   numResistanceSteps = 20;
const float stepResistanceWeight = (maxResistance - minResistance)/numResistanceSteps;
const float minPower = 10.0;
const float maxPower = 80.0;
const int   numPowerSteps = 70;
const float stepPowerWeight = (maxPower - minPower)/numPowerSteps; 
const float minTemperature = 150.0;
const float maxTemperature = 315.0;
const int   numTemperatureSteps = 33;
const float stepTemperatureWeight = (maxTemperature - minTemperature)/numTemperatureSteps; 
const int   numTemperatureUnitsSteps = kNumTemperatureUnits;  // °C, °F and K
const float minVoltage = 1.0;
const float maxVoltage = 4.2;
//const float incVoltage = 0.1;                                         // results in non-rounded increment
//const int   numVoltageSteps = (maxVoltage-minVoltage)/incVoltage;     // results in non-rounded increment
const int   numVoltageSteps = 32; // (maxVoltage-minVoltage)/incVoltage;    // was 20;
const float stepVoltageWeight = (maxVoltage - minVoltage)/numVoltageSteps;  // this should equal the incVoltage

// Progs are the number of sub settings for a particular function (or State)
// Some of these constants could be redundant (use kNum... instead of num...)
const int   numProgs = kNumProgramModes;      // Used to cycle (wrap around) Vaping display programs
const int   numVoltageDropProgs = kNumVDPModes;      // Used to cycle (wrap around) VoltageDropProgs
const int   numMaterialProgs = kNumMaterials;      // Used to cycle (wrap around) MaterialProgs
const int   numDefaultsSteps = 2;                // yes and no - Reset defaults?
const int   numDefaultsSureSteps = 2;            // yes and no - Are you sure?
const int   numControlTypeSteps = kNumControlTypes;  //  voltage, power, temperature

const int interval = 100;

// Variables

int strPos = 0;
int desiredVoltage = 0; // For safety - We can assign a stored value, from EEPROM, later if we want
int state = 0; 
int wpm = 350;
int readPeriod = 60000 / wpm; //period in ms
char thisWord[30];
char lastWord[30];
char allWords[kLCDHeight][kLCDWidth];
int wordLoc;
long startTime = 0;

// For timing
unsigned long lastMillis = 0;

#if defined (__Use_DFRobot_1602_LCD__)
// initialize the library with the numbers of the interface pins
LiquidCrystalFast lcd(8, 255,  9,  4,  5,  6, 7);   // For DFRobot 1602 shield
#elif defined (__Use_TFT_ILI9163C_Extended_Char_LCD__)
TFT_ILI9163C_Extended_Char lcd = TFT_ILI9163C_Extended_Char(__CS, __DC, __RST); 
#elif defined (__Use_SSD1306_LCD__)
// Page Buffer
//U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C lcd(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);   // pin remapping with ESP8266 HW I2C
// Full buffer
//U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C lcd(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);   // pin remapping with ESP8266 HW I2C
// My extension
SSD1306_Extended_Char lcd(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);   // pin remapping with ESP8266 HW I2C
#elif defined (__Use_SSD1306_OLED_HW_I2C_FULL_LCD__)
SSD1306_OLED_HW_I2C_FULL lcd = SSD1306_OLED_HW_I2C_FULL();
#elif defined (__Use_Small_SSD1306_LCD__)
Small_SSD1306 lcd = Small_SSD1306();
#elif defined (__Use_Small_SSD1306_LCD_Print_8x16__)
Small_SSD1306_Print_8x16 lcd = Small_SSD1306_Print_8x16();
#elif defined (__Use_Small_SSD1306_LCD_Print_8x16_lib__)
Small_SSD1306_Print_8x16_lib lcd = Small_SSD1306_Print_8x16_lib();
#elif defined (__Use_1602_LCD__)
LiquidCrystalFast lcd(9,  8,  7,  6,  5, 4, 3);   // Original GhettoVape III wiring
#else
LiquidCrystalFast lcd(9,  8,  7,  6,  5, 4, 3);   // Original GhettoVape III wiring
#endif
// LCD pins:          RS  RW  EN  D4 D5  D6 D7

// Create a button
#if defined (__Use_MMButton__)
MMButton button(secondButton);
#else
MButton button(secondButton);
#endif

/*
 * 
 *  SETUP
 * 
 * 
 */

void setup() {

#if defined (__Debug__) && defined (__Debug_Presets__)
// Set Test EE defaults
  EE_Presets_Test();
#endif
  
  // Set up analogue input pins:
  pinMode(batteryPin, INPUT);
  pinMode(coilVoltageDropPin, INPUT);
  pinMode(currentMeasurePin, INPUT);

  button.setup();            // set as INPUT, set HIGH (need to change this to LOW, for modified schematic)
//Temporary comment for testing with MomentaryButton
#if !defined (__Use_MomentaryButton__) // only mButton derived objects can use setThreshold()
  button.setThreshold(300);  // 1 sec between short and long hold
#endif

#if defined (__Use_MMButton__) // only MMButton derived objects can use setPullUpDown()
#if defined (__S2_To_HIGH__)
button.setPullUpDown(LOW);  // Pull up button = pull down resistor at input
#else
button.setPullUpDown(HIGH);  // Pull down button = pull up resistor at input
#endif
#endif

#if defined (__Use_TFT_ILI9163C_Extended_Char_LCD__)
  lcd.begin();
  lcd.setTextColor(WHITE, BLACK);  
  lcd.setTextSize(kTextSize);
//  lcd.fillScreen();
#elif defined (__Use_SSD1306_LCD__)
  lcd.begin();
  lcd.enableUTF8Print();          // enable UTF
#if defined (__Use_Font_u8g2_font_6x10_mf__)
  lcd.setFont(u8g2_font_6x10_mf);  // non tranparent font
#elif defined (__Use_Font_u8g2_font_6x10_tf__)
  lcd.setFont(u8g2_font_6x10_tf);
#elif defined (__Use_Font_u8g2_font_ncenB08_tr__)
  lcd.setFont(u8g2_font_ncenB08_tr);
#elif defined (__Use_Font_u8g2_font_ncenB14_tr__)
  lcd.setFont(u8g2_font_ncenB14_tr);
#elif defined (__Use_Font_u8g2_font_unifont_t_symbols__)
  lcd.setFont(u8g2_font_unifont_t_symbols);  //  tranparent font  ? Has omega
#elif defined (__Use_Font_u8g2_font_pxplusibmvga8_m_all__)
  lcd.setFont(u8g2_font_pxplusibmvga8_m_all);
#endif // fonts
  lcd.setFontMode(0);  // non transparent font mode
  lcd.setBitmapMode(0);  // non transparent bitmap mode (should not be needed as this is default)
//  lcd.enableUTF8Print();  // non transparent bitmap mode (should not be needed as this is default)

//  lcd.setFontRefHeightExtendedText();
  lcd.setDrawColor(1);
//  lcd.setFontPosTop();
//  lcd.setFontDirection(0);

#if defined (__Debug__) && defined (__Debug_Welcome__)  // Start Debug - Hello Message
  lcd.clearBuffer();          // clear the internal memory
  lcd.drawStr(30,20,"GhettoVaper");  // write something to the internal memory
//  lcd.drawStr(0,10,"\x2126");  // write something to the internal memory
//  lcd.drawStr(0,16,(char)176);  // write degree to the internal memory - prints "a"
//  lcd.drawStr(0,16,"_01234567890123456789_");  // write degree to the internal memory - prints "a"
//  lcd.drawStr(20,16,char(176));  // write degree to the internal memory - prints "a"
//  lcd.drawStr(30,16,"\260");  // write degree to the internal memory - prints "a"
//  lcd.drawGlyph(5, 30, 0x2126);  /* dec 9731/hex 2603 Snowman */ // Works!!


//  lcd.drawStr(10,10,char(8486));  // write something to the internal memory - -  prints nothing
//  lcd.drawStr(20,10,"\x21\x26");  // write something to the internal memory
//  lcd.drawStr(40,10,"10 \1650");  // write something to the internal memory
//  lcd.drawStr(40,10,char(\1650));  // write something to the internal memory
//        lcd.print(" \1650"); // omega symbol in octal (8486 in decimal) 2126 in hex - for U8g2 u8g2_font_unifont_t_symbols
//        lcd.print(char(8486)); // omega symbol in octal (8486 in decimal) 2126 in hex - for U8g2 u8g2_font_unifont_t_symbols
//        lcd.print("\x21\x26"); // omega symbol in octal (8486 in decimal) 2126 in hex - for U8g2 u8g2_font_unifont_t_symbols
//        lcd.print("\x2126"); // omega symbol in octal (8486 in decimal) 2126 in hex - for U8g2 u8g2_font_unifont_t_symbols

//    lcd.setCursor(0,0); //  works!!!
//    lcd.print(" Ω"); // works!!!!
  lcd.sendBuffer();          // transfer internal memory to the display
  delay(200);
#endif // End Debug - Hello Message
//end setup hit test

#elif defined (__Use_SSD1306_OLED_HW_I2C_FULL_LCD__) || defined (__Use_Small_SSD1306_LCD__) || defined (__Use_Small_SSD1306_LCD_Print_8x16__) || defined (__Use_Small_SSD1306_LCD_Print_8x16_lib__)
  lcd.begin();

#else // we are using a 1602 LCD display and we can configure that and define custom characters
  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
  // Turn on the backlight
  pinMode(lcd_backlight, OUTPUT);
  analogWrite(lcd_backlight, 255);
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
#endif
  lcd.clear();

// Check for unitialised EEPROM
  if (checkOutOfRange())
    EE_Presets();         // Reset EEPROM to defaults
  else {                  // Reset default check questions anyway
    EEPROM.write(EE_defaultsSureAddress, 0); //Reset back to zero/NO - else you are presents with "Yes" at the next "Are you sure?" - should not be needed
    EEPROM.write(EE_defaultsAddress, 0);     //Reset back to zero/NO - else you are presented with "Yes" at the next "Reset Defaults?"

  }
}

void loop() {


#if defined (__S2_To_HIGH__)
  // For push S2 to HIGH
  if(digitalRead(secondButton)) {      // if S2 is held
#elif defined (__MULTI_PUSH_S2__)      // not yet written
  // For multi-push S2
  if(!digitalRead(secondButton)) {    // if S2 is clicked five times
#else
  // For push S2 to LOW - default, as original
  if(!digitalRead(secondButton)) {   // if S2 is held
#endif
    lcd.clear();
    stateMachine();
  }
  else {                             // if S2 does not meet the if
    // Read the voltage across the coil
    EEPROM.write(EE_batteryVoltageDropAddress,analogRead(batteryPin));  // store the analogue read
    EEPROM.write(EE_coilVoltageDropAddress,analogRead(coilVoltageDropPin));  // store the analogue read
    // Read the voltage across the current measuring rsistance
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
        desiredVoltage = (minVoltage + (EEVoltage))*255/(batteryVoltage);                                     // desiredVoltage is not a voltage at all, it is a proportinal binary value mapped between 0 and 255
        if (minVoltage + EEVoltage > batteryVoltage)  // if there isn't sufficient battery life...
          desiredVoltage = 255;                                                                               // then just supply the maximum      
        break;
      }
      case (kPowerControl):
      {
        // For the stored voltage calculated from the power
//        float desiredVoltage = EEPROM.read(EE_voltage4PowerAddress);                                        // desiredVoltage is not a voltage at all, it is a proportinal binary value mapped between 0 and 255

        // For power
        float desiredPower = minPower + EEPROM.read(EE_powerAddress)*stepPowerWeight;
        float resistanceOfCoil = minResistance + EEPROM.read(EE_resistanceAddress)*stepResistanceWeight;

        // For power control - auto adjust
        float currentInCoil = (analogRead(currentMeasurePin)*5.25)/(1024*kAmplifier_Factor*kCurrentMeasureR);
        float powerInCoil = currentInCoil*currentInCoil*resistanceOfCoil;
        
        // For power control - auto adjust
        if (powerInCoil != desiredPower) {
          float newPower = desiredPower-powerInCoil;
          float voltageChange = sqrt(newPower*resistanceOfCoil);
          if (voltageChange < 0)
            desiredVoltage--;  // just decrease the DAC by one - doesn't really matter what the real voltage is
          else if (voltageChange > 0)
            desiredVoltage++;   // just increase the DAC by one - doesn't really matter what the real voltage is
          // Store the changes in EEPROM, EE_voltage4PowerAddress 
//          EEPROM.write(EE_voltage4PowerAddress,desiredVoltage);  // store the analogue read
        }

        // This code below could be set in the state machine/settings, when the power control is set AND when the power changed
        // However, it would need to be saved in EEPROM, as powering off th device would mean that the power control settings are retained, but the desired voltage is lost.
        // This voltage is already saved, in the EE_voltageAddress
        // However, we do not want to mess with the user's settings for the voltage, as it will cause confusion
        // So store as a separate EE_voltage4PowerAddress
        // NOTE: the battery voltage will change (reduce) after the settings have been changed, and so there is an argument for keping these calculations here, and not one-time-only
        // NOTE: there is a need to check for the min voltage - if the battery voltage is below that which is required, then just set to 255
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
        // For the stored voltage calculated from the temperature
//        float desiredVoltage = EEPROM.read(EE_voltage4PowerAddress);                       // desiredVoltage is not a voltage at all, it is a proportinal binary value mapped between 0 and 255
        // This voltage needs to be calculated before it can be stored, and retrieved
        // NOTE: there is a need to check for the min voltage - if the battery voltage is below that which is required, then just set to 255

         // For temperature control, using TCR
        float resistanceOfCoil = minResistance + EEPROM.read(EE_resistanceAddress)*stepResistanceWeight;
        float roomTemperature = kRoomTemperature;
        float currentInCoil = (analogRead(currentMeasurePin)*5.25)/(1024*kAmplifier_Factor*kCurrentMeasureR);
        float resistanceOfVapingCoil =  ((EEPROM.read(EE_batteryVoltageDropAddress) - EEPROM.read(EE_coilVoltageDropAddress))*5.25* currentInCoil)/1024;
        float resistanceOfVapingCoilDelta = resistanceOfVapingCoil - resistanceOfCoil;
        float temperatureOfCoil = roomTemperature + (resistanceOfVapingCoilDelta/(kTCRs[EEPROM.read(EE_materialAddress)]*resistanceOfCoil));
        float desiredTemperature = minTemperature + EEPROM.read(EE_temperatureAddress)*stepTemperatureWeight;

        //For temperature control - auto adjust
        if (temperatureOfCoil != desiredTemperature) {
          float deltaTemperature = desiredTemperature - temperatureOfCoil;
          if (deltaTemperature < 0)
            desiredVoltage--;  // just decrease the DAC by one - doesn't really matter what the real voltage is
          else if (deltaTemperature > 0)
            desiredVoltage++;   // just increase the DAC by one - doesn't really matter what the real voltage is
          // However, what value are we increasing desiredVoltage from exactly?
          //      If we start at a voltage that is too high then the temperature will quickly overshoot, until the desiredVoltage is brought down
          //      If we start at a voltage too low then the desiredTemperature may take a while to achieve
          //      If we have to set a low initial desiredVoltage, where do we set it?
          //            In the state machine/settings when selecting the temperature and when the temperature setting is adjusted?
          // Should it be made to start from:
          //      the last used value, which was used when using voltage control?
          //      a minimum point, say 1V?
          // What value does desiredVoltage have when first switched on? If we assign zero in the declaration then fine
          // NOTE: You can not read an analogue output, without disconnecting the timer. The pin remains an output but stops PWM
          //      See https://forum.arduino.cc/index.php?topic=64965.0
          // NOTE: If 0 or 255 is written to the PWM pin, the timer is disengaged and it acts as a simple digitalWrite()
          //      See http://forum.arduino.cc/index.php?topic=122543.0
          // Should we remember the last used voltage in EEPROM? 
          //      Yes, as powering off the device, will retain the temperature controll settings, but lose the desiredVoltage
          //      Use a separate EEPROM setting, such as EE_voltage4TemperatureAddress
//          EEPROM.write(EE_voltage4TempAddress,desiredVoltage);  // store the analogue read
        }
        break;
      }

      analogWrite(fetPin, desiredVoltage);                                                                   // Activate PWM to trigger NFET
    }
    displayProgram();

  }
}


void stateMachine(){
  while(digitalRead(secondButton));
  delay(50);

#if defined(__Debug__) && defined(__Debug_State__)
state=kSTATE_TEMPERATURE;
#endif

  while(true){
    switch(state) 
    {
      case(kSTATE_BATTERY_VOLTAGE):  // show battery voltage
      {
        lcd.setCursor(0,0);
        //        --|1234567890123456|--
        lcd.print(F("Battery Voltage:"));
        lcd.setCursor(0,1);
        lcd.print(analogRead(batteryPin)*5.2/1024);
        lcd.print(F(" V          "));
        button.check();
        if(button.wasHeld())
        {
//          state = 1;
          state++;
          buttonWasHeld();
        }
        break;
      }

      case(kSTATE_COIL_VOLTAGE):  // adjust coil voltage
      {
        lcd.setCursor(0,0);
        //        --|1234567890123456|--
        lcd.print(F("Coil Voltage:   "));
        lcd.setCursor(0,1);
        lcd.print(minVoltage + EEPROM.read(EE_voltageAddress)*stepVoltageWeight);
        lcd.print(F(" V          "));
        button.check();
        if(button.wasClicked())
        {
          buttonWasClicked();
          EEPROM.write(EE_voltageAddress, (EEPROM.read(EE_voltageAddress)+1)%numVoltageSteps);
        }
        if(button.wasHeld())
        {
//          state = 2;
          state++;
          buttonWasHeld();
        }
        break;
      }

      case(kSTATE_POWER):  // adjust power
      {
        lcd.setCursor(0,0);
        lcd.print(F("Power:          "));
        lcd.setCursor(0,1);
        lcd.print(minPower + EEPROM.read(EE_powerAddress)*stepPowerWeight);
        lcd.print(F(" W         "));
        button.check();
        if(button.wasClicked())
        {
          buttonWasClicked();
          EEPROM.write(EE_powerAddress, (EEPROM.read(EE_powerAddress)+1)%numPowerSteps);
          // Calculate the voltage required
          float voltsForPower = sqrt((minPower + EEPROM.read(EE_powerAddress)*stepPowerWeight)*(minResistance + EEPROM.read(EE_resistanceAddress)*stepResistanceWeight));
          EEPROM.write(EE_voltageAddress, (voltsForPower-minVoltage)/stepVoltageWeight);
        }
        if(button.wasHeld())
        {
//          state = 3;
          state++;
          buttonWasHeld();
        }
        break;
      }

      case(kSTATE_RESISTANCE):  // adjust coil resistance
      {
        lcd.setCursor(0,0);
        lcd.print(F("Coil Resistance:"));
        lcd.setCursor(0,1);
        lcd.print(minResistance + EEPROM.read(EE_resistanceAddress)*stepResistanceWeight);
#if defined (__Use_TFT_ILI9163C_Extended_Char_LCD__)
        lcd.print(F(" \351          ")); // omega symbol in octal (0xE9, 233 in decimal) - for GFX
#elif defined (__Use_SSD1306_LCD__)
        lcd.print(F(" Ω          ")); // omega symbol in octal (247 in decimal) - for Adafruit SSD1306

//            lcd.print(" \367"); // omega symbol in octal (247 in decimal) - for Adafruit SSD1306
//        lcd.print(" \1212"); /// omega symbol in octal (650 in decimal) - for U8g2 u8g2_font_6x10_mf

//        lcd.setFont(u8g2_font_10x20_t_greek);
//        lcd.print(" \1650"); // omega symbol in octal (937 in decimal) - for U8g2 u8g2_font_6x10_mf
//        lcd.print((char)937); // omega symbol in octal (937 in decimal) - for U8g2 u8g2_font_6x10_mf

//        lcd.setFont(u8g2_font_unifont_t_symbols);
//        lcd.print(" \1650"); // omega symbol in octal (8486 in decimal) 2126 in hex - for U8g2 u8g2_font_unifont_t_symbols
//        lcd.print(char(8486)); // omega symbol in octal (8486 in decimal) 2126 in hex - for U8g2 u8g2_font_unifont_t_symbols
//        lcd.print("\x21\x26"); // omega symbol in octal (8486 in decimal) 2126 in hex - for U8g2 u8g2_font_unifont_t_symbols
//        lcd.print("\x2126"); // omega symbol in octal (8486 in decimal) 2126 in hex - for U8g2 u8g2_font_unifont_t_symbols
//        lcd.drawGlyph(50, 28, 0x2126);  /* dec 8486/hex 0x2126 Omega */

//        lcd.setFont(u8g2_font_6x10_mf);
#elif defined (__Use_Small_SSD1306_LCD_Print_8x16__) || defined (__Use_Small_SSD1306_LCD_Print_8x16_lib__)
//         lcd.print(F(" \141          ")); // omega symbol in octal (0xE9, 97 in decimal) - for SSD1306_OLED_HW_I2C_LIB 8x16
         lcd.print(F(" \201          ")); // omega symbol in octal (0xE9, 97+32 in decimal) - for SSD1306_OLED_HW_I2C_LIB 8x16
#elif defined (__Use_1602_LCD__) || defined (__Use_DFRobot_1602_LCD__)
//        lcd.print((char)244); // Ohm symbol (Omega)
        lcd.print(F(" \364          ")); // Ohm symbol (Omega) octal (244 in decimal)
#else
        lcd.print(F(" \364          ")); // Ohm symbol (Omega) octal (244 in decimal)
#endif
        button.check();
        if(button.wasClicked())
        {
          buttonWasClicked();
          EEPROM.write(EE_resistanceAddress, (EEPROM.read(EE_resistanceAddress)+1)%numResistanceSteps);
        }
        if(button.wasHeld())
        {
//          state = 4;
          state++;
          buttonWasHeld();
        }
        break;
      }

      case(kSTATE_MATERIAL):  // adjust material
      {
        lcd.setCursor(0,0);
        //        --|1234567890123456|-- <----- Measure    
        lcd.print(F("Coil Material:  "));
        lcd.setCursor(0,1);
        switch(EEPROM.read(EE_materialAddress))
        {
          case(kMaterial_SS304):
            lcd.print(F("SS 304          "));
            break;
          case(kMaterial_SS316):
            lcd.print(F("SS 316          "));
            break;
          case(kMaterial_SS317):
            lcd.print(F("SS 317          "));
            break;
          case(kMaterial_SS430):
            lcd.print(F("SS 430          "));
            break;
          case(kMaterial_Ni200):
            lcd.print(F("Ni200           "));
            break;
          case(kMaterial_Ti):
            lcd.print(F("Ti              "));
            break;
          case(kMaterial_Tungsten):
            lcd.print(F("Tungsten        "));
            break;
          case(kMaterial_NiFe30):
            lcd.print(F("NiFe30          "));
            break;
          case(kMaterial_Kanthal_A1):
            lcd.print(F("Kanthal A/APM   "));
            break;
          case(kMaterial_Kanthal_A):
            lcd.print(F("Kanthal A/AE+F/D"));
        //            --|1234567890123456|-- <----- Measure    
  // -----------------  "                " <----- Measure      
            break;
        }

        button.check();
        if(button.wasClicked())
        {
          buttonWasClicked();
          EEPROM.write(EE_materialAddress, (EEPROM.read(EE_materialAddress)+1)%numMaterialProgs);
        }
        if(button.wasHeld())
        {
//          state = 5;
          state++;
          buttonWasHeld();
        }
        break;
      }

      case(kSTATE_TEMPERATURE):  // adjust temperature
      {
        lcd.setCursor(0,0);
#if defined (__Use_Small_SSD1306_LCD_Print_8x16__) || defined (__Use_Small_SSD1306_LCD_Print_8x16_lib__)
        //        --|1234567890123456|-- <----- Measure    
        lcd.print(F("Coil Temperature"));
#else
        lcd.print(F("Coil Temperature:"));
#endif
        lcd.setCursor(0,1);
        switch (EEPROM.read(EE_temperatureUnitsAddress))
        {
          case(kTemperatureUnits_F):
          {
            lcd.print(((minTemperature + EEPROM.read(EE_temperatureAddress)*stepTemperatureWeight)*1.8) + 32);
#if defined (__Use_TFT_ILI9163C_Extended_Char_LCD__)
            lcd.print(F(" \367F       ")); // 0 = Fahrenheit // degree symbol in octal (247 in decimal)
#elif defined (__Use_SSD1306_LCD__)
//            lcd.print(" \367F"); // 0 = Fahrenheit // degree symbol in octal (247 in decimal) - for Adafruit SSD1306
            lcd.print(F(" \260F       ")); // 0 = Fahrenheit // degree symbol in octal (176 in decimal) - for U8g2 u8g2_font_6x10_mf
#elif defined (__Use_Small_SSD1306_LCD_Print_8x16__) || defined (__Use_Small_SSD1306_LCD_Print_8x16_lib__)
//            lcd.print(F(" \140F       ")); // 0 = Fahrenheit // degree symbol in octal (96 in decimal) - for SSD1306_OLED_HW_I2C_LIB 8x16
            lcd.print(F(" \200F       ")); // 0 = Fahrenheit // degree symbol in octal (128 in decimal (have to add 32 to 96)) - for SSD1306_OLED_HW_I2C_LIB 8x16
#elif defined (__Use_1602_LCD__) || defined (__Use_DFRobot_1602_LCD__)
            lcd.print(F(" \337F       ")); // 0 = Fahrenheit // degree symbol in octal (247 in decimal)
#else
            lcd.print(F(" \337F       ")); // 0 = Fahrenheit // degree symbol in octal (223 in decimal)
#endif
            break;
          }  
          case(kTemperatureUnits_C):
          {
            lcd.print(minTemperature + EEPROM.read(EE_temperatureAddress)*stepTemperatureWeight);
#if defined (__Use_TFT_ILI9163C_Extended_Char_LCD__)
            lcd.print(F(" \367C       ")); // 1 = Centigrade // degree symbol in octal (247 in decimal)
#elif defined (__Use_SSD1306_LCD__)
//            lcd.print(" \367C"); // 1 = Centigrade // degree symbol in octal (247 in decimal) - for Adafruit SSD1306
            lcd.print(F(" \260C       ")); // 1 = Centigrade // degree symbol in octal (176 in decimal) - for U8g2 u8g2_font_6x10_mf
#elif defined (__Use_Small_SSD1306_LCD_Print_8x16__) || defined (__Use_Small_SSD1306_LCD_Print_8x16_lib__)
//            lcd.print(F(" \140C       ")); // 1 = Centigrade // degree symbol in octal (96 in decimal) - for SSD1306_OLED_HW_I2C_LIB 8x16
            lcd.print(F(" \200C       ")); // 1 = Centigrade // degree symbol in octal (128 in decimal (have to add 32 to 96/) - for SSD1306_OLED_HW_I2C_LIB 8x16
#elif defined (__Use_1602_LCD__) || defined (__Use_DFRobot_1602_LCD__)
            lcd.print(F(" \337C       ")); // 1 = Centigrade // degree symbol in octal (247 in decimal)
#else
            lcd.print(F(" \337C       ")); // 1 = Centigrade // degree symbol in octal (223 in decimal)
#endif
            break;                  
          }
          case(kTemperatureUnits_K):
          {
// dtostrf() is not required as there is a set number of characters
//            static char outstr[15];
//            lcd.print(dtostrf((minTemperature + EEPROM.read(EE_temperatureAddress)*stepTemperatureWeight)+273.15,6,2,outstr));
            lcd.print((minTemperature + EEPROM.read(EE_temperatureAddress)*stepTemperatureWeight)+273.15);
            lcd.print(F(" K        "));     // 2 = Kelvin 
            break;               
          }
        }
        button.check();
        if(button.wasClicked())
        {
          buttonWasClicked();
          EEPROM.write(EE_temperatureAddress, (EEPROM.read(EE_temperatureAddress)+1)%numTemperatureSteps);
        }
        if(button.wasHeld())
        {
//          state = 4;
          state++;
          buttonWasHeld();
        }
        break;
      }

      case(kSTATE_TEMPERATURE_UNITS):  // adjust temperature units
      {
        lcd.setCursor(0,0);
#if defined (__Use_Small_SSD1306_LCD_Print_8x16__) || defined (__Use_Small_SSD1306_LCD_Print_8x16_lib__)
        //        --|1234567890123456|-- <----- Measure    
        lcd.print(F("Temperature unit"));
#else
        lcd.print(F("Temperature units:"));
#endif
        lcd.setCursor(0,1);
        switch (EEPROM.read(EE_temperatureUnitsAddress))
        {
          case(kTemperatureUnits_F):
          {
#if defined (__Use_TFT_ILI9163C_Extended_Char_LCD__)
            lcd.print(F(" \367F              ")); // 0 = Fahrenheit // degree symbol in octal (247 in decimal)
#elif defined (__Use_SSD1306_LCD__)
//            lcd.print(" \367F"); // 0 = Fahrenheit // degree symbol in octal (247 in decimal) - for Adafruit SSD1306
            lcd.print(F(" \260F              ")); // 0 = Fahrenheit // degree symbol in octal (176 in decimal) - for U8g2 u8g2_font_6x10_mf
#elif defined (__Use_Small_SSD1306_LCD_Print_8x16__) || defined (__Use_Small_SSD1306_LCD_Print_8x16_lib__)
            lcd.print(F(" \200F       ")); // 0 = Fahrenheit // degree symbol in octal (96+32 in decimal) - for SSD1306_OLED_HW_I2C_LIB 8x16
#elif defined (__Use_1602_LCD__) || defined (__Use_DFRobot_1602_LCD__)
            lcd.print(F(" \337F              ")); // 0 = Fahrenheit // degree symbol in octal (247 in decimal)
#else
            lcd.print(F(" \337F              ")); // 0 = Fahrenheit // degree symbol in octal (223 in decimal)
#endif
            break;
          }
          case(kTemperatureUnits_C):
          {
#if defined (__Use_TFT_ILI9163C_Extended_Char_LCD__)
  // -----------------"                " ----- Measure      
            lcd.print(F(" \367C              ")); // 1 = Centigrade // degree symbol in octal (247 in decimal)
#elif defined (__Use_SSD1306_LCD__)
//            lcd.print(" \367C              "); // 1 = Centigrade // degree symbol in octal (247 in decimal) - for Adafruit SSD1306
            lcd.print(F(" \260C              ")); // 1 = Centigrade // degree symbol in octal (176 in decimal) - for U8g2 u8g2_font_6x10_mf
#elif defined (__Use_Small_SSD1306_LCD_Print_8x16__) || defined (__Use_Small_SSD1306_LCD_Print_8x16_lib__)
            lcd.print(F(" \200C       ")); // 1 = Centigrade // degree symbol in octal (92+32 in decimal) - for SSD1306_OLED_HW_I2C_LIB 8x16
#elif defined (__Use_1602_LCD__) || defined (__Use_DFRobot_1602_LCD__)
            lcd.print(F(" \337C              ")); // 1 = Centigrade // degree symbol in octal (247 in decimal)
#else
            lcd.print(F(" \337C              ")); // 1 = Centigrade // degree symbol in octal (223 in decimal)
#endif
            break;
          }
          case(kTemperatureUnits_K):
          {
            lcd.print(F(" K              "));     // 2 = Kelvin    
            break;
          }
        }
        button.check();
        if(button.wasClicked())
        {
          buttonWasClicked();
          EEPROM.write(EE_temperatureUnitsAddress, (EEPROM.read(EE_temperatureUnitsAddress)+1)%numTemperatureUnitsSteps);
        }
        if(button.wasHeld())
        {
//          state = 4;
          state++;
          buttonWasHeld();
        }
        break;
      }

// This does not make much sense - It does not display whilst vaping, only displays the values measured during the last vape
// Would be better to not use EE_programVoltageDropAddress, but alway start at case variable == 0, display "Diagnostics", then 
// - subsequent clicks cycle through the values
// - hold, resets case variable to 0
      case(kSTATE_VOLTAGEDROP):  // show coil voltage drop and power
      {
        // Use state machine to show:
        switch(EEPROM.read(EE_programVoltageDropAddress)){
          case(kVDPM_Header):
          {
        //   Print Battery Voltage when vaping
            lcd.setCursor(0,0);
  // -----------------"                " ----- Measure      
            lcd.print(F("Diagnostics:    "));
            lcd.setCursor(0,1);
            lcd.print(F("                "));
            break;
          }
          
          case(kVDPM_Batt):
          {
        //   Print Battery Voltage when vaping
            lcd.setCursor(0,0);
            lcd.print(F("Battery Voltage:"));
            lcd.setCursor(0,1);
            lcd.print(EEPROM.read(EE_batteryVoltageDropAddress)*5.2/1024);
            lcd.print(F(" V"));
            break;
          }
          
          case(kVDPM_FET):
          {
            //   Print Voltage below coil
            lcd.setCursor(0,0);
            lcd.print(F("FET Voltage:    "));
            lcd.setCursor(0,1);
            lcd.print(EEPROM.read(EE_coilVoltageDropAddress)*5.2/1024);
            lcd.print(F(" V"));
            break;
          }
          
          case(kVDPM_Coil):
          {
            //   Print  Voltage Drop across coil
            lcd.setCursor(0,0);
            lcd.print(F("Coil Voltage:   "));
            lcd.setCursor(0,1);
            lcd.print((EEPROM.read(EE_batteryVoltageDropAddress)-EEPROM.read(EE_coilVoltageDropAddress))*5.2/1024);
            lcd.print(F(" V"));
            break;
          }
          
          case(kVDPM_CoilPower):
          {
            //   Print power through coil
            int batteryVoltageDrop = EEPROM.read(EE_batteryVoltageDropAddress);
            int coilVoltageDrop = EEPROM.read(EE_coilVoltageDropAddress);
            lcd.setCursor(0,0);
            lcd.print(F("Coil Power:     "));
            lcd.setCursor(0,1);
//            lcd.print((((EEPROM.read(EE_batteryVoltageDropAddress)-EEPROM.read(EE_coilVoltageDropAddress))*5.2/1024)*((EEPROM.read(EE_batteryVoltageDropAddress)-EEPROM.read(EE_coilVoltageDropAddress))*5.2/1024))/(minResistance + EEPROM.read(EE_resistanceAddress)*stepResistanceWeight));
            lcd.print((((batteryVoltageDrop-coilVoltageDrop)*5.2/1024)*((batteryVoltageDrop-coilVoltageDrop)*5.2/1024))/(minResistance + EEPROM.read(EE_resistanceAddress)*stepResistanceWeight)); // slightly faster
            lcd.print(F(" W"));
            break;
          }
          
          case(kVDPM_CurrentReadVoltage):
          {
            //   Print voltage at current measuring resistance
            lcd.setCursor(0,0);
            lcd.print(F("Current Voltage:"));
            lcd.setCursor(0,1);
            lcd.print(EEPROM.read(EE_currentMeasureAddress)*5.2/1024);
            lcd.print(F(" V"));
            break;
          }
        }
        button.check();
        if(button.wasClicked())
        {
          buttonWasClicked();
          EEPROM.write(EE_programVoltageDropAddress, (EEPROM.read(EE_programVoltageDropAddress)+1)%numVoltageDropProgs);
        }
        if(button.wasHeld())
        {
          EEPROM.write(EE_programVoltageDropAddress, 0); // set back to header
          state++;
          buttonWasHeld();
//         state = 6;
        }
        break;
      }

      case(kSTATE_READER):
      {
//        lcd.clear();
        lcd.setCursor(0,0);
  // -------------"                " ----- Measure      
        lcd.print(F("Vaping Display: "));
        lcd.setCursor(0,1);
        switch(EEPROM.read(EE_programAddress)){
          case(kPM_Juice):
            lcd.print(F("JUICE           "));            // Display JUICE in custom characters
            break;
          case(kPM_Fresh):
            lcd.print(F("FRESH           "));            // Display FRESH in custom characters
            break;
          case(kPM_SpeedRead):             // Display the message
            lcd.print(F("SpeedRead       "));
            break;
          case(kPM_Diag_VoltRead):         // Display the ADC and voltages of the battery and FET
            lcd.print(F("Diag ADC BAT FET"));
            break;
          case(kPM_Diag_BatVoltRead_EE):   // Display the voltage and EE storage for battery
            lcd.print(F("Diag V EE BATT  "));
            break;
          case(kPM_Diag_FETVoltRead_EE):   // Display the voltage and EE storage for the FET
            lcd.print(F("Diag V EE FET   "));
            break;
          case(kPM_Diag_CurVoltRead_EE):   // Display the voltage and EE storage for the current measuring resistance
            lcd.print(F("Diag V EE CUR   "));
            break;
        }

        button.check();
        if(button.wasClicked())
        {
          buttonWasClicked();
          EEPROM.write(EE_programAddress, (EEPROM.read(EE_programAddress)+1)%numProgs);
        }
        if(button.wasHeld())
        {
          state++;
          buttonWasHeld();
//          state = 7;
        }
        break;
      }

      case(kSTATE_ADDRESS):
      {
//        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(F("Let's roll!!    "));
        lcd.setCursor(0,1);
        lcd.print(F("                "));
        button.check();
        if(button.wasHeld())
        {
          state++;;
          buttonWasHeld();
        }
        break;
      }

      case(kSTATE_DEFAULTS):
      {
//        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(F("Reset defaults? "));
        lcd.setCursor(0,1);
        if (EEPROM.read(EE_defaultsAddress))
          lcd.print(F("YES             ")); // 1 = YES
        else
          lcd.print(F("NO              ")); // 0 = NO
        button.check();
        if(button.wasClicked())
        {
          buttonWasClicked();
          EEPROM.write(EE_defaultsAddress, (EEPROM.read(EE_defaultsAddress)+1)%numDefaultsSteps);
        }
        if(button.wasHeld()) {
          if (EEPROM.read(EE_defaultsAddress)) {
            state = kSTATE_SURE;
          }
          else {
            state++;
//            EEPROM.write(EE_defaultsAddress, 0);//Reset back to zero/NO - else you are presented with "Yes" at the next "Reset Defaults?" - should not be needed
          }
          buttonWasHeld();
        }
        break;
      }

      case(kSTATE_CONTROL_TYPE):  // adjust temperature units
      {
//       lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(F("Control by:     "));
        lcd.setCursor(0,1);
        switch (EEPROM.read(EE_controlTypeAddress))
        {
          case(kVoltageControl):
          {
            lcd.print(F("Voltage         ")); 
            break;
          }
          case(kPowerControl):
          {
            lcd.print(F("Power           ")); // 1 = Centigrade
            break;
          }
          case(kTemperatureControl):
          {
            lcd.print(F("Temperature     "));     // 2 = Kelvin    
            break;                          
          }
        }
        button.check();
        if(button.wasClicked())
        {
          buttonWasClicked();
          EEPROM.write(EE_controlTypeAddress, (EEPROM.read(EE_controlTypeAddress)+1)%numControlTypeSteps);
        }
        if(button.wasHeld())
        {
//          state = 4;
          state++;
          buttonWasHeld();
        }
        break;
      }

      
     case(kSTATE_SURE):
      {
//        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(F("Are you sure?   "));
        lcd.setCursor(0,1);
        if (EEPROM.read(EE_defaultsSureAddress))
          lcd.print(F("YES             ")); // 1 = YES
        else
          lcd.print(F("NO              ")); // 0 = NO
        button.check();
        if(button.wasClicked())
        {
          buttonWasClicked();
          EEPROM.write(EE_defaultsSureAddress, (EEPROM.read(EE_defaultsSureAddress)+1)%numDefaultsSureSteps);
        }
        if(button.wasHeld()) {
          if (EEPROM.read(EE_defaultsSureAddress)) {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print(F("Resetting..."));
            delay(300);
            EE_Presets();
          }
          else
          {
 //           EEPROM.write(EE_defaultsSureAddress, 0); //Reset back to zero/NO - else you are presents with "Yes" at the next "Are you sure?" - should not be needed
            EEPROM.write(EE_defaultsAddress, 0);     //Reset back to zero/NO - else you are presented with "Yes" at the next "Reset Defaults?"
          }
          state = 0;  // go back to state 0
          buttonWasHeld();
        }
        break;
      }
    }

    if (state >= kNumStates && state < 99) {   // Sanity Check
      state= 0;
    }

    delay(30); 
  }
}

void buttonWasClicked(){
//  lcd.clear();  //causes flashing, when changing settings, only need to change the value on the lower line, not the title on the top line as well

/*  
  lcd.setCursor(0,1);
  for (int n=0;n<kLCDWidth;n++)  // this is very slow
    lcd.print(" ");              // this is very slow
//  lcd.print("                ");  // can not do this, maybe screen is wider than 16
*/

//Clear only second line, except for Diagnostic state
// This is too slow, and still causes flashing (in the second line...
// ... also not needed as the prints now contain 16 characters (with padding spaces)
/*
  if (state==kSTATE_VOLTAGEDROP){ // for the diagnostic state...
    lcd.clear();                  // ...just clear whole screen
  } else {                        // for all other settings screens...
    clearLCDSecondLine();         // ...clear only bottom line
  }
*/

// Not required as we clear only second line now
//#if defined (__Use_SSD1306_LCD__)
//    lcd.sendBuffer();          // transfer internal memory to the display
//#else
//  lcd.clear();
//#endif
}

void buttonWasHeld(){
//  lcd.clear();
  
//#if defined (__Use_SSD1306_LCD__)
//    lcd.sendBuffer();          // transfer internal memory to the display
//#else
//  lcd.clear();
//#endif
}
/*
void clearLCDSecondLine(){
//#define __Useclearfor__
//#define __UseStrCopyBlanks__ 
#define __UseStrCopyBlanks2__ 
//#define __UseBlankLine__ 

#if defined (__Useclearfor__)
  lcd.setCursor(0,1);
  for (int n=0;n<kLCDWidth;n++)  // this is very slow
    lcd.print(" ");              // this is very slow

#elif defined (__UseStrCopyBlanks__)
  lcd.setCursor(0,1);
  char my_str[] = "                                                  ";

  char tmpString[kLCDWidth];
  strcpy (tmpString, my_str);
  tmpString[kLCDWidth] = '\0';
  lcd.print(tmpString);  

  my_str[kLCDWidth] = '\0';
  lcd.print(my_str);  

#elif defined (__UseStrCopyBlanks2__)  // quicker than for loop
  lcd.setCursor(0,1);
  char my_str[] = "                                                  ";

  my_str[kLCDWidth] = '\0';
  lcd.print(my_str);  

#elif defined (__UseBlankLine__)
  lcd.setCursor(0,1);
  lcd.print("                ");  // can not do this, maybe screen is wider than 16

#endif
}
*/
void displayProgram() {

  if (EEPROM.read(EE_programAddress)>=numProgs)  // if numProgs is out of range, on a freshly installed machine (bug fix)
    EEPROM.write(EE_programAddress,0); // set it to zero
  switch(EEPROM.read(EE_programAddress))
  {
    case(kPM_Juice):
    {
      //JUICE
//      do 
//      {
#if !defined (__Use_TFT_ILI9163C_Extended_Char_LCD__) && !defined (__Use_SSD1306_LCD__)  && !defined (__Use_SSD1306_OLED_HW_I2C_FULL_LCD__)  && !defined (__Use_Small_SSD1306_LCD__)  && !defined (__Use_Small_SSD1306_LCD_Print_8x16__)  && !defined (__Use_Small_SSD1306_LCD_Print_8x16_lib__)
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
#else
        lcd.setCursor(0,0);
        lcd.print(F("JUICE"));
        delay(interval);
#endif
        lcd.clear();
        delay(interval);
//      }
//      while(true);
      break;
    }

    case(kPM_Fresh):
    {
//      do 
//      {
#if !defined (__Use_TFT_ILI9163C_Extended_Char_LCD__) && !defined (__Use_SSD1306_LCD__)  && !defined (__Use_SSD1306_OLED_HW_I2C_FULL_LCD__)  && !defined (__Use_Small_SSD1306_LCD__)  && !defined (__Use_Small_SSD1306_LCD_Print_8x16__)  && !defined (__Use_Small_SSD1306_LCD_Print_8x16_lib__)
        customF(0);    // displays custom 0 on the LCD
        customR(3);
        customE(7);
        customS(10);
        customH(13);
        delay(interval);
#else
        lcd.setCursor(0,0);
        lcd.print(F("FRESH"));
        delay(interval);
#endif
        lcd.clear(); 
        delay(interval);
//      }
//      while(true);
      break;
    }

    case(kPM_SpeedRead):
    {
      speedRead4();
      break;
    }
    
    // Display the ADC values and voltages of the battery and FET
    case(kPM_Diag_VoltRead):
    {
      if (millis()-lastMillis>1000){
        lastMillis=millis();
#if defined (__Use_SSD1306_LCD__)
        lcd.setPrintMode(false);    // disable individual print
#elif defined(__Use_TFT_ILI9163C_Extended_Char_LCD__)
//don't clear for 1.44' display
#else
        lcd.clear();
#endif
        lcd.setCursor(0,0);
        lcd.print(F("BAT     "));
        lcd.setCursor(4,0);
//        lcd.print(analogRead(batteryPin));
        lcd.print(u2s(analogRead(batteryPin),4));
        lcd.setCursor(9,0);
        lcd.print(analogRead(batteryPin)*5.2/1024);
        lcd.setCursor(14,0);
        lcd.print("V");
        lcd.setCursor(0,1);
        lcd.print(F("FET     "));
        lcd.setCursor(4,1);
//        lcd.print(analogRead(coilVoltageDropPin));
        lcd.print(u2s(analogRead(coilVoltageDropPin),4));
        lcd.setCursor(9,1);
        lcd.print(analogRead(coilVoltageDropPin)*5.2/1024);
        lcd.setCursor(14,1);
        lcd.print("V");
#if defined (__Use_SSD1306_LCD__)
        lcd.sendBuffer();          // transfer internal memory to the display
        lcd.setPrintMode(true);    // re-enable individual print
#endif
      }
      break;
    }

    // Display the voltage and EE storage for battery
    case(kPM_Diag_BatVoltRead_EE):
    {
      if (millis()-lastMillis>1000){
        lastMillis=millis();
#if defined (__Use_SSD1306_LCD__)
        lcd.setPrintMode(false);    // disable individual print
#elif defined(__Use_TFT_ILI9163C_Extended_Char_LCD__)
//don't clear for 1.44' display
#else
        lcd.clear();
#endif
        lcd.setCursor(0,0);
        lcd.print(F("BAT     "));
        lcd.setCursor(4,0);
//        lcd.print(analogRead(batteryPin));
        lcd.print(u2s(analogRead(batteryPin),4));
        lcd.setCursor(9,0);
        lcd.print(analogRead(batteryPin)*5.2/1024);
        lcd.setCursor(14,0);
        lcd.print("V");
        lcd.setCursor(0,1);
        lcd.print(F("EEB     "));
        lcd.setCursor(4,1);
//        lcd.print(EEPROM.read(EE_batteryVoltageDropAddress));
        lcd.print(u2s(EEPROM.read(EE_batteryVoltageDropAddress),4));
        lcd.setCursor(9,1);
        lcd.print(EEPROM.read(EE_batteryVoltageDropAddress)*5.2/1024);
        lcd.setCursor(14,1);
        lcd.print("V");
#if defined (__Use_SSD1306_LCD__)
        lcd.sendBuffer();          // transfer internal memory to the display
        lcd.setPrintMode(true);    // re-enable individual print
#endif
      }
      break;
    }
    
    // Display the voltage and EE storage for the FET
    case(kPM_Diag_FETVoltRead_EE):
    {
      if (millis()-lastMillis>1000){
        lastMillis=millis();
#if defined (__Use_SSD1306_LCD__)
        lcd.setPrintMode(false);    // disable individual print
#elif defined(__Use_TFT_ILI9163C_Extended_Char_LCD__)
//don't clear for 1.44' display
#else
        lcd.clear();
#endif
        lcd.setCursor(0,0);
        lcd.print(F("FET     "));
        lcd.setCursor(4,0);
//        lcd.print(analogRead(coilVoltageDropPin));
        lcd.print(u2s(analogRead(coilVoltageDropPin),4));
        lcd.setCursor(9,0);
        lcd.print(analogRead(coilVoltageDropPin)*5.2/1024);
        lcd.setCursor(14,0);
        lcd.print("V");
        lcd.setCursor(0,1);
        lcd.print(F("EEF     "));
        lcd.setCursor(4,1);
//        lcd.print(EEPROM.read(EE_coilVoltageDropAddress));
        lcd.print(u2s(EEPROM.read(EE_coilVoltageDropAddress),4));
        lcd.setCursor(9,1);
        lcd.print(EEPROM.read(EE_coilVoltageDropAddress)*5.2/1024);
        lcd.setCursor(14,1);
        lcd.print("V");
#if defined (__Use_SSD1306_LCD__)
        lcd.sendBuffer();          // transfer internal memory to the display
        lcd.setPrintMode(true);    // re-enable individual print
#endif
      }
      break;
    }
    
    // Display the voltage and EE storage for the current measuring resistance
    case(kPM_Diag_CurVoltRead_EE):   
    {
      if (millis()-lastMillis>1000){
        lastMillis=millis();
#if defined (__Use_SSD1306_LCD__)
        lcd.setPrintMode(false);    // disable individual print
#elif defined(__Use_TFT_ILI9163C_Extended_Char_LCD__)
//don't clear for 1.44' display
#else
        lcd.clear();
#endif
        lcd.setCursor(0,0);
        lcd.print(F("CUR     "));
        lcd.setCursor(4,0);
//        lcd.print(analogRead(currentMeasurePin));
        lcd.print(u2s(analogRead(currentMeasurePin),4));
        lcd.setCursor(9,0);
        lcd.print(analogRead(currentMeasurePin)*5.2/1024);
        lcd.setCursor(14,0);
        lcd.print("V");
        lcd.setCursor(0,1);
        lcd.print(F("EEC     "));
        lcd.setCursor(4,1);
//        lcd.print(EEPROM.read(EE_currentMeasureAddress));
        lcd.print(u2s(EEPROM.read(EE_currentMeasureAddress),4));
        lcd.setCursor(9,1);
        lcd.print(EEPROM.read(EE_currentMeasureAddress)*5.2/1024);
        lcd.setCursor(14,1);
        lcd.print("V");
#if defined (__Use_SSD1306_LCD__)
        lcd.sendBuffer();          // transfer internal memory to the display
        lcd.setPrintMode(true);    // re-enable individual print
#endif
      }
      break;
    }
  }
}
/*
void speedRead(){
  const int kLCDWidth = 16;
  int i;
  strPos = 0;
  boolean firstScreen=true;
  while(speedMessage[strPos] != '\0'){
    lcd.clear();
    for (int y=0; y<2; y++) {
      for(i = 0; speedMessage[strPos] != ' ' && speedMessage[strPos] != '\0'; i++){
        thisWord[i] = speedMessage[strPos++];
      }
      if (speedMessage[strPos] != '\0')
        strPos++;
      thisWord[i] = '\0';
//      lcd.setCursor(4-i/5,y);
      if (!firstScreen){
          lcd.setCursor(0,0);
          for (int blank = 0; blank<kLCDWidth;blank++)lcd.print(" ");
          lcd.setCursor(8-strlen(lastWord)/2,0);
          lcd.print(lastWord);
          lcd.setCursor(0,1);
          for (int blank = 0; blank<kLCDWidth;blank++)lcd.print(" ");
          lcd.setCursor(8-strlen(thisWord)/2,1);
          lcd.print(thisWord);
      } else {  //first screen, i.e. start of message starts by scrolling down. Thereafter is scrolls up - This is a bit odd looking
          lcd.setCursor(8-strlen(thisWord)/2,y);
          lcd.print(thisWord);
      }
      if (thisWord[i-1] == '.'  || thisWord[i-1] == ',')
        delay(2500);
      else
        delay(1000);
      strcpy(lastWord, thisWord);
    }
    firstScreen=false;
  }
}

void speedRead2(){
  const int kLCDWidth = 16;
  const int kLCDHeight = 2;
  int i;
  strPos = 0;
  boolean firstScreen=true;
  boolean lastScreen=false;
  boolean endIt=false;
  while((speedMessage[strPos] != '\0' || lastScreen) && !endIt){
    if (lastScreen) {
      lastScreen=false;
      endIt=true;
    }
    lcd.clear();
    for (int y=0; y<kLCDHeight; y++) {
      for(i = 0; speedMessage[strPos] != ' ' && speedMessage[strPos] != '\0'; i++){
        thisWord[i] = speedMessage[strPos++];
      }
      if (speedMessage[strPos] != '\0') 
        strPos++;
      else
        lastScreen=true;      
      thisWord[i] = '\0';
      if (!firstScreen){
          lcd.setCursor(0,0);
          for (int blank = 0; blank<kLCDWidth;blank++)lcd.print(" ");
          lcd.setCursor(8-strlen(lastWord)/2,0);
          lcd.print(lastWord);
          lcd.setCursor(0,1);
          for (int blank = 0; blank<kLCDWidth;blank++)lcd.print(" ");
          lcd.setCursor(8-strlen(thisWord)/2,1);
          lcd.print(thisWord);
      } else {  //first screen, i.e. start of message starts by scrolling up.  - This is better looking
          lcd.setCursor(8-strlen(thisWord)/2,1);
          lcd.print(thisWord);
      }
      if (thisWord[i-1] == '.'  || thisWord[i-1] == ',')
        delay(2500);
      else
        delay(1000);
      strcpy(lastWord, thisWord);
      firstScreen=false;
    }
  }
}

void speedRead3(){
  int i;
  strPos = 0;
  boolean firstScreen=true;
  boolean lastScreen=false;
  boolean endIt=false;
  while((speedMessage[strPos] != '\0' || lastScreen) && !endIt){
    if (lastScreen) {
      lastScreen=false;
      endIt=true;
    }
    lcd.clear();
    for (int y=0; y<kLCDHeight; y++) {
      for(i = 0; speedMessage[strPos] != ' ' && speedMessage[strPos] != '\0'; i++){
        allWords[kLCDHeight-1][i] = speedMessage[strPos++];
      }
      if (speedMessage[strPos] != '\0') 
        strPos++;
      else
        lastScreen=true;      
      allWords[kLCDHeight-1][i] = '\0';
      if (!firstScreen){
        for (int height=0; height<kLCDHeight;height++) {      
          lcd.setCursor(0,height);
          for (int blank = 0; blank<kLCDWidth;blank++) {
            lcd.print(" ");
          }
          lcd.setCursor(8-strlen(allWords[height])/2,height);
          lcd.print(allWords[height]);
        }
      } else {  //first screen, i.e. start of message starts by scrolling up.  - This is better looking
          lcd.setCursor(8-strlen(allWords[kLCDHeight-1])/2,kLCDHeight-1);
          lcd.print(allWords[kLCDHeight-1]);
      }
      if (allWords[kLCDHeight-1][i-1] == '.'  || allWords[kLCDHeight-1][i-1] == ',')
        delay(2500);
      else
        delay(1000);
      for (int n=1; n<kLCDHeight;n++) 
        strcpy(allWords[n-1], allWords[n]);
      firstScreen=false;
    }
  }
}
*/

//Speed read4 does not return to the coil control, stays in loop, until the whole message is finished, same as juice used to do
// quicker? Blank only the number of previous word
void speedRead4(){
  int i;
  strPos = 0;
  boolean firstScreen=true;
  boolean lastScreen=false;
  boolean endIt=false;

#if defined (__Use_SSD1306_LCD__)
  lcd.setPrintMode(false);  //turn off sendBuffer()
#endif
//#if defined (__Use_SSD1306_LCD__)
//  lcd.clearBuffer();          // clear the internal memory - not required as clear() is available
//#else
  lcd.clear();
//#endif
  while((speedMessage[strPos] != '\0' || lastScreen) && !endIt){

    if (lastScreen) {
      lastScreen=false;
      endIt=true;
    }
    for (int y=0; y<kLCDHeight; y++) {
      for(i = 0; speedMessage[strPos] != ' ' && speedMessage[strPos] != '\0'; i++){
        allWords[kLCDHeight-1][i] = speedMessage[strPos++];
      }
      if (speedMessage[strPos] != '\0') 
        strPos++;
      else
        lastScreen=true;      
      allWords[kLCDHeight-1][i] = '\0';
      if (!firstScreen){
        lcd.setCursor(0,0);                      // For the top line, becuase we can't remember the previous off screen word...
        lcd.print("                ");           // ...blank the whole line
        lcd.setCursor(kLCDWidth/2-strlen(allWords[0])/2,0);    // set cursor half way across the screen, and indented half the word length
        lcd.print(allWords[0]);                  // print first line out of loop, because, in the loop, we start at 1
        for (int height=1; height<kLCDHeight;height++) {      // quicker? Blank only the number of previous word
          lcd.setCursor(kLCDWidth/2-strlen(allWords[height-1])/2,height);  // set cursor to start of previous word
          for (int blank = 0; blank<strlen(allWords[height-1]);blank++) {     // for the length of the previous word...
            lcd.print(" ");                                                   // print blanks
          }
          lcd.setCursor(kLCDWidth/2-strlen(allWords[height])/2,height);    // set cursor half way across the screen, and indented half the word length
          lcd.print(allWords[height]);
        }
      } else {  //first screen, i.e. start of message starts by scrolling up.  - This is better looking
          lcd.setCursor(kLCDWidth/2-strlen(allWords[kLCDHeight-1])/2,kLCDHeight-1);
          lcd.print(allWords[kLCDHeight-1]);
      }
#if defined (__Use_SSD1306_LCD__)
      lcd.sendBuffer();          // transfer internal memory to the display
#endif
      if (allWords[kLCDHeight-1][i-1] == '.'  || allWords[kLCDHeight-1][i-1] == ',')
        delay(2500);
      else
        delay(1000);
      for (int n=1; n<kLCDHeight;n++) 
        strcpy(allWords[n-1], allWords[n]);
      firstScreen=false;
    }
  }
#if defined (__Use_SSD1306_LCD__)
  lcd.setPrintMode(true);  //turn back on sendBuffer()
#endif
}




boolean checkOutOfRange(){ 
  boolean resetNeeded = false;
  
  if (EEPROM.read(EE_defaultsAddress) >= numDefaultsSteps ||
     EEPROM.read(EE_defaultsSureAddress) >= numDefaultsSureSteps ||
     EEPROM.read(EE_programAddress) >= numProgs ||
     EEPROM.read(EE_controlTypeAddress) >= numControlTypeSteps ||
     EEPROM.read(EE_programVoltageDropAddress) >= numVoltageDropProgs ||
     EEPROM.read(EE_temperatureUnitsAddress) >= numTemperatureUnitsSteps ||
     EEPROM.read(EE_materialAddress) >= numMaterialProgs)
    resetNeeded = true;
    
  return (resetNeeded);  
}

void EE_Presets(){
  EEPROM.write(EE_programAddress, kPM_Juice);  // Prints "JUICE" by default
  EEPROM.write(EE_voltageAddress, 0);
  EEPROM.write(EE_resistanceAddress, 1);  // should default to 1 Ohm or 0.5 Ohm, or what? Can not be zero as it gives an infinite power result
  EEPROM.write(EE_powerAddress, 0);       // should default to 30 W, for safety?
  EEPROM.write(EE_coilVoltageDropAddress, 0);
  EEPROM.write(EE_programVoltageDropAddress, 0);
  EEPROM.write(EE_batteryVoltageDropAddress, 0);
//  EEPROM.write(EE_programMaterialAddress, kMaterial_SS316);  // not needed as we have EE_material address
  EEPROM.write(EE_materialAddress, kMaterial_SS316);  // default SS 316
  EEPROM.write(EE_temperatureAddress, 0);
  EEPROM.write(EE_temperatureUnitsAddress, kTemperatureUnits_C);  // default to °C
  EEPROM.write(EE_defaultsAddress, 0);             // default to "Do not reset"
  EEPROM.write(EE_defaultsSureAddress, 0);         // default to "No I am not sure"
  EEPROM.write(EE_controlTypeAddress, 0);          // default to voltage control
  EEPROM.write(EE_currentMeasureAddress, 0);       // default to 0 - no current flow
//  EEPROM.write(EE_voltage4PowerAddress, 0);        // default to 0 for safety - this is set when the power control option is selected, or power is adjusted
//  EEPROM.write(EE_voltage4TemperatureAddress, 0);  // default to 0 for safety - this is set when the temperature control option is selected, or temperature is adjusted
}

void EE_Presets_Test(){
  EEPROM.write(EE_programAddress, kPM_SpeedRead);  // Prints speedread by default, when debugging - This actually prints star wars, or "Vape on it!"
//  EEPROM.write(EE_voltageAddress, 0);
//  EEPROM.write(EE_resistanceAddress, 1);  // should default to 1 Ohm or 0.5 Ohm, or what? Can not be zero as it gives an infinite power result
//  EEPROM.write(EE_powerAddress, 0);       // should default to 30 W, for safety?
//  EEPROM.write(EE_coilVoltageDropAddress, 0);
//  EEPROM.write(EE_programVoltageDropAddress, 0);
//  EEPROM.write(EE_batteryVoltageDropAddress, 0);
//  EEPROM.write(EE_programMaterialAddress, kMaterial_SS316);  // not needed as we have EE_material address
//  EEPROM.write(EE_materialAddress, kMaterial_SS316);  // default SS 316
//  EEPROM.write(EE_temperatureAddress, 0);
//  EEPROM.write(EE_temperatureUnitsAddress, kTemperatureUnits_C);  // default to °C
//  EEPROM.write(EE_defaultsAddress, 0);             // default to "Do not reset"
//  EEPROM.write(EE_defaultsSureAddress, 0);         // default to "No I am not sure"
//  EEPROM.write(EE_controlTypeAddress, 0);          // default to voltage control
//  EEPROM.write(EE_currentMeasureAddress, 0);       // default to 0 - no current flow
//  EEPROM.write(EE_voltage4PowerAddress, 0);        // default to 0 for safety - this is set when the power control option is selected, or power is adjusted
//  EEPROM.write(EE_voltage4TemperatureAddress, 0);  // default to 0 for safety - this is set when the temperature control option is selected, or temperature is adjusted
}

/*============================================================================*/
/* Convert unsigned value to d-digit integer string in local buffer      */
/*============================================================================*/
char *u2s(unsigned  x, unsigned d)
{  static char b[5];
   char *p;
   unsigned digits = 0;
   unsigned  t = x;

   do ++digits; while (t /= 10);
   // if (digits > d) d = digits; // uncomment to allow more digits than spec'd
   *(p = b + d) = '\0';
   do *--p = x % 10 + '0'; while (x /= 10);
   while (p != b) *--p = ' ';
   return b;
}

/*============================================================================*/
/* Convert unsigned value to d-digit long string in local buffer      */
/*============================================================================*/
char *ul2s(unsigned long x, unsigned d)
{  static char b[7];
   char *p;
   unsigned digits = 0;
   unsigned long t = x;

   do ++digits; while (t /= 10);
   // if (digits > d) d = digits; // uncomment to allow more digits than spec'd
   *(p = b + d) = '\0';
   do *--p = x % 10 + '0'; while (x /= 10);
   while (p != b) *--p = ' ';
   return b;
}

/*============================================================================*/
/* Convert unsigned value to d-digit long string in local buffer      */
/*============================================================================*/
/*
char *f2s(float x, unsigned d)
{  static char b[7];
   char *p;
   unsigned digits = 0;
   float t = x;

   do ++digits; while (t /= 10);
   // if (digits > d) d = digits; // uncomment to allow more digits than spec'd
   *(p = b + d) = '\0';
   do *--p = x % 10 + '0'; while (x /= 10);
   while (p != b) *--p = ' ';
   return b;
}
*/

