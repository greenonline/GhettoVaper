// ******************** DEFINES - START ********************

// Test
//#define __Debug__ // This should normally be commented out
//#define __Debug_Presets__ // This should normally be commented out
//#define __Debug_State__ // This should normally be commented out
//#define __Debug_Welcome__ // This should normally be commented out

// Button mechanism
#define __Use_MMButton__ // Use new version - This should normally be uncommented out (i.e. normally do NOT comment out)
// MButton is the default - however MButton can only be used with pull down buttons 


// Select which LCD you are using - 1602 is the default
// Testing with DFRobot 1602 display (default standard 1602 shield)
//#define __Use_DFRobot_1602_LCD__
#define __Use_TFT_ILI9163C_Extended_Char_LCD__ // for 0.96" colour display
//#define __Use_SSD1306_LCD__  // For SSD1306 128x32 0.91"
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
