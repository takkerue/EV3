#include "ev3api.h"
#include "SW_DisplayView.h"
#include "SW_main.h"

static void LcdClear(void);
static void LcdDrawStringAtLine(const char *str, const uint32_t line);

static int refreshCount = 0;

void SW_DisplayView_update()
{
        if (refreshCount >= 10) {
                refreshCount = 0;
                LcdClear();
        } else {
                ++refreshCount;
        }

        LcdDrawStringAtLine("STOP WATCH", 0);
        {
                const char *modeTaxts[NumOfMode] = {"STOP", "RUNNING" };
                LcdDrawStringAtLine(modeTaxts[SW_mode()], 1);
        }
        {
                char text[100];
                int currentCount = SW_currentTimeMs();
                int displayCount;
                if (currentCount > 999999999) {
                        displayCount = 999999999;
                } else {
                        displayCount = currentCount;
                }
                sprintf(text, "%6d.%03d", displayCount / 1000, displayCount % 1000);
                LcdDrawStringAtLine(text, 2);
        }
        return;
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
static void LcdDrawStringAtLine(const char *str, const uint32_t line) {
	int32_t fontHeight = 0;
	int32_t fontWidth = 0;
	ev3_lcd_set_font(EV3_FONT_MEDIUM);
	ev3_font_get_size(EV3_FONT_MEDIUM, &fontWidth, &fontHeight);
	ev3_lcd_draw_string(str, 0, (int32_t)(fontHeight * 1.5 * line));
	return;
}
