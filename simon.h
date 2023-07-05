/*
 * simon.h
 *
 *  Created on: Mar 7, 2023
 *      Author: malik
 */

#ifndef SRC_SIMON_H_
#define SRC_SIMON_H_


#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

#define OUTPUT true
#define INPUT false
#define OFF 0
#define ON 1
#define MAX_STEPS 10

#define GREEN GPIO_PIN_0
#define BLUE GPIO_PIN_1
#define YELLOW GPIO_PIN_4
#define RED GPIO_PIN_6

#define BUTTON1 GPIO_PIN_8
#define BUTTON2 GPIO_PIN_10
#define BUTTON3 GPIO_PIN_4
#define BUTTON4 GPIO_PIN_5


#define BLUE_PRESSED 0
#define GREEN_PRESSED 1
#define RED_PRESSED 2
#define YELLOW_PRESSED 3
#define RESET_GAME 4
#define USER_WAIT 6


// clear terminal
#define clear() printf("\033[H\033[J") // clearing the serial terminal



void pattern_gen(int *steps, int *record);
void game(int *user_record, int *user_idx, int *user_steps, int *steps, int *record, bool *enable, int *score, int *high_score);
bool compare_arrays(int *arr1, int *arr2, int len);

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);


#endif /* SRC_SIMON_H_ */
