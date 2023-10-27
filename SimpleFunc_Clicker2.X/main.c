/*
 * FreeRTOS V202212.01
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/******************************************************************************
 * This project provides two demo applications.  A simple blinky style project,
 * and a more comprehensive test and demo application.  The
 * mainCREATE_SIMPLE_BLINKY_DEMO_ONLY setting (defined in this file) is used to
 * select between the two.  The simply blinky demo is implemented and described
 * in main_blinky.c.  The more comprehensive test and demo application is
 * implemented and described in main_full.c.
 *
 * This file implements the code that is not demo specific, including the
 * hardware setup and FreeRTOS hook functions.
 */

//=============================================================================
// include
//=============================================================================
#include "xc.h"


#ifdef ___NOP
/* Core configuratin fuse settings */
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_2
#pragma config CP = OFF, BWP = OFF, PWP = OFF
#endif


/*** DEVCFG0 ***/
#pragma config DEBUG =      OFF
#pragma config ICESEL =     ICS_PGx2
#pragma config PWP =        OFF
#pragma config BWP =        OFF
#pragma config CP =         OFF


/*** DEVCFG1 ***/
//#pragma config FNOSC =      PRIPLL
#pragma config FNOSC =      0b001
#pragma config FPBDIV =     DIV_2
#pragma config FSOSCEN =    ON
#pragma config IESO =       OFF
#pragma config POSCMOD =    HS
#pragma config OSCIOFNC =   OFF
#pragma config FCKSM =      CSDCMD
#pragma config WDTPS =      PS1048576
#pragma config FWDTEN =     OFF


/*** DEVCFG2 ***/
#pragma config FPLLIDIV =   DIV_2
#pragma config FPLLMUL =    MUL_20
#pragma config FPLLODIV =   DIV_1
#pragma config UPLLEN =     ON
#pragma config UPLLIDIV =   DIV_2

/*** DEVCFG3 ***/
//#pragma config FSRSSEL =    PRIORITY_7
//#pragma config FVBUSONIO =  ON
#pragma config USERID =     0xffff
//#pragma config FUSBIDIO =   ON


//=============================================================================
// define
//=============================================================================

//=============================================================================
// variable
//=============================================================================

//=============================================================================
// external variable
//=============================================================================


//=============================================================================
// Prototype
//=============================================================================

//=============================================================================
//  main
//=============================================================================
int main( void )
{

    TRISEbits.TRISE3  = 0;   // LED2
    TRISAbits.TRISA10 = 0;   // LED2
    
    TRISEbits.TRISE4 = 1;   // Button 1
    TRISGbits.TRISG9 = 1;   // Button 2
  
    //-----------------------------------------
    // INTERRUPT
    //-----------------------------------------
    INTCONbits.MVEC   = 1;
    asm volatile("ei");
    
    while(1){
        PORTEbits.RE3 =1;
        PORTAbits.RA10 =1;
    }
    


	return 0;
}
/*-----------------------------------------------------------*/

