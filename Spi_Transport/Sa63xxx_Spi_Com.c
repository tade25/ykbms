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

uint8_t SpiCom_valTxBuffer_Mp[SA63XXX_CONFIG_SPI_TX_BUFFER_SIZE] = {0};
uint8_t SpiCom_valRxBuffer_Mp[SA63XXX_CONFIG_SPI_RX_BUFFER_SIZE] = {0};
static const uint16_t SpiCom_valCrc16Table_Mp[SA63XXX_SPI_COM_CRC_TABLE_SIZE] = {   
    0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
    0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
    0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
    0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
    0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
    0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
    0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
    0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
    0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
    0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
    0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
    0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
    0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
    0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
    0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
    0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
    0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
    0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
    0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
    0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
    0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
    0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
    0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
    0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
    0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
    0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
    0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
    0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
    0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
    0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
    0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
    0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};

/**
 * @brief  计算Modbus协议的16位CRC校验值（查表法实现）
 * @param  data_input 输入数据缓冲区指针，指向待计算CRC校验的字节数组
 * @param  length     输入数据的有效字节长度
 * @retval uint16_t   计算完成的Modbus CRC16校验结果
 * @note   1. 依赖预定义的Modbus CRC16查表法数组 Ssc_valCrc16Table_Mp
 *         2. Modbus CRC16标准规定初始值为0xFFFF，无最终异或值
 *         3. 输入参数data_Input需保证有效，且length不超过缓冲区长度
 */
uint16_t Crc16_Modbus(uint8_t* data_input, uint8_t length)
{
    uint16_t result  = 0xFFFF;
    uint16_t tableNo = 0;
 
    if(NULL == data_input)
        return result;

    for(int i = 0; i < length; i++)
    {
        tableNo = ((result & 0xff) ^ (data_input[i] & 0xff));
        result  = ((result >> 8) & 0xff) ^ SpiCom_valCrc16Table_Mp[tableNo];
    }
    
    return result;  
}


/**
 * @brief  获取从机返回数据
 * @param  none
 * @retval uint8_t* 数据首地址
 */
uint8_t* Sa63xxx_GetRxData(void)
{
    return &SpiCom_valRxBuffer_Mp[4];
}

/**
 * @brief  Sa63122的将响应推出的函数
 * @param  data_len 数据字段的长度
 * @retval Std_ReturnType 成功(返回0)/失败(返回1)
 */
Std_ReturnType Sa63xxx_ResponseRegister(uint8_t data_len)
{
    uint8_t Ssc_valDataLen_Lo = 6 + data_len;
    uint8_t Ssc_valDataPos_Lo = 0;
    Sa63xxx_Spi_Hal_ErrCode Ssc_valRet_Lo = Sa63xxx_Spi_Hal_Ok;
    uint8_t* Ssc_valCmdPtr_Lo = &SpiCom_valTxBuffer_Mp[0];

    if(data_len > SA63XXX_RES_FRAME_DATA_LEN)
        return E_NOT_OK;

    while(!Sa63xxx_GetSpiReadyStatus());

    while(Ssc_valDataLen_Lo--)
    {
        Ssc_valCmdPtr_Lo[Ssc_valDataPos_Lo] = 0xFF;
        Ssc_valDataPos_Lo++;
    }

    Ssc_valRet_Lo = Sa63xxx_Spi_Hal_Transfer(&SpiHal_valConfig_Mp,
                                            &SpiCom_valTxBuffer_Mp[0],
                                            &SpiCom_valRxBuffer_Mp[0],
                                            Ssc_valDataPos_Lo
                                        );
    if(Ssc_valRet_Lo != Sa63xxx_Spi_Hal_Ok)
        return E_NOT_OK;
    
    return E_OK;
}

/**
 * @brief  Sa63122的spi写函数
 * @param  dev_addr 设备地址 / 在stack_write/addressing时传入0即可
 * @param  reg_addr 寄存器地址
 * @param  rw_type 读写类型
 * @param  data 数据首地址
 * @param  init_byte 数据的首字节
 * @retval Std_ReturnType 成功(返回0)/失败(返回1)
 */
Std_ReturnType Sa63xxx_WriteRegister(
    Sa63xxx_Spi_DevAddrType dev_addr,
    uint16 reg_addr,
    Sa63xxx_Spi_WType w_type,
    uint8_t* data,
    uint8_t data_len
)
{
    uint8_t Ssc_valDataPos_Lo = 0;
    uint16_t Ssc_valCrcRes_Lo = 0;
    Sa63xxx_Spi_Hal_ErrCode Ssc_valRet_Lo = Sa63xxx_Spi_Hal_Ok;
    uint8_t* Ssc_valCmdPtr_Lo = &SpiCom_valTxBuffer_Mp[0];

    if(NULL == data)
        return E_NOT_OK;

    if(data_len > SA63XXX_CMD_FRAME_DATA_LEN)
        return E_NOT_OK;

    Ssc_valCmdPtr_Lo[0] = SA63XXX_CMD_FRAME_COMB_INIT(Sa63xxx_Spi_Command_Frame, w_type, data_len);
    if((Sa63xxx_Spi_Stack_Write == w_type) || (Sa63xxx_Spi_Addressing == w_type))
    {
        Ssc_valCmdPtr_Lo[1] = (uint8_t)(reg_addr >> 8);
        Ssc_valCmdPtr_Lo[2] = (uint8_t)(reg_addr >> 0);
        Ssc_valDataPos_Lo = 3;
    }
    else
    {
        Ssc_valCmdPtr_Lo[1] = (uint8_t)dev_addr;
        Ssc_valCmdPtr_Lo[2] = (uint8_t)(reg_addr >> 8);
        Ssc_valCmdPtr_Lo[3] = (uint8_t)(reg_addr >> 0);
        Ssc_valDataPos_Lo = 4; 
    }

    while(data_len--)
    {
        Ssc_valCmdPtr_Lo[Ssc_valDataPos_Lo] = *data;
        Ssc_valDataPos_Lo++;
        data++;
    }

    Ssc_valCrcRes_Lo = Crc16_Modbus(Ssc_valCmdPtr_Lo, Ssc_valDataPos_Lo);
    if(0xFFFF == Ssc_valCrcRes_Lo)
        return E_NOT_OK;
    
    Ssc_valCmdPtr_Lo[Ssc_valDataPos_Lo++] = (uint8_t)(Ssc_valCrcRes_Lo >> 0);
    Ssc_valCmdPtr_Lo[Ssc_valDataPos_Lo++] = (uint8_t)(Ssc_valCrcRes_Lo >> 8);

    Ssc_valRet_Lo = Sa63xxx_Spi_Hal_Transfer(&SpiHal_valConfig_Mp,
                                            &SpiCom_valTxBuffer_Mp[0],
                                            &SpiCom_valRxBuffer_Mp[0],
                                            Ssc_valDataPos_Lo
                                        );
    if(Ssc_valRet_Lo != Sa63xxx_Spi_Hal_Ok)
        return E_NOT_OK;
    
    return E_OK;
}

/**
 * @brief  Sa63122的spi读函数
 * @param  dev_addr 设备地址 / 在stack_read时传入0即可
 * @param  reg_addr 寄存器地址
 * @param  r_type 读类型
 * @param  data_len 数据长度
 * @retval Std_ReturnType 成功(返回0)/失败(返回1)
 */
Std_ReturnType Sa63xxx_ReadRegister(
    Sa63xxx_Spi_DevAddrType dev_addr,
    uint16 reg_addr,
    Sa63xxx_Spi_RType r_type,
    uint8_t data_len
)
{
    uint8_t Ssc_valDataPos_Lo = 0;
    uint16_t Ssc_valCrcRes_Lo = 0;
    Sa63xxx_Spi_Hal_ErrCode Ssc_valRet_Lo = Sa63xxx_Spi_Hal_Ok;
    uint8_t* Ssc_valCmdPtr_Lo = &SpiCom_valTxBuffer_Mp[0];

    if(data_len > SA63XXX_RES_FRAME_DATA_LEN)
        return E_NOT_OK;

    Ssc_valCmdPtr_Lo[0] = SA63XXX_CMD_FRAME_COMB_INIT(Sa63xxx_Spi_Command_Frame, r_type, 1);
    if(Sa63xxx_Spi_Stack_Read == r_type)
    {
        Ssc_valCmdPtr_Lo[1] = (uint8_t)(reg_addr >> 8);
        Ssc_valCmdPtr_Lo[2] = (uint8_t)(reg_addr >> 0);
        Ssc_valCmdPtr_Lo[3] = (data_len - 1);
        Ssc_valDataPos_Lo = 4;
    }
    else
    {
        Ssc_valCmdPtr_Lo[1] = (uint8_t)dev_addr;
        Ssc_valCmdPtr_Lo[2] = (uint8_t)(reg_addr >> 8);
        Ssc_valCmdPtr_Lo[3] = (uint8_t)(reg_addr >> 0);
        Ssc_valCmdPtr_Lo[4] = (data_len - 1);
        Ssc_valDataPos_Lo = 5;
    }

    Ssc_valCrcRes_Lo = Crc16_Modbus(Ssc_valCmdPtr_Lo, Ssc_valDataPos_Lo);
    if(0xFFFF == Ssc_valCrcRes_Lo)
        return E_NOT_OK;
    
    Ssc_valCmdPtr_Lo[Ssc_valDataPos_Lo++] = (uint8_t)(Ssc_valCrcRes_Lo >> 0);
    Ssc_valCmdPtr_Lo[Ssc_valDataPos_Lo++] = (uint8_t)(Ssc_valCrcRes_Lo >> 8);

    Ssc_valRet_Lo = Sa63xxx_Spi_Hal_Transfer(&SpiHal_valConfig_Mp,
                                            &SpiCom_valTxBuffer_Mp[0],
                                            &SpiCom_valRxBuffer_Mp[0],
                                            Ssc_valDataPos_Lo
                                        );
    if(Ssc_valRet_Lo != Sa63xxx_Spi_Hal_Ok)
        return E_NOT_OK;
    
    return E_OK;
}
