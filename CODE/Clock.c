      
#include "derivative.h"      
#include "clock.h"
#include "Interrupt.h"




//==================================================================================================
// 初始化时钟，PLL配置总线时钟为外部晶振的两倍，16MHZ
void Clock_Init(void) {
  CRGFLG_LOCKIF = 1;                
  CRGINT_LOCKIE = 0;                
  CLKSEL = 0x00;                                                                                        
  PLLCTL_PLLON = 0;
  SYNR = 0x01;                       
  REFDV = 0x00;
  PLLCTL_PLLON = 1; 
  while(CRGFLG_LOCK == 0) {         
    ;
  }
  
  CLKSEL_PLLSEL = 1;
  //RTICTL = 0x97;
  //CRGINT_RTIE = 1;                 
}

//==================================================================================================
   

//==================================================================================================