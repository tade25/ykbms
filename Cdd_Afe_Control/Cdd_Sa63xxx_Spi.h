#ifndef __CDD_SA63XXX_SPI_H_
#define __CDD_SA63XXX_SPI_H_

#include "Sa63xxx_Reg_Types.h"
#include "Sa63000_Spi_Hal.h"

extern uint8_t Css_valTxBuffer_Mp[SA63000_CONFIG_SPI_TX_BUFFER_SIZE];

/**
 * @brief  获取从机返回数据
 * @param  none
 * @retval uint8_t* 数据首地址
 */
extern uint8_t* Sa63122_GetRxData(void);

/**
 * @brief  计算Modbus协议的16位CRC校验值（查表法实现）
 * @param  data_Input 输入数据缓冲区指针，指向待计算CRC校验的字节数组
 * @param  length     输入数据的有效字节长度
 * @retval uint16_t   计算完成的Modbus CRC16校验结果
 * @note   1. 依赖预定义的Modbus CRC16查表法数组 Cas_valCrc16Table_Mp，
 *         2. Modbus CRC16标准规定初始值为0xFFFF，无最终异或值
 *         3. 输入参数data_Input需保证有效，且length不超过缓冲区长度
 */
extern uint16_t Crc16_Modbus(uint8_t* data_Input, uint8_t length);

/**
 * @brief  Sa63122的将响应推出的函数
 * @param  data_len 数据长度
 * @retval Std_ReturnType 成功(返回0)/失败(返回1)
 */
extern Std_ReturnType Sa63122_ResponseRegister(uint8_t data_len);

/**
 * @brief  Sa63122的spi写函数
 * @param  dev_addr 设备地址 / 在stack_write/addressing时传入0即可
 * @param  reg_addr 寄存器地址
 * @param  rw_type 读写类型
 * @param  data 数据首地址
 * @param  init_byte 数据的首字节
 * @retval Std_ReturnType 成功(返回0)/失败(返回1)
 */
extern Std_ReturnType Sa63122_WriteRegister(
    Sa63000_Spi_DevAddrType dev_addr,
    Sa63122_RegType reg_addr,
    Sa63000_Spi_WType w_type,
    uint8_t* data,
    uint8_t data_len
);

/**
 * @brief  Sa63122的spi读函数
 * @param  dev_addr 设备地址 / 在stack_read时传入0即可
 * @param  reg_addr 寄存器地址
 * @param  r_type 读类型
 * @param  data_len 数据长度
 * @retval Std_ReturnType 成功(返回0)/失败(返回1)
 */
extern Std_ReturnType Sa63122_ReadRegister(
    Sa63000_Spi_DevAddrType dev_addr,
    Sa63122_RegType reg_addr,
    Sa63000_Spi_RType r_type,
    uint8_t data_len
);

#endif /* __CDD_SA63XXX_SPI_H_ */
