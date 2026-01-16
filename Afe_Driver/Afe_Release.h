#ifndef __AFE_RELEASE_H_
#define __AFE_RELEASE_H_

#include <stdint.h>

extern uint8_t Cdd_Afe_GetVoltageValue(uint8_t ValChId, uint16_t* ValVoltage);
extern uint8_t Cdd_Afe_GetRistValue(uint8_t ValChId, uint32_t* ValRist);
extern uint8_t Cdd_Afe_GetCellOplStat(uint8_t ValChId, uint32_t* ValStat);
extern uint8_t Cdd_Afe_SetBalance(uint8_t ValChId, uint32_t ValBalCfg, uint8_t BalEn);
extern uint8_t Cdd_Afe_GetBalanceStatus(uint8_t ValChId, uint32_t* ValBalStat);

#endif /* __AFE_RELEASE_H_ */
