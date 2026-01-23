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
#include "Sa63xxx_Spi_Hal_Config.h"
#if (CCORE3011 == SA63000_CHIP_TYPE)
#include "Spi.h"
#include "Spi_Cfg.h"
#include "CCFC3011PT.h"
#elif (ZX146 == SA63000_CHIP_TYPE)
//TODO
#endif

#define SA63XXX_DELAY_CMD_FRAME(byte_num)   (uint32_t)(SA63XXX_CONFIG_DELAY_1US_CNT * (byte_num * (6.5 + 1.875) -\
                                            (1.28 + 1.6) + 15))

/*
 * Sa63xxx_Spi_Hal_Ok: 成功
 * Sa63xxx_Spi_Hal_Err_Init: 初始化失败
 * Sa63xxx_Spi_Hal_Err_Param: 错误的参数
 * Sa63xxx_Spi_Hal_Err_Trans: 传输失败
 */
typedef enum {
    Sa63xxx_Spi_Hal_Ok          = 0,
    Sa63xxx_Spi_Hal_Err_Init    = 1,
    Sa63xxx_Spi_Hal_Err_Param   = 2,
    Sa63xxx_Spi_Hal_Err_Trans   = 3
} Sa63xxx_Spi_Hal_ErrCode;

/*
 * Spi_Hal_Modex：模式x
 */
typedef enum {
    Sa63xxx_Spi_Hal_Mode0   = 0,
    Sa63xxx_Spi_Hal_Mode1   = 1,
    Sa63xxx_Spi_Hal_Mode2   = 2,
    Sa63xxx_Spi_Hal_Mode3   = 3
} Sa63xxx_Spi_Hal_Mode;

/*
 * mode：模式
 * baudrate：波特率(1M = 1000000)
 */
typedef struct {
    Sa63xxx_Spi_Hal_Mode mode;
    uint32_t baudrate;
#if (CCORE3011 == SA63000_CHIP_TYPE)
    Spi_ChannelType channel;    /* mcal填充数据接口的索引 */
    Spi_SequenceType sequence;  /* mcal发送数据接口的索引*/
#elif (ZX146 == SA63000_CHIP_TYPE)
//TODO
#endif
} Sa63xxx_Spi_Hal_Config;

extern const Sa63xxx_Spi_Hal_Config SpiHal_valConfig_Mp;
extern void Sa63xxx_Spi_Delay(uint32_t cnt);
extern uint8_t Sa63xxx_GetSpiReadyStatus(void);
extern Sa63xxx_Spi_Hal_ErrCode Sa63xxx_Spi_Hal_Transfer(
    const Sa63xxx_Spi_Hal_Config* config,
    const uint8_t* tx_buf,
    uint8_t* rx_buf,
    uint16_t len
);

#endif /* __SA63000_SPI_HAL_H_ */
