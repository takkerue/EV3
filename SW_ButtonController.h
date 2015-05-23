#ifndef _SW_BUTTON_CONTROLLER_H_
#define _SW_BUTTON_CONTROLLER_H_

#include "common.h"

typedef enum {
	StartButton = 0,
	ResetButton,
	NumOfButton
} StopWatchButton;

void SW_Button_init();
void SW_Button_update();
bool SW_Button_isPressed(StopWatchButton id);
bool SW_Button_isChanged(StopWatchButton id);
void SW_Button_setOnChangedListener(void (*listener)(StopWatchButton));

#endif
