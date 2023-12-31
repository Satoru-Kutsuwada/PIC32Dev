/* 
 * File:   usr_system.h
 * Author: nosak
 *
 * Created on 2023/10/16, 12:51
 */

#ifndef USR_SYSTEM_H
#define	USR_SYSTEM_H

#ifdef	__cplusplus
extern "C" {
#endif

//=============================================================================
//
//=============================================================================

#include "xc.h"

    
    
//=============================================================================
//
//=============================================================================
typedef struct{
    void *malloc_pt;
}PRINT_MSG_FORM;

//=============================================================================
//
//=============================================================================
typedef struct {
    uint16_t     year;
    uint8_t     wday;
    uint8_t     month;
    uint8_t     day;
    uint8_t     hour;
    uint8_t     min;
    uint8_t     sec;
    uint16_t    msec;
    uint16_t    usec;    
} USR_RTC_DATA;
//=============================================================================
// System Define
//=============================================================================
#define usrCPU_CLOCK_HZ						( 80000000UL )
#define usrPERIPHERAL_CLOCK_HZ				( 40000000UL )
#define usrTIM1_SRC_CLOCK_HZ				( 32768UL )
#define usrBAUNRATE         				( 115200UL )
    

//=============================================================================
// UART Define
//=============================================================================
#define     USRTx_RX_BUF    128
#define     USR_UARTx_OK                0
#define     USR_UARTx_ERR_OVERRUN       1
        
typedef struct{
    uint8_t     buf[USRTx_RX_BUF];
    int         wpt;
    int         rpt;
    uint16_t    status;    
} USR_UARTx_BUF;

//=============================================================================
// UART Define
//=============================================================================
typedef enum{
    UART_FOR_DEBUG,
    UART_FOR_485
}UART_KIND;



#define UART1_AVALABLE
//#define UART2_AVALABLE
//#define UART3_AVALABLE
//#define UART5_AVALABLE
//#define UART6_AVALABLE

//#define UART4851_AVALABLE
//#define UART4852_AVALABLE
#define UART4853_AVALABLE
//#define UART4855_AVALABLE
//#define UART4856_AVALABLE



//-----------------------------------------------------
#ifdef UART1_AVALABLE
#define	UART_MODE	U1MODE
#define	UART_ON     U1MODEbits.ON
#define	UART_CLKSEL	U1MODEbits.CLKSEL
#define	UART_BRGH	U1MODEbits.BRGH
#define	UART_PDSEL	U1MODEbits.PDSEL
#define	UART_STSEL	U1MODEbits.STSEL
#define	UART_RTSMD	U1MODEbits.RTSMD
		
#define	UART_STA	U1STA
#define	UART_UTXEN	U1STAbits.UTXEN
#define	UART_URXEN	U1STAbits.URXEN
#define	UART_UTXBF	U1STAbits.UTXBF
#define	UART_TRMT	U1STAbits.TRMT
#define	UART_PERR	U1STAbits.PERR
#define	UART_FERR	U1STAbits.FERR
#define	UART_OERR	U1STAbits.OERR
#define	UART_URXDA	U1STAbits.URXDA
		
#define	UART_TXREG	U1TXREG
#define	UART_RXREG	U1RXREG
#define	UART_BRG	U1BRG

// PORT
#define	UART_RXPORT	TRISDbits.TRISD2
    
		
//	Flag	
#define	UART_EIF    IFS0bits.U1EIF
#define	UART_RXIF   IFS0bits.U1RXIF
#define	UART_TXIF   IFS0bits.U1TXIF
		
//	Enable	
#define	UART_EIE	IEC0bits.U1EIE
#define	UART_RXIE	IEC0bits.U1RXIE
#define	UART_TXIE	IEC0bits.U1TXIE

// Priority
#define	UART_IP     IPC6bits.U1IP
#define	UART_IS     IPC6bits.U1IS

// VECTOR
#define UART_VECTOR 24
    
#endif
    
//-----------------------------------------------------
#ifdef UART2_AVALABLE
#define	UART_MODE	U2MODE
#define	UART_ON     U2MODEbits.ON
#define	UART_CLKSEL	U2MODEbits.CLKSEL
#define	UART_BRGH	U2MODEbits.BRGH
#define	UART_PDSEL	U2MODEbits.PDSEL
#define	UART_STSEL	U2MODEbits.STSEL
#define	UART_RTSMD	U2MODEbits.RTSMD

#define	UART_STA	U2STA
#define	UART_UTXEN	U2STAbits.UTXEN
#define	UART_URXEN	U2STAbits.URXEN
#define	UART_UTXBF	U2STAbits.UTXBF
#define	UART_TRMT	U2STAbits.TRMT
#define	UART_PERR	U2STAbits.PERR
#define	UART_FERR	U2STAbits.FERR
#define	UART_OERR	U2STAbits.OERR
#define	UART_URXDA	U2STAbits.URXDA
		
#define	UART_TXREG	U2TXREG
#define	UART_RXREG	U2RXREG
#define	UART_BRG	U2BRG

// PORT
#define	UART_RXPORT	TRISFbits.TRISF5
    
		
//	Flag	
#define	UART_EIF    IFS1bits.U2EIF
#define	UART_RXIF   IFS1bits.U2RXIF
#define	UART_TXIF   IFS1bits.U2TXIF
		
//	Enable	
#define	UART_EIE	IEC1bits.U2EIE
#define	UART_RXIE	IEC1bits.U2RXIE
#define	UART_TXIE	IEC1bits.U2TXIE

// Priority
#define	UART_IP     IPC8bits.U2IP
#define	UART_IS     IPC8bits.U2IS

// VECTOR
#define	UART_VECTOR     _UART_2_VECTOR 

#endif
        
//-----------------------------------------------------
#ifdef UART3_AVALABLE
#define	UART_MODE	U3MODE
#define	UART_ON     U3MODEbits.ON
#define	UART_CLKSEL	U3MODEbits.CLKSEL
#define	UART_BRGH	U3MODEbits.BRGH
#define	UART_PDSEL	U3MODEbits.PDSEL
#define	UART_STSEL	U3MODEbits.STSEL
#define	UART_RTSMD	U3MODEbits.RTSMD
		
#define	UART_STA	U3STA
#define	UART_UTXEN	U3STAbits.UTXEN
#define	UART_URXEN	U3STAbits.URXEN
#define	UART_UTXBF	U3STAbits.UTXBF
#define	UART_TRMT	U3STAbits.TRMT
#define	UART_PERR	U3STAbits.PERR
#define	UART_FERR	U3STAbits.FERR
#define	UART_OERR	U3STAbits.OERR
#define	UART_URXDA	U3STAbits.URXDA
		
#define	UART_TXREG	U3TXREG
#define	UART_RXREG	U3RXREG
#define	UART_BRG	U3BRG

// PORT
#define	UART_RXPORT	TRISGbits.TRISG7
    
		
//	Flag	
#define	UART_EIF    IFS1bits.U3EIF
#define	UART_RXIF   IFS1bits.U3RXIF
#define	UART_TXIF   IFS1bits.U3TXIF
		
//	Enable	
#define	UART_EIE	IEC1bits.U3EIE
#define	UART_RXIE	IEC1bits.U3RXIE
#define	UART_TXIE	IEC1bits.U3TXIE

// Priority
#define	UART_IP     IPC7bits.U3IP
#define	UART_IS     IPC7bits.U3IS

// VECTOR


#endif
        
//-----------------------------------------------------
#ifdef UART4_AVALABLE

    
#endif
        
//-----------------------------------------------------
#ifdef UART5_AVALABLE
#define	UART_MODE	U5MODE
#define	UART_ON     U5MODEbits.ON
#define	UART_CLKSEL	U5MODEbits.CLKSEL
#define	UART_BRGH	U5MODEbits.BRGH
#define	UART_PDSEL	U5MODEbits.PDSEL
#define	UART_STSEL	U5MODEbits.STSEL
#define	UART_RTSMD	U5MODEbits.RTSMD
		
#define	UART_STA	U5STA
#define	UART_UTXEN	U5STAbits.UTXEN
#define	UART_URXEN	U5STAbits.URXEN
#define	UART_UTXBF	U5STAbits.UTXBF
#define	UART_TRMT	U5STAbits.TRMT
#define	UART_PERR	U5STAbits.PERR
#define	UART_FERR	U5STAbits.FERR
#define	UART_OERR	U5STAbits.OERR
#define	UART_URXDA	U5STAbits.URXDA
		
#define	UART_TXREG	U5TXREG
#define	UART_RXREG	U5RXREG
#define	UART_BRG	U5BRG

// PORT
#define	UART_RXPORT	TRISBbits.TRISB8
    
//	Flag	
#define	UART_EIF    IFS2bits.U5EIF
#define	UART_RXIF   IFS2bits.U5RXIF
#define	UART_TXIF   IFS2bits.U5TXIF
		
//	Enable	
#define	UART_EIE	IEC2bits.U5EIE
#define	UART_RXIE	IEC2bits.U5RXIE
#define	UART_TXIE	IEC2bits.U5TXIE

// Priority
#define	UART_IP     IPC12bits.U5IP
#define	UART_IS     IPC12bits.U5IS


// VECTOR
  
    
#endif
        
//-----------------------------------------------------
#ifdef UART6_AVALABLE
#define	UART_MODE	U6MODE
#define	UART_ON     U6MODEbits.ON
#define	UART_CLKSEL	U6MODEbits.CLKSEL
#define	UART_BRGH	U6MODEbits.BRGH
#define	UART_PDSEL	U6MODEbits.PDSEL
#define	UART_STSEL	U6MODEbits.STSEL
#define	UART_RTSMD	U6MODEbits.RTSMD
		
#define	UART_STA	U6STA
#define	UART_UTXEN	U6STAbits.UTXEN
#define	UART_URXEN	U6STAbits.URXEN
#define	UART_UTXBF	U6STAbits.UTXBF
#define	UART_TRMT	U6STAbits.TRMT
#define	UART_PERR	U6STAbits.PERR
#define	UART_FERR	U6STAbits.FERR
#define	UART_OERR	U6STAbits.OERR
#define	UART_URXDA	U6STAbits.URXDA
		
#define	UART_TXREG	U6TXREG
#define	UART_RXREG	U6RXREG
#define	UART_BRG	U6BRG

// PORT
#define	UART_RXPORT	TRISGbits.TRISG9
    
		
//	Flag	
#define	UART_EIF    IFS2bits.U6EIF
#define	UART_RXIF   IFS2bits.U6RXIF
#define	UART_TXIF   IFS2bits.U6TXIF
		
//	Enable	
#define	UART_EIE	IEC2bits.U6EIE
#define	UART_RXIE	IEC2bits.U6RXIE
#define	UART_TXIE	IEC2bits.U6TXIE

// Priority
#define	UART_IP     IPC12bits.U6IP
#define	UART_IS     IPC12bits.U6IS

// VECTOR

#endif
        
     
//=============================================================================
// UART485 Define
//=============================================================================


//-----------------------------------------------------
#ifdef UART4851_AVALABLE
#define	UART485_MODE	U1MODE
#define	UART485_ON     U1MODEbits.ON
#define	UART485_CLKSEL	U1MODEbits.CLKSEL
#define	UART485_BRGH	U1MODEbits.BRGH
#define	UART485_PDSEL	U1MODEbits.PDSEL
#define	UART485_STSEL	U1MODEbits.STSEL
#define	UART485_RTSMD	U1MODEbits.RTSMD
		
#define	UART485_STA	U1STA
#define	UART485_UTXEN	U1STAbits.UTXEN
#define	UART485_URXEN	U1STAbits.URXEN
#define	UART485_UTXBF	U1STAbits.UTXBF
#define	UART485_TRMT	U1STAbits.TRMT
#define	UART485_PERR	U1STAbits.PERR
#define	UART485_FERR	U1STAbits.FERR
#define	UART485_OERR	U1STAbits.OERR
#define	UART485_URXDA	U1STAbits.URXDA
		
#define	UART485_TXREG	U1TXREG
#define	UART485_RXREG	U1RXREG
#define	UART485_BRG	U1BRG

// PORT
#define	UART485_RXPORT	TRISDbits.TRISD2
#define UART485_CTRL    LATBbits.LATB1;    
    
		
//	Flag	
#define	UART485_EIF    IFS0bits.U1EIF
#define	UART485_RXIF   IFS0bits.U1RXIF
#define	UART485_TXIF   IFS0bits.U1TXIF
		
//	Enable	
#define	UART485_EIE	IEC0bits.U1EIE
#define	UART485_RXIE	IEC0bits.U1RXIE
#define	UART485_TXIE	IEC0bits.U1TXIE

// Priority
#define	UART485_IP     IPC6bits.U1IP
#define	UART485_IS     IPC6bits.U1IS

// VECTOR
#define UART485_VECTOR 24
    
#endif
    
//-----------------------------------------------------
#ifdef UART4852_AVALABLE
#define	UART485_MODE	U2MODE
#define	UART485_ON     U2MODEbits.ON
#define	UART485_CLKSEL	U2MODEbits.CLKSEL
#define	UART485_BRGH	U2MODEbits.BRGH
#define	UART485_PDSEL	U2MODEbits.PDSEL
#define	UART485_STSEL	U2MODEbits.STSEL
#define	UART485_RTSMD	U2MODEbits.RTSMD

#define	UART485_STA	U2STA
#define	UART485_UTXEN	U2STAbits.UTXEN
#define	UART485_URXEN	U2STAbits.URXEN
#define	UART485_UTXBF	U2STAbits.UTXBF
#define	UART485_TRMT	U2STAbits.TRMT
#define	UART485_PERR	U2STAbits.PERR
#define	UART485_FERR	U2STAbits.FERR
#define	UART485_OERR	U2STAbits.OERR
#define	UART485_URXDA	U2STAbits.URXDA
		
#define	UART485_TXREG	U2TXREG
#define	UART485_RXREG	U2RXREG
#define	UART485_BRG	U2BRG

// PORT
#define	UART485_RXPORT	TRISFbits.TRISF5
#define UART485_CTRL    LATBbits.LATB1;    

    
		
//	Flag	
#define	UART485_EIF    IFS1bits.U2EIF
#define	UART485_RXIF   IFS1bits.U2RXIF
#define	UART485_TXIF   IFS1bits.U2TXIF
		
//	Enable	
#define	UART485_EIE	IEC1bits.U2EIE
#define	UART485_RXIE	IEC1bits.U2RXIE
#define	UART485_TXIE	IEC1bits.U2TXIE

// Priority
#define	UART485_IP     IPC8bits.U2IP
#define	UART485_IS     IPC8bits.U2IS

// VECTOR
#define	UART485_VECTOR     _UART485_2_VECTOR 

#endif
        
//-----------------------------------------------------
#ifdef UART4853_AVALABLE
#define	UART485_MODE	U3MODE
#define	UART485_ON     U3MODEbits.ON
#define	UART485_CLKSEL	U3MODEbits.CLKSEL
#define	UART485_BRGH	U3MODEbits.BRGH
#define	UART485_PDSEL	U3MODEbits.PDSEL
#define	UART485_STSEL	U3MODEbits.STSEL
#define	UART485_RTSMD	U3MODEbits.RTSMD
		
#define	UART485_STA	U3STA
#define	UART485_UTXEN	U3STAbits.UTXEN
#define	UART485_URXEN	U3STAbits.URXEN
#define	UART485_UTXBF	U3STAbits.UTXBF
#define	UART485_TRMT	U3STAbits.TRMT
#define	UART485_PERR	U3STAbits.PERR
#define	UART485_FERR	U3STAbits.FERR
#define	UART485_OERR	U3STAbits.OERR
#define	UART485_URXDA	U3STAbits.URXDA
		
#define	UART485_TXREG	U3TXREG
#define	UART485_RXREG	U3RXREG
#define	UART485_BRG	U3BRG

// PORT
#define	UART485_RXPORT	TRISGbits.TRISG7
#define UART485_CTRL    LATBbits.LATB1;    
    
		
//	Flag	
#define	UART485_EIF    IFS1bits.U3EIF
#define	UART485_RXIF   IFS1bits.U3RXIF
#define	UART485_TXIF   IFS1bits.U3TXIF
		
//	Enable	
#define	UART485_EIE	IEC1bits.U3EIE
#define	UART485_RXIE	IEC1bits.U3RXIE
#define	UART485_TXIE	IEC1bits.U3TXIE

// Priority
#define	UART485_IP     IPC7bits.U3IP
#define	UART485_IS     IPC7bits.U3IS

// VECTOR


#endif
        
//-----------------------------------------------------
#ifdef UART4854_AVALABLE

    
#endif
        
//-----------------------------------------------------
#ifdef UART4855_AVALABLE
#define	UART485_MODE	U5MODE
#define	UART485_ON     U5MODEbits.ON
#define	UART485_CLKSEL	U5MODEbits.CLKSEL
#define	UART485_BRGH	U5MODEbits.BRGH
#define	UART485_PDSEL	U5MODEbits.PDSEL
#define	UART485_STSEL	U5MODEbits.STSEL
#define	UART485_RTSMD	U5MODEbits.RTSMD
		
#define	UART485_STA	U5STA
#define	UART485_UTXEN	U5STAbits.UTXEN
#define	UART485_URXEN	U5STAbits.URXEN
#define	UART485_UTXBF	U5STAbits.UTXBF
#define	UART485_TRMT	U5STAbits.TRMT
#define	UART485_PERR	U5STAbits.PERR
#define	UART485_FERR	U5STAbits.FERR
#define	UART485_OERR	U5STAbits.OERR
#define	UART485_URXDA	U5STAbits.URXDA
		
#define	UART485_TXREG	U5TXREG
#define	UART485_RXREG	U5RXREG
#define	UART485_BRG	U5BRG

// PORT
#define	UART485_RXPORT	TRISBbits.TRISB8
#define UART485_CTRL    LATBbits.LATB1;    
    
//	Flag	
#define	UART485_EIF    IFS2bits.U5EIF
#define	UART485_RXIF   IFS2bits.U5RXIF
#define	UART485_TXIF   IFS2bits.U5TXIF
		
//	Enable	
#define	UART485_EIE	IEC2bits.U5EIE
#define	UART485_RXIE	IEC2bits.U5RXIE
#define	UART485_TXIE	IEC2bits.U5TXIE

// Priority
#define	UART485_IP     IPC12bits.U5IP
#define	UART485_IS     IPC12bits.U5IS


// VECTOR
  
    
#endif
        
//-----------------------------------------------------
#ifdef UART4856_AVALABLE
#define	UART485_MODE	U6MODE
#define	UART485_ON     U6MODEbits.ON
#define	UART485_CLKSEL	U6MODEbits.CLKSEL
#define	UART485_BRGH	U6MODEbits.BRGH
#define	UART485_PDSEL	U6MODEbits.PDSEL
#define	UART485_STSEL	U6MODEbits.STSEL
#define	UART485_RTSMD	U6MODEbits.RTSMD
		
#define	UART485_STA	U6STA
#define	UART485_UTXEN	U6STAbits.UTXEN
#define	UART485_URXEN	U6STAbits.URXEN
#define	UART485_UTXBF	U6STAbits.UTXBF
#define	UART485_TRMT	U6STAbits.TRMT
#define	UART485_PERR	U6STAbits.PERR
#define	UART485_FERR	U6STAbits.FERR
#define	UART485_OERR	U6STAbits.OERR
#define	UART485_URXDA	U6STAbits.URXDA
		
#define	UART485_TXREG	U6TXREG
#define	UART485_RXREG	U6RXREG
#define	UART485_BRG	U6BRG

// PORT
#define	UART485_RXPORT	TRISGbits.TRISG9
#define UART485_CTRL    LATBbits.LATB1;    
    
		
//	Flag	
#define	UART485_EIF    IFS2bits.U6EIF
#define	UART485_RXIF   IFS2bits.U6RXIF
#define	UART485_TXIF   IFS2bits.U6TXIF
		
//	Enable	
#define	UART485_EIE	IEC2bits.U6EIE
#define	UART485_RXIE	IEC2bits.U6RXIE
#define	UART485_TXIE	IEC2bits.U6TXIE

// Priority
#define	UART485_IP     IPC12bits.U6IP
#define	UART485_IS     IPC12bits.U6IS

// VECTOR

#endif





#ifdef	__cplusplus
}
#endif

#endif	/* USR_SYSTEM_H */

