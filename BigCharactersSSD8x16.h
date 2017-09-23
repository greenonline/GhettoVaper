#include "Arduino.h"
#include "Small_SSD1306_Print_8x16_lib.h"


///BIG CHARACTER SHIZ
//extern const int kLT;
//extern const int kUB;
//extern const int kRT;
//extern const int kLL;
//extern const int kLB;
//extern const int kLR;
//extern const int kMB;
//extern const int kcross;


// the 8 arrays that form each segment of the custom numbers
extern byte LT1[8];
extern byte LT2[8];
extern byte LT3[8];
extern byte LT4[8];
extern byte UB1[8];
extern byte UB2[8];
extern byte UB3[8];
extern byte UB4[8];
extern byte RT1[8];
extern byte RT2[8];
extern byte RT3[8];
extern byte RT4[8];
extern byte LL1[8];
extern byte LL2[8];
extern byte LL3[8];
extern byte LL4[8];
extern byte LB1[8];
extern byte LB2[8];
extern byte LB3[8];
extern byte LB4[8];
extern byte LR1[8];
extern byte LR2[8];
extern byte LR3[8];
extern byte LR4[8];
extern byte MB1[8];
extern byte MB2[8];
extern byte MB3[8];
extern byte MB4[8];
//extern byte block[8];
//extern byte blank[8];
extern byte cross1[8];
extern byte cross2[8];
extern byte cross3[8];
extern byte cross4[8];

extern Small_SSD1306_Print_8x16_lib lcd;

void customJ_SSD_thin(int location);
void customU_SSD_thin(int location);
void customI_SSD_thin(int location);
void customC_SSD_thin(int location);
void customE_SSD_thin(int location);
void customF_SSD_thin(int location);
void customR_SSD_thin(int location);
void customS_SSD_thin(int location);
void customH_SSD_thin(int location);

void customA_SSD_thin(int location);
void customB_SSD_thin(int location);
void customD_SSD_thin(int location);
void customK_SSD_thin(int location);
void customL_SSD_thin(int location);
void customO_SSD_thin(int location);
void customP_SSD_thin(int location);
void customT_SSD_thin(int location);

void customJ_SSD(int location);
void customU_SSD(int location);
void customI_SSD(int location);
void customC_SSD(int location);
void customE_SSD(int location);
void customF_SSD(int location);
void customR_SSD(int location);
void customS_SSD(int location);
void customH_SSD(int location);

void customA_SSD(int location);
void customB_SSD(int location);
void customD_SSD(int location);
void customK_SSD(int location);
void customL_SSD(int location);
void customO_SSD(int location);
void customP_SSD(int location);
void customT_SSD(int location);



//END BIG CHARACTER SHIZ
