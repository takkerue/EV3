enum SW_ButtonType_E {
    StartButton = 0,
    ResetButton,
    NumOfButton
};

void SW_Button_init();
void SW_Button_update();
bool SW_Button_isPressed(SW_ButtonType_E id);
bool SW_Button_isChanged(SW_ButtonType_E id);
void SW_Button_setOnChangedListener(void (*listener)(SW_ButtonType_E));
