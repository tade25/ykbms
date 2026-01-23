#ifndef __AFE_RELEASE_PRV_H_
#define __AFE_RELEASE_PRV_H_

/**
 * @brief  AFE初始化函数，需要在底层初始化中调用
 * @param  none
 * @retval none
 */
extern void Afe_Init(void);

/**
 * @brief  AFE的10ms调度函数，需要在OS的任务中调用
 * @param  none
 * @retval none
 */
extern void Afe_MainFunction_10ms(void);

#endif /* __AFE_RELEASE_PRV_H_ */
