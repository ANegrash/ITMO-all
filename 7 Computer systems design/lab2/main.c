/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdbool.h"
#include "math.h"
#include "stddef.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

char letters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int morse[] = {22222, 12222, 11222, 11122, 11112, 11111, 21111, 22111, 22211, 22221, 12, 2111, 2121, 211, 1, 1121, 221, 1111, 11, 1222, 212, 1211, 22, 21, 222, 1221, 2212, 121, 111, 2, 112, 1112, 122, 2112, 2122, 2211};
_Bool isUseInterrupts = false;

char buffer[8];
int bufferGetPosition = 0;
int bufferAddPosition = 0;

_Bool isPressed() { return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15) == GPIO_PIN_RESET; }

_Bool isNotPressed() { return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15) == GPIO_PIN_SET; }

_Bool isBufferEmpty() { return (buffer[0] == 0 && buffer[1] == 0 && buffer[2] == 0 && buffer[3] == 0 && buffer[4] == 0 && buffer[5] == 0 && buffer[6] == 0 && buffer[7] == 0); }

_Bool isBufferFull() { return (buffer[0] != 0 && buffer[1] != 0  && buffer[2] != 0 && buffer[3] != 0 && buffer[4] != 0 && buffer[5] != 0 && buffer[6] != 0 && buffer[7] != 0); }

void turnOn() {
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
}

void turnOff() {
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
}

void addToBuffer(char s) {
	buffer[bufferAddPosition] = s;
	bufferAddPosition++;
	if (bufferAddPosition > 7) {
		bufferAddPosition = 0;
	}
}

char getCharFromBuffer() {
	char toReturn = buffer[bufferGetPosition];
	buffer[bufferGetPosition] = 0;
	bufferGetPosition++;
	if (bufferGetPosition > 7) {
		bufferGetPosition = 0;
	}
	return toReturn;
}

int getMorseCode(char s) {
	int position = -1;
	for (int i = 0; i < sizeof(letters); i++) {
		if (s == letters[i]) {
			position = i;
			break;
		}
	}
	if (position >= 0) {
		return morse[position];
	} else {
		return position;
	}
}

char getCharByMorseCode(int s) {
	int position = -1;
	for (int i = 0; i < sizeof(morse); i++) {
		if (s == morse[i]) {
			position = i;
			break;
		}
	}
	if (position >= 0) {
		return letters[position];
	} else {
		return '-';
	}
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART6_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    char recieved, current, toSend[2];
    int currentMorse = -1;
    int morseTen = 5;
    int btnMorse = 0;
    int btnCounter = 0;
    _Bool isLightOn = false;
    _Bool isPause = false;
    _Bool isBtnPressed = false;
    _Bool isBtnPause = false;
    uint32_t blinkStartTime, pauseStartTime, diffLO, diffPause, btnStart, btnDiff, btnPauseStart, btnPauseDiff;
    int blinkingMode;
    char err[] = "Unsupported symbol by button \n";
    char intOn[] = "Interrupts turned On\n";
    char intOff[] = "Interrupts turned Off\n";

	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		if (!isUseInterrupts) {
			//No Interrupts
			if (HAL_OK == HAL_UART_Receive(&huart6, (uint8_t *) &recieved, 1, 1)) {
				char toret[2];
				toret[0] = recieved;
				toret[1] = '\n';
				HAL_UART_Transmit(&huart6, (uint8_t *) toret, 2, 10);
				if (recieved == '+') {
					isUseInterrupts = true;
					HAL_UART_Transmit(&huart6, (uint8_t *) intOn, sizeof(intOn), 10);
					HAL_NVIC_EnableIRQ(USART6_IRQn);
					uart6_start_recieve_char_it();
					continue;
				}

				if (!isBufferFull()) {
					addToBuffer(recieved);
				}
			}

			if (!isLightOn && !isPause) {
				if (!isBufferEmpty() && currentMorse < 0) {
					current = getCharFromBuffer();
					currentMorse = getMorseCode(current);
				}

				if (currentMorse >= 0) {
					blinkingMode = currentMorse / pow(10, morseTen);
					currentMorse = currentMorse % (int)pow(10, morseTen);
					morseTen--;
					if (morseTen == -1) {
						morseTen = 5;
						currentMorse = -1;
					}

					if (blinkingMode > 0) {
						blinkStartTime = HAL_GetTick();
						turnOn();
						isLightOn = true;
					}

				}
			}

			if (isLightOn) {
				diffLO = HAL_GetTick() - blinkStartTime;
				if (blinkingMode == 1) {
					if (diffLO >= 300) {
						turnOff();
						pauseStartTime = HAL_GetTick();
						isLightOn = false;
						isPause = true;
					}
				} else if (blinkingMode == 2) {
					if (diffLO >= 700) {
						turnOff();
						pauseStartTime = HAL_GetTick();
						isLightOn = false;
						isPause = true;
					}
				}
			}

			if (isPause) {
				diffPause = HAL_GetTick() - pauseStartTime;
				if (diffPause >= 300) {
					isPause = false;
				}
			}

			if (!isBtnPressed) {
				if (isPressed()) {
					isBtnPressed = true;
					isBtnPause = false;
					btnStart = HAL_GetTick();
				}
			}

			if (isBtnPressed) {
				if (isNotPressed()) {
					isBtnPressed = false;
					isBtnPause = true;
					btnDiff = HAL_GetTick() - btnStart;
					btnPauseStart = HAL_GetTick();

					if (btnDiff >= 100) {
						if (btnDiff < 500) {
							btnMorse = btnMorse * 10 + 1;
							btnCounter++;
						} else {
							btnMorse = btnMorse * 10 + 2;
							btnCounter++;
						}
					}
				}
			}

			if (isBtnPause) {
				if (isNotPressed()) {
					btnPauseDiff = HAL_GetTick() - btnPauseStart;

					if (btnPauseDiff > 1000) {
						toSend[0] = getCharByMorseCode(btnMorse);
						if (toSend[0] == '-') {
							HAL_UART_Transmit(&huart6, (uint8_t *) err, sizeof(err), 10);
						} else {
							toSend[1] = '\n';
							HAL_UART_Transmit(&huart6, (uint8_t *) toSend, 2, 10);
						}
						isBtnPause = false;
						btnMorse = 0;
						btnCounter = 0;
					}
				}
			}

		} else {
			//With Interrupts
			if (uart6_try_get_received_char((uint8_t *) &recieved)) {
				uart6_start_recieve_char_it();

				char toret[2];
				toret[0] = recieved;
				toret[1] = '\n';
				uart6_transmit_it((uint8_t *) &toret, sizeof(toret));
				if (recieved == '+') {
					isUseInterrupts = false;
					HAL_UART_Abort_IT(&huart6);
					HAL_NVIC_DisableIRQ(USART6_IRQn);
					HAL_UART_Transmit(&huart6, (uint8_t *) intOff, sizeof(intOff), 10);
					continue;
				}

				if (!isBufferFull()) {
					addToBuffer(recieved);
				}
			}

			if (!isLightOn && !isPause) {
				if (!isBufferEmpty() && currentMorse < 0) {
					current = getCharFromBuffer();
					currentMorse = getMorseCode(current);
				}

				if (currentMorse >= 0) {
					blinkingMode = currentMorse / pow(10, morseTen);
					currentMorse = currentMorse % (int)pow(10, morseTen);
					morseTen--;
					if (morseTen == -1) {
						morseTen = 5;
						currentMorse = -1;
					}

					if (blinkingMode > 0) {
						blinkStartTime = HAL_GetTick();
						turnOn();
						isLightOn = true;
					}

				}
			}

			if (isLightOn) {
				diffLO = HAL_GetTick() - blinkStartTime;
				if (blinkingMode == 1) {
					if (diffLO >= 300) {
						turnOff();
						pauseStartTime = HAL_GetTick();
						isLightOn = false;
						isPause = true;
					}
				} else if (blinkingMode == 2) {
					if (diffLO >= 700) {
						turnOff();
						pauseStartTime = HAL_GetTick();
						isLightOn = false;
						isPause = true;
					}
				}
			}

			if (isPause) {
				diffPause = HAL_GetTick() - pauseStartTime;
				if (diffPause >= 300) {
					isPause = false;
				}
			}

			if (!isBtnPressed) {
				if (isPressed()) {
					isBtnPressed = true;
					isBtnPause = false;
					btnStart = HAL_GetTick();
				}
			}

			if (isBtnPressed) {
				if (isNotPressed()) {
					isBtnPressed = false;
					isBtnPause = true;
					btnDiff = HAL_GetTick() - btnStart;
					btnPauseStart = HAL_GetTick();

					if (btnDiff >= 100) {
						if (btnDiff < 500) {
							btnMorse = btnMorse * 10 + 1;
							btnCounter++;
						} else {
							btnMorse = btnMorse * 10 + 2;
							btnCounter++;
						}
					}
				}
			}

			if (isBtnPause) {
				if (isNotPressed()) {
					btnPauseDiff = HAL_GetTick() - btnPauseStart;

					if (btnPauseDiff > 1000) {
						toSend[0] = getCharByMorseCode(btnMorse);
						if (toSend[0] == '-') {
							uart6_transmit_it((uint8_t *) &err, sizeof(err));
						} else {
							toSend[1] = '\n';
							uart6_transmit_it((uint8_t *) &toSend, sizeof(toSend));
						}
						isBtnPause = false;
						btnMorse = 0;
						btnCounter = 0;
					}
				}
			}
		}
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */