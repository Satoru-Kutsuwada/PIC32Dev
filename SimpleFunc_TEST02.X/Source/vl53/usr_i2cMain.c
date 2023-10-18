//=============================================================================
// include
//=============================================================================
#include <xc.h>	
#include "usr_system.h"

//=============================================================================
// define
//=============================================================================
#define STATUS_OK              0x00
#define STATUS_FAIL            0x01
#define MAX_MULTI_CNT 20

// I2C　リカバリー回数
#define I2C_RECOVRY_MAX           10

#define I2C_SEND_ACK  0 
#define I2C_SEND_NACK 1 
//=============================================================================
// extern variable
//=============================================================================


//=============================================================================
// variable
//=============================================================================
uint16_t    bcl_error_chk;


typedef enum{
    I2C_STAT_START = 0,
    I2C_STAT_WITE_ADDRESS_TX,
    I2C_STAT_READ_ADDRESS_TX,
    I2C_STAT_INDEX_TX,
    I2C_STAT_DATA_TX,
    I2C_STAT_STOP,
    I2C_STAT_SUSPEND,
    I2C_STAT_RESTART,
    I2C_STAT_READ,
    I2C_STAT_END,
    I2C_STAT_MAX
            
            
}I2C_STAT_STEP; //i2c_data.status


typedef enum{
    I2C_NO_ERROR = 0,

    I2C_ERR_STAT_BCL,        
    I2C_ERR_STAT_WCOL,        
    I2C_ERR_STAT_TIMEOUT,        
    I2C_ERR_STAT_NACK,
    I2C_ERR_STAT_ADDRESS_NACK,
    I2C_ERR_STAT_INDEX_NACK,
    I2C_ERR_STAT_DATA_NACK,
            
    I2C_ERROR_ETC
}I2C_ERROR; //i2c_data.status



typedef enum{
    I2C_WRITE_MULTI = 1,
    I2C_READ_MULTI
}I2C_OPERATION_TYPE;


typedef struct{
    I2C_STAT_STEP status;
    I2C_ERROR error;
    I2C_OPERATION_TYPE op_type;
    uint8_t address;
    uint8_t index;
    uint8_t count;
    uint8_t count_step;
    uint8_t dt[MAX_MULTI_CNT];
    uint8_t restart_cnt;
    
}I2C_DATA;

I2C_DATA i2c_data;

//=============================================================================
// Prototype
//=============================================================================
void Xprintf(const char *string, ...);



/********************************************************************
 * Function:        void i2c_init(void)
 *
 *    speed : I2Cの通信速度を指定(0=100KHz 1=400KHz)                            *
*                                                                              *
*    注)クロック8MHzでの設定です、他のクロックはSSPADDを変更する必要が有ります *
*             4MHz  8MHz  16MHz  32MHz  40MHz  48MHz                           *
*    100KHz   0x09  0x13   0x27   0x4F   0x63   0x77                           *
*    400kHz         0x04   0x09   0x13   0x18   0x1D                           
 ********************************************************************/

void i2c_init(uint8_t sel)
{
    
    // Fpb = 40Mhz, Fsk = 400kHz
    I2C_DISSLW = 0;
    I2C_BRG = 0x002F;
    
    // Port 
    I2C_SCL = 1;
    I2C_SDA = 1;

    // Interrupt
    I2C_ICIP = 7;
    I2C_ICIS = 0;
    I2C_ICIF = 0;
    I2C_ICIE = 1;
    
    // I2C Enable
    I2C_ON = 1;
    
    
}


//=============================================================================
//
//=============================================================================
uint8_t i2c_CheckIdleWait(uint8_t mask)
{
    uint8_t status;
    int index;

    status = STATUS_OK ;    

    index = Set_Timer(100);
    while ( I2C_TBF     ||     //送信中
            I2C_RBF     ||     //受信データあり
            I2C_SEN     ||
            I2C_RSEN    ||
            I2C_PEN     ||
            I2C_RCEN    ||
            I2C_ACKEN ){ 

        
        if( Get_Timer(index) == 0 ){
            //SetLogDataM( LOG_DISP_I2C, "ERR(TOUT): CheckIdle",I2C_SSPSTAT,I2C_SSPCON1,I2C_SSPCON2,0);
            i2c_data.error = I2C_ERR_STAT_TIMEOUT;        
            status = STATUS_FAIL;    
            break;   
        }
    }
    Rel_Timer(index);
    
    return  status;
}
//=============================================================================
//
//=============================================================================
uint8_t i2c_start(void)
{
    uint8_t status;
    int index;

    status = STATUS_OK ;    
    bcl_error_chk = 0;
    
    status = i2c_CheckIdleWait(0x05);

    if( status == STATUS_OK ){
        //SetLogDataM( LOG_DISP_I2C, "START",I2C_SSPSTAT,I2C_SSPCON1,I2C_SSPCON2,0);
        

        I2C_ICIF = 0;
        //I2C_BCLIF = 0;

        I2C_SEN = 1;

        index = Set_Timer(100);
        while( I2C_ICIF == 0 ){
            if(bcl_error_chk){
                //SetLogDataM( LOG_DISP_I2C, "ERR(BCL): START",I2C_SSPSTAT,I2C_SSPCON1,I2C_SSPCON2,0);
                i2c_data.error = I2C_ERR_STAT_BCL;      
                status = STATUS_FAIL;    
            }
            if(I2C_IWCOL){
                //SetLogDataM( LOG_DISP_I2C, "ERR(WCOL): START",I2C_SSPSTAT,I2C_SSPCON1,I2C_SSPCON2,0);
                I2C_IWCOL = 0;
                i2c_data.error = I2C_ERR_STAT_WCOL;        
                status = STATUS_FAIL;    
                break         ;   
            }
            if( Get_Timer(index) == 0 ){
                //SetLogDataM( LOG_DISP_I2C, "ERR(TOUT): START",I2C_SSPSTAT,I2C_SSPCON1,I2C_SSPCON2,0);
                i2c_data.error = I2C_ERR_STAT_TIMEOUT;        
                status = STATUS_FAIL;    
                break         ;   
            }
        }
        Rel_Timer(index);
    }    


    return  status;
}

//=============================================================================
//
//=============================================================================
uint8_t i2c_stop(void)
{
    uint8_t status;
    int index;

    status = STATUS_OK ;    
    bcl_error_chk = 0;

    status = i2c_CheckIdleWait(0x05);

    if( status == STATUS_OK ){
        //SetLogDataM( LOG_DISP_I2C, "STOP",I2C_SSPSTAT,I2C_SSPCON1,I2C_SSPCON2,0);

        I2C_ICIF = 0;
        //I2C_BCLIF = 0;

        I2C_PEN = 1;

        index = Set_Timer(100);
        while(I2C_ICIF == 0 )
        {
            if(bcl_error_chk){
                //SetLogDataM( LOG_DISP_I2C, "ERR(BCL): STOP",I2C_SSPSTAT,I2C_SSPCON1,I2C_SSPCON2,0);
                i2c_data.error = I2C_ERR_STAT_BCL;      
                status = STATUS_FAIL;    
            }
            if(I2C_IWCOL){
                //SetLogDataM( LOG_DISP_I2C, "ERR(WCOL): STOP",I2C_SSPSTAT,I2C_SSPCON1,I2C_SSPCON2,0);
                I2C_IWCOL = 0;
                i2c_data.error = I2C_ERR_STAT_WCOL;        
                status = STATUS_FAIL;    
                break;           
            }
            if( Get_Timer(index) == 0 ){
                //SetLogDataM( LOG_DISP_I2C, "ERR(TOUT): STOP",I2C_SSPSTAT,I2C_SSPCON1,I2C_SSPCON2,0);
                i2c_data.error = I2C_ERR_STAT_TIMEOUT;        
                status = STATUS_FAIL;    
                break;   
            }
        }
        Rel_Timer(index);
    }

    return  status;
}


//=============================================================================
//
//=============================================================================
uint8_t i2c_write( uint8_t dt )
{
    uint8_t status;
    int index;

    status = STATUS_OK ;    
    bcl_error_chk = 0;

    status = i2c_CheckIdleWait(0x05);

    if( status == STATUS_OK ){
        if( i2c_data.status < I2C_STAT_MAX ){
            //SetLogDataM( LOG_DISP_I2C, &i2c_list[i2c_data.status].string[0],I2C_SSPSTAT,I2C_SSPCON1,I2C_SSPCON2,dt);
        }
        else{
            Xprintf("ERROR STATUS = %d\r\n",i2c_data.status);
        }
        I2C_ICIF = 0;
        //I2C_BCLIF = 0;

        I2C_TRN = dt;

        index = Set_Timer(100);
        while( I2C_ICIF == 0 ) {
            if(bcl_error_chk){
                //SetLogDataM( LOG_DISP_I2C, "ERR(BCL): WRITE",I2C_SSPSTAT,I2C_SSPCON1,I2C_SSPCON2,0);
                i2c_data.error = I2C_ERR_STAT_BCL;      
                status = STATUS_FAIL;    
            }
            if(I2C_IWCOL){
                //SetLogDataM( LOG_DISP_I2C, "ERR(WCOL): WRITE",I2C_SSPSTAT,I2C_SSPCON1,I2C_SSPCON2,0);
                I2C_IWCOL = 0;
                i2c_data.error = I2C_ERR_STAT_WCOL;        
                status = STATUS_FAIL;    
                break;           
            }
            if( Get_Timer(index) == 0 ){
                //SetLogDataM( LOG_DISP_I2C, "ERR(TOUT): WRITE",I2C_SSPSTAT,I2C_SSPCON1,I2C_SSPCON2,0);
                i2c_data.error = I2C_ERR_STAT_TIMEOUT;        
                status = STATUS_FAIL;    
                break;   
            }
        }
        Rel_Timer(index);
    
        if( status == STATUS_OK ){
            if( I2C_ACKSTAT ){
                //SetLogDataM( LOG_DISP_I2C, "ERR(NACK): WRITE",I2C_SSPSTAT,I2C_SSPCON1,I2C_SSPCON2,dt);
                i2c_data.error = I2C_ERR_STAT_NACK;
                status = STATUS_FAIL;    
            }
            else{
                //SetLogDataM( LOG_DISP_I2C, "WRITE ACK",I2C_SSPSTAT,I2C_SSPCON1,I2C_SSPCON2,dt);
            }
        }
    }
    
    return  status;
}

//=============================================================================
//
//=============================================================================
uint8_t i2c_read( uint8_t acknNak, uint8_t *dt )
{
    uint8_t status;
    int index;

    status = STATUS_OK ;    
    bcl_error_chk = 0;

    status = i2c_CheckIdleWait(0x05);

    if( status == STATUS_OK ){
        //SetLogDataM( LOG_DISP_I2C, "READ START",I2C_SSPSTAT,I2C_SSPCON1,I2C_SSPCON2,0);

        I2C_ICIF = 0;
        //I2C_BCLIF = 0;

        I2C_RCEN   = 1;

        index = Set_Timer(100);
        while(I2C_ICIF == 0 ){
            if(bcl_error_chk){
                //SetLogDataM( LOG_DISP_I2C, "ERR(BCL): READ",I2C_SSPSTAT,I2C_SSPCON1,I2C_SSPCON2,0);
                i2c_data.error = I2C_ERR_STAT_BCL;      
                status = STATUS_FAIL;    
            }
            if(I2C_IWCOL){
                //SetLogDataM( LOG_DISP_I2C, "ERR(WCOL): READ",I2C_SSPSTAT,I2C_SSPCON1,I2C_SSPCON2,0);
                I2C_IWCOL = 0;
                i2c_data.error = I2C_ERR_STAT_WCOL;        
                status = STATUS_FAIL;    
                break;           
            }
            if( Get_Timer(index) == 0 ){
                //SetLogDataM( LOG_DISP_I2C, "ERR(TOUT): READ",I2C_SSPSTAT,I2C_SSPCON1,I2C_SSPCON2,0);
                i2c_data.error = I2C_ERR_STAT_TIMEOUT;        
                status = STATUS_FAIL;    
                break;   
            }
        }
        Rel_Timer(index);
    }
    
    if( status == STATUS_OK ){
        *dt = I2C_RCV;
    
        status = i2c_CheckIdleWait(0x05);

        if( status == STATUS_OK ){
            I2C_ACKDT = acknNak ;        // ACKデータのセット
            I2C_ACKEN = 1 ;          // ACKデータを返す
        }
        //SetLogDataM( LOG_DISP_I2C, "READ END",I2C_SSPSTAT,I2C_SSPCON1,I2C_SSPCON2,*dt);
    }

    return  status;
}

//=============================================================================
//
//=============================================================================
int32_t i2c_writeMulti(uint8_t address,uint8_t reg, uint8_t *dst, uint8_t count)
{
    uint8_t i;
    uint8_t *dt;
    uint8_t status;
    int index;
    
    
    status = STATUS_OK ;    
    
  
    
    if( count > MAX_MULTI_CNT ){
        Xprintf("Error I2CData Size Over");
        status = STATUS_FAIL;          
    }
    else{
        
        //++++++++++++++++++++++++++++++++++++++++++++++++++
        // I2C START
        //++++++++++++++++++++++++++++++++++++++++++++++++++
        I2C_ON = 1;
        I2C_ACKDT =0;
        //++++++++++++++++++++++++++++++++++++++++++++++++++
        // データ設定
        //++++++++++++++++++++++++++++++++++++++++++++++++++

        i2c_data.address = address;
        i2c_data.index = reg;
        i2c_data.count = count;
        i2c_data.count_step = 0;
        i2c_data.restart_cnt = 0;
        i2c_data.op_type = I2C_WRITE_MULTI;
        i2c_data.status = I2C_STAT_START;
        i2c_data.error = I2C_NO_ERROR;

        for( i=0; i<count; i++ ){
            i2c_data.dt[i] = *dst;
//            Xprintf("dt=0x%x,",*dst);
            dst ++;
        }
//            Xprintf("\r\n");

        // 割込みフラグクリア
        I2C_ICIF = 0;
        //I2C_BCLIF = 0;

        // 割込みイネーブル
        I2C_ICIE = 0;
        //I2C_BCLIE = 1; 
        
        
        //++++++++++++++++++++++++++++++++++++++++++++++++++
        // 処理
        //++++++++++++++++++++++++++++++++++++++++++++++++++
        while( status == STATUS_OK ){
            //SetLogDataM( LOG_DISP_I2C_STAT, "STATUS",i2c_data.status,0,0,0);
            switch( i2c_data.status ){
                case I2C_STAT_START:
                    status = i2c_start();
                    if( status == STATUS_OK ){
                        i2c_data.status = I2C_STAT_WITE_ADDRESS_TX;
                    }
                    break;
                case I2C_STAT_WITE_ADDRESS_TX:
                    status = i2c_write(i2c_data.address);
                    if( status == STATUS_OK ){
                        i2c_data.status = I2C_STAT_INDEX_TX;
                    }
                    break;
                case I2C_STAT_INDEX_TX:
                    status = i2c_write(i2c_data.index);
                    if( status == STATUS_OK ){
                        i2c_data.status = I2C_STAT_DATA_TX;
                    }
                    break;
                case I2C_STAT_DATA_TX:
                    if( i2c_data.count_step < i2c_data.count ){
                        dt = i2c_data.dt[i2c_data.count_step];
                        i2c_data.count_step ++;
                        status = i2c_write(dt);
                    }

                    if( status == STATUS_OK ){
                        if( i2c_data.count_step >= i2c_data.count ){
                            i2c_data.status = I2C_STAT_STOP;
                        }
                    }
                    break;
                case I2C_STAT_STOP:
                    status = i2c_stop();
                    if( status == STATUS_OK ){
                        i2c_data.status = I2C_STAT_END;
                    }
                    break;
                default:
                    Xprintf("ERROR (WRITE MAIN) STATUS = %d\r\n",i2c_data.status);

                    break;
            }
            
            if( status == STATUS_OK ){
                if( i2c_data.status == I2C_STAT_END ){
                    // 正常終了
                    //SetLogDataM( LOG_DISP_NO_DATA, "I2C END",0,0,0,0);
                    break;
                }
            }
            else{
                // リカバリー処理　今は強制終了
                I2C_ON = 0;
                I2C_ICIE = 0;
//                I2C_BCLIE = 0; 
            
                //Wait(1);
                
                if(i2c_data.restart_cnt < I2C_RECOVRY_MAX){
                    i2c_data.restart_cnt ++;

                    
                    //++++++++++++++++++++++++++++++++++++++++++++++++++
                    // I2C START
                    //++++++++++++++++++++++++++++++++++++++++++++++++++
                    I2C_ON = 1;

                    //++++++++++++++++++++++++++++++++++++++++++++++++++
                    // データ設定
                    //++++++++++++++++++++++++++++++++++++++++++++++++++
                    status = STATUS_OK;

                    i2c_data.count_step = 0;
                    i2c_data.status = I2C_STAT_START;
                    i2c_data.error = I2C_NO_ERROR;

                    // 割込みフラグクリア
                    I2C_ICIF = 0;
                    //I2C_BCLIF = 0;

                    // 割込みイネーブル
                    I2C_ICIE = 0;
                    //I2C_BCLIE = 1; 
                    
                    //SetLogDataM( LOG_DISP_I2C, "RESTART",I2C_SSPSTAT,I2C_SSPCON1,I2C_SSPCON2,0);
                }
                else{
                    //SetLogDataM( LOG_DISP_I2C, "ERROR_END",I2C_SSPSTAT,I2C_SSPCON1,I2C_SSPCON2,0);
                }
            }
        }
    }   

    return  status;
}       
//=============================================================================
//
//=============================================================================
int32_t i2c_readMulti(uint8_t address,uint8_t reg, uint8_t *dst, uint8_t count)
{
    uint8_t i;
    uint8_t acknack;
    uint8_t status;
    
    status = STATUS_OK ;    


    if( count > MAX_MULTI_CNT ){
        Xprintf("Error I2CData Size Over");
        status = STATUS_FAIL;          
    }
    else{
        
        //++++++++++++++++++++++++++++++++++++++++++++++++++
        // I2C START
        //++++++++++++++++++++++++++++++++++++++++++++++++++
        I2C_ON = 1;
        I2C_ACKDT =0;

        //++++++++++++++++++++++++++++++++++++++++++++++++++
        // データ設定
        //++++++++++++++++++++++++++++++++++++++++++++++++++

        i2c_data.address = address;
        i2c_data.index = reg;
        i2c_data.count = count;
        i2c_data.count_step = 0;
        i2c_data.restart_cnt = 0;
        i2c_data.op_type = I2C_READ_MULTI;
        i2c_data.status = I2C_STAT_START;
        i2c_data.error = I2C_NO_ERROR;

        for( i=0; i<count; i++ ){
            i2c_data.dt[i] = 0;
        }

        // 割込みフラグクリア
        I2C_ICIF = 0;
        //I2C_BCLIF = 0;

        // 割込みイネーブル
        I2C_ICIE = 0;
        //I2C_BCLIE = 1; 
        
        
        //++++++++++++++++++++++++++++++++++++++++++++++++++
        // 処理
        //++++++++++++++++++++++++++++++++++++++++++++++++++
        while( status == STATUS_OK ){
            ////SetLogDataM( LOG_DISP_I2C_STAT, "STATUS",i2c_data.status,0,0,0);
            switch( i2c_data.status ){
                case I2C_STAT_START:
                    status = i2c_start();
                    if( status == STATUS_OK ){
                        i2c_data.status = I2C_STAT_WITE_ADDRESS_TX;
                    }
                    break;
                case I2C_STAT_WITE_ADDRESS_TX:
                    status = i2c_write(i2c_data.address);
                    if( status == STATUS_OK ){
                        i2c_data.status = I2C_STAT_INDEX_TX;
                    }
                    break;
                case I2C_STAT_INDEX_TX:
                    status = i2c_write(i2c_data.index);
                    if( status == STATUS_OK ){
                        i2c_data.status = I2C_STAT_SUSPEND;
                    }
                    break;
                case I2C_STAT_SUSPEND:
                    status = i2c_stop();
                    if( status == STATUS_OK ){
                        i2c_data.status = I2C_STAT_RESTART;
                    }
                    break;

                case I2C_STAT_RESTART:
                    status = i2c_start();
                    if( status == STATUS_OK ){
                        i2c_data.status = I2C_STAT_READ_ADDRESS_TX;
                    }
                    break;

                case I2C_STAT_READ_ADDRESS_TX:
                    status = i2c_write(i2c_data.address|0x01);
                    if( status == STATUS_OK ){
                        i2c_data.status = I2C_STAT_READ;
                    }
                    break;
                case I2C_STAT_READ:
                    
                    if( i2c_data.count_step < i2c_data.count ){
                        if( i2c_data.count_step  < (i2c_data.count-1) )
                            acknack = I2C_SEND_ACK;
                        else
                            acknack = I2C_SEND_NACK;
                       
                        status = i2c_read( acknack, &i2c_data.dt[i2c_data.count_step] );
                        i2c_data.count_step ++;
                    }
                    
                    if( status == STATUS_OK ){
                        if( i2c_data.count_step >= i2c_data.count ){
                            i2c_data.status = I2C_STAT_STOP;
                        }
                    }
                    break;
                case I2C_STAT_STOP:
                    status = i2c_stop();
                    if( status == STATUS_OK ){
                        i2c_data.status = I2C_STAT_END;
                    }
                    break;
                default:
                    Xprintf("ERROR (READ MAIN) STATUS = %d\r\n",i2c_data.status);
                    break;
            }
            
            if( status == STATUS_OK ){
                if( i2c_data.status == I2C_STAT_END ){
                    // 正常終了
                    //SetLogDataM( LOG_DISP_NO_DATA, "I2C END",0,0,0,0);
                    

                    for( i=0; i<i2c_data.count ; i++ ){
                        *dst = i2c_data.dt[i];
                        dst ++;
                    }
                    
                    break;
                }
            }
            else{
                // リカバリー処理　今は強制終了
                I2C_ON = 0;
                I2C_ICIE = 0;
                //I2C_BCLIE = 0; 

                
                //Wait(1);
                
                if(i2c_data.restart_cnt <I2C_RECOVRY_MAX){
                    i2c_data.restart_cnt ++;

                    //++++++++++++++++++++++++++++++++++++++++++++++++++
                    // I2C START
                    //++++++++++++++++++++++++++++++++++++++++++++++++++
                    I2C_ON = 1;

                    //++++++++++++++++++++++++++++++++++++++++++++++++++
                    // データ設定
                    //++++++++++++++++++++++++++++++++++++++++++++++++++
                    status = STATUS_OK;
                    i2c_data.count_step = 0;
                    i2c_data.status = I2C_STAT_START;
                    i2c_data.error = I2C_NO_ERROR;

                    // 割込みフラグクリア
                    I2C_ICIF = 0;
                    //I2C_BCLIF = 0;

                    // 割込みイネーブル
                    I2C_ICIE = 0;
                    //I2C_BCLIE = 1; 

                    //SetLogDataM( LOG_DISP_I2C, "RESTART",I2C_SSPSTAT,I2C_SSPCON1,I2C_SSPCON2,0);
                }
                else{
                    //SetLogDataM( LOG_DISP_I2C, "ERROR_END",I2C_SSPSTAT,I2C_SSPCON1,I2C_SSPCON2,0);
                }
            }
        }
    }   

    return  status;
}       
