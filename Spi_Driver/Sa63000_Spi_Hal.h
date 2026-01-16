/*
 *******************************************************************************
 * 文件名：Sa63000_Spi_Hal.h
 * 功能描述：定义Sa63000的spi的错误码/模式/配置结构体
 * 作者：dwyane tade <tandehuai@evpt.com.cn>
 * 创建日期：2025-12-15
 * 版本：V1.0.0
 * 最后修改：
 * 修改说明：
 * 版权信息：Copyright (C) 2025 天津易鼎丰动力科技有限公司 All Rights Reserved.
 * 注意事项：
 *******************************************************************************
 */

#ifndef __SA63000_SPI_HAL_H_
#define __SA63000_SPI_HAL_H_

#include <stdint.h>
#include "Sa63000_Spi_Hal_Config.h"
#if (CCORE3011 == SA63000_CHIP_TYPE)
#include "Spi.h"
#include "Spi_Cfg.h"
#include "CCFC3011PT.h"
#elif (ZX146 == SA63000_CHIP_TYPE)
//TODO
#endif

/********************************* 类型重定义 ****************************************/
/*
 * Spi_Single_Read: 读取单个设备
 * Spi_Stack_Read: 读取多个设备
 */
typedef enum {
    Spi_Single_Read = 0,
    Spi_Stack_Read  = 2,
} Sa63000_Spi_RType;

/*
 * Spi_Single_Write: 写入单个设备
 * Spi_Stack_Write: 写入多个设备
 * Spi_Addressing: 寻址命令
 */
typedef enum {
    Spi_Single_Write    = 1,
    Spi_Stack_Write     = 3,    // SA63000 and SA63122
    Spi_Addressing      = 4,
    Spi_BroadCast_Write = 5,    // only for SA63280
} Sa63000_Spi_WType;

/*
 * Spi_Response_Frame: 响应帧
 * Spi_Command_Frame: 命令帧
 */
typedef enum {
    Spi_Response_Frame = 0,
    Spi_Command_Frame,    
} Sa63000_Spi_FrameType;

/*
 * Spi_Dev_Addr_xx: 设备地址x
 */
typedef enum {
    Spi_Dev_Addr_00 = 0,
    Spi_Dev_Addr_01 = 1,
    Spi_Dev_Addr_02 = 2,
    Spi_Dev_Addr_03 = 3,
    Spi_Dev_Addr_04 = 4,
    Spi_Dev_Addr_05 = 5,
    Spi_Dev_Addr_06 = 6,
    Spi_Dev_Addr_07 = 7,
    Spi_Dev_Addr_08 = 8,    
} Sa63000_Spi_DevAddrType;

/*
 * Spi_Hal_Ok: 成功
 * Spi_Hal_Err_Init: 初始化失败
 * Spi_Hal_Err_Param: 错误的参数
 * Spi_Hal_Err_Trans: 传输失败
 */
typedef enum {
    Spi_Hal_Ok        = 0,
    Spi_Hal_Err_Init  = 1,
    Spi_Hal_Err_Param = 2,
    Spi_Hal_Err_Trans = 3
} Sa63000_Spi_Hal_ErrCode;

/*
 * Spi_Hal_Modex：模式x
 */
typedef enum {
    Spi_Hal_Mode0 = 0,
    Spi_Hal_Mode1 = 1,
    Spi_Hal_Mode2 = 2,
    Spi_Hal_Mode3 = 3
} Sa63000_Spi_Hal_Mode;

/*
 * mode：模式
 * baudrate：波特率(1M = 1000000)
 */
typedef struct {
    Sa63000_Spi_Hal_Mode mode;
    uint32_t baudrate;
#if (CCORE3011 == SA63000_CHIP_TYPE)
    Spi_ChannelType channel;    /* mcal填充数据接口的索引 */
    Spi_SequenceType sequence;  /* mcal发送数据接口的索引*/
#elif (ZX146 == SA63000_CHIP_TYPE)
//TODO
#endif
} Sa63000_Spi_Hal_Config;

/********************************* 宏定义 ****************************************/
#define SA63000_DELAY_10US                  10 * (SA63000_CONFIG_DELAY_1US_CNT)
#define SA63000_DELAY_2_75MS                2750 * (SA63000_CONFIG_DELAY_1US_CNT)
#define SA63000_DELAY_2_2MS                 2200 * (SA63000_CONFIG_DELAY_1US_CNT)
#define SA63000_DELAY_CMD_FRAME(byte_num)   (uint32_t)(SA63000_CONFIG_DELAY_1US_CNT * (byte_num * (6.5 + 1.875) -\
                                            (1.28 + 1.6) + 15))
#define SA63000_RES_FRAME_DATA_LEN          120
#define SA63000_CMD_FRAME_DATA_LEN          16
#define SA63000_CMD_FRAME_COMB_INIT(frame_type, rw_type, data_len)\
                                            (uint8_t)((frame_type << 7) | (rw_type << 4) | (data_len - 1))

extern const Sa63000_Spi_Hal_Config Ssh_valConfig_Mp;
extern uint8_t Sa63000_GetSpiReadyStatus(void);
extern void Sa63000_Spi_Delay(uint32_t cnt);
extern void Sa63000_Spi_Hal_Init(const Sa63000_Spi_Hal_Config* config);
extern Sa63000_Spi_Hal_ErrCode Sa63000_Spi_Hal_Transfer(
    const Sa63000_Spi_Hal_Config* config,
    const uint8_t* tx_buf,
    uint8_t* rx_buf,
    uint16_t len
);

#endif /* __SA63000_SPI_HAL_H_ */
