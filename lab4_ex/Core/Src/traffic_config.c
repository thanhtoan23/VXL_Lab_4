#include <traffic_config.h>

int set_buff=0;
int num_buffer=0;
int red_set = 0, gre_set = 0, yel_set = 0;
int display_index=0;

void fsm_traffic_config(){
	switch(status){
	case SET_INIT:
		HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(YEL1_GPIO_Port, YEL1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GRE1_GPIO_Port, GRE1_Pin, GPIO_PIN_RESET);

		HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(YEL2_GPIO_Port, YEL2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GRE2_GPIO_Port, GRE2_Pin, GPIO_PIN_RESET);

		status = MODE2;
		setTimer2(50);
		setTimer3(100);
		setTimer5(20);  // SỬA TỪ 25ms XUỐNG 20ms
		break;
	case MODE2:
		if(timer2_flag==1){
			HAL_GPIO_TogglePin(RED1_GPIO_Port, RED1_Pin);
			HAL_GPIO_TogglePin(RED2_GPIO_Port, RED2_Pin);
			setTimer2(50);
		}
		if(timer5_flag==1){
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin,  SET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin,  SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin,  SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin,  SET);

			switch(display_index){
			case 0:
				num_buffer = 0;
				displayDigit(num_buffer);
				HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin,  RESET);
				break;
			case 1:
				num_buffer = 2;
				displayDigit(num_buffer);
				HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin,  RESET);
				break;
			case 2:
				num_buffer = set_buff/10;
				displayDigit(num_buffer);
				HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin,  RESET);
				break;
			case 3:
				num_buffer = set_buff%10;
				displayDigit(num_buffer);
				HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin,  RESET);
				break;
			}
			display_index = (display_index + 1) % 4;
			setTimer5(20);  // SỬA TỪ 25ms XUỐNG 20ms
		}
		if(isButton1Press() == 1){
			HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, GPIO_PIN_RESET);
			set_buff=0;
			display_index=0;
			status = MODE3;
		}
		if(isButton2Press() ==1){
			set_buff+=1;
		}
		if(isButton3Press() ==1){
			red_set = set_buff;
			set_buff = 0;
		}
		break;
	case MODE3:
		if(timer2_flag==1){
			HAL_GPIO_TogglePin(YEL1_GPIO_Port, YEL1_Pin);
			HAL_GPIO_TogglePin(YEL2_GPIO_Port, YEL2_Pin);
			setTimer2(50);
		}
		if(timer5_flag==1){
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin,  SET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin,  SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin,  SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin,  SET);

			switch(display_index){
			case 0:
				num_buffer = 0;
				displayDigit(num_buffer);
				HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin,  RESET);
				break;
			case 1:
				num_buffer = 3;
				displayDigit(num_buffer);
				HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin,  RESET);
				break;
			case 2:
				num_buffer = set_buff/10;
				displayDigit(num_buffer);
				HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin,  RESET);
				break;
			case 3:
				num_buffer = set_buff%10;
				displayDigit(num_buffer);
				HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin,  RESET);
				break;
			}
			display_index = (display_index + 1) % 4;
			setTimer5(20);  // SỬA TỪ 25ms XUỐNG 20ms
		}
		if(isButton1Press() == 1){
			HAL_GPIO_WritePin(YEL1_GPIO_Port, YEL1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(YEL2_GPIO_Port, YEL2_Pin, GPIO_PIN_RESET);
			status = MODE4;
			set_buff=0;
			display_index=0;
		}
		if(isButton2Press() ==1){
			set_buff+=1;
		}
		if(isButton3Press() ==1){
			yel_set = set_buff;
			set_buff = 0;
		}
		break;
	case MODE4:
		if(timer2_flag==1){
			HAL_GPIO_TogglePin(GRE1_GPIO_Port, GRE1_Pin);
			HAL_GPIO_TogglePin(GRE2_GPIO_Port, GRE2_Pin);
			setTimer2(50);
		}
		if(timer5_flag==1){
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin,  SET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin,  SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin,  SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin,  SET);

			switch(display_index){
			case 0:
				num_buffer = 0;
				displayDigit(num_buffer);
				HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin,  RESET);
				break;
			case 1:
				num_buffer = 4;
				displayDigit(num_buffer);
				HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin,  RESET);
				break;
			case 2:
				num_buffer = set_buff/10;
				displayDigit(num_buffer);
				HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin,  RESET);
				break;
			case 3:
				num_buffer = set_buff%10;
				displayDigit(num_buffer);
				HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin,  RESET);
				break;
			}
			display_index = (display_index + 1) % 4;
			setTimer5(20);  // SỬA TỪ 25ms XUỐNG 20ms
		}
		if(isButton1Press() == 1){
			if(red_set == gre_set + yel_set){
				red_dur = red_set*100;
				yellow_dur = yel_set*100;
				green_dur = gre_set * 100;
			}
			HAL_GPIO_WritePin(GRE1_GPIO_Port, GRE1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GRE2_GPIO_Port, GRE2_Pin, GPIO_PIN_RESET);
			status = INIT;
			set_buff=0;
			display_index=0;
		}
		if(isButton2Press() ==1){
			set_buff+=1;
		}
		if(isButton3Press() ==1){
			gre_set = set_buff;
			set_buff = 0;
		}
		break;
	default:
		break;
	}
}
