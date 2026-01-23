#include "Cdd_Sa63000_Driver.h"

#define SA63000_DELAY_WAKE_UP_AFE   ((10 + 2 * SA63XXX_CONFIG_AFE_NUM ) * SA63XXX_CONFIG_DELAY_1MS_CNT)
#define SA63000_DELAY_10US          10 * (SA63XXX_CONFIG_DELAY_1US_CNT)
#define SA63000_DELAY_2_75MS        2750 * (SA63XXX_CONFIG_DELAY_1US_CNT)
#define SA63000_DELAY_2_2MS         (2 * SA63XXX_CONFIG_DELAY_1MS_CNT + 2 * SA63XXX_CONFIG_DELAY_100US_CNT)

void Sa63000_WakeUpDevices(void)
{
    uint8 Csd_valData_Lo = 0;

#if (CCORE3011 == MCU_CHIP_TYPE)

#if SA63000_CONFIG_SPI_READY
    SIUL.PCR[106].R = 0x005c;
#if SA63000_CONFIG_VIO
#else
    Sa63xxx_Spi_Delay(SA63000_DELAY_10US);
#endif
#endif

#if SA63000_CONFIG_VIO
    SIUL.PCR[105].R = 0x009c;
    SIUL.GPDO[105].R = 0x01;
    Sa63xxx_Spi_Delay(SA63000_DELAY_10US);
#endif

    SIUL.PCR[104].R = 0x009c;
    SIUL.GPDO[104].R = 0x00;
    Sa63xxx_Spi_Delay(SA63XXX_CONFIG_DELAY_1US_CNT);
    SIUL.PCR[110].R = 0x009c;
    SIUL.GPDO[110].R = 0x00;
    Sa63xxx_Spi_Delay(SA63000_DELAY_2_75MS);
    SIUL.GPDO[110].R = 0x01;
    Sa63xxx_Spi_Delay(SA63XXX_CONFIG_DELAY_1US_CNT);
    SIUL.GPDO[104].R = 0x01;

    /* 重新配置CS和MOSI */
    SIUL.PCR[104].R = 0x6c9c;
    SIUL.PCR[110].R = 0x699c;
    Sa63xxx_Spi_Delay(SA63000_DELAY_2_2MS);

#elif (ZX146 == MCU_CHIP_TYPE)
    //TODO
#endif

    /* 配置Sa63000 */
    Csd_valData_Lo = 0x00;
    Sa63xxx_WriteRegister(Sa63xxx_Spi_Dev_Addr_00, (uint16)SA63000_COMM_CONF, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo, 1);

    /* 唤醒AFE和BJB */
    Csd_valData_Lo = 0x04;
    Sa63xxx_WriteRegister(Sa63xxx_Spi_Dev_Addr_00, SA63000_CONTROL, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo, 1);
    Sa63xxx_Spi_Delay(SA63000_DELAY_WAKE_UP_AFE);

    /* 寻址 */
    Csd_valData_Lo = 0x81;
    Sa63xxx_WriteRegister(0, 0, Sa63xxx_Spi_Addressing, &Csd_valData_Lo, 1);
    Sa63xxx_ResponseRegister(1);
    Csd_valData_Lo = 0x00;
    Sa63xxx_WriteRegister(0, (uint16)CTRL2, Sa63xxx_Spi_Stack_Write, &Csd_valData_Lo, 1);
}
