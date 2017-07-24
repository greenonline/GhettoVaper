#include "Arduino.h"
#include "LiquidCrystalFast.h"


///BIG CHARACTER SHIZ

// the 8 arrays that form each segment of the custom numbers
extern byte LT[8];
extern byte UB[8];
extern byte RT[8];
extern byte LL[8];
extern byte LB[8];
extern byte LR[8];
extern byte MB[8];
extern byte block[8];
extern byte blank[8];
extern byte cross[8];

extern LiquidCrystalFast lcd;

void customJ(int location);
void customU(int location);
void customI(int location);
void customC(int location);
void customE(int location);
void customF(int location);
void customR(int location);
void customS(int location);
void customH(int location);


//END BIG CHARACTER SHIZ
