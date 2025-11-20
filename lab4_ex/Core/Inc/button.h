#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define NORMAL_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET

int isButton1Press();
int isButton2Press();
int isButton3Press();
void getKeyInput();
void getKeyInput_2();
void getKeyInput_3();

#endif /* INC_BUTTON_H_ */
