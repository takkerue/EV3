#include "ev3api.h"
#include "app.h"

// 内部関数プロトタイプ宣言
static void LcdClear(void);
static void LcdDrawStringAtLine(char *str, uint32_t line);
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

typedef enum {
	StopMode = 0,
	RunningMode,
	NumOfMode
} StopWatchMode;

void SW_main(void) {
    StopWatchMode mode = StopMode;
	unsigned int baseCount = 0;
	unsigned int startCount = 0;
	unsigned int currentCount = 0;

	ev3_sensor_config(EV3_PORT_1, TOUCH_SENSOR);

	ButtonState button[NumOfButton];
	button[StartButton].isPressed = ev3_touch_sensor_is_pressed(EV3_PORT_1);
	button[StartButton].wasPressed = button[StartButton].isPressed;
	button[ResetButton].isPressed = ev3_button_is_pressed(LEFT_BUTTON);
	button[ResetButton].wasPressed = button[ResetButton].isPressed;

	LcdClear();

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
		LcdDrawStringAtLine("TITLE", 0);
		LcdDrawStringAtLine("TEXT", 1);
		{
			char text[100];
			sprintf(text, "%d", currentCount);
			LcdDrawStringAtLine(text, 2);
		}
		tslp_tsk(10);
	}
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

/**
 * @brief LCD表示内容のクリア
 */
static void LcdClear(void) {
	ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE); // Clear menu area
	return;
}

/**
 * @brief LCDのline行分改行した位置に文字列表示
 */
static void LcdDrawStringAtLine(char *str, uint32_t line) {
	int32_t fontHeight = 0;
	int32_t fontWidth = 0;
	ev3_lcd_set_font(EV3_FONT_MEDIUM);
	ev3_font_get_size(EV3_FONT_MEDIUM, &fontWidth, &fontHeight);
	ev3_lcd_draw_string(str, 0, (int32_t)(fontHeight * 1.5 * line));
	return;
}
