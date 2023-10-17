//=============================================================================
//  include
//=============================================================================
#include "usr_system.h"
#include "xc.h"

//=============================================================================
// define
//=============================================================================
// Timer1 init
//#define T1_100msec
//#define T1_10msec
//#define T1_1msec
//#define T1_100usec
#define T1_10usec
//#define T1_1usec


//=============================================================================
// variable
//=============================================================================
uint16_t    timer1_cnt;
uint16_t    usrRTCcnt;
uint16_t    usrRTCflg;



USR_RTC_DATA usrRTC;
USR_RTC_DATA usrSRTC;

//=============================================================================
// Timer1 interrupt
//=============================================================================
#pragma vector OnTimer1 4
#pragma interrupt OnTimer1 IPL7AUTO
void OnTimer1(void) 
{
    IFS0bits.T1IF = 0; // 割り込みフラグをリセット

    timer1_cnt++;

//-----------------------------------------------------------------------------
#ifdef    T1_100msec
usrSRTC.usec = 0;
usrSRTC.msec += 100;
#endif
//-----------------------------------------------------------------------------
#ifdef T1_10msec
usrSRTC.usec = 0;
usrSRTC.msec += 10;
#endif
//-----------------------------------------------------------------------------
#ifdef  T1_1msec
usrSRTC.usec = 0;
usrSRTC.msec ++;
#endif
//-----------------------------------------------------------------------------
#ifdef T1_100usec
usrSRTC.usec += 100;
#endif
//-----------------------------------------------------------------------------
#ifdef    T1_10usec
usrSRTC.usec += 10;
#endif
//-----------------------------------------------------------------------------
#ifdef    T1_1usec
usrSRTC.usec ++;
#endif
//-----------------------------------------------------------------------------

    if( usrSRTC.usec == 1000 ){
        usrSRTC.usec = 0;
        usrSRTC.msec ++;
    }

    if( usrSRTC.msec == 1000 ){
        usrSRTC.msec = 0;
        usrSRTC.sec ++;
        if( usrSRTC.sec == 60 ){
            usrSRTC.sec = 0;
            usrSRTC.min ++;
            if( usrSRTC.min == 60 ){
                usrSRTC.min = 0;
                usrSRTC.hour ++;
            }
        }
    }
}


//=============================================================================
// Timer1 init
//=============================================================================
void usrInitTimer1(void)
{
    T1CONbits.ON = 0;    // 設定のため、タイマー1を無効にする
    TMR1 = 0;            // タイマー1をリセット

//-----------------------------------------------------------------------------
#ifdef    T1_100msec
    // 100ms周期で割り込み <- 250ns(1 / 40MHz) * 256 * 15625(0x3D09) = 100ms
    T1CONbits.TCKPS = 3; // プリスケーラ : x1/256
    PR1 = 0x3D09;        // カウンター
#endif
//-----------------------------------------------------------------------------
#ifdef T1_10msec
    T1CONbits.TCKPS = 1; // プリスケーラ : x1/256
    PR1 = 50000;        // カウンター
#endif
//-----------------------------------------------------------------------------
#ifdef  T1_1msec
    T1CONbits.TCKPS = 0; // プリスケーラ : x1/256
    PR1 = 40000;        // カウンター
#endif
//-----------------------------------------------------------------------------
#ifdef T1_100usec
    T1CONbits.TCKPS = 0; // プリスケーラ : x1/256
    PR1 = 4000;        // カウンター
#endif
//-----------------------------------------------------------------------------
#ifdef    T1_10usec
    T1CONbits.TCKPS = 0; // プリスケーラ : x1/256
    PR1 = 400;        // カウンター
#endif
//-----------------------------------------------------------------------------
#ifdef    T1_1usec
    T1CONbits.TCKPS = 0; // プリスケーラ : x1/256
    PR1 = 40;        // カウンター
#endif
//-----------------------------------------------------------------------------
    
    
    INTCONbits.MVEC = 1; // マルチベクタ割り込みを有効にする
    
    IPC1bits.T1IP = 7;   // 割り込み優先度(0-7)
    IPC1bits.T1IS = 0;   // 副優先度(0-3)
    IFS0bits.T1IF = 0;   // 割り込みフラグをリセット
    IEC0bits.T1IE = 1;   // タイマー1の割り込みを許可
    
    // __builtin_enable_interrupts();  // マイコンにおける割り込みの有効。「asm volatile("ei")」と同義
    T1CONbits.ON = 1;    // タイマー1有効
}

//=============================================================================
// Timer2 interrupt
//=============================================================================
#pragma vector OnTimer2 8
#pragma interrupt OnTimer2 IPL7AUTO
void OnTimer2(void) 
{
    IFS0bits.T2IF = 0;   // 割り込みフラグをリセット

    timer1_cnt++;

//-----------------------------------------------------------------------------
#ifdef    T1_100msec
usrSRTC.usec = 0;
usrSRTC.msec += 100;
#endif
//-----------------------------------------------------------------------------
#ifdef T1_10msec
usrSRTC.usec = 0;
usrSRTC.msec += 10;
#endif
//-----------------------------------------------------------------------------
#ifdef  T1_1msec
usrSRTC.usec = 0;
usrSRTC.msec ++;
#endif
//-----------------------------------------------------------------------------
#ifdef T1_100usec
usrSRTC.usec += 100;
#endif
//-----------------------------------------------------------------------------
#ifdef    T1_10usec
usrSRTC.usec += 10;
#endif
//-----------------------------------------------------------------------------
#ifdef    T1_1usec
usrSRTC.usec ++;
#endif
//-----------------------------------------------------------------------------

    if( usrSRTC.usec == 1000 ){
        usrSRTC.usec = 0;
        usrSRTC.msec ++;
    }

    if( usrSRTC.msec == 1000 ){
        usrSRTC.msec = 0;
        usrSRTC.sec ++;
        if( usrSRTC.sec == 60 ){
            usrSRTC.sec = 0;
            usrSRTC.min ++;
            if( usrSRTC.min == 60 ){
                usrSRTC.min = 0;
                usrSRTC.hour ++;
            }
        }
    }
}

//=============================================================================
// Timer2 init
//=============================================================================
void usrInitTimer2(void)
{
    T2CON = 0;
    
    T2CONbits.ON = 1;
    T2CONbits.SIDL = 0;     // 
    T2CONbits.T32 = 0;      // 16bit timer
    T2CONbits.TCKPS = 0;    // 1:1 PriScale

    TMR2 = 0;            // タイマー1をリセット

//-----------------------------------------------------------------------------
#ifdef    T1_100msec
    // 100ms周期で割り込み <- 250ns(1 / 40MHz) * 256 * 15625(0x3D09) = 100ms
    T2CONbits.TCKPS = 3; // プリスケーラ : x1/256
    PR2 = 0x3D09-1;        // カウンター
#endif
//-----------------------------------------------------------------------------
#ifdef T1_10msec
    T2CONbits.TCKPS = 1; // プリスケーラ : x1/256
    PR2 = 50000-1;        // カウンター
#endif
//-----------------------------------------------------------------------------
#ifdef  T1_1msec
    T2CONbits.TCKPS = 0; // プリスケーラ : x1/256
    PR2 = 40000-1;        // カウンター
#endif
//-----------------------------------------------------------------------------
#ifdef T1_100usec
    T2CONbits.TCKPS = 0; // プリスケーラ : x1/256
    PR2 = 4000-1;        // カウンター
#endif
//-----------------------------------------------------------------------------
#ifdef    T1_10usec
    T2CONbits.TCKPS = 0; // プリスケーラ : x1/256
    PR2 = 400-1;        // カウンター
#endif
//-----------------------------------------------------------------------------
#ifdef    T1_1usec
    T2CONbits.TCKPS = 0; // プリスケーラ : x1/256
    PR2 = 40-1;        // カウンター
#endif
//-----------------------------------------------------------------------------
    
    
    INTCONbits.MVEC = 1; // マルチベクタ割り込みを有効にする
    
    IPC2bits.T2IP = 7;   // 割り込み優先度(0-7)
    IPC2bits.T2IS = 0;   // 副優先度(0-3)
    IFS0bits.T2IF = 0;   // 割り込みフラグをリセット
    IEC0bits.T2IE = 1;   // タイマー1の割り込みを許可
    
    // __builtin_enable_interrupts();  // マイコンにおける割り込みの有効。「asm volatile("ei")」と同義
    T2CONbits.ON = 1;    // タイマー1有効
}

//=============================================================================
// RTC interrupt
// #define _RTCC_VECTOR                             35
//=============================================================================
#pragma vector usrRTCinterrupt 35
#pragma interrupt usrRTCinterrupt IPL7AUTO
void usrRTCinterrupt(void) 
{
    uint8_t temp;
    IFS1bits.RTCCIF = 0;   // 割り込みフラグをリセット

    usrRTCflg = 1;
    temp = ALRMTIMEbits.SEC01;
    temp ++;
    if( temp > 10 )
        temp = 0;
    
    ALRMTIMEbits.SEC01 = temp;
    
    usrRTCcnt = timer1_cnt;
    timer1_cnt = 0;
    //timer1_cnt = 0;
    
}

//=============================================================================
// Timer1 init
//=============================================================================

void usrInitRTC(void)
{
    RTCCON = 0;
    //----------------------------
    //  RTCC 書き込みが有効化
    //----------------------------
    SYSKEY = 0xaa996655;        // write first unlock key to SYSKEY
    SYSKEY = 0x556699aa;        // write second unlock key to SYSKEY
    RTCCONbits.RTCWREN = 1;     

    //----------------------------
    //  RTCC 割込み
    //----------------------------
    IPC8bits.RTCCIP = 7;   // 割り込み優先度(0-7)
    IPC8bits.RTCCIS = 0;   // 副優先度(0-3)
    IFS1bits.RTCCIF = 0;   // 割り込みフラグをリセット
    IEC1bits.RTCCIE = 0;   // rtcの割り込みをDISABLE

    //----------------------------
    //  クロックがオフになるまで待ちます
    //----------------------------
    while(RTCCON&0x40);                 // wait for clock to be turned off
    
    RTCCONbits.RTSECSEL = 1;
    
    RTCTIME     = 0x12153000;            // 12 hr, 15 min, 30 sec
    RTCDATE     = 0x23101305;            // 2023.10.13 Friday
    
    RTCALRM = 0;
    RTCALRMbits.AMASK = 1;      // 毎秒
    RTCALRMbits.ARPT = 0xff;
    RTCALRMbits.CHIME = 1;

    ALRMTIME = 0x12153100;            // 12 hr, 15 min, 31 sec
    ALRMDATE = 0x23101305;            // 2023.10.13 Friday

    RTCALRMbits.ALRMEN = 1;

    
    RTCCONbits.ON = 1;

    //----------------------------
    //  RTCC 書き込みが無効化
    //----------------------------
    RTCCONbits.RTCWREN = 0;
    
    while(!(RTCCON&0x40));              // wait for clock to be turned on

    IEC1bits.RTCCIE = 1;   // rtcの割り込みを許可
    
}


void usrGetRTC(void)
{
    usrRTC.hour     = 10*RTCTIMEbits.HR10    + RTCTIMEbits.HR01;
    usrRTC.min      = 10*RTCTIMEbits.MIN10   + RTCTIMEbits.MIN01;
    usrRTC.sec      = 10*RTCTIMEbits.SEC10   + RTCTIMEbits.SEC01;
    
    usrRTC.day      = 10+RTCDATEbits.DAY10   + RTCDATEbits.DAY01;
    usrRTC.month    = 10*RTCDATEbits.MONTH10 + RTCDATEbits.MONTH01;
    usrRTC.year     = 10*RTCDATEbits.YEAR10  + RTCDATEbits.YEAR01;
    usrRTC.wday     = RTCDATEbits.WDAY01;
}
