/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-16     Rick       the first version
 */
#include <fal.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>
#include <stdlib.h>

#define DBG_TAG "Storage"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

static uint32_t dest_addr = 0;
static const struct fal_partition *part_dev = NULL;

void StorageInit(void)
{
    fal_init();
    part_dev = fal_partition_find("cfg");
    if (part_dev != RT_NULL)
    {
        LOG_D("Probed a flash partition | %s | flash_dev: %s | offset: %ld | len: %d |.\n",
                part_dev->name, part_dev->flash_name, part_dev->offset, part_dev->len);
    }
    fal_partition_read(part_dev, 0, &dest_addr, 4);
    if(dest_addr == 0 || dest_addr == 0xFFFFFFFF)
    {
        dest_addr = 10000001;
    }
    LOG_D("dest_addr %d\r\n",dest_addr);
}

void Storage_Main_Write(uint32_t device_id)
{
    dest_addr = device_id;
    fal_partition_erase(part_dev, 0, 4);
    fal_partition_write(part_dev, 0, &device_id, 4);
}

uint32_t Storage_Main_Read(void)
{
    return dest_addr;
}
