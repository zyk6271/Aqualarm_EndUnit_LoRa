/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-16     Rick       the first version
 */

#include "rtthread.h"
#include "main.h"
#include "radio.h"
#include "radio_app.h"
#include "radio_encoder.h"
#include "radio_protocol.h"
#include "radio_protocol_mainunit.h"

#define DBG_TAG "RF_API"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

void RF_Request_Main_Learn(void)
{
    uint8_t data = 2;
    tx_format tx_frame = {0};

    tx_frame.msg_ack = RT_TRUE;
    tx_frame.msg_type = MSG_UNCONFIRMED_UPLINK;
    tx_frame.dest_addr = Storage_Main_Read();
    tx_frame.source_addr = get_local_address();
    tx_frame.command = LEARN_DEVICE_CMD;
    tx_frame.tx_data = &data;
    tx_frame.tx_len = 1;
    radio_mainunit_command_send(&tx_frame);
}

void RF_Learn_Request(void)
{
    uint32_t dest_addr = 0xFFFFFFFF;
    tx_format tx_frame = {0};

    tx_frame.msg_ack = RT_TRUE;
    tx_frame.msg_type = MSG_UNCONFIRMED_UPLINK;
    tx_frame.dest_addr = dest_addr;
    tx_frame.source_addr = get_local_address();
    tx_frame.command = LEARN_DEVICE_CMD;
    radio_mainunit_command_send(&tx_frame);
}

void RF_Open_Valve(void)
{
    uint8_t data = 1;
    tx_format tx_frame = {0};

    tx_frame.msg_ack = RT_TRUE;
    tx_frame.msg_type = MSG_UNCONFIRMED_UPLINK;
    tx_frame.dest_addr = Storage_Main_Read();
    tx_frame.source_addr = get_local_address();
    tx_frame.command = CONTROL_VALVE_CMD;
    tx_frame.tx_data = &data;
    tx_frame.tx_len = 1;
    radio_mainunit_command_send(&tx_frame);
}

void RF_Close_Valve(void)
{
    uint8_t data = 0;
    tx_format tx_frame = {0};
    tx_frame.msg_ack = RT_TRUE;
    tx_frame.msg_type = MSG_UNCONFIRMED_UPLINK;
    tx_frame.dest_addr = Storage_Main_Read();
    tx_frame.source_addr = get_local_address();
    tx_frame.command = CONTROL_VALVE_CMD;
    tx_frame.tx_data = &data;
    tx_frame.tx_len = 1;
    radio_mainunit_command_send(&tx_frame);
}

void RF_Water_Alarm_Enable(void)
{
    tx_format tx_frame = {0};
    uint8_t data[2] = {0x00,0x01};
    tx_frame.msg_ack = RT_TRUE;
    tx_frame.msg_type = MSG_UNCONFIRMED_UPLINK;
    tx_frame.dest_addr = Storage_Main_Read();
    tx_frame.source_addr = get_local_address();
    tx_frame.command = WARNING_UPLOAD_CMD;
    tx_frame.tx_data = data;
    tx_frame.tx_len = 2;
    tx_frame.parameter = 2;
    radio_mainunit_command_send(&tx_frame);
}

void RF_Water_Alarm_Disable(void)
{
    tx_format tx_frame = {0};
    uint8_t data[2] = {0x00,0x00};

    tx_frame.msg_ack = RT_TRUE;
    tx_frame.msg_type = MSG_UNCONFIRMED_UPLINK;
    tx_frame.dest_addr = Storage_Main_Read();
    tx_frame.source_addr = get_local_address();
    tx_frame.command = WARNING_UPLOAD_CMD;
    tx_frame.tx_data = data;
    tx_frame.tx_len = 2;
    radio_mainunit_command_send(&tx_frame);
}

void RF_Peak_Alarm_Enable(void)
{
    tx_format tx_frame = {0};
    uint8_t data[2] = {0x01,0x01};

    tx_frame.msg_ack = RT_TRUE;
    tx_frame.msg_type = MSG_UNCONFIRMED_UPLINK;
    tx_frame.dest_addr = Storage_Main_Read();
    tx_frame.source_addr = get_local_address();
    tx_frame.command = WARNING_UPLOAD_CMD;
    tx_frame.tx_data = data;
    tx_frame.tx_len = 2;
    radio_mainunit_command_send(&tx_frame);
}

void RF_Peak_Alarm_Disable(void)
{
    tx_format tx_frame = {0};
    uint8_t data[2] = {0x01,0x00};

    tx_frame.msg_ack = RT_TRUE;
    tx_frame.msg_type = MSG_UNCONFIRMED_UPLINK;
    tx_frame.dest_addr = Storage_Main_Read();
    tx_frame.source_addr = get_local_address();
    tx_frame.command = WARNING_UPLOAD_CMD;
    tx_frame.tx_data = data;
    tx_frame.tx_len = 2;
    radio_mainunit_command_send(&tx_frame);
}

void RF_HeartWithMain(void)
{
    uint8_t data[8] = {0};
    tx_format tx_frame = {0};

    data[0] = Get_Bat_Level();
    data[1] = Get_Warning_Status();

    tx_frame.msg_ack = RT_TRUE;
    tx_frame.msg_type = MSG_UNCONFIRMED_UPLINK;
    tx_frame.dest_addr = Storage_Main_Read();
    tx_frame.source_addr = get_local_address();
    tx_frame.command = HEART_UPLOAD_CMD;
    tx_frame.tx_data = data;
    tx_frame.tx_len = 2;
    tx_frame.parameter = 1;
    radio_mainunit_command_send(&tx_frame);
}
