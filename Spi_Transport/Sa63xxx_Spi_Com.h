#ifndef __SA63XXX_SPI_H_
#define __SA63XXX_SPI_H_

#include "Sa63xxx_Reg_Types.h"
#include "Sa63xxx_Spi_Hal.h"

#define SA63XXX_SPI_COM_CRC_TABLE_SIZE      256
#define SA63XXX_RES_FRAME_DATA_LEN          120
#define SA63XXX_CMD_FRAME_DATA_LEN          16
#define SA63XXX_CMD_FRAME_COMB_INIT(frame_type, rw_type, data_len)\
                                            (uint8_t)((frame_type << 7) | (rw_type << 4) | (data_len - 1))

/*
 * Spi_Single_Read: 读取单个设备
 * Spi_Stack_Read: 读取多个设备
 */
typedef enum {
    Sa63xxx_Spi_Single_Read = 0,
    Sa63xxx_Spi_Stack_Read  = 2,
} Sa63xxx_Spi_RType;

/*
 * Spi_Single_Write: 写入单个设备
 * Spi_Stack_Write: 写入多个设备
 * Spi_Addressing: 寻址命令
 * Spi_BroadCast_Write 广播写
 */
typedef enum {
    Sa63xxx_Spi_Single_Write    = 1,
    Sa63xxx_Spi_Stack_Write     = 3,    // only for SA63000 and SA63122
    Sa63xxx_Spi_Addressing      = 4,
    Sa63xxx_Spi_BroadCast_Write = 5,    // only for SA63280
} Sa63xxx_Spi_WType;

/*
 * Spi_Response_Frame: 响应帧
 * Spi_Command_Frame: 命令帧
 */
typedef enum {
    Sa63xxx_Spi_Response_Frame = 0,
    Sa63xxx_Spi_Command_Frame,    
} Sa63xxx_Spi_FrameType;

/*
 * Spi_Dev_Addr_xx: 设备地址x
 */
typedef enum {
    Sa63xxx_Spi_Dev_Addr_00 = 0,
    Sa63xxx_Spi_Dev_Addr_01 = 1,
    Sa63xxx_Spi_Dev_Addr_02 = 2,
    Sa63xxx_Spi_Dev_Addr_03 = 3,
    Sa63xxx_Spi_Dev_Addr_04 = 4,
    Sa63xxx_Spi_Dev_Addr_05 = 5,
    Sa63xxx_Spi_Dev_Addr_06 = 6,
    Sa63xxx_Spi_Dev_Addr_07 = 7,
    Sa63xxx_Spi_Dev_Addr_08 = 8,    
    Sa63xxx_Spi_Dev_Addr_09 = 9,
    Sa63xxx_Spi_Dev_Addr_10 = 10,
    Sa63xxx_Spi_Dev_Addr_11 = 11,
    Sa63xxx_Spi_Dev_Addr_12 = 12,
    Sa63xxx_Spi_Dev_Addr_13 = 13,
    Sa63xxx_Spi_Dev_Addr_14 = 14,
    Sa63xxx_Spi_Dev_Addr_15 = 15,
    Sa63xxx_Spi_Dev_Addr_16 = 16, 
} Sa63xxx_Spi_DevAddrType;

/*
 *******************************************************************************
 * 文件名：Sa63xxx_Spi_Com.c
 * 功能描述：实现Sa63xxx的通信协议层，完成和芯片的读/写/响应操作
 * 作者：dwyane tade <tandehuai@evpt.com.cn>
 * 创建日期：2026-01-23
 * 版本：V1.0.0
 * 最后修改：
 * 修改说明：
 * 版权信息：Copyright (C) 2025 天津易鼎丰动力科技有限公司 All Rights Reserved.
 *******************************************************************************
 */

#include "Sa63xxx_Spi_Com.h"

extern uint8_t SpiCom_valTxBuffer_Mp[SA63XXX_CONFIG_SPI_TX_BUFFER_SIZE];
extern uint16_t Crc16_Modbus(uint8_t* data_input, uint8_t length);
extern uint8_t* Sa63xxx_GetRxData(void);
extern Std_ReturnType Sa63xxx_ResponseRegister(uint8_t data_len);
extern Std_ReturnType Sa63xxx_WriteRegister(
    Sa63xxx_Spi_DevAddrType dev_addr,
    uint16 reg_addr,
    Sa63xxx_Spi_WType w_type,
    uint8_t* data,
    uint8_t data_len
);
extern Std_ReturnType Sa63xxx_ReadRegister(
    Sa63xxx_Spi_DevAddrType dev_addr,
    uint16 reg_addr,
    Sa63xxx_Spi_RType r_type,
    uint8_t data_len
);

#endif /* __SA63XXX_SPI_H_ */
