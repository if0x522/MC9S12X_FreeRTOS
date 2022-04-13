#include "TickTimer.h"

byte TickTimer_SetFreqHz(word Freq)
{
  byte rtval;                                                

  if ((Freq > 1000) || (Freq < 50))    
    return 0;                  
  if(Freq  == 1000){
     rtval = 0x9F;
  }else if((Freq < 1000)&&(Freq> 500)){
     rtval = 0xa0;
      rtval = rtval|((byte)(7812/Freq) - 1);
  }else if((Freq < 499)&&(Freq> 250)){
     rtval = 0xb0;
      rtval = rtval|((byte)(3906/Freq) - 1);
  }else if((Freq < 251)&&(Freq> 122)){
     rtval = 0xc0;
      rtval = rtval|((byte)(1953/Freq) - 1);
  }else if((Freq < 123)&&(Freq> 61)){
     rtval = 0xd0;
      rtval = rtval|((byte)(976/Freq) - 1);
  }else if((Freq < 62)&&(Freq> 50)){
     rtval = 0xe0;
      rtval = rtval|((byte)(488/Freq) - 1);
  }
  RTICTL = rtval;
  return 1;                       
}
//==================================================================================================
byte TickTimer_Enable(void)
{
  CRGINT_RTIE = 1;
  CRGFLG_RTIF = 1;                         
  return 1;                       
}