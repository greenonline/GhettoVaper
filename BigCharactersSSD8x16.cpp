
#include "BigCharactersSSD8x16.h"

///BIG CHARACTER SHIZ

//const int kLT = 0;
//const int kUB = 1;
//const int kRT = 2;
//const int kLL = 3;
//const int kLB = 4;
//const int kLR = 5;
//const int kMB = 6;
//const int kcross = 7;


// the 8 arrays that form each segment of the custom numbers
// Custom character "0"
// 0xF0,0xF8,0xFC,0xFE,0xFF, // LT1 98
byte  LT1[8] = 
{
  B00001,
  B00011,
  B00111,
  B01111,
  B11111,
  B11111,
  B11111,
  B11111
};

//0xFF,0xFF,0xFF,0xFF,0xFF, // block 99
byte  LT2[8] = 
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

//0xFF,0xFF,0xFF,0xFF,0xFF, // block 99
byte  LT3[8] = 
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

//0xFF,0xFF,0xFF,0xFF,0xFF, // block 99
byte  LT4[8] = 
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

// Custom character "1"
//0x3F,0x3F,0x3F,0x3F,0x3F, // topbar, 100
byte UB1[8] =
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000,
  B00000
};

// Custom character "1"
//0x3F,0x3F,0x3F,0x3F, // topbar, 100
byte UB2[8] =
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000,
  B00000
};

// Custom character "1"
byte UB3[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

// Custome character "1"
byte UB4[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

// Custom character "2"
byte RT1[8] =
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

//0xFF,0xFE,0xFC,0xF8,0xF0
byte RT2[8] =
{
  B10000,
  B11000,
  B11100,
  B11110,
  B11111,
  B11111,
  B11111,
  B11111
};

byte RT3[8] =
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

byte RT4[8] =
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

// Custom character "3"
byte LL1[8] =
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

byte LL2[8] =
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

//0x0F,0x1F,0x3F,0x7F,0xFF
byte LL3[8] =
{
  B11111,
  B11111,
  B11111,
  B11111,
  B01111,
  B00111,
  B00011,
  B00001
};

byte LL4[8] =
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

// Custom character "4"
byte LB1[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte LB2[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

//0xFE,0xFE,0xFE,0xFE,0xFE, // lowbar (LB)
byte LB3[8] =
{
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

//0xFE,0xFE,0xFE,0xFE,0xFE
byte LB4[8] =
{
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

// Custom character "5"
byte LR1[8] =
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

byte LR2[8] =
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

byte LR3[8] =
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

//0xFF,0x7F,0x3F,0x1F,0x0F, // lowright (LR)
byte LR4[8] =
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11110,
  B11100,
  B11000,
  B10000
};

// Custom character "6"
//0x3F,0x3F,0x3F,0x3F,0x3F, // middle blankTop (MBT)
byte MB1[8] =
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000,
  B00000
};

//0x3F,0x3F,0x3F,0x3F,0x3F
byte MB2[8] =
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000,
  B00000
};

//0xF0,0xF0,0xF0,0xF0,0xF0, // middle blank bottom (MBB)
byte MB3[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111
};

//0xF0,0xF0,0xF0,0xF0,0xF0
byte MB4[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111
};

// Custom character "7"
//byte block[8] =
//{
//  B11111,
//  B11111,
//  B11111,
//  B11111,
//  B11111,
//  B11111,
//  B11111,
//  B11111
//};

// Custom character "8"
//byte blank[8] =
//{
//  B00000,
//  B00000,
//  B00000,
//  B00000,
//  B00000,
//  B00000,
//  B00000,
//  B00000
//};

// Custom character "9"
//0x07,0x3F,0xFF,0xFF,0xFE, // cross1 (C1)
byte cross1[8] =
{
  B11110,
  B11111,
  B11111,
  B01111,
  B01111,
  B01111,
  B00111,
  B00111
};

//0xF8,0xC0,0x00,0x00,0x00, // cross2 (C2)
byte cross2[8] =
{
  B00000,
  B00000,
  B00000,
  B10000,
  B10000,
  B10000,
  B11000,
  B11000
};

//0x00,0x00,0x00,0x03,0x1F, // cross3 (C3)
byte cross3[8] =
{
  B00011,
  B00011,
  B00001,
  B00001,
  B00001,
  B00000,
  B00000,
  B00000
};

//0x7F,0xFF,0xFF,0xFC,0xE0, // cross4 (C4)
byte cross4[8] =
{
  B11100,
  B11100,
  B11110,
  B11110,
  B11110,
  B11111,
  B11111,
  B01111
};

// Custom character "/"
//0x07,0x3F,0xFF,0xFF,0xFE, // cross1 (C1)
byte criss1[8] =
{
  B00111,
  B00111,
  B01111,
  B01111,
  B01111,
  B11111,
  B11111,
  B11110
};

//0xF8,0xC0,0x00,0x00,0x00, // cross2 (C2)
byte criss2[8] =
{
  B11000,
  B11000,
  B10000,
  B10000,
  B10000,
  B00000,
  B00000,
  B00000
};

//0x00,0x00,0x00,0x03,0x1F, // cross3 (C3)
byte criss3[8] =
{
  B00000,
  B00000,
  B00000,
  B00001,
  B00001,
  B00001,
  B00011,
  B00011
};

//0x7F,0xFF,0xFF,0xFC,0xE0, // cross4 (C4)
byte criss4[8] =
{
  B01111,
  B11111,
  B11111,
  B11110,
  B11110,
  B11110,
  B11100,
  B11100
};


void customJ_SSD(int location)
{ // uses segments to build the number 0
  lcd.setPrint8x16CharacterMode(false);
  lcd.setCursor(location,0); // set cursor to column 0, line 0 (first row)
  // ' '
  lcd.write("  ");  // call each segment to create
  // ' '
  lcd.write("  ");  // bottom half of the number
  // 2
//  lcd.write("\143\145");
  lcd.write("\203\205");  // add 32 \40
  lcd.setCursor(location, 1); // set cursor to colum 0, line 1 (second row)
  // ' '
  lcd.write("  ");  // call each segment to create
  // ' '
  lcd.write("  ");  // call each segment to create
  // 2
//  lcd.write("\143\143");  // call each segment to create
  lcd.write("\203\203");  // call each segment to create
  lcd.setCursor(location, 2); // set cursor to colum 0, line 1 (second row)
  // 3
//  lcd.write("\143\143");  // call each segment to create
  lcd.write("\203\203");  // call each segment to create
  // 4
  lcd.write("  ");  // bottom half of the number
  // 5
//  lcd.write("\143\143");
  lcd.write("\203\203");
  lcd.setCursor(location, 3); // set cursor to colum 0, line 1 (second row)
  // 3
//  lcd.write("\146\143");  // call each segment to create
  lcd.write("\206\203");  // call each segment to create
  // 4
//  lcd.write("\147\147");  // bottom half of the number
  lcd.write("\207\207");  // bottom half of the number
  // 5
//  lcd.write("\143\150");
  lcd.write("\203\210");
  lcd.setPrint8x16CharacterMode(true);
}

// Thinner Character
void customJ_SSD_thin(int location)
{ // uses segments to build the number 0
  lcd.setPrint8x16CharacterMode(false);
  lcd.setCursor(location,0); // set cursor to column 0, line 0 (first row)
  // ' ' ' ' 2
//  lcd.write("  \145");  // call each segment to create
  lcd.write("  \205");  // call each segment to create
  lcd.setCursor(location, 1); // set cursor to colum 0, line 1 (second row)
  // ' ' ' ' 2
//  lcd.write("  \143");  // call each segment to create
  lcd.write("  \203");  // call each segment to create
  lcd.setCursor(location, 2); // set cursor to colum 0, line 1 (second row)
  // 3 4 5
//  lcd.write("\143 \143");  // call each segment to create
  lcd.write("\203 \203");  // call each segment to create
  lcd.setCursor(location, 3); // set cursor to colum 0, line 1 (second row)
  // 3 4 5
//  lcd.write("\146\147\150");  // call each segment to create
  lcd.write("\206\207\210");  // call each segment to create
  lcd.setPrint8x16CharacterMode(true);
}

void customU_SSD(int location)
{
  lcd.setPrint8x16CharacterMode(false);
  lcd.setCursor(location,0); // set cursor to column 0, line 0 (first row)
  // 2
//  lcd.write("\143\145");
  lcd.write("\203\205");
  // ' '
  lcd.write("  ");  // bottom half of the number
  // 2
//  lcd.write("\143\145");
  lcd.write("\203\205");
  lcd.setCursor(location, 1); // set cursor to colum 0, line 1 (second row)
  // 2
//  lcd.write("\143\143");  // call each segment to create
  lcd.write("\203\203");  // call each segment to create
  // ' '
  lcd.write("  ");  // call each segment to create
  // 2
//  lcd.write("\143\143");  // call each segment to create
  lcd.write("\203\203");  // call each segment to create
  lcd.setCursor(location, 2); // set cursor to colum 0, line 1 (second row)
  // 3
//  lcd.write("\143\143");  // call each segment to create
  lcd.write("\203\203");  // call each segment to create
  // 4
  lcd.write("  ");  // bottom half of the number
  // 5
//  lcd.write("\143\143");  // call each segment to create
  lcd.write("\203\203");  // call each segment to create
  lcd.setCursor(location, 3); // set cursor to colum 0, line 1 (second row)
  // 3
//  lcd.write("\146\143");  // call each segment to create
  lcd.write("\206\203");  // call each segment to create
  // 4
//  lcd.write("\147\147");  // bottom half of the number
  lcd.write("\207\207");  // bottom half of the number
  // 5
//  lcd.write("\143\150");
  lcd.write("\203\210");
  lcd.setPrint8x16CharacterMode(true);
}

void customU_SSD_thin(int location)
{
  lcd.setPrint8x16CharacterMode(false);
  lcd.setCursor(location,0); // set cursor to column 0, line 0 (first row)
  // 2 ' ' 2
//  lcd.write("\145 \145");
  lcd.write("\205 \205");
  lcd.setCursor(location, 1); // set cursor to colum 0, line 1 (second row)
  // 2 ' ' 2
//  lcd.write("\143 \143");  // call each segment to create
  lcd.write("\203 \203");  // call each segment to create
  lcd.setCursor(location, 2); // set cursor to colum 0, line 1 (second row)
  // 3 4 5
//  lcd.write("\143\143");  // call each segment to create
  lcd.write("\203 \203");  // call each segment to create
  lcd.setCursor(location, 3); // set cursor to colum 0, line 1 (second row)
  // 3 4 5
//  lcd.write("\146\147\150");  // call each segment to create
  lcd.write("\206\207\210");  // call each segment to create
  lcd.setPrint8x16CharacterMode(true);
}

void customI_SSD(int location)
{
  lcd.setPrint8x16CharacterMode(false);
  lcd.setCursor(location,0); // set cursor to column 0, line 0 (first row)
  // ' '
  lcd.write("  ");  // bottom half of the number
  // 2
//  lcd.write("\143\145");
  lcd.write("\203\205");
  // ' '
  lcd.write("  ");  // bottom half of the number
  lcd.setCursor(location, 1); // set cursor to colum 0, line 1 (second row)
  // ' '
  lcd.write("  ");  // call each segment to create
  // 2
//  lcd.write("\143\143");  // call each segment to create
  lcd.write("\203\203");  // call each segment to create
  // ' '
  lcd.write("  ");  // call each segment to create
  lcd.setCursor(location, 2); // set cursor to colum 0, line 1 (second row)
  // ' '
  lcd.write("  ");  // bottom half of the number
  // 3
//  lcd.write("\143\143");  // call each segment to create
  lcd.write("\203\203");  // call each segment to create
  // ' '
  lcd.write("  ");  // bottom half of the number
  lcd.setCursor(location, 3); // set cursor to colum 0, line 1 (second row)
  // ' '
  lcd.write("  ");  // bottom half of the number
  // 3
//  lcd.write("\146\143");  // call each segment to create
  lcd.write("\206\203");  // call each segment to create
  // ' '
  lcd.write("  ");  // bottom half of the number
  lcd.setPrint8x16CharacterMode(true);
}

void customI_SSD_thin(int location)
{
  lcd.setPrint8x16CharacterMode(false);
  lcd.setCursor(location,0); // set cursor to column 0, line 0 (first row)
  // ' ' 2 ' '
//  lcd.write(" \145 ");
  lcd.write(" \205 ");  // bottom half of the number
  lcd.setCursor(location, 1); // set cursor to colum 0, line 1 (second row)
  // ' ' 2 ' '
//  lcd.write(" \143 ");  // call each segment to create
  lcd.write(" \204 ");  // call each segment to create
  lcd.setCursor(location, 2); // set cursor to colum 0, line 1 (second row)
  // ' ' 3 ' '
//  lcd.write(" \143 ");  // call each segment to create
  lcd.write(" \203 ");  // bottom half of the number
  lcd.setCursor(location, 3); // set cursor to colum 0, line 1 (second row)
  // ' ' 3 ' '
//  lcd.write(" \146 ");  // call each segment to create
  lcd.write(" \206 ");  // bottom half of the number
  lcd.setPrint8x16CharacterMode(true);
}

void customC_SSD(int location)
{
  lcd.setPrint8x16CharacterMode(false);
  lcd.setCursor(location,0);
  // 0
//  lcd.write("\142\143");  // call each segment to create
  lcd.write("\202\203");  // call each segment to create
  // 1
//  lcd.write("\144\144");  // should be 1
  lcd.write("\204\204");  // should be 1
  // 7
//  lcd.write("\153\154");  // was 1, should have been 9, now is 7
  lcd.write("\213\214");  // was 1, should have been 9, now is 7
  lcd.setCursor(location, 1);
  // 0
//  lcd.write("\143\143");  // call each segment to create
  lcd.write("\203\203");  // call each segment to create
  // 1
  lcd.write("  ");  // was 7, should be 0 for the curved C top left
  // 7
//  lcd.write("\155\156");  // was 1, should have been 9, now is 7
  lcd.write("\215\216");  // was 1, should have been 9, now is 7
  lcd.setCursor(location, 2); // set cursor to colum 0, line 1 (second row)
  // 3
//  lcd.write("\143\143");  // call each segment to create
  lcd.write("\203\203");  // call each segment to create
  // 4
  lcd.write("  ");  // bottom half of the number
  // 4
  lcd.write("  ");  // bottom half of the number
  lcd.setCursor(location, 3); // set cursor to colum 0, line 1 (second row)
  // 3
//  lcd.write("\146\143");  // call each segment to create
  lcd.write("\206\203");  // call each segment to create
  // 4
//  lcd.write("\147\147");  // bottom half of the number
  lcd.write("\207\207");  // bottom half of the number
  // 4
//  lcd.write("\147\147");  // bottom half of the number
  lcd.write("\207\207");  // bottom half of the number
  lcd.setPrint8x16CharacterMode(true);
}

void customC_SSD_thin(int location)
{
  lcd.setPrint8x16CharacterMode(false);
  lcd.setCursor(location,0);
  // 0 1 7
//  lcd.write("\142\144\153");  // call each segment to create
  lcd.write("\202\204\213");  // call each segment to create  //?????????
//  lcd.write("\142\144\154");  // call each segment to create
//  lcd.write("\202\204\214");  // call each segment to create  //?????????
  lcd.setCursor(location, 1);
  // 0 1 7
//  lcd.write("\143 \155");  // call each segment to create
  lcd.write("\203 \215");  // call each segment to create   //?????????
//  lcd.write("\143 \156");  // call each segment to create
// lcd.write("\203 \216");  // call each segment to create   //?????????
  lcd.setCursor(location, 2); // set cursor to colum 0, line 1 (second row)
  // 3 4 4
//  lcd.write("\143  ");  // call each segment to create
  lcd.write("\203  ");  // call each segment to create
  lcd.setCursor(location, 3); // set cursor to colum 0, line 1 (second row)
  // 3 4 4
//  lcd.write("\146\147\147");  // call each segment to create
  lcd.write("\206\207\207");  // call each segment to create
  lcd.setPrint8x16CharacterMode(true);
}

void customE_SSD(int location)
{
  lcd.setPrint8x16CharacterMode(false);
  lcd.setCursor(location,0);
  // 0
//  lcd.write("\142\143");  // was 7, should be 0 for the curved C top left
  lcd.write("\202\203");  // was 7, should be 0 for the curved C top left
  // 6
//  lcd.write("\151\151");
  lcd.write("\211\211");
  // ' '
  lcd.write("  "); // was a 6
  lcd.setCursor(location, 1);
  // 0 
//  lcd.write("\142\143");  // was 7, should be 0 for the curved C top left
  lcd.write("\202\203");  // was 7, should be 0 for the curved C top left
  // 6
//  lcd.write("\152\152");
  lcd.write("\212\212");
  // ' '
  lcd.write("  "); // was a 6
  lcd.setCursor(location, 2); // set cursor to colum 0, line 1 (second row)
  // 3
//  lcd.write("\142\143");  // was 7, should be 0 for the curved C top left
  lcd.write("\202\203");  // was 7, should be 0 for the curved C top left
  // 4
  lcd.write("  ");  // bottom half of the number
  // ' '
  lcd.write("  ");  // bottom half of the number
  lcd.setCursor(location, 3); // set cursor to colum 0, line 1 (second row)
  // 3
//  lcd.write("\146\143");  // call each segment to create
  lcd.write("\206\203");  // call each segment to create
  // 4
//  lcd.write("\147\147");  // bottom half of the number
  lcd.write("\207\207");  // bottom half of the number
  // ' '
  lcd.write("  ");  // bottom half of the number
  lcd.setPrint8x16CharacterMode(true);
}

void customE_SSD_thin(int location)
{
  lcd.setPrint8x16CharacterMode(false);
  lcd.setCursor(location,0);
  // 0 6 ' '
//  lcd.write("\142\151 ");  // was 7, should be 0 for the curved C top left
//  lcd.write("\202\211 ");  // was 7, should be 0 for the curved C top left - short
  lcd.write("\202\211\211");  // was 7, should be 0 for the curved C top left - long
  lcd.setCursor(location, 1);
  // 0 6 ' '
//  lcd.write("\142\152 ");  // was 7, should be 0 for the curved C top left
//  lcd.write("\202\212 ");  // was 7, should be 0 for the curved C top left - short
  lcd.write("\202\212\212");  // was 7, should be 0 for the curved C top left - long
  lcd.setCursor(location, 2); // set cursor to colum 0, line 1 (second row)
  // 3 4 ' '
//  lcd.write("\142\143");  // was 7, should be 0 for the curved C top left
  lcd.write("\202  ");  // was 7, should be 0 for the curved C top left
  lcd.setCursor(location, 3); // set cursor to colum 0, line 1 (second row)
  // 3 4 ' '
//  lcd.write("\146\147 ");  // call each segment to create
//  lcd.write("\206\207 ");  // call each segment to create - short
  lcd.write("\206\207\207");  // call each segment to create - long
  lcd.setPrint8x16CharacterMode(true);
}

void customF_SSD(int location)
{
  lcd.setPrint8x16CharacterMode(false);
  lcd.setCursor(location,0);
  // 0
//  lcd.write("\142\143");  // was 7, should be 0 for the curved C top left
  lcd.write("\202\203");  // was 7, should be 0 for the curved C top left
  // 6
//  lcd.write("\151\151");
  lcd.write("\211\211");
  // " "
  lcd.write("  ");
  lcd.setCursor(location, 1);
  // 0
//  lcd.write("\143\143");  // was 7, should be 0 for the curved C top left
  lcd.write("\203\203");  // was 7, should be 0 for the curved C top left
  // 6
//  lcd.write("\152\152");
  lcd.write("\212\212");
  // " "
  lcd.write("  ");
  lcd.setCursor(location, 2);
  // 5
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // " "
  lcd.write("  ");
  // " "
  lcd.write("  ");
  lcd.setCursor(location, 3);
  // 5
//  lcd.write("\143\150");
  lcd.write("\203\210");
  // " "
  lcd.write("  ");
  // " "
  lcd.write("  ");
  lcd.setPrint8x16CharacterMode(true);
}

void customF_SSD_thin(int location)
{
  lcd.setPrint8x16CharacterMode(false);
  lcd.setCursor(location,0);
  // 0 6 ' '
//  lcd.write("\142\151 ");  // was 7, should be 0 for the curved C top left
  lcd.write("\202\211 ");  // was 7, should be 0 for the curved C top left
  lcd.setCursor(location, 1);
  // 0 6 ' '
//  lcd.write("\143\152 ");  // was 7, should be 0 for the curved C top left
  lcd.write("\203\212 ");  // was 7, should be 0 for the curved C top left
  lcd.setCursor(location, 2);
  // 5 ' ' ' '
//  lcd.write("\143\143");
  lcd.write("\203  ");
  lcd.setCursor(location, 3);
  // 5 ' ' ' '
//  lcd.write("\150  ");
  lcd.write("\210  ");
  lcd.setPrint8x16CharacterMode(true);
}

void customR_SSD(int location)
{
  lcd.setPrint8x16CharacterMode(false);
  lcd.setCursor(location,0);
  // 0
//  lcd.write("\142\143");  // was 7, should be 0 for the curved C top left
  lcd.write("\202\203");  // was 7, should be 0 for the curved C top left
  // 6
//  lcd.write("\151\151");
  lcd.write("\211\211");
  // 2
//  lcd.write("\143\145");
  lcd.write("\203\205");
  lcd.setCursor(location, 1);
  // 0
//  lcd.write("\143\143");  // was 7, should be 0 for the curved C top left
  lcd.write("\203\203");  // was 7, should be 0 for the curved C top left
  // 6
//  lcd.write("\152\152");
  lcd.write("\212\212");
  // 2
//  lcd.write("\143\143");
  lcd.write("\203\203");
  lcd.setCursor(location, 2);
  // 5
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // " "
  lcd.write("  ");  // call each segment to create
  // 7
//  lcd.write("\153\154");  // was 1, should have been 9, now is 7
  lcd.write("\213\214");  // was 1, should have been 9, now is 7
  lcd.setCursor(location, 3);
  // 5
//  lcd.write("\143\150");  // call each segment to create
  lcd.write("\203\210");  // call each segment to create
  // " "
  lcd.write("  ");  // call each segment to create
  // 7
//  lcd.write("\155\156");  // was 1, should have been 9, now is 7
  lcd.write("\215\216");  // was 1, should have been 9, now is 7
  lcd.setPrint8x16CharacterMode(true);
}

void customR_SSD_thin(int location)
{
  lcd.setPrint8x16CharacterMode(false);
  lcd.setCursor(location,0);
  // 0 6 2
//  lcd.write("\142\151\145");  // was 7, should be 0 for the curved C top left
  lcd.write("\202\211\205");  // was 7, should be 0 for the curved C top left
  lcd.setCursor(location, 1);
  // 0 6 2
//  lcd.write("\143\152\143");  // was 7, should be 0 for the curved C top left
  lcd.write("\203\212\203");  // was 7, should be 0 for the curved C top left
  lcd.setCursor(location, 2);
  // 5 ' ' 7
//  lcd.write("\143\143");
  lcd.write("\203 ");  //?????????
  // " "
  lcd.write("  ");  // call each segment to create
  // 7
//  lcd.write("\153\154");  // was 1, should have been 9, now is 7
  lcd.write("\213\214");  // was 1, should have been 9, now is 7
  lcd.setCursor(location, 3);
  // 5
//  lcd.write("\143\150");  // call each segment to create
  lcd.write("\203\210");  // call each segment to create
  // " "
  lcd.write("  ");  // call each segment to create
  // 7
//  lcd.write("\155\156");  // was 1, should have been 9, now is 7
  lcd.write("\215\216");  // was 1, should have been 9, now is 7
  lcd.setPrint8x16CharacterMode(true);
}

void customS_SSD(int location)
{
  lcd.setPrint8x16CharacterMode(false);
  lcd.setCursor(location, 0);
  // 0
//  lcd.write("\142\143");  // was 7, should be 0 for the curved C top left
  lcd.write("\202\203");  // was 7, should be 0 for the curved C top left
  // 6
//  lcd.write("\151\151");
  lcd.write("\211\211");
  // 6
//  lcd.write("\151\151");
  lcd.write("\211\211");
  lcd.setCursor(location, 1);
  // 0
//  lcd.write("\143\143");  // was 7, should be 0 for the curved C top left
  lcd.write("\203\203");  // was 7, should be 0 for the curved C top left
  // 6
//  lcd.write("\152\152");
  lcd.write("\212\212");
  // 6
//  lcd.write("\152\152");
  lcd.write("\212\212");
  lcd.setCursor(location, 2);
  // 4
  lcd.write("  ");  // call each segment to create
  // 4
  lcd.write("  ");  // call each segment to create
  // 5
//  lcd.write("\143\143");
  lcd.write("\203\203");
  lcd.setCursor(location, 3);
  // 4
//  lcd.write("\147\147");  // bottom half of the number
  lcd.write("\207\207");  // bottom half of the number
  // 4
//  lcd.write("\147\147");  // bottom half of the number
  lcd.write("\207\207");  // bottom half of the number
  // 5
//  lcd.write("\143\150");  // call each segment to create
  lcd.write("\203\210");  // call each segment to create
  lcd.setPrint8x16CharacterMode(true);
}

void customS_SSD_thin(int location)
{
  lcd.setPrint8x16CharacterMode(false);
  lcd.setCursor(location, 0);
  // 0 6 6
//  lcd.write("\142\151\151");  // was 7, should be 0 for the curved C top left
  lcd.write("\202\211\211");  // was 7, should be 0 for the curved C top left
  lcd.setCursor(location, 1);
  // 0 6 6
//  lcd.write("\143\152\152");  // was 7, should be 0 for the curved C top left
  lcd.write("\203\212\212");  // was 7, should be 0 for the curved C top left
  lcd.setCursor(location, 2);
  // 4 4 5
//  lcd.write("  \143");
  lcd.write("  \203");  // call each segment to create
  lcd.setCursor(location, 3);
  // 4 4 5
//  lcd.write("\147\147\150");  // bottom half of the number
  lcd.write("\207\207\210");  // bottom half of the number
  lcd.setPrint8x16CharacterMode(true);
}

void customH_SSD(int location)
{
  lcd.setPrint8x16CharacterMode(false);
  lcd.setCursor(location, 0);
  // 2
//  lcd.write("\143\145");
  lcd.write("\203\205");
  // 4
  lcd.write("  ");  // call each segment to create
  // 2
//  lcd.write("\143\145");
  lcd.write("\203\205");
  lcd.setCursor(location, 1);
  // 2
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // 4
//  lcd.write("\147\147");  // bottom half of the number
  lcd.write("\207\207");  // bottom half of the number
  // 2
//  lcd.write("\143\143");
  lcd.write("\203\203");
  lcd.setCursor(location, 2);
  // 3
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // ' '
  lcd.write("  ");  
  // 3
//  lcd.write("\143\143");
  lcd.write("\203\203");
  lcd.setCursor(location, 3);
  // 3
//  lcd.write("\146\143");
  lcd.write("\206\203");
  // ' '
  lcd.write("  ");  
  // 3
//  lcd.write("\146\143");
  lcd.write("\206\203");
  lcd.setPrint8x16CharacterMode(true);
}

void customH_SSD_thin(int location)
{
  lcd.setPrint8x16CharacterMode(false);
  lcd.setCursor(location, 0);
  // 2 4 2
//  lcd.write("\145 \145");
  lcd.write("\205 \205");
  lcd.setCursor(location, 1);
  // 2 4 2
//  lcd.write("\143\147\143");
  lcd.write("\203\207\203");
  lcd.setCursor(location, 2);
  // 3 ' ' 3
//  lcd.write("\143 \143");
  lcd.write("\203 \203");
  lcd.setCursor(location, 3);
  // 3 ' ' 3
//  lcd.write("\146 \146");
  lcd.write("\206 \206");
  lcd.setPrint8x16CharacterMode(true);
}

void customA_SSD(int location)
{
  lcd.setPrint8x16CharacterMode(false);
  lcd.setCursor(location,0);
  // 0
//  lcd.write("\142\143");  // was 7, should be 0 for the curved C top left
  lcd.write("\202\203");  // was 7, should be 0 for the curved C top left
  // 6
//  lcd.write("\151\151");
  lcd.write("\211\211");
  // 2
//  lcd.write("\143\145");
  lcd.write("\203\205");
  lcd.setCursor(location,1);
  // 0
//  lcd.write("\143\143");  // was 7, should be 0 for the curved C top left
  lcd.write("\203\203");  // was 7, should be 0 for the curved C top left
  // 6
//  lcd.write("\152\152");
  lcd.write("\212\212");
  // 2
//  lcd.write("\143\143");
  lcd.write("\203\203");
  lcd.setCursor(location,2);
  //3
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // ' '
  lcd.write("  ");  
  // 3
//  lcd.write("\143\143");
  lcd.write("\203\203");
  lcd.setCursor(location,3);
  // 3
//  lcd.write("\146\143");
  lcd.write("\206\203");
  // ' '
  lcd.write("  ");
  // 3
//  lcd.write("\146\143");
  lcd.write("\206\203");
  lcd.setPrint8x16CharacterMode(true);
}

void customA_SSD_thin(int location)
{
  lcd.setPrint8x16CharacterMode(false);
  lcd.setCursor(location,0);
  // 0 6 2
//  lcd.write("\142\151\145");  // was 7, should be 0 for the curved C top left
  lcd.write("\202\211\205");  // was 7, should be 0 for the curved C top left
  lcd.setCursor(location,1);
  // 0 6 2
//  lcd.write("\143\152\143");  // was 7, should be 0 for the curved C top left
  lcd.write("\203\212\203");  // was 7, should be 0 for the curved C top left
  lcd.setCursor(location,2);
  //3 ' ' 3
//  lcd.write("\143 \143");
  lcd.write("\203 \203");
  lcd.setCursor(location,3);
  // 3 ' ' 3
//  lcd.write("\146 \1462");
  lcd.write("\206 \206");
  lcd.setPrint8x16CharacterMode(true);
}

// B - 255?
void customB_SSD(int location)
{
  lcd.setPrint8x16CharacterMode(false);
  lcd.setCursor(location,0);
  // 255
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // 6
//  lcd.write("\151\151");
  lcd.write("\211\211");
  // 2
//  lcd.write("\143\145");
  lcd.write("\203\205");
  lcd.setCursor(location,1);
  // 255
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // 6
//  lcd.write("\152\152");
  lcd.write("\212\212");
  // 2
//  lcd.write("\143\143");
  lcd.write("\203\203");
  lcd.setCursor(location,2);
  // 255
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // 4
  lcd.write("  ");  // call each segment to create
  // 5
//  lcd.write("\143\143");
  lcd.write("\203\203");
  lcd.setCursor(location,3);
  // 255
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // 4
//  lcd.write("\147\147");  // bottom half of the number
  lcd.write("\207\207");  // bottom half of the number
  // 5
//  lcd.write("\143\150");  // call each segment to create
  lcd.write("\203\210");  // call each segment to create
  lcd.setPrint8x16CharacterMode(true);
}

// B - 255?
void customB_SSD_thin(int location)
{
  lcd.setPrint8x16CharacterMode(false);
  lcd.setCursor(location,0);
  // 255 6 2
//  lcd.write("\143\151\145");
  lcd.write("\203\211\205");
  lcd.setCursor(location,1);
  // 255 6 2
//  lcd.write("\143\143");
  lcd.write("\203\212\203");
  lcd.setCursor(location,2);
  // 255 4 5
//  lcd.write("\143 \143");
  lcd.write("\203 \203");
  lcd.setCursor(location,3);
  // 255 4 5
//  lcd.write("\143\147\150");
  lcd.write("\203\207\210");
  lcd.setPrint8x16CharacterMode(true);
}

void customD_SSD(int location)
{
  lcd.setPrint8x16CharacterMode(false);
  lcd.setCursor(location,0);
  // 255
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // 1
//  lcd.write("\144\144");
  lcd.write("\204\204");
  // 2
//  lcd.write("\143\145");
  lcd.write("\203\205");
  lcd.setCursor(location,1);
  // 255
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // 1
  lcd.write("  ");  // was 7, should be 0 for the curved C top left
  // 2
//  lcd.write("\143\143");
  lcd.write("\203\203");
  lcd.setCursor(location,2);
  // 255
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // 4
  lcd.write("  ");  // bottom half of the number
  // 5
//  lcd.write("\143\143");
  lcd.write("\203\203");
  lcd.setCursor(location,3);
  // 255
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // 4
//  lcd.write("\147\147");  // bottom half of the number
  lcd.write("\207\207");  // bottom half of the number
  // 5
//  lcd.write("\143\150");
  lcd.write("\203\210");
  lcd.setPrint8x16CharacterMode(true);  // needed? Will inadvertantly reset big characters
}

void customD_SSD_thin(int location)
{
  lcd.setPrint8x16CharacterMode(false);
  lcd.setCursor(location,0);
  // 255 1 2
//  lcd.write("\143\144\145");
  lcd.write("\203\204\205");
 lcd.setCursor(location,1);
  // 255 1 2
//  lcd.write("\143 \143");
  lcd.write("\203 \203");
  lcd.setCursor(location,2);
  // 255 4 5
//  lcd.write("\143 \143");
  lcd.write("\203 \203");
  lcd.setCursor(location,3);
  // 255 4 5
//  lcd.write("\143\147\150");
  lcd.write("\203\207\210");
  lcd.setPrint8x16CharacterMode(true);  // needed? Will inadvertantly reset big characters
}

#if 0
void customK_SSD(int location)
{
  lcd.setPrint8x16CharacterMode(false);  // needed? Will inadvertantly reset big characters
  lcd.setCursor(location,0);
  // 2
//  lcd.write("\143\145");
  lcd.write("\203\205");
  // ' '
  lcd.write("  ");
  // 2
//  lcd.write("\143\145");
  lcd.write("\203\205");
  lcd.setCursor(location,1);
  // 2
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // ' '
  lcd.write("  ");
  // 2
//  lcd.write("\143\143");
  lcd.write("\203\203");
  lcd.setCursor(location, 2);
  // 5
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // ' '
  lcd.write("  ");
  // 7
//  lcd.write("\153\154");  // was 1, should have been 9, now is 7
  lcd.write("\213\214");  // was 1, should have been 9, now is 7
  lcd.setCursor(location, 3);
  // 5
//  lcd.write("\143\150");
  lcd.write("\203\210");
  // ' '
  lcd.write("  ");
  // 7
//  lcd.write("\155\156");  // was 1, should have been 9, now is 7
  lcd.write("\215\216");  // was 1, should have been 9, now is 7
  lcd.setPrint8x16CharacterMode(true);  // needed? Will inadvertantly reset big characters
}
#endif

void customK_SSD(int location)
{
  lcd.setPrint8x16CharacterMode(false);  // needed? Will inadvertantly reset big characters
  lcd.setCursor(location,0);
  // 2
//  lcd.write("\143\145");
  lcd.write("\203\205");
  // ' '
//  lcd.write("  ");
  // 2
//  lcd.write("\143\145");
//  lcd.write("\203\205");
  lcd.write("\221\222");
  lcd.setCursor(location,1);
  // 2
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // ' '
//  lcd.write("  ");
  // 2
//  lcd.write("\143\143");
//  lcd.write("\203\203");
  lcd.write("\217\220");
  lcd.setCursor(location, 2);
  // 5
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // ' '
//  lcd.write("  ");
  // 7
//  lcd.write("\153\154");  // was 1, should have been 9, now is 7
  lcd.write("\213\214");  // was 1, should have been 9, now is 7
  lcd.setCursor(location, 3);
  // 5
//  lcd.write("\143\150");
  lcd.write("\203\210");
  // ' '
//  lcd.write("  ");
  // 7
//  lcd.write("\155\156");  // was 1, should have been 9, now is 7
  lcd.write("\215\216");  // was 1, should have been 9, now is 7
  lcd.setPrint8x16CharacterMode(true);  // needed? Will inadvertantly reset big characters
}

void customK_SSD_thin(int location)
{
  lcd.setPrint8x16CharacterMode(false);  // needed? Will inadvertantly reset big characters
  lcd.setCursor(location,0);
  // 2 ' ' 2
//  lcd.write("\145 \145");
//  lcd.write("\205 \205");
//  lcd.write("\145 \145");
  lcd.write("\205\221\222");
  lcd.setCursor(location,1);
  // 2 ' ' 2
//  lcd.write("\143 \143");
//  lcd.write("\203 \203");
//  lcd.write("\143 \143");
  lcd.write("\203\217\220");
  lcd.setCursor(location, 2);
  // 5 ' ' 7
//  lcd.write("\143 \153");
//  lcd.write("\203 \213");  // ??????
//  lcd.write("\143 \154");
  lcd.write("\203\213\214");  // ??????
  lcd.setCursor(location, 3);
  // 5 ' ' 7
//  lcd.write("\150 \155");
//  lcd.write("\210 \215");  // ??????
//  lcd.write("\150 \156");
  lcd.write("\210\215\216");  // ??????
  lcd.setPrint8x16CharacterMode(true);  // needed? Will inadvertantly reset big characters
}

void customL_SSD(int location)
{
  lcd.setPrint8x16CharacterMode(false);  // needed? Will inadvertantly reset big characters
  lcd.setCursor(location,0);
  // 2
//  lcd.write("\143\145");
  lcd.write("\203\205");
  // ' '
  lcd.write("  ");   // was 7 - 2 gives a stylised "I"
  // ' '
  lcd.write("  ");
  lcd.setCursor(location,1);
  // 2
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // ' '
  lcd.write("  ");   // was 7 - 2 gives a stylised "I"
  // ' '
  lcd.write("  ");
  lcd.setCursor(location, 2);
  // 255
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // 4
  lcd.write("  ");  // was 7 - 3 gives a stylisd "I"
  // ' '
  lcd.write("  ");
  lcd.setCursor(location, 3);
  // 255
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // 4
//  lcd.write("\147\147");  // bottom half of the number
  lcd.write("\207\207");  // bottom half of the number
  // ' '
  lcd.write("  ");
  lcd.setPrint8x16CharacterMode(true);  // needed? Will inadvertantly reset big characters
}

void customL_SSD_thin(int location)
{
  lcd.setPrint8x16CharacterMode(false);  // needed? Will inadvertantly reset big characters
  lcd.setCursor(location,0);
  // 2 ' ' ' '
//  lcd.write("\145  ");
  lcd.write("\205  ");
  lcd.setCursor(location,1);
  // 2 ' ' ' '
//  lcd.write("\143  ");
  lcd.write("\203  ");
  lcd.setCursor(location, 2);
  // 255 4 ' '
//  lcd.write("\142  ");
  lcd.write("\203  ");
  lcd.setCursor(location, 3);
  // 255 4 ' '
//  lcd.write("\143\147 ");
  lcd.write("\203\207 ");
  lcd.setPrint8x16CharacterMode(true);  // needed? Will inadvertantly reset big characters
}

void customO_SSD(int location)
{
  lcd.setPrint8x16CharacterMode(false);  // needed? Will inadvertantly reset big characters
  lcd.setCursor(location,0);
  // 0
//  lcd.write("\142\143");  // was 7, should be 0 for the curved C top left
  lcd.write("\202\203");  // was 7, should be 0 for the curved C top left
  // 1
//  lcd.write("\144\144");  // should be 1
  lcd.write("\204\204");  // should be 1
  // 2
//  lcd.write("\143\145");
  lcd.write("\203\205");
  lcd.setCursor(location,1);
  // 0
//  lcd.write("\143\143");  // was 7, should be 0 for the curved C top left
  lcd.write("\203\203");  // was 7, should be 0 for the curved C top left
  // 1
  lcd.write("  ");
  // 2
//  lcd.write("\143\143");
  lcd.write("\203\203");
  lcd.setCursor(location, 2); // set cursor to colum 0, line 1 (second row)
  // 3
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // 4
  lcd.write("  ");  // bottom half of the number
  // 5
//  lcd.write("\143\143");
  lcd.write("\203\203");
  lcd.setCursor(location, 3); // set cursor to colum 0, line 1 (second row)
  // 3
//  lcd.write("\146\143");  // call each segment to create
  lcd.write("\206\203");  // call each segment to create
  // 4
//  lcd.write("\147\147");  // bottom half of the number
  lcd.write("\207\207");  // bottom half of the number
  // 5
//  lcd.write("\143\150");
  lcd.write("\203\210");
  lcd.setPrint8x16CharacterMode(true);
}

void customO_SSD_thin(int location)
{
  lcd.setPrint8x16CharacterMode(false);  // needed? Will inadvertantly reset big characters
  lcd.setCursor(location,0);
  // 0 1 2
//  lcd.write("\142\144\145");  // was 7, should be 0 for the curved C top left
  lcd.write("\202\204\205");  // was 7, should be 0 for the curved C top left
  lcd.setCursor(location,1);
  // 0 1 2
//  lcd.write("\143 \143");  // was 7, should be 0 for the curved C top left
  lcd.write("\203 \203");  // was 7, should be 0 for the curved C top left
  lcd.setCursor(location, 2); // set cursor to colum 0, line 1 (second row)
  // 3 4 5
//  lcd.write("\143\143");
  lcd.write("\203 \203");
  lcd.setCursor(location, 3); // set cursor to colum 0, line 1 (second row)
  // 3
//  lcd.write("\146\147\150");  // call each segment to create
  lcd.write("\206\207\210");  // call each segment to create
  lcd.setPrint8x16CharacterMode(true);
}

void customP_SSD(int location)
{
  lcd.setPrint8x16CharacterMode(false);  // needed? Will inadvertantly reset big characters
  lcd.setCursor(location,0);
  // 0
//  lcd.write("\142\143");  // was 7, should be 0 for the curved C top left
  lcd.write("\202\203");  // was 7, should be 0 for the curved C top left
  // 6
//  lcd.write("\151\151");
  lcd.write("\211\211");
  // 2
//  lcd.write("\143\145");
  lcd.write("\203\205");
  lcd.setCursor(location,1);
  // 0
//  lcd.write("\143\143");  // was 7, should be 0 for the curved C top left
  lcd.write("\203\203");  // was 7, should be 0 for the curved C top left
  // 6
//  lcd.write("\152\152");
  lcd.write("\212\212");
  // 2
//  lcd.write("\143\143"); // flat bottom loop
//  lcd.write("\203\203");
//  lcd.write("\143\150"); // curved bottom loop
  lcd.write("\203\210");
  lcd.setCursor(location, 2);
  // 5
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // ' '
  lcd.write("  ");
  // ' '
  lcd.write("  ");
  lcd.setCursor(location, 3);
  // 5
//  lcd.write("\143\150");
  lcd.write("\203\210");
  // ' '
  lcd.write("  ");
  // ' '
  lcd.write("  ");
  lcd.setPrint8x16CharacterMode(true);  // needed? Will inadvertantly reset big characters
}

void customP_SSD_thin(int location)
{
  lcd.setPrint8x16CharacterMode(false);  // needed? Will inadvertantly reset big characters
  lcd.setCursor(location,0);
  // 0 6 2
//  lcd.write("\142\151\145");  // was 7, should be 0 for the curved C top left
  lcd.write("\202\211\205");  // was 7, should be 0 for the curved C top left
  lcd.setCursor(location,1);
  // 0 6 2
//  lcd.write("\143\152\143");   // flat bottom loop
//  lcd.write("\203\212\203");  // was 7, should be 0 for the curved C top left
//  lcd.write("\143\152\150"); // curved bottom loop
  lcd.write("\203\212\210");  
  lcd.setCursor(location, 2);
  // 5 ' ' ' '
//  lcd.write("\143  ");
  lcd.write("\203  ");
  lcd.setCursor(location, 3);
  // 5 ' ' ' '
//  lcd.write("\150  ");
  lcd.write("\210  ");
  lcd.setPrint8x16CharacterMode(true);  // needed? Will inadvertantly reset big characters
}

void customT_SSD(int location)
{
  lcd.setPrint8x16CharacterMode(false);  // needed? Will inadvertantly reset big characters
  lcd.setCursor(location,0);
  // 1
//  lcd.write("\144\144");  // should be 1
  lcd.write("\204\204");  // should be 1
  // 255
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // 1
//  lcd.write("\144\144");  // should be 1
  lcd.write("\204\204");  // should be 1
  lcd.setCursor(location,1);
  // 1
  lcd.write("  ");  // should be 1
  // 255
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // 1
  lcd.write("  ");  // should be 1
  lcd.setCursor(location, 2);
  // ' '
  lcd.write("  ");
  // 3
//  lcd.write("\143\143");
  lcd.write("\203\203");
  // ' '
  lcd.write("  ");
  lcd.setCursor(location, 3);
  // ' '
  lcd.write("  ");
  // 3
//  lcd.write("\146\143");
  lcd.write("\206\203");
  // ' '
  lcd.write("  ");
  lcd.setPrint8x16CharacterMode(true);  // needed? Will inadvertantly reset big characters
}

void customT_SSD_thin(int location)
{
  lcd.setPrint8x16CharacterMode(false);  // needed? Will inadvertantly reset big characters
  lcd.setCursor(location,0);
  // 1 255 1
//  lcd.write("\144\143\144");  // should be 1
  lcd.write("\204\203\204");  // should be 1
  lcd.setCursor(location,1);
  // 1 255 1
//  lcd.write(" \143 ");
  lcd.write(" \203");
  lcd.setCursor(location, 2);
  // ' ' 3 ' '
//  lcd.write(" \143 ");
  lcd.write(" \203 ");
  lcd.setCursor(location, 3);
  // ' ' 3 ' '
//  lcd.write(" \146 ");
  lcd.write(" \206 ");
  lcd.setPrint8x16CharacterMode(true);  // needed? Will inadvertantly reset big characters
}

//END BIG CHARACTER SHIZ
