
#include "BigCharacters.h"

///BIG CHARACTER SHIZ

const int kLT = 0;
const int kUB = 1;
const int kRT = 2;
const int kLL = 3;
const int kLB = 4;
const int kLR = 5;
const int kMB = 6;
const int kcross = 7;


// the 8 arrays that form each segment of the custom numbers
// Custome character "0"
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

// Custome character "1"
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

// Custome character "2"
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

// Custome character "3"
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

// Custome character "4"
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

// Custome character "5"
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

// Custome character "6"
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

// Custome character "7"
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

// Custome character "8"
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

// Custome character "9"
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
  lcd.write(" ");  // call each segment to create
  lcd.write(" ");  // bottom half of the number
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
  lcd.write(" ");
  lcd.write(2);
  lcd.setCursor(location,1);
  lcd.write(3);
  lcd.write(4);  
  lcd.write(5);
}

void customI(int location)
{
  lcd.setCursor(location,0);
  lcd.write(" ");   
  lcd.write(2);   // was 7 - 2 gives a stylised "I"
  lcd.write(" ");
  lcd.setCursor(location, 1);
  lcd.write(" ");
  lcd.write(3);  // was 7 - 3 gives a stylisd "I"
  lcd.write(" ");
}

void customC(int location)
{
  lcd.setCursor(location,0);
  lcd.write(0);  // was 7, should be 0 for the curved C top left
  lcd.write(1);  // should be 1
  lcd.write(7);  // was 1, should have been 9, now is 7
  lcd.setCursor(location, 1);
  lcd.write(3);
  lcd.write(4);
  lcd.write(4); 
}

void customE(int location)
{
  lcd.setCursor(location,0);
  lcd.write(0);  // was 7, should be 0 for the curved E top left
  lcd.write(6);
  lcd.write(" "); // was a 6
  lcd.setCursor(location, 1);
  lcd.write(3);  // was 7 - 3 gives a stylisd "E"
  lcd.write(4);
  lcd.write(" "); // was a 4
}

void customF(int location)
{
  lcd.setCursor(location,0);
  lcd.write(0);
  lcd.write(6);
  lcd.write(" ");
  lcd.setCursor(location, 1);
  lcd.write(5);
  lcd.write(" ");
  lcd.write(" ");
}

void customR(int location)
{
  lcd.setCursor(location,0);
  lcd.write(0);
  lcd.write(6);
  lcd.write(2);  // 2 or 5 ?
  lcd.setCursor(location, 1);
  lcd.write(5);
  lcd.write(" ");
  lcd.write(7);
}

void customS(int location)
{
  lcd.setCursor(location,0);
  lcd.write(0);  // was 7, should be 0 for the curved S top left
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
  lcd.write(2);  // 0 or 2
  lcd.write(4);
  lcd.write(2);  // 0 or 2
  lcd.setCursor(location,1);
  lcd.write(3);  // 3 or 5
  lcd.write(" ");  
  lcd.write(3);  // 3 or 5
}

void customA(int location)
{
  lcd.setCursor(location,0);
  lcd.write(0);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(location,1);
  lcd.write(3);
  lcd.write(" ");  
  lcd.write(3);
}

void customB(int location)
{
  lcd.setCursor(location,0);
  lcd.write(255);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(location,1);
  lcd.write(255);
  lcd.write(4);  
  lcd.write(5);
}

void customD(int location)
{
  lcd.setCursor(location,0);
  lcd.write(255);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(location,1);
  lcd.write(255);
  lcd.write(4);  
  lcd.write(5);
}

void customK(int location)
{
  lcd.setCursor(location,0);
  lcd.write(2);
  lcd.write(" ");
  lcd.write(2);  // 2 or 5 ?
  lcd.setCursor(location, 1);
  lcd.write(5);
  lcd.write(" ");
  lcd.write(7);
}

void customL(int location)
{
  lcd.setCursor(location,0);
  lcd.write(2);   
  lcd.write(" ");   // was 7 - 2 gives a stylised "I"
  lcd.write(" ");
  lcd.setCursor(location, 1);
  lcd.write(255);
  lcd.write(4);  // was 7 - 3 gives a stylisd "I"
  lcd.write(" ");
}

void customO(int location)
{
  lcd.setCursor(location,0);
  lcd.write(0);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(location,1);
  lcd.write(3);
  lcd.write(4);  
  lcd.write(5);
}

void customP(int location)
{
  lcd.setCursor(location,0);
  lcd.write(0);
  lcd.write(6);
  lcd.write(2);  // 2 or 5 ?
  lcd.setCursor(location, 1);
  lcd.write(5);
  lcd.write(" ");
  lcd.write(" ");
}

void customT(int location)
{
  lcd.setCursor(location,0);
  lcd.write(1);   
  lcd.write(255); 
  lcd.write(1);
  lcd.setCursor(location, 1);
  lcd.write(" ");
  lcd.write(3);  // was 7 - 3 gives a stylisd "T"
  lcd.write(" ");
}

//END BIG CHARACTER SHIZ
