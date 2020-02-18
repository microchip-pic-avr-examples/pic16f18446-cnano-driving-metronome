<div id="readme" class="Box-body readme blob js-code-block-container">
  <article class="markdown-body entry-content p-3 p-md-6" itemprop="text"><p><a href="https://www.microchip.com" rel="nofollow"><img src="https://camo.githubusercontent.com/5fb5505f69a28ff407841612dfe2b7004f210594/68747470733a2f2f636c6475702e636f6d2f553071684c7742696a462e706e67" alt="MCHP" data-canonical-src="https://cldup.com/U0qhLwBijF.png" style="max-width:100%;"></a></p>

## Driving a metronome using a PIC Microcontroller

#### Hardware components:
* PIC16F18446 Curiosity Nano
* Switec Stepper motor
* Potentiometer
* LED
* Buzzer

#### Software requirements:
* MPLABX IDE v5.30
* XC8 C compiler v2.10
* MPLAB Code Configurator (MCC) v3.95.0
* PIC16 Library v1.77.0

This repository contains the source code for a metronome application. It was developed using the PIC16F18446 microcontroller, along with a Switec Stepper motor, a potentiometer, a LED and a buzzer.

The implementation of the application consists of a circuit composed of Core Independent Peripherals (CIPs), which is capable to create the signals that drive the Switec Stepper motor as a metronome. It also adjust the number of beats per minute of the metronome by reading an input value, provided by the user.

Due to the usage of CIPs, the driving of the motor is done independently form software, so the computation complexity and program memory space used are substantially reduced.

The source code for initialization of peripherals used in the microcontroller is generated using the MPLAB Code Configurator (MCC).

Relevant devices: PIC16F18424, PIC16F18425, PIC16F18426, PIC16F18444, PIC16F18445, PIC16F18446, PIC16F18455, PIC16F18456.  
