#include "Cdd_Sa63122_Driver.h"

static Sa63122_DriverType Csd_valDrv_Mp;

Sa63122_DriverType* Sa63122_DriverGet(void)
{
    return &Csd_valDrv_Mp;
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
    Sa63122_DriverType* DrvPtr = Sa63122_DriverGet();

    start = (dev_addr == 0xff) ? 0 : dev_addr;
    final = (dev_addr == 0xff) ? AFE_NUMBER : (dev_addr + 1);

    for(i = start;i < final;i++)
    {
        Buff[0]  = DrvPtr->reg_record[i].A_DEV_ADD1.R;
        Buff[1]  = DrvPtr->reg_record[i].A_DEV_ADD2.R;
        Buff[2]  = DrvPtr->reg_record[i].A_COMM_CONF1.R;
        Buff[3]  = DrvPtr->reg_record[i].A_COMM_CONF2.R;
        Buff[4]  = DrvPtr->reg_record[i].A_COMM_TO.R;
        Buff[5]  = DrvPtr->reg_record[i].A_RSVD_0005;
        Buff[6]  = DrvPtr->reg_record[i].A_COMP_CONF1.R;
        Buff[7]  = DrvPtr->reg_record[i].A_COMP_CONF2.R;
        Buff[8]  = DrvPtr->reg_record[i].A_ADC_CONF.R;
        Buff[9]  = DrvPtr->reg_record[i].A_RSVD_0009;
        Buff[10] = DrvPtr->reg_record[i].A_MEA_CONF.R;
        Buff[11] = DrvPtr->reg_record[i].A_RSVD_000B;
        Buff[12] = DrvPtr->reg_record[i].A_RSVD_000C;
        Buff[13] = DrvPtr->reg_record[i].A_SLP_MON_CONF.R;
        Buff[14] = DrvPtr->reg_record[i].A_OVUV_OTUT_CONF1.R;
        Buff[15] = DrvPtr->reg_record[i].A_OVUV_OTUT_CONF2.R;
        Buff[16] = DrvPtr->reg_record[i].A_OVUV_OTUT_CONF3.R;
        Buff[17] = DrvPtr->reg_record[i].A_OVUV_OTUT_CONF4.R;
        Buff[18] = DrvPtr->reg_record[i].A_OVUV_OTUT_CONF5.R;
        Buff[19] = DrvPtr->reg_record[i].A_OVUV_OTUT_CONF6.R;
        Buff[20] = DrvPtr->reg_record[i].A_OVUV_OTUT_CONF7.R;
        Buff[21] = DrvPtr->reg_record[i].A_CB_CONF1.R;
        Buff[22] = DrvPtr->reg_record[i].A_CB_CONF2.R;
        Buff[23] = DrvPtr->reg_record[i].A_CB_CONF3.R;
        Buff[24] = DrvPtr->reg_record[i].A_TWARN_CONF.R;
        Buff[25] = DrvPtr->reg_record[i].A_GPIO_DO_EN1.R;
        Buff[26] = DrvPtr->reg_record[i].A_GPIO_DO_EN2.R;
        Buff[27] = DrvPtr->reg_record[i].A_GPIO_DI_EN1.R;
        Buff[28] = DrvPtr->reg_record[i].A_GPIO_DI_EN2.R;
        Buff[29] = DrvPtr->reg_record[i].A_GPIO_WEAK_PUPD_EN1.R;
        Buff[30] = DrvPtr->reg_record[i].A_GPIO_WEAK_PUPD_EN2.R;
        Buff[31] = DrvPtr->reg_record[i].A_FLT_SUM_MSK.R;
        Buff[32] = DrvPtr->reg_record[i].A_RSVD_0101;
        Buff[33] = DrvPtr->reg_record[i].A_RSVD_0102;
        Buff[34] = DrvPtr->reg_record[i].A_RSVD_0103;
        Buff[35] = DrvPtr->reg_record[i].A_OV_FLT_MSK1.R;
        Buff[36] = DrvPtr->reg_record[i].A_OV_FLT_MSK2.R;
        Buff[37] = DrvPtr->reg_record[i].A_OV_FLT_MSK3.R;
        Buff[38] = DrvPtr->reg_record[i].A_UV_FLT_MSK1.R;
        Buff[39] = DrvPtr->reg_record[i].A_UV_FLT_MSK2.R;
        Buff[40] = DrvPtr->reg_record[i].A_UV_FLT_MSK3.R;
        Buff[41] = DrvPtr->reg_record[i].A_CELL_COMP_FLT_MSK1.R;
        Buff[42] = DrvPtr->reg_record[i].A_CELL_COMP_FLT_MSK2.R;
        Buff[43] = DrvPtr->reg_record[i].A_CELL_COMP_FLT_MSK3.R;
        Buff[44] = DrvPtr->reg_record[i].A_GPIO_COMP_FLT_MSK1.R;
        Buff[45] = DrvPtr->reg_record[i].A_GPIO_COMP_FLT_MSK2.R;
        Buff[46] = DrvPtr->reg_record[i].A_OT_FLT_MSK1.R;
        Buff[47] = DrvPtr->reg_record[i].A_OT_FLT_MSK2.R;
        Buff[48] = DrvPtr->reg_record[i].A_UT_FLT_MSK1.R;
        Buff[49] = DrvPtr->reg_record[i].A_UT_FLT_MSK2.R;
        Buff[50] = DrvPtr->reg_record[i].A_SYS_FLT_MSK1.R;
        Buff[51] = DrvPtr->reg_record[i].A_SYS_FLT_MSK2.R;
        Buff[52] = DrvPtr->reg_record[i].A_RSVD_0115;
        Buff[53] = DrvPtr->reg_record[i].A_SYS_FLT_MSK4.R;
        Buff[54] = DrvPtr->reg_record[i].A_SYS_FLT_MSK5.R;

        for(j = 0; j < SA63122_FACT_REG1_MAX; j++)
        {
            Buff[j + 55] = DrvPtr->reg_record[i].FACT_REG1[j];
        }

        for(j = 0; j < SA63122_FACT_REG2_MAX; j++)
        {
            Buff[j + 65] = DrvPtr->reg_record[i].FACT_REG2[j];
        }

        crc = Crc16_Modbus(&Buff[0], 193);
        DrvPtr->reg_record[i].A_CONF_CRC_H = (crc >> 8) & 0xff;
        DrvPtr->reg_record[i].A_CONF_CRC_L = (crc >> 0) & 0xff;
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
    Sa63122_DriverType* DrvPtr = Sa63122_DriverGet();

    start = (dev_addr == 0xff) ? 0 : dev_addr;
    final = (dev_addr == 0xff) ? AFE_NUMBER : (dev_addr + 1);

    for(i = start;i < final;i++)
    {
        Cas_valData_Lo[0] = DrvPtr->reg_record[i].A_CONF_CRC_H;
        Cas_valData_Lo[1] = DrvPtr->reg_record[i].A_CONF_CRC_L;
        Sa63xxx_WriteRegister(0, CONF_CRC_H, Sa63xxx_Spi_Stack_Write, &Cas_valData_Lo[0], 2);
    }
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
    uint8_t* Csd_valRxDataPtr_Lo = Sa63xxx_GetRxData();
    Sa63122_DriverType* DrvPtr = Sa63122_DriverGet();

    /* FACT1~FACT10 */
    Sa63xxx_ReadRegister(Sa63xxx_Spi_Dev_Addr_01, FACT_REG1, Sa63xxx_Spi_Single_Read, 10);
    Sa63xxx_ResponseRegister(10);
    for(i = 0;i < 1;i++)
    {
        memcpy(&DrvPtr->reg_record[i].FACT_REG1[0], Csd_valRxDataPtr_Lo, 10);
    }

    /* FACT11~FACT138 */
    Sa63xxx_ReadRegister(Sa63xxx_Spi_Dev_Addr_01, FACT_REG11, Sa63xxx_Spi_Single_Read, 64);
    Sa63xxx_ResponseRegister(64);
    for(i = 0;i < 1;i++)
    {
        memcpy(&DrvPtr->reg_record[i].FACT_REG2[0], Csd_valRxDataPtr_Lo, 64);
    }

    Sa63xxx_ReadRegister(Sa63xxx_Spi_Dev_Addr_01, FACT_REG74, Sa63xxx_Spi_Single_Read, 64);
    Sa63xxx_ResponseRegister(64);
    for(i = 0;i < 1;i++)
    {
        memcpy(&DrvPtr->reg_record[i].FACT_REG2[64], Csd_valRxDataPtr_Lo, 64);
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
    Sa63122_DriverType* DrvPtr = Sa63122_DriverGet();

    /******************************************** Config Start ********************************************/
    for(i = 0;i < 1;i++)
    {
        // DrvPtr->reg_record[i].A_DEV_ADD1.R = i + 1;
        DrvPtr->reg_record[i].A_DEV_ADD1.R = 0x81;
        DrvPtr->reg_record[i].A_DEV_ADD2.R = 0;
    }
    
    /* COMM_CONF1/2/TO */
    Cas_valData_Lo[0] = 0x08;
    Cas_valData_Lo[1] = 0x00;
    Cas_valData_Lo[2] = 0xBB;
    for(i = 0;i < 1;i++)
    {
        DrvPtr->reg_record[i].A_COMM_CONF1.R = Cas_valData_Lo[0];
        DrvPtr->reg_record[i].A_COMM_CONF2.R = Cas_valData_Lo[1];
        DrvPtr->reg_record[i].A_COMM_TO.R = Cas_valData_Lo[2];
    }
    Sa63xxx_WriteRegister(0, COMM_CONF1, Sa63xxx_Spi_Stack_Write, &Cas_valData_Lo[0], 3);

    /* COMP_CONF1/2 ADC_CONF*/
    Cas_valData_Lo[0] = 0xDE;
    Cas_valData_Lo[1] = 0x00;
    Cas_valData_Lo[2] = 0x09;
    for(i = 0;i < 1;i++)
    {
        DrvPtr->reg_record[i].A_COMP_CONF1.R = Cas_valData_Lo[0];
        DrvPtr->reg_record[i].A_COMP_CONF2.R = Cas_valData_Lo[1];
        DrvPtr->reg_record[i].A_ADC_CONF.R = Cas_valData_Lo[2];
        DrvPtr->reg_record[i].A_RSVD_0009 = 0x55;
    }
    Sa63xxx_WriteRegister(0, COMP_CONF1, Sa63xxx_Spi_Stack_Write, &Cas_valData_Lo[0], 3);

    /* MEA_CONF */
    Cas_valData_Lo[0] = 0x55;
    for(i = 0;i < 1;i++)
        DrvPtr->reg_record[i].A_MEA_CONF.R = Cas_valData_Lo[0];
    Sa63xxx_WriteRegister(0, MEA_CONF, Sa63xxx_Spi_Stack_Write, &Cas_valData_Lo[0], 1);

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
        DrvPtr->reg_record[i].A_SLP_MON_CONF.R = Cas_valData_Lo[0];
        DrvPtr->reg_record[i].A_OVUV_OTUT_CONF1.R = Cas_valData_Lo[1];
        DrvPtr->reg_record[i].A_OVUV_OTUT_CONF2.R = Cas_valData_Lo[2];
        DrvPtr->reg_record[i].A_OVUV_OTUT_CONF3.R = Cas_valData_Lo[3];
        DrvPtr->reg_record[i].A_OVUV_OTUT_CONF4.R = Cas_valData_Lo[4];
        DrvPtr->reg_record[i].A_OVUV_OTUT_CONF5.R = Cas_valData_Lo[5];
        DrvPtr->reg_record[i].A_OVUV_OTUT_CONF6.R = Cas_valData_Lo[6];
        DrvPtr->reg_record[i].A_OVUV_OTUT_CONF7.R = Cas_valData_Lo[7];
    }
    Sa63xxx_WriteRegister(0, SLP_MON_CONF, Sa63xxx_Spi_Stack_Write, &Cas_valData_Lo[0], 8);

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
        DrvPtr->reg_record[i].A_CB_CONF1.R = Cas_valData_Lo[0];
        DrvPtr->reg_record[i].A_CB_CONF2.R = Cas_valData_Lo[1];
        DrvPtr->reg_record[i].A_CB_CONF3.R = Cas_valData_Lo[2];
        DrvPtr->reg_record[i].A_TWARN_CONF.R = Cas_valData_Lo[3];
        DrvPtr->reg_record[i].A_GPIO_DO_EN1.R = Cas_valData_Lo[4];
        DrvPtr->reg_record[i].A_GPIO_DO_EN2.R = Cas_valData_Lo[5];
        DrvPtr->reg_record[i].A_GPIO_DI_EN1.R = Cas_valData_Lo[6];
        DrvPtr->reg_record[i].A_GPIO_DI_EN2.R = Cas_valData_Lo[7];
        DrvPtr->reg_record[i].A_GPIO_WEAK_PUPD_EN1.R = Cas_valData_Lo[8];
        DrvPtr->reg_record[i].A_GPIO_WEAK_PUPD_EN2.R = Cas_valData_Lo[9];
    }
    Sa63xxx_WriteRegister(0, CB_CONF1, Sa63xxx_Spi_Stack_Write, &Cas_valData_Lo[0], 10);
    
    /* FLT_SUM_MSK */
    Cas_valData_Lo[0] = 0x00;
    for(i = 0;i < 1;i++)
    {
        DrvPtr->reg_record[i].A_FLT_SUM_MSK.R = Cas_valData_Lo[0];
    }
    Sa63xxx_WriteRegister(0, FLT_SUM_MSK, Sa63xxx_Spi_Stack_Write, &Cas_valData_Lo[0], 1);
            
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
        DrvPtr->reg_record[i].A_OV_FLT_MSK1.R = Cas_valData_Lo[0];
        DrvPtr->reg_record[i].A_OV_FLT_MSK2.R = Cas_valData_Lo[1];
        DrvPtr->reg_record[i].A_OV_FLT_MSK3.R = Cas_valData_Lo[2];
        DrvPtr->reg_record[i].A_UV_FLT_MSK1.R = Cas_valData_Lo[3];
        DrvPtr->reg_record[i].A_UV_FLT_MSK2.R = Cas_valData_Lo[4];
        DrvPtr->reg_record[i].A_UV_FLT_MSK3.R = Cas_valData_Lo[5];
        DrvPtr->reg_record[i].A_CELL_COMP_FLT_MSK1.R = Cas_valData_Lo[6];
        DrvPtr->reg_record[i].A_CELL_COMP_FLT_MSK2.R = Cas_valData_Lo[7];
        DrvPtr->reg_record[i].A_CELL_COMP_FLT_MSK3.R = Cas_valData_Lo[8];
        DrvPtr->reg_record[i].A_GPIO_COMP_FLT_MSK1.R = Cas_valData_Lo[9];
        DrvPtr->reg_record[i].A_GPIO_COMP_FLT_MSK2.R = Cas_valData_Lo[10];
        DrvPtr->reg_record[i].A_OT_FLT_MSK1.R = Cas_valData_Lo[11];
        DrvPtr->reg_record[i].A_OT_FLT_MSK2.R = Cas_valData_Lo[12];
        DrvPtr->reg_record[i].A_UT_FLT_MSK1.R = Cas_valData_Lo[13];
        DrvPtr->reg_record[i].A_UT_FLT_MSK2.R = Cas_valData_Lo[14];
    }
    Sa63xxx_WriteRegister(0, OV_FLT_MSK1, Sa63xxx_Spi_Stack_Write, &Cas_valData_Lo[0], 15);

    /* SYS_FLT_MSK1/2 */
    Cas_valData_Lo[0] = 0x00;
    Cas_valData_Lo[1] = 0x00;
    for(i = 0;i < 1;i++)
    {
        DrvPtr->reg_record[i].A_SYS_FLT_MSK1.R = Cas_valData_Lo[0];
        DrvPtr->reg_record[i].A_SYS_FLT_MSK2.R = Cas_valData_Lo[1];
    }
    Sa63xxx_WriteRegister(0, SYS_FLT_MSK1, Sa63xxx_Spi_Stack_Write, &Cas_valData_Lo[0], 2);

    /* SYS_FLT_MSK4/5 */
    Cas_valData_Lo[0] = 0x00;
    Cas_valData_Lo[1] = 0x00;
    for(i = 0;i < 1;i++)
    {
        DrvPtr->reg_record[i].A_SYS_FLT_MSK4.R = Cas_valData_Lo[0];
        DrvPtr->reg_record[i].A_SYS_FLT_MSK5.R = Cas_valData_Lo[1];
    }
    Sa63xxx_WriteRegister(0, SYS_FLT_MSK4, Sa63xxx_Spi_Stack_Write, &Cas_valData_Lo[0], 2);

    /* SYS_FLT_MSK5 */
    Cas_valData_Lo[0] = 0x02;
    for(i = 0;i < 1;i++)
    {
        DrvPtr->reg_record[i].A_SYS_FLT_MSK5.R = Cas_valData_Lo[0];
    }
    Sa63xxx_WriteRegister(Sa63xxx_Spi_Dev_Addr_01, SYS_FLT_MSK5, Sa63xxx_Spi_Single_Write, &Cas_valData_Lo[0], 1);
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
    Sa63122_DriverType* DrvPtr = Sa63122_DriverGet();

    for(i = AFE_DEV_ADDR_DEV1;i <= AFE_NUMBER;i++)
    {
        /* 均衡打开的时候不采样 */
        if(0 == Sa63122_GetBalCurrentState(DrvPtr, (i - 1)))
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, ADC_CTRL, Sa63xxx_Spi_Single_Write, &Cas_valData_Lo, 1);
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

    Sa63xxx_WriteRegister(0, OV_FLT1, Sa63xxx_Spi_Stack_Write, &Cas_valData_Lo[0], 10);
    Sa63xxx_WriteRegister(0, GPIO_COMP_FLT2, Sa63xxx_Spi_Stack_Write, &Cas_valData_Lo[0], 10);
}

/**
 * @brief  读取电芯电压
 * @param  dev_addr 设备地址
 * @retval none
 */
void Sa63122_ReadCellVoltage(uint8_t dev_addr)
{
    uint8_t i = 0;
    uint8_t* Csd_valDataPtr_Lo = Sa63xxx_GetRxData();
    Sa63122_DriverType* DrvPtr = Sa63122_DriverGet();

    if((0 == dev_addr) || (dev_addr > AFE_NUMBER))
        return;

    /* 均衡打开的时候不读取数据 */
    if(0 == Sa63122_GetBalCurrentState(DrvPtr, (dev_addr - 1)))
    {
        Sa63xxx_ReadRegister((Sa63xxx_Spi_DevAddrType)dev_addr, CH1_H, Sa63xxx_Spi_Single_Read, 2 * SA63122_CELL_NUMBER);
        Sa63xxx_ResponseRegister(2 * SA63122_CELL_NUMBER);
        for(i = 0;i < SA63122_CELL_NUMBER;i++)
        {
            DrvPtr->Cell_Voltage_Buffer[SA63122_CELL_NUMBER * (dev_addr - 1) + i] =\
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
    uint8_t* Csd_valDataPtr_Lo = Sa63xxx_GetRxData();
    Sa63122_DriverType* DrvPtr = Sa63122_DriverGet();

    if((0 == dev_addr) || (dev_addr > AFE_NUMBER))
        return;

    /* 均衡打开的时候不读取数据 */
    if(0 == Sa63122_GetBalCurrentState(DrvPtr, (dev_addr - 1)))
    {
        Sa63xxx_ReadRegister((Sa63xxx_Spi_DevAddrType)dev_addr, GPIO0_H, Sa63xxx_Spi_Single_Read, 2 * SA63122_GPIO_NUMBER);
        Sa63xxx_ResponseRegister(2 * SA63122_GPIO_NUMBER);
        for(i = 0;i < SA63122_GPIO_NUMBER;i++)
        {
            DrvPtr->Gpio_Voltage_Buffer[SA63122_GPIO_NUMBER * (dev_addr - 1) + i] =\
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
    Sa63122_DriverType* DrvPtr = Sa63122_DriverGet();

    for(i = AFE_DEV_ADDR_DEV1;i <= AFE_NUMBER;i++)
    {
        if((true == Sa63122_GetBalCurrentState(DrvPtr, (i - 1))) &&\
            (false == Sa63122_GetBalLastState(DrvPtr, (i - 1))))
        {
            for(j = 0;j < 6;j++)
            {
                Csd_valData_Lo[2 * j] = 0x83;
                Csd_valData_Lo[2 * j + 1] = 0xff;
            }
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, CB_TO_CH1_H, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 12);
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, CB_TO_CH7_H, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 12);
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, CB_TO_CH13_H, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 12);
            Csd_valData_Lo[0] = DrvPtr->bal_cfg[i - 1];
            Csd_valData_Lo[1] = DrvPtr->bal_cfg[i - 1] >> 8;
            Csd_valData_Lo[2] = (DrvPtr->bal_cfg[i - 1] >> 16) & 0x3;
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, CBFET_EN1, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 3);
            Csd_valData_Lo[0] = 0x05;
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, CB_CTRL, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 1);
            Sa63122_UpdateBalLastState(DrvPtr, (i - 1));
        }
        else if((false == Sa63122_GetBalCurrentState(DrvPtr, (i - 1))) &&\
            (true == Sa63122_GetBalLastState(DrvPtr, (i - 1))))
        {
            memset(&Csd_valData_Lo[0], 0 ,12);
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, CB_TO_CH1_H, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 12);
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, CB_TO_CH7_H, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 12);
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, CB_TO_CH13_H, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 12);
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, CBFET_EN1, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 3);
            Csd_valData_Lo[0] = 0x02;
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, CB_CTRL, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 1);
            Sa63122_UpdateBalLastState(DrvPtr, (i - 1));
        }
    }
}

void Sa63122_GetCellBalStatus(void)
{
    uint8_t i = 0;
    uint8_t* Csd_valDataPtr_Lo = Sa63xxx_GetRxData();
    Sa63122_DriverType* DrvPtr = Sa63122_DriverGet();

    Sa63xxx_ReadRegister(Sa63xxx_Spi_Dev_Addr_01, CB_DONE_STAT1, Sa63xxx_Spi_Single_Read, 3);
    Sa63xxx_ResponseRegister(3);
    for(i = 0;i < 3;i++)
    {
        DrvPtr->bal_status[i] = Csd_valDataPtr_Lo[i];
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
    uint8_t* rx_buf_ptr = Sa63xxx_GetRxData();
    Sa63122_DriverType* DrvPtr = Sa63122_DriverGet();
    uint16_t vol_buf2[18] = {0};
    uint16_t* buf1_ptr = &DrvPtr->cell_opl_vol_buf1[0];

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
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, CB_TO_CH1_H, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 12);
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, CB_TO_CH7_H, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 12);
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, CB_TO_CH13_H, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 12);
            Csd_valData_Lo[0] = 0x55;
            Csd_valData_Lo[1] = 0x55;
            Csd_valData_Lo[2] = 0x01;
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, CBFET_EN1, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 3);
            Csd_valData_Lo[0] = 0x04;
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, CB_CTRL, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 1);
            Csd_valData_Lo[0] = 0x05;
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, CB_CTRL, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 1);
            Sa63xxx_Spi_Delay(24000);
            Csd_valData_Lo[0] = 0x02;
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, CB_CTRL, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 1);
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, ADC_CTRL, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 1);
        }
        break;
    case SA63122_CELL_OPL_DECT_STEP_ODD_GET_VOL:
        for(i = AFE_DEV_ADDR_DEV1;i <= AFE_NUMBER;i++)
        {
            Sa63xxx_ReadRegister((Sa63xxx_Spi_DevAddrType)i, CH1_H, Sa63xxx_Spi_Single_Read, 2 * SA63122_CELL_NUMBER);
            Sa63xxx_ResponseRegister(2 * SA63122_CELL_NUMBER);
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
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, CB_TO_CH1_H, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 12);
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, CB_TO_CH7_H, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 12);
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, CB_TO_CH13_H, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 12);
            Csd_valData_Lo[0] = 0xAA;
            Csd_valData_Lo[1] = 0xAA;
            Csd_valData_Lo[2] = 0x02;
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, CBFET_EN1, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 3);
            Csd_valData_Lo[0] = 0x04;
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, CB_CTRL, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 1);
            Csd_valData_Lo[0] = 0x05;
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, CB_CTRL, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 1);
            Sa63xxx_Spi_Delay(24000);
            Csd_valData_Lo[0] = 0x02;
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, CB_CTRL, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 1);
            Sa63xxx_WriteRegister((Sa63xxx_Spi_DevAddrType)i, ADC_CTRL, Sa63xxx_Spi_Single_Write, &Csd_valData_Lo[0], 1);
        }
        break;
    case SA63122_CELL_OPL_DECT_STEP_EVEN_GET_VOL:
        for(i = AFE_DEV_ADDR_DEV1;i <= AFE_NUMBER;i++)
        {
            Sa63xxx_ReadRegister((Sa63xxx_Spi_DevAddrType)i, CH1_H, Sa63xxx_Spi_Single_Read, 2 * SA63122_CELL_NUMBER);
            Sa63xxx_ResponseRegister(2 * SA63122_CELL_NUMBER);
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
                DrvPtr->cell_opl[i - 1] |= (1 << 0);
            else
                DrvPtr->cell_opl[i - 1] &= ~(1 << 0);

            if((vol_buf1[2] < 2500) && (vol_buf2[1] < 2500))    // cell_2
                DrvPtr->cell_opl[i - 1] |= (1 << 1);
            else
                DrvPtr->cell_opl[i - 1] &= ~(1 << 1);

            if((vol_buf1[2] < 2500) && (vol_buf2[3] < 2500))    // cell_3
                DrvPtr->cell_opl[i - 1] |= (1 << 2);
            else
                DrvPtr->cell_opl[i - 1] &= ~(1 << 2);

            if((vol_buf1[4] < 2500) && (vol_buf2[3] < 2500))    // cell_4
                DrvPtr->cell_opl[i - 1] |= (1 << 3);
            else
                DrvPtr->cell_opl[i - 1] &= ~(1 << 3);

            if((vol_buf1[4] < 2500) && (vol_buf2[5] < 2500))    // cell_5
                DrvPtr->cell_opl[i - 1] |= (1 << 4);
            else
                DrvPtr->cell_opl[i - 1] &= ~(1 << 4);

            if((vol_buf1[6] < 2500) && (vol_buf2[5] < 2500))    // cell_6
                DrvPtr->cell_opl[i - 1] |= (1 << 5);
            else
                DrvPtr->cell_opl[i - 1] &= ~(1 << 5);

            if((vol_buf1[6] < 2500) && (vol_buf2[7] < 2500))    // cell_7
                DrvPtr->cell_opl[i - 1] |= (1 << 6);
            else
                DrvPtr->cell_opl[i - 1] &= ~(1 << 6);

            if((vol_buf1[8] < 2500) && (vol_buf2[7] < 2500))    // cell_8
                DrvPtr->cell_opl[i - 1] |= (1 << 7);
            else
                DrvPtr->cell_opl[i - 1] &= ~(1 << 7);

            if((vol_buf1[8] < 2500) && (vol_buf2[9] < 2500))    // cell_9
                DrvPtr->cell_opl[i - 1] |= (1 << 8);
            else
                DrvPtr->cell_opl[i - 1] &= ~(1 << 8);

            if((vol_buf1[10] < 2500) && (vol_buf2[9] < 2500))   // cell_10
                DrvPtr->cell_opl[i - 1] |= (1 << 9);
            else
                DrvPtr->cell_opl[i - 1] &= ~(1 << 9);

            if((vol_buf1[10] < 2500) && (vol_buf2[11] < 2500))  // cell_11
                DrvPtr->cell_opl[i - 1] |= (1 << 10);
            else
                DrvPtr->cell_opl[i - 1] &= ~(1 << 10);

            if((vol_buf1[12] < 2500) && (vol_buf2[11] < 2500))  // cell_12
                DrvPtr->cell_opl[i - 1] |= (1 << 11);
            else
                DrvPtr->cell_opl[i - 1] &= ~(1 << 11);

            if((vol_buf1[12] < 2500) && (vol_buf2[13] < 2500))  // cell_13
                DrvPtr->cell_opl[i - 1] |= (1 << 12);
            else
                DrvPtr->cell_opl[i - 1] &= ~(1 << 12);

            if((vol_buf1[14] < 2500) && (vol_buf2[13] < 2500))  // cell_14
                DrvPtr->cell_opl[i - 1] |= (1 << 13);
            else
                DrvPtr->cell_opl[i - 1] &= ~(1 << 13);

            if((vol_buf1[14] < 2500) && (vol_buf2[15] < 2500))  // cell_15
                DrvPtr->cell_opl[i - 1] |= (1 << 14);
            else
                DrvPtr->cell_opl[i - 1] &= ~(1 << 14);

            if((vol_buf1[16] < 2500) && (vol_buf2[15] < 2500))  // cell_16
                DrvPtr->cell_opl[i - 1] |= (1 << 15);
            else
                DrvPtr->cell_opl[i - 1] &= ~(1 << 15);

            if((vol_buf1[16] < 2500) && (vol_buf2[17] < 2500))  // cell_17
                DrvPtr->cell_opl[i - 1] |= (1 << 16);
            else
                DrvPtr->cell_opl[i - 1] &= ~(1 << 16);
            
            // cell18
            */
            for(;buf1_idx <= 16;)
            {
                if((buf1_ptr[buf1_idx] < SA63122_CELL_OPL_DECT_THR) &&\
                    (vol_buf2[buf2_idx] < SA63122_CELL_OPL_DECT_THR))
                    SA63122_SET_BIT(DrvPtr->cell_opl[i - 1], bit_pos++);
                else
                    SA63122_CLR_BIT(DrvPtr->cell_opl[i - 1], bit_pos++);
                
                if(16 == buf1_idx)
                    break;
                
                if((buf1_ptr[2 + buf1_idx] < SA63122_CELL_OPL_DECT_THR) &&\
                    (vol_buf2[buf2_idx] < SA63122_CELL_OPL_DECT_THR))
                    SA63122_SET_BIT(DrvPtr->cell_opl[i - 1], bit_pos++);
                else
                    SA63122_CLR_BIT(DrvPtr->cell_opl[i - 1], bit_pos++);
                buf1_idx += 2;
                buf2_idx += 2;
            }
        }
        break;
    default:
        break;
    }
}
