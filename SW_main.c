#include "ev3api.h"
#include "app.h"

#include "SW_main.h"
#include "SW_DisplayView.h"

// 内部関数プロトタイプ宣言
static int ClockGetTime();

typedef struct {
	unsigned char isPressed;
	unsigned char wasPressed;
} ButtonState;

typedef enum {
	StartButton = 0,
	ResetButton,
	NumOfButton
} StopWatchButton;

static unsigned int currentCount = 0;
static StopWatchMode mode = StopMode;

void SW_main(void) {
	unsigned int baseCount = 0;
	unsigned int startCount = 0;
	ev3_sensor_config(EV3_PORT_1, TOUCH_SENSOR);

	ButtonState button[NumOfButton];
	button[StartButton].isPressed = ev3_touch_sensor_is_pressed(EV3_PORT_1);
	button[StartButton].wasPressed = button[StartButton].isPressed;
	button[ResetButton].isPressed = ev3_button_is_pressed(LEFT_BUTTON);
	button[ResetButton].wasPressed = button[ResetButton].isPressed;

	while(1) {
		button[StartButton].wasPressed = button[StartButton].isPressed;
		button[StartButton].isPressed = ev3_touch_sensor_is_pressed(EV3_PORT_1);
		button[ResetButton].wasPressed = button[ResetButton].isPressed;
		button[ResetButton].isPressed = ev3_button_is_pressed(LEFT_BUTTON);
		if (	(button[StartButton].isPressed) &&
			(button[StartButton].isPressed != button[StartButton].wasPressed)) {
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
		if (	(button[ResetButton].isPressed) &&
			(button[ResetButton].isPressed != button[StartButton].wasPressed)) {
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
		SW_DisplayView_update();

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
