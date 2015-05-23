#include "ev3api.h"
#include "app.h"

#include "SW_main.h"
#include "SW_DisplayView.h"	//TODO remove
#include "SW_ButtonController.h"

// 内部関数プロトタイプ宣言
static int ClockGetTime();

static unsigned int currentCount = 0;
static StopWatchMode mode = StopMode;

void SW_main(void) {
	unsigned int baseCount = 0;
	unsigned int startCount = 0;
	ev3_sensor_config(EV3_PORT_1, TOUCH_SENSOR);
	SW_Button_init();//TODO remove
	while(1) {
		SW_Button_update();//TODO remove
		if (SW_Button_isPressed(StartButton) && SW_Button_isChanged(StartButton)) {
			switch (mode) {
			case StopMode:
				mode = RunningMode;
				startCount = ClockGetTime();
				break;
			case RunningMode:
				mode = StopMode;
				baseCount = baseCount + ClockGetTime() - startCount;
				break;
			default:
				mode = StopMode;
				break;
			}
		}
		if (SW_Button_isPressed(ResetButton) && SW_Button_isChanged(ResetButton)) {
				mode = StopMode;
				baseCount = 0;
				startCount = 0;
		}

		switch (mode) {
		case StopMode:
			currentCount = baseCount;
			break;
		case RunningMode:
			currentCount = ClockGetTime() - startCount + baseCount;
			break;
		default:
			currentCount = 0;
			break;
		}

		if (ev3_button_is_pressed(LEFT_BUTTON)) {
			ev3_led_set_color(LED_RED);
		} else if (ev3_button_is_pressed(RIGHT_BUTTON)) {
			ev3_led_set_color(LED_GREEN);
		} else if (ev3_touch_sensor_is_pressed(EV3_PORT_1)) {
			ev3_led_set_color(LED_ORANGE);
		} else {
			ev3_led_set_color(LED_OFF);
		}
		SW_DisplayView_update();//TODO remove

		tslp_tsk(10);
	}
}

/**
 * @brief ストップウォッチ計測時間の取得
 * @return 計測時間[ms]
 */
unsigned int SW_currentTimeMs(void)
{
	return currentCount;
}

/**
 * @brief ストップウォッチのモードの取得
 * @return モード
 */
StopWatchMode SW_mode(void)
{
	return mode;
}

/**
 * @brief ストップウォッチ計測時間の取得
 * @return 計測時間[ms]
 */
StopWatchMode SW_currentMode(void)
{
	return mode;
}
/**
 * @brief タイマカウンタの取得
 * @return タイマカウンタ[ms]
 */
static int ClockGetTime()
{
	SYSTIM count;
	get_tim(&count);
	return (int)count;
}
