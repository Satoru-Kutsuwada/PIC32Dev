/*
 * usr_debug_tool.c
 *
 *  Created on: Jul 21, 2023
 *      Author: nosak
 */

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
// external variable
//=============================================================================
extern  USR_UARTx_BUF    usrUartxRx;

extern  USR_VL53_DATA   usrVL53Ctrl;

//=============================================================================
// Prototype
//=============================================================================
size_t xPortGetFreeHeapSize( void );
void task_stack_display(void);
void Xprintf(const char *string, ...);
//=============================================================================
// variable
//=============================================================================
int input_pos;
char *sk_mem_dump;


//-----------------------------------------
//
//-----------------------------------------
typedef enum{
    INPUT_INIT,
    INPUT_SAVING,
    INPUT_DATA_FIX

} INPUT_CHAR_STEP;

INPUT_CHAR_STEP input_char_step = INPUT_INIT;

//-----------------------------------------
//
//-----------------------------------------
#define INPUT_BUF_SIZE 30

typedef struct{
char main[INPUT_BUF_SIZE];
char *sub_ptr[INPUT_BUF_SIZE/2];
uint16_t data[INPUT_BUF_SIZE/2];

uint16_t data1;
uint16_t data2;
}INPUT_STRING;

INPUT_STRING input_string;


//-----------------------------------------
//
//-----------------------------------------
 typedef enum{
    CMD_RTC,
    CMD_LOG,
    CMD_RS485,
	CMD_MEM_DUMP,
	CMD_MSG_QUE,
	CMD_VL53,

    CMD_MAX
 }COMMAND_MENUE;

#define MAX_COM_LENGTH 10
 typedef struct{
     COMMAND_MENUE pt;
     char command[MAX_COM_LENGTH];
 } COMAND_LIST;

 const COMAND_LIST com_list[] = {
     { CMD_RTC,      	"rtc"  },
     { CMD_LOG,      	"log" },
	 { CMD_RS485,    	"rs485" },
	 { CMD_MEM_DUMP,    "mem" },
	 { CMD_MSG_QUE,    	"msg" },
	 { CMD_VL53,    	"vl53" },
//	 { CMD_MSG_QUE,		"msg" ),


     { CMD_MAX, "none" }
 };

 //-----------------------------------------
 //
 //-----------------------------------------
 typedef enum{
     DEB_PROMPT_MODE = 0,
     DEB_LOG_MENUE,
     DEB_RS485_MENUE,
     DEB_MEM_MENUE,
	 DEB_MEM_INPUT_MENUE,
	 DEB_RS485_SCAN_MENUE,
	 DEB_VL53_MENUE,


     DEB_DISP_MAX
 } DEB_MENUE_TYPE;

 DEB_MENUE_TYPE dev_menue_type = DEB_PROMPT_MODE;


 //-----------------------------------------
 //
 //-----------------------------------------
#define MAX_LENGTH 30
typedef struct{
   char    name[MAX_LENGTH];
} MENUE;

const MENUE Deb_menue00[] = {
    "\r\nLOG MENUE\r\n",
    " 1.LOG DISPLAY\r\n",
    " 2.LOG CLEAR\r\n",
    " 3.STOP MODE:IMMMEDIATE\r\n",
    " 4.STOP MODE:MAX_DATA_STOP\r\n",
    " 5.STOP MODE:NON_STOP\r\n",

    " r.EXIT\r\n"
};


const MENUE Deb_menue01[] = {
    "\r\nRS485 MENUE\r\n",
    " 1.RX MODE\r\n",
    " 2.TX MODE\r\n",

    " r.EXIT"
};

const MENUE Deb_menue02[] = {
    "\r\nMEMPRY MENUE\r\n",
    " 1.ADDRESS INPUT\r\n",
    " 2.TASK01\r\n",
    " 3.TASK02\r\n",
    " 4.TASK03\r\n",
    " ",
    " (f)foward / (b)back\r\n",

    " r.EXIT\r\n"
};

const MENUE Deb_menue03[] = {
    "\r\nMEMPRY INPUT MENUE\r\n",
    " ADDRESS INPUT (r.Return) = 0x"
};

const MENUE Deb_menue04[] = {
    "\r\nRS485 SCAN MENUE\r\n",
    " 1.Single run\r\n",
    " 2.Continuous run\r\n",
    " 3.Stop\r\n",
    " 4.Message Que Info\r\n",
    " ",

    " r.EXIT\r\n"
};

const MENUE Deb_menue05[] = {
     "\r\nVL53 MENUE\r\n",
     " 1.VL53_INIT\r\n",
     " 2.CONTIIOUS RANGING\r\n",
     " 3.SINGLE RANGING\r\n",
     " 4.SINGLE RANGING HA\r\n",
     " 5.SINGLE RANGING HS\r\n",
     " 6.SINGLE RANGING LR\r\n",
     " 7.VL53 Data DISPLAY\r\n",
     " 8.   Init\r\n",
     " 9.   MESURE\r\n",

     " r.EXIT\r\n"
 };

typedef struct
{
   MENUE *pt;
   uint8_t clumn;
} MENUE_NUM_PAGE;

const MENUE_NUM_PAGE MenueList[]={
   (MENUE *)Deb_menue00, (uint8_t)(sizeof(Deb_menue00 )/sizeof(MENUE)),
   (MENUE *)Deb_menue01, (uint8_t)(sizeof(Deb_menue01 )/sizeof(MENUE)),
   (MENUE *)Deb_menue02, (uint8_t)(sizeof(Deb_menue02 )/sizeof(MENUE)),
   (MENUE *)Deb_menue03, (uint8_t)(sizeof(Deb_menue03 )/sizeof(MENUE)),
   (MENUE *)Deb_menue04, (uint8_t)(sizeof(Deb_menue04 )/sizeof(MENUE)),
   (MENUE *)Deb_menue05, (uint8_t)(sizeof(Deb_menue05 )/sizeof(MENUE))
};

typedef struct{
	uint8_t		*pxTopOfStack;
	uint8_t		*pxStack;
	uint16_t	size;
} STACK_INFO;

 /* Private function prototypes -----------------------------------------------*/
INPUT_CHAR_STEP read_line_streem(void);
COMMAND_MENUE input2menu(void);
void DBmanue_memdump(void);
void hex_dmp(uint8_t *buf, uint16_t size);
void vl53_mesure_new_proc(void);
void vl53_init(void);

int getch_buf(USR_UARTx_BUF *buf);
void DBmanue_prompt(void);
void DBmanue_log(void);
void DBmanue_vl53(void);
void DBmanue_rs485(void);
void DBmanue_mem_input(void);
void DispMenue(uint8_t type);
void vl53data_disp(void);
//=============================================================================
//
//=============================================================================
void debu_main(void)
{
	if(read_line_streem() == INPUT_DATA_FIX){

		input_char_step = INPUT_INIT;

		switch(dev_menue_type){
		case DEB_PROMPT_MODE:
			DBmanue_prompt();
			break;
		case DEB_LOG_MENUE:
			DBmanue_log();
			break;
		case DEB_RS485_MENUE:
			DBmanue_rs485();
			break;
		case DEB_MEM_MENUE:
			DBmanue_memdump();
			break;
		case DEB_MEM_INPUT_MENUE:
			DBmanue_mem_input();
			break;
		case DEB_RS485_SCAN_MENUE:
			break;
		case DEB_VL53_MENUE:
			DBmanue_vl53();
			break;
		default:
			break;
		}

        // メニュを表示する
        DispMenue(dev_menue_type);
	}
}
//==============================================================================
//
//==============================================================================
void DispMenue(uint8_t type)
{
    uint8_t i;
    if( type==DEB_PROMPT_MODE ){
        Xprintf("ST> ");
    }
    else{
        for( i=0; i<MenueList[type-1].clumn; i++){
            Xprintf("%s", &MenueList[type-1].pt[i].name[0]);
        }
    }
}

//=============================================================================
//
//=============================================================================



void DBmanue_prompt(void)
{
	uint8_t		i;

//	size_t 	lsize2;
//	size_t 	lsize1;

	switch( input2menu() ){
    case CMD_RTC:

        break;
    case CMD_LOG:
        dev_menue_type = DEB_LOG_MENUE;
        break;
    case CMD_RS485:
        dev_menue_type = DEB_RS485_MENUE;
        break;
    case CMD_MEM_DUMP:
        dev_menue_type = DEB_MEM_MENUE;
    	break;
    case CMD_MSG_QUE:
    	dev_menue_type = DEB_RS485_SCAN_MENUE;
    	break;
    case CMD_VL53:
    	dev_menue_type = DEB_VL53_MENUE;
    	break;

    default:
    	Xprintf("Command not found.\r\n");
    	Xprintf("Support Comand ...\r\n");
    	for( i=0; i<CMD_MAX ; i++ ){
        	Xprintf(" %s\r\n",&com_list[i].command[0]);
    	}

        break;
    }
}

//=============================================================================
//
//=============================================================================
void DBmanue_vl53(void)
{
	switch( input_string.main[0] ){
	case '1':
        usrVL53Ctrl.StopReq = 1;
        break;
    case '2':
        usrVL53Ctrl.StopReq = 1;
        while( usrVL53Ctrl.RasingMode != RASING_MODE_NON ){
            vTaskDelay(10); 
        }
        usrVL53Ctrl.RasingMode = RASING_MODE_CONTINUE;
        
        break;
    case '3':
        usrVL53Ctrl.StopReq = 1;
        while( usrVL53Ctrl.RasingMode != RASING_MODE_NON ){
            vTaskDelay(10); 
        }
        usrVL53Ctrl.RasingMode = RASING_MODE_SINGLE;
        break;
    case '4':
        usrVL53Ctrl.StopReq = 1;
        while( usrVL53Ctrl.RasingMode != RASING_MODE_NON ){
            vTaskDelay(10); 
        }
        usrVL53Ctrl.RasingMode = RASING_MODE_SINGLE_HA;
        break;
    case '5':
        usrVL53Ctrl.StopReq = 1;
        while( usrVL53Ctrl.RasingMode != RASING_MODE_NON ){
            vTaskDelay(10); 
        }
        usrVL53Ctrl.RasingMode = RASING_MODE_SINGLE_HS;
        break;
    case '6':
        usrVL53Ctrl.StopReq = 1;
        while( usrVL53Ctrl.RasingMode != RASING_MODE_NON ){
            vTaskDelay(10); 
        }
        usrVL53Ctrl.RasingMode = RASING_MODE_SINGLE_LR;
        break;
    case '7':
        vl53data_disp();
		break;
	case '8':
		//vl53_init();
		break;
	case '9':
		//vl53_mesure_new_proc();

		break;
	case 'r':
	case 'R':
		dev_menue_type = DEB_PROMPT_MODE;
	default:
		break;
	}
}

//=============================================================================
//
//=============================================================================

//=============================================================================
//
//=============================================================================
void DBmanue_log(void)
{
	switch( input_string.main[0] ){
	case '1':
		//LogInfo_display();
		break;
	case '2':
		//LogInfo_clear();
		break;
	case '3':
		//Set_logflg(LF_NON_STOP);
		break;
	case '4':
		//Set_logflg(LF_IMMMEDIATE_STOP);
		break;
	case '5':
		//Set_logflg(LF_MAX_DATA_STOP);
		break;
	case 'r':
	case 'R':
		dev_menue_type = DEB_PROMPT_MODE;
	default:
		break;
	}
}

//=============================================================================
//
//=============================================================================
void DBmanue_rs485(void)
{
	switch( input_string.main[0] ){
	case '1':
		break;
	case '2':
		break;
	case '3':
		break;
	case '4':
		break;
	case '5':
		break;
	case 'r':
	case 'R':
		dev_menue_type = DEB_PROMPT_MODE;
	default:
		break;
	}
}


//==============================================================================
//
//==============================================================================
void DBmanue_memdump(void)
{
	STACK_INFO stack;

	switch( input_string.main[0] ){
	case '1':
		dev_menue_type = DEB_MEM_INPUT_MENUE;
		break;
	case '2':
#ifdef ___NOP
		Disp_task_info(SK_TASK_main);
		Get_task_stackptr(SK_TASK_main,&stack);
		hex_dmp(stack.pxStack, stack.size);
		//hex_dmp(stack.pxTopOfStack, stack.size);
#endif
		break;
	case '3':
#ifdef ___NOP
		Disp_task_info(SK_TASK_sub1);
		Get_task_stackptr(SK_TASK_sub1,&stack);
		hex_dmp(stack.pxStack, stack.size);
		//hex_dmp(stack.pxTopOfStack, stack.size);
#endif
		break;
	case '4':
#ifdef ___NOP
		Disp_task_info(SK_TASK_sub2);
		Get_task_stackptr(SK_TASK_sub2,&stack);
		hex_dmp(stack.pxStack, stack.size);
		//hex_dmp(stack.pxTopOfStack, stack.size);
#endif
		break;
	case '5':
		break;
	case 'f':
		if(sk_mem_dump != NULL){
			sk_mem_dump += 128*4;
			hex_dmp(sk_mem_dump, 128*4);
		}
		break;
	case 'b':
		if(sk_mem_dump != NULL){
			sk_mem_dump -= 128*4;
			hex_dmp(sk_mem_dump, 128*4);
		}
		break;
	case 'r':
	case 'R':
		dev_menue_type = DEB_PROMPT_MODE;
	default:
		break;
	}

}

//==============================================================================
//
//==============================================================================
void DBmanue_mem_input(void)
{
	int 		i = 0;
	uint32_t	dt = 0;
	uint8_t		c = input_string.main[0];

	if( c == 'r' || c == 'R' ){

	}
	else{
		while( input_string.main[i] != '\0'){
			c= input_string.main[i];

			dt <<= 4;

			if( c >= '0'  && c <= '9' ){
				dt |= ( c - '0');
			}
			else if( c >= 'a'  && c <= 'f' ){
				dt |= ( c - 'a' + 10);
			}
			else if( c >= 'A'  && c <= 'F' ){
				dt |= ( c - 'A' + 10);
			}

			i++;
		}

		Xprintf("dt=%lx",dt);
		hex_dmp((uint8_t *)dt, 128*4);
	}

	dev_menue_type = DEB_MEM_MENUE;

}



//==============================================================================
//
//==============================================================================
void hex_dmp(uint8_t *buf, uint16_t size)
{
    int i,j;
    uint8_t *p;
    uint8_t *p_disp;
    uint8_t tmp[17];
    uint16_t flg;
    uint16_t pre_data;
    uint16_t	size_plus;
    uint32_t pp;



   p = buf;
   pp = (uint32_t)buf;
   p_disp = (uint8_t *)(pp & 0xfffffff0);
   p = p_disp;

   pre_data = (uint8_t)pp & 0x0000000F;
   sk_mem_dump = p_disp;

   size_plus = size + pre_data;
   if(( size_plus % 16 ) != 0){
    	   size_plus = size_plus + 16 - (size_plus % 16);
    }


    Xprintf("\r\n%p -->>\r\n",p);
    Xprintf("            0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F    -- ASCII --\r\n");
    Xprintf("-----------+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+-----------------\r\n");


    for (i=0; i<size_plus; i++) {

    	if(( i % 16)== 0){
    	    Xprintf("%08p  ",p_disp);
    	    if( p_disp != &p[i] ){
    	    	Xprintf("\r\nERROR p_disp=%p,p=%p\r\n",p_disp,&p[i]);
    	    }
    	    p_disp += 16;
    	}


		j = i % 16;

		if( i < (size + pre_data) ){
			Xprintf("%02x ", p[i]);
			tmp[j] = (uint8_t)((p[i]<0x20||p[i]>=0x7f)? '.': p[i]);
					}
		else{
			Xprintf("   ");
			tmp[j] = ' ';
		}

		flg = 1;
		if(( i % 16)==15 ){
			flg = 0;
			tmp[j+1] = '\0';
			Xprintf(" %s\r\n", tmp);
		}
    }

    if( flg == 1 ){
		tmp[j+1] = '\0';
		Xprintf("%s\r\n", tmp);
    }

}

//==============================================================================
//
//==============================================================================

COMMAND_MENUE input2menu(void)
{
     uint16_t i = 0;
    COMMAND_MENUE rtn = CMD_MAX;

        while( com_list[i].pt != CMD_MAX ){
            if (strcmp(&input_string.main[0], &com_list[i].command[0]) == 0){
                rtn = com_list[i].pt;
                break;
            }
            i++;
        }

    return rtn;
}
//==============================================================================
//
//==============================================================================
void command_split(void)
{
	int		i;
	int		j;
	char	moji = 0;
	char 	*ptr;

	for( j = 0; j<INPUT_BUF_SIZE/2; j++ ){
		input_string.sub_ptr[j] = 0;
	}

	for( i= 0; i<INPUT_BUF_SIZE; i++ ){
		switch(input_string.main[i]){
		case ' ':		// スペース
		case ',':		//　カンマ
		case '	':		//　タブ
			input_string.main[i] = '\0';
			moji = 0;
			break;
		default:
			if( moji == 0 ){
				if( j < INPUT_BUF_SIZE/2){
					input_string.sub_ptr[j] = &input_string.main[i];
				}
				moji = 1;
			}
			break;
		}
	}

	for( j = 1; j<INPUT_BUF_SIZE/2; j++ ){
		ptr = input_string.sub_ptr[j];
		moji = 1;
		if( ptr != 0 ){
			if ( ptr[0] == '0' && ptr[1] == 'x'){
				ptr ++;
				ptr ++;
				while( *ptr != '\0' ){
					if( ('0'<=*ptr && *ptr<='9') || ('A'<=*ptr && *ptr<='F') || ('a'<=*ptr && *ptr<='f')){

					}
					else{
						moji = 0;
					}
					ptr ++;
				}

				if( moji == 1 ){
					sscanf(input_string.sub_ptr[j], "%x", &input_string.data[j]);
				}
			}
			else{
				while( *ptr != '\0' ){
					if( '0'<=*ptr && *ptr<='9'){
					}
					else{
						moji = 0;
					}
					ptr ++;
				}

				if( moji == 1 ){
					sscanf(input_string.sub_ptr[j], "%d", &input_string.data[j]);
				}
			}

		}
		else{
			break;
		}
	}

}

//==============================================================================
//
//==============================================================================
 INPUT_CHAR_STEP read_line_streem(void)
{
    char    c;
    char	string[2];

    string[0] = '\0';
    string[1] = '\0';


    c = (char)getch_buf(&usrUartxRx);

    //Xprintf("read_line_streem()\r\n");

    if( c != 0 ){



        switch(input_char_step){
            case INPUT_INIT:
                input_pos = 0;
                input_char_step = INPUT_SAVING;


            case INPUT_SAVING:
                if( isprint(c) && (input_pos <= INPUT_BUF_SIZE - 2)){
                    input_string.main[input_pos] = c;
                    input_pos ++;
                    string[0] = c;
                    Xprintf("%s",string);
                }
                else if (c == 0x08 && input_pos > 0) {      // Back Space
                    input_pos --;
                    Xprintf("\x08 \x08");
                }
                else if (c == '\r') {
                    input_string.main[input_pos] = '\0';
                    Xprintf("\r\n");
                    input_char_step = INPUT_DATA_FIX;

                    command_split();
                }
            default:
                break;
        }
    }
    return(input_char_step);
 }
