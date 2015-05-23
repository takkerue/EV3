#include "ev3api.h"

#include "SW_ButtonController.h"

typedef struct {
	unsigned char isPressed;
	unsigned char wasPressed;
} ButtonState;

ButtonState button[NumOfButton];

void SW_Button_init()
{
        button[StartButton].isPressed = ev3_touch_sensor_is_pressed(EV3_PORT_1);
	button[StartButton].wasPressed = button[StartButton].isPressed;
	button[ResetButton].isPressed = ev3_button_is_pressed(LEFT_BUTTON);
	button[ResetButton].wasPressed = button[ResetButton].isPressed;
        return;
}

void SW_Button_update()
{
        button[StartButton].wasPressed = button[StartButton].isPressed;
        button[StartButton].isPressed = ev3_touch_sensor_is_pressed(EV3_PORT_1);
        button[ResetButton].wasPressed = button[ResetButton].isPressed;
        button[ResetButton].isPressed = ev3_button_is_pressed(LEFT_BUTTON);

        return;
}

bool SW_Button_isPressed(StopWatchButton id)
{
        if (id >= NumOfButton) {
                return false;
        }
        return button[id].isPressed;
}

bool SW_Button_isChanged(StopWatchButton id)
{
        if (id >= NumOfButton) {
                return false;
        }
        return (button[id].isPressed != button[id].wasPressed);
}

void SW_Button_setOnChangedListener(void (*listener)(StopWatchButton))
{
    return;
}
