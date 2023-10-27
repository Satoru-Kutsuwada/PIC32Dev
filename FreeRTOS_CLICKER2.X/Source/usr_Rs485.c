
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


//=============================================================================
// Master - Slave Command Format
//=============================================================================

/* Private variables ---------------------------------------------------------*/
#define TEXT_LENGTH		6
const char com_start_text[]   = "COM-ST\0";
const char message_end_text[] = "MSGEND\0";
char comp_buf[TEXT_LENGTH+1];

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
	RT_STATE_PROCESSING,
	RT_STATE_RESPONS,

	RT_STATE_MAX
} RS485_TASK_STATE;


typedef enum {
	RS485_AD_MASTER = 0,
	RS485_AD_SLEVE01,
	RS485_AD_SLEVE02,
	RS485_AD_MAX
}RS485_ADDRESS;        
        
        
typedef enum {
	RS485_CMD_STATUS = 1,
	RS485_CMD_VERSION,
	RS485_CMD_MESUR_START,
	RS485_CMD_MESUR_STOP,
	RS485_CMD_MESUR_DATA,

	RS485_CMD_MAX
}RS485_COMMAND;


#define     USR_COMMAND_DATA_MAX    (COM_COMMAND_11-COM_COMMAND)
typedef struct{
    RS485_TASK_EVENT    event;
    RS485_TASK_STATE    status;
	RS485_COMMAND		command;
    uint8_t             commandData[USR_COMMAND_DATA_MAX];
	RS485_ADDRESS		OwnAddress;
	RS485_ADDRESS		FromAddress;
    uint16_t            comCounter;
} CMD_MSG;

CMD_MSG     usrComMessRxISR;    // UART Rx ISR --> Task
CMD_MSG     usrComMessTxISR;    // UART Tx ISR --> Task
CMD_MSG     usrComDataMain;         // UART Tx ISR --> Task



//==============================================================================
//
//==============================================================================

typedef struct{
	void				*maroc_ptr;
	CMD_MSG             cm;
}MESSAGE_QUE_DATA;


void RS_nop( CMD_MSG	*rt_task );
void RS_UartRxStrt( CMD_MSG	*rt_task );
void RS_UartRxRcv( CMD_MSG	*rt_task );

void RS_MesurRes( CMD_MSG	*rt_task );
void RS_UartTxEnd( CMD_MSG	*rt_task );
void RS_RcvTimeout( CMD_MSG	*rt_task );
void RS_ProcTimeout( CMD_MSG	*rt_task );
void RS_ResTimeout( CMD_MSG	*rt_task );


const void (*rs485_func_table[RT_EVENT_MAX][RT_STATE_MAX])( CMD_MSG	*rt_task )={
	//      READY		Receiving      Processing  Respons
		{ RS_UartRxStrt,  RS_UartRxRcv,      RS_nop,         RS_nop			},      // UART_Rx
		{ RS_nop,     RS_nop,         RS_MesurRes,    RS_nop			},      // Measurement_RES
		{ RS_nop,     RS_nop,         RS_nop,         RS_UartTxEnd    },      // UART_Tx
		{ RS_nop,     RS_RcvTimeout,  RS_ProcTimeout, RS_ResTimeout    }     // UART_Tx
};


//==============================================================================
//
//==============================================================================
RETURN_STATUS	usrChkStartTxt	( int i, uint8_t *chksum );
RETURN_STATUS	usrSetComCntrt	( int i, uint8_t *chksum );
RETURN_STATUS	usrChksumCnt	( int i, uint8_t *chksum );
RETURN_STATUS	usrIDchkAddress	( int i, uint8_t *chksum );
RETURN_STATUS	usrDistAddress	( int i, uint8_t *chksum );
RETURN_STATUS	usrSrcAddress	( int i, uint8_t *chksum );
RETURN_STATUS	usrIDchkCommand	( int i, uint8_t *chksum );
RETURN_STATUS	usrxCommandData	( int i, uint8_t *chksum );
RETURN_STATUS	usrIDchkChksum	( int i, uint8_t *chksum );
RETURN_STATUS	usrChksum	( int i, uint8_t *chksum );
RETURN_STATUS	usrChkEndTxt	( int i, uint8_t *chksum );



const RETURN_STATUS (*usrRcvChkTable[COM_TABLE_MAX])( int i, uint8_t *chksum ) = {
                    // スタートテキスト	
    usrChkStartTxt,	//	COM_START_TXT_00 = 0,
    usrChkStartTxt,	//	COM_START_TXT_01,
    usrChkStartTxt,	//	COM_START_TXT_02,
    usrChkStartTxt,	//	COM_START_TXT_03,
    usrChkStartTxt,	//	COM_START_TXT_04,
    usrChkStartTxt,	//	COM_START_TXT_05,

            // 通信カウンタ	
    usrSetComCntrt,	//	COM_COUNTER_L,
    usrSetComCntrt,	//	COM_COUNTER_H,

            // アドレス	
    usrIDchkAddress,	//	COM_ADDRESS_ID,
    usrDistAddress,	//	COM_ADDRESS_DIST,
    usrSrcAddress,	//	COM_ADDRESS_SORC,
    usrChksumCnt,	//	COM_ADDRESS_RESERVD,

            // コマンド・レスポンス	
    usrIDchkCommand,	//	COM_COMMAND_ID,
    usrxCommandData,	//	COM_COMMAND,
    usrxCommandData,	//	COM_COMMAND_00,
    usrxCommandData,	//	COM_COMMAND_01,
    usrxCommandData,	//	COM_COMMAND_02,
    usrxCommandData,	//	COM_COMMAND_03,
    usrxCommandData,	//	COM_COMMAND_04,
    usrxCommandData,	//	COM_COMMAND_05,
    usrxCommandData,	//	COM_COMMAND_06,
    usrxCommandData,	//	COM_COMMAND_07,
    usrxCommandData,	//	COM_COMMAND_08,
    usrxCommandData,	//	COM_COMMAND_09,
    usrxCommandData,	//	COM_COMMAND_10,
    usrxCommandData,	//	COM_COMMAND_11,

            //　チェックサム	
    usrIDchkChksum,	//	COM_CHKSUM_ID,
    usrChksum,	//	COM_CHKSUM,

            // エンドテキスト	
    usrChkEndTxt,	//	COM_END_TXT_00,
    usrChkEndTxt,	//	COM_END_TXT_01,
    usrChkEndTxt,	//	COM_END_TXT_02,
    usrChkEndTxt,	//	COM_END_TXT_03,
    usrChkEndTxt,	//	COM_END_TXT_04,
    usrChkEndTxt		//	COM_END_TXT_05,

};


//=============================================================================
//  vTask002
//=============================================================================
void vTask002(void *pvParameters)
{
#ifdef ___NOP
    uint8_t buf[2];
    buf[1] = '\0';
#endif
    
    Xprintf("vTask002()\r\n");
    vTaskDelay(100);
    while(1) {

#ifdef ___NOP
        buf[0] = (uint8_t)getch_buf(&usrUartx485Rx);
//        buf[0] = (uint8_t)getch485();
        if(buf[0] != 0 ){
            putstring(UART_FOR_485,buf);
        }
        //usrMessage_send( usrT02Message_buf,"TEST2=%d\r\n",12345 );
       vTaskDelay(200);
#endif
       rs485_com_task();

    }
}
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
void usrUartRxISR(void)
{
    BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;


    usrComMessRxISR.event = RT_EVENT_UART_RX;
    xQueueSendFromISR(usrRs485Queue,(void *)&usrComMessRxISR,&xHigherPriorityTaskWoken);
    portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
    
}

//==============================================================================
//
//==============================================================================
void RS_nop( CMD_MSG	*rt_task )
{
//	Set_logInfo2("★RS_nop(S=%d,E=%d)",rt_task->state, rt_task->event);
}

//==============================================================================
//
//==============================================================================
void usrSetResponsData(RS485_COMMAND command)
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
    usrResponsData.buf[COM_COMMAND_00] = usrComDataMain.command;
    
    
	
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

    
}

//==============================================================================
//
//==============================================================================
void usrCommandProcessing(void)
{
    switch(usrComDataMain.command){
    case RS485_CMD_STATUS:
        usrComDataMain.status = RT_STATE_RESPONS;
        break;	
	case RS485_CMD_VERSION:
        usrComDataMain.status = RT_STATE_RESPONS;
        break;	
	case RS485_CMD_MESUR_START:
        usrComDataMain.status = RT_STATE_PROCESSING;
        break;	
	case RS485_CMD_MESUR_STOP:
        usrComDataMain.status = RT_STATE_PROCESSING;
        break;	
	case RS485_CMD_MESUR_DATA:
        usrComDataMain.status = RT_STATE_PROCESSING;
        break;	
    default:
        break;	
    }
}


//==============================================================================
//
//==============================================================================
RETURN_STATUS	usrChkStartTxt	( int i, uint8_t *chksum )
{
    RETURN_STATUS   status = RET_TRUE;
    if( usrCommandData.buf[i] != com_start_text[i] ){
            status = RET_FALSE;
    }
    return status;
}		

//==============================================================================
//
//==============================================================================
RETURN_STATUS	usrSetComCntrt	( int i, uint8_t *chksum )
{
    RETURN_STATUS   status = RET_TRUE;

    *chksum += usrCommandData.buf[i];
    
    if( i == COM_COUNTER_L ){
        usrComDataMain.comCounter = (uint16_t)usrCommandData.buf[i+1];
        usrComDataMain.comCounter <<= 8;
        usrComDataMain.comCounter |= (uint16_t)usrCommandData.buf[i];
    }
    else{
        usrComDataMain.comCounter = (uint16_t)usrCommandData.buf[i];
        usrComDataMain.comCounter <<= 8;
        usrComDataMain.comCounter |= (uint16_t)usrCommandData.buf[i-1];
    }

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
RETURN_STATUS	usrIDchkAddress	( int i, uint8_t *chksum )
{
    RETURN_STATUS   status = RET_TRUE;
    *chksum += usrCommandData.buf[i];
    if( usrCommandData.buf[i] != '#' ){
        status = RET_FALSE;
    }
    return status;
}		
//==============================================================================
//
//==============================================================================
RETURN_STATUS	usrDistAddress	( int i, uint8_t *chksum )
{
    RETURN_STATUS   status = RET_TRUE;
    *chksum += usrCommandData.buf[i];
    usrComDataMain.FromAddress = usrCommandData.buf[i];
    if( usrCommandData.buf[i] != usrComDataMain.OwnAddress ){
        status = RET_FALSE;
    }
    return status;
}		
//==============================================================================
//
//==============================================================================
RETURN_STATUS	usrSrcAddress	( int i, uint8_t *chksum )
{
    RETURN_STATUS   status = RET_TRUE;
    *chksum += usrCommandData.buf[i];
    if( usrCommandData.buf[i] != RS485_AD_MASTER ){
        status = RET_FALSE;
    }
    return status;
}		
//==============================================================================
//
//==============================================================================
RETURN_STATUS	usrIDchkCommand	( int i, uint8_t *chksum )
{
    RETURN_STATUS   status = RET_TRUE;
    *chksum += usrCommandData.buf[i];
    if( usrCommandData.buf[i] != '*' ){
        status = RET_FALSE;
    }
    return status;
}		
//==============================================================================
//
//==============================================================================
RETURN_STATUS	usrxCommandData	( int i, uint8_t *chksum )
{
    RETURN_STATUS   status = RET_TRUE;
    *chksum += usrCommandData.buf[i];
    if( i == COM_COMMAND ){
        usrComDataMain.command = usrCommandData.buf[i];
    }
    else{
        usrComDataMain.commandData[i-COM_COMMAND-1] = usrCommandData.buf[i];
    }
    return status;
}		
//==============================================================================
//
//==============================================================================
RETURN_STATUS	usrIDchkChksum	( int i, uint8_t *chksum )
{
    RETURN_STATUS   status = RET_TRUE;
    if( usrCommandData.buf[i] != '$' ){
        status = RET_FALSE;
    }
    return status;
}		
//==============================================================================
//
//==============================================================================
RETURN_STATUS	usrChksum	( int i, uint8_t *chksum )
{
    RETURN_STATUS   status = RET_TRUE;
    if( usrCommandData.buf[i] != *chksum ){
        status = RET_FALSE;
    }
    return status;
}		
//==============================================================================
//
//==============================================================================
RETURN_STATUS	usrChkEndTxt	( int i, uint8_t *chksum )
{
    RETURN_STATUS   status = RET_TRUE;
    if( usrCommandData.buf[i] != message_end_text[i-COM_END_TXT_00] ){
        status = RET_FALSE;
    }
    return status;
}		

//==============================================================================
//
//==============================================================================
RETURN_STATUS   usrRcvDataCheck(void)
{
    int             i;
    RETURN_STATUS   status = RET_TRUE;
    uint8_t         chksum = 0;
    
    

    // フォーマットチェック
    for( i=0; i<COM_TABLE_MAX; i++ ){
        if( (*usrRcvChkTable[i])( i, &chksum ) == RET_FALSE ){
           break;	
        }
    }
    
    return status;
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
    
    l_RcvNum = usrUartx485Rx.wpt - usrUartx485Rx.rpt;
    
    if( l_RcvNum < 0 ){
        l_RcvNum +=  USRTx_RX_BUF;
    }
    
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
    int     flag;
    
    l_RcvNum = usrUartx485Rx.wpt - usrUartx485Rx.rpt;
    
    if( l_RcvNum < 0 ){
        l_RcvNum +=  USRTx_RX_BUF;
    }
    
    //---------------------------------------------------
    // スタートテキスト検索
    //---------------------------------------------------
    flag = 0;
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
void RS_MesurRes( CMD_MSG	*rt_task )
{
//	Set_logInfo2("★RS_nop(S=%d,E=%d)",rt_task->state, rt_task->event);
}

//==============================================================================
//
//==============================================================================
void RS_UartTxEnd( CMD_MSG	*rt_task )
{
//	Set_logInfo2("★RS_nop(S=%d,E=%d)",rt_task->state, rt_task->event);
}

//==============================================================================
//
//==============================================================================
void RS_RcvTimeout( CMD_MSG	*rt_task )
{
//	Set_logInfo2("★RS_nop(S=%d,E=%d)",rt_task->state, rt_task->event);
}

//==============================================================================
//
//==============================================================================
void RS_ProcTimeout( CMD_MSG	*rt_task )
{
//	Set_logInfo2("★RS_nop(S=%d,E=%d)",rt_task->state, rt_task->event);
}

//==============================================================================
//
//==============================================================================
void RS_ResTimeout( CMD_MSG	*rt_task )
{
//	Set_logInfo2("★RS_nop(S=%d,E=%d)",rt_task->state, rt_task->event);
}



//==============================================================================
//
//==============================================================================
void rs485_com_task(void)
{
    CMD_MSG				RTtask;
    MESSAGE_QUE_DATA	*msg;
	uint8_t				msgQueBuf[sizeof(void *)];
    uint8_t				event;
	uint8_t				state;

    usrRS485_Init();

    while(1){
        if(xQueueReceive(usrRs485Queue, msgQueBuf, portMAX_DELAY) == pdPASS ) {
            msg = (MESSAGE_QUE_DATA *)msgQueBuf;
            msg = (MESSAGE_QUE_DATA	*)msg->maroc_ptr;


            vPortFree(msg->maroc_ptr);



            //-------------------------------------------------------------------------
            //	処理関数
            //-------------------------------------------------------------------------
            (*rs485_func_table[event][state ])( &RTtask );

        }
        else{


        }
    }
}

