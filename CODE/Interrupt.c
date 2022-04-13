#include "derivative.h"      /* derivative-specific definitions */
#include "COM0.h"

extern void near _Startup(void);
extern void near vPortTickInterrupt( void );
extern void near vPortYield( void );

unsigned long ulCLOCK_SYSTEM_TICK = 0;

#pragma CODE_SEG __NEAR_SEG NON_BANKED

static void MCU_init_reset(void);
/*
** ===================================================================
**     Method      :  MCU_init_reset (component MC9S12XET256_80)
**
**     Description :
**         Device initialization code for after reset initialization.
** ===================================================================
*/
static void MCU_init_reset(void)
{

  /*  Initialization of memory configuration */
  /* MMCCTL1: TGMRAMON=0,EEEIFRON=0,PGMIFRON=0,RAMHM=0,EROMON=0,ROMHM=0,ROMON=1 */
  MMCCTL1 = 0x01U;                                      
  /* DIRECT: DP15=0,DP14=0,DP13=0,DP12=0,DP11=0,DP10=0,DP9=0,DP8=0 */
  DIRECT = 0x00U;                                      
  /* IVBR: IVB_ADDR=0xFF */
  IVBR = 0xFFU;                                      
  /* ECLKCTL: NECLK=1,NCLKX2=1,DIV16=0,EDIV4=0,EDIV3=0,EDIV2=0,EDIV1=0,EDIV0=0 */
  ECLKCTL = 0xC0U;                                      
  /* Jump to the default entry point */
  /*lint -save  -e950 Disable MISRA rule (1.1) checking. */
  asm jmp _Startup;
  /*lint -restore Enable MISRA rule (1.1) checking. */
} /*MCU_init*/

/*
** ===================================================================
**     Interrupt handler : isr_default
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

__interrupt void isr_default(void)
{
    for(;;);
}


/* end of isr_default */

/*
** ===================================================================
**     Interrupt handler : isrVrti
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

__interrupt void isrVrti(void)
{
    CRGFLG_RTIF = 1;                  /*  Clear Interrupt Flag    */     
    ulCLOCK_SYSTEM_TICK++;
    //os_printf("XIRQ ERROR");
}
/* end of isrVrti */
#pragma CODE_SEG DEFAULT

/* Interrupt vector table */


/* ISR prototype */
typedef void (*near tIsrFunc)(void);

#ifndef UNASSIGNED_ISR
  #define UNASSIGNED_ISR isr_default   /* unassigned interrupt service routine */
#endif

static const tIsrFunc _InterruptVectorTable[] @0xFF10U = { /* Interrupt vector table */

  /* ISR name                               No.  Address Pri  Name            */
  &UNASSIGNED_ISR,                      /* 0x08  0xFF10   -   ivVsi           */
  &UNASSIGNED_ISR,                      /* 0x09  0xFF12   -   ivVsyscall      */
  &UNASSIGNED_ISR,                      /* 0x0A  0xFF14   -   ivVmpuaccesserr */
  &UNASSIGNED_ISR,                      /* 0x0B  0xFF16   -   ivVxsei         */
  &UNASSIGNED_ISR,                      /* 0x0C  0xFF18   1   ivVReserved115  */
  &UNASSIGNED_ISR,                      /* 0x0D  0xFF1A   1   ivVReserved114  */
  &UNASSIGNED_ISR,                      /* 0x0E  0xFF1C   1   ivVReserved113  */
  &UNASSIGNED_ISR,                      /* 0x0F  0xFF1E   1   ivVReserved112  */
  &UNASSIGNED_ISR,                      /* 0x10  0xFF20   1   ivVReserved111  */
  &UNASSIGNED_ISR,                      /* 0x11  0xFF22   1   ivVReserved110  */
  &UNASSIGNED_ISR,                      /* 0x12  0xFF24   1   ivVReserved109  */
  &UNASSIGNED_ISR,                      /* 0x13  0xFF26   1   ivVReserved108  */
  &UNASSIGNED_ISR,                      /* 0x14  0xFF28   1   ivVReserved107  */
  &UNASSIGNED_ISR,                      /* 0x15  0xFF2A   1   ivVReserved106  */
  &UNASSIGNED_ISR,                      /* 0x16  0xFF2C   1   ivVReserved105  */
  &UNASSIGNED_ISR,                      /* 0x17  0xFF2E   1   ivVReserved104  */
  &UNASSIGNED_ISR,                      /* 0x18  0xFF30   1   ivVReserved103  */
  &UNASSIGNED_ISR,                      /* 0x19  0xFF32   1   ivVReserved102  */
  &UNASSIGNED_ISR,                      /* 0x1A  0xFF34   1   ivVReserved101  */
  &UNASSIGNED_ISR,                      /* 0x1B  0xFF36   1   ivVReserved100  */
  &UNASSIGNED_ISR,                      /* 0x1C  0xFF38   1   ivVReserved99   */
  &UNASSIGNED_ISR,                      /* 0x1D  0xFF3A   1   ivVReserved98   */
  &UNASSIGNED_ISR,                      /* 0x1E  0xFF3C   1   ivVatd1compare  */
  &UNASSIGNED_ISR,                      /* 0x1F  0xFF3E   1   ivVatd0compare  */
  &UNASSIGNED_ISR,                      /* 0x20  0xFF40   1   ivVReserved95   */
  &UNASSIGNED_ISR,                      /* 0x21  0xFF42   1   ivVReserved94   */
  &UNASSIGNED_ISR,                      /* 0x22  0xFF44   1   ivVReserved93   */
  &UNASSIGNED_ISR,                      /* 0x23  0xFF46   1   ivVReserved92   */
  &UNASSIGNED_ISR,                      /* 0x24  0xFF48   1   ivVReserved91   */
  &UNASSIGNED_ISR,                      /* 0x25  0xFF4A   1   ivVReserved90   */
  &UNASSIGNED_ISR,                      /* 0x26  0xFF4C   1   ivVReserved89   */
  &UNASSIGNED_ISR,                      /* 0x27  0xFF4E   1   ivVReserved88   */
  &UNASSIGNED_ISR,                      /* 0x28  0xFF50   1   ivVReserved87   */
  &UNASSIGNED_ISR,                      /* 0x29  0xFF52   1   ivVReserved86   */
  &UNASSIGNED_ISR,                      /* 0x2A  0xFF54   1   ivVReserved85   */
  &UNASSIGNED_ISR,                      /* 0x2B  0xFF56   1   ivVReserved84   */
  &UNASSIGNED_ISR,                      /* 0x2C  0xFF58   1   ivVReserved83   */
  &UNASSIGNED_ISR,                      /* 0x2D  0xFF5A   1   ivVReserved82   */
  &UNASSIGNED_ISR,                      /* 0x2E  0xFF5C   1   ivVReserved81   */
  &UNASSIGNED_ISR,                      /* 0x2F  0xFF5E   1   ivVReserved80   */
  &UNASSIGNED_ISR,                      /* 0x30  0xFF60   1   ivVReserved79   */
  &UNASSIGNED_ISR,                      /* 0x31  0xFF62   1   ivVReserved78   */
  &UNASSIGNED_ISR,                      /* 0x32  0xFF64   1   ivVxst7         */
  &UNASSIGNED_ISR,                      /* 0x33  0xFF66   1   ivVxst6         */
  &UNASSIGNED_ISR,                      /* 0x34  0xFF68   1   ivVxst5         */
  &UNASSIGNED_ISR,                      /* 0x35  0xFF6A   1   ivVxst4         */
  &UNASSIGNED_ISR,                      /* 0x36  0xFF6C   1   ivVxst3         */
  &UNASSIGNED_ISR,                      /* 0x37  0xFF6E   1   ivVxst2         */
  &UNASSIGNED_ISR,                      /* 0x38  0xFF70   1   ivVxst1         */
  &UNASSIGNED_ISR,                      /* 0x39  0xFF72   1   ivVxst0         */
  &UNASSIGNED_ISR,                      /* 0x3A  0xFF74   1   ivVpit3         */
  &UNASSIGNED_ISR,                      /* 0x3B  0xFF76   1   ivVpit2         */
  &UNASSIGNED_ISR,                      /* 0x3C  0xFF78   1   ivVpit1         */
  &UNASSIGNED_ISR,                      /* 0x3D  0xFF7A   1   ivVpit0         */
  &UNASSIGNED_ISR,                      /* 0x3E  0xFF7C   1   ivVhti          */
  &UNASSIGNED_ISR,                      /* 0x3F  0xFF7E   1   ivVapi          */
  &UNASSIGNED_ISR,                      /* 0x40  0xFF80   1   ivVlvi          */
  &UNASSIGNED_ISR,                      /* 0x41  0xFF82   1   ivVReserved62   */
  &UNASSIGNED_ISR,                      /* 0x42  0xFF84   1   ivVReserved61   */
  &UNASSIGNED_ISR,                      /* 0x43  0xFF86   1   ivVReserved60   */
  &UNASSIGNED_ISR,                      /* 0x44  0xFF88   1   ivVReserved59   */
  &UNASSIGNED_ISR,                      /* 0x45  0xFF8A   1   ivVReserved58   */
  &UNASSIGNED_ISR,                      /* 0x46  0xFF8C   1   ivVpwmesdn      */
  &UNASSIGNED_ISR,                      /* 0x47  0xFF8E   1   ivVportp        */
  &UNASSIGNED_ISR,                      /* 0x48  0xFF90   1   ivVcan4tx       */
  &UNASSIGNED_ISR,                      /* 0x49  0xFF92   1   ivVcan4rx       */
  &UNASSIGNED_ISR,                      /* 0x4A  0xFF94   1   ivVcan4err      */
  &UNASSIGNED_ISR,                      /* 0x4B  0xFF96   1   ivVcan4wkup     */
  &UNASSIGNED_ISR,                      /* 0x4C  0xFF98   1   ivVReserved51   */
  &UNASSIGNED_ISR,                      /* 0x4D  0xFF9A   1   ivVReserved50   */
  &UNASSIGNED_ISR,                      /* 0x4E  0xFF9C   1   ivVReserved49   */
  &UNASSIGNED_ISR,                      /* 0x4F  0xFF9E   1   ivVReserved48   */
  &UNASSIGNED_ISR,                      /* 0x50  0xFFA0   1   ivVReserved47   */
  &UNASSIGNED_ISR,                      /* 0x51  0xFFA2   1   ivVReserved46   */
  &UNASSIGNED_ISR,                      /* 0x52  0xFFA4   1   ivVReserved45   */
  &UNASSIGNED_ISR,                      /* 0x53  0xFFA6   1   ivVReserved44   */
  &UNASSIGNED_ISR,                      /* 0x54  0xFFA8   1   ivVcan1tx       */
  &UNASSIGNED_ISR,                      /* 0x55  0xFFAA   1   ivVcan1rx       */
  &UNASSIGNED_ISR,                      /* 0x56  0xFFAC   1   ivVcan1err      */
  &UNASSIGNED_ISR,                      /* 0x57  0xFFAE   1   ivVcan1wkup     */
  &UNASSIGNED_ISR,                      /* 0x58  0xFFB0   1   ivVcan0tx       */
  &UNASSIGNED_ISR,                      /* 0x59  0xFFB2   1   ivVcan0rx       */
  &UNASSIGNED_ISR,                      /* 0x5A  0xFFB4   1   ivVcan0err      */
  &UNASSIGNED_ISR,                      /* 0x5B  0xFFB6   1   ivVcan0wkup     */
  &UNASSIGNED_ISR,                      /* 0x5C  0xFFB8   1   ivVflash        */
  &UNASSIGNED_ISR,                      /* 0x5D  0xFFBA   1   ivVflashfd      */
  &UNASSIGNED_ISR,                      /* 0x5E  0xFFBC   1   ivVspi2         */
  &UNASSIGNED_ISR,                      /* 0x5F  0xFFBE   1   ivVspi1         */
  &UNASSIGNED_ISR,                      /* 0x60  0xFFC0   1   ivViic0         */
  &UNASSIGNED_ISR,                      /* 0x61  0xFFC2   1   ivVReserved30   */
  &UNASSIGNED_ISR,                      /* 0x62  0xFFC4   1   ivVcrgscm       */
  &UNASSIGNED_ISR,                      /* 0x63  0xFFC6   1   ivVcrgplllck    */
  &UNASSIGNED_ISR,                      /* 0x64  0xFFC8   1   ivVectpabovf    */
  &UNASSIGNED_ISR,                      /* 0x65  0xFFCA   1   ivVectmdcu      */
  &UNASSIGNED_ISR,                      /* 0x66  0xFFCC   1   ivVReserved25   */
  &UNASSIGNED_ISR,                      /* 0x67  0xFFCE   1   ivVportj        */
  &UNASSIGNED_ISR,                      /* 0x68  0xFFD0   1   ivVatd1         */
  &UNASSIGNED_ISR,                      /* 0x69  0xFFD2   1   ivVatd0         */
  &UNASSIGNED_ISR,                      /* 0x6A  0xFFD4   1   ivVsci1         */
  &UNASSIGNED_ISR,                      /* 0x6B  0xFFD6   1   ivVsci0         */
  &UNASSIGNED_ISR,                      /* 0x6C  0xFFD8   1   ivVspi0         */
  &UNASSIGNED_ISR,                      /* 0x6D  0xFFDA   1   ivVectpaie      */
  &UNASSIGNED_ISR,                      /* 0x6E  0xFFDC   1   ivVectpaaovf    */
  &UNASSIGNED_ISR,                      /* 0x6F  0xFFDE   1   ivVectovf       */
  &UNASSIGNED_ISR,                      /* 0x70  0xFFE0   1   ivVectch7       */
  &UNASSIGNED_ISR,                      /* 0x71  0xFFE2   1   ivVectch6       */
  &UNASSIGNED_ISR,                      /* 0x72  0xFFE4   1   ivVectch5       */
  &UNASSIGNED_ISR,                      /* 0x73  0xFFE6   1   ivVectch4       */
  &UNASSIGNED_ISR,                      /* 0x74  0xFFE8   1   ivVectch3       */
  &UNASSIGNED_ISR,                      /* 0x75  0xFFEA   1   ivVectch2       */
  &UNASSIGNED_ISR,                      /* 0x76  0xFFEC   1   ivVectch1       */
  &UNASSIGNED_ISR,                      /* 0x77  0xFFEE   1   ivVectch0       */
  &vPortTickInterrupt,                             /* 0x78  0xFFF0   1   ivVrti          */
  &UNASSIGNED_ISR,                      /* 0x79  0xFFF2   1   ivVirq          */
  &UNASSIGNED_ISR,                      /* 0x7A  0xFFF4   -   ivVxirq         */
  &vPortYield,                      /* 0x7B  0xFFF6   -   ivVswi          */
  &UNASSIGNED_ISR                       /* 0x7C  0xFFF8   -   ivVtrap         */
};

static const tIsrFunc _ResetVectorTable[] @0xFFFAU = { /* Reset vector table */
  /* Reset handler name                    Address Name             Description */
  &MCU_init_reset,                      /* 0xFFFA  ivVcop           unused by PE */
  &MCU_init_reset,                      /* 0xFFFC  ivVclkmon        unused by PE */
  &MCU_init_reset                       /* 0xFFFE  ivVreset         used by PE */
};

