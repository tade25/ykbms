#include "Afe_Release.h"
#include "Cdd_Sa63122_DevAdapter.h"

#define AFE_DEV_INSTANCE ((void*)Sa63122_DevGet())

/*************************** 释放底层初始化/调度函数 ***************************/
void Afe_Init(void)
{
    Sa63122_DevType* Ar_valDev_Lo = Sa63122_DevGet();
    Afe_BaseDev* Ac_valBase_Lo = &Ar_valDev_Lo->base;

    Ac_valBase_Lo->state = AFE_DEVICE_STATE_INITING;
    if(Ac_valBase_Lo->init && (Ac_valBase_Lo->init(AFE_DEV_INSTANCE)))
    {
        Ac_valBase_Lo->state = AFE_DEVICE_STATE_READY;
    }
    else
    {
        Ac_valBase_Lo->state = AFE_DEVICE_STATE_ERROR;
    }
}

void Afe_MainFunction_10ms(void)
{
    Sa63122_DevType* Ar_valDev_Lo = Sa63122_DevGet();
    Afe_BaseDev* Ac_valBase_Lo = &Ar_valDev_Lo->base;

    if((AFE_DEVICE_STATE_READY == Ac_valBase_Lo->state) && Ac_valBase_Lo->process)
    {
        Ac_valBase_Lo->process(AFE_DEV_INSTANCE);
    }
}

/*************************** 释放应用层接口函数 ***************************/
uint8_t Cdd_Afe_GetVoltageValue(uint8_t ValChId, uint16_t* ValVoltage)
{
    Sa63122_DevType* Ar_valDev_Lo = Sa63122_DevGet();

    if(ValChId >= CELL_NUMBER_MAX)
        return E_NOT_OK;

    *ValVoltage = Ar_valDev_Lo->base.get_cell_vol(ValChId);

    return E_OK;
}

uint8_t Cdd_Afe_GetCellOplStat(uint8_t ValChId, uint32_t* ValStat)
{
    Sa63122_DevType* Ar_valDev_Lo = Sa63122_DevGet();

    if(ValChId >= CELL_NUMBER_MAX)
        return E_NOT_OK;

    *ValStat = Ar_valDev_Lo->base.get_cell_opl(ValChId);

    return E_OK;
}

uint8_t Cdd_Afe_GetRistValue(uint8_t ValChId, uint32_t* ValRist)
{
    Sa63122_DevType* Ar_valDev_Lo = Sa63122_DevGet();
    
    if(ValChId >= GPIO_NUMBER_MAX)
        return E_NOT_OK;

    *ValRist = Ar_valDev_Lo->base.get_temp_rist(ValChId);

    return E_OK;
}

uint8_t Cdd_Afe_GetRistOplStat(uint8_t ValChId, uint32_t* ValStat)
{
    Sa63122_DevType* Ar_valDev_Lo = Sa63122_DevGet();

    if(ValChId >= GPIO_NUMBER_MAX)
        return E_NOT_OK;

    *ValStat = Ar_valDev_Lo->base.get_rist_opl(ValChId);

    return E_OK;
}

uint8_t Cdd_Afe_GetCurrentValue(uint8_t ValChId, float* ValCurrent)
{
    /* 保留 */
    /* 电流采集在高压采集芯片 */
    return E_OK;
}

uint8_t Cdd_Afe_SetBalance(uint8_t ValChId, uint32_t ValBalCfg, uint8_t BalEn)
{
    Sa63122_DevType* Ar_valDev_Lo = Sa63122_DevGet();

    if(ValChId >= AFE_NUMBER)
        return E_NOT_OK;
    
    Ar_valDev_Lo->base.set_cell_bal(ValChId, ValBalCfg, BalEn);

    return E_OK;
}

uint8_t Cdd_Afe_GetBalanceStatus(uint8_t ValChId, uint32_t* ValBalStat)
{
    Sa63122_DevType* Ar_valDev_Lo = Sa63122_DevGet();

    if(ValChId >= AFE_NUMBER)
        return E_NOT_OK;

    *ValBalStat = Ar_valDev_Lo->base.get_cell_bal_stat(ValChId);

    return E_OK;
}

uint8_t bal_en_mp = 0;
uint32_t bal_cfg_mp = 0;
uint32_t bal_status = 0;
uint16_t vol_buff[18] = {0};
uint32_t rist_buff[12] = {0};
void afe_release_function(void)
{
    uint8_t i = 0;

    for(i = 0;i < 18;i++)
        Cdd_Afe_GetVoltageValue(i, &vol_buff[i]);
    for(i = 0;i < 12;i++)
        Cdd_Afe_GetRistValue(i, &rist_buff[i]);
    Cdd_Afe_SetBalance(0, bal_cfg_mp, bal_en_mp);
    Cdd_Afe_GetBalanceStatus(0, &bal_status);
}
