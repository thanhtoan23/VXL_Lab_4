#include "button.h"

int button1_flag = 0;
int button2_flag = 0;
int button3_flag = 0;

int KeyReg0 = NORMAL_STATE;
int KeyReg1 = NORMAL_STATE;
int KeyReg2 = NORMAL_STATE;

int KeyReg3 = NORMAL_STATE;

int KeyReg4 = NORMAL_STATE;
int KeyReg5 = NORMAL_STATE;
int KeyReg6 = NORMAL_STATE;

int KeyReg7 = NORMAL_STATE;

int KeyReg8 = NORMAL_STATE;
int KeyReg9 = NORMAL_STATE;
int KeyReg10 = NORMAL_STATE;

int KeyReg11 = NORMAL_STATE;

int TimerKeyPress = 200;
int TimerKeyPress_2 = 200;
int TimerKeyPress_3 = 200;

int isButton1Press(){
	if(button1_flag==1){
		button1_flag = 0;
		return 1;
	}
	return 0;
}
int isButton2Press(){
	if(button2_flag==1){
		button2_flag = 0;
		return 1;
	}
	return 0;
}
int isButton3Press(){
	if(button3_flag==1){
		button3_flag = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess(){
	button1_flag = 1;
}
void subKeyProcess_2(){
	button2_flag = 1;
}
void subKeyProcess_3(){
	button3_flag = 1;
}

void getKeyInput(){
	KeyReg0 = KeyReg1;
	KeyReg1 = KeyReg2;
	KeyReg2 = HAL_GPIO_ReadPin(BUT1_GPIO_Port, BUT1_Pin);
	if((KeyReg0 == KeyReg1) && (KeyReg1 == KeyReg2)){
		if(KeyReg3 != KeyReg2){
			KeyReg3 = KeyReg2;
			if(KeyReg2 == PRESSED_STATE){
				//TODO
				subKeyProcess();
				TimerKeyPress = 50;
			}
		}
		else{
			TimerKeyPress--;
			if(TimerKeyPress == 0){
				KeyReg3 = NORMAL_STATE;
			}
		}
	}
}

void getKeyInput_2(){
	KeyReg4 = KeyReg5;
	KeyReg5 = KeyReg6;
	KeyReg6 = HAL_GPIO_ReadPin(BUT2_GPIO_Port, BUT2_Pin);
	if((KeyReg4 == KeyReg5) && (KeyReg5 == KeyReg6)){
		if(KeyReg7 != KeyReg6){
			KeyReg7 = KeyReg6;
			if(KeyReg6 == PRESSED_STATE){
				//TODO
				subKeyProcess_2();
				TimerKeyPress_2 = 50;
			}
		}
		else{
			TimerKeyPress_2--;
			if(TimerKeyPress_2 == 0){
				KeyReg7 = NORMAL_STATE;
			}
		}
	}
}
void getKeyInput_3(){
	KeyReg8 = KeyReg9;
	KeyReg9 = KeyReg10;
	KeyReg10 = HAL_GPIO_ReadPin(BUT3_GPIO_Port, BUT3_Pin);
	if((KeyReg8 == KeyReg9) && (KeyReg9 == KeyReg10)){
		if(KeyReg11 != KeyReg10){
			KeyReg11 = KeyReg10;
			if(KeyReg10 == PRESSED_STATE){
				//TODO
				subKeyProcess_3();
				TimerKeyPress_3 = 50;
			}
		}
		else{
			TimerKeyPress_3--;
			if(TimerKeyPress_3 == 0){
				KeyReg11 = NORMAL_STATE;
			}
		}
	}
}
