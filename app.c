/**
 * EV3RT baseline
 */

#include "ev3api.h"
#include "app.h"

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

/**
 * @brief メインタスク エントリポイント
 * @detail EV3RT OSのMAIN_TASKエントリーポイント
 */
void main_task(intptr_t unused) {
	ev3_sensor_config(EV3_PORT_1, TOUCH_SENSOR);
	while(1) {
		if (ev3_button_is_pressed(LEFT_BUTTON)) {
			ev3_led_set_color(LED_RED);
		} else if (ev3_button_is_pressed(RIGHT_BUTTON)) {
			ev3_led_set_color(LED_GREEN);
		} else if (ev3_touch_sensor_is_pressed(EV3_PORT_1)) {
			ev3_led_set_color(LED_ORANGE);
		} else {
		//	ev3_led_set_color(LED_OFF);
		}
	tslp_tsk(10);
	}
}
