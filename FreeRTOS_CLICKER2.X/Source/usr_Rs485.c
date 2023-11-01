
/*
 * usr_rs485_main.c
 *
 *  Created on: 2023/07/31
 *      Author: nosak
 */

//=============================================================================
// include
//=============================================================================
#include "FreeRTOS.h"
#include "usr_system.h"
//#include <string.h>
#include "queue.h"

//=============================================================================
// Prototype
//=============================================================================
void putch485(uint8_t c);
void usrComDataInit(void);
//=============================================================================
// define
//=============================================================================



/* Private define ------------------------------------------------------------*/
#define RS485_ADD_ID	0x00
#define RS485_CMD_ID	0x03

#define RS485_ADD_BYTE	3
#define RS485_SUM_BYTE	2


#define RS485_COM_01_BYTE	6
#define RS485_COM_02_BYTE	7
#define RS485_COM_03_BYTE	3
#define RS485_COM_04_BYTE	7


/* Private define ------------------------------------------------------------*/

typedef enum {
	RET_FALSE = 0,
	RET_TRUE

}RETURN_STATUS;


//=============================================================================
// variable
//=============================================================================


extern USR_VL53_DATA   usrVL53Ctrl;

uint16_t usrLogSW_RS485 = 1;

#define LOG_PRINT_RS485(...)                                                      \
{                                                                               \
    if(usrLogSW_RS485){                                                           \
        Xprintf(__VA_ARGS__);                                                   \
    }                                                                           \
}

//=============================================================================
// Master - Slave Command Format
//=============================================================================

/* Private variables ---------------------------------------------------------*/
#define TEXT_LENGTH		6
const char com_start_text[]   = "COM-ST\0";
const char message_end_text[] = "MSGEND\0";

/* Private variables ---------------------------------------------------------*/
typedef enum{
	// スタートテキスト
	COM_START_TXT_00 = 0,
	COM_START_TXT_01,
	COM_START_TXT_02,
	COM_START_TXT_03,
	COM_START_TXT_04,
	COM_START_TXT_05,

	// 通信カウンタ
	COM_COUNTER_L,
	COM_COUNTER_H,

	// アドレス
	COM_ADDRESS_ID,
	COM_ADDRESS_DIST,
	COM_ADDRESS_SORC,
	COM_ADDRESS_RESERVD,

	// コマンド・レスポンス
	COM_COMMAND_ID,
	COM_COMMAND,
	COM_COMMAND_00,
	COM_COMMAND_01,
	COM_COMMAND_02,
	COM_COMMAND_03,
	COM_COMMAND_04,
	COM_COMMAND_05,
	COM_COMMAND_06,
	COM_COMMAND_07,
	COM_COMMAND_08,
	COM_COMMAND_09,
	COM_COMMAND_10,
	COM_COMMAND_11,

	//　チェックサム
	COM_CHKSUM_ID,
	COM_CHKSUM,

	// エンドテキスト
	COM_END_TXT_00,
	COM_END_TXT_01,
	COM_END_TXT_02,
	COM_END_TXT_03,
	COM_END_TXT_04,
	COM_END_TXT_05,

	COM_TABLE_MAX

}COM_TABLE;


typedef struct{
uint8_t     buf[COM_TABLE_MAX];
uint16_t    wpt;
} COM_RES_DATA;

COM_RES_DATA usrCommandData;
COM_RES_DATA usrResponsData;




/* Command 01 -------------------------------*/
/* Command 01 RESPONS -----------------------*/
#define COM_ERR_DITAIL 		COM_COMMAND_01
#define COM_SES_KIND 		COM_COMMAND_02

/* Command 02 ---------*/
/* Command 02 RESPONS -----------------------*/
#define COM_SLV_VERSION_L 	COM_COMMAND_01
#define COM_SLV_VERSION_H 	COM_COMMAND_02
#define COM_SNS_VERSION_L 	COM_COMMAND_03
#define COM_SNS_VERSION_H 	COM_COMMAND_04

/* Command 03 ---------*/
#define COM_SENS_CTRL 		COM_COMMAND_01

/* Command 03 RESPONS -----------------------*/

/* Command 04 ---------*/
#define COM_DATA_KIND 		COM_COMMAND_01

/* Command 04 RESPONS -----------------------*/
#define COM_MESUR_DATA_L 	COM_COMMAND_01
#define COM_MESUR_DATA_ML 	COM_COMMAND_02
#define COM_MESUR_DATA_MH 	COM_COMMAND_03
#define COM_MESUR_DATA_H 	COM_COMMAND_04





/* Private function prototypes -----------------------------------------------*/





//=============================================================================
// external variable
//=============================================================================
extern      USR_UARTx_BUF       usrUartx485Rx;
extern      QueueHandle_t       usrRs485Queue;

//=============================================================================
// Prototype
//=============================================================================
int getch_buf(USR_UARTx_BUF *buf);
void Xprintf(const char *string, ...);

void usrComResMemoryDump(uint8_t *string, COM_RES_DATA *data);
//==============================================================================
//
//==============================================================================

typedef enum{
	RT_EVENT_UART_RX = 0,
	RT_EVENT_MEASUR_RES,
	RT_EVENT_UART_TX,
	RT_EVENT_TIMEOUT,

	RT_EVENT_MAX
} RS485_TASK_EVENT;

typedef enum{
	RT_STATE_READY = 0,
	RT_STATE_RECEIVING,
	RT_STATE_RESPONS,

	RT_STATE_MAX
} RS485_TASK_STATE;


typedef enum {
	RS485_AD_MASTER = 0,
	RS485_AD_SLEVE01,
	RS485_AD_SLEVE02,
	RS485_AD_MAX
}RS485_ADDRESS; 
#define RS485_OWN_ADDRESS   RS485_AD_SLEVE01
        
        
typedef enum {
	RS485_CMD_STATUS = 1,
	RS485_CMD_VERSION,
	RS485_CMD_MESUR_START,
	RS485_CMD_MESUR_STOP,
	RS485_CMD_MESUR_DATA,

	RS485_CMD_MAX
}RS485_COMMAND;

typedef enum {
    RS485_DS_INIT,
    RS485_DS_IDLE,
    RS485_DS_MESURING_SINGLE,
    RS485_DS_MESURING_SINGLE_HA,
    RS485_DS_MESURING_SINGLE_HS,
    RS485_DS_MESURING_SINGLE_LR,
    RS485_DS_MESURING_CONTINUE,
    RS485_DS_ERROR,
    RS485_DS_MAX
}RS485_DEVICE_STATUS;

typedef enum {
    RS485_MS_INITIALIZE,
    RS485_MS_MESURING,
    RS485_MS_MESURING_OVER_RENGE,
    RS485_MS_ERROR,
    RS485_MS_MAX
}RS485_MESURING_STATUS;

typedef enum {
    RS485_ERR_NON,
    RS485_ERR_I2C_ERROR,
    RS485_ERR_MAX
}RS485_ERROR_DETAIL;

typedef enum {
    RS485_DSK_VL53OX,
    RS485_DKS_SONIC,
    RS485_DSK_MAX
}RS485_DEVICE_KIND;

#define     USR_COMMAND_DATA_MAX    (COM_COMMAND_11-COM_COMMAND)
typedef struct{
    RS485_TASK_EVENT    event;
    RS485_TASK_STATE    status;
	
    RS485_DEVICE_STATUS device_status;
    RS485_DEVICE_KIND   device_kind;
    RS485_ERROR_DETAIL  error_detail;
    uint8_t             slv_m_ver;
    uint8_t             slv_s_ver;
    uint8_t             sens_m_ver;
    uint8_t             sens_s_ver;
    RASING_MODE         req_mesure_mode;    
    
    RS485_COMMAND		command;
    uint8_t             commandData[USR_COMMAND_DATA_MAX];    
	RS485_ADDRESS		OwnAddress;
	RS485_ADDRESS		FromAddress;
    uint16_t            comCounter;
} CMD_MSG;

CMD_MSG     usrComDataMain;         // UART Tx ISR --> Task

typedef struct{
	void				*maroc_ptr;
    RS485_TASK_EVENT    event;
	CMD_MSG             cm;
}MESSAGE_QUE_DATA;

typedef struct{
	void				*maroc_ptr;
    RS485_TASK_EVENT    event;
}MESSAGE_QUE_DATA_ISR;

MESSAGE_QUE_DATA_ISR   usrMsgQueueUART485Tx;
MESSAGE_QUE_DATA_ISR   usrMsgQueueUART485Rx;
//==============================================================================
//
//==============================================================================



void RS_nop( CMD_MSG	*rt_task );
void RS_UartRxStrt( CMD_MSG	*rt_task );
void RS_UartRxRcv( CMD_MSG	*rt_task );

void RS_UartTxEnd( CMD_MSG	*rt_task );
void RS_RcvTimeout( CMD_MSG	*rt_task );
void RS_ResTimeout( CMD_MSG	*rt_task );

void usrMessage_send(const char *string, ...);

//==============================================================================
//
//==============================================================================
const void (*rs485_func_table[RT_EVENT_MAX][RT_STATE_MAX])( CMD_MSG	*rt_task )={
	//      READY           Receiving        Respons
		{ RS_UartRxStrt,    RS_UartRxRcv,   RS_nop			},      // UART_Rx
		{ RS_nop,           RS_nop,         RS_nop			},      // Measurement_RES
		{ RS_nop,           RS_nop,         RS_UartTxEnd    },      // UART_Tx
		{ RS_nop,           RS_RcvTimeout,  RS_ResTimeout   }     // UART_Tx
};




//==============================================================================
//
//==============================================================================
void usrRS485_Init(void)
{
    int     i;
    
    usrCommandData.wpt = 0;
    usrResponsData.wpt = 0;
    
    usrComDataMain.FromAddress = 0;
    usrComDataMain.OwnAddress = RS485_AD_SLEVE01;
    usrComDataMain.comCounter = 0;
    usrComDataMain.status = RT_STATE_READY;
    usrComDataMain.event = 0;
    usrComDataMain.command = 0;
    
    for( i=0; i< USR_COMMAND_DATA_MAX; i++ ){
        usrComDataMain.commandData[i] = 0;    
    }
    
}


//==============================================================================
//
//==============================================================================
void RS_nop( CMD_MSG	*rt_task )
{
    Xprintf("RS_nop()\r\n");
}

//==============================================================================
//
//==============================================================================
void usrSetResponsData(RS485_COMMAND command )
{
    int         i;
    uint8_t     chksum = 0;
    
    for( i=0; i < COM_TABLE_MAX; i++ ){
        usrResponsData.buf[i] = 0;
    }
    
    usrResponsData.buf[COM_START_TXT_00] = com_start_text[0];
	usrResponsData.buf[COM_START_TXT_01] = com_start_text[1];
	usrResponsData.buf[COM_START_TXT_02] = com_start_text[2];
	usrResponsData.buf[COM_START_TXT_03] = com_start_text[3];
	usrResponsData.buf[COM_START_TXT_04] = com_start_text[4];
	usrResponsData.buf[COM_START_TXT_05] = com_start_text[5];

	// 通信カウンタ
    usrComDataMain.comCounter ++;
	usrResponsData.buf[COM_COUNTER_L] = (uint8_t)(usrComDataMain.comCounter & 0x00ff);
	usrResponsData.buf[COM_COUNTER_H] = (uint8_t)(usrComDataMain.comCounter >> 8);

	// アドレス
	usrResponsData.buf[COM_ADDRESS_ID] = '#';
	usrResponsData.buf[COM_ADDRESS_DIST] = RS485_AD_MASTER;
	usrResponsData.buf[COM_ADDRESS_SORC] = usrComDataMain.OwnAddress;
	
	// コマンド・レスポンス
	usrResponsData.buf[COM_COMMAND_ID] = '*';
    usrResponsData.buf[COM_COMMAND] = usrComDataMain.command;
    
    switch(command){
    case RS485_CMD_STATUS:
        usrResponsData.buf[COM_COMMAND_00] = 0;
        usrResponsData.buf[COM_COMMAND_01] = usrComDataMain.device_status;
        usrResponsData.buf[COM_COMMAND_02] = usrComDataMain.error_detail;
        usrResponsData.buf[COM_COMMAND_03] = usrComDataMain.device_kind;
        break;
        
    case RS485_CMD_VERSION:
        usrResponsData.buf[COM_COMMAND_00] = 0;
        usrResponsData.buf[COM_COMMAND_01] = usrComDataMain.slv_m_ver;
        usrResponsData.buf[COM_COMMAND_02] = usrComDataMain.slv_s_ver;
        usrResponsData.buf[COM_COMMAND_03] = usrComDataMain.sens_m_ver;
        usrResponsData.buf[COM_COMMAND_04] = usrComDataMain.sens_s_ver;
        break;
        
    case RS485_CMD_MESUR_START:
        usrResponsData.buf[COM_COMMAND_00] = 0;
        break;
        
    case RS485_CMD_MESUR_STOP:
        usrResponsData.buf[COM_COMMAND_00] = 0;
        break;
        
    case RS485_CMD_MESUR_DATA:
        usrResponsData.buf[COM_COMMAND_00] = 0;
        usrResponsData.buf[COM_COMMAND_01] = RS485_MS_INITIALIZE;
        usrResponsData.buf[COM_COMMAND_02] = 0;
        usrResponsData.buf[COM_COMMAND_03] = 0;

        switch( usrComDataMain.device_status ){
        case RS485_DS_INIT:
             break;           
        case RS485_DS_IDLE:
             break;           
        case RS485_DS_MESURING_SINGLE:
            if( usrComDataMain.req_mesure_mode == RASING_MODE_SINGLE ){
                if( usrVL53Ctrl.MesurData > 8000 ){
                    usrResponsData.buf[COM_COMMAND_01] = RS485_MS_MESURING_OVER_RENGE;
                    usrResponsData.buf[COM_COMMAND_02] = 0;
                    usrResponsData.buf[COM_COMMAND_03] = 0;               
                }
                else{
                    usrResponsData.buf[COM_COMMAND_01] = RS485_MS_MESURING;
                    usrResponsData.buf[COM_COMMAND_02] = usrVL53Ctrl.MesurData & 0x00ff;
                    usrResponsData.buf[COM_COMMAND_03] = usrVL53Ctrl.MesurData >> 8;
                }
            }
        break;           
        case RS485_DS_MESURING_SINGLE_HA:
            if( usrComDataMain.req_mesure_mode == RASING_MODE_SINGLE_HA ){
                if( usrVL53Ctrl.MesurData > 8000 ){
                    usrResponsData.buf[COM_COMMAND_01] = RS485_MS_MESURING_OVER_RENGE;
                    usrResponsData.buf[COM_COMMAND_02] = 0;
                    usrResponsData.buf[COM_COMMAND_03] = 0;               
                }
                else{
                    usrResponsData.buf[COM_COMMAND_01] = RS485_MS_MESURING;
                    usrResponsData.buf[COM_COMMAND_02] = usrVL53Ctrl.MesurData & 0x00ff;
                    usrResponsData.buf[COM_COMMAND_03] = usrVL53Ctrl.MesurData >> 8;
                }
            }
             break;           
        case RS485_DS_MESURING_SINGLE_HS:
            if( usrComDataMain.req_mesure_mode == RASING_MODE_SINGLE_HS ){
                if( usrVL53Ctrl.MesurData > 8000 ){
                    usrResponsData.buf[COM_COMMAND_01] = RS485_MS_MESURING_OVER_RENGE;
                    usrResponsData.buf[COM_COMMAND_02] = 0;
                    usrResponsData.buf[COM_COMMAND_03] = 0;               
                }
                else{
                    usrResponsData.buf[COM_COMMAND_01] = RS485_MS_MESURING;
                    usrResponsData.buf[COM_COMMAND_02] = usrVL53Ctrl.MesurData & 0x00ff;
                    usrResponsData.buf[COM_COMMAND_03] = usrVL53Ctrl.MesurData >> 8;
                }
            }
             break;           
        case RS485_DS_MESURING_SINGLE_LR:
            if( usrComDataMain.req_mesure_mode == RASING_MODE_SINGLE_LR ){
                if( usrVL53Ctrl.MesurData > 8000 ){
                    usrResponsData.buf[COM_COMMAND_01] = RS485_MS_MESURING_OVER_RENGE;
                    usrResponsData.buf[COM_COMMAND_02] = 0;
                    usrResponsData.buf[COM_COMMAND_03] = 0;               
                }
                else{
                    usrResponsData.buf[COM_COMMAND_01] = RS485_MS_MESURING;
                    usrResponsData.buf[COM_COMMAND_02] = usrVL53Ctrl.MesurData & 0x00ff;
                    usrResponsData.buf[COM_COMMAND_03] = usrVL53Ctrl.MesurData >> 8;
                }
            }
             break;           
        case RS485_DS_MESURING_CONTINUE:
            if( usrComDataMain.req_mesure_mode == RASING_MODE_CONTINUE ){
                if( usrVL53Ctrl.MesurData > 8000 ){
                    usrResponsData.buf[COM_COMMAND_01] = RS485_MS_MESURING_OVER_RENGE;
                    usrResponsData.buf[COM_COMMAND_02] = 0;
                    usrResponsData.buf[COM_COMMAND_03] = 0;               
                }
                else{
                    usrResponsData.buf[COM_COMMAND_01] = RS485_MS_MESURING;
                    usrResponsData.buf[COM_COMMAND_02] = usrVL53Ctrl.MesurData & 0x00ff;
                    usrResponsData.buf[COM_COMMAND_03] = usrVL53Ctrl.MesurData >> 8;
                }
            }
             break;           
        case RS485_DS_ERROR:
            usrResponsData.buf[COM_COMMAND_01] = RS485_MS_ERROR;
             break;           
        }
        
        break;
    default:
        break;
    }
    
	
	//　チェックサム
	usrResponsData.buf[COM_CHKSUM_ID] = '$';

    for( i=COM_COUNTER_L; i < COM_CHKSUM; i++ ){
        chksum += usrResponsData.buf[i];
    }

	usrResponsData.buf[COM_CHKSUM] = chksum;

    
    
    
	// エンドテキスト
    usrResponsData.buf[COM_END_TXT_00] = message_end_text[0];
	usrResponsData.buf[COM_END_TXT_01] = message_end_text[1];
	usrResponsData.buf[COM_END_TXT_02] = message_end_text[2];
	usrResponsData.buf[COM_END_TXT_03] = message_end_text[3];
	usrResponsData.buf[COM_END_TXT_04] = message_end_text[4];
	usrResponsData.buf[COM_END_TXT_05] = message_end_text[5];

    usrComResMemoryDump("Respons ", &usrResponsData );

}

//==============================================================================
//
//==============================================================================
void usrResponsTX(void)
{
    usrResponsData.wpt = 1;    
    UART485_CTRL=1;
    putch485(usrResponsData.buf[0]);

}
//==============================================================================
//
//==============================================================================
void usrCommandProcessing(void)
{
    
    switch(usrComDataMain.command){
    case RS485_CMD_STATUS:
        break;	
	case RS485_CMD_VERSION:
        break;	
	case RS485_CMD_MESUR_START:
        usrComDataMain.req_mesure_mode  = usrCommandData.buf[COM_COMMAND_00];
        if( usrVL53Ctrl.RasingMode != usrComDataMain.req_mesure_mode ){
            usrVL53Ctrl.StopReq = 1;
            usrVL53Ctrl.StartRasingMode = usrComDataMain.req_mesure_mode;
        }
        break;	
	case RS485_CMD_MESUR_STOP:
        usrComDataMain.req_mesure_mode  = RASING_MODE_NON;
        usrVL53Ctrl.StopReq = 1;
        break;	
	case RS485_CMD_MESUR_DATA:
        usrComDataMain.req_mesure_mode  = usrCommandData.buf[COM_COMMAND_00];
        if( usrVL53Ctrl.RasingMode != usrComDataMain.req_mesure_mode ){
            usrVL53Ctrl.StopReq = 1;
            usrVL53Ctrl.StartRasingMode = usrComDataMain.req_mesure_mode;
        }
        break;	
    default:
        break;	
    }

    usrSetResponsData(usrComDataMain.command);
    usrComDataMain.status = RT_STATE_RESPONS;
    usrResponsTX();
 
}


//==============================================================================
//
//==============================================================================
RETURN_STATUS	usrChkStartTxt	( void )
{
    int             i;
    RETURN_STATUS   status = RET_TRUE;
    
    for( i=0; i<TEXT_LENGTH; i++ ){
        if( usrCommandData.buf[i] != com_start_text[i] ){
                status = RET_FALSE;
                break;
        }
    }
    return status;
}		

//==============================================================================
//
//==============================================================================
RETURN_STATUS	usrSetComCnt	( void )
{
    RETURN_STATUS   status = RET_TRUE;

    
    usrComDataMain.comCounter =  (uint16_t)usrCommandData.buf[COM_COUNTER_H];
    usrComDataMain.comCounter <<= 8;
    usrComDataMain.comCounter |= (uint16_t)usrCommandData.buf[COM_COUNTER_L];

    return status;
}		

//==============================================================================
//
//==============================================================================
RETURN_STATUS	usrChksumCnt	( int i, uint8_t *chksum )
{
    RETURN_STATUS   status = RET_TRUE;
    *chksum += usrCommandData.buf[i];
    return status;
}		
//==============================================================================
//
//==============================================================================
RETURN_STATUS	usrIDcheck	( void )
{
    RETURN_STATUS   status = RET_TRUE;
    
    if( usrCommandData.buf[COM_ADDRESS_ID] != '#' ){
        status = RET_FALSE;
    }
    if( usrCommandData.buf[COM_COMMAND_ID] != '*' ){
        status = RET_FALSE;
    }
    if( usrCommandData.buf[COM_CHKSUM_ID] != '$' ){
        status = RET_FALSE;
    }
            
    return status;
}		

//==============================================================================
//
//==============================================================================
RETURN_STATUS	usrCheckAddress	( void )
{
    RETURN_STATUS   status = RET_TRUE;

    if( usrCommandData.buf[COM_ADDRESS_SORC] != RS485_AD_MASTER ){
        status = RET_FALSE;
    }
    else{
        usrComDataMain.FromAddress = usrCommandData.buf[COM_ADDRESS_SORC];
    }
    
    if( usrCommandData.buf[COM_ADDRESS_DIST] != usrComDataMain.OwnAddress ){
        status = RET_FALSE;
    }

    return status;
}		
	
//==============================================================================
//
//==============================================================================
RETURN_STATUS	usrxCommandData	( void )
{
    int             i;
    RETURN_STATUS   status = RET_TRUE;
    
    usrComDataMain.command = usrCommandData.buf[COM_COMMAND];

    for( i=0; i < USR_COMMAND_DATA_MAX; i++ ){
        usrComDataMain.commandData[i] = usrCommandData.buf[COM_COMMAND_00+i];
    }

    return status;
}		

//==============================================================================
//
//==============================================================================
RETURN_STATUS	usrChekSum( void )
{
    int             i;
    uint8_t         chksum = 0;
    RETURN_STATUS   status = RET_TRUE;
    
    for( i=COM_COUNTER_L; i < COM_CHKSUM; i++ ){
        chksum +=  usrCommandData.buf[i];
    }

    if( chksum !=  usrCommandData.buf[COM_CHKSUM] ){
        status = RET_FALSE;
    }

    return status;
}		
//==============================================================================
//
//==============================================================================
RETURN_STATUS	usrChkEndTxt( void )
{
    int             i;
    RETURN_STATUS   status = RET_TRUE;
    
    for( i=0; i<TEXT_LENGTH; i++ ){
        if( usrCommandData.buf[COM_END_TXT_00+i] != message_end_text[i] ){
                status = RET_FALSE;
                break;
        }
    }
    return status;
}		
//==============================================================================
//
//==============================================================================
void usrComResMemoryDump(uint8_t *string, COM_RES_DATA *data)
{
    int         i,j;
    uint8_t     temp;
    uint8_t     ascii[COM_TABLE_MAX];
    
    LOG_PRINT_RS485("%s  wpt=%d\r\n", string, data->wpt );
    
    for( i=0; i<COM_TABLE_MAX; i++ ){
        LOG_PRINT_RS485("%2x ", data->buf[i]);
    }
    LOG_PRINT_RS485("\r\n");

    for( i=0; i<COM_TABLE_MAX; i++ ){
        temp = data->buf[i];
        if(temp<0x20||temp>=0x7f){
            temp = '.';
        }
        LOG_PRINT_RS485( "%c ", temp);
    }
    LOG_PRINT_RS485("\r\n");
}

//==============================================================================
//
//==============================================================================
RETURN_STATUS   usrRcvDataCheck(void)
{
    int             i;
    RETURN_STATUS   status = RET_TRUE;
    uint8_t         chksum = 0;
    
    usrComResMemoryDump("Command ", &usrCommandData );
    
    // Start Txt
    status = usrChkStartTxt();
    
    // Com Countrer
    if(status == RET_TRUE){
        status = usrSetComCnt();
    }
    
    // ID Chack # * $
    if(status == RET_TRUE){
        status = usrIDcheck();
    }
    
    // Address Chack
    if(status == RET_TRUE){
        status = usrCheckAddress();
    }
 
    // Command 
    if(status == RET_TRUE){
        status = usrxCommandData();
    }
 
    // End Txt
    if(status == RET_TRUE){
        status = usrChkEndTxt();
    }
 
    // Checksum 
    if(status == RET_TRUE){
        status = usrChekSum();
    }
    
    return status;
}

//==============================================================================
//
//==============================================================================
void usrRxMemoryDump(void)
{
    int         i,j;
    uint8_t     temp;
    uint8_t     ascii[17];
    
    LOG_PRINT_RS485("usrUartx485Rx rpt=%d, wpt=%d, status=0x%x\r\n", usrUartx485Rx.rpt,usrUartx485Rx.wpt, usrUartx485Rx.status );
    for( i=0; i<USRTx_RX_BUF; i++ ){
        temp = usrUartx485Rx.buf[i];
        ascii[i%16] =  (uint8_t)((temp<0x20||temp>=0x7f)? '.': temp);
        ascii[i%16+1] =  '\0';
        switch(i%16){
            case 7:
                LOG_PRINT_RS485("%2x  ", temp);
                break;
            case 15:
                LOG_PRINT_RS485("%2x    %s\r\n", temp, ascii);
                break;
            default:
                LOG_PRINT_RS485("%2x ", temp);
                break;
        }
    }
}
//==============================================================================
//
//==============================================================================
void RS_UartRxStrt( CMD_MSG	*rt_task )
{    
    int     l_RcvNum;
    int     i,j;
    int     rpt[6];
    int     flag;
    
    LOG_PRINT_RS485("RS_UartRxStrt()\r\n");
    
    l_RcvNum = usrUartx485Rx.wpt - usrUartx485Rx.rpt;
    
    if( l_RcvNum < 0 ){
        l_RcvNum +=  USRTx_RX_BUF;
    }
    
    usrRxMemoryDump();
    
    
    //---------------------------------------------------
    // スタートテキスト検索
    //---------------------------------------------------
    flag = 0;
    for( i=0; i<l_RcvNum; i++ ){
        for( j=0; j<6; j++ ){
            rpt[j] = usrUartx485Rx.rpt + i + j;
            rpt[j] = (rpt[j] < USRTx_RX_BUF) ? (rpt[j]):(rpt[j] - USRTx_RX_BUF);
        }
        if( usrUartx485Rx.buf[rpt[0]] == com_start_text[0] 
            && usrCommandData.buf[rpt[1]] == com_start_text[1]
            && usrCommandData.buf[rpt[2]] == com_start_text[2]
            && usrCommandData.buf[rpt[3]] == com_start_text[3]
            && usrCommandData.buf[rpt[4]] == com_start_text[4]
            && usrCommandData.buf[rpt[5]] == com_start_text[5] ){
     
            usrUartx485Rx.rpt += i;

            while( usrCommandData.wpt < COM_TABLE_MAX ){
                if(usrUartx485Rx.wpt != usrUartx485Rx.rpt){
                    usrCommandData.buf[usrCommandData.wpt] = (int)usrUartx485Rx.buf[usrUartx485Rx.rpt];
                    usrCommandData.wpt ++;

                    usrUartx485Rx.rpt ++;
                    if(usrUartx485Rx.rpt > USRTx_RX_BUF ){
                        usrUartx485Rx.rpt = 0;
                    }
                }
                else{
                    break;
                }
            }

            flag = 1;
            break;
        }
    }

    if( flag ==  1 ){
        usrComDataMain.status = RT_STATE_RECEIVING;
        
        if( usrCommandData.wpt == COM_TABLE_MAX  ){
            if( usrRcvDataCheck() == RET_TRUE){
                usrCommandProcessing();
            }
        }

    }
}
    
//==============================================================================
//
//==============================================================================
void RS_UartRxRcv( CMD_MSG	*rt_task )
{
    int     l_RcvNum;
    int     i,j;
    int     rptr[6];
    
    LOG_PRINT_RS485("RS_UartRxRcv()\r\n");

    l_RcvNum = usrUartx485Rx.wpt - usrUartx485Rx.rpt;
    
    if( l_RcvNum < 0 ){
        l_RcvNum +=  USRTx_RX_BUF;
    }
    
    //---------------------------------------------------
    // スタートテキスト検索
    //---------------------------------------------------
    while( usrCommandData.wpt < COM_TABLE_MAX ){
        if(usrUartx485Rx.wpt != usrUartx485Rx.rpt){
            usrCommandData.buf[usrCommandData.wpt] = (int)usrUartx485Rx.buf[usrUartx485Rx.rpt];
            usrCommandData.wpt ++;

            usrUartx485Rx.rpt ++;
            if(usrUartx485Rx.rpt > USRTx_RX_BUF ){
                usrUartx485Rx.rpt = 0;
            }
        }
        else{
            break;
        }
    }

    if( usrCommandData.wpt == COM_TABLE_MAX  ){
        if( usrRcvDataCheck() == RET_TRUE){
            usrCommandProcessing();
        }
    }
}

//==============================================================================
//
//==============================================================================
void RS_UartTxEnd( CMD_MSG	*rt_task )
{
    LOG_PRINT_RS485("RS_UartTxEnd()\r\n");

    usrComDataInit();
    usrComDataMain.status = RT_STATE_READY;
}

//==============================================================================
//
//==============================================================================
void RS_RcvTimeout( CMD_MSG	*rt_task )
{
    Xprintf("RS_UartTxEnd() Error Command Rx Time out:%d\r\n",__LINE__);
    usrComDataInit();
    usrComDataMain.status = RT_STATE_READY;
}



//==============================================================================
//
//==============================================================================
void RS_ResTimeout( CMD_MSG	*rt_task )
{
    Xprintf("RS_UartTxEnd() Error Command Tx Time out:%d\r\n",__LINE__);
    usrComDataInit();
    usrComDataMain.status = RT_STATE_READY;
}

//=============================================================================
// UART485 RX interrupt 
//=============================================================================
#define _UART_3_VECTOR                           31

#pragma vector ISR_Uart485Rx 31
#pragma interrupt ISR_Uart485Rx IPL7AUTO
void ISR_Uart485Rx(void) 
{
    BaseType_t      xHigherPriorityTaskWoken;
    BaseType_t      Status;

    if( UART485_RXIE && UART485_RXIF ){
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

        xHigherPriorityTaskWoken = pdFALSE;
        usrMsgQueueUART485Rx.event = RT_EVENT_UART_RX;
        usrMsgQueueUART485Rx.maroc_ptr = (void *)&usrMsgQueueUART485Rx;

        Status = xQueueSendFromISR(usrRs485Queue, (void *)&usrMsgQueueUART485Rx, &xHigherPriorityTaskWoken);

        if( xHigherPriorityTaskWoken ) { 
            portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
        } 

        UART485_RXIF = 0;
    }
    else if( UART485_TXIE && UART485_TXIF ){
        if( usrResponsData.wpt < COM_TABLE_MAX ){
            while ( UART485_TRMT ){
                
                UART485_TXREG = usrResponsData.buf[usrResponsData.wpt];
                usrResponsData.wpt++;
  
                if( usrResponsData.wpt == COM_TABLE_MAX ){
                    break;
                }
            }
        }        
        else{
            xHigherPriorityTaskWoken = pdFALSE;
            usrMsgQueueUART485Tx.event = RT_EVENT_UART_TX;
            usrMsgQueueUART485Tx.maroc_ptr = (void *)&usrMsgQueueUART485Tx;
            UART485_CTRL = 0;

            Status = xQueueSendFromISR(usrRs485Queue, (void *)&usrMsgQueueUART485Tx, &xHigherPriorityTaskWoken);

            if( xHigherPriorityTaskWoken ) { 
                portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
            } 
        }
        UART485_TXIF = 0;
    }
    

}

//==============================================================================
//
//==============================================================================
void usrComDataInit(void)
{
	uint8_t                 i;

    
    usrComDataMain.FromAddress      = RS485_AD_MASTER;
    usrComDataMain.OwnAddress       = RS485_OWN_ADDRESS;
    usrComDataMain.comCounter       = 0;
    usrComDataMain.command          = 0;
    for( i=0; i < USR_COMMAND_DATA_MAX; i++ ){
        usrComDataMain.commandData[i] = 0;    
    }
    usrComDataMain.event = 0;
    usrComDataMain.status =0;
    usrComDataMain.device_kind      = RS485_DSK_VL53OX;
    usrComDataMain.device_status    = RS485_DS_INIT;
    usrComDataMain.error_detail     = RS485_ERR_NON;
    usrComDataMain.req_mesure_mode  = RASING_MODE_NON;
    usrComDataMain.sens_m_ver       = 0;
    usrComDataMain.sens_s_ver       = 0;
    usrComDataMain.slv_m_ver        = USR_MAIN_VER;
    usrComDataMain.slv_s_ver        = USR_SUB_VER;
    
    for( i=0; i < COM_TABLE_MAX; i++ ){
        usrResponsData.buf[i] = 0;
        usrCommandData.buf[i] = 0;
    }
    usrResponsData.wpt = 0;
    usrCommandData.wpt = 0;
    
}

//==============================================================================
//
//==============================================================================
void vTask002(void *pvParameters)
{
    MESSAGE_QUE_DATA        *msg;
    MESSAGE_QUE_DATA_ISR	*msg_isr;
	uint8_t                 msgQueBuf[sizeof(void *)];
    uint8_t                 event;
	uint8_t                 state;
    RS485_TASK_STATE        timeout_start_state;
    TickType_t              xTicksToWait = portMAX_DELAY; 
    BaseType_t              result; 
    
    usrMessage_send("usrRS485_Init()\r\n");
    usrRS485_Init();
    usrMessage_send("usrComDataInit()\r\n");
    usrComDataInit();
            
    while(1){
        result = xQueueReceive(usrRs485Queue, msgQueBuf, xTicksToWait);
        
        switch(result){
        case pdPASS:
            msg = (MESSAGE_QUE_DATA *)msgQueBuf;
            msg = (MESSAGE_QUE_DATA	*)msg->maroc_ptr;
            msg_isr = (MESSAGE_QUE_DATA_ISR *)msgQueBuf;
            msg_isr = (MESSAGE_QUE_DATA_ISR	*)msg_isr->maroc_ptr;
            
            
            usrComDataMain.event = msg->event;
            
            switch(usrComDataMain.event){
            case RT_EVENT_UART_RX:
                 break;
            case RT_EVENT_MEASUR_RES:
                vPortFree(msg);
                 break;
            case RT_EVENT_UART_TX:
                 break;
            default:
                Xprintf("Error line%d event = %d\r\n",__LINE__,result);
                 break;
            }
            
            event = usrComDataMain.event;
            state = usrComDataMain.status;
            

            break;
        case errQUEUE_EMPTY:
            if( timeout_start_state == usrComDataMain.status ){
                usrComDataMain.event = RT_EVENT_TIMEOUT;
            }
            event = usrComDataMain.event;
            state = usrComDataMain.status;

            break;
        default:
            Xprintf("Error line%d xQueueReceive() = %d\r\n",__LINE__,result);
            while(1);
            break;
        }                

        //------------------------------------------------------------------
        //	処理関数
        //------------------------------------------------------------------
        LOG_PRINT_RS485("RS485 Event=%d, Status=%d\r\n", event, state);
        (*rs485_func_table[event][state ])( &usrComDataMain );

        
        
        timeout_start_state = usrComDataMain.status;
        switch(usrComDataMain.status){
        case RT_STATE_RECEIVING:
        case RT_STATE_RESPONS:
            xTicksToWait = 500;
            break;
        default:
            xTicksToWait = portMAX_DELAY; 
            break;
       }
    }
}

