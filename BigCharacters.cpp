
#include "BigCharacters.h"

// the 8 arrays that form each segment of the custom numbers
 byte  LT[8] = 
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
