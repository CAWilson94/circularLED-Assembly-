#include "msp430.h"                     ; #define controlled include file

        NAME    main                    ; module name

        PUBLIC                          ; make the main label vissible
                                        ; outside this module
                                        
        ORG     0FFFEh                  ; set assembler location counter
        DC16    init                    ; set reset vector to 'init' label
        
        RSEG DATA16_N ; awrite then
        
        lim:
        DS16 1  ; limit value for loop (16 bit counts to 128)
          
        counter:
        DS16 1                          ; Counter value for loop (16 bit)
        
        ADC_RESULT:                     ; whats in your potentiometer
          DS8 2
          
        DIRECTION:                     ; whats in your potentiometer
          DS16 1
        
        RSEG CSTACK                     ; pre-declaration of segment
           
        RSEG CODE                       ; place program in 'CODE' segment
         
        Int_ADC:    
        
           MOV.W &0x712, ADC_RESULT     ;ADCMEM0
           RETI                         ;return from interrupt
        
        
        timer_interrupt:                ; Timer interrupt routine
        
        CMP.W #0x02, DIRECTION          ; Check for middle LED direction
        JZ middle
        
        CMP.W #1, DIRECTION             ; Check for right LED direction
        JZ right
        
        
        CMP.W #0, DIRECTION             ; Check for left LED direction
        JGE left 
        RETI
        
          left:                         ; if left, sub until min count & reset
            SUB.W #1, counter
            JZ counter_8
            RETI
          
          right:                        ; if left, add until max count & reset
            ADD.W #1, counter
            CMP.W #9, counter
            JGE counter_1
            RETI
            
          middle:                       ; if middle, only light current LED. 
            NOP                         ; I.e. do nothing
            RETI
            
          counter_8:                    ; Set counter value to max (8)
            MOV.W #8, counter
            RETI                        ; return from interrupt
            
          counter_1:
            MOV.W #0x01, counter        ; Set counter value to min(0)
            RETI                        ; return from interrupt
          
            

led1:

     BIS.B #0x01, P8OUT;
     BIC.B #0x02, P5OUT;
     BIC.B #0x04, P5OUT;
     BIC.B #0x08, P5OUT;

     BIC.B #0x80, P2OUT;
     JMP coreloop;
     
led2:

     BIC.B #0x01, P8OUT;
     BIS.B #0x02, P5OUT;
     BIC.B #0x04, P5OUT;
     BIC.B #0x08, P5OUT;
        
     BIC.B #0x80, P2OUT;
     JMP coreloop;

     
led3:
     BIC.B #0x01, P8OUT;
     BIC.B #0x02, P5OUT;
     BIS.B #0x04, P5OUT;
     BIC.B #0x08, P5OUT;
        
     BIC.B #0x80, P2OUT;
     JMP coreloop;
     
led4:
     BIC.B #0x01, P8OUT;
     BIC.B #0x02, P5OUT;
     BIC.B #0x04, P5OUT;
     BIS.B #0x08, P5OUT;
        
     BIC.B #0x80, P2OUT;
     JMP coreloop;
     
led5:
     BIC.B #0x01, P8OUT;
     BIS.B #0x02, P5OUT;
     BIS.B #0x04, P5OUT;
     BIS.B #0x08, P5OUT;
        
     BIS.B #0x80, P2OUT;
     JMP coreloop;
     
led6:
     BIS.B #0x01, P8OUT;
     BIC.B #0x02, P5OUT;
     BIS.B #0x04, P5OUT;
     BIS.B #0x08, P5OUT;
        
     BIS.B #0x80, P2OUT;
     JMP coreloop;
     
led7:
     BIS.B #0x01, P8OUT;
     BIS.B #0x02, P5OUT;
     BIC.B #0x04, P5OUT;
     BIS.B #0x08, P5OUT;
        
     BIS.B #0x80, P2OUT;
     JMP coreloop;
     
led8:
     BIS.B #0x01, P8OUT;
     BIS.B #0x02, P5OUT;
     BIS.B #0x04, P5OUT;
     BIC.B #0x08, P5OUT;
        
     BIS.B #0x80, P2OUT;
     JMP coreloop;
/*
  Checking for values in the potentiometer to vary speed and direction of LED's
*/

check_more_765:                         
      MOV.W #0x01, DIRECTION
      
      MOV.W #3226, TA0CCR0  ; give the timer a value of 3277 to count to 
      BIS.W #0x100, TA0CTL  ; select ACLK
      BIS.W #0x10, TA0CTL   ; Select up mode
      BIS.W #CCIE, TA0CCTL0 ; Enable timer interrupts
      
      JMP caseShit
      
check_less_765:
      MOV.W #0x01, DIRECTION
      
      MOV.W #6226, TA0CCR0  ; give the timer a value of 3277 to count to 
      BIS.W #0x100, TA0CTL  ; select ACLK
      BIS.W #0x10, TA0CTL   ; Select up mode
      BIS.W #CCIE, TA0CCTL0 ; Enable timer interrupts
      
      JMP caseShit

check_less_500:
      MOV.W #0x02, DIRECTION
      NOP
      JMP caseShit

check_less_400:
      MOV.W #0x0, DIRECTION
      
      MOV.W #6226, TA0CCR0  ; give the timer a value of 3277 to count to 
      BIS.W #0x100, TA0CTL  ; select ACLK
      BIS.W #0x10, TA0CTL   ; Select up mode
      BIS.W #CCIE, TA0CCTL0 ; Enable timer interrupts
      
      JMP caseShit
      
check_less_192:
     MOV.W #0x0, DIRECTION
    
     MOV.W #3277, TA0CCR0  ; give the timer a value of 3277 to count to 
     BIS.W #0x100, TA0CTL  ; select ACLK
     BIS.W #0x10, TA0CTL   ; Select up mode
     BIS.W #CCIE, TA0CCTL0 ; Enable timer interrupts
    
     JMP caseShit  
    
caseShit:                  ; Increments through LED's in their circular order
      CMP.W #1, counter
      JEQ led1
      CMP.W #2, counter
      JEQ led2
      CMP.W #3, counter
      JEQ led3
      CMP.W #4, counter
      JEQ led4
      CMP.W #5, counter
      JEQ led8
      CMP.W #6, counter
      JEQ led7
      CMP.W #7, counter
      JEQ led6
      CMP.W #8, counter
      JEQ led5
      JMP coreloop;
 

     
init:   MOV     #SFE(CSTACK), SP        ; set up stack

main:   NOP                             ; main program
        MOV.W   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
        BIC.W #LOCKLPM5, &PM5CTL0 
        // Set Direction of LED's to out
        BIS.B #0x01, P8DIR              
        BIS.B #0x02, P5DIR
        BIS.B #0x04, P5DIR
        BIS.B #0x08, P5DIR
        // Bottom rail
        BIS.B #0x80, P2DIR
        
        BIS.W #ADCPCTL9, SYSCFG2      ; Initialize the Potentiometer 
        
        BIS.W #ADCSHT_2, ADCCTL0      ; ADCCTL0 |= ADCSHT_2
        BIS.W #ADCON, ADCCTL0         ; ADCCTL0 |= ADCON
        BIS.W #ADCSHP, ADCCTL1        ; ADCCTL1 |= ADCSHP
        BIS.W #ADCRES, ADCCTL2        ; ADCCTL2 &= ~ADCRES
        BIS.W #ADCINCH_9, ADCMCTL0    ; ADCMCTL0 |= ADCINCH_9
        BIS.W #ADCIE0, ADCIE          ; Enable ADC interrupt

        MOV.W #8, counter       ; put 8 into the counter
        MOV.W #2, DIRECTION     ; Do nothing

        MOV.W #3277, TA0CCR0  ; give the timer a value of 3277 to count to 
        BIS.W #0x100, TA0CTL  ; select ACLK
        BIS.W #0x10, TA0CTL   ; Select up mode
        BIS.W #CCIE, TA0CCTL0 ; Enable timer interrupts
     
        NOP 
        EINT                  ; enable interrupts
        NOP
        
 coreloop:
 
      BIS.W #(ADCENC|ADCSC),ADCCTL0; 
      
      CMP.W #192, ADC_RESULT
      JN check_less_192  
      CMP.W #400, ADC_RESULT
      JN check_less_400
      CMP.W #500, ADC_RESULT
      JN check_less_500
      CMP.W #765, ADC_RESULT
      JN check_less_765
    
      JMP check_more_765
      NOP
      
      
    COMMON INTVEC
        ; Defaults to starting at 0
            ORG ADC_VECTOR ; Move origin to 0x60, the interrupt vector for ADC
        DC16 Int_ADC ; Point to the interrupt routine
        
            ORG TIMER0_A0_VECTOR;
        DC16 timer_interrupt;
            
 
      END
        