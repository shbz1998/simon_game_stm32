/*
 * simon.c
 *
 *  Created on: Mar 7, 2023
 *      Author: malik
 */
#include <stdio.h>
#include "simon.h"


volatile uint status = USER_WAIT;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    static uint32_t last_interrupt_time = 0;
    uint32_t current_time = HAL_GetTick();

    if (current_time - last_interrupt_time > 150) { // 150ms debounce time
        if(GPIO_Pin == B1_Pin){
            HAL_GPIO_TogglePin(GPIOA, BLUE);
            HAL_Delay(10);
            HAL_GPIO_TogglePin(GPIOA, BLUE);
            status = BLUE_PRESSED; //BLUE

        }

        else if(GPIO_Pin == BUTTON1){
            HAL_GPIO_TogglePin(GPIOA, GREEN);
            HAL_Delay(10);
            HAL_GPIO_TogglePin(GPIOA, GREEN);
            status = GREEN_PRESSED; //GREEN

        }

        else if(GPIO_Pin == BUTTON2){
            HAL_GPIO_TogglePin(GPIOA, RED);
            HAL_Delay(10);
            HAL_GPIO_TogglePin(GPIOA, RED);
            status = RED_PRESSED; //RED

        }

        else if(GPIO_Pin == BUTTON3){
            HAL_GPIO_TogglePin(GPIOA, YELLOW);
            HAL_Delay(10);
            HAL_GPIO_TogglePin(GPIOA, YELLOW);
            status = YELLOW_PRESSED; //YELLOW

        }

        else if(GPIO_Pin == BUTTON4){
            status = RESET_GAME; //RESET

        }
        last_interrupt_time = current_time;
    }
}




void pattern_gen(int *steps, int *record) {
    uint32_t pin_num[] = {RED, GREEN, YELLOW, BLUE};

    for (int i = 0; i < *steps; i++) {
        uint32_t idx = rand() % 4;
        uint32_t pin = pin_num[idx];

        HAL_GPIO_WritePin(GPIOA, RED | GREEN | YELLOW | BLUE, GPIO_PIN_RESET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(GPIOA, pin, GPIO_PIN_SET);
        record[i] = pin;
        HAL_Delay(800);
    }

    HAL_GPIO_WritePin(GPIOA, RED | GREEN | YELLOW | BLUE, GPIO_PIN_RESET);
}


void game(int *user_record, int *user_idx, int *user_steps, int *steps, int *record, bool *enable, int *score, int *high_score) {
  clear();

  printf("SCORE: %d\r\n", *score);
  printf("HIGHSCORE: %d\r\n", *high_score);

  if(*score == MAX_STEPS){
	  printf("Congrats you have won!\r\n");
	  HAL_Delay(500);
	  *user_idx = 0;
	  *user_steps = 0;
	  *score = 0;
	  *steps = 1;
	  *enable = true;
	  *high_score = MAX_STEPS;
  }

  if (*enable) { // generate pattern
    pattern_gen(steps, record);
    *enable = false;
  }

  else { // user turn
	  HAL_GPIO_WritePin(GPIOA, RED, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOA, GREEN, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOA, YELLOW, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOA, BLUE, GPIO_PIN_RESET);

    if (*user_steps == *steps) { // compare

      if (compare_arrays(record, user_record, *steps)) {
        ++(*score);
        ++(*steps);
      } else {
    	if(*score > *high_score){
    		*high_score = *score;
    	}
        *score = 0;
        *steps = 1;
        printf("WRONG!\r\n");
        HAL_Delay(1000);
      }
      *enable = true;
      HAL_Delay(300);
      *user_idx = 0;
      *user_steps = 0;
    }

    else{
    	if(status == BLUE_PRESSED){
            if(*user_idx > MAX_STEPS - 1){
            	*user_idx = 0;
            }
            user_record[(*user_idx)++] = BLUE;
            ++(*user_steps);
            printf("PRESSED: %d \r\n", *user_steps);
            status = 6;
    	}

    	else if (status == GREEN_PRESSED){
            if(*user_idx > MAX_STEPS - 1){
            	*user_idx = 0;
            }
            user_record[(*user_idx)++] = GREEN;
            ++(*user_steps);
            printf("PRESSED: %d \r\n", *user_steps);
            status = 6;
    	}

    	else if(status == RED_PRESSED){
            if(*user_idx > MAX_STEPS - 1){
            	*user_idx = 0;
            }
            user_record[(*user_idx)++] = RED;
            ++(*user_steps);
            printf("PRESSED: %d \r\n", *user_steps);
            status = 6;
    	}

    	else if(status == YELLOW_PRESSED){
            if(*user_idx > MAX_STEPS - 1){
            	*user_idx = 0;
            }
            user_record[(*user_idx)++] = YELLOW;
            ++(*user_steps);
            printf("PRESSED: %d \r\n", *user_steps);
            status = 6;
    	}

    	else if(status == RESET_GAME){
    		*user_idx = 0;
    		*user_steps = 0;
    		*score = 0;
    		*steps = 1;
    		*enable = true;
    		*high_score = 0;

    		printf("GAME RESET!\r\n");
    		HAL_Delay(500);
    		clear();

    		status = 6;
    	}

    	else {
    		printf("USER TURN!\r\n");
    		HAL_Delay(500);
    		clear();
    	}
    	}
    }
}



bool compare_arrays(int *arr1, int *arr2, int len) {
  for (int i = 0; i < len; i++) {
    if (arr1[i] != arr2[i]) {
      return false;
    }
  }
  return true;
}



