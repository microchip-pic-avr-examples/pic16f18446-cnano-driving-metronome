/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC16F18446
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.00
        MPLAB             :  MPLAB X 5.10

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "pin_manager.h"




void (*IOCBF5_InterruptHandler)(void);


void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    /**
    TRISx registers
    */
    TRISA = 0x1B;
    TRISB = 0x80;
    TRISC = 0x00;

    /**
    ANSELx registers
    */
    ANSELC = 0xFF;
    ANSELB = 0x80;
    ANSELA = 0x13;

    /**
    WPUx registers
    */
    WPUB = 0x50;
    WPUA = 0x00;
    WPUC = 0x00;

    /**
    ODx registers
    */
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;

    /**
    SLRCONx registers
    */
    SLRCONA = 0x37;
    SLRCONB = 0xF0;
    SLRCONC = 0xFF;


    /**
    IOCx registers 
    */
    //interrupt on change for group IOCBF - flag
    IOCBFbits.IOCBF5 = 0;
    //interrupt on change for group IOCBN - negative
    IOCBNbits.IOCBN5 = 1;
    //interrupt on change for group IOCBP - positive
    IOCBPbits.IOCBP5 = 1;



    // register default IOC callback functions at runtime; use these methods to register a custom function
    IOCBF5_SetInterruptHandler(IOCBF5_DefaultInterruptHandler);
   
    // Enable IOCI interrupt 
    PIE0bits.IOCIE = 1; 
    
	
    RC0PPS = 0x01;   //RC0->CLC1:CLC1OUT;    
    RC3PPS = 0x02;   //RC3->CLC2:CLC2OUT;    
    RB5PPS = 0x17;   //RB5->TMR0:TMR0;    
    RC1PPS = 0x01;   //RC1->CLC1:CLC1OUT;    
    RC4PPS = 0x02;   //RC4->CLC2:CLC2OUT;    
    RC2PPS = 0x02;   //RC2->CLC2:CLC2OUT;    
    RA2PPS = 0x18;   //RA2->NCO1:NCO1OUT;    
    T0CKIPPS = 0x02;   //RA2->TMR0:T0CKI;    
    CLCIN0PPS = 0x0D;   //RB5->CLC3:CLCIN0;    
    CLCIN2PPS = 0x0E;   //RB6->CLC4:CLCIN2;    
    CLCIN1PPS = 0x0C;   //RB4->CLC3:CLCIN1;    
    RC5PPS = 0x02;   //RC5->CLC2:CLC2OUT;    
    RC6PPS = 0x04;   //RC6->CLC4:CLC4OUT;    
    RC7PPS = 0x04;   //RC7->CLC4:CLC4OUT;    
}
  
void PIN_MANAGER_IOC(void)
{   
	// interrupt on change for pin IOCBF5
    if(IOCBFbits.IOCBF5 == 1)
    {
        IOCBF5_ISR();  
    }	
}

/**
   IOCBF5 Interrupt Service Routine
*/
void IOCBF5_ISR(void) {

    // Add custom IOCBF5 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCBF5_InterruptHandler)
    {
        IOCBF5_InterruptHandler();
    }
    IOCBFbits.IOCBF5 = 0;
}

/**
  Allows selecting an interrupt handler for IOCBF5 at application runtime
*/
void IOCBF5_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCBF5_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCBF5
*/
void IOCBF5_DefaultInterruptHandler(void){
    // add your IOCBF5 interrupt custom code
    // or set custom function using IOCBF5_SetInterruptHandler()
}

/**
 End of File
*/