#include "Cdd_Sa63122_Driver.h"

static Sa63122_DriverType Csd_valDrv_Mp;
static Sa63122_DriverType* Csd_valDrvPtr_Mp = &Csd_valDrv_Mp;

Sa63122_DriverType* Sa63122_DriverGet(void)
{
    return Csd_valDrvPtr_Mp;
}

/**
 * @brief  计算配置寄存器的CRC值
 * @param  none
 * @retval none
 */
void Sa63122_Reg_CalcCrc(uint8_t dev_addr)
{
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t start = 0;
    uint8_t final = 0;
    uint8_t Buff[193];
    uint16_t crc = 0;

    start = (dev_addr == 0xff) ? 0 : dev_addr;
    final = (dev_addr == 0xff) ? AFE_NUMBER : (dev_addr + 1);

    for(i = start;i < final;i++)
    {
        Buff[0]  = Csd_valDrvPtr_Mp->reg_record[i].A_DEV_ADD1.R;
        Buff[1]  = Csd_valDrvPtr_Mp->reg_record[i].A_DEV_ADD2.R;
        Buff[2]  = Csd_valDrvPtr_Mp->reg_record[i].A_COMM_CONF1.R;
        Buff[3]  = Csd_valDrvPtr_Mp->reg_record[i].A_COMM_CONF2.R;
        Buff[4]  = Csd_valDrvPtr_Mp->reg_record[i].A_COMM_TO.R;
        Buff[5]  = Csd_valDrvPtr_Mp->reg_record[i].A_RSVD_0005;
        Buff[6]  = Csd_valDrvPtr_Mp->reg_record[i].A_COMP_CONF1.R;
        Buff[7]  = Csd_valDrvPtr_Mp->reg_record[i].A_COMP_CONF2.R;
        Buff[8]  = Csd_valDrvPtr_Mp->reg_record[i].A_ADC_CONF.R;
        Buff[9]  = Csd_valDrvPtr_Mp->reg_record[i].A_RSVD_0009;
        Buff[10] = Csd_valDrvPtr_Mp->reg_record[i].A_MEA_CONF.R;
        Buff[11] = Csd_valDrvPtr_Mp->reg_record[i].A_RSVD_000B;
        Buff[12] = Csd_valDrvPtr_Mp->reg_record[i].A_RSVD_000C;
        Buff[13] = Csd_valDrvPtr_Mp->reg_record[i].A_SLP_MON_CONF.R;
        Buff[14] = Csd_valDrvPtr_Mp->reg_record[i].A_OVUV_OTUT_CONF1.R;
        Buff[15] = Csd_valDrvPtr_Mp->reg_record[i].A_OVUV_OTUT_CONF2.R;
        Buff[16] = Csd_valDrvPtr_Mp->reg_record[i].A_OVUV_OTUT_CONF3.R;
        Buff[17] = Csd_valDrvPtr_Mp->reg_record[i].A_OVUV_OTUT_CONF4.R;
        Buff[18] = Csd_valDrvPtr_Mp->reg_record[i].A_OVUV_OTUT_CONF5.R;
        Buff[19] = Csd_valDrvPtr_Mp->reg_record[i].A_OVUV_OTUT_CONF6.R;
        Buff[20] = Csd_valDrvPtr_Mp->reg_record[i].A_OVUV_OTUT_CONF7.R;
        Buff[21] = Csd_valDrvPtr_Mp->reg_record[i].A_CB_CONF1.R;
        Buff[22] = Csd_valDrvPtr_Mp->reg_record[i].A_CB_CONF2.R;
        Buff[23] = Csd_valDrvPtr_Mp->reg_record[i].A_CB_CONF3.R;
        Buff[24] = Csd_valDrvPtr_Mp->reg_record[i].A_TWARN_CONF.R;
        Buff[25] = Csd_valDrvPtr_Mp->reg_record[i].A_GPIO_DO_EN1.R;
        Buff[26] = Csd_valDrvPtr_Mp->reg_record[i].A_GPIO_DO_EN2.R;
        Buff[27] = Csd_valDrvPtr_Mp->reg_record[i].A_GPIO_DI_EN1.R;
        Buff[28] = Csd_valDrvPtr_Mp->reg_record[i].A_GPIO_DI_EN2.R;
        Buff[29] = Csd_valDrvPtr_Mp->reg_record[i].A_GPIO_WEAK_PUPD_EN1.R;
        Buff[30] = Csd_valDrvPtr_Mp->reg_record[i].A_GPIO_WEAK_PUPD_EN2.R;
        Buff[31] = Csd_valDrvPtr_Mp->reg_record[i].A_FLT_SUM_MSK.R;
        Buff[32] = Csd_valDrvPtr_Mp->reg_record[i].A_RSVD_0101;
        Buff[33] = Csd_valDrvPtr_Mp->reg_record[i].A_RSVD_0102;
        Buff[34] = Csd_valDrvPtr_Mp->reg_record[i].A_RSVD_0103;
        Buff[35] = Csd_valDrvPtr_Mp->reg_record[i].A_OV_FLT_MSK1.R;
        Buff[36] = Csd_valDrvPtr_Mp->reg_record[i].A_OV_FLT_MSK2.R;
        Buff[37] = Csd_valDrvPtr_Mp->reg_record[i].A_OV_FLT_MSK3.R;
        Buff[38] = Csd_valDrvPtr_Mp->reg_record[i].A_UV_FLT_MSK1.R;
        Buff[39] = Csd_valDrvPtr_Mp->reg_record[i].A_UV_FLT_MSK2.R;
        Buff[40] = Csd_valDrvPtr_Mp->reg_record[i].A_UV_FLT_MSK3.R;
        Buff[41] = Csd_valDrvPtr_Mp->reg_record[i].A_CELL_COMP_FLT_MSK1.R;
        Buff[42] = Csd_valDrvPtr_Mp->reg_record[i].A_CELL_COMP_FLT_MSK2.R;
        Buff[43] = Csd_valDrvPtr_Mp->reg_record[i].A_CELL_COMP_FLT_MSK3.R;
        Buff[44] = Csd_valDrvPtr_Mp->reg_record[i].A_GPIO_COMP_FLT_MSK1.R;
        Buff[45] = Csd_valDrvPtr_Mp->reg_record[i].A_GPIO_COMP_FLT_MSK2.R;
        Buff[46] = Csd_valDrvPtr_Mp->reg_record[i].A_OT_FLT_MSK1.R;
        Buff[47] = Csd_valDrvPtr_Mp->reg_record[i].A_OT_FLT_MSK2.R;
        Buff[48] = Csd_valDrvPtr_Mp->reg_record[i].A_UT_FLT_MSK1.R;
        Buff[49] = Csd_valDrvPtr_Mp->reg_record[i].A_UT_FLT_MSK2.R;
        Buff[50] = Csd_valDrvPtr_Mp->reg_record[i].A_SYS_FLT_MSK1.R;
        Buff[51] = Csd_valDrvPtr_Mp->reg_record[i].A_SYS_FLT_MSK2.R;
        Buff[52] = Csd_valDrvPtr_Mp->reg_record[i].A_RSVD_0115;
        Buff[53] = Csd_valDrvPtr_Mp->reg_record[i].A_SYS_FLT_MSK4.R;
        Buff[54] = Csd_valDrvPtr_Mp->reg_record[i].A_SYS_FLT_MSK5.R;

        for(j = 0; j < SA63122_FACT_REG1_MAX; j++)
        {
            Buff[j + 55] = Csd_valDrvPtr_Mp->reg_record[i].FACT_REG1[j];
        }

        for(j = 0; j < SA63122_FACT_REG2_MAX; j++)
        {
            Buff[j + 65] = Csd_valDrvPtr_Mp->reg_record[i].FACT_REG2[j];
        }

        crc = Crc16_Modbus(&Buff[0], 193);
        Csd_valDrvPtr_Mp->reg_record[i].A_CONF_CRC_H = (crc >> 8) & 0xff;
        Csd_valDrvPtr_Mp->reg_record[i].A_CONF_CRC_L = (crc >> 0) & 0xff;
    }
}

/**
 * @brief  配置Sa63122芯片的寄存器CRC
 * @param  none
 * @retval none
 */
void Sa63122_Reg_WriteCrc(uint8_t dev_addr)
{
    uint8_t i = 0;
    uint8_t start = 0;
    uint8_t final = 0;
    uint8_t Cas_valData_Lo[2] = {0x00};

    start = (dev_addr == 0xff) ? 0 : dev_addr;
    final = (dev_addr == 0xff) ? AFE_NUMBER : (dev_addr + 1);

    for(i = start;i < final;i++)
    {
        Cas_valData_Lo[0] = Csd_valDrvPtr_Mp->reg_record[i].A_CONF_CRC_H;
        Cas_valData_Lo[1] = Csd_valDrvPtr_Mp->reg_record[i].A_CONF_CRC_L;
        Sa63122_WriteRegister(0, CONF_CRC_H, Spi_Stack_Write, &Cas_valData_Lo[0], 2);
    }
}

/**
 * @brief  配置Sa63000芯片
 * @param  none
 * @retval none
 */
void Sa63000_RegConfig(void)
{
    uint8_t Cas_valData_Lo = 0x00;

    Cas_valData_Lo = 0x00;
    Sa63122_WriteRegister(Spi_Dev_Addr_00, Sa63000_Comm_Conf, Spi_Single_Write, &Cas_valData_Lo, 1);
}

/**
 * @brief  给AFE发送Wake Tone
 * @param  none
 * @retval none
 */
void Sa63000_SendWakeTone(void)
{
    uint8_t Cas_valData_Lo = 0x00;

    Cas_valData_Lo = 0x04;
    Sa63122_WriteRegister(Spi_Dev_Addr_00, Sa63000_Control, Spi_Single_Write, &Cas_valData_Lo, 1);
    Sa63000_Spi_Delay(SA63122_DELAY_78MS);
}

/**
 * @brief  完成菊花链中的芯片寻址
 * @param  none
 * @retval none
 */
void Sa63122_SendAddressing(void)
{
    uint8_t Cas_valData_Lo = 0x00;

    Cas_valData_Lo = 0x81;
    Sa63122_WriteRegister(0, 0, Spi_Addressing, &Cas_valData_Lo, 1);
    Sa63122_ResponseRegister(1);
    Cas_valData_Lo = 0x00;
    Sa63122_WriteRegister(Spi_Dev_Addr_00, CTRL2, Spi_Stack_Write, &Cas_valData_Lo, 1);
}

/**
 * @brief  读取工厂寄存器
 * @param  none
 * @retval none
 */
void Sa63122_ReadFact(void)
{
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t* Csd_valRxDataPtr_Lo = NULL;

    /* FACT1~FACT10 */
    Csd_valRxDataPtr_Lo = Sa63122_GetRxData();
    Sa63122_ReadRegister(Spi_Dev_Addr_01, FACT_REG1, Spi_Single_Read, 10);
    Sa63122_ResponseRegister(10);
    for(i = 0;i < 1;i++)
    {
        memcpy(&Csd_valDrvPtr_Mp->reg_record[i].FACT_REG1[0], Csd_valRxDataPtr_Lo, 10);
    }

    /* FACT11~FACT138 */
    Sa63122_ReadRegister(Spi_Dev_Addr_01, FACT_REG11, Spi_Single_Read, 64);
    Sa63122_ResponseRegister(64);
    for(i = 0;i < 1;i++)
    {
        memcpy(&Csd_valDrvPtr_Mp->reg_record[i].FACT_REG2[0], Csd_valRxDataPtr_Lo, 64);
    }

    Sa63122_ReadRegister(Spi_Dev_Addr_01, FACT_REG74, Spi_Single_Read, 64);
    Sa63122_ResponseRegister(64);
    for(i = 0;i < 1;i++)
    {
        memcpy(&Csd_valDrvPtr_Mp->reg_record[i].FACT_REG2[64], Csd_valRxDataPtr_Lo, 64);
    }
}

/**
 * @brief  完成配置寄存器的设置
 * @param  none
 * @retval none
 */
void Sa63122_RegConfig(void)
{
    uint8_t i = 0;
    uint8_t Cas_valData_Lo[16] = {0};

    /******************************************** Config Start ********************************************/
    for(i = 0;i < 1;i++)
    {
        // Csd_valDrvPtr_Mp->reg_record[i].A_DEV_ADD1.R = i + 1;
        Csd_valDrvPtr_Mp->reg_record[i].A_DEV_ADD1.R = 0x81;
        Csd_valDrvPtr_Mp->reg_record[i].A_DEV_ADD2.R = 0;
    }
    
    /* COMM_CONF1/2/TO */
    Cas_valData_Lo[0] = 0x08;
    Cas_valData_Lo[1] = 0x00;
    Cas_valData_Lo[2] = 0xBB;
    for(i = 0;i < 1;i++)
    {
        Csd_valDrvPtr_Mp->reg_record[i].A_COMM_CONF1.R = Cas_valData_Lo[0];
        Csd_valDrvPtr_Mp->reg_record[i].A_COMM_CONF2.R = Cas_valData_Lo[1];
        Csd_valDrvPtr_Mp->reg_record[i].A_COMM_TO.R = Cas_valData_Lo[2];
    }
    Sa63122_WriteRegister(0, COMM_CONF1, Spi_Stack_Write, &Cas_valData_Lo[0], 3);

    /* COMP_CONF1/2 ADC_CONF*/
    Cas_valData_Lo[0] = 0xDE;
    Cas_valData_Lo[1] = 0x00;
    Cas_valData_Lo[2] = 0x09;
    for(i = 0;i < 1;i++)
    {
        Csd_valDrvPtr_Mp->reg_record[i].A_COMP_CONF1.R = Cas_valData_Lo[0];
        Csd_valDrvPtr_Mp->reg_record[i].A_COMP_CONF2.R = Cas_valData_Lo[1];
        Csd_valDrvPtr_Mp->reg_record[i].A_ADC_CONF.R = Cas_valData_Lo[2];
        Csd_valDrvPtr_Mp->reg_record[i].A_RSVD_0009 = 0x55;
    }
    Sa63122_WriteRegister(0, COMP_CONF1, Spi_Stack_Write, &Cas_valData_Lo[0], 3);

    /* MEA_CONF */
    Cas_valData_Lo[0] = 0x55;
    for(i = 0;i < 1;i++)
        Csd_valDrvPtr_Mp->reg_record[i].A_MEA_CONF.R = Cas_valData_Lo[0];
    Sa63122_WriteRegister(0, MEA_CONF, Spi_Stack_Write, &Cas_valData_Lo[0], 1);

    /* SLP_MON-CONF / OVUV_OT_UT_CONF1/2/3/4/5/6/7 */
    Cas_valData_Lo[0] = 0x45;
    Cas_valData_Lo[1] = 0x80;
    Cas_valData_Lo[2] = 0x60;
    Cas_valData_Lo[3] = 0x18;
    Cas_valData_Lo[4] = 0x7E;
    Cas_valData_Lo[5] = 0x7E;
    Cas_valData_Lo[6] = 0x00;
    Cas_valData_Lo[7] = 0x00;
    for(i = 0;i < 1;i++)
    {
        Csd_valDrvPtr_Mp->reg_record[i].A_SLP_MON_CONF.R = Cas_valData_Lo[0];
        Csd_valDrvPtr_Mp->reg_record[i].A_OVUV_OTUT_CONF1.R = Cas_valData_Lo[1];
        Csd_valDrvPtr_Mp->reg_record[i].A_OVUV_OTUT_CONF2.R = Cas_valData_Lo[2];
        Csd_valDrvPtr_Mp->reg_record[i].A_OVUV_OTUT_CONF3.R = Cas_valData_Lo[3];
        Csd_valDrvPtr_Mp->reg_record[i].A_OVUV_OTUT_CONF4.R = Cas_valData_Lo[4];
        Csd_valDrvPtr_Mp->reg_record[i].A_OVUV_OTUT_CONF5.R = Cas_valData_Lo[5];
        Csd_valDrvPtr_Mp->reg_record[i].A_OVUV_OTUT_CONF6.R = Cas_valData_Lo[6];
        Csd_valDrvPtr_Mp->reg_record[i].A_OVUV_OTUT_CONF7.R = Cas_valData_Lo[7];
    }
    Sa63122_WriteRegister(0, SLP_MON_CONF, Spi_Stack_Write, &Cas_valData_Lo[0], 8);

    /* CB_CONF1/2/3 TWARN_CONF GPIO_DO_EN1/2 GPIO_DI_EN1/2 GPIO_WEAK_PUPD_EN1/2 */
    Cas_valData_Lo[0] = 0x7F;
    Cas_valData_Lo[1] = 0x78;
    Cas_valData_Lo[2] = 0x00;
    Cas_valData_Lo[3] = 0x03;
    Cas_valData_Lo[4] = 0x00;
    Cas_valData_Lo[5] = 0x00;
    Cas_valData_Lo[6] = 0x00;
    Cas_valData_Lo[7] = 0x00;
    Cas_valData_Lo[8] = 0xFF;
    Cas_valData_Lo[9] = 0x0F;
    for(i = 0;i < 1;i++)
    {
        Csd_valDrvPtr_Mp->reg_record[i].A_CB_CONF1.R = Cas_valData_Lo[0];
        Csd_valDrvPtr_Mp->reg_record[i].A_CB_CONF2.R = Cas_valData_Lo[1];
        Csd_valDrvPtr_Mp->reg_record[i].A_CB_CONF3.R = Cas_valData_Lo[2];
        Csd_valDrvPtr_Mp->reg_record[i].A_TWARN_CONF.R = Cas_valData_Lo[3];
        Csd_valDrvPtr_Mp->reg_record[i].A_GPIO_DO_EN1.R = Cas_valData_Lo[4];
        Csd_valDrvPtr_Mp->reg_record[i].A_GPIO_DO_EN2.R = Cas_valData_Lo[5];
        Csd_valDrvPtr_Mp->reg_record[i].A_GPIO_DI_EN1.R = Cas_valData_Lo[6];
        Csd_valDrvPtr_Mp->reg_record[i].A_GPIO_DI_EN2.R = Cas_valData_Lo[7];
        Csd_valDrvPtr_Mp->reg_record[i].A_GPIO_WEAK_PUPD_EN1.R = Cas_valData_Lo[8];
        Csd_valDrvPtr_Mp->reg_record[i].A_GPIO_WEAK_PUPD_EN2.R = Cas_valData_Lo[9];
    }
    Sa63122_WriteRegister(0, CB_CONF1, Spi_Stack_Write, &Cas_valData_Lo[0], 10);
    
    /* FLT_SUM_MSK */
    Cas_valData_Lo[0] = 0x00;
    for(i = 0;i < 1;i++)
    {
        Csd_valDrvPtr_Mp->reg_record[i].A_FLT_SUM_MSK.R = Cas_valData_Lo[0];
    }
    Sa63122_WriteRegister(0, FLT_SUM_MSK, Spi_Stack_Write, &Cas_valData_Lo[0], 1);
            
    /* OV_FLT_MSK1/2/3 UV_FLT_MSK1/2/3 CELL_COMP_FLT_MSK1/2/3
        GPIO_COMP_FLT_MSK1/2 OT_FLT_MSK1/2 UT_FLT_MSK1/2 */
    Cas_valData_Lo[0] = 0x00;
    Cas_valData_Lo[1] = 0x00;
    Cas_valData_Lo[2] = 0x00;
    Cas_valData_Lo[3] = 0x00;
    Cas_valData_Lo[4] = 0x00;
    Cas_valData_Lo[5] = 0x00;
    Cas_valData_Lo[6] = 0x00;
    Cas_valData_Lo[7] = 0x00;
    Cas_valData_Lo[8] = 0x00;
    Cas_valData_Lo[9] = 0x00;
    Cas_valData_Lo[10] = 0x00;
    Cas_valData_Lo[11] = 0x00;
    Cas_valData_Lo[12] = 0x00;
    Cas_valData_Lo[13] = 0x00;
    Cas_valData_Lo[14] = 0x00;
    for(i = 0;i < 1;i++)
    {
        Csd_valDrvPtr_Mp->reg_record[i].A_OV_FLT_MSK1.R = Cas_valData_Lo[0];
        Csd_valDrvPtr_Mp->reg_record[i].A_OV_FLT_MSK2.R = Cas_valData_Lo[1];
        Csd_valDrvPtr_Mp->reg_record[i].A_OV_FLT_MSK3.R = Cas_valData_Lo[2];
        Csd_valDrvPtr_Mp->reg_record[i].A_UV_FLT_MSK1.R = Cas_valData_Lo[3];
        Csd_valDrvPtr_Mp->reg_record[i].A_UV_FLT_MSK2.R = Cas_valData_Lo[4];
        Csd_valDrvPtr_Mp->reg_record[i].A_UV_FLT_MSK3.R = Cas_valData_Lo[5];
        Csd_valDrvPtr_Mp->reg_record[i].A_CELL_COMP_FLT_MSK1.R = Cas_valData_Lo[6];
        Csd_valDrvPtr_Mp->reg_record[i].A_CELL_COMP_FLT_MSK2.R = Cas_valData_Lo[7];
        Csd_valDrvPtr_Mp->reg_record[i].A_CELL_COMP_FLT_MSK3.R = Cas_valData_Lo[8];
        Csd_valDrvPtr_Mp->reg_record[i].A_GPIO_COMP_FLT_MSK1.R = Cas_valData_Lo[9];
        Csd_valDrvPtr_Mp->reg_record[i].A_GPIO_COMP_FLT_MSK2.R = Cas_valData_Lo[10];
        Csd_valDrvPtr_Mp->reg_record[i].A_OT_FLT_MSK1.R = Cas_valData_Lo[11];
        Csd_valDrvPtr_Mp->reg_record[i].A_OT_FLT_MSK2.R = Cas_valData_Lo[12];
        Csd_valDrvPtr_Mp->reg_record[i].A_UT_FLT_MSK1.R = Cas_valData_Lo[13];
        Csd_valDrvPtr_Mp->reg_record[i].A_UT_FLT_MSK2.R = Cas_valData_Lo[14];
    }
    Sa63122_WriteRegister(0, OV_FLT_MSK1, Spi_Stack_Write, &Cas_valData_Lo[0], 15);

    /* SYS_FLT_MSK1/2 */
    Cas_valData_Lo[0] = 0x00;
    Cas_valData_Lo[1] = 0x00;
    for(i = 0;i < 1;i++)
    {
        Csd_valDrvPtr_Mp->reg_record[i].A_SYS_FLT_MSK1.R = Cas_valData_Lo[0];
        Csd_valDrvPtr_Mp->reg_record[i].A_SYS_FLT_MSK2.R = Cas_valData_Lo[1];
    }
    Sa63122_WriteRegister(0, SYS_FLT_MSK1, Spi_Stack_Write, &Cas_valData_Lo[0], 2);

    /* SYS_FLT_MSK4/5 */
    Cas_valData_Lo[0] = 0x00;
    Cas_valData_Lo[1] = 0x00;
    for(i = 0;i < 1;i++)
    {
        Csd_valDrvPtr_Mp->reg_record[i].A_SYS_FLT_MSK4.R = Cas_valData_Lo[0];
        Csd_valDrvPtr_Mp->reg_record[i].A_SYS_FLT_MSK5.R = Cas_valData_Lo[1];
    }
    Sa63122_WriteRegister(0, SYS_FLT_MSK4, Spi_Stack_Write, &Cas_valData_Lo[0], 2);

    /* SYS_FLT_MSK5 */
    Cas_valData_Lo[0] = 0x02;
    for(i = 0;i < 1;i++)
    {
        Csd_valDrvPtr_Mp->reg_record[i].A_SYS_FLT_MSK5.R = Cas_valData_Lo[0];
    }
    Sa63122_WriteRegister(Spi_Dev_Addr_01, SYS_FLT_MSK5, Spi_Single_Write, &Cas_valData_Lo[0], 1);
}

/**
 * @brief  开启一次ADC采集
 * @param  none
 * @retval none
 */
void Sa63122_StartAdc(void)
{
    uint8_t i = 0;
    uint8_t Cas_valData_Lo = 0x02;

    for(i = AFE_DEV_ADDR_DEV1;i <= AFE_NUMBER;i++)
    {
        /* 均衡打开的时候不采样 */
        if(0 == Sa63122_GetBalCurrentState(Csd_valDrvPtr_Mp, (i - 1)))
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, ADC_CTRL, Spi_Single_Write, &Cas_valData_Lo, 1);
    }
}

/**
 * @brief  清除所有的错误
 * @param  none
 * @retval none
 */
void Sa63122_ClearFaults(void)
{
    uint8_t Cas_valData_Lo[10] = {0};

    Sa63122_WriteRegister(0, OV_FLT1, Spi_Stack_Write, &Cas_valData_Lo[0], 10);
    Sa63122_WriteRegister(0, GPIO_COMP_FLT2, Spi_Stack_Write, &Cas_valData_Lo[0], 10);
}

/**
 * @brief  读取电芯电压
 * @param  dev_addr 设备地址
 * @retval none
 */
void Sa63122_ReadCellVoltage(uint8_t dev_addr)
{
    uint8_t i = 0;
    uint8_t* Csd_valDataPtr_Lo = Sa63122_GetRxData();

    if((0 == dev_addr) || (dev_addr > AFE_NUMBER))
        return;

    /* 均衡打开的时候不读取数据 */
    if(0 == Sa63122_GetBalCurrentState(Csd_valDrvPtr_Mp, (dev_addr - 1)))
    {
        Sa63122_ReadRegister((Sa63000_Spi_DevAddrType)dev_addr, CH1_H, Spi_Single_Read, 2 * SA63122_CELL_NUMBER);
        Sa63122_ResponseRegister(2 * SA63122_CELL_NUMBER);
        for(i = 0;i < SA63122_CELL_NUMBER;i++)
        {
            Csd_valDrvPtr_Mp->Cell_Voltage_Buffer[SA63122_CELL_NUMBER * (dev_addr - 1) + i] =\
                                                                (uint16_t)(((uint16_t)Csd_valDataPtr_Lo[2 * i] << 8) |\
                                                                (uint16_t)Csd_valDataPtr_Lo[2 * i + 1]);
        }
    }
}

/**
 * @brief  读取GPIO电压
 * @param  dev_addr 设备地址
 * @retval none
 */
void Sa63122_ReadGpioVoltage(uint8_t dev_addr)
{
    uint8_t i = 0;
    uint8_t* Csd_valDataPtr_Lo = Sa63122_GetRxData();

    if((0 == dev_addr) || (dev_addr > AFE_NUMBER))
        return;

    /* 均衡打开的时候不读取数据 */
    if(0 == Sa63122_GetBalCurrentState(Csd_valDrvPtr_Mp, (dev_addr - 1)))
    {
        Sa63122_ReadRegister((Sa63000_Spi_DevAddrType)dev_addr, GPIO0_H, Spi_Single_Read, 2 * SA63122_GPIO_NUMBER);
        Sa63122_ResponseRegister(2 * SA63122_GPIO_NUMBER);
        for(i = 0;i < SA63122_GPIO_NUMBER;i++)
        {
            Csd_valDrvPtr_Mp->Gpio_Voltage_Buffer[SA63122_GPIO_NUMBER * (dev_addr - 1) + i] =\
                                                                (uint16_t)(((uint16_t)Csd_valDataPtr_Lo[2 * i] << 8) |\
                                                                (uint16_t)Csd_valDataPtr_Lo[2 * i + 1]);     
        }
    }
}

void Sa63122_StartCellBal(void)
{
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t Csd_valData_Lo[12] = {0};

    for(i = AFE_DEV_ADDR_DEV1;i <= AFE_NUMBER;i++)
    {
        if((true == Sa63122_GetBalCurrentState(Csd_valDrvPtr_Mp, (i - 1))) &&\
            (false == Sa63122_GetBalLastState(Csd_valDrvPtr_Mp, (i - 1))))
        {
            for(j = 0;j < 6;j++)
            {
                Csd_valData_Lo[2 * j] = 0x83;
                Csd_valData_Lo[2 * j + 1] = 0xff;
            }
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, CB_TO_CH1_H, Spi_Single_Write, &Csd_valData_Lo[0], 12);
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, CB_TO_CH7_H, Spi_Single_Write, &Csd_valData_Lo[0], 12);
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, CB_TO_CH13_H, Spi_Single_Write, &Csd_valData_Lo[0], 12);
            Csd_valData_Lo[0] = Csd_valDrvPtr_Mp->bal_cfg[i - 1];
            Csd_valData_Lo[1] = Csd_valDrvPtr_Mp->bal_cfg[i - 1] >> 8;
            Csd_valData_Lo[2] = (Csd_valDrvPtr_Mp->bal_cfg[i - 1] >> 16) & 0x3;
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, CBFET_EN1, Spi_Single_Write, &Csd_valData_Lo[0], 3);
            Csd_valData_Lo[0] = 0x05;
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, CB_CTRL, Spi_Single_Write, &Csd_valData_Lo[0], 1);
            Sa63122_UpdateBalLastState(Csd_valDrvPtr_Mp, (i - 1));
        }
        else if((false == Sa63122_GetBalCurrentState(Csd_valDrvPtr_Mp, (i - 1))) &&\
            (true == Sa63122_GetBalLastState(Csd_valDrvPtr_Mp, (i - 1))))
        {
            memset(&Csd_valData_Lo[0], 0 ,12);
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, CB_TO_CH1_H, Spi_Single_Write, &Csd_valData_Lo[0], 12);
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, CB_TO_CH7_H, Spi_Single_Write, &Csd_valData_Lo[0], 12);
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, CB_TO_CH13_H, Spi_Single_Write, &Csd_valData_Lo[0], 12);
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, CBFET_EN1, Spi_Single_Write, &Csd_valData_Lo[0], 3);
            Csd_valData_Lo[0] = 0x02;
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, CB_CTRL, Spi_Single_Write, &Csd_valData_Lo[0], 1);
            Sa63122_UpdateBalLastState(Csd_valDrvPtr_Mp, (i - 1));
        }
    }
}

void Sa63122_GetCellBalStatus(void)
{
    uint8_t i = 0;
    uint8_t* Csd_valDataPtr_Lo = Sa63122_GetRxData();

    Sa63122_ReadRegister(Spi_Dev_Addr_01, CB_DONE_STAT1, Spi_Single_Read, 3);
    Sa63122_ResponseRegister(3);
    for(i = 0;i < 3;i++)
    {
        Csd_valDrvPtr_Mp->bal_status[i] = Csd_valDataPtr_Lo[i];
    }
}

void Sa63122_OwDetection(uint8_t step)
{
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t buf1_idx = 0;
    uint8_t buf2_idx = 1;
    uint8_t bit_pos = 0;
    uint8_t Csd_valData_Lo[12] = {0};
    uint8_t* rx_buf_ptr = Sa63122_GetRxData();
    uint16_t vol_buf2[18] = {0};
    uint16_t* buf1_ptr = &Csd_valDrvPtr_Mp->cell_opl_vol_buf1[0];

    switch(step)
    {
    case SA63122_CELL_OPL_DECT_STEP_ODD_BAL:
        for(i = AFE_DEV_ADDR_DEV1;i <= AFE_NUMBER;i++)
        {
            for(j = 0;j < 3;j++)
            {
                Csd_valData_Lo[4 * j] = 0x83;
                Csd_valData_Lo[4 * j + 1] = 0xff;
            }
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, CB_TO_CH1_H, Spi_Single_Write, &Csd_valData_Lo[0], 12);
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, CB_TO_CH7_H, Spi_Single_Write, &Csd_valData_Lo[0], 12);
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, CB_TO_CH13_H, Spi_Single_Write, &Csd_valData_Lo[0], 12);
            Csd_valData_Lo[0] = 0x55;
            Csd_valData_Lo[1] = 0x55;
            Csd_valData_Lo[2] = 0x01;
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, CBFET_EN1, Spi_Single_Write, &Csd_valData_Lo[0], 3);
            Csd_valData_Lo[0] = 0x04;
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, CB_CTRL, Spi_Single_Write, &Csd_valData_Lo[0], 1);
            Csd_valData_Lo[0] = 0x05;
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, CB_CTRL, Spi_Single_Write, &Csd_valData_Lo[0], 1);
            Sa63000_Spi_Delay(24000);
            Csd_valData_Lo[0] = 0x02;
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, CB_CTRL, Spi_Single_Write, &Csd_valData_Lo[0], 1);
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, ADC_CTRL, Spi_Single_Write, &Csd_valData_Lo[0], 1);
        }
        break;
    case SA63122_CELL_OPL_DECT_STEP_ODD_GET_VOL:
        for(i = AFE_DEV_ADDR_DEV1;i <= AFE_NUMBER;i++)
        {
            Sa63122_ReadRegister((Sa63000_Spi_DevAddrType)i, CH1_H, Spi_Single_Read, 2 * SA63122_CELL_NUMBER);
            Sa63122_ResponseRegister(2 * SA63122_CELL_NUMBER);
        }
        for(i = 0;i < 18;i++)
            buf1_ptr[i] = SA63122_UINT8_COMBINE_TO_UINT16(rx_buf_ptr[2 * i], rx_buf_ptr[2 * i + 1]);
        break;
    case SA63122_CELL_OPL_DECT_STEP_EVEN_BAL:
        for(i = AFE_DEV_ADDR_DEV1;i <= AFE_NUMBER;i++)
        {
            for(j = 0;j < 3;j++)
            {
                Csd_valData_Lo[2 + 4 * j] = 0x83;
                Csd_valData_Lo[2 + 4 * j + 1] = 0xff;
            }
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, CB_TO_CH1_H, Spi_Single_Write, &Csd_valData_Lo[0], 12);
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, CB_TO_CH7_H, Spi_Single_Write, &Csd_valData_Lo[0], 12);
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, CB_TO_CH13_H, Spi_Single_Write, &Csd_valData_Lo[0], 12);
            Csd_valData_Lo[0] = 0xAA;
            Csd_valData_Lo[1] = 0xAA;
            Csd_valData_Lo[2] = 0x02;
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, CBFET_EN1, Spi_Single_Write, &Csd_valData_Lo[0], 3);
            Csd_valData_Lo[0] = 0x04;
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, CB_CTRL, Spi_Single_Write, &Csd_valData_Lo[0], 1);
            Csd_valData_Lo[0] = 0x05;
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, CB_CTRL, Spi_Single_Write, &Csd_valData_Lo[0], 1);
            Sa63000_Spi_Delay(24000);
            Csd_valData_Lo[0] = 0x02;
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, CB_CTRL, Spi_Single_Write, &Csd_valData_Lo[0], 1);
            Sa63122_WriteRegister((Sa63000_Spi_DevAddrType)i, ADC_CTRL, Spi_Single_Write, &Csd_valData_Lo[0], 1);
        }
        break;
    case SA63122_CELL_OPL_DECT_STEP_EVEN_GET_VOL:
        for(i = AFE_DEV_ADDR_DEV1;i <= AFE_NUMBER;i++)
        {
            Sa63122_ReadRegister((Sa63000_Spi_DevAddrType)i, CH1_H, Spi_Single_Read, 2 * SA63122_CELL_NUMBER);
            Sa63122_ResponseRegister(2 * SA63122_CELL_NUMBER);
        }

        for(i = 0;i < 18;i++)
            vol_buf2[i] = SA63122_UINT8_COMBINE_TO_UINT16(rx_buf_ptr[2 * i], rx_buf_ptr[2 * i + 1]);
        
        for(i = 0;i < SA63122_CELL_NUMBER;i++)
        {
            if(buf1_ptr[i] & 0x8000)
            	buf1_ptr[i] = (65535 - buf1_ptr[i]);
            if(vol_buf2[i] & 0x8000)
            	vol_buf2[i] = (65535 - vol_buf2[i]);
        }

        for(i = AFE_DEV_ADDR_DEV1;i <= AFE_NUMBER;i++)
        {
            /* 原始的判断电芯开路逻坤 */
            /*
            if((vol_buf1[0] < 2500) && (vol_buf2[1] < 2500))    // cell_1
                Csd_valDrvPtr_Mp->cell_opl[i - 1] |= (1 << 0);
            else
                Csd_valDrvPtr_Mp->cell_opl[i - 1] &= ~(1 << 0);

            if((vol_buf1[2] < 2500) && (vol_buf2[1] < 2500))    // cell_2
                Csd_valDrvPtr_Mp->cell_opl[i - 1] |= (1 << 1);
            else
                Csd_valDrvPtr_Mp->cell_opl[i - 1] &= ~(1 << 1);

            if((vol_buf1[2] < 2500) && (vol_buf2[3] < 2500))    // cell_3
                Csd_valDrvPtr_Mp->cell_opl[i - 1] |= (1 << 2);
            else
                Csd_valDrvPtr_Mp->cell_opl[i - 1] &= ~(1 << 2);

            if((vol_buf1[4] < 2500) && (vol_buf2[3] < 2500))    // cell_4
                Csd_valDrvPtr_Mp->cell_opl[i - 1] |= (1 << 3);
            else
                Csd_valDrvPtr_Mp->cell_opl[i - 1] &= ~(1 << 3);

            if((vol_buf1[4] < 2500) && (vol_buf2[5] < 2500))    // cell_5
                Csd_valDrvPtr_Mp->cell_opl[i - 1] |= (1 << 4);
            else
                Csd_valDrvPtr_Mp->cell_opl[i - 1] &= ~(1 << 4);

            if((vol_buf1[6] < 2500) && (vol_buf2[5] < 2500))    // cell_6
                Csd_valDrvPtr_Mp->cell_opl[i - 1] |= (1 << 5);
            else
                Csd_valDrvPtr_Mp->cell_opl[i - 1] &= ~(1 << 5);

            if((vol_buf1[6] < 2500) && (vol_buf2[7] < 2500))    // cell_7
                Csd_valDrvPtr_Mp->cell_opl[i - 1] |= (1 << 6);
            else
                Csd_valDrvPtr_Mp->cell_opl[i - 1] &= ~(1 << 6);

            if((vol_buf1[8] < 2500) && (vol_buf2[7] < 2500))    // cell_8
                Csd_valDrvPtr_Mp->cell_opl[i - 1] |= (1 << 7);
            else
                Csd_valDrvPtr_Mp->cell_opl[i - 1] &= ~(1 << 7);

            if((vol_buf1[8] < 2500) && (vol_buf2[9] < 2500))    // cell_9
                Csd_valDrvPtr_Mp->cell_opl[i - 1] |= (1 << 8);
            else
                Csd_valDrvPtr_Mp->cell_opl[i - 1] &= ~(1 << 8);

            if((vol_buf1[10] < 2500) && (vol_buf2[9] < 2500))   // cell_10
                Csd_valDrvPtr_Mp->cell_opl[i - 1] |= (1 << 9);
            else
                Csd_valDrvPtr_Mp->cell_opl[i - 1] &= ~(1 << 9);

            if((vol_buf1[10] < 2500) && (vol_buf2[11] < 2500))  // cell_11
                Csd_valDrvPtr_Mp->cell_opl[i - 1] |= (1 << 10);
            else
                Csd_valDrvPtr_Mp->cell_opl[i - 1] &= ~(1 << 10);

            if((vol_buf1[12] < 2500) && (vol_buf2[11] < 2500))  // cell_12
                Csd_valDrvPtr_Mp->cell_opl[i - 1] |= (1 << 11);
            else
                Csd_valDrvPtr_Mp->cell_opl[i - 1] &= ~(1 << 11);

            if((vol_buf1[12] < 2500) && (vol_buf2[13] < 2500))  // cell_13
                Csd_valDrvPtr_Mp->cell_opl[i - 1] |= (1 << 12);
            else
                Csd_valDrvPtr_Mp->cell_opl[i - 1] &= ~(1 << 12);

            if((vol_buf1[14] < 2500) && (vol_buf2[13] < 2500))  // cell_14
                Csd_valDrvPtr_Mp->cell_opl[i - 1] |= (1 << 13);
            else
                Csd_valDrvPtr_Mp->cell_opl[i - 1] &= ~(1 << 13);

            if((vol_buf1[14] < 2500) && (vol_buf2[15] < 2500))  // cell_15
                Csd_valDrvPtr_Mp->cell_opl[i - 1] |= (1 << 14);
            else
                Csd_valDrvPtr_Mp->cell_opl[i - 1] &= ~(1 << 14);

            if((vol_buf1[16] < 2500) && (vol_buf2[15] < 2500))  // cell_16
                Csd_valDrvPtr_Mp->cell_opl[i - 1] |= (1 << 15);
            else
                Csd_valDrvPtr_Mp->cell_opl[i - 1] &= ~(1 << 15);

            if((vol_buf1[16] < 2500) && (vol_buf2[17] < 2500))  // cell_17
                Csd_valDrvPtr_Mp->cell_opl[i - 1] |= (1 << 16);
            else
                Csd_valDrvPtr_Mp->cell_opl[i - 1] &= ~(1 << 16);
            
            // cell18
            */
            for(;buf1_idx <= 16;)
            {
                if((buf1_ptr[buf1_idx] < SA63122_CELL_OPL_DECT_THR) &&\
                    (vol_buf2[buf2_idx] < SA63122_CELL_OPL_DECT_THR))
                    SA63122_SET_BIT(Csd_valDrvPtr_Mp->cell_opl[i - 1], bit_pos++);
                else
                    SA63122_CLR_BIT(Csd_valDrvPtr_Mp->cell_opl[i - 1], bit_pos++);
                
                if(16 == buf1_idx)
                    break;
                
                if((buf1_ptr[2 + buf1_idx] < SA63122_CELL_OPL_DECT_THR) &&\
                    (vol_buf2[buf2_idx] < SA63122_CELL_OPL_DECT_THR))
                    SA63122_SET_BIT(Csd_valDrvPtr_Mp->cell_opl[i - 1], bit_pos++);
                else
                    SA63122_CLR_BIT(Csd_valDrvPtr_Mp->cell_opl[i - 1], bit_pos++);
                buf1_idx += 2;
                buf2_idx += 2;
            }
        }
        break;
    default:
        break;
    }
}
