/*******************************************************************************
Copyright � 2015, STMicroelectronics International N.V.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of STMicroelectronics nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND
NON-INFRINGEMENT OF INTELLECTUAL PROPERTY RIGHTS ARE DISCLAIMED.
IN NO EVENT SHALL STMICROELECTRONICS INTERNATIONAL N.V. BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************************/

/**
 * @file VL53L0X_i2c.c
 *
 * Copyright (C) 2014 ST MicroElectronics
 *
 * provide variable word size byte/Word/dword VL6180x register access via i2c
 *
 */
#ifdef ___NOP
#include "vl53l0x_platform.h"
#include "vl53l0x_i2c_platform.h"
#include "vl53l0x_api.h"
#include <Windows.h>
#endif  // ___NOP

#include "vl53l0x_platform.h"
#include "vl53l0x_api.h"
//#include "stm32f4xx_hal.h"
#include <string.h>



#define LOG_FUNCTION_START(fmt, ... )           _LOG_FUNCTION_START(TRACE_MODULE_PLATFORM, fmt, ##__VA_ARGS__)
#define LOG_FUNCTION_END(status, ... )          _LOG_FUNCTION_END(TRACE_MODULE_PLATFORM, status, ##__VA_ARGS__)
#define LOG_FUNCTION_END_FMT(status, fmt, ... ) _LOG_FUNCTION_END_FMT(TRACE_MODULE_PLATFORM, status, fmt, ##__VA_ARGS__)

/**
 * @def I2C_BUFFER_CONFIG
 *
 * @brief Configure Device register I2C access
 *
 * @li 0 : one GLOBAL buffer \n
 *   Use one global buffer of MAX_I2C_XFER_SIZE byte in data space \n
 *   This solution is not multi-Device compliant nor multi-thread cpu safe \n
 *   It can be the best option for small 8/16 bit MCU without stack and limited ram  (STM8s, 80C51 ...)
 *
 * @li 1 : ON_STACK/local \n
 *   Use local variable (on stack) buffer \n
 *   This solution is multi-thread with use of i2c resource lock or mutex see VL6180x_GetI2CAccess() \n
 *
 * @li 2 : User defined \n
 *    Per Device potentially dynamic allocated. Requires VL6180x_GetI2cBuffer() to be implemented.
 * @ingroup Configuration
 */




#define I2C_TIME_OUT_BASE   10
#define I2C_TIME_OUT_BYTE   1
//#define VL53L0X_OsDelay(...) HAL_Delay(2)


#ifndef HAL_I2C_MODULE_ENABLED
#warning "HAL I2C module must be enable "
#endif
//extern I2C_HandleTypeDef hi2c1;
//#define VL53L0X_pI2cHandle    (&hi2c1)

/* when not customized by application define dummy one */
#ifndef VL53L0X_GetI2cBus
/** This macro can be overloaded by user to enforce i2c sharing in RTOS context
 */
#   define VL53L0X_GetI2cBus(...) (void)0
#endif

#ifndef VL53L0X_PutI2cBus
/** This macro can be overloaded by user to enforce i2c sharing in RTOS context
 */
#   define VL53L0X_PutI2cBus(...) (void)0
#endif

//#ifndef VL53L0X_OsDelay
//#   define  VL53L0X_OsDelay(...) (void)0
//#endif


uint8_t _I2CBuffer[64];

void VL53L0X_OsDelay(void);

//======================================================================
//
//======================================================================
int _I2CWrite(VL53L0X_DEV Dev, uint8_t *pdata, uint32_t count) {
    int status;
    int i2c_time_out = I2C_TIME_OUT_BASE+ count* I2C_TIME_OUT_BYTE;

//    status = HAL_I2C_Master_Transmit(Dev->I2cHandle, Dev->I2cDevAddr, pdata, count, i2c_time_out);
    if (status) {
        //VL6180x_ErrLog("I2C error 0x%x %d len", dev->I2cAddr, len);
        //XNUCLEO6180XA1_I2C1_Init(&hi2c1);
    }
    return status;
}

//======================================================================
//
//======================================================================
int _I2CRead(VL53L0X_DEV Dev, uint8_t *pdata, uint32_t count) {
    int status;
    int i2c_time_out = I2C_TIME_OUT_BASE+ count* I2C_TIME_OUT_BYTE;

//    status = HAL_I2C_Master_Receive(Dev->I2cHandle, Dev->I2cDevAddr|1, pdata, count, i2c_time_out);
    if (status) {
        //VL6180x_ErrLog("I2C error 0x%x %d len", dev->I2cAddr, len);
        //XNUCLEO6180XA1_I2C1_Init(&hi2c1);
    }
    return status;
}


//======================================================================
//
//======================================================================
VL53L0X_Error VL53L0X_LockSequenceAccess(VL53L0X_DEV Dev){
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;

    return Status;
}

//======================================================================
//
//======================================================================
VL53L0X_Error VL53L0X_UnlockSequenceAccess(VL53L0X_DEV Dev){
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;

    return Status;
}




//======================================================================
//
//======================================================================
// the ranging_sensor_comms.dll will take care of the page selection
VL53L0X_Error VL53L0X_WriteMulti(VL53L0X_DEV Dev, uint8_t index, uint8_t *pdata, uint32_t count) {
    int status_int;
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    if (count > sizeof(_I2CBuffer) - 1) {
        return VL53L0X_ERROR_INVALID_PARAMS;
    }
    _I2CBuffer[0] = index;
    memcpy(&_I2CBuffer[1], pdata, count);
    VL53L0X_GetI2cBus();
    status_int = _I2CWrite(Dev, _I2CBuffer, count + 1);
    if (status_int != 0) {
        Status = VL53L0X_ERROR_CONTROL_INTERFACE;
    }
    VL53L0X_PutI2cBus();
    return Status;
}

//======================================================================
//
//======================================================================
// the ranging_sensor_comms.dll will take care of the page selection
VL53L0X_Error VL53L0X_ReadMulti(VL53L0X_DEV Dev, uint8_t index, uint8_t *pdata, uint32_t count) {
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    int32_t status_int;
    VL53L0X_GetI2cBus();
    status_int = _I2CWrite(Dev, &index, 1);
    if (status_int != 0) {
        Status = VL53L0X_ERROR_CONTROL_INTERFACE;
        goto done;
    }
    status_int = _I2CRead(Dev, pdata, count);
    if (status_int != 0) {
        Status = VL53L0X_ERROR_CONTROL_INTERFACE;
    }
done:
    VL53L0X_PutI2cBus();
    return Status;
}

//======================================================================
//
//======================================================================
VL53L0X_Error VL53L0X_WrByte(VL53L0X_DEV Dev, uint8_t index, uint8_t data) {
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    int32_t status_int;

    _I2CBuffer[0] = index;
    _I2CBuffer[1] = data;

    VL53L0X_GetI2cBus();
    status_int = _I2CWrite(Dev, _I2CBuffer, 2);
    if (status_int != 0) {
        Status = VL53L0X_ERROR_CONTROL_INTERFACE;
    }
    VL53L0X_PutI2cBus();
    return Status;
}

//======================================================================
//
//======================================================================
VL53L0X_Error VL53L0X_WrWord(VL53L0X_DEV Dev, uint8_t index, uint16_t data) {
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    int32_t status_int;

    _I2CBuffer[0] = index;
    _I2CBuffer[1] = data >> 8;
    _I2CBuffer[2] = data & 0x00FF;

    VL53L0X_GetI2cBus();
    status_int = _I2CWrite(Dev, _I2CBuffer, 3);
    if (status_int != 0) {
        Status = VL53L0X_ERROR_CONTROL_INTERFACE;
    }
    VL53L0X_PutI2cBus();
    return Status;
}

//======================================================================
//
//======================================================================
VL53L0X_Error VL53L0X_WrDWord(VL53L0X_DEV Dev, uint8_t index, uint32_t data) {
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    int32_t status_int;
    _I2CBuffer[0] = index;
    _I2CBuffer[1] = (data >> 24) & 0xFF;
    _I2CBuffer[2] = (data >> 16) & 0xFF;
    _I2CBuffer[3] = (data >> 8)  & 0xFF;
    _I2CBuffer[4] = (data >> 0 ) & 0xFF;
    VL53L0X_GetI2cBus();
    status_int = _I2CWrite(Dev, _I2CBuffer, 5);
    if (status_int != 0) {
        Status = VL53L0X_ERROR_CONTROL_INTERFACE;
    }
    VL53L0X_PutI2cBus();
    return Status;
}

//======================================================================
//
//======================================================================
VL53L0X_Error VL53L0X_UpdateByte(VL53L0X_DEV Dev, uint8_t index, uint8_t AndData, uint8_t OrData) {
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    uint8_t data;

    Status = VL53L0X_RdByte(Dev, index, &data);
    if (Status) {
        goto done;
    }
    data = (data & AndData) | OrData;
    Status = VL53L0X_WrByte(Dev, index, data);
done:
    return Status;
}

//======================================================================
//
//======================================================================
VL53L0X_Error VL53L0X_RdByte(VL53L0X_DEV Dev, uint8_t index, uint8_t *data) {
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    int32_t status_int;

    VL53L0X_GetI2cBus();
    status_int = _I2CWrite(Dev, &index, 1);
    if( status_int ){
        Status = VL53L0X_ERROR_CONTROL_INTERFACE;
        goto done;
    }
    status_int = _I2CRead(Dev, data, 1);
    if (status_int != 0) {
        Status = VL53L0X_ERROR_CONTROL_INTERFACE;
    }
done:
    VL53L0X_PutI2cBus();
    return Status;
}

//======================================================================
//
//======================================================================
VL53L0X_Error VL53L0X_RdWord(VL53L0X_DEV Dev, uint8_t index, uint16_t *data) {
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    int32_t status_int;

    VL53L0X_GetI2cBus();
    status_int = _I2CWrite(Dev, &index, 1);

    if( status_int ){
        Status = VL53L0X_ERROR_CONTROL_INTERFACE;
        goto done;
    }
    status_int = _I2CRead(Dev, _I2CBuffer, 2);
    if (status_int != 0) {
        Status = VL53L0X_ERROR_CONTROL_INTERFACE;
        goto done;
    }

    *data = ((uint16_t)_I2CBuffer[0]<<8) + (uint16_t)_I2CBuffer[1];
done:
    VL53L0X_PutI2cBus();
    return Status;
}

//======================================================================
//
//======================================================================
VL53L0X_Error VL53L0X_RdDWord(VL53L0X_DEV Dev, uint8_t index, uint32_t *data) {
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    int32_t status_int;

    VL53L0X_GetI2cBus();
    status_int = _I2CWrite(Dev, &index, 1);
    if (status_int != 0) {
        Status = VL53L0X_ERROR_CONTROL_INTERFACE;
        goto done;
    }
    status_int = _I2CRead(Dev, _I2CBuffer, 4);
    if (status_int != 0) {
        Status = VL53L0X_ERROR_CONTROL_INTERFACE;
        goto done;
    }

    *data = ((uint32_t)_I2CBuffer[0]<<24) + ((uint32_t)_I2CBuffer[1]<<16) + ((uint32_t)_I2CBuffer[2]<<8) + (uint32_t)_I2CBuffer[3];

done:
    VL53L0X_PutI2cBus();
    return Status;
}

//======================================================================
//
//======================================================================

VL53L0X_Error VL53L0X_PollingDelay(VL53L0X_DEV Dev) 
{
    VL53L0X_Error status = VL53L0X_ERROR_NONE;

    // do nothing
    VL53L0X_OsDelay();
    return status;
}
#ifdef ___NOP2
#endif
//======================================================================
//
//======================================================================
void VL53L0X_OsDelay(void)
{
    uint16_t    i;
    
    for(i=0; i<0xffff; i++){
        
    }
}