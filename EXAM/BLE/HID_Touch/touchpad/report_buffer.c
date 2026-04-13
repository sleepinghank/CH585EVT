/* Copyright 2023 @ lokher (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "report_buffer.h"
#include "PMU.h"
#include <string.h>
#include "timer.h"
#include "debug.h"
#include "gpio.h"
/* The report buffer is mainly used to fix key press lost issue of macro
 * when wireless module fifo isn't large enough. The maximun macro
 * string length is determined by this queue size, and should be
 * REPORT_BUFFER_QUEUE_SIZE devided by 2 since each character is implemented
 * by sending a key pressing then a key releasing report.
 * Please note that it cosume sizeof(report_buffer_t)  * REPORT_BUFFER_QUEUE_SIZE
 * bytes RAM, with default setting, used RAM size is
 *        sizeof(report_buffer_t) * 256 = 34* 256  =  8704 bytes
 */
#ifndef REPORT_BUFFER_QUEUE_SIZE
#    define REPORT_BUFFER_QUEUE_SIZE 64
#endif

/* BLE 驱动层忙态返回值，与 CH58xBLE_LIB.h 中 blePending(0x16) 对齐 */
#define SEND_STATUS_BLE_PENDING  0x16

extern wt_func_t wireless_transport;

/* report_interval value should be less than bluetooth connection interval because
 * it takes some time for communicating between mcu and bluetooth module. Carefully
 * set this value to feed the bt module so that we don't lost the key report nor lost
 * the anchor point of bluetooth interval. The bluetooth connection interval varies
 * if BLE is used, invoke report_buffer_set_inverval() to update the value
 */
uint8_t report_interval = DEFAULT_BLE_REPORT_INVERVAL_MS;

static uint32_t report_timer_buffer = 0;
uint32_t        retry_time_buffer   = 0;
report_buffer_t report_buffer_queue[REPORT_BUFFER_QUEUE_SIZE];
uint16_t        report_buffer_queue_head;
uint16_t        report_buffer_queue_tail;
report_buffer_t kb_rpt;
int8_t         retry = -1; // -1 表示未进入重试状态，非负值表示剩余重试次数
uint8_t sended_buf_len = 0; // 已发送长度
uint8_t can_send_len    = BLE_BUFF_NUM; // 本轮可发送长度，默认为0xff
// static report_buffer_t latest_touch_report;   // 触控板最新报文（不入队）
// static bool            has_new_touch_report;   // 是否有新触控板报文待发送

uint8_t bt_driver_send_ptp(uint8_t *report, uint8_t len)
{
    uint8_t ret = HidDev_Report(HID_RPT_ID_TOUCHPAD_IN, HID_REPORT_TYPE_INPUT,
                                len, report);
    if (ret != 0) {
        LOG_E("[BT] send_ptp fail, ret=%d,len=%d", ret, len);
    }
    return ret;
}


void report_buffer_init(void) {
    // Initialise the report queue
    memset(&report_buffer_queue, 0, sizeof(report_buffer_queue));
    report_buffer_queue_head = 0;
    report_buffer_queue_tail = 0;
    memset(&kb_rpt, 0, sizeof(kb_rpt));
    retry                    = -1;
    sended_buf_len = 0;
    can_send_len    = BLE_BUFF_NUM;
    // memset(&latest_touch_report, 0, sizeof(latest_touch_report));
    // has_new_touch_report = false;
    // retry_time_buffer        = 0;
    // report_timer_buffer      = timer_read32();
}

bool report_buffer_enqueue(report_buffer_t *report) {
    // 触控板报文：存入最新值变量，不入队
    // if (report->type == REPORT_TYPE_PTP || report->type == REPORT_TYPE_MOUSE) {
    //     latest_touch_report  = *report;
    //     has_new_touch_report = true;
    //     return true;
    // }

    // 其他报文：正常入队
    uint16_t next = (report_buffer_queue_head + 1) % REPORT_BUFFER_QUEUE_SIZE;
    if (next == report_buffer_queue_tail) {
        return false;
    }

    report_buffer_queue[report_buffer_queue_head] = *report;
    report_buffer_queue_head                      = next;
    return true;
}

inline bool report_buffer_dequeue(report_buffer_t *report) {
    if (report_buffer_queue_head == report_buffer_queue_tail) {
        return false;
    }

    *report                  = report_buffer_queue[report_buffer_queue_tail];
    report_buffer_queue_tail = (report_buffer_queue_tail + 1) % REPORT_BUFFER_QUEUE_SIZE;
    return true;
}

// bool report_buffer_dequeue_latest(report_buffer_t *report) {
//     if (!has_new_touch_report) {
//         return false;
//     }
//     *report              = latest_touch_report;
//     has_new_touch_report = false;
//     return true;
// }

bool report_buffer_is_empty() {
    return report_buffer_queue_head == report_buffer_queue_tail;
}

// void report_buffer_update_timer(void) {
//     report_timer_buffer = timer_read32();
// }

// bool report_buffer_next_inverval(void) {
//     return timer_elapsed32(report_timer_buffer) > report_interval;
// }

// void report_buffer_set_inverval(uint8_t interval) {
//     // OG_TRACE("report_buffer_set_inverval: %d\n\r", interval);
//     report_interval = interval;
// }

// uint8_t report_buffer_get_retry(void) {
//     return retry;
// }

// void report_buffer_set_retry(uint8_t times) {
//     retry = times;
// }


uint8_t report_buffer_send(){
    uint8_t send_status = 0; // 默认错误状态

    if (kb_rpt.type == REPORT_TYPE_PTP ) {
        LOG_I("1");
        send_status = bt_driver_send_ptp((uint8_t *)&kb_rpt.ptp, kb_rpt.payload_len);
    }

    return send_status;
}


bool report_buffer_task(void) {
    if (wireless_get_state() != WT_CONNECTED) return false;
    bool pending_data = false;
    // 当前缓存中有数据，并且可发送长度未满载时，继续发送剩余数据
    if ( can_send_len >0){
        if (retry > 0){
            --retry;
            // 重试，直接发上次的包
            pending_data = true;
        } else if (!report_buffer_is_empty() && retry == -1){
            // 没有重试，取出下一条新报文
            if (report_buffer_dequeue(&kb_rpt) && kb_rpt.type != REPORT_TYPE_NONE) {
                pending_data = true;
            }
        }
        // } else if ((has_new_touch_report || !report_buffer_is_empty()) && retry == -1){
        //     // 优先取触控板最新值，再从队列取
        //     if (report_buffer_dequeue_latest(&kb_rpt)) {
        //         pending_data = true;
        //     } else if (report_buffer_dequeue(&kb_rpt) && kb_rpt.type != REPORT_TYPE_NONE) {
        //         pending_data = true;
        //     }
        // }
    }
    if (pending_data) {
        uint8_t send_status = report_buffer_send();
        if (send_status == 0) {
            // writePinHigh(A8);
            // 发送成功，更新已发送长度和可发送长度
            sended_buf_len ++;
            if (can_send_len > 0){
                can_send_len --;
            }
            retry           = -1; // 重置重试计数
        } else if (send_status == SEND_STATUS_BLE_PENDING) {
            LOG_I("BLE pending, retry later");
            can_send_len = 0; // 蓝牙模块忙，暂时不可发送新报文
            // 蓝牙模块忙，保持当前状态等待重试
            retry = (retry == -1) ? RETPORT_RETRY_COUNT : retry; // 首次进入重试状态时设置重试次数
        } else {
            // 其他错误，进入重试流程
            retry = (retry == -1) ? RETPORT_RETRY_COUNT : retry; // 首次进入重试状态时设置重试次数
        }
        if (retry == 0) {
            // 重试次数耗尽，丢弃当前报文
            retry = -1; // 重置重试状态
            memset(&kb_rpt, 0, sizeof(kb_rpt)); // 清空当前报文
            can_send_len = 0x08; // 恢复默认可发送长度
        }
    }
    return pending_data;
}

bool report_buffer_waiting_send(void) {
    //if (has_new_touch_report) return true;
    if (!report_buffer_is_empty() || retry > 0) return true;
    return false;
}

uint8_t report_buffer_delete_pending(void) {
    if (wireless_get_state() != WT_CONNECTED) return 0;
    uint8_t UnAckPacket = 0;
    if (wireless_transport.get_unack_packets){
        UnAckPacket = wireless_transport.get_unack_packets();
        if (UnAckPacket == 0) {
            // 没有未确认的报文，重置发送状态
            sended_buf_len = 0;
            can_send_len = BLE_BUFF_NUM; // 恢复默认可发送长度
        } else {
            if (UnAckPacket < sended_buf_len) {
                uint8_t to_delete = sended_buf_len - UnAckPacket;
                sended_buf_len -= to_delete;
                can_send_len = to_delete; // 更新可发送长度以触发后续发送
            }
        }
    }   
    LOG_I("UnAck=%d", UnAckPacket);
    return UnAckPacket; // 没有在途报文可删除
}

