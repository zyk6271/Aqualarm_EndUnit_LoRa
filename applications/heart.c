/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-28     Rick       the first version
 */
#include "rtthread.h"
#include "board.h"

#define DBG_TAG "heart"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

RNG_HandleTypeDef rng_handle;

static uint8_t heart_count;

struct rt_lptimer heart_timer;
struct rt_lptimer once_heart_timer;

uint32_t random_second_get(uint32_t min,uint32_t max)
{
    uint32_t value, second = 0;
    HAL_RNG_GenerateRandomNumber(&rng_handle, &value);
    second = value % (max - min + 1) + min;
    return second;
}

void heart_timer_callback(void *parameter)
{
    LOG_D("Heart Retry Count is %d\r\n",heart_count);
    if(heart_count++ < 10)
    {
        RF_HeartWithMain();
    }
    else
    {
        Warning_Active_Num(2);
    }
}

void Start_Heart_Timer(void)
{
    LOG_D("Start Heart_retry timer\r\n");
    rt_lptimer_start(&heart_timer);
}

void Stop_Heart_Timer(void)
{
    LOG_D("Stop_Heart_Timer\r\n");
    rt_lptimer_stop(&heart_timer);
}

void period_heart_start(void)
{
    uint32_t ramdom_sec = random_second_get(30,270) * 1000;
    rt_lptimer_control(&once_heart_timer, RT_TIMER_CTRL_SET_TIME, &ramdom_sec);
    rt_lptimer_start(&once_heart_timer);
}

void once_heart_timer_callback(void *parameter)
{
    heart_count = 0;
    RF_HeartWithMain();
}

void rng_hw_init(void)
{
    rng_handle.Instance = RNG;
    if (HAL_RNG_Init(&rng_handle) != HAL_OK)
    {
        Error_Handler();
    }
}

void rng_hw_deinit(void)
{
    rng_handle.Instance = RNG;
    if (HAL_RNG_DeInit(&rng_handle) != HAL_OK)
    {
        Error_Handler();
    }
}

void heart_init(void)
{
    rng_hw_init();
    rt_lptimer_init(&heart_timer, "heart_timer", heart_timer_callback, RT_NULL,5*60*1000, RT_TIMER_FLAG_ONE_SHOT | RT_TIMER_FLAG_SOFT_TIMER);
    rt_lptimer_init(&once_heart_timer, "once_heart_timer", once_heart_timer_callback, RT_NULL,30*1000, RT_TIMER_FLAG_ONE_SHOT | RT_TIMER_FLAG_SOFT_TIMER);
    rt_lptimer_start(&once_heart_timer);
}
