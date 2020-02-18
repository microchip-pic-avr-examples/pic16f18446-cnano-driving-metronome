/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC16F18446
        Driver Version    :  2.00
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

#include "mcc_generated_files/mcc.h"

#define NUMBER_OF_CONVERSIONS               ADRPT
#define OFFSET                              4
#define DIVISION_FACTOR                     12
#define STEPS_IN_DIAL                       22
#define STEPS_TO_INITIAL_POSITION           146
#define HALF_OF_MAX_STEPS_NUMBER            160
#define NUMBER_OF_PULSES                    100
#define DURATION_OF_A_PULSE                 30

#define NCO_ENABLE()                        do { NCO1CONbits.EN = 1;} while(0)
#define NCO_DISABLE()                       do { NCO1CONbits.EN = 0;} while(0)
#define TIMER0_PRESCALER()                  do { T0CON1 = 0x01; } while(0)
#define TIMER0_NO_PRESCALER()               do { T0CON1 = 0x00; } while(0)
#define TIMER_START_FROM_ZERO()             do { TMR0_WriteTimer(0x00); } while(0)
#define MODE_METRONOME()                    RB4_SetLow()
#define MODE_FREE_RUN()                     RB4_SetHigh()
#define RUN_CLOCKWISE()                     RB6_SetLow()
#define RUN_COUNTERCLOCKWISE()              RB6_SetHigh()
#define POT_VALUE_TO_NCO_FREQUENCY(pot)     (pot / DIVISION_FACTOR + OFFSET)

/*
                         Main application
 */

static uint16_t METRONOME_getPotentiometerValue(void);

static void METRONOME_initialize(void);

static void METRONOME_setInInitialPosition(void);

static void METRONOME_turnLedAndBuzzerOn(void);

static inline void METRONOME_runCompletelyCounterclockwise(void);

static inline void METRONOME_runInStartPosition(void);

static inline void METRONOME_prepareForOscillating(void);

static void TIMER_runOnePeriod(void);

static uint8_t potValue;

void main(void)
{
    SYSTEM_Initialize();
    
    METRONOME_initialize();
    
    INTERRUPT_GlobalInterruptEnable();

    while (1)
    {
        potValue = METRONOME_getPotentiometerValue() >> 4;
        
        if(potValue == 0)
        {
            NCO_DISABLE();
        }
        else
        {
            NCO_ENABLE();
        }
        
        NCO1INCL = POT_VALUE_TO_NCO_FREQUENCY(potValue);
    }
}

static uint16_t METRONOME_getPotentiometerValue()
{
    ADCC_ClearAccumulator();
    
    while(ADCC_GetCurrentCountofConversions() < NUMBER_OF_CONVERSIONS)
    {
        ADCC_StartConversion(channel_ANA4);

        while (!ADCC_IsConversionDone())
        {
            ;
        }
    }
    
    return ADCC_GetFilterValue();
}

static void METRONOME_initialize(void)
{
    METRONOME_setInInitialPosition();
    
    IOCBF5_SetInterruptHandler(METRONOME_turnLedAndBuzzerOn);
}

static void METRONOME_setInInitialPosition(void)
{
    MODE_FREE_RUN();
    
    METRONOME_runCompletelyCounterclockwise();
    
    METRONOME_runInStartPosition();
    
    METRONOME_prepareForOscillating();
    
    NCO_ENABLE();
    
    TMR0_StartTimer();
}

/*The ON duration was divided into 100 pulses in order to obtain a louder sound of the buzzer*/
static void METRONOME_turnLedAndBuzzerOn(void)
{
    uint8_t index;
    
    for(index = 0; index < NUMBER_OF_PULSES; index++)
    {
        LED_BUZZER_PIN_Toggle();
        __delay_us(DURATION_OF_A_PULSE);
    }
}

static inline void METRONOME_runCompletelyCounterclockwise(void)
{
    RUN_COUNTERCLOCKWISE();
    
    TIMER0_PRESCALER(); 
    TMR0_Reload(HALF_OF_MAX_STEPS_NUMBER);
    
    NCO_ENABLE();
    
    TIMER_runOnePeriod();
    
    NCO_DISABLE();
}

static inline void METRONOME_runInStartPosition(void)
{
    TIMER_START_FROM_ZERO();
    TIMER0_NO_PRESCALER();
    TMR0_Reload(STEPS_TO_INITIAL_POSITION);
    
    RUN_CLOCKWISE();
    
    NCO_ENABLE();
    
    TIMER_runOnePeriod();

    NCO_DISABLE();
}

static inline void METRONOME_prepareForOscillating(void)
{
    MODE_METRONOME();
    
    TIMER_START_FROM_ZERO();
    TIMER0_NO_PRESCALER();
    
    TMR0_Reload(STEPS_IN_DIAL);
}

static void TIMER_runOnePeriod(void)
{
    TMR0_StartTimer();
    while(!(TMR0_HasOverflowOccured()))
    {
        ;
    }
    TMR0_StopTimer();
    PIR0bits.TMR0IF = 0;
}