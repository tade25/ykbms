#include "Cdd_Sa63122_DevAdapter.h"
#include "Cdd_Sa63000_Driver.h"

bool Sa63122_Devinit(void* dev)
{
    Sa63000_WakeUpDevices();
    
    Sa63122_ReadFact();
    Sa63122_RegConfig();
    Sa63122_Reg_CalcCrc(0xFF);
    Sa63122_Reg_WriteCrc(0xFF);
    Sa63122_ClearFaults();

    return TRUE;
}

void Sa63122_DevProcess(void* dev)
{
#if 0
    uint8_t i = 0;
    Sa63122_DevType* Cas_valDev_Lo = (Sa63122_DevType*)dev;

    switch(Cas_valDev_Lo->status)
    {
    case AFE_STATUS_START:
        Sa63122_GetCellBalStatus();
        Sa63122_StartCellBal();
        Sa63122_StartAdc();
        Cas_valDev_Lo->status = AFE_STATUS_ACQU;
        break;
	case AFE_STATUS_ACQU:
       Sa63122_ReadCellVoltage(Cas_valDev_Lo->curr_dev + 1);
       Sa63122_ReadGpioVoltage(Cas_valDev_Lo->curr_dev + 1);
        Cas_valDev_Lo->curr_dev++;
        if(AFE_NUMBER == Cas_valDev_Lo->curr_dev) {
            Cas_valDev_Lo->status = AFE_STATUS_START;
            Cas_valDev_Lo->curr_dev = 0;
            Cas_valDev_Lo->opl_dect_cnt += (AFE_NUMBER + 1);
            if(100 == Cas_valDev_Lo->opl_dect_cnt)
            {
                Cas_valDev_Lo->status = AFE_STATUS_OW;
                Cas_valDev_Lo->opl_dect_cnt = 0;
            }
        }
		break;
    case AFE_STATUS_OW:
        Sa63122_OwDetection(Cas_valDev_Lo->opl_dect_step);
        Cas_valDev_Lo->opl_dect_step++;
        if(SA63122_CELL_OPL_DECT_STEP_MAX == Cas_valDev_Lo->opl_dect_step)
        {
			Cas_valDev_Lo->opl_dect_step = 0;
			Cas_valDev_Lo->status = AFE_STATUS_START;
        }
        break;
    default:
        break;
    }
#endif
}

uint16_t Sa63122_DevGetCellVoltage(uint8_t index)
{
    Sa63122_DriverType* Csd_valDrv_Lo = Sa63122_DriverGet();

    return SA63122_CALC_CELL_VOLTAGE(Csd_valDrv_Lo->Cell_Voltage_Buffer[index]);
}

uint32_t Sa63122_DevGetTempRist(uint8_t index)
{
    Sa63122_DriverType* Csd_valDrv_Lo = Sa63122_DriverGet();

    return SA63122_CALC_TEMP_RIST(SA63122_CALC_GPIO_VOLTAGE(Csd_valDrv_Lo->Gpio_Voltage_Buffer[index]));
}

void Sa63122_DevSetCellBal(uint8_t ch, uint32_t bal_cfg, uint8_t bal_en)
{
    Sa63122_DriverType* Csd_valDrv_Lo = Sa63122_DriverGet();

    Csd_valDrv_Lo->bal_cfg[ch] = bal_cfg;
    if(bal_en)
        Sa63122_SetBalCurrentState(Csd_valDrv_Lo, ch, true);
    else
        Sa63122_SetBalCurrentState(Csd_valDrv_Lo, ch, false);
}

uint32_t Sa63122_DevGetCellBalStat(uint8_t ch)
{
    Sa63122_DriverType* Csd_valDrv_Lo = Sa63122_DriverGet();

    return (uint32_t)((uint32_t)(Csd_valDrv_Lo->bal_status[3 * ch] << 0) |\
            (uint32_t)(Csd_valDrv_Lo->bal_status[3 * ch + 1] << 8) |\
            (uint32_t)(Csd_valDrv_Lo->bal_status[3 * ch + 2] << 16));
}

uint32_t Sa63122_DevGetCellOplStat(uint8_t ch)
{

}

uint16_t Sa63122_DevGetRistOplStat(uint8_t ch)
{

}

static Sa63122_DevType Ac_valAfeDev_Mp = {
    .base = {
        .state = AFE_DEVICE_STATE_UNINIT,
        .version = {
            .api = AFE_API_VERSION,
            .drv = AFE_DRV_VERSION,
        },
        .init = Sa63122_Devinit,
        .process = Sa63122_DevProcess,
        .get_cell_vol = Sa63122_DevGetCellVoltage,
        .get_temp_rist = Sa63122_DevGetTempRist,
        .get_cell_opl = Sa63122_DevGetCellOplStat,
        .get_rist_opl = Sa63122_DevGetRistOplStat,
        .set_cell_bal = Sa63122_DevSetCellBal,
        .get_cell_bal_stat = Sa63122_DevGetCellBalStat,
    },
};

Sa63122_DevType* Sa63122_DevGet(void)
{
    return &Ac_valAfeDev_Mp;
}
