
/**
  ******************************************************************************
  * @file           : app_x-cube-eeprma1.h
  * @brief          :  This file provides code for the configuration
  *						of the EEPRMA1 instances.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_X_CUBE_EEPRMA1_H
#define __APP_X_CUBE_EEPRMA1_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
void MX_EEPROM_Init(void);
void MX_EEPROM_Process(void);

#ifdef __cplusplus
}
#endif
#endif /* __APP_X_CUBE_EEPRMA1_H */

