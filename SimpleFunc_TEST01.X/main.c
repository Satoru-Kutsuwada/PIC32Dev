
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
//  include
//=============================================================================
#include "usr_system.h"
#include "xc.h"

//=============================================================================
// define
//=============================================================================



//=============================================================================
// variable
//=============================================================================
extern uint16_t    timer1_cnt;



#define    USR_RX_BUF_MAX  64
#define    USR_TX_BUF_MAX  32
#define    USR_TX_BUF_NUM  4


#define    USR_RX_DATA      0x8000
#define    USR_RX_ERROR     0x0001


typedef struct {
    uint16_t    wptr;
    uint16_t    rptr;
    uint16_t    status;
    uint8_t     buf[USR_RX_BUF_MAX];
}USR_UART_BUF;

//USR_UART_BUF usrTx;
USR_UART_BUF usrRx;

typedef enum{
    TX_BUF_AVAILABLE=0,
    TX_BUF_NOT_AVAILABLE,
    TX_BUF_REQUEST
            
}TX_BUF_STATUS;

typedef struct {
    TX_BUF_STATUS    status;
    uint16_t    num;
    uint16_t    ptr;
    uint8_t     buf[USR_RX_BUF_MAX];
}USR_UART_TX_BUF;

USR_UART_TX_BUF usrTx;



//=============================================================================
// prototype
//=============================================================================
    void usrInitTimer1(void);

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

    usrRx.rptr = 0;
    usrRx.wptr = 0;
    usrRx.status = 0;

    usrTx.num = 0;
    usrTx.ptr = 0;
    usrTx.status = 0;






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

void putstringISR(uint8_t *string)
{
    uint8_t lst_data = 0;
    
    while(usrTx.status != TX_BUF_AVAILABLE);
    
    usrTx.num = 0;
    usrTx.ptr = 0;
    while(*string != '\0'){
        if( lst_data == 0 ){
            lst_data = *string;
        }
        else{
            usrTx.buf[usrTx.num] = *string; 
            usrTx.num ++;
            string++;
        }
    }
    usrTx.status = TX_BUF_REQUEST;
    putch(lst_data);
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
int getReciveData(void)
{
    int ch = 0;
    
    if(usrRx.rptr != usrRx.wptr){
        ch = usrRx.buf[usrRx.rptr];
        usrRx.rptr ++;
        
        if( usrRx.rptr > USR_RX_BUF_MAX ){
            usrRx.rptr = 0;
        }
    }
    return ch;
}
//=============================================================================
//
//=============================================================================
int main( void )
{
    int ch;
    uint16_t    temp;
    
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

    //-----------------------------------------
    // TIMER1
    //-----------------------------------------
    usrInitTimer1();

    // INTERRUPT
    INTCONbits.MVEC   = 1;
    asm volatile("ei");
    

    putstring("********************\r\n");
    putstring("***  USRT START  ***\r\n");
    putstring("********************\r\n\r\n");
    //putstringISR("@@@@@@@@@@@@@@@@@@@@\r\n");
    //putstringISR("@@@  USRT START  @@@\r\n");
    //putstringISR("@@@@@@@@@@@@@@@@@@@@\r\n");

  
    putstring("MAIN LOOP\r\n");


	while(1){
        ch = getch();
        if( ch != 0 ){
            putch(ch);
        }
        
        if( temp != timer1_cnt ){
            temp = timer1_cnt;
            putstring("timer1_cnt count up\r\n");
        }
        
        
        
	}
    
    
	return 0;

}


//=============================================================================
//    UARTReceiveInterrupt
//=============================================================================
#pragma vector UARTInterrupt 24
#pragma interrupt UARTInterrupt IPL7AUTO
void UARTInterrupt(void)
{
    uint16_t    i;
    uint16_t    dtnum;
    
    // UART ERROR
    if( UART_EIF ){
        UART_EIF = 0;
    }

    // UART RX
    if( UART_RXIF ){
        UART_RXIF = 0;

#ifdef ___NOP
        
        if( UART_URXDA ){
            usrRx.buf[usrRx.wptr] = UART_RXREG;
            usrRx.status |= USR_RX_DATA;
            usrRx.wptr ++;
            if( usrRx.wptr > USR_RX_BUF_MAX ){
                usrRx.wptr = 0;
            }
            
            if( usrRx.wptr == usrRx.rptr ){
                usrRx.status |= USR_RX_ERROR;
            }
            
        }
#endif
    }

    // UART TX
    if( UART_TXIF ){
        UART_TXIF = 0;
        
#ifdef ___NOP
        if(usrTx.status == TX_BUF_REQUEST){
            for(i=usrTx.ptr; i<usrTx.num;i++){
                if( UART_UTXBF ){
                    break;
                }
                else{
                    UART_TXREG = usrTx.buf[i];
                    usrTx.ptr ++;
        
                }
        
            }
        }
        if(usrTx.ptr == usrTx.num){
            usrTx.status = TX_BUF_AVAILABLE;
        }
#endif
    }    
}

