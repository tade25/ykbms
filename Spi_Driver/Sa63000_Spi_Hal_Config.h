/*
 *******************************************************************************
 * 文件名：Sa63000_Spi_Hal_Config.h
 * 功能描述：定义一些Sa63000的一些必要的宏定义
 * 作者：dwyane tade <tandehuai@evpt.com.cn>
 * 创建日期：2025-12-24
 * 版本：V1.0.0
 * 最后修改：
 * 修改说明：
 * 版权信息：Copyright (C) 2025 天津易鼎丰动力科技有限公司 All Rights Reserved.
 * 注意事项：
 *******************************************************************************
 */

#ifndef __SA63000_SPI_HAL_CONFIG_H_
#define __SA63000_SPI_HAL_CONFIG_H_

#define MCU_CHIP_TYPE                           CCORE3011
// #define MCU_CHIP_TYPE                           ZX146
#define SA63000_CONFIG_VIO                      1
#define SA63000_CONFIG_SPI_READY                1
#define SA63000_CONFIG_SPI_TX_BUFFER_SIZE       70
#define SA63000_CONFIG_SPI_RX_BUFFER_SIZE       70
#define SA63000_CONFIG_DELAY_1US_CNT            60

#endif __SA63000_SPI_HAL_CONFIG_H_
