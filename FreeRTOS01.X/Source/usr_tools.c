
#include <xc.h>	

#include <stdio.h>
#include <stdarg.h>
#include "usr_system.h"


void putch(unsigned char c);

void putstring(uint8_t *string);

const char ConvC[]= { '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f' };




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
void putstring(uint8_t *string)
{
    while(*string != '\0'){
        putch(*string);
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
//=============================================================================
//  UART init
//=============================================================================
void usrUART_Init(void)
{
const uint32_t usrBaundRate_BRG = ( (usrPERIPHERAL_CLOCK_HZ / usrBAUNRATE ) / 4 ) - 1;




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
    UART_RXIE   = 0;
    UART_TXIE   = 0;

    
    
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
    int         intvalue;
    char        *charvalue;
    char        ch;
    uint16_t    uintvalue;
    long    uint32value;
    double      floatvalue;

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
                        ch = va_arg(ap, char);
                        //printf("intvaluee=%d\r\n",intvalue);
                        buffer = my_putchar(ch, buffer );
                        break;
                    case  'd':
                        intvalue = va_arg(ap, int);
                        //printf("intvaluee=%d\r\n",intvalue);
                        buffer = my_putint(intvalue, buffer);
                        break;
                    case  'f':
                        floatvalue = va_arg(ap, double);
                        buffer = my_putfloat(floatvalue, 2, buffer );
                        break;
                    case  's':
                        charvalue = va_arg(ap, char*);
                        buffer = my_puts(charvalue, buffer );
                        break;
                    case  'x':
                        uintvalue = (uint16_t)va_arg(ap, int);
                        //printf("uintvalue=%x\r\n",uintvalue);
                        buffer = my_putshex(uintvalue, 0, buffer );
                        break;
                    case  'p':
                        uint32value = (long)va_arg(ap, long);
                        //uintvalue = (uint16_t)(uint32value >> 16);
                        //debu_uint2a('@',uintvalue);
                        //uintvalue = (uint16_t)uint32value;
                        //debu_uint2a('*',uintvalue);
                        buffer = my_putshex32((long)uint32value,  buffer );
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

        putstring(Malloc_buf);
        va_end(ap);
        
        //vPortFree(Malloc_buf);
    }
    vPortFree(Malloc_buf);
}

#define USR_PUT_CHAR(x)             \
{                                   \
        while (!UART_TRMT);         \
        UART_TXREG = (x);            \
}


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

