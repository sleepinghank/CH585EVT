#pragma once

#include <stdbool.h>
#include <stdint.h>

extern uint8_t touchpad_taskID;

/* middleware/touchpad 内部事件 */
#define TOUCHPAD_INIT_EVT        (1 << 0)  // 触控板初始化事件
#define TOUCHPAD_DATA_EVT        (1 << 1)  // 触控数据处理事件
#define TOUCHPAD_REG_INIT_EVT    (1 << 2)  // 触控寄存器事件
#define TOUCHPAD_KB_BREAK_EVT    (1 << 3)  // 键盘打字隔离到期事件
#define TOUCHPAD_OFF_EVT         (1 << 4)  // 触控板关闭事件
/* 报告缓冲发送事件 */
#define REPORT_SEND_EVT            (1 << 7)   // 报告缓冲区有数据待发送
#define REPORT_DELETE_PAK_EVT      (1 << 8)   // 报告缓冲区有数据待删除
#define REPORT_CLEAR_EVT            (1 << 9)   // 报告缓冲区清空事件


#define TOUCHPAD_SDA          B20  /* PB20_SDA - U2.28 */
#define TOUCHPAD_SCL          B21  /* PB21_SCL - U2.29 */
#define TOUCHPAD_INT          A3   /* PA3_INT - 下降沿触发 - U2.42 */

#define TOUCHPAD_POWER_PIN        A11  /* PA11 - 供电控制 - U2.44 */
#define TOUCHPAD_BUTTON_PIN       A10  /* PA10  */

/* ========== 触控板尺寸 ========== */
#define TOUCHPAD_MAX_X        1728
#define TOUCHPAD_MAX_Y        944
// 按键单指拖动保持开关
// #define HOLD_BUTTON
// 按下双击转换为右键开关
// #define DOUBLE_CLICK_TO_RIGHT_BUTTON
// 预设手势开关
// #define MCS_GESTURE
// 边缘防误触开关
#define EDGE_MISTOUCH
// 贝叶斯防误触开关
#define BAYES_MISTOUCH
// 贝叶斯防抖周期
#define BAYES_DEBOUNCE_CYCLE						2 
#define	TP_MAX_CONTACT_COUNT							4 // 最大总触摸点数

typedef struct{
#ifdef MOUSE_SHARED_EP
    uint8_t report_id;
#endif
	uint8_t button;
	uint8_t x_l8:8;
	uint8_t x_m4:4; 
	uint8_t y_l4:4;	
	uint8_t y_m8:8;	
	uint8_t wheel;
	uint8_t twheel;
} PACKED report_mouse_t;

typedef struct{
#ifdef DIGITIZER_SHARED_EP
    uint8_t report_id;
#endif
	uint8_t scantime_l8;
	uint8_t scantime_m8;
    uint8_t button:1;
    uint8_t button1:1;
    uint8_t button2:1;
    uint8_t Reserved:5;
	contact_report_t contact_rpt[TP_MAX_CONTACT_COUNT];
	uint8_t contactCnt;
} PACKED report_ptp_t;

/* 注册 touchpad middleware 的独立 OSAL 任务。 */
void touchpad_setup(void);

/* 直接执行上电路径，并启动 middleware 初始化状态机。 */
void touchpad_power_on(void);

/* 关闭触控板，并清理 middleware 侧的初始化定时事件。 */
void touchpad_power_off(void);

/* 将 input_service 的 GPIO 中断转发为 touchpad 数据事件。 */
void touchpad_notify_int(void);

/* 主循环轮询处理触控板数据，由 peripheral_process 调用。 */
void touchpad_task(void);

/* 设置键盘打字后触控板抑制时间，单位毫秒。 */
void touchpad_set_kb_break(uint16_t ms);

/* 停止 touchpad middleware 已投递的待处理事件。 */
void touchpad_stop_all_events(void);

/* 执行看门狗检查，必要时重走触控板初始化流程。 */
void touchpad_watchdog_check(void);

/* 对外暴露触控板模式切换，底层仍由 touch_component 实现。 */
void touchpad_set_mode(uint8_t mode);
