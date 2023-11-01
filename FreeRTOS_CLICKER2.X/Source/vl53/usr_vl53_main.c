/*
 * usr_vl53_main.c
 *
 *  Created on: Aug 10, 2023
 *      Author: nosak
 */

//==============================================================================
// include
//==============================================================================
#include "FreeRTOS.h"
#include "usr_system.h"
#include "vl53l0x_api.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

uint16_t usrLogSW_VL53 = 0;


//==============================================================================
// define
//==============================================================================
#define VERSION_REQUIRED_MAJOR 1 ///< Required sensor major version
#define VERSION_REQUIRED_MINOR 0 ///< Required sensor minor version
#define VERSION_REQUIRED_BUILD 4 ///< Required sensor build

//==============================================================================
// Variable
//==============================================================================
#ifdef ___NOP
uint8_t 	Message[64];
uint8_t 	MessageLen;

uint32_t 	refSpadCount;

uint8_t 	isApertureSpads;
uint8_t 	VhvSettings;
uint8_t 	PhaseCal;

VL53L0X_RangingMeasurementData_t 	RangingData;
#endif
//VL53L0X_Dev_t  						vl53l0x_c; // center module
VL53L0X_Dev_t   MyDevice;
VL53L0X_DEV    						Dev = &MyDevice;





USR_VL53_DATA   usrVL53Ctrl;




//==============================================================================
// Extern Variable
//==============================================================================
extern      USR_RTC_DATA        usrSRTC;
//==============================================================================
// prototypes
//==============================================================================
void vl53_main(void);
void SystemClock_Config(void);
void vl53l0x_Racing_test(RASING_MODE sel);
void usrVl53l0x_Racing_test(RASING_MODE sel);
void Xprintf(const char *string, ...);

void print_range_status(VL53L0X_RangingMeasurementData_t* pRangingMeasurementData);
void print_pal_error(VL53L0X_Error Status,uint16_t  line);
void i2c_init(void);
VL53L0X_Error WaitStopCompleted(VL53L0X_DEV Dev) ;
VL53L0X_Error WaitMeasurementDataReady(VL53L0X_DEV Dev) ;

VL53L0X_Error usrSinglRanging(VL53L0X_Dev_t *pMyDevice, RASING_MODE sel);
void usrMessage_send(const char *string, ...);
void    teset_msg(void);


//=============================================================================
//  vTask001
//=============================================================================
void vTask001(void *pvParameters) 
{
    VL53L0X_Error                       Status = VL53L0X_ERROR_NONE;;
    VL53L0X_RangingMeasurementData_t    RangingMeasurementData;
    FixPoint1616_t                      LimitCheckCurrent;
    VL53L0X_RangingMeasurementData_t   *pRangingMeasurementData    = &RangingMeasurementData;
        
    Xprintf("vTask001()\r\n");
    i2c_init();
    usrVL53Ctrl.RasingMode = RASING_MODE_NON;
    usrVL53Ctrl.Status = 0;
    usrVL53Ctrl.StopReq = 0;
    usrVL53Ctrl.MesurData = -1;
    usrVL53Ctrl.StartRasingMode = RASING_MODE_NON;
    
    vTaskDelay(100);    


    usrMessage_send("TEST MESSAGE from Task001\r\n");
    
    vTaskDelay(100);    

   // teset_msg();
    

    while(1){
        while(usrVL53Ctrl.RasingMode == RASING_MODE_NON) {
            usrVL53Ctrl.RasingMode = usrVL53Ctrl.StartRasingMode;
            vTaskDelay(100);    
        }
        
        LOG_PRINT_VL53("usrVL53Ctrl.RasingMode=%d\r\n",usrVL53Ctrl.RasingMode);

        switch(usrVL53Ctrl.RasingMode){
        case RASING_MODE_SINGLE :
            Xprintf("RASING_MODE_SINGLE\r\n");
            break;
        case RASING_MODE_SINGLE_HA:
            Xprintf("RASING_MODE_SINGLE_HA\r\n");
            break;
        case RASING_MODE_SINGLE_HS:
            Xprintf("RASING_MODE_SINGLE_HS\r\n");
            break;
        case RASING_MODE_SINGLE_LR:
            Xprintf("RASING_MODE_SINGLE_LR\r\n");
            break;
        case RASING_MODE_CONTINUE:
            Xprintf("RASING_MODE_CONTINUE\r\n");
            break;
        }
        usrVl53l0x_Racing_test(usrVL53Ctrl.RasingMode);

        if(usrVL53Ctrl.RasingMode == RASING_MODE_CONTINUE ){
                if(Status == VL53L0X_ERROR_NONE){
                    /*
                     * < VL53L0X_StartMeasurement() >
                     * デバイスの測定を開始します。
                     * 開始される測定は、VL53L0X_SetParameters() で設定されたデバイスパラメータに依存します。
                     * これはノンブロッキング関数です。
                     * この関数は、VL53L0X_State を VL53L0X_STATE_IDLE から VL53L0X_STATE_RUNNING に変更します。
                     */
                    Status = VL53L0X_StartMeasurement(&MyDevice);
                    print_pal_error(Status,__LINE__);
                }

                usrVL53Ctrl.StopReq = 0;
                while( usrVL53Ctrl.StopReq == 0 ) {
                    Status = WaitMeasurementDataReady(&MyDevice);
                    if(Status != VL53L0X_ERROR_NONE){
                        Xprintf("Error:%d  WaitMeasurementDataReady(line%d)\r\n",Status,__LINE__);
                    }
                    
                    if(Status == VL53L0X_ERROR_NONE){
                        /*
                         * < VL53L0X_GetRangingMeasurementData() >
                         * 特定のセットアップのデバイスから測定値を取得します。
                         * 機能の説明
                         * 最後に成功したレンジング測定からデータを取得する
                         *
                         * 警告：
                         * USER はデータを取得する前に VL53L0X_GetNumberOfROIZones() に
                         * 注意する必要があります。 PAL は、測定関数で使用される
                         * 対応するデータ構造に NumberOfROIZones を掛けた値を埋めます。
                         */
                        Status = VL53L0X_GetRangingMeasurementData(&MyDevice, pRangingMeasurementData);
                        if(Status != VL53L0X_ERROR_NONE){
                            Xprintf("Error:%d  GetRangingMeasurementData(line%d)\r\n",Status,__LINE__);
                        }
                        

                        usrVL53Ctrl.MesurData = pRangingMeasurementData->RangeMilliMeter;
                        Xprintf("%2d %3d.%3d MesurData: %d\r\n", usrSRTC.sec, usrSRTC.msec, usrSRTC.usec, usrVL53Ctrl.MesurData);

                        /*
                         * <VL53L0X_ClearInterruptMask()>
                         * 指定されたシステム割り込み条件をクリアします。
                         * 指定された割り込みをクリアします。
                         */
                        VL53L0X_ClearInterruptMask(&MyDevice, VL53L0X_REG_SYSTEM_INTERRUPT_GPIO_NEW_SAMPLE_READY);
                        VL53L0X_PollingDelay(&MyDevice);
                    }
                    else {
                        break;
                    }
                }


                if(Status == VL53L0X_ERROR_NONE){
                    /*
                     * <VL53L0X_StopMeasurement()>
                     * デバイスの測定を停止します。
                     * 電流測定の終了時にデバイスをスタンバイモードに設定します
                     * シングルモードでは、測定終了時にデバイスが自動的にスタンバイモードに
                     * 戻るため、必要ありません。 この関数は、VL53L0X_State を
                     * VL53L0X_STATE_RUNNING から VL53L0X_STATE_IDLE に変更します。
                     */
                    Status = VL53L0X_StopMeasurement(&MyDevice);
                    if(Status != VL53L0X_ERROR_NONE){
                        Xprintf("Error:%d  StopMeasurement(line%d)\r\n",Status,__LINE__);
                    }
                }

                if(Status == VL53L0X_ERROR_NONE){
                    Status = WaitStopCompleted(&MyDevice);
                    if(Status != VL53L0X_ERROR_NONE){
                        Xprintf("Error:%d  WaitStopCompleted(line%d)\r\n",Status,__LINE__);
                    }
                }

                if(Status == VL53L0X_ERROR_NONE){
                    /*
                     * <VL53L0X_ClearInterruptMask()>
                     * 指定されたシステム割り込み条件をクリアします。
                     * 指定された割り込みをクリアします。
                     */
                    Status = VL53L0X_ClearInterruptMask(&MyDevice,VL53L0X_REG_SYSTEM_INTERRUPT_GPIO_NEW_SAMPLE_READY);
                    if(Status != VL53L0X_ERROR_NONE){
                        Xprintf("Error:%d  ClearInterruptMask(line%d)\r\n",Status,__LINE__);
                    }
                }
        }
        else{
            Status = usrSinglRanging(&MyDevice, usrVL53Ctrl.RasingMode);
            if(Status != VL53L0X_ERROR_NONE){
                Xprintf("Error:%d  usrSinglRanging(line%d)\r\n",Status,__LINE__);
            }

            usrVL53Ctrl.StopReq = 0;
            while( usrVL53Ctrl.StopReq == 0 ) {
                if(Status == VL53L0X_ERROR_NONE){
                    /*
                    * <VL53L0X_PerformSingleRangingMeasurement()>
                    * 単一の測距測定を実行し、測距測定データを取得します。
                    * 機能の説明
                    * この関数は、 VL53L0X_SetDeviceMode() でデバイス モードを
                    * VL53L0X_DEVICEMODE_SINGLE_RANGING に変更します。
                    * VL53L0X_PerformSingleMeasurement() で測定を実行します。
                    * VL53L0X_GetRangingMeasurementData で最後に成功したレンジング
                    * 測定からデータを取得します。
                    * 最後に、 VL53L0X_ClearInterruptMask() で割り込みをクリアします。
                    *
                    * ノート：
                    * この機能はデバイスへのアクセスです
                    * この関数はデバイス モードを VL53L0X_DEVICEMODE_SINGLE_RANGING に変更します。
                    *
                    */
                    Status = VL53L0X_PerformSingleRangingMeasurement(&MyDevice, &RangingMeasurementData);
                    
                    usrVL53Ctrl.MesurData = pRangingMeasurementData->RangeMilliMeter;
                    Xprintf("MesurData: %d\r\n", usrVL53Ctrl.MesurData);
                    
                    print_pal_error(Status,__LINE__);
                    print_range_status(&RangingMeasurementData);

                    /*
                     * <VL53L0X_GetLimitCheckCurrent()>
                     * リミットチェックに使用される信号の現在値を取得します。
                     * 機能の説明
                     * この関数は、リミットチェックに使用される信号の現在値を取得します。
                     * 最新の値を取得するには、事前にレンジングを実行する必要があります。
                     * 報告される値は、LimitCheckId で識別される制限チェックにリンクされます。
                     * ノート：
                     * この機能はデバイスへのアクセスです
                     */
                    switch(usrVL53Ctrl.RasingMode){
                    case RASING_MODE_SINGLE:
                    case RASING_MODE_SINGLE_HA:
                    case RASING_MODE_SINGLE_HS:
                        VL53L0X_GetLimitCheckCurrent(&MyDevice, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, &LimitCheckCurrent);
                        LOG_PRINT_VL53(",RANGE IGNORE THRESHOLD: %f\r\n", (float)LimitCheckCurrent/65536.0);
                        break;
                   case RASING_MODE_SINGLE_LR:
                       LOG_PRINT_VL53("\r\n");
                    default:
                        break;
                    }


                    if (Status != VL53L0X_ERROR_NONE){
                        break;
                    }
                }
            }
        }
        
        usrVL53Ctrl.Status = Status;
        usrVL53Ctrl.RasingMode = RASING_MODE_NON;
        usrVL53Ctrl.StopReq = 0;
    }
}


//==============================================================================
//
//==============================================================================
void print_pal_error(VL53L0X_Error Status,uint16_t  line)
{
    char buf[VL53L0X_MAX_STRING_LENGTH];

    if( Status != 0 ){
        VL53L0X_GetPalErrorString(Status, buf);
        Xprintf("API Status: %i : %s(line%d)\r\n", Status, buf,line);

    }
}
//==============================================================================
//
//==============================================================================


//==============================================================================
//
//==============================================================================
#ifdef ___NOP

#endif
//==============================================================================
//
//==============================================================================
void vl53_LogDisp(char *string,int8_t status)
{
#ifdef ___VL53_LOG_DISP
    //Xprintf("%s ++++++++++++++++++++++++++++++ STATUS = %d\r\n",string, status);
#endif
}

//==============================================================================
//
//==============================================================================
VL53L0X_Error WaitStopCompleted(VL53L0X_DEV Dev) 
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    uint32_t StopCompleted=0;
    uint32_t LoopNb;

    // Wait until it finished
    // use timeout to avoid deadlock
    if (Status == VL53L0X_ERROR_NONE) {
        LoopNb = 0;
        do {
            Status = VL53L0X_GetStopCompletedStatus(Dev, &StopCompleted);
            if ((StopCompleted == 0x00) || Status != VL53L0X_ERROR_NONE) {
                break;
            }
            LoopNb = LoopNb + 1;
            VL53L0X_PollingDelay(Dev);
        } while (LoopNb < VL53L0X_DEFAULT_MAX_LOOP);

        if (LoopNb >= VL53L0X_DEFAULT_MAX_LOOP) {
            Status = VL53L0X_ERROR_TIME_OUT;
        }

    }

    return Status;
}

//==============================================================================
//
//==============================================================================

void print_range_status(VL53L0X_RangingMeasurementData_t* pRangingMeasurementData)
{
    char buf[VL53L0X_MAX_STRING_LENGTH];
    uint8_t RangeStatus;

    /*
     * New Range Status: data is valid when pRangingMeasurementData->RangeStatus = 0
     */

    RangeStatus = pRangingMeasurementData->RangeStatus;

    VL53L0X_GetRangeStatusString(RangeStatus, buf);
    LOG_PRINT_VL53(" Range Status: %d : %s ", RangeStatus, (char *)buf);

}


//==============================================================================
//
//==============================================================================

VL53L0X_Error WaitMeasurementDataReady(VL53L0X_DEV Dev) 
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    uint8_t NewDatReady=0;
    uint32_t LoopNb;

    LOG_PRINT_VL53("WaitMeasurementDataReady()\r\n");

    
    // Wait until it finished
    // use timeout to avoid deadlock
    if (Status == VL53L0X_ERROR_NONE) {
        LoopNb = 0;
        do {
            /*
             * <VL53L0X_GetMeasurementDataReady()>
             * 測定データを返す準備ができました。
             * 機能の説明
             * この関数は、測定データが準備できたことを示します。
             * この関数は、割り込みモードが使用されているかどうかをチェックし、
             * それに応じてチェックが行われます。 Perform 関数が割り込みをクリアした
             * 場合、 VL53L0X_PerformSingleRangingMeasurement() の場合と同様、
             * この関数は動作しません。
             * 前の関数はブロッキング関数でしたが、VL53L0X_GetMeasurementDataReady
             * はノンブロッキング キャプチャに使用されます。
             *
             * ノート：
             * この機能はデバイスへのアクセスです
             *
             * パラメーター：
             * デバイスハンドル
             * 測定データ準備完了へのポインタ。
             *   0=データの準備ができていない、1=データの準備ができている
             */
            Status = VL53L0X_GetMeasurementDataReady(Dev, &NewDatReady);
            if ((NewDatReady == 0x01) || Status != VL53L0X_ERROR_NONE) {
                break;
            }
            LoopNb = LoopNb + 1;
            VL53L0X_PollingDelay(Dev);
        } while (LoopNb < VL53L0X_DEFAULT_MAX_LOOP);

        if (LoopNb >= VL53L0X_DEFAULT_MAX_LOOP) {
            Status = VL53L0X_ERROR_TIME_OUT;
        }
    }

    return Status;
}

//==============================================================================
//
// sel : 0 SINGLE RACING
//       1 SINGLE RACING HA
//       2 SINGLE RACING HS
//       3 SINGLE RACING LR
//       4 CONTINUE RASING
//
//==============================================================================
#ifdef  ___NOP2
VL53L0X_Error SK_RangingTest2(VL53L0X_Dev_t *pMyDevice, RASING_MODE sel)
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    VL53L0X_RangingMeasurementData_t    RangingMeasurementData;
    VL53L0X_RangingMeasurementData_t   *pRangingMeasurementData    = &RangingMeasurementData;
    int i;
    int max;
    FixPoint1616_t LimitCheckCurrent;

    uint32_t refSpadCount;
    uint8_t isApertureSpads;
    uint8_t VhvSettings;
    uint8_t PhaseCal;

    /*
     * <VL53L0X_StaticInit()>
     * 基本的なデバイスの初期化 (最終的にはパッチのロード) を実行します。
     * この関数は、VL53L0X_State を VL53L0X_STATE_WAIT_STATICINIT から VL53L0X_STATE_IDLE に変更します。
     * この段階では、すべてのデフォルト設定が適用されます。
     */
    if(Status == VL53L0X_ERROR_NONE)
    {
        LOG_PRINT_VL53 ("1 VL53L0X_StaticInit()\r\n\n");
        Status = VL53L0X_StaticInit(pMyDevice); // Device Initialization
        print_pal_error(Status,__LINE__);
    }


    if(Status == VL53L0X_ERROR_NONE)
    {
        LOG_PRINT_VL53 ("2 VL53L0X_PerformRefCalibration()\r\n\n");
        Status = VL53L0X_PerformRefCalibration(pMyDevice, &VhvSettings, &PhaseCal); // Device Initialization
        print_pal_error(Status,__LINE__);
    }

    if(Status == VL53L0X_ERROR_NONE)
    {
        LOG_PRINT_VL53 ("3 VL53L0X_PerformRefSpadManagement()\r\n\n");
        Status = VL53L0X_PerformRefSpadManagement(pMyDevice, &refSpadCount, &isApertureSpads); // Device Initialization

        print_pal_error(Status,__LINE__);
    }

    if(Status == VL53L0X_ERROR_NONE)
    {

        LOG_PRINT_VL53 ("4 VL53L0X_SetDeviceMode()\r\n\n");
        Status = VL53L0X_SetDeviceMode(pMyDevice, VL53L0X_DEVICEMODE_SINGLE_RANGING); // Setup in single ranging mode


        print_pal_error(Status,__LINE__);
    }

    /*
     * <VL53L0X_SetSequenceStepEnable()>
     * 要求されたシーケンス ステップの (オン/オフ) 状態を設定します。
     * 機能の説明
     * この機能は、要求されたシーケンス ステップを有効または無効にします。
     * ノート：
     * この機能はデバイスにアクセスします
     * パラメーター：
     *   Device Handle
     *   Sequence step identifier.
     *   Demanded state {0=Off,1=On} is enabled.     *
     */
    if (Status == VL53L0X_ERROR_NONE) {
        if(sel == RASING_MODE_SINGLE_LR){
            //Status = VL53L0X_SetSequenceStepEnable(pMyDevice,VL53L0X_SEQUENCESTEP_DSS, 1);
        }
    }


   
    /*
     * < VL53L0X_SetLimitCheckEnable() >
     * Enable/Disable Sigma and Signal check
     * 特定の制限チェックを有効/無効にします。
     * 機能の説明
     * この機能は、特定の制限チェックを有効/無効にします。
     * 制限チェックは LimitCheckId で識別されます。
     */

    if (Status == VL53L0X_ERROR_NONE) {
        LOG_PRINT_VL53 ("5 VL53L0X_SetLimitCheckEnable()\r\n\n");
        Status = VL53L0X_SetLimitCheckEnable(pMyDevice, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1);
    }

    if (Status == VL53L0X_ERROR_NONE) {
        LOG_PRINT_VL53 ("6 VL53L0X_SetLimitCheckEnable()\r\n\n");
        Status = VL53L0X_SetLimitCheckEnable(pMyDevice, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1);
    }

    if (Status == VL53L0X_ERROR_NONE) {
        if(sel == RASING_MODE_SINGLE){
            LOG_PRINT_VL53 ("7 VL53L0X_SetLimitCheckEnable()\r\n\n");
            Status = VL53L0X_SetLimitCheckEnable(pMyDevice, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, 1);
        }
    }

    /*
     * < VL53L0X_SetLimitCheckValue() >
     * 特定の制限チェック値を設定します。
     * 機能の説明
     * この関数は、特定の制限チェック値を設定します。
     * 制限チェックは LimitCheckId で識別されます。
     */
    switch(sel){
    case RASING_MODE_SINGLE:
        if (Status == VL53L0X_ERROR_NONE) {
            LOG_PRINT_VL53 ("8 VL53L0X_SetLimitCheckValue()\r\n\n");
            Status = VL53L0X_SetLimitCheckValue(pMyDevice, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, (FixPoint1616_t)(1.5*0.023*65536));
        }
         break;
    case RASING_MODE_SINGLE_HA:
        if (Status == VL53L0X_ERROR_NONE) {
            Status = VL53L0X_SetLimitCheckValue(pMyDevice, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, (FixPoint1616_t)(0.25*65536));
        }
        if (Status == VL53L0X_ERROR_NONE) {
            Status = VL53L0X_SetLimitCheckValue(pMyDevice, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, (FixPoint1616_t)(18*65536));
        }
        break;
    case RASING_MODE_SINGLE_HS:
        if (Status == VL53L0X_ERROR_NONE) {
            Status = VL53L0X_SetLimitCheckValue(pMyDevice, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, (FixPoint1616_t)(0.25*65536));
        }
        if (Status == VL53L0X_ERROR_NONE) {
            Status = VL53L0X_SetLimitCheckValue(pMyDevice, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, (FixPoint1616_t)(32*65536));
        }

        break;
    case RASING_MODE_SINGLE_LR:
        if (Status == VL53L0X_ERROR_NONE) {
            Status = VL53L0X_SetLimitCheckValue(pMyDevice, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, (FixPoint1616_t)(0.1*65536));
        }
        if (Status == VL53L0X_ERROR_NONE) {
            Status = VL53L0X_SetLimitCheckValue(pMyDevice, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, (FixPoint1616_t)(60*65536));
        }

        break;
    default:
        break;
    }

    /*
     * <>
     * レンジング タイミング バジェットをマイクロ秒単位で設定します。
     * 機能の説明
     * 現在のモード (レンジング、ヒストグラム、ASL ...) のフルレンジング シーケンスを
     * 実行するためにユーザーがデバイスに許可する最大時間を定義します。
     */
    switch(sel){
    case RASING_MODE_SINGLE:
         break;
    case RASING_MODE_SINGLE_HA:
        if (Status == VL53L0X_ERROR_NONE) {
            Status = VL53L0X_SetMeasurementTimingBudgetMicroSeconds(pMyDevice, 200000);
        }
        break;
    case RASING_MODE_SINGLE_HS:
        if (Status == VL53L0X_ERROR_NONE) {
            Status = VL53L0X_SetMeasurementTimingBudgetMicroSeconds(pMyDevice, 30000);
        }
        break;
   case RASING_MODE_SINGLE_LR:
        if (Status == VL53L0X_ERROR_NONE) {
            Status = VL53L0X_SetMeasurementTimingBudgetMicroSeconds(pMyDevice, 33000);
        }
        break;
    default:
        break;
    }

    /*
     * < VL53L0X_SetVcselPulsePeriod() >
     * VCSEL パルス周期を設定します。
     * 機能の説明
     * この関数は、指定された周期タイプの VCSEL パルス周期を取得します。
     */
    switch(sel){
    case RASING_MODE_SINGLE:
         break;
    case RASING_MODE_SINGLE_HA:
        break;
    case RASING_MODE_SINGLE_HS:
        break;
   case RASING_MODE_SINGLE_LR:
        if (Status == VL53L0X_ERROR_NONE) {
            Status = VL53L0X_SetVcselPulsePeriod(pMyDevice, VL53L0X_VCSEL_PERIOD_PRE_RANGE, 18);
        }
        if (Status == VL53L0X_ERROR_NONE) {
            Status = VL53L0X_SetVcselPulsePeriod(pMyDevice, VL53L0X_VCSEL_PERIOD_FINAL_RANGE, 14);
        }
        break;
    default:
        break;
    }

    if(sel==RASING_MODE_SINGLE_LR){
        max = 50;
    }
    else{
        max = 10;
    }


    //Xprintf("001 Range MilliMeter= %d(%d)\r\n",RangingMeasurementData.RangeMilliMeter,pMyDevice->Data.LastRangeMeasure.RangeMilliMeter);



    if(Status == VL53L0X_ERROR_NONE){
        for( i=0; i<max; i++ ){

            /*
             * <VL53L0X_PerformSingleRangingMeasurement()>
             * 単一の測距測定を実行し、測距測定データを取得します。
             * 機能の説明
             * この関数は、 VL53L0X_SetDeviceMode() でデバイス モードを
             * VL53L0X_DEVICEMODE_SINGLE_RANGING に変更します。
             * VL53L0X_PerformSingleMeasurement() で測定を実行します。
             * VL53L0X_GetRangingMeasurementData で最後に成功したレンジング
             * 測定からデータを取得します。
             * 最後に、 VL53L0X_ClearInterruptMask() で割り込みをクリアします。
             *
             * ノート：
             * この機能はデバイスへのアクセスです
             * この関数はデバイス モードを VL53L0X_DEVICEMODE_SINGLE_RANGING に変更します。
             *
             */
            ////Xprintf ("Call of VL53L0X_PerformSingleRangingMeasurement\r\n");
            //LOG_PRINT_VL53 ("9 VL53L0X_PerformSingleRangingMeasurement()\r\n\n");
            Status = VL53L0X_PerformSingleRangingMeasurement(pMyDevice, &RangingMeasurementData);
            Xprintf("Range MilliMeter = %d(%d),",RangingMeasurementData.RangeMilliMeter,pMyDevice->Data.LastRangeMeasure.RangeMilliMeter);

            print_pal_error(Status,__LINE__);
            print_range_status(&RangingMeasurementData);

            /*
             * <VL53L0X_GetLimitCheckCurrent()>
             * リミットチェックに使用される信号の現在値を取得します。
             * 機能の説明
             * この関数は、リミットチェックに使用される信号の現在値を取得します。
             * 最新の値を取得するには、事前にレンジングを実行する必要があります。
             * 報告される値は、LimitCheckId で識別される制限チェックにリンクされます。
             * ノート：
             * この機能はデバイスへのアクセスです
             */
            switch(sel){
            case RASING_MODE_SINGLE:
            case RASING_MODE_SINGLE_HA:
            case RASING_MODE_SINGLE_HS:
                VL53L0X_GetLimitCheckCurrent(pMyDevice, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, &LimitCheckCurrent);
                Xprintf(",RANGE IGNORE THRESHOLD: %f\r\n", (float)LimitCheckCurrent/65536.0);
                break;
           case RASING_MODE_SINGLE_LR:
               Xprintf("\r\n");
            default:
                break;
            }

            ////Xprintf("003 Range MilliMeter = %d(%d)\r\n",RangingMeasurementData.RangeMilliMeter,pMyDevice->Data.LastRangeMeasure.RangeMilliMeter) ;


            if (Status != VL53L0X_ERROR_NONE){
                break;
            }

            ////Xprintf("Measured distance: %i\r\n", RangingMeasurementData.RangeMilliMeter);
        }

    }
   
    LOG_PRINT_VL53 ("SK_RangingTest() End\r\n\n");

    return Status;

}

//==============================================================================
//
// sel : 0 SINGLE RACING
//       1 SINGLE RACING HA
//       2 SINGLE RACING HS
//       3 SINGLE RACING LR
//
//==============================================================================
void vl53l0x_Racing_test2(RASING_MODE sel)
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
//    VL53L0X_Dev_t MyDevice;
    VL53L0X_Dev_t *pMyDevice = &MyDevice;
    VL53L0X_Version_t                   Version;
    VL53L0X_Version_t                  *pVersion   = &Version;
    VL53L0X_DeviceInfo_t                DeviceInfo;

    int32_t status_int;
    int32_t init_done = 0;
    int NecleoComStatus = 0;
    int NecleoAutoCom = 1;

    LOG_PRINT_VL53 ("vl53l0x_Racing_test()\r\n\n");

//    MyDevice.I2cHandle = &hi2c1;
    MyDevice.I2cDevAddr = 0x52;
    pMyDevice->I2cDevAddr      = 0x52;

    /*
     *  Get the version of the VL53L0X API running in the firmware
     */

    if(Status == VL53L0X_ERROR_NONE){
        status_int = VL53L0X_GetVersion(pVersion);
        if (status_int != 0){
            Status = VL53L0X_ERROR_CONTROL_INTERFACE;
            LOG_PRINT_VL53 ("Error:VL53L0X_GetVersion()\r\n\n");
        }
        else{
            //  Verify the version of the VL53L0X API running in the firmware
            if( pVersion->major != VERSION_REQUIRED_MAJOR ||
                pVersion->minor != VERSION_REQUIRED_MINOR ||
                pVersion->build != VERSION_REQUIRED_BUILD )
            {
                LOG_PRINT_VL53("VL53L0X API Version Error: Your firmware has %d.%d.%d (revision %d). This example requires %d.%d.%d.\r\n",
                    pVersion->major, pVersion->minor, pVersion->build, pVersion->revision,
                    VERSION_REQUIRED_MAJOR, VERSION_REQUIRED_MINOR, VERSION_REQUIRED_BUILD);
            }
        }
    }

    /*
     * 機能の説明
     * 新しいデバイスの「電源投入」またはリセット後に使用されていない場合、
     * VL53L0X_ERROR_CALIBRATION_WARNING が返される場合があります。
     * これは、間違ったキャリブレーション データがデバイスからフェッチされた
     * 可能性があり、レンジング オフセット エラーが発生する可能性があります。
     *
     * アプリケーションがデバイスリセットを実行できない場合、または VL53L0X_DataInitを
     * 複数回実行する必要がある場合は、最初の電源投入時に
     * VL53L0X_GetOffsetCalibrationData() を使用し、その後すべての初期化で
     * VL53L0X_SetOffsetCalibrationData() を使用して、適切なオフセットキャリブレーションの保存と
     * 復元を独自に行う必要があります。
     * この関数は VL53L0X_State を変更します。
     * VL53L0X_STATE_POWERDOWN から VL53L0X_STATE_WAIT_STATICINIT まで。
     */
    if(Status == VL53L0X_ERROR_NONE){
        //Xprintf ("Call of VL53L0X_DataInit\r\n");
        LOG_PRINT_VL53 ("VL53L0X_DataInit()\r\n\n");
        Status = VL53L0X_DataInit(&MyDevice); // Data initialization
        print_pal_error(Status,__LINE__);
    }

    if(Status == VL53L0X_ERROR_NONE){
        LOG_PRINT_VL53 ("VL53L0X_GetDeviceInfo()\r\n\n");
        Status = VL53L0X_GetDeviceInfo(&MyDevice, &DeviceInfo);

        if(Status == VL53L0X_ERROR_NONE){
            //Xprintf("VL53L0X_GetDeviceInfo:\r\n");
            //Xprintf("Device Name : %s\r\n", DeviceInfo.Name);
            //Xprintf("Device Type : %s\r\n", DeviceInfo.Type);
            //Xprintf("Device ID : %s\r\n", DeviceInfo.ProductId);
            //Xprintf("ProductRevisionMajor : %d\r\n", DeviceInfo.ProductRevisionMajor);
            //Xprintf("ProductRevisionMinor : %d\r\n", DeviceInfo.ProductRevisionMinor);

            if ((DeviceInfo.ProductRevisionMinor != 1) && (DeviceInfo.ProductRevisionMinor != 1)) {
            	//Xprintf("Error expected cut 1.1 but found cut %d.%d\r\n",DeviceInfo.ProductRevisionMajor, DeviceInfo.ProductRevisionMinor);
                Status = VL53L0X_ERROR_NOT_SUPPORTED;
            }
        }
        print_pal_error(Status,__LINE__);
    }

    if(Status == VL53L0X_ERROR_NONE){
        LOG_PRINT_VL53 ("SK_RangingTest()\r\n\n");
        Status = SK_RangingTest( pMyDevice,sel);
    }
    
    print_pal_error(Status,__LINE__);
    
    LOG_PRINT_VL53 ("vl53l0x_Racing_test() End\r\n\n");

}
#endif


//==============================================================================
//
// sel : 0 SINGLE RACING
//       1 SINGLE RACING HA
//       2 SINGLE RACING HS
//       3 SINGLE RACING LR
//       4 CONTINUE RASING
//
//==============================================================================

VL53L0X_Error usrSinglRanging(VL53L0X_Dev_t *pMyDevice, RASING_MODE sel)
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    VL53L0X_RangingMeasurementData_t    RangingMeasurementData;
    VL53L0X_RangingMeasurementData_t   *pRangingMeasurementData    = &RangingMeasurementData;
    int i;
    int max;
    FixPoint1616_t LimitCheckCurrent;




    /*
     * < VL53L0X_SetLimitCheckEnable() >
     * Enable/Disable Sigma and Signal check
     * 特定の制限チェックを有効/無効にします。
     * 機能の説明
     * この機能は、特定の制限チェックを有効/無効にします。
     * 制限チェックは LimitCheckId で識別されます。
     */

    if (Status == VL53L0X_ERROR_NONE) {
        Status = VL53L0X_SetLimitCheckEnable(pMyDevice, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1);
    }

    if (Status == VL53L0X_ERROR_NONE) {
        Status = VL53L0X_SetLimitCheckEnable(pMyDevice, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1);
    }

    if (Status == VL53L0X_ERROR_NONE) {
        if(sel == RASING_MODE_SINGLE){
            Status = VL53L0X_SetLimitCheckEnable(pMyDevice, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, 1);
        }
    }

    /*
     * < VL53L0X_SetLimitCheckValue() >
     * 特定の制限チェック値を設定します。
     * 機能の説明
     * この関数は、特定の制限チェック値を設定します。
     * 制限チェックは LimitCheckId で識別されます。
     */
    switch(sel){
    case RASING_MODE_SINGLE:
        if (Status == VL53L0X_ERROR_NONE) {
            Status = VL53L0X_SetLimitCheckValue(pMyDevice, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, (FixPoint1616_t)(1.5*0.023*65536));
        }
         break;
    case RASING_MODE_SINGLE_HA:
        if (Status == VL53L0X_ERROR_NONE) {
            Status = VL53L0X_SetLimitCheckValue(pMyDevice, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, (FixPoint1616_t)(0.25*65536));
        }
        if (Status == VL53L0X_ERROR_NONE) {
            Status = VL53L0X_SetLimitCheckValue(pMyDevice, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, (FixPoint1616_t)(18*65536));
        }
        break;
    case RASING_MODE_SINGLE_HS:
        if (Status == VL53L0X_ERROR_NONE) {
            Status = VL53L0X_SetLimitCheckValue(pMyDevice, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, (FixPoint1616_t)(0.25*65536));
        }
        if (Status == VL53L0X_ERROR_NONE) {
            Status = VL53L0X_SetLimitCheckValue(pMyDevice, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, (FixPoint1616_t)(32*65536));
        }

        break;
    case RASING_MODE_SINGLE_LR:
        if (Status == VL53L0X_ERROR_NONE) {
            Status = VL53L0X_SetLimitCheckValue(pMyDevice, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, (FixPoint1616_t)(0.1*65536));
        }
        if (Status == VL53L0X_ERROR_NONE) {
            Status = VL53L0X_SetLimitCheckValue(pMyDevice, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, (FixPoint1616_t)(60*65536));
        }

        break;
    default:
        break;
    }

    /*
     * <>
     * レンジング タイミング バジェットをマイクロ秒単位で設定します。
     * 機能の説明
     * 現在のモード (レンジング、ヒストグラム、ASL ...) のフルレンジング シーケンスを
     * 実行するためにユーザーがデバイスに許可する最大時間を定義します。
     */
    switch(sel){
    case RASING_MODE_SINGLE:
         break;
    case RASING_MODE_SINGLE_HA:
        if (Status == VL53L0X_ERROR_NONE) {
            Status = VL53L0X_SetMeasurementTimingBudgetMicroSeconds(pMyDevice, 200000);
        }
        break;
    case RASING_MODE_SINGLE_HS:
        if (Status == VL53L0X_ERROR_NONE) {
            Status = VL53L0X_SetMeasurementTimingBudgetMicroSeconds(pMyDevice, 30000);
        }
        break;
   case RASING_MODE_SINGLE_LR:
        if (Status == VL53L0X_ERROR_NONE) {
            Status = VL53L0X_SetMeasurementTimingBudgetMicroSeconds(pMyDevice, 33000);
        }
        break;
    default:
        break;
    }

    /*
     * < VL53L0X_SetVcselPulsePeriod() >
     * VCSEL パルス周期を設定します。
     * 機能の説明
     * この関数は、指定された周期タイプの VCSEL パルス周期を取得します。
     */
    switch(sel){
    case RASING_MODE_SINGLE:
         break;
    case RASING_MODE_SINGLE_HA:
        break;
    case RASING_MODE_SINGLE_HS:
        break;
   case RASING_MODE_SINGLE_LR:
        if (Status == VL53L0X_ERROR_NONE) {
            Status = VL53L0X_SetVcselPulsePeriod(pMyDevice, VL53L0X_VCSEL_PERIOD_PRE_RANGE, 18);
        }
        if (Status == VL53L0X_ERROR_NONE) {
            Status = VL53L0X_SetVcselPulsePeriod(pMyDevice, VL53L0X_VCSEL_PERIOD_FINAL_RANGE, 14);
        }
        break;
    default:
        break;
    }

    if(sel==RASING_MODE_SINGLE_LR){
        max = 50;
    }
    else{
        max = 10;
    }

    return Status;

}

//==============================================================================
//
// sel : 0 SINGLE RACING
//       1 SINGLE RACING HA
//       2 SINGLE RACING HS
//       3 SINGLE RACING LR
//
//==============================================================================
void usrVl53l0x_Racing_test(RASING_MODE sel)
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
//    VL53L0X_Dev_t MyDevice;
    VL53L0X_Dev_t *pMyDevice = &MyDevice;
    VL53L0X_Version_t                   Version;
    VL53L0X_Version_t                  *pVersion   = &Version;
    VL53L0X_DeviceInfo_t                DeviceInfo;

    int32_t status_int;
    int32_t init_done = 0;
    int NecleoComStatus = 0;
    int NecleoAutoCom = 1;
    
    uint8_t VhvSettings;
    uint32_t refSpadCount;
    uint8_t isApertureSpads;
    uint8_t PhaseCal;

    



    MyDevice.I2cDevAddr = 0x52;

    if(sel == RASING_MODE_CONTINUE){
        Xprintf ("VL53L0X PAL Continuous Ranging example\r\n");
    }
    else{
        Xprintf ("VL53L0X API Simple Ranging example\r\n\n");
    }

    pMyDevice->I2cDevAddr      = 0x52;

    /*
     *  Get the version of the VL53L0X API running in the firmware
     */

    if(Status == VL53L0X_ERROR_NONE){
        status_int = VL53L0X_GetVersion(pVersion);
        if (status_int != 0){
            Status = VL53L0X_ERROR_CONTROL_INTERFACE;
            Xprintf("VL53L0X_ERROR_CONTROL_INTERFACE(line%d)\r\n",__LINE__);
        }
        else{
            //  Verify the version of the VL53L0X API running in the firmware
            if( pVersion->major != VERSION_REQUIRED_MAJOR ||
                pVersion->minor != VERSION_REQUIRED_MINOR ||
                pVersion->build != VERSION_REQUIRED_BUILD )
            {
                Xprintf("VL53L0X API Version Error: Your firmware has %d.%d.%d (revision %d). This example requires %d.%d.%d.\r\n",
                    pVersion->major, pVersion->minor, pVersion->build, pVersion->revision,
                    VERSION_REQUIRED_MAJOR, VERSION_REQUIRED_MINOR, VERSION_REQUIRED_BUILD);
            }
        }
    }

    /*
     * 機能の説明
     * 新しいデバイスの「電源投入」またはリセット後に使用されていない場合、
     * VL53L0X_ERROR_CALIBRATION_WARNING が返される場合があります。
     * これは、間違ったキャリブレーション データがデバイスからフェッチされた
     * 可能性があり、レンジング オフセット エラーが発生する可能性があります。
     *
     * アプリケーションがデバイスリセットを実行できない場合、または VL53L0X_DataInitを
     * 複数回実行する必要がある場合は、最初の電源投入時に
     * VL53L0X_GetOffsetCalibrationData() を使用し、その後すべての初期化で
     * VL53L0X_SetOffsetCalibrationData() を使用して、適切なオフセットキャリブレーションの保存と
     * 復元を独自に行う必要があります。
     * この関数は VL53L0X_State を変更します。
     * VL53L0X_STATE_POWERDOWN から VL53L0X_STATE_WAIT_STATICINIT まで。
     */
    if(Status == VL53L0X_ERROR_NONE){
        Status = VL53L0X_DataInit(&MyDevice); // Data initialization
        print_pal_error(Status,__LINE__);
    }

    if(Status == VL53L0X_ERROR_NONE){
        Status = VL53L0X_GetDeviceInfo(&MyDevice, &DeviceInfo);

        if(Status == VL53L0X_ERROR_NONE){
            LOG_PRINT_VL53("VL53L0X_GetDeviceInfo:\r\n");
            LOG_PRINT_VL53("Device Name : %s\r\n", DeviceInfo.Name);
            LOG_PRINT_VL53("Device Type : %s\r\n", DeviceInfo.Type);
            LOG_PRINT_VL53("Device ID : %s\r\n", DeviceInfo.ProductId);
            LOG_PRINT_VL53("ProductRevisionMajor : %d\r\n", DeviceInfo.ProductRevisionMajor);
            LOG_PRINT_VL53("ProductRevisionMinor : %d\r\n", DeviceInfo.ProductRevisionMinor);

            if ((DeviceInfo.ProductRevisionMinor != 1) && (DeviceInfo.ProductRevisionMinor != 1)) {
                Status = VL53L0X_ERROR_NOT_SUPPORTED;
            }
        }
        print_pal_error(Status,__LINE__);
    }

    
    /*
     * <VL53L0X_StaticInit()>
     * 基本的なデバイスの初期化 (最終的にはパッチのロード) を実行します。
     * この関数は、VL53L0X_State を VL53L0X_STATE_WAIT_STATICINIT から VL53L0X_STATE_IDLE に変更します。
     * この段階では、すべてのデフォルト設定が適用されます。
     */
    if(Status == VL53L0X_ERROR_NONE)
    {
        Status = VL53L0X_StaticInit(&MyDevice); // Device Initialization
        print_pal_error(Status,__LINE__);
    }


    if(Status == VL53L0X_ERROR_NONE)
    {
        Status = VL53L0X_PerformRefCalibration(&MyDevice, &VhvSettings, &PhaseCal); // Device Initialization
        print_pal_error(Status,__LINE__);
    }

    if(Status == VL53L0X_ERROR_NONE)
    {
        Status = VL53L0X_PerformRefSpadManagement(&MyDevice, &refSpadCount, &isApertureSpads); // Device Initialization
        print_pal_error(Status,__LINE__);
    }

    if(Status == VL53L0X_ERROR_NONE)
    {
        if(sel == RASING_MODE_CONTINUE ){
            Status = VL53L0X_SetDeviceMode(&MyDevice, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING); // Setup in single ranging mode
        }
        else{
            Status = VL53L0X_SetDeviceMode(&MyDevice, VL53L0X_DEVICEMODE_SINGLE_RANGING); // Setup in single ranging mode
        }

        print_pal_error(Status,__LINE__);
    }

    /*
     * <VL53L0X_SetSequenceStepEnable()>
     * 要求されたシーケンス ステップの (オン/オフ) 状態を設定します。
     * 機能の説明
     * この機能は、要求されたシーケンス ステップを有効または無効にします。
     * ノート：
     * この機能はデバイスにアクセスします
     * パラメーター：
     *   Device Handle
     *   Sequence step identifier.
     *   Demanded state {0=Off,1=On} is enabled.     *
     */
    if (Status == VL53L0X_ERROR_NONE) {
        if(sel == RASING_MODE_SINGLE_LR){
            //Status = VL53L0X_SetSequenceStepEnable(pMyDevice,VL53L0X_SEQUENCESTEP_DSS, 1);
        }
    }
} 

//==============================================================================
//
//==============================================================================
void vl53data_disp(void)
{
    int i;

    Xprintf("Part2PartOffsetNVMMicroMeter = %d\r\n", 	MyDevice.Data.Part2PartOffsetNVMMicroMeter	);
    Xprintf("Part2PartOffsetAdjustmentNVMMicroMeter = %d\r\n",	MyDevice.Data.Part2PartOffsetAdjustmentNVMMicroMeter	);
    Xprintf("VL53L0X_DeviceParameters_t\r\n");
    Xprintf("  DeviceMode = 0x%x\r\n",	MyDevice.Data.CurrentParameters.DeviceMode	);
    Xprintf("  HistogramMode = 0x%x\r\n",	MyDevice.Data.CurrentParameters.HistogramMode	);
    Xprintf("  MeasurementTimingBudgetMicroSeconds = 0x%u\r\n",	MyDevice.Data.CurrentParameters.MeasurementTimingBudgetMicroSeconds	);
    Xprintf("  InterMeasurementPeriodMilliSeconds = 0x%u\r\n",	MyDevice.Data.CurrentParameters.InterMeasurementPeriodMilliSeconds	);
    Xprintf("  XTalkCompensationEnable = 0x%x\r\n",	MyDevice.Data.CurrentParameters.XTalkCompensationEnable	);
    Xprintf("  XTalkCompensationRangeMilliMeter = 0x%x\r\n",	MyDevice.Data.CurrentParameters.XTalkCompensationRangeMilliMeter	);
    Xprintf("  XTalkCompensationRateMegaCps = 0x%u\r\n",	MyDevice.Data.CurrentParameters.XTalkCompensationRateMegaCps	);
    Xprintf("  RangeOffsetMicroMeters = %d\r\n",	MyDevice.Data.CurrentParameters.RangeOffsetMicroMeters	);

    //Xprintf("  LimitChecksEnable[VL53L0X_CHECKENABLE_NUMBER_OF_CHECKS] = 0x%x\r\n",	MyDevice.Data.CurrentParameters.LimitChecksEnable[VL53L0X_CHECKENABLE_NUMBER_OF_CHECKS]	);
    Xprintf("  LimitChecksEnable[] = ");
    for(i=0; i<VL53L0X_CHECKENABLE_NUMBER_OF_CHECKS; i++){
        Xprintf("0x%02x,",	MyDevice.Data.CurrentParameters.LimitChecksEnable[i]	);
    }
    Xprintf("\r\n");


    //Xprintf("  LimitChecksStatus[VL53L0X_CHECKENABLE_NUMBER_OF_CHECKS] = 0x%x\r\n",	MyDevice.Data.CurrentParameters.LimitChecksStatus[VL53L0X_CHECKENABLE_NUMBER_OF_CHECKS]	);
    Xprintf("  LimitChecksStatus[] = ");
    for(i=0; i<VL53L0X_CHECKENABLE_NUMBER_OF_CHECKS; i++){
        Xprintf("0x%02x,",	MyDevice.Data.CurrentParameters.LimitChecksStatus[i]	);
    }
    Xprintf("\r\n");

    //Xprintf("  LimitChecksValue[VL53L0X_CHECKENABLE_NUMBER_OF_CHECKS] = 0x%u\r\n",	MyDevice.Data.CurrentParameters.LimitChecksValue[VL53L0X_CHECKENABLE_NUMBER_OF_CHECKS]	);
    Xprintf("  LimitChecksValue[] = ");
    for(i=0; i<VL53L0X_CHECKENABLE_NUMBER_OF_CHECKS; i++){
        Xprintf("0x%u,",	MyDevice.Data.CurrentParameters.LimitChecksValue[i]	);
    }
    Xprintf("\r\n");


    //Xprintf("  ambRate_mcps = 0x%u\r\n",	MyDevice.Data.CurrentParameters.dmax_lut.ambRate_mcps[VL53L0X_DMAX_LUT_SIZE]	);

#ifdef ___NOP
    Xprintf("  ambRate_mcps[] = ");
    for(i=0; i<VL53L0X_DMAX_LUT_SIZE; i++){
        Xprintf("0x%u,", MyDevice.Data.CurrentParameters.dmax_lut.ambRate_mcps[i]	);
    }
    Xprintf("\r\n");

//    Xprintf("  dmax_mm = 0x%u\r\n",	MyDevice.Data.CurrentParameters.dmax_lut.dmax_mm[VL53L0X_DMAX_LUT_SIZE]	);
    Xprintf("  dmax_mm[] = ");
    for(i=0; i<VL53L0X_DMAX_LUT_SIZE; i++){
        Xprintf("0x%u,", MyDevice.Data.CurrentParameters.dmax_lut.dmax_mm[i]	);
    }
#endif
    Xprintf("\r\n");

    Xprintf("  WrapAroundCheckEnable = 0x%x\r\n",	MyDevice.Data.CurrentParameters.WrapAroundCheckEnable	);
    Xprintf("VL53L0X_RangingMeasurementData_t\r\n");
    Xprintf("  TimeStamp = 0x%u\r\n",	MyDevice.Data.LastRangeMeasure.TimeStamp	);
    Xprintf("  MeasurementTimeUsec = 0x%u\r\n",	MyDevice.Data.LastRangeMeasure.MeasurementTimeUsec	);
    Xprintf("  RangeMilliMeter = %d mm\r\n",	MyDevice.Data.LastRangeMeasure.RangeMilliMeter	);
    Xprintf("  RangeDMaxMilliMeter = %d mm\r\n",	MyDevice.Data.LastRangeMeasure.RangeDMaxMilliMeter	);
    Xprintf("  SignalRateRtnMegaCps = %d\r\n",	MyDevice.Data.LastRangeMeasure.SignalRateRtnMegaCps	);
    Xprintf("  AmbientRateRtnMegaCps = %d\r\n",	MyDevice.Data.LastRangeMeasure.AmbientRateRtnMegaCps	);
    Xprintf("  EffectiveSpadRtnCount = %d\r\n",	MyDevice.Data.LastRangeMeasure.EffectiveSpadRtnCount	);
    Xprintf("  ZoneId = 0x%x\r\n",	MyDevice.Data.LastRangeMeasure.ZoneId	);
    Xprintf("  RangeFractionalPart = 0x%x\r\n",	MyDevice.Data.LastRangeMeasure.RangeFractionalPart	);
    Xprintf("  RangeStatus = 0x%x\r\n",	MyDevice.Data.LastRangeMeasure.RangeStatus	);

    Xprintf("VL53L0X_HistogramMeasurementData_t\r\n");
    //Xprintf("  HistogramData[VL53L0X_HISTOGRAM_BUFFER_SIZE] = 0x%u\r\n",	MyDevice.Data.LastHistogramMeasure.HistogramData[VL53L0X_HISTOGRAM_BUFFER_SIZE]	);
    Xprintf("  HistogramData[] = ");
    for(i=0; i<VL53L0X_HISTOGRAM_BUFFER_SIZE; i++){
        Xprintf("0x%u,", MyDevice.Data.LastHistogramMeasure.HistogramData[i]	);
        switch(i){
            case 7:
            case 15:
            case 23:
                Xprintf("\r\n");
                Xprintf("                  = ");
                break;
        }
    }
    Xprintf("\r\n");



    Xprintf("  FirstBin = 0x%x\r\n",	MyDevice.Data.LastHistogramMeasure.FirstBin	);
    Xprintf("  BufferSize = 0x%x\r\n",	MyDevice.Data.LastHistogramMeasure.BufferSize	);
    Xprintf("  NumberOfBins = 0x%x\r\n",	MyDevice.Data.LastHistogramMeasure.NumberOfBins	);
    Xprintf("  ErrorStatus = 0x%x\r\n",	MyDevice.Data.LastHistogramMeasure.ErrorStatus	);

    Xprintf("VL53L0X_DeviceSpecificParameters_t\r\n");
    Xprintf("  OscFrequencyMHz  = 0x%u\r\n",	MyDevice.Data.DeviceSpecificParameters.OscFrequencyMHz 	);
    Xprintf("  LastEncodedTimeout  = 0x%x\r\n",	MyDevice.Data.DeviceSpecificParameters.LastEncodedTimeout 	);
    Xprintf("  Pin0GpioFunctionality = 0x%x\r\n",	MyDevice.Data.DeviceSpecificParameters.Pin0GpioFunctionality	);
    Xprintf("  FinalRangeTimeoutMicroSecs = 0x%u\r\n",	MyDevice.Data.DeviceSpecificParameters.FinalRangeTimeoutMicroSecs	);
    Xprintf("  FinalRangeVcselPulsePeriod = 0x%x\r\n",	MyDevice.Data.DeviceSpecificParameters.FinalRangeVcselPulsePeriod	);
    Xprintf("  PreRangeTimeoutMicroSecs = 0x%u\r\n",	MyDevice.Data.DeviceSpecificParameters.PreRangeTimeoutMicroSecs	);
    Xprintf("  PreRangeVcselPulsePeriod = 0x%x\r\n",	MyDevice.Data.DeviceSpecificParameters.PreRangeVcselPulsePeriod	);
    Xprintf("  SigmaEstRefArray = 0x%x\r\n",	MyDevice.Data.DeviceSpecificParameters.SigmaEstRefArray	);
    Xprintf("  SigmaEstEffPulseWidth = 0x%x\r\n",	MyDevice.Data.DeviceSpecificParameters.SigmaEstEffPulseWidth	);
    Xprintf("  SigmaEstEffAmbWidth = 0x%x\r\n",	MyDevice.Data.DeviceSpecificParameters.SigmaEstEffAmbWidth	);
    Xprintf("  ReadDataFromDeviceDone = 0x%x\r\n",	MyDevice.Data.DeviceSpecificParameters.ReadDataFromDeviceDone	);
    Xprintf("  ModuleId = 0x%x\r\n",	MyDevice.Data.DeviceSpecificParameters.ModuleId	);
    Xprintf("  Revision = 0x%x\r\n",	MyDevice.Data.DeviceSpecificParameters.Revision	);
    Xprintf("  ProductId[VL53L0X_MAX_STRING_LENGTH] = %s\r\n",	&MyDevice.Data.DeviceSpecificParameters.ProductId[0]	);
    Xprintf("  ReferenceSpadCount = 0x%x\r\n",	MyDevice.Data.DeviceSpecificParameters.ReferenceSpadCount	);
    Xprintf("  ReferenceSpadType = 0x%x\r\n",	MyDevice.Data.DeviceSpecificParameters.ReferenceSpadType	);
    Xprintf("  RefSpadsInitialised = 0x%x\r\n",	MyDevice.Data.DeviceSpecificParameters.RefSpadsInitialised	);
    Xprintf("  PartUIDUpper = 0x%u\r\n",	MyDevice.Data.DeviceSpecificParameters.PartUIDUpper	);
    Xprintf("  PartUIDLower = 0x%u\r\n",	MyDevice.Data.DeviceSpecificParameters.PartUIDLower	);
    Xprintf("  SignalRateMeasFixed400mm = 0x%u\r\n",	MyDevice.Data.DeviceSpecificParameters.SignalRateMeasFixed400mm	);

    Xprintf("VL53L0X_SpadData_t\r\n");
//    Xprintf("  RefSpadEnables = 0x%x\r\n",	MyDevice.Data.SpadData.RefSpadEnables[VL53L0X_REF_SPAD_BUFFER_SIZE]	);
    Xprintf("  RefSpadEnables[] = ");
    for(i=0; i<VL53L0X_REF_SPAD_BUFFER_SIZE; i++){
        Xprintf("0x%02x,",	MyDevice.Data.SpadData.RefSpadEnables[i]	);
    }
    Xprintf("\r\n");

    //    Xprintf("  RefGoodSpadMap = 0x%x\r\n",	MyDevice.Data.SpadData.RefGoodSpadMap[VL53L0X_REF_SPAD_BUFFER_SIZE]	);

    Xprintf("  RefGoodSpadMap[] = ");
    for(i=0; i<VL53L0X_REF_SPAD_BUFFER_SIZE; i++){
        Xprintf("0x%02x,",	MyDevice.Data.SpadData.RefGoodSpadMap[i]	);
    }
    Xprintf("\r\n");


    Xprintf("ETC.\r\n");
    Xprintf("  SequenceConfig = 0x%x\r\n",	MyDevice.Data.SequenceConfig	);
    Xprintf("  RangeFractionalEnable = 0x%x\r\n",	MyDevice.Data.RangeFractionalEnable	);
    Xprintf("  PalState = 0x%x\r\n",	MyDevice.Data.PalState	);
    Xprintf("  PowerMode = 0x%x\r\n",	MyDevice.Data.PowerMode	);
    Xprintf("  SigmaEstRefArray = 0x%x\r\n",	MyDevice.Data.SigmaEstRefArray	);
    Xprintf("  SigmaEstEffPulseWidth = 0x%x\r\n",	MyDevice.Data.SigmaEstEffPulseWidth	);
    Xprintf("  SigmaEstEffAmbWidth = 0x%x\r\n",	MyDevice.Data.SigmaEstEffAmbWidth	);
    Xprintf("  StopVariable = 0x%x\r\n",	MyDevice.Data.StopVariable	);
    Xprintf("  targetRefRate = 0x%x\r\n",	MyDevice.Data.targetRefRate	);
    Xprintf("  SigmaEstimate = 0x%u\r\n",	MyDevice.Data.SigmaEstimate	);
    Xprintf("  SignalEstimate = 0x%u\r\n",	MyDevice.Data.SignalEstimate	);
    Xprintf("  LastSignalRefMcps = 0x%u\r\n",	MyDevice.Data.LastSignalRefMcps	);
//    Xprintf("  *pTuningSettingsPointer = 0x%x\r\n",	MyDevice.Data.*pTuningSettingsPointer	);
    Xprintf("  UseInternalTuningSettings = 0x%x\r\n",	MyDevice.Data.UseInternalTuningSettings	);
    Xprintf("  LinearityCorrectiveGain = 0x%x\r\n",	MyDevice.Data.LinearityCorrectiveGain	);

    Xprintf("  I2cDevAddr = 0x%x\r\n",	MyDevice.I2cDevAddr	);
}
