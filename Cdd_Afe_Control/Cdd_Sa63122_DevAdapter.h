#ifndef __CDD_SA63122_DEVADAPTER_H_
#define __CDD_SA63122_DEVADAPTER_H_

#include "Cdd_Sa63122_Driver.h"

typedef struct {
    Afe_BaseDev base;
    uint16_t opl_dect_cnt;
    uint8_t opl_dect_step;
    uint8_t curr_dev;
    uint8_t status;
}Sa63122_DevType;

extern Sa63122_DevType* Sa63122_DevGet(void);

#endif
