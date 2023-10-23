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
QueueHandle_t usrMsgQueue;
SemaphoreHandle_t usrMessage_sem;

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
  
//=============================================================================
//  vTask001
//=============================================================================
void vTask001(void *pvParameters) 
{
    uint8_t buf[2];
    buf[1] = '\0';
    
    Xprintf("vTask001()\r\n");
    vTaskDelay(100);
    while(1) {
        buf[0] = (uint8_t)getch_buf(&usrUartxRx);
        if(buf[0] != 0 ){
            usrMessage_send(usrT01Message_buf, buf);
        }

        if( usrRTCflg == 1 ){
            usrRTCflg = 0;
            usrMessage_send(usrT01Message_buf, "%d:%d:%d %d.%d\r\n", usrSRTC.hour, usrSRTC.min, usrSRTC.sec, usrSRTC.msec, usrSRTC.usec);
        }
    }
}
    
//=============================================================================
//  vTask002
//=============================================================================
void vTask002(void *pvParameters)
{
    uint8_t buf[2];
    buf[1] = '\0';
    
    Xprintf("vTask002()\r\n");
    vTaskDelay(100);
    while(1) {
        buf[0] = (uint8_t)getch_buf(&usrUartx485Rx);
//        buf[0] = (uint8_t)getch485();
        if(buf[0] != 0 ){
            putstring(UART_FOR_485,buf);
        }
         
         
        //usrMessage_send( usrT02Message_buf,"TEST2=%d\r\n",12345 );
       vTaskDelay(200);
    }
}
       
//=============================================================================
//  vTask003 UART for debug message
//=============================================================================
void vTask003(void *pvParameters)
{
    PRINT_MSG_FORM  *pm_msg;
    uint8_t			msgQueBuf[sizeof(void *)];
    char            *print_mess;
    char            temp[]="%p,%p\r\n";
    UBaseType_t uxNumberOfItems;
    
    Xprintf("vTask003()\r\n");
    vTaskDelay(100);
    while(1) {
                    
        if(xQueueReceive(usrMsgQueue, msgQueBuf, portMAX_DELAY) == pdPASS ) {
            //uxNumberOfItems = uxQueueMessagesWaiting(xQueue);
            //Xprintf("uxNumberOfItems=%d\r\n",uxNumberOfItems);
            //if( uxNumberOfItems > 0 ){
                pm_msg = (PRINT_MSG_FORM *)msgQueBuf;
                print_mess = (char *)pm_msg->malloc_pt;

                Xprintf(print_mess);
            //}
            //else if( usrRTCflg == 1 ){
            //    usrRTCflg = 0;
            //    //Xprintf("%d:%d:%d %d.%d\r\n", usrSRTC.hour, usrSRTC.min, usrSRTC.sec, usrSRTC.msec, usrSRTC.usec);
           // }
        }
        else{
            Xprintf("Error vTask003\r\n\0");
        }
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
    usrUART485_Init();
    
    putstring(UART_FOR_DEBUG,"********************\r\n");
    putstring(UART_FOR_DEBUG,"***  USRT START  ***\r\n");
    putstring(UART_FOR_DEBUG,"********************\r\n\r\n");

    putstring(UART_FOR_485,"@@@@@@@@@@@@@@@@@@@@\r\n");
    putstring(UART_FOR_485,"@@@  USRT START  @@@\r\n");
    putstring(UART_FOR_485,"@@@@@@@@@@@@@@@@@@@@\r\n\r\n");

    
    Init_Timer();
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
    usrMsgQueue = xQueueCreate(QUEUE_LENGTH, sizeof(void *));  
    Xprintf("usrMsgQueue=0x%p\r\n",usrMsgQueue);

    
    //-----------------------------------------
    // xTaskCreate
    //-----------------------------------------
    Status = xTaskCreate(vTask001, "U01", configMINIMAL_STACK_SIZE + 10, NULL, 1, NULL);
    Xprintf("xTaskCreate(Task01)=%d\r\n",Status);
    Status = xTaskCreate(vTask002, "U02", configMINIMAL_STACK_SIZE + 10, NULL, 2, NULL);
    Xprintf("xTaskCreate(Task02)=%d\r\n",Status);
    Status = xTaskCreate(vTask003, "U03", configMINIMAL_STACK_SIZE + 10, NULL, 3, NULL);
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
