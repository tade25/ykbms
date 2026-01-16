#ifndef __AFE_TYPES_H_
#define __AFE_TYPES_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/********************************* 宏定义 ****************************************/
#define AFE_NUMBER  1
#define AFE_DEV_ADDR_ALL    0xFF
#define AFE_DEV_ADDR_BRIDGE 0
#define AFE_DEV_ADDR_DEV1   1
#define AFE_DEV_ADDR_DEV2   2
#define AFE_DEV_ADDR_DEV3   3
#define AFE_DEV_ADDR_DEV4   4
#define AFE_DEV_ADDR_DEV5   5
#define AFE_DEV_ADDR_DEV6   6
#define AFE_DEV_ADDR_DEV7   7
#define AFE_DEV_ADDR_DEV8   8

#define AFE_DRIVER_VERSION_MAJOR_MINOR(major,minor) (((major) << 8) | (minor))
#define AFE_API_VERSION AFE_DRIVER_VERSION_MAJOR_MINOR(0, 1)//api version
#define AFE_DRV_VERSION AFE_DRIVER_VERSION_MAJOR_MINOR(0, 1)//driver version

#define AFE_STATUS_START    0   /* 开启一次采集 */
#define AFE_STATUS_ACQU     1   /* 进行采集 */
#define AFE_STATUS_OW       2   /* 1s进行一次开路检测 */

/********************************* 类型重定义 ****************************************/
typedef struct {
    uint16_t api;
    uint16_t drv;
} Afe_DriverVersion;

typedef enum {
    AFE_DEVICE_STATE_UNINIT,
    AFE_DEVICE_STATE_INITING,
    AFE_DEVICE_STATE_READY,
    AFE_DEVICE_STATE_ERROR
}Afe_DevState;

typedef struct {
    Afe_DevState state;
    Afe_DriverVersion version;
    bool (*init)(void*);
    void (*process)(void*);
    uint16_t (*get_cell_vol)(uint8_t);
    uint32_t (*get_temp_rist)(uint8_t);
    uint32_t (*get_cell_opl)(uint8_t);
    uint16_t (*get_rist_opl)(uint8_t);
    void (*set_cell_bal)(uint8_t, uint32_t, uint8_t);
    uint32_t (*get_cell_bal_stat)(uint8_t);
}Afe_BaseDev;

#endif /* __AFE_TYPES_H_ */
