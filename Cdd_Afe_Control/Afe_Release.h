#ifndef __AFE_RELEASE_H_
#define __AFE_RELEASE_H_

#include <stdint.h>

uint8_t Cdd_Afe_GetVoltageValue(uint8_t ValChId, uint16_t* ValVoltage);
uint8_t Cdd_Afe_GetCellOplStat(uint8_t ValChId, uint32_t* ValStat);
uint8_t Cdd_Afe_GetRistValue(uint8_t ValChId, uint32_t* ValRist);
uint8_t Cdd_Afe_GetRistOplStat(uint8_t ValChId, uint32_t* ValStat);
uint8_t Cdd_Afe_SetBalance(uint8_t ValChId, uint32_t ValBalCfg, uint8_t BalEn);
uint8_t Cdd_Afe_GetBalanceStatus(uint8_t ValChId, uint32_t* ValBalStat);

#endif /* __AFE_RELEASE_H_ */
