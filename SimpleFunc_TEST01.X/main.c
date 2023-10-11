//=============================================================================
//
//=============================================================================
#include "usr_system.h"
#include "xc.h"
//#include <libpic30.h> 
//=============================================================================
//
//=============================================================================


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
#pragma config FSRSSEL =    PRIORITY_7
#pragma config FVBUSONIO =  ON
#pragma config USERID =     0xffff
#pragma config FUSBIDIO =   ON




//=============================================================================
// define
//=============================================================================



//=============================================================================
// variable
//=============================================================================


//=============================================================================
// prototype
//=============================================================================

//==============================================================================
// Waite time = num x 10ms
//==============================================================================
void Wait(uint16_t num)
{
     uint16_t i ;

     for (i=0 ; i < num ; i++) {
          //__delay_ms(10) ;
         asm("NOP");
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
    
    
    UART_STSEL  = 0;    // STOP bit 1
    UART_PDSEL  = 0;    // 8-bit data, no parity
    UART_BRGH   = 1;
    
    UART_BRG    = usrBaundRate_BRG;
    
    UART_RXPORT = 1;
    
    UART_UTXEN  = 1;
    UART_URXEN  = 1;
    UART_ON     = 1;
    
     Wait(0xffff);
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
//
//=============================================================================
int main( void )
{
    int ch;
    
    /* Wait for PLL to be locked */
    while(OSCCONbits.SLOCK == 0U)
                 {
                      /* Nothing to do */
                 }
    
    
    //-----------------------------------------
    // PORT
    //-----------------------------------------
    // T1/T2 buton
    TRISB = 0;
    TRISBbits.TRISB4 = 1;       // T1 入力に設定
    TRISBbits.TRISB0 = 1;       // T2 入力に設定
    
    // LD1/LD2
    TRISD = 0;
    PORTDbits.RD4 = 1;          // LD1　ON
    PORTDbits.RD1 = 1;          // LD2　ON
    
    //-----------------------------------------
    // UART
    //-----------------------------------------
    usrUART_Init();
    putstring("********************\r\n");
    putstring("***  USRT START  ***\r\n");
    putstring("********************\r\n");

    //-----------------------------------------
    // INTERRUPT
    //-----------------------------------------
    //INTCONbits.MVEC = 1;        // マルチベクタモード
    
	while(1){
        ch = getch();
        if( ch != 0 ){
            putch(ch);
        }
	}
    
    
	return 0;

}

