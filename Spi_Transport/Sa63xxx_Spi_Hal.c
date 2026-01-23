/*
 *******************************************************************************
 * 文件名：Sa63000_Spi_Hal.c
 * 功能描述：实现对单片机SPI模块的抽象，提供Sa63xxx通用的SPI读写函数
 * 作者：dwyane tade <tandehuai@evpt.com.cn>
 * 创建日期：2026-01-23
 * 版本：V1.0.0
 * 最后修改：
 * 修改说明：
 * 版权信息：Copyright (C) 2025 天津易鼎丰动力科技有限公司 All Rights Reserved.
 *******************************************************************************
 */

#include "Sa63xxx_Spi_Hal.h"

#if (CCORE3011 == MCU_CHIP_TYPE)
const Sa63xxx_Spi_Hal_Config SpiHal_valConfig_Mp = {
    .channel = SpiChannel_AFE_SA63000,
    .sequence = SpiSequence_AFE_SA63000,
};

/**
 * @brief  延迟函数
 * @param  cnt 计数个数 / 55个数1us
 * @retval none
 */
#pragma optimize=0
__attribute__((noinline))
void Sa63xxx_Spi_Delay(uint32_t cnt)
{
    volatile uint32_t i = 0;
    volatile uint32_t dummy = 0;

    __asm__ volatile ("nop");
    for(i = 0; i < cnt; i++)
    {
        __asm__ volatile ("nop");
        __asm__ volatile ("nop");
        __asm__ volatile ("nop");
        __asm__ volatile ("nop");
        dummy++;
    }
}
#pragma optimize=reset

#elif (ZX146 == MCU_CHIP_TYPE)
//TODO
#endif

uint8_t Sa63xxx_GetSpiReadyStatus(void)
{
#if (CCORE3011 == MCU_CHIP_TYPE)
    return SIUL.GPDI[106].R;
#elif (ZX146 == MCU_CHIP_TYPE)
    //TODO
#endif
}

Sa63xxx_Spi_Hal_ErrCode Sa63xxx_Spi_Hal_Transfer(
    const Sa63xxx_Spi_Hal_Config* config,
    const uint8_t* tx_buf,
    uint8_t* rx_buf,
    uint16_t len
)
{
    if ((NULL == config) || (0 == len) || ((NULL == tx_buf) && (rx_buf == NULL)))
        return Sa63xxx_Spi_Hal_Err_Param;

#if (CCORE3011 == MCU_CHIP_TYPE)
    Std_ReturnType Ssh_valRet_Lo = E_OK;

    Ssh_valRet_Lo = Spi_SetupEB(config->channel, tx_buf, rx_buf, len);
    if(Ssh_valRet_Lo != E_OK)
        return Sa63xxx_Spi_Hal_Err_Trans;
    Ssh_valRet_Lo = Spi_SyncTransmit(config->sequence);
    if(Ssh_valRet_Lo != E_OK)
        return Sa63xxx_Spi_Hal_Err_Trans;
    Sa63xxx_Spi_Delay(SA63XXX_DELAY_CMD_FRAME(len));
#elif (ZX146 == MCU_CHIP_TYPE)
    //TODO
#endif
    return Sa63xxx_Spi_Hal_Ok;
}
