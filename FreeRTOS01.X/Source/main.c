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


/* Core configuratin fuse settings */
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_2
#pragma config CP = OFF, BWP = OFF, PWP = OFF


//=============================================================================
// define
//=============================================================================
#define QUEUE_LENGTH 4

//=============================================================================
// variable
//=============================================================================
QueueHandle_t xQueue;
SemaphoreHandle_t Usrt_semaphore;

//=============================================================================
// external variable
//=============================================================================


//=============================================================================
// Prototype
//=============================================================================
static void prvSetupHardware( void );

void usrUART_Init(void);
void putstring(uint8_t *string);
void Xprintf(const char *string, ...);


//=============================================================================
//  vTask001
//=============================================================================
void vTask001(void *pvParameters) 
{
    Xprintf("vTask001()\r\n");
    vTaskDelay(100);
    while(1) {
        vTaskDelay(250);
    }
}
    
//=============================================================================
//  vTask002
//=============================================================================
void vTask002(void *pvParameters)
{
    Xprintf("vTask002()\r\n");
    vTaskDelay(100);
    while(1) {
        vTaskDelay(250);
    }
}
       
//=============================================================================
//  vTask003
//=============================================================================
void vTask003(void *pvParameters)
{
    Xprintf("vTask003()\r\n");
    vTaskDelay(100);
    while(1) {
        vTaskDelay(250);
    }
}

//=============================================================================
//  main
//=============================================================================
int main( void )
{
    BaseType_t  Status;
    
    //-----------------------------------------
    // Prepare the hardware to run this demo. 
    //-----------------------------------------
	prvSetupHardware();

    //-----------------------------------------
    // UART
    //-----------------------------------------
    usrUART_Init();
    putstring("********************\r\n");
    putstring("***  USRT START  ***\r\n");
    putstring("********************\r\n\r\n");

    //-----------------------------------------
    // xSemaphoreCreateBinary
    //-----------------------------------------
    Usrt_semaphore = xSemaphoreCreateBinary();

    Xprintf("Usrt_semaphore=0x%p\r\n",Usrt_semaphore);
    if(Usrt_semaphore != NULL){
        Status = xSemaphoreGive(Usrt_semaphore);
        Xprintf("xSemaphoreGive()=%d\r\n",Status);
    }

    //-----------------------------------------
    // xQueueCreate
    //-----------------------------------------
    xQueue = xQueueCreate(QUEUE_LENGTH, sizeof(void *));  
    Xprintf("xQueue=0x%p\r\n",xQueue);

    
    //-----------------------------------------
    // xTaskCreate
    //-----------------------------------------
    Status = xTaskCreate(vTask001, "U01", configMINIMAL_STACK_SIZE + 10, NULL, 3, NULL);
    Xprintf("xTaskCreate(Task01)=%d\r\n",Status);
    Status = xTaskCreate(vTask002, "U02", configMINIMAL_STACK_SIZE + 10, NULL, 2, NULL);
    Xprintf("xTaskCreate(Task02)=%d\r\n",Status);
    Status = xTaskCreate(vTask003, "U03", configMINIMAL_STACK_SIZE + 10, NULL, 1, NULL);
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
