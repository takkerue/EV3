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

// 内部関数プロトタイプ宣言
static void LcdClear(void);
static void LcdDrawStringAtLine(char *str, uint32_t line);
static int ClockGetTime();
static void ClockReset();

/**
 * @brief メインタスク エントリポイント
 * @detail EV3RT OSのMAIN_TASKエントリーポイント
 */
void main_task(intptr_t unused) {
	ev3_sensor_config(EV3_PORT_1, TOUCH_SENSOR);

	LcdClear();
	while(1) {
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
		sprintf(text, "%d", ClockGetTime());
		LcdDrawStringAtLine(text, 2);
	}
	tslp_tsk(10);
	}
}

static int clockCount = 0;

/**
 * @bried クロック計数周期ハンドラのエントリポイント
 * @note 1ms周期でカウントアップ
 * @param 周期ハンドラID
 */
void clock_cychdr(intptr_t idx) {
	++clockCount;
	return;
}

/**
 * @brief タイマカウンタの取得
 * @return タイマカウンタ[ms]
 */
static int ClockGetTime()
{
	return clockCount;
}

/**
 * @brief タイマカウンタのリセット
 */
static void ClockReset()
{
	clockCount = 0;
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
