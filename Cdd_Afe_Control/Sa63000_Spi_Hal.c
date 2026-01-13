/*
 *******************************************************************************
 * 文件名：Sa63000_Spi_Hal.c
 * 功能描述：实现Sa63000的spi抽象模块
 * 作者：dwyane tade <tandehuai@evpt.com.cn>
 * 创建日期：2025-12-15
 * 版本：V1.0.0
 * 最后修改：
 * 修改说明：
 * 版权信息：Copyright (C) 2025 天津易鼎丰动力科技有限公司 All Rights Reserved.
 * 注意事项：1、不要修改函数定义 2、Ssh_valHandle_Mp/Ssh_valConfig_Mp释放给Afe模块调用，不要修改
 *******************************************************************************
 */

#include "Sa63000_Spi_Hal.h"

#if (CCORE3011 == MCU_CHIP_TYPE)
const Sa63000_Spi_Hal_Config Ssh_valConfig_Mp = {
    .channel = SpiChannel_AFE_SA63000,
    .sequence = SpiSequence_AFE_SA63000,
};

/**
 * @brief  延迟函数
 * @param  cnt 计数个数 / 60个数1us
 * @retval none
 */
#pragma optimize=0
__attribute__((noinline))
void Sa63000_Spi_Delay(uint32_t cnt)
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

uint8_t Sa63000_GetSpiReadyStatus(void)
{
#if (CCORE3011 == MCU_CHIP_TYPE)
    return SIUL.GPDI[106].R;
#elif (ZX146 == MCU_CHIP_TYPE)
    //TODO
#endif
}

/**
 * @brief  发送Wake Ping唤醒Sa63000
 * @param  cnt 计数个数 / 60个数1us
 * @retval none
 */
void Sa63000_Spi_Hal_Init(const Sa63000_Spi_Hal_Config* config)
{
    if(NULL == config)
        return;

#if (CCORE3011 == MCU_CHIP_TYPE)

#if SA63000_CONFIG_SPI_READY
    SIUL.PCR[106].R = 0x005c;
#if SA63000_CONFIG_VIO
#else
    Sa63000_Spi_Delay(SA63000_DELAY_10US);
#endif
#endif

#if SA63000_CONFIG_VIO
    SIUL.PCR[105].R = 0x009c;
    SIUL.GPDO[105].R = 0x01;
    Sa63000_Spi_Delay(SA63000_DELAY_10US);
#endif

    SIUL.PCR[104].R = 0x009c;
    SIUL.GPDO[104].R = 0x00;
    Sa63000_Spi_Delay(SA63000_CONFIG_DELAY_1US_CNT);
    SIUL.PCR[110].R = 0x009c;
    SIUL.GPDO[110].R = 0x00;
    Sa63000_Spi_Delay(SA63000_DELAY_2_75MS);
    SIUL.GPDO[110].R = 0x01;
    Sa63000_Spi_Delay(SA63000_CONFIG_DELAY_1US_CNT);
    SIUL.GPDO[104].R = 0x01;

    /* 重新配置CS和MOSI */
    SIUL.PCR[104].R = 0x6c9c;
    SIUL.PCR[110].R = 0x699c;
    Sa63000_Spi_Delay(SA63000_DELAY_2_2MS);

#elif (ZX146 == MCU_CHIP_TYPE)
    //TODO
#endif
}

Sa63000_Spi_Hal_ErrCode Sa63000_Spi_Hal_Transfer(
    const Sa63000_Spi_Hal_Config* config,
    const uint8_t* tx_buf,
    uint8_t* rx_buf,
    uint16_t len
)
{
    if ((NULL == config) || (0 == len) || ((NULL == tx_buf) && (rx_buf == NULL)))
        return Spi_Hal_Err_Param;

#if (CCORE3011 == SA63000_MCU_CHIP_TYPE)
    Std_ReturnType Ssh_valRet_Lo = E_OK;

    Ssh_valRet_Lo = Spi_SetupEB(config->channel, tx_buf, rx_buf, len);
    if(Ssh_valRet_Lo != E_OK)
        return Spi_Hal_Err_Trans;
    Ssh_valRet_Lo = Spi_SyncTransmit(config->sequence);
    if(Ssh_valRet_Lo != E_OK)
        return Spi_Hal_Err_Trans;
    Sa63000_Spi_Delay(SA63000_DELAY_CMD_FRAME(len));
#elif (ZX146 == SA63000_MCU_CHIP_TYPE)
    //TODO
#endif
    return Spi_Hal_Ok;
}
