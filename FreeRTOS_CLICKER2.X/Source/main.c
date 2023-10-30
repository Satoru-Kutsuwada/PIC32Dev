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
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"


/* Standard demo includes. */
//#include "partest.h"

/* Hardware specific includes. */
#include "ConfigPerformance.h"
#include "usr_system.h"

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
#define USR_MSG_QUEUE_LENGTH                4
#define USR_RS485_QUEUE_LENGTH              10
        

//=============================================================================
// variable
//=============================================================================
QueueHandle_t       usrMsgQueue;
QueueHandle_t       usrRs485Queue;

SemaphoreHandle_t   usrMessage_sem;

//=============================================================================
// external variable
//=============================================================================
extern  uint8_t         usrT01Message_buf[];
extern  uint8_t         usrT02Message_buf[];
extern  USR_RTC_DATA    usrSRTC;
extern  uint16_t        usrRTCflg;
extern  USR_UARTx_BUF   usrUartxRx;
extern  USR_UARTx_BUF   usrUartx485Rx;

//=============================================================================
// Prototype
//=============================================================================
static void prvSetupHardware( void );

void usrUART_Init(void);
void usrUART485_Init(void);
void putstring(UART_KIND flg, uint8_t *string);

void Xprintf(const char *string, ...);
// void usrMessage_send(char *text,uint8_t *buffer);
void usrMessage_send(uint8_t *msgbuffer, const char *string, ...);

void usrInitTimer2(void);
void Init_Timer(void);
int getch_buf(USR_UARTx_BUF *buf);
int getch485(void);
void rs485_com_task(void);
       
void vTask001(void *pvParameters);
void vTask002(void *pvParameters);
void vTask003(void *pvParameters);
    

//=============================================================================
//
//=============================================================================

void wait(uint32_t time)
{
    uint32_t i;

    for( i=0; i<time; i++ ){

    }

}
     
//=============================================================================
//  main
//=============================================================================
int main( void )
{
    BaseType_t  Status;
    
    uint32_t    my_RCON;
    
    my_RCON = RCON;
    
    TRISEbits.TRISE3  = 0;   // LED2
    TRISAbits.TRISA10 = 0;   // LED2
    
    TRISEbits.TRISE4 = 1;   // Button 1
    TRISGbits.TRISG9 = 1;   // Button 2
    
    
 
    
    //-----------------------------------------
    // Prepare the hardware to run this demo. 
    //-----------------------------------------
	prvSetupHardware();

    //-----------------------------------------
    // UART
    //-----------------------------------------
    usrUART_Init();
    usrUART485_Init();
    
    putstring(UART_FOR_DEBUG,"********************\r\n");
    putstring(UART_FOR_DEBUG,"***  UART START  ***\r\n");
    putstring(UART_FOR_DEBUG,"********************\r\n\r\n");

    putstring(UART_FOR_485,"@@@@@@@@@@@@@@@@@@@@\r\n");
    putstring(UART_FOR_485,"@@@  UART START  @@@\r\n");
    putstring(UART_FOR_485,"@@@@@@@@@@@@@@@@@@@@\r\n\r\n");
    
    Xprintf("RCON = 0x%p\r\n",my_RCON);
    usrInitTimer2();
    
    //-----------------------------------------
    // xSemaphoreCreateBinary
    //-----------------------------------------
    usrMessage_sem = xSemaphoreCreateBinary();

    Xprintf("usrMessage_sem=0x%p\r\n",usrMessage_sem);
    if(usrMessage_sem != NULL){
        Status = xSemaphoreGive(usrMessage_sem);
        Xprintf("xSemaphoreGive()=%d\r\n",Status);
    }

    //-----------------------------------------
    // xQueueCreate
    //-----------------------------------------
    usrMsgQueue = xQueueCreate(USR_MSG_QUEUE_LENGTH, sizeof(void *));  
    Xprintf("usrMsgQueue=0x%p\r\n",usrMsgQueue);

    usrRs485Queue = xQueueCreate(USR_RS485_QUEUE_LENGTH, sizeof(void *));  
    Xprintf("usrRs485Queue=0x%p\r\n",usrRs485Queue);

    
    //-----------------------------------------
    // xTaskCreate
    //  #define configMINIMAL_STACK_SIZE				( 190 )
    //-----------------------------------------
    Status = xTaskCreate(vTask001, "U01", 190 + 10, NULL, 2, NULL);
    Xprintf("xTaskCreate(Task01)=%d\r\n",Status);
    Status = xTaskCreate(vTask002, "U02", 190 + 10, NULL, 2, NULL);
    Xprintf("xTaskCreate(Task02)=%d\r\n",Status);
    Status = xTaskCreate(vTask003, "U03", 190 + 10, NULL, 3, NULL);
    Xprintf("xTaskCreate(Task03)=%d\r\n",Status);

    //-----------------------------------------
    // vTaskStartScheduler
    //-----------------------------------------
    Xprintf("vTaskStartScheduler()\r\n");
    vTaskStartScheduler();
    
    while(1){
        
    }
    
    vTask001(0);
    vTask002(0);
    vTask003(0);

	return 0;
}
/*-----------------------------------------------------------*/

static void prvSetupHardware( void )
{
	/* Configure the hardware for maximum performance. */
	vHardwareConfigurePerformance();

	/* Setup to use the external interrupt controller. */
	vHardwareUseMultiVectoredInterrupts();

	portDISABLE_INTERRUPTS();

}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* vApplicationMallocFailedHook() will only be called if
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	function that will get called if a call to pvPortMalloc() fails.
	pvPortMalloc() is called internally by the kernel whenever a task, queue,
	timer or semaphore is created.  It is also called by various parts of the
	demo application.  If heap_1.c or heap_2.c are used, then the size of the
	heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	to query the size of free heap space that remains (although it does not
	provide information on how the remaining heap might be fragmented). */
	taskDISABLE_INTERRUPTS();
    Xprintf("Error: MallocFailed()\r\n");
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	task.  It is essential that code added to this hook function never attempts
	to block in any way (for example, call xQueueReceive() with a block time
	specified, or call vTaskDelay()).  If the application makes use of the
	vTaskDelete() API function (as this demo application does) then it is also
	important that vApplicationIdleHook() is permitted to return to its calling
	function, because it is the responsibility of the idle task to clean up
	memory allocated by the kernel to any task that has since been deleted. */
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time task stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook	function is
	called if a task stack overflow is detected.  Note the system/interrupt
	stack is not checked. */
	taskDISABLE_INTERRUPTS();
    Xprintf("Error: StackOverflow()\r\n");
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This function will be called by each tick interrupt if
	configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
	added here, but the tick hook is called from an interrupt context, so
	code must not attempt to block, and only the interrupt safe FreeRTOS API
	functions can be used (those that end in FromISR()). */
}
/*-----------------------------------------------------------*/

void _general_exception_handler( unsigned long ulCause, unsigned long ulStatus )
{
	/* This overrides the definition provided by the kernel.  Other exceptions
	should be handled here. */
    Xprintf("Error: general_exception()\r\n");

	for( ;; );
}

/*-----------------------------------------------------------*/

void vAssertCalled( const char * pcFile, unsigned long ulLine )
{
volatile unsigned long ul = 0;

	( void ) pcFile;
	( void ) ulLine;

	__asm volatile( "di" );
	{
        Xprintf("Error: vAssertCalled(%s, %d)\r\n",pcFile,ulLine);
		/* Set ul to a non-zero value using the debugger to step out of this
		function. */
		while( ul == 0 )
		{
			portNOP();
		}
	}
	__asm volatile( "ei" );
}
