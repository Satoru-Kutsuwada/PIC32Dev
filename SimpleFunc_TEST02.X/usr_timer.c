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
#define T1_10msec
//#define T1_1msec
//#define T1_100usec
//#define T1_10usec
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
// Prototype
//=============================================================================
void ssCount_Timer(void);



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
ssCount_Timer();
usrSRTC.usec = 0;
usrSRTC.msec += 100;
#endif
//-----------------------------------------------------------------------------
#ifdef T1_10msec
ssCount_Timer();
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

