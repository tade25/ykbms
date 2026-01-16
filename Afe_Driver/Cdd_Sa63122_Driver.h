#ifndef __CDD_SA63122_DRIVER_H_
#define __CDD_SA63122_DRIVER_H_

#include "Afe_Types.h"
#include "Sa63xxx_Spi.h"

/********************************* 宏定义 ****************************************/
#define SA63122_UINT8_COMBINE_TO_UINT16(high_byte, low_byte)  ((uint16_t)(((uint16_t)(high_byte) << 8) |\
                                                                (uint16_t)(low_byte)))
#define SA63122_SET_BIT(x, bit)                     ((x) |= (1U << (bit)))
#define SA63122_CLR_BIT(x, bit)                     ((x) &= ~(1U << (bit)))
#define SA63122_CELL_OPL_DECT_THR                   2800
#define SA63122_CELL_OPL_DECT_STEP_ODD_BAL          0
#define SA63122_CELL_OPL_DECT_STEP_ODD_GET_VOL      1
#define SA63122_CELL_OPL_DECT_STEP_EVEN_BAL         2
#define SA63122_CELL_OPL_DECT_STEP_EVEN_GET_VOL     3
#define SA63122_CELL_OPL_DECT_STEP_MAX              4
#define SA63122_CELL_NUMBER                         18
#define SA63122_GPIO_NUMBER                         12
#define SA63122_FACT_REG1_MAX                       (10)
#define SA63122_FACT_REG2_MAX                       (128)
// #define SA63122_DELAY_28MS  7000 * AFE_NUMBER* (SA63000_CONFIG_DELAY_1US_CNT)
#define SA63122_DELAY_14MS                          7000 * 2* (SA63000_CONFIG_DELAY_1US_CNT)
#define SA63122_DELAY_78MS                          78000 * (SA63000_CONFIG_DELAY_1US_CNT)

#define SA63122_CALC_CELL_VOLTAGE(vol_buf)          (uint16_t)(0.2 * vol_buf)
#define SA63122_CALC_GPIO_VOLTAGE(vol_buf)          (0.00004 * 2.5 * vol_buf)
#define SA63122_CALC_TEMP_RIST(vol)                 (uint32_t)(10000.0 * (vol) / (2.5 - (vol)))

#define CELL_NUMBER_MAX                             (AFE_NUMBER) * (SA63122_CELL_NUMBER)
#define GPIO_NUMBER_MAX                             (AFE_NUMBER) * (SA63122_GPIO_NUMBER)

#define BAL_CURRENT_STATE_BIT                       0U     // bit0：当前均衡开关状态
#define BAL_LAST_STATE_BIT                          1U     // bit1：上一次均衡开关状态
#define BAL_CURRENT_STATE_MASK                      (1U << BAL_CURRENT_STATE_BIT)
#define BAL_LAST_STATE_MASK                         (1U << BAL_LAST_STATE_BIT)

/* SA63122 需要计算CRC的配置寄存器 */
typedef struct {
    union{
        struct{
            uint8_t TOP_DEV    :1;
            uint8_t ADD        :7;
        };
        uint8_t R;
    }A_DEV_ADD1;

    union{
        struct{
            uint8_t RSVD       :1;
            uint8_t NUM        :7;
        };
        uint8_t R;
    }A_DEV_ADD2;

    union{
        struct{
            uint8_t CB_STL     :5;
            uint8_t RSVD1      :2;
            uint8_t I2C_MAS_EN :1;
        };
        uint8_t R;
    }A_COMM_CONF1;

    union{
        struct{
            uint8_t COMN_TX_DIS :1;
            uint8_t COMS_TX_DIS :1;
            uint8_t STACK_RESP  :6;
        };
        uint8_t R;
    }A_COMM_CONF2;

    union{
        struct{
            uint8_t LCTO_SEL   :2;
            uint8_t LONG       :3;
            uint8_t SHORT      :3;
        };
        uint8_t R;
    }A_COMM_TO;

    uint8_t A_RSVD_0005;

    union{
        struct{
            uint8_t GPIO_COMP_THR :3;
            uint8_t CELL_COMP_THR :5;
        };
        uint8_t R;
    }A_COMP_CONF1;

    union{
        struct{
            uint8_t RSVD1         :3;
            uint8_t CELL_COMP_DEGL:5;
        };
        uint8_t R;
    }A_COMP_CONF2;

    union{
        struct{
            uint8_t RSVD2       :1;
            uint8_t LPF_VCELL   :2;
            uint8_t RSVD1       :5;
        };
        uint8_t R;
    }A_ADC_CONF;

    uint8_t A_RSVD_0009;

    union{
        struct{
            uint8_t CH_SET      :4;
            uint8_t RSVD1       :4;
        };
        uint8_t R;
    }A_MEA_CONF;

    uint8_t A_RSVD_000B;
    uint8_t A_RSVD_000C;

    union{
        struct{
            uint8_t SLP_PERIOD  :6;
            uint8_t RSVD1       :1;
            uint8_t SLP_MON_EN  :1;
        };
        uint8_t R;
    }A_SLP_MON_CONF;

    union{
        struct{
            uint8_t OVUV_OTUT_EN:1;
            uint8_t RSVD1       :2;
            uint8_t OVUV_DEGL   :5;
        };
        uint8_t R;
    }A_OVUV_OTUT_CONF1;

    union{
        struct{
            uint8_t RSVD1       :1;
            uint8_t OV_THR      :7;
        };
        uint8_t R;
    }A_OVUV_OTUT_CONF2;

    union{
        struct{
            uint8_t RSVD1       :1;
            uint8_t UV_THR      :7;
        };
        uint8_t R;
    }A_OVUV_OTUT_CONF3;

    union{
        struct{
            uint8_t RSVD1       :1;
            uint8_t OT_PACK_THR :4;
            uint8_t UT_PACK_THR :3;
        };
        uint8_t R;
    }A_OVUV_OTUT_CONF4;

    union{
        struct{
            uint8_t RSVD1       :1;
            uint8_t OT_PCB_THR  :4;
            uint8_t UT_PCB_THR  :3;
        };
        uint8_t R;
    }A_OVUV_OTUT_CONF5;

    union{
        struct{
            uint8_t GPIO7_THR_SEL:1;
            uint8_t GPIO6_THR_SEL:1;
            uint8_t GPIO5_THR_SEL:1;
            uint8_t GPIO4_THR_SEL:1;
            uint8_t GPIO3_THR_SEL:1;
            uint8_t GPIO2_THR_SEL:1;
            uint8_t GPIO1_THR_SEL:1;
            uint8_t GPIO0_THR_SEL:1;
        };
        uint8_t R;
    }A_OVUV_OTUT_CONF6;

    union{
        struct{
            uint8_t RSVD1        :4;
            uint8_t GPIO11_THR_SEL:1;
            uint8_t GPIO10_THR_SEL:1;
            uint8_t GPIO9_THR_SEL:1;
            uint8_t GPIO8_THR_SEL:1;
        };
        uint8_t R;
    }A_OVUV_OTUT_CONF7;

    union{
        struct{
            uint8_t CB_ROT_PACK_THR:5;
            uint8_t CB_DUTY      :3;
        };
        uint8_t R;
    }A_CB_CONF1;

    union{
        struct{
            uint8_t CB_ROT_PCB_THR:5;
            uint8_t CB_PERIOD    :3;
        };
        uint8_t R;
    }A_CB_CONF2;

    union{
        struct{
            uint8_t CB_JOT_THR   :4;
            uint8_t ROT_PAUSE_EN :1;
            uint8_t ADC_PAUSE_EN :1;
            uint8_t JOT_PAUSE_EN :1;
            uint8_t FLT_STOP_EN  :1;
        };
        uint8_t R;
    }A_CB_CONF3;

    union{
        struct{
            uint8_t RSVD1        :5;
            uint8_t TWARN_THR    :3;
        };
        uint8_t R;
    }A_TWARN_CONF;

    union{
        struct{
            uint8_t GPIO7       :1;
            uint8_t GPIO6       :1;
            uint8_t GPIO5       :1;
            uint8_t GPIO4       :1;
            uint8_t GPIO3       :1;
            uint8_t GPIO2       :1;
            uint8_t GPIO1       :1;
            uint8_t GPIO0       :1;
        };
        uint8_t R;
    }A_GPIO_DO_EN1;

    union{
        struct{
            uint8_t RSVD1       :4;
            uint8_t GPIO11      :1;
            uint8_t GPIO10      :1;
            uint8_t GPIO9       :1;
            uint8_t GPIO8       :1;
        };
        uint8_t R;
    }A_GPIO_DO_EN2;

    union{
        struct{
            uint8_t GPIO7       :1;
            uint8_t GPIO6       :1;
            uint8_t GPIO5       :1;
            uint8_t GPIO4       :1;
            uint8_t GPIO3       :1;
            uint8_t GPIO2       :1;
            uint8_t GPIO1       :1;
            uint8_t GPIO0       :1;
        };
        uint8_t R;
    }A_GPIO_DI_EN1;

    union{
        struct{
            uint8_t RSVD1       :4;
            uint8_t GPIO11      :1;
            uint8_t GPIO10      :1;
            uint8_t GPIO9       :1;
            uint8_t GPIO8       :1;
        };
        uint8_t R;
    }A_GPIO_DI_EN2;

    union{
        struct{
            uint8_t GPIO7       :1;
            uint8_t GPIO6       :1;
            uint8_t GPIO5       :1;
            uint8_t GPIO4       :1;
            uint8_t GPIO3       :1;
            uint8_t GPIO2       :1;
            uint8_t GPIO1       :1;
            uint8_t GPIO0       :1;
        };
        uint8_t R;
    }A_GPIO_WEAK_PUPD_EN1;

    union{
        struct{
            uint8_t RSVD1       :4;
            uint8_t GPIO11      :1;
            uint8_t GPIO10      :1;
            uint8_t GPIO9       :1;
            uint8_t GPIO8       :1;
        };
        uint8_t R;
    }A_GPIO_WEAK_PUPD_EN2;

    union{
        struct{
            uint8_t RSVD1        :4;
            uint8_t SYS_FLT_MSK  :1;
            uint8_t COMP_FLT_MSK :1;
            uint8_t OTUT_FLT_MSK :1;
            uint8_t OVUV_FLT_MSK :1;
        };
        uint8_t R;
    }A_FLT_SUM_MSK;

    uint8_t A_RSVD_0101;
    uint8_t A_RSVD_0102;
    uint8_t A_RSVD_0103;

    union{
        struct{
            uint8_t CH8_MSK     :1;
            uint8_t CH7_MSK     :1;
            uint8_t CH6_MSK     :1;
            uint8_t CH5_MSK     :1;
            uint8_t CH4_MSK     :1;
            uint8_t CH3_MSK     :1;
            uint8_t CH2_MSK     :1;
            uint8_t CH1_MSK     :1;
        };
        uint8_t R;
    }A_OV_FLT_MSK1;

    union{
        struct{
            uint8_t CH16_MSK    :1;
            uint8_t CH15_MSK    :1;
            uint8_t CH14_MSK    :1;
            uint8_t CH13_MSK    :1;
            uint8_t CH12_MSK    :1;
            uint8_t CH11_MSK    :1;
            uint8_t CH10_MSK    :1;
            uint8_t CH9_MSK     :1;
        };
        uint8_t R;
    }A_OV_FLT_MSK2;

    union{
        struct{
            uint8_t RSVD1       :6;
            uint8_t CH18_MSK    :1;
            uint8_t CH17_MSK    :1;
        };
        uint8_t R;
    }A_OV_FLT_MSK3;

    union{
        struct{
            uint8_t CH8_MSK     :1;
            uint8_t CH7_MSK     :1;
            uint8_t CH6_MSK     :1;
            uint8_t CH5_MSK     :1;
            uint8_t CH4_MSK     :1;
            uint8_t CH3_MSK     :1;
            uint8_t CH2_MSK     :1;
            uint8_t CH1_MSK     :1;
        };
        uint8_t R;
    }A_UV_FLT_MSK1;

    union{
        struct{
            uint8_t CH16_MSK    :1;
            uint8_t CH15_MSK    :1;
            uint8_t CH14_MSK    :1;
            uint8_t CH13_MSK    :1;
            uint8_t CH12_MSK    :1;
            uint8_t CH11_MSK    :1;
            uint8_t CH10_MSK    :1;
            uint8_t CH9_MSK     :1;
        };
        uint8_t R;
    }A_UV_FLT_MSK2;

    union{
        struct{
            uint8_t RSVD1       :6;
            uint8_t CH18_MSK    :1;
            uint8_t CH17_MSK    :1;
        };
        uint8_t R;
    }A_UV_FLT_MSK3;

    union{
        struct{
            uint8_t CH8_MSK     :1;
            uint8_t CH7_MSK     :1;
            uint8_t CH6_MSK     :1;
            uint8_t CH5_MSK     :1;
            uint8_t CH4_MSK     :1;
            uint8_t CH3_MSK     :1;
            uint8_t CH2_MSK     :1;
            uint8_t CH1_MSK     :1;
        };
        uint8_t R;
    }A_CELL_COMP_FLT_MSK1;

    union{
        struct{
            uint8_t CH16_MSK    :1;
            uint8_t CH15_MSK    :1;
            uint8_t CH14_MSK    :1;
            uint8_t CH13_MSK    :1;
            uint8_t CH12_MSK    :1;
            uint8_t CH11_MSK    :1;
            uint8_t CH10_MSK    :1;
            uint8_t CH9_MSK     :1;
        };
        uint8_t R;
    }A_CELL_COMP_FLT_MSK2;

    union{
        struct{
            uint8_t RSVD1       :6;
            uint8_t CH18_MSK    :1;
            uint8_t CH17_MSK    :1;
        };
        uint8_t R;
    }A_CELL_COMP_FLT_MSK3;

    union{
        struct{
            uint8_t GPIO7_MSK   :1;
            uint8_t GPIO6_MSK   :1;
            uint8_t GPIO5_MSK   :1;
            uint8_t GPIO4_MSK   :1;
            uint8_t GPIO3_MSK   :1;
            uint8_t GPIO2_MSK   :1;
            uint8_t GPIO1_MSK   :1;
            uint8_t GPIO0_MSK   :1;
        };
        uint8_t R;
    }A_GPIO_COMP_FLT_MSK1;

    union{
        struct{
            uint8_t RSVD1       :4;
            uint8_t GPIO11_MSK  :1;
            uint8_t GPIO10_MSK  :1;
            uint8_t GPIO9_MSK   :1;
            uint8_t GPIO8_MSK   :1;
        };
        uint8_t R;
    }A_GPIO_COMP_FLT_MSK2;

    union{
        struct{
            uint8_t GPIO7_MSK   :1;
            uint8_t GPIO6_MSK   :1;
            uint8_t GPIO5_MSK   :1;
            uint8_t GPIO4_MSK   :1;
            uint8_t GPIO3_MSK   :1;
            uint8_t GPIO2_MSK   :1;
            uint8_t GPIO1_MSK   :1;
            uint8_t GPIO0_MSK   :1;
        };
        uint8_t R;
    }A_OT_FLT_MSK1;

    union{
        struct{
            uint8_t RSVD1       :4;
            uint8_t GPIO11_MSK  :1;
            uint8_t GPIO10_MSK  :1;
            uint8_t GPIO9_MSK   :1;
            uint8_t GPIO8_MSK   :1;
        };
        uint8_t R;
    }A_OT_FLT_MSK2;

    union{
        struct{
            uint8_t GPIO7_MSK   :1;
            uint8_t GPIO6_MSK   :1;
            uint8_t GPIO5_MSK   :1;
            uint8_t GPIO4_MSK   :1;
            uint8_t GPIO3_MSK   :1;
            uint8_t GPIO2_MSK   :1;
            uint8_t GPIO1_MSK   :1;
            uint8_t GPIO0_MSK   :1;
        };
        uint8_t R;
    }A_UT_FLT_MSK1;

    union{
        struct{
            uint8_t RSVD1       :4;
            uint8_t GPIO11_MSK  :1;
            uint8_t GPIO10_MSK  :1;
            uint8_t GPIO9_MSK   :1;
            uint8_t GPIO8_MSK   :1;
        };
        uint8_t R;
    }A_UT_FLT_MSK2;

    union{
        struct{
            uint8_t RSVD1       :4;
            uint8_t TBYTE_FAST_MSK:1;
            uint8_t TBYTE_TO_MSK :1;
            uint8_t FCOMM_FLT_MSK:1;
            uint8_t FR_CRC_MSK   :1;
        };
        uint8_t R;
    }A_SYS_FLT_MSK1;

    union{
        struct{
            uint8_t TWARN_MSK   :1;
            uint8_t GND_OW_MSK  :1;
            uint8_t CONF_CRC_MSK:1;
            uint8_t MTP_CRC_MSK :1;
            uint8_t CP_OV_MSK   :1;
            uint8_t CP_UV_MSK   :1;
            uint8_t VAA_OV_MSK  :1;
            uint8_t VAA_UV_MSK  :1;
        };
        uint8_t R;
    }A_SYS_FLT_MSK2;

    uint8_t A_RSVD_0115;

    union{
        struct{
            uint8_t RSVD2       :1;
            uint8_t CB_CONF_FLT_MSK:1;
            uint8_t SCTO_MSK    :1;
            uint8_t LCTO_MSK    :1;
            uint8_t RSVD1       :3;
            uint8_t CMP_FLT_MSK :1;
        };
        uint8_t R;
    }A_SYS_FLT_MSK4;

    union{
        struct{
            uint8_t RSVD1       :5;
            uint8_t HBFAST_MSK  :1;
            uint8_t HBTO_MSK    :1;
            uint8_t FLT_TONE_DET_MSK:1;
        };
        uint8_t R;
    }A_SYS_FLT_MSK5;

    uint8_t	FACT_REG1[10];
    uint8_t	FACT_REG2[128];
	uint8_t A_CONF_CRC_H;
	uint8_t A_CONF_CRC_L;
} Sa63122_RegRecordType;

typedef struct {
    Sa63122_RegRecordType reg_record[AFE_NUMBER];
    uint32_t bal_cfg[AFE_NUMBER];
    uint32_t cell_opl[AFE_NUMBER];
    uint16_t Cell_Voltage_Buffer[AFE_NUMBER * SA63122_CELL_NUMBER];
    uint16_t Gpio_Voltage_Buffer[AFE_NUMBER * SA63122_GPIO_NUMBER];
    uint16_t rist_opl[AFE_NUMBER];
    uint16_t cell_opl_vol_buf1[AFE_NUMBER * SA63122_CELL_NUMBER];
    uint8_t status[AFE_NUMBER];
    uint8_t bal_status[3 * AFE_NUMBER];
}Sa63122_DriverType;

/********************************* 内联函数 ****************************************/
/**
 * @brief  更新指定AFE的均衡上一次状态（将当前状态值赋给上一次状态）
 * @param  p_driver: 指向Sa63122_DriverType结构体的指针
 * @param  afe_idx:  AFE索引（0 ~ AFE_NUMBER-1）
 * @retval bool:     操作成功返回true，参数错误返回false
 */
static inline bool Sa63122_UpdateBalLastState(Sa63122_DriverType *p_driver, uint8_t afe_idx)
{
    uint8_t current_state = (p_driver->status[afe_idx] & BAL_CURRENT_STATE_MASK) >> BAL_CURRENT_STATE_BIT;

    if (p_driver == NULL || afe_idx >= AFE_NUMBER) {
        return false;
    }
    
    p_driver->status[afe_idx] &= ~BAL_LAST_STATE_MASK;
    p_driver->status[afe_idx] |= (current_state << BAL_LAST_STATE_BIT);

    return true;
}

/**
 * @brief  设置指定AFE的均衡当前状态（更新bit0）
 * @param  p_driver: 指向Sa63122_DriverType结构体的指针
 * @param  afe_idx:  AFE索引（0 ~ AFE_NUMBER-1）
 * @param  is_on:    均衡开关状态（true=开启，false=关闭）
 * @retval bool:     操作成功返回true，参数错误返回false
 */
static inline bool Sa63122_SetBalCurrentState(Sa63122_DriverType *p_driver, uint8_t afe_idx, bool is_on)
{
    if (p_driver == NULL || afe_idx >= AFE_NUMBER) {
        return false;
    }

    p_driver->status[afe_idx] &= ~BAL_CURRENT_STATE_MASK;
    if (is_on) {
        p_driver->status[afe_idx] |= BAL_CURRENT_STATE_MASK;
    }

    return true;
}

/**
 * @brief  获取指定AFE的均衡当前状态
 * @param  p_driver: 指向Sa63122_DriverType结构体的指针
 * @param  afe_idx:  AFE索引（0 ~ AFE_NUMBER-1）
 * @retval bool:     有效状态返回true/false，参数错误返回false
 */
static inline bool Sa63122_GetBalCurrentState(const Sa63122_DriverType *p_driver, uint8_t afe_idx)
{
    if (p_driver == NULL || afe_idx >= AFE_NUMBER) {
        return false;
    }
    return (p_driver->status[afe_idx] & BAL_CURRENT_STATE_MASK) != 0;
}

/**
 * @brief  获取指定AFE的均衡上一次状态
 * @param  p_driver: 指向Sa63122_DriverType结构体的指针
 * @param  afe_idx:  AFE索引（0 ~ AFE_NUMBER-1）
 * @retval bool:     有效状态返回true/false，参数错误返回false
 */
static inline bool Sa63122_GetBalLastState(const Sa63122_DriverType *p_driver, uint8_t afe_idx)
{
    if (p_driver == NULL || afe_idx >= AFE_NUMBER) {
        return false;
    }
    return (p_driver->status[afe_idx] & BAL_LAST_STATE_MASK) != 0;
}

/********************************* 外部函数声明 ****************************************/
extern Sa63122_DriverType* Sa63122_DriverGet(void);
extern void Sa63122_Reg_CalcCrc(uint8_t dev_addr);
extern void Sa63122_Reg_WriteCrc(uint8_t dev_addr);
extern void Sa63000_RegConfig(void);
extern void Sa63000_SendWakeTone(void);
extern void Sa63122_SendAddressing(void);
extern void Sa63122_ReadFact(void);
extern void Sa63122_RegConfig(void);
extern void Sa63122_StartAdc(void);
extern void Sa63122_ClearFaults(void);
extern void Sa63122_ReadCellVoltage(uint8_t dev_addr);
extern void Sa63122_ReadGpioVoltage(uint8_t dev_addr);
extern void Sa63122_StartCellBal(void);
extern void Sa63122_GetCellBalStatus(void);
extern void Sa63122_OwDetection(uint8_t step);

#endif /* __CDD_AFE_SA63122_H_ */
