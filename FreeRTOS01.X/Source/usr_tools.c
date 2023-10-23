//=============================================================================
// include
//=============================================================================
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "usr_system.h"
//#include <xc.h>	
#include <stdio.h>
#include <stdarg.h>


//=============================================================================
// define
//=============================================================================





//=============================================================================
// variable
//=============================================================================
const char ConvC[]= { '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f' };

#define     MESG_BUF_MAX    30
uint8_t     usrT01Message_buf[MESG_BUF_MAX];
uint8_t     usrT02Message_buf[MESG_BUF_MAX];


USR_UARTx_BUF    usrUartxRx;
USR_UARTx_BUF    usrUartx485Rx;


//=============================================================================
// external variable
//=============================================================================
extern      QueueHandle_t usrMsgQueue;
extern      SemaphoreHandle_t usrMessage_sem;


//=============================================================================
// Prototype
//=============================================================================
void putch(unsigned char c);
void putstring(UART_KIND flg, uint8_t *string);


//=============================================================================
//  UART Data Tx
//=============================================================================
void putch485(uint8_t c)
{
    while (!UART485_TRMT); // 送信バッファが空になるまで待機
    UART485_TXREG = c; // データを送信
}

//=============================================================================
//  UART Data Tx
//=============================================================================
void putch(uint8_t c)
{
    while (!UART_TRMT); // 送信バッファが空になるまで待機
    UART_TXREG = c; // データを送信
}

//=============================================================================
//  UART string data Tx
//=============================================================================
void putstring(UART_KIND flg, uint8_t *string)
{
    while(*string != '\0'){
        switch(flg){
        case UART_FOR_DEBUG:
            putch(*string);
            break;
        case UART_FOR_485:
            putch485(*string);
            break;
        }
        string++;
    }
}
//==============================================================================
//
//==============================================================================
int getch(void)
{
    if(!UART_URXDA){
        //putstring("data non\r\n");
        return (char)0;
        
    }
    else{
        //putstring("data rcv\r\n");
        
        return (int) UART_RXREG; // 受信データを返す
    }        
}
int getch485(void)
{
    if(!UART485_URXDA){
        //putstring("data non\r\n");
        return (char)0;
        
    }
    else{
        //putstring("data rcv\r\n");
        
        return (int) UART485_RXREG; // 受信データを返す
    }        
}

//==============================================================================
//
//==============================================================================
int getch_buf(USR_UARTx_BUF *buf)
{
    int rxdata = 0;
    
    if(buf->wpt != buf->rpt){
        rxdata = (int)buf->buf[buf->rpt];
    
        buf->rpt ++;
        if(buf->rpt > USRTx_RX_BUF ){
            buf->rpt = 0;
        }
    }
    return (int) rxdata; // 受信データを返す
}

//=============================================================================
// UART RX interrupt 
//=============================================================================
#define _UART_1_VECTOR                           24

#pragma vector ISR_UartRx 24
#pragma interrupt ISR_UartRx IPL7AUTO
void ISR_UartRx(void) 
{
    UART_RXIF = 0;

    while( UART_URXDA ){
        usrUartxRx.buf[usrUartxRx.wpt] = UART_RXREG;
        usrUartxRx.wpt ++;
        if(usrUartxRx.wpt > USRTx_RX_BUF ){
            usrUartxRx.wpt = 0;
        }
        
        if(usrUartxRx.rpt == usrUartxRx.wpt){
            usrUartxRx.status = USR_UARTx_ERR_OVERRUN;
        }
    }
}
 
//=============================================================================
// UART485 RX interrupt 
//=============================================================================
#define _UART_3_VECTOR                           31

#pragma vector ISR_Uart485Rx 31
#pragma interrupt ISR_Uart485Rx IPL7AUTO
void ISR_Uart485Rx(void) 
{
    UART485_RXIF = 0;

    while( UART485_URXDA ){
        usrUartx485Rx.buf[usrUartx485Rx.wpt] = UART485_RXREG;
        usrUartx485Rx.wpt ++;
        if(usrUartx485Rx.wpt > USRTx_RX_BUF ){
            usrUartx485Rx.wpt = 0;
        }
        
        if(usrUartx485Rx.rpt == usrUartx485Rx.wpt){
            usrUartx485Rx.status = USR_UARTx_ERR_OVERRUN;
        }
    }
}
//=============================================================================
//  UART init
//=============================================================================
void usrUART_Init(void)
{
const uint32_t usrBaundRate_BRG = ( (usrPERIPHERAL_CLOCK_HZ / usrBAUNRATE ) / 4 ) - 1;


    usrUartxRx.rpt = 0;
    usrUartxRx.wpt = 0;
    usrUartxRx.status = USR_UARTx_OK;

    UART_MODE   = 0;
    UART_STA    = 0;
    
    // MODE REG
    UART_STSEL  = 0;    // STOP bit 1
    UART_PDSEL  = 0;    // 8-bit data, no parity
    UART_BRGH   = 1;
    UART_RTSMD  = 1;
    
    // Baund Rate
    UART_BRG    = usrBaundRate_BRG;
    
    // RxPORT INPUT
    UART_RXPORT = 1;
    
    // UART START
    UART_UTXEN  = 1;
    UART_URXEN  = 1;
    UART_ON     = 1;
   
    // INTERRUPT
    //	Flag	
    UART_EIF    = 0;
    UART_RXIF   = 0;
    UART_TXIF   = 0;

    // Priority
    UART_IP     = 7;
    UART_IS     = 0;
    	
    //	Enable	
    UART_EIE    = 0;
    UART_RXIE   = 1;
    UART_TXIE   = 0;

    
    
}
//=============================================================================
//  UART init
//=============================================================================
void usrUART485_Init(void)
{
const uint32_t usrBaundRate_BRG = ( (usrPERIPHERAL_CLOCK_HZ / usrBAUNRATE ) / 4 ) - 1;


    usrUartx485Rx.rpt = 0;
    usrUartx485Rx.wpt = 0;
    usrUartx485Rx.status = USR_UARTx_OK;

    UART485_MODE   = 0;
    UART485_STA    = 0;
    
    // MODE REG
    UART485_STSEL  = 0;    // STOP bit 1
    UART485_PDSEL  = 0;    // 8-bit data, no parity
    UART485_BRGH   = 1;
    UART485_RTSMD  = 1;
    
    // Baund Rate
    UART485_BRG    = usrBaundRate_BRG;
    
    // RxPORT INPUT
    UART485_RXPORT = 1;
    
    // UART485 START
    UART485_UTXEN  = 1;
    UART485_URXEN  = 1;
    UART485_ON     = 1;
   
    // INTERRUPT
    //	Flag	
    UART485_EIF    = 0;
    UART485_RXIF   = 0;
    UART485_TXIF   = 0;

    // Priority
    UART485_IP     = 7;
    UART485_IS     = 0;
    	
    //	Enable	
    UART485_EIE    = 0;
    UART485_RXIE   = 1;
    UART485_TXIE   = 0;

    
    
}
//==============================================================================
//
//==============================================================================

uint8_t *my_putint(int num, uint8_t *buf)
{
    int temp;
    int keta;
    

	if (num < 0) {
        *buf = '-';
        buf++;
        num = -num;
    }
    temp = num;
    keta = 1;
    

    while (num / 10 != 0) {
        num = num / 10;
        keta *= 10;
    }
    num = temp;

    for( ; keta>0; keta/=10 ){
        num = num / keta;
        *buf = '0' + num;
        buf++;
        *buf = '\0';
        num = temp - (keta * num);
        temp = num;
    }
            
    return buf;
}
//==============================================================================
//
//==============================================================================

uint8_t *my_putfloat(double num, int precision, uint8_t *buf)
{
	int dt;
	double fracPart,dtf;
	int intPart;
	int digit;
    int count;

	intPart = (int)num;
    buf = my_putint(intPart, buf);
    *buf = '.';
    buf ++;

    fracPart = num - intPart;

    if (fracPart < 0) {
        fracPart = -fracPart;
    }

    count = 0;
    while (count < precision) {
        fracPart *= 10;
        digit = (int)fracPart;

        *buf = '0' + digit;
        buf ++;

        fracPart -= digit;
        count++;
    }

    *buf = '\0';

    return buf;

}
//=============================================================================
//
//
//=============================================================================

uint8_t *my_putchar(char c, uint8_t *buf )
{
	//SKprintf("_putchar c=%x, buf=%p\r\n",c,buf);
	*buf = c;
	buf ++;
	return buf ;
}

//=============================================================================
//
//
//=============================================================================
uint8_t *my_puts(char* str, uint8_t *buf )
{
	uint8_t *buf2;

	buf2=buf;

	//SKprintf("_puts str=%s, buf=%p\r\n",str,buf);
    while ( *str != '\0' ) {
        buf = my_putchar(*str, buf);
        str++;
    }
    *buf='\0';
	//SKprintf("_puts str=%s  %p\r\n",buf2, buf);
	return buf ;
}



//=============================================================================
//
//
//=============================================================================


uint8_t *my_putshex(uint16_t dt, uint8_t flg, uint8_t *buf )
{
	uint8_t	sw;

	switch(flg){
	case 4:
		*buf = ConvC[( dt >> 12 ) & 0x0f ];
		buf ++;
		*buf = ConvC[( dt >> 8 ) & 0x0f ];
		buf ++;
		*buf = ConvC[( dt >> 4 ) & 0x0f ];
		buf ++;
		*buf = ConvC[ dt  & 0x0f ];
		buf ++;
		break;

	case 2:
		*buf = ConvC[( dt >> 4 ) & 0x0f ];
		buf ++;
		*buf = ConvC[ dt  & 0x0f ];
		buf ++;
		break;
	case 0:
		sw = 0;
		if(( sw == 1) || (( dt >> 12 ) & 0x0f ) != 0 ){
			*buf = ConvC[( dt >> 12 ) & 0x0f ];
			buf ++;
			sw = 1;
		}
		if(( sw == 1) || (( dt >> 8 ) & 0x0f ) != 0 ){
			*buf = ConvC[( dt >> 8 ) & 0x0f ];
			buf ++;
			sw = 1;
		}
		if(( sw == 1) || (( dt >> 4 ) & 0x0f ) != 0 ){
			*buf = ConvC[( dt >> 4 ) & 0x0f ];
			buf ++;
			sw = 1;
		}

		*buf = ConvC[ dt & 0x0f ];
		buf ++;
       *buf = '\0';

		break;
	}
	return buf ;
}
//=============================================================================
//
//
//=============================================================================

//char	loginfo_buf[64];


uint8_t *my_putshex32(long dt, uint8_t *buf )
{
	uint8_t	sw;
    uint8_t	i;
    
    sw = 0;
    
    for( i=28; i > 0; i-=4){
        if(( sw == 1) || (( dt >> i ) & 0x0f ) != 0 ){
            *buf = ConvC[( dt >> i ) & 0x0f ];
            buf ++;
            sw = 1;
        }
    }
    *buf = ConvC[ dt & 0x0f ];
    buf ++;
    *buf = '\0';
    
    
	return buf ;
}
void debu_uint2a(uint8_t ch,uint16_t dt)
{
    uint8_t	i;
    
    putch(ch);
    for( i=12; i > 0; i-=4){
        putch(ConvC[( dt >> i ) & 0x0f ]);
    }
    putch(ConvC[( dt >> i ) & 0x0f ]);
    putch('\r');
    putch('\n');
    
}

#define     XPRINT_BUF_SIZE     128
// uint8_t printbuf[128];
//=============================================================================
//
//
//=============================================================================
void Xprintf(const char *string, ...)
{
	va_list     ap;
	uint8_t        *buffer,*Malloc_buf;

    //int         intvalue;
    //char        *charvalue;
    //char        ch;
    //uint16_t    uintvalue;
    //long    uint32value;
    //double      floatvalue;

    Malloc_buf = ( uint8_t * ) pvPortMalloc( sizeof( uint8_t )*XPRINT_BUF_SIZE );
    
    //Malloc_buf = ( uint8_t * ) printbuf;
    //Malloc_buf = ( char * ) pvPortMalloc( 64 );
    buffer = Malloc_buf;
    if(Malloc_buf != NULL){ 
        va_start(ap, string);

        while (*string != '\0') {
            if (*string == '%') {
                string++; // Move past '%'
                switch (*string ){
                    case  'c':
                        // ch = va_arg(ap, char);
                        buffer = my_putchar((char)va_arg(ap, char), buffer );
                        break;
                    case  'd':
                        //intvalue = va_arg(ap, int);
                        //printf("intvaluee=%d\r\n",intvalue);
                        buffer = my_putint((int)va_arg(ap, int), buffer);
                        break;
                    case  'f':
                        //floatvalue = va_arg(ap, double);
                        buffer = my_putfloat((double)va_arg(ap, double), 2, buffer );
                        break;
                    case  's':
                        //charvalue = va_arg(ap, char*);
                        buffer = my_puts((char *)va_arg(ap, char*), buffer );
                        break;
                    case  'x':
                        //uintvalue = (uint16_t)va_arg(ap, int);
                        //printf("uintvalue=%x\r\n",uintvalue);
                        buffer = my_putshex((uint16_t)va_arg(ap, int), 0, buffer );
                        break;
                    case  'p':
                        //uint32value = (long)va_arg(ap, long);
                        //uintvalue = (uint16_t)(uint32value >> 16);
                        //debu_uint2a('@',uintvalue);
                        //uintvalue = (uint16_t)uint32value;
                        //debu_uint2a('*',uintvalue);
                        buffer = my_putshex32((long)va_arg(ap, long),  buffer );
                        break;
                    default:
                        buffer = my_putchar('%', buffer );
                        buffer = my_putchar(*string, buffer );
                        break;
                }
            }
            else {
                buffer = my_putchar(*string, buffer );
            }
            string++;
        }

        *buffer = '\0';

        putstring(UART_FOR_DEBUG,Malloc_buf);
        va_end(ap);
        
        //vPortFree(Malloc_buf);
    }
    vPortFree(Malloc_buf);
}
//=============================================================================
//
//=============================================================================

#define USR_PUT_CHAR(x)             \
{                                   \
        while (!UART_TRMT);         \
        UART_TXREG = (x);            \
}

//=============================================================================
//
//=============================================================================

void Yprintf( uint8_t *string, uint32_t dt )
{
    uint16_t    i;
    
    while (*string != '\0') {
        if (*string == '%') {
            string++; // Move past '%'
            switch (*string ){
                case  'x':
                    for(i=28;  i>0; i-=4){
                        USR_PUT_CHAR(ConvC[( dt >> i ) & 0x0f ]);
                    }
                    USR_PUT_CHAR(ConvC[( dt & 0x0f) ]);
                    break;
                default:
                    USR_PUT_CHAR('%');
                    USR_PUT_CHAR(*string);
                    break;
            }
        }
        else {
            USR_PUT_CHAR(*string);
        }
        string++;
    }
}

//=============================================================================
//
//=============================================================================
#ifdef ___NOP
void usrMessage_send(char *text,uint8_t *buffer)
{
    uint8_t i;
    PRINT_MSG_FORM pm_msg;
    BaseType_t  Status;
    
   if( xSemaphoreTake( usrMessage_sem, portMAX_DELAY  ) == pdTRUE ){
    
        for( i=0; i<MESG_BUF_MAX; i++ ){
            if( text[i] != '\0' ){
                buffer[i] = text[i];
            }
            else{
                buffer[i] = text[i];
                break;
            }
        }
        buffer[i] = '\0';


        pm_msg.malloc_pt = (void *)buffer;

        Status = xQueueSend(xQueue, (void *)&pm_msg, 0);
        if( Status  != pdPASS ){
            Xprintf( "QSEND ERROR :Statust=%d\r\n", Status);
        }
    
        xSemaphoreGive( usrMessage_sem );
    
   }
}
#endif


void usrMessage_send(uint8_t *msgbuffer, const char *string, ...)
{
    va_list         ap;
    uint8_t         *buffer;
    PRINT_MSG_FORM  pm_msg;
    BaseType_t      Status;
    
   if( xSemaphoreTake( usrMessage_sem, portMAX_DELAY  ) == pdTRUE ){
 
        buffer = ( uint8_t * ) msgbuffer;

        va_start(ap, string);

        while (*string != '\0') {
            if (*string == '%') {
                string++; // Move past '%'
                switch (*string ){
                    case  'c':
                        // ch = va_arg(ap, char);
                        buffer = my_putchar((char)va_arg(ap, char), buffer );
                        break;
                    case  'd':
                        //intvalue = va_arg(ap, int);
                        //printf("intvaluee=%d\r\n",intvalue);
                        buffer = my_putint((int)va_arg(ap, int), buffer);
                        break;
                    case  'f':
                        //floatvalue = va_arg(ap, double);
                        buffer = my_putfloat((double)va_arg(ap, double), 2, buffer );
                        break;
                    case  's':
                        //charvalue = va_arg(ap, char*);
                        buffer = my_puts((char *)va_arg(ap, char*), buffer );
                        break;
                    case  'x':
                        //uintvalue = (uint16_t)va_arg(ap, int);
                        //printf("uintvalue=%x\r\n",uintvalue);
                        buffer = my_putshex((uint16_t)va_arg(ap, int), 0, buffer );
                        break;
                    case  'p':
                        //uint32value = (long)va_arg(ap, long);
                        //uintvalue = (uint16_t)(uint32value >> 16);
                        //debu_uint2a('@',uintvalue);
                        //uintvalue = (uint16_t)uint32value;
                        //debu_uint2a('*',uintvalue);
                        buffer = my_putshex32((long)va_arg(ap, long),  buffer );
                        break;
                    default:
                        buffer = my_putchar('%', buffer );
                        buffer = my_putchar(*string, buffer );
                        break;
                }
            }
            else {
                buffer = my_putchar(*string, buffer );
            }
            string++;
        }

        *buffer = '\0';

        va_end(ap);


        pm_msg.malloc_pt = (void *)msgbuffer;

        Status = xQueueSend(usrMsgQueue, (void *)&pm_msg, 0);
        if( Status  != pdPASS ){
            Xprintf( "QSEND ERROR :Statust=%d\r\n", Status);
        }
         xSemaphoreGive( usrMessage_sem );
   }      
}