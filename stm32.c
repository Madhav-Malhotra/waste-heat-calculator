* USER CODE BEGIN Header */

/**

  ******************************************************************************

  * @file           : main.c

  * @brief          : Main program body

  ******************************************************************************

  * @attention

  *

  * Copyright (c) 2022 STMicroelectronics.

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


/* Private includes ----------------------------------------------------------*/

/* USER CODE BEGIN Includes */

#include "string.h"

#include "stdio.h"

/* USER CODE END Includes */


/* Private typedef -----------------------------------------------------------*/

/* USER CODE BEGIN PTD */


/* USER CODE END PTD */


/* Private define ------------------------------------------------------------*/

/* USER CODE BEGIN PD */

#define WATER_DENSITY 997.77          // [ kg / (m^3)  ]

#define WATER_HEAT_CAPACITY 4.186     // [ J / g / K   ]

#define DAILY_USE 2.0                 // [ hours / day ]

#define YEARLY_USE 365                // [ days / year ]

#define UNIT_PRICE 0.13               // [ $ / kWh     ]

#define ALT_RATED_POWER 1700.0        // [ W / hour    ]

#define ALT_INITIAL_COST 944.0        // [ $CAD        ]

#define ALT_REBATE_PERCENT 0.25       // [ %           ]

/* USER CODE END PD */


/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PM */


/* USER CODE END PM */


/* Private variables ---------------------------------------------------------*/

ADC_HandleTypeDef hadc1;


UART_HandleTypeDef huart2;


/* USER CODE BEGIN PV */


/* USER CODE END PV */


/* Private function prototypes -----------------------------------------------*/

void SystemClock_Config(void);

static void MX_GPIO_Init(void);

static void MX_USART2_UART_Init(void);

static void MX_ADC1_Init(void);

/* USER CODE BEGIN PFP */


long double raw_to_VOUT(uint16_t raw_input);

long double VOUT_to_resist(long double VOUT);

long double resist_to_temp(long double resist);

long double water_mass_weight(long double weight_container,

                         long double weight_water_container);

long double water_mass_volume(long double volume);

long double energy_transferred(long double water_mass, long double *temp_array);

long double power(long double energy, long double time);

long double efficiency(long double useful_power, long double rated_power);

long double annual_energy(long double power, long double daily_use, int yearly_use);

long double waste_energy(long double energy, long double efficiency);

long double energy_variable_cost(long double energy, long double unit_price);

long double ROI(long double initial_cost, long double annual_savings);


/* USER CODE END PFP */


/* Private user code ---------------------------------------------------------*/

/* USER CODE BEGIN 0 */


/* USER CODE END 0 */


/**

  * @brief  The application entry point.

  * @retval int

  */

int main(void)

{

  /* USER CODE BEGIN 1 */

uint16_t raw_input = 0;

char text[100] = {0};

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

  MX_USART2_UART_Init();

  MX_ADC1_Init();

  /* USER CODE BEGIN 2 */


  /* USER CODE END 2 */


  /* Infinite loop */

  /* USER CODE BEGIN WHILE */

  while (1)

  {

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET); //Set GPIO high (for timing purposes)


  HAL_ADC_Start(&hadc1); // Read from ADC

  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY); // Wait for analog to digital conversion

  raw_input = HAL_ADC_GetValue(&hadc1); // Get digital val (0 = 0V, 4095 = max voltage in - ex: 3.3V for 3.3V pin or 5V for 5V pin)


  // Convert raw to resistance

  long double VOUT = raw_to_VOUT(raw_input);

  long double resist = VOUT_to_resist(VOUT);

  long double temp = resist_to_temp(resist);


  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET); //Set GPIO low (for timing purposes)


  // Convert resistance to string and print

  //sprintf(text, "V: %Lf\r\n", VOUT); // % means insert, Lf for long floating point (long double), \r\n for return new line

  sprintf(text, "T: %Lf\r\n", temp); // % means insert, Lf for long floating point (long double), \r\n for return new line

  HAL_UART_Transmit(&huart2, (uint8_t*)text, strlen(text), HAL_MAX_DELAY);


  // Wait another second (CHANGED to TWO TEMPORARILY)

  HAL_Delay(1995);

    /* USER CODE END WHILE */


    /* USER CODE BEGIN 3 */

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

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);


  /** Initializes the RCC Oscillators according to the specified parameters

  * in the RCC_OscInitTypeDef structure.

  */

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;

  RCC_OscInitStruct.HSIState = RCC_HSI_ON;

  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;

  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;

  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;

  RCC_OscInitStruct.PLL.PLLM = 16;

  RCC_OscInitStruct.PLL.PLLN = 336;

  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;

  RCC_OscInitStruct.PLL.PLLQ = 7;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)

  {

    Error_Handler();

  }


  /** Initializes the CPU, AHB and APB buses clocks

  */

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK

                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;

  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;

  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;

  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;

  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;


  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)

  {

    Error_Handler();

  }

}


/**

  * @brief ADC1 Initialization Function

  * @param None

  * @retval None

  */

static void MX_ADC1_Init(void)

{


  /* USER CODE BEGIN ADC1_Init 0 */


  /* USER CODE END ADC1_Init 0 */


  ADC_ChannelConfTypeDef sConfig = {0};


  /* USER CODE BEGIN ADC1_Init 1 */


  /* USER CODE END ADC1_Init 1 */


  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)

  */

  hadc1.Instance = ADC1;

  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;

  hadc1.Init.Resolution = ADC_RESOLUTION_12B;

  hadc1.Init.ScanConvMode = DISABLE;

  hadc1.Init.ContinuousConvMode = DISABLE;

  hadc1.Init.DiscontinuousConvMode = DISABLE;

  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;

  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;

  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;

  hadc1.Init.NbrOfConversion = 1;

  hadc1.Init.DMAContinuousRequests = DISABLE;

  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;

  if (HAL_ADC_Init(&hadc1) != HAL_OK)

  {

    Error_Handler();

  }


  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.

  */

  sConfig.Channel = ADC_CHANNEL_0;

  sConfig.Rank = 1;

  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)

  {

    Error_Handler();

  }

  /* USER CODE BEGIN ADC1_Init 2 */


  /* USER CODE END ADC1_Init 2 */


}


/**

  * @brief USART2 Initialization Function

  * @param None

  * @retval None

  */

static void MX_USART2_UART_Init(void)

{


  /* USER CODE BEGIN USART2_Init 0 */


  /* USER CODE END USART2_Init 0 */


  /* USER CODE BEGIN USART2_Init 1 */


  /* USER CODE END USART2_Init 1 */

  huart2.Instance = USART2;

  huart2.Init.BaudRate = 115200;

  huart2.Init.WordLength = UART_WORDLENGTH_8B;

  huart2.Init.StopBits = UART_STOPBITS_1;

  huart2.Init.Parity = UART_PARITY_NONE;

  huart2.Init.Mode = UART_MODE_TX_RX;

  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;

  huart2.Init.OverSampling = UART_OVERSAMPLING_16;

  if (HAL_UART_Init(&huart2) != HAL_OK)

  {

    Error_Handler();

  }

  /* USER CODE BEGIN USART2_Init 2 */


  /* USER CODE END USART2_Init 2 */


}


/**

  * @brief GPIO Initialization Function

  * @param None

  * @retval None

  */

static void MX_GPIO_Init(void)

{

  GPIO_InitTypeDef GPIO_InitStruct = {0};


  /* GPIO Ports Clock Enable */

  __HAL_RCC_GPIOC_CLK_ENABLE();

  __HAL_RCC_GPIOH_CLK_ENABLE();

  __HAL_RCC_GPIOA_CLK_ENABLE();

  __HAL_RCC_GPIOB_CLK_ENABLE();


  /*Configure GPIO pin Output Level */

  HAL_GPIO_WritePin(GPIOA, LD2_Pin|GPIO_PIN_10, GPIO_PIN_RESET);


  /*Configure GPIO pin : B1_Pin */

  GPIO_InitStruct.Pin = B1_Pin;

  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;

  GPIO_InitStruct.Pull = GPIO_NOPULL;

  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);


  /*Configure GPIO pins : LD2_Pin PA10 */

  GPIO_InitStruct.Pin = LD2_Pin|GPIO_PIN_10;

  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;

  GPIO_InitStruct.Pull = GPIO_NOPULL;

  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


}


/* USER CODE BEGIN 4 */


// ========= TEMP UTILS ==============

long double raw_to_VOUT(uint16_t raw_input) {

long double VOUT = (long double)raw_input * (long double)5 / (long double)4095;

return VOUT;

}


long double VOUT_to_resist(long double VOUT) {

long double resist = ((long double)-12 * VOUT) / (VOUT - (long double)5 );

return resist;

}


long double resist_to_temp(long double resist) {

long double base = 28.0; // Resistance at 24 degrees celsius

long double change = 1.15; // Resistance increase per degree celsius

return 24 + ((resist - base) / change);

}


// ============ PHYS UTILS ==============

long double water_mass_weight(long double weight_container, long double weight_water_container) {

long double weight_water = (weight_water_container - weight_container) / 1000;

  return weight_water;

}

long double water_mass_volume(long double volume) {

  return (volume / 1000) * (WATER_DENSITY / 1000);

}

long double energy_transferred(long double water_mass, long double* temp_array) {

  long double change_temperature = *(temp_array + 1) - *temp_array;

  long double energy = water_mass * (WATER_HEAT_CAPACITY * 1000) * change_temperature;

  return energy;

}

long double power(long double energy, long double time) {

  return energy / time;

}

long double efficiency(long double useful_power, long double rated_power) {

  return useful_power / rated_power;

}

long double annual_energy(long double power, long double daily_use, int yearly_use) {

  long double time_in_seconds = 3600 * daily_use * yearly_use;

  return power * time_in_seconds;

}

long double waste_energy(long double energy, long double efficiency) {

  return energy * (1 - efficiency);

}

long double energy_variable_cost(long double energy, long double unit_price) {

  return energy * unit_price;

}

long double ROI(long double initial_cost, long double annual_savings) {

  return initial_cost / annual_savings;

}


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