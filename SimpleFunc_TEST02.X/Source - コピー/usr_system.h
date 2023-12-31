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
#define UART1_AVALABLE
//#define UART2_AVALABLE
//#define UART3_AVALABLE
//#define UART5_AVALABLE
//#define UART6_AVALABLE

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
        
        
//ppppppppppppppppppppppppppppppp


#define TIMER_AV_NUM	3

/* Public typedef ------------------------------------------------------------*/
typedef struct{
	uint32_t	dt;
	uint32_t	dt_buf[TIMER_AV_NUM];
	uint32_t	dt_max;
	uint32_t	dt_av;
	uint8_t		av_wcnt;
	uint8_t		start;

	uint16_t	usec;
	uint16_t	msec;
	uint16_t	usec_max;
	uint16_t	msec_max;
} TIMER_TIC;

typedef struct{
	uint16_t	usec;
	uint16_t	msec;
	uint16_t	sec;
	uint16_t	min;
	uint16_t	hour;
}TIMER_DATA;



/* Public typedef ------------------------------------------------------------*/
typedef struct{
	uint8_t		*pxTopOfStack;
	uint8_t		*pxStack;
	uint16_t	size;
} STACK_INFO;



/* Public typedef ------------------------------------------------------------*/
typedef enum {
	RET_FALSE = 0,
	RET_TRUE

}RETURN_STATUS;



/* Public define -------------------------------------------------------------*/
#define PRiNTF_BUFFMAX 50


typedef enum{
	LF_NON_STOP = 0,
	LF_IMMMEDIATE_STOP,
	LF_MAX_DATA_STOP,

	LF_MAX
} LOG_FLAG;

typedef enum{
	SK_TASK_main = 0,
	SK_TASK_sub1,
	SK_TASK_sub2,

	SK_TASK_MAX
} SK_TASK;

typedef enum{
	SK_UART1_RS485 = 0,
	SK_UART2_DEBUG,

	SK_UART_MAX
} SK_UART;

/* Public define -------------------------------------------------------------*/
typedef enum {
	RS485_AD_MASTER = 0,
	RS485_AD_SLEVE01,
	RS485_AD_SLEVE02,


	RS485_AD_MAX
}RA485_ADDRESS;

#define MY_RS485_ADDRESS RS485_AD_MASTER


typedef enum {
	RS485_CMD_STATUS = 1,
	RS485_CMD_VERSION,
	RS485_CMD_MESUR,
	RS485_CMD_MESUR_DATA,

	RS485_CMD_MAX
}RA485_COMMAND;


typedef enum{
	RT_EVENT_START_REQ = 0,
	RT_EVENT_UART_RX,
	RT_EVENT_RESPONS,
	RT_EVENT_STOP_REQ,
	RT_EVENT_TIMEOUT,

	RT_EVENT_MAX
} RS485_TASK_EVENT;
typedef enum{
	RT_STATE_INIT = 0,
	RT_STATE_READY,
	RT_STATE_RESPONS_RECIVE,
	RT_STATE_RESPONS,

	RT_STATE_MAX
} RS485_TASK_STATE;

typedef struct{
	RS485_TASK_EVENT	event;
	RS485_TASK_STATE	state;

	RA485_COMMAND		command;
	uint16_t			command_sub;
	RA485_ADDRESS		address;
	uint8_t				sub1;
	uint8_t				timer_id;
	uint8_t				retry_num;

} CMD_MSG;


typedef union{
	CMD_MSG				cmd_msg;
}MESSAGE_CMD_DETAIL;

typedef struct{
	void				*maroc_ptr;
	SK_TASK				send_task;

	MESSAGE_CMD_DETAIL	u;
}MESSAGE_QUE_DATA;

typedef struct{
	void				*maroc_ptr;
	SK_TASK				send_task;

//	osMessageQueueId_t 	hmsg;
	uint16_t			time;
	void				*mail_form;
	uint8_t				timer_id;
}TIMER_EVENT_FORM;


/* Private variables ---------------------------------------------------------*/
#define  	RCV_BUF_SIZE 	128

typedef struct{

	uint8_t	buf[10];
	uint8_t	ptr;

} ESC_SEQ;


typedef struct{
	uint8_t		rcv_dt[2];
	uint8_t		rcvbuf[RCV_BUF_SIZE];
	//uint16_t		rcvnum;
	uint16_t		totalnum;
	uint16_t		rcv_wpt;
	uint16_t		rcv_rpt;
	//uint16_t		Sem_rs485_rcv;
	uint16_t		Set_cnt;
	uint16_t		Get_cnt;


} UART_BUF;

/* Public macro --------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/



typedef struct{

	// RTC_TimeTypeDef -----------------------------------------------------
	uint8_t Hours;
	uint8_t Minutes;
	uint8_t Seconds;
	uint8_t usec;
	uint16_t msec;


	// TIMER_TIC ------------------------------------------------------------
	//uint32_t	dt;
	//uint32_t	dt_av;

	// LOG ------------------------------------------------------------------
	char	string[PRiNTF_BUFFMAX] ;

} LOG_RECODE;

#define LOG_RECODE_MAX	100



typedef struct{
	uint16_t 	wptr;
	uint16_t 	rptr;
	uint16_t 	num;
	LOG_FLAG		flg;

	LOG_RECODE	rec[LOG_RECODE_MAX];
} LOG_DATA;



/* Public variables ----------------------------------------------------------*/

typedef enum{
    RASING_MODE_SINGLE,
    RASING_MODE_SINGLE_HA,
    RASING_MODE_SINGLE_HS,
    RASING_MODE_SINGLE_LR,
    RASING_MODE_CONTINUE,

    RASING_MODE_MAX
}RASING_MODE;




//ppppppppppppppppppppppppppppppp


#ifdef	__cplusplus
}
#endif

#endif	/* USR_SYSTEM_H */

