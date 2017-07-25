#include "Arduino.h"
#include "LiquidCrystalFast.h"


///BIG CHARACTER SHIZ
extern const int kLT;
extern const int kUB;
extern const int kRT;
extern const int kLL;
extern const int kLB;
extern const int kLR;
extern const int kMB;
extern const int kcross;


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

void customA(int location);
void customB(int location);
void customD(int location);
void customK(int location);
void customL(int location);
void customO(int location);
void customP(int location);
void customT(int location);



//END BIG CHARACTER SHIZ
