      
#include "derivative.h"      
#include "clock.h"
#include "Interrupt.h"




//==================================================================================================
// ��ʼ��ʱ�ӣ�PLL��������ʱ��Ϊ�ⲿ�����������16MHZ
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