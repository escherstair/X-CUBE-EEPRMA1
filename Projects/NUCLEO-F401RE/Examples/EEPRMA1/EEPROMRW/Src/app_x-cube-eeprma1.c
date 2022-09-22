/**
  ******************************************************************************
  * @file           : app_x-cube-eeprma1.c
  * @brief          : This file provides code for the configuration
  *						of the STMicroelectronics.X-CUBE-EEPRMA1.3.1.1 instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "main.h"

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "app_x-cube-eeprma1.h"
#include "stm32f4xx_nucleo.h"
#include "eeprma1_m24.h"
#include "eeprma1_m95.h"
#include "eeprma1_conf.h"

/** @defgroup EEPROM_NUCLEO
  * @{
  */

/** @defgroup Main
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/*Source address of one node should be destination for other node & vice-versa*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#define COUNTOF(a)      (sizeof(a) / sizeof(*(a)))

/*size of data to be read/write */
#define SIZE10     (COUNTOF(tx10)-1)
#define SIZE16     (COUNTOF(tx16)-1)
#define SIZE43     (COUNTOF(tx43)-1)
#define SIZE128    (COUNTOF(tx128)-1)
#define SIZE256    (COUNTOF(tx256)-1)
#define SIZE260    (COUNTOF(tx260)-1)
#define SIZE495    (COUNTOF(tx495)-1)
#define SIZE512    (COUNTOF(tx512)-1)
#define SIZE20     (COUNTOF(tx20)-1)

/*Sample data for R/W */
uint8_t tx10[] = "STM32F4/L4";
uint8_t tx20[] = "NUCLEO-L0/F4/G4 ODE ";
uint8_t tx16[] = "HelloSTM32 12345";
uint8_t tx43[] = "HelloSTM32 12345678911 HelloSTM32 12345678911";
uint8_t tx128[] = "At power-up, the device does not respond to any instruction until VCC has reached the internal reset threshold voltage.Thank you";
uint8_t tx256[] = "abcdefghE-EEPROM-Expansion Firmware library EEPROM driver example : This firmware provides a basic example of how to use the X-Nucleo-eXpansion firmware library. This block of data is specially written to test the data write function of EEPROM (SPI/I2C)  ";
uint8_t tx260[] = "abcdefghE-EEPROM-Expansion Firmware library EEPROM driver example : This firmware provides a basic example of how to use the X-Nucleo-eXpansion firmware library. This block of data is specially written to test the data write function of EEPROM (SPI/I2C)  IC   ";
uint8_t tx495[] = "abcdefghE-EEPROM- Expansion Firmware library EEPROM driver example : This firmware provides a basic example of how to use the X-Nucleo-eXpansion firmware library. This block of data is specially written to test the data write function of EEPROM (SPI/I2C)   abcdefghE-EEPROM-Expansion Firmware library EEPROM driver example : This firmware provides a basic example of how to use the X-Nucleo-eXpansion firmware library. This block of data is specially written to test the data write function of E";
uint8_t tx512[] = "abcdefghE-EEPROM- Expansion Firmware library EEPROM driver example : This firmware provides a basic example of how to use the X-Nucleo-eXpansion firmware library. This block of data is specially written to test the data write function of EEPROM (SPI/I2C)   abcdefghE-EEPROM-Expansion Firmware library EEPROM driver example : This firmware provides a basic example of how to use the X-Nucleo-eXpansion firmware library. This block of data is specially written to test the data write function of EEPROM SPI/I2C IC";

/*Rx buffer*/
uint8_t rx10[SIZE10];
uint8_t rx16[SIZE16];
uint8_t rx43[SIZE43];
uint8_t rx128[SIZE128];
uint8_t rx256[SIZE256];
uint8_t rx260[SIZE260];
uint8_t rx495[SIZE495];
uint8_t rx512[SIZE512];

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Global variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
extern void SystemClock_Config( void );
void M24_TestSingleByte(uint32_t  TargetAddress,int32_t TargetName,int32_t expWriteStatus,int32_t expReadStatus);
void M95_TestSingleByte(uint32_t  TargetAddress,uint32_t TargetName,int32_t expWriteStatus,int32_t expReadStatus);
void M24_TestData(uint32_t  TargetAddress,uint32_t TargetName, uint8_t tx[],uint8_t rx[],uint16_t size,int32_t expWriteStatus,int32_t expReadStatus);
void M95_TestData(uint32_t  TargetAddress,uint32_t TargetName, uint8_t tx[],uint8_t rx[],uint16_t Size,int32_t expWriteStatus,int32_t expReadStatus);
void M24_TestPage(uint32_t  TargetAddress,uint32_t TargetName,uint8_t tx[],uint8_t rx[],uint16_t size,int32_t expWriteStatus,int32_t expReadStatus);
void M95_TestPage(uint32_t  TargetAddress,uint32_t TargetName,uint8_t tx[],uint8_t rx[],uint16_t size,int32_t expWriteStatus,int32_t expReadStatus);
void TestData_WriteProtect(uint32_t  TargetAddress,uint8_t TargetName, uint8_t tx[],uint8_t rx[],uint16_t Size,int32_t expWriteStatus,int32_t expReadStatus);
int32_t WriteEnableReadStatus(uint32_t TargetName);
int32_t WriteDisableReadStatus(uint32_t TargetName);
int32_t TestData_BlockProtect (uint8_t BlockProtect,uint32_t  TargetAddress,uint8_t TargetName, uint8_t tx[],uint8_t rx[],uint16_t Size);
void MX_EEPROM_RW_Init(void);
void MX_EEPROM_RW_Process(void);

/* Exported functions ------------------------------------------------------- */

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

void MX_EEPROM_Init(void)
{
  /* USER CODE BEGIN SV */

  /* USER CODE END SV */

  /* USER CODE BEGIN M24_M95_Library_Init_PreTreatment */

  /* USER CODE END M24_M95_Library_Init_PreTreatment */

  /* Initialize the peripherals and the M24 and M95 components */
  MX_EEPROM_RW_Init();

  /* USER CODE BEGIN SV */

  /* USER CODE END SV */

  /* USER CODE BEGIN M24_M95_Library_Init_PostTreatment */

  /* USER CODE END M24_M95_Library_Init_PostTreatment */
}

void MX_EEPROM_Process(void)
{
  /* USER CODE BEGIN S2LP_Library_Process */
   MX_EEPROM_RW_Process();

  /* USER CODE END M24_M95_Library_Process */
}

  /**
  * @brief  Initialize the EEPROM Read Write Example
  * @retval None
  */

void MX_EEPROM_RW_Init(void)
{

  EEPRMA1_GPIO_Init();
 /* Init UART for display message on console */
  BSP_COM_Init(COM1);
  while( EEPRMA1_M24_Init(EEPRMA1_M24C02_0)!= BSP_ERROR_NONE);
  while( EEPRMA1_M24_Init(EEPRMA1_M24256_0)!= BSP_ERROR_NONE);
  while( EEPRMA1_M24_Init(EEPRMA1_M24M01_0)!= BSP_ERROR_NONE);
  while( EEPRMA1_M95_Init(EEPRMA1_M95M01_0)!= BSP_ERROR_NONE);
  while( EEPRMA1_M95_Init(EEPRMA1_M95256_0)!= BSP_ERROR_NONE);
  while( EEPRMA1_M95_Init(EEPRMA1_M95040_0)!= BSP_ERROR_NONE);

  /* Write Enable, Write Disable and Read Status only for SPI EEPROM  */
  printf(" \r\n ");
  printf("--SPI EEPROM READ STATUS-- \r\n");
  WriteDisableReadStatus(EEPRMA1_M95256_0);
  HAL_Delay(5);
  WriteEnableReadStatus(EEPRMA1_M95256_0);
  HAL_Delay(5);
  WriteDisableReadStatus(EEPRMA1_M95040_0);
  HAL_Delay(5);
  WriteEnableReadStatus(EEPRMA1_M95040_0);
  HAL_Delay(5);
  WriteDisableReadStatus(EEPRMA1_M95M01_0);
  HAL_Delay(5);
  WriteEnableReadStatus(EEPRMA1_M95M01_0);

  /* Writing Single Byte in I2C EEPROM */
  printf(" \r\n ");
  printf("-- I2C/SPI EEPROM SINGLE BYTE-- \r\n");
    M24_TestSingleByte(0x00,EEPRMA1_M24C02_0,BSP_ERROR_NONE,BSP_ERROR_NONE);
    M24_TestSingleByte(0xC8,EEPRMA1_M24256_0,BSP_ERROR_NONE,BSP_ERROR_NONE);
    M24_TestSingleByte(0x05,EEPRMA1_M24M01_0,BSP_ERROR_NONE,BSP_ERROR_NONE);
    M95_TestSingleByte(0x01,EEPRMA1_M95040_0,BSP_ERROR_NONE,BSP_ERROR_NONE);
    M95_TestSingleByte(0x01,EEPRMA1_M95M01_0,BSP_ERROR_NONE,BSP_ERROR_NONE);
 /*EEPROM I2C : Multiple Bytes read/write*/
  printf(" \r\n ");
  printf("-- I2C/SPI EEPROM DATA -- \r\n");
    /* Write Data into I2C EEPROM memory from begin to end and then read */
   M24_TestData(0x00,EEPRMA1_M24C02_0,tx256,rx256,SIZE256,BSP_ERROR_NONE,BSP_ERROR_NONE);
   M95_TestData(0x00,EEPRMA1_M95040_0,tx256,rx256,SIZE256,BSP_ERROR_NONE,BSP_ERROR_NONE);

  /*EEPROM I2C : Page read/write*/
  printf(" \r\n ");
  printf("--I2C EEPROM PAGE-- \r\n");
  M24_TestPage(0x00,EEPRMA1_M24C02_0,tx16,rx16,SIZE16,BSP_ERROR_NONE,BSP_ERROR_NONE);

  /*EEPROM SPI : Page read/write*/
  printf(" \r\n ");
  printf("--SPI EEPROM PAGE-- \r\n");
  M95_TestPage(0x00,EEPRMA1_M95M01_0,tx256,rx256,SIZE256,BSP_ERROR_NONE,BSP_ERROR_NONE);

}

void MX_EEPROM_RW_Process(void)
{
}

/**
  * @brief  Write Enable(WREN) test examples for SPI_EEPROM memory .
  * @param  TargetName : SPI_EEPROM memory name to write.
  * @retval EEPROMEX enum status
  */
int32_t WriteEnableReadStatus(uint32_t TargetName)
{

  uint8_t rx[1];
  int32_t readstatus;
  switch (TargetName)
  {
  case EEPRMA1_M95M01_0:
    if ( EEPRMA1_M95_WriteCmd( EEPROMEX_WREN, M95M01_SPI_ADDR ) == BSP_ERROR_NONE )
      readstatus = EEPRMA1_SPI_ReadReg(rx, M95M01_SPI_ADDR);
    else
      return BSP_ERROR_COMPONENT_FAILURE;
    break;
  case EEPRMA1_M95256_0:
    if ( EEPRMA1_M95_WriteCmd( EEPROMEX_WREN, M95256_SPI_ADDR ) == BSP_ERROR_NONE )
      readstatus = EEPRMA1_SPI_ReadReg(rx, M95256_SPI_ADDR);
    else
      return BSP_ERROR_COMPONENT_FAILURE;
    break;
  case EEPRMA1_M95040_0:
    if ( EEPRMA1_M95_WriteCmd( EEPROMEX_WREN, M95040_SPI_ADDR ) == BSP_ERROR_NONE )
      readstatus = EEPRMA1_SPI_ReadReg(rx, M95040_SPI_ADDR);
    else
      return BSP_ERROR_COMPONENT_FAILURE;
    break;
  }

  //int32_t readstatus = EEPRMA1_M95_ReadReg(TargetName, rx);
 // int32_t readstatus = EEPRMA1_SPI_ReadReg(rx, M95256_SPI_ADDR);
  if (TargetName == EEPRMA1_M95M01_0)
    printf("target: %s|rx: %02x \r\n","M95M01",rx[0]);
  else if (TargetName == EEPRMA1_M95256_0)
    printf("target: %s|rx: %02x \r\n","M95256",rx[0]);
  else if (TargetName == EEPRMA1_M95040_0)
    printf("target: %s|rx: %02x \r\n","M95040",rx[0]);

  return readstatus;

}

/**
  * @brief  Write Disable(WRDI) test examples for SPI_EEPROM memory .
  * @param  TargetName : SPI_EEPROM memory name to write.
  * @retval EEPROMEX enum status
  */
int32_t WriteDisableReadStatus(uint32_t TargetName)
{
  uint8_t rx[1];
  int32_t readstatus;
  switch (TargetName)
  {
  case EEPRMA1_M95M01_0:
    if ( EEPRMA1_M95_WriteCmd( EEPROMEX_WRDI, M95M01_SPI_ADDR ) != BSP_ERROR_NONE )
      return BSP_ERROR_COMPONENT_FAILURE;
    else
      readstatus = EEPRMA1_SPI_ReadReg(rx, M95M01_SPI_ADDR);
    break;
  case EEPRMA1_M95256_0:
    if ( EEPRMA1_M95_WriteCmd( EEPROMEX_WRDI, M95256_SPI_ADDR ) != BSP_ERROR_NONE )
      return BSP_ERROR_COMPONENT_FAILURE;
    else
      readstatus = EEPRMA1_SPI_ReadReg(rx, M95256_SPI_ADDR);
    break;
  case EEPRMA1_M95040_0:
    if ( EEPRMA1_M95_WriteCmd( EEPROMEX_WRDI, M95040_SPI_ADDR ) != BSP_ERROR_NONE )
      return BSP_ERROR_COMPONENT_FAILURE;
    else
      readstatus = EEPRMA1_SPI_ReadReg(rx, M95040_SPI_ADDR);
    break;
  }

  //int32_t readstatus = EEPRMA1_M95_ReadReg(TargetName, rx);
 // int32_t readstatus = EEPRMA1_SPI_ReadReg(rx, M95256_SPI_ADDR);
  if (TargetName == EEPRMA1_M95M01_0)
    printf("target: %s|rx: %02x \r\n","M95M01",rx[0]);
  else if (TargetName == EEPRMA1_M95256_0)
    printf("target: %s|rx: %02x \r\n","M95256",rx[0]);
  else if (TargetName == EEPRMA1_M95040_0)
    printf("target: %s|rx: %02x \r\n","M95040",rx[0]);

  return readstatus;
}

/**
  * @brief  Block Protect  + write + READ check test example for SPI_EEPROM memory .
  * @param  TargetAddress : SPI data memory address to write.
  * @param  TargetName : SPI_EEPROM memory name to write.
  * @param  tx : Input Buffer to Write.
  * @param  rx : Output Buffer to Read.
  * @param  Size : Size in bytes of the value to be written.
  * @retval EEPROMEX enum status
  */
int32_t TestData_BlockProtect(uint8_t Block_Protect,uint32_t  TargetAddress, uint8_t TargetName, uint8_t tx[],uint8_t rx[],uint16_t Size)
{
  int32_t readstatus = BSP_ERROR_NONE;

  EEPRMA1_M95_IsDeviceReady(TargetName);
 /* Protect */
  if (EEPRMA1_SPI_WriteReg(Block_Protect, TargetName) != BSP_ERROR_NONE)
    return BSP_ERROR_COMPONENT_FAILURE;
   /* write */
    EEPRMA1_M95_WriteData(TargetName, tx, TargetAddress, Size);
    HAL_Delay(5);
  /* read */
     readstatus = EEPRMA1_M95_ReadData(TargetName, rx, TargetAddress, Size);

  if (TargetName == EEPRMA1_M95040_0)
    printf("BlockProtect|target: %s|address: %lu|TX: %s|\t RX: %s|data size: %d \r\n\n","M95040",TargetAddress,tx,rx,Size);
  else if (TargetName == EEPRMA1_M95M01_0)
    printf("BlockProtect|target: %s|address: %lu|TX: %s|\t RX: %s|data size: %d \r\n\n","M95M01",TargetAddress,tx,rx,Size);
  else if (TargetName == EEPRMA1_M95256_0)
    printf("BlockProtect|target: %s|address: %lu|TX: %s|\t RX: %s|data size: %d \r\n\n","M95256",TargetAddress,tx,rx,Size);

  return readstatus;
}

/**
  * @brief  Write data + Protect with WC + write different data+ READ to check no change test example only for I2C_EEPROM memory .
  * @param  TargetAddress : SPI data memory address to write.
  * @param  TargetName : SPI_EEPROM memory name to write.
  * @param  tx : Input Buffer to Write.
  * @param  rx : Output Buffer to Read.
  * @param  Size : Size in bytes of the value to be written.
  * @param  expWriteStatus : Expected Write EEPROM enum Status according to parameter passed.
  * @param  expReadStatus : Expected Read EEPROM enum Status according to parameter passed.
  */
void TestData_WriteProtect(uint32_t  TargetAddress,uint8_t TargetName, uint8_t tx[],uint8_t rx[],uint16_t Size,int32_t expWriteStatus,int32_t expReadStatus)
{

  EEPROMEX_CTRL_LOW(WC); /*Only for I2C*/
  int32_t writeStatus = EEPRMA1_M24_WriteData(TargetName, tx, TargetAddress, Size);
  HAL_Delay(5);

  EEPROMEX_CTRL_HIGH(WC); /*Only for I2C*/

  EEPRMA1_M24_WriteData(TargetName, tx10,TargetAddress,SIZE10);
  HAL_Delay(5);
  int32_t readstatus= EEPRMA1_M24_ReadData(TargetName, rx, TargetAddress, Size);
  HAL_Delay(5);

  if (TargetName == EEPRMA1_M24C02_0) {
    if ( (writeStatus == expWriteStatus) && (readstatus == expReadStatus) )
      printf("TestData|target: %s|address: %lu|TX: %s|\t RX: %s|data size: %d|result: passed \r\n","M24C02",TargetAddress,tx,rx,Size);
    else
      printf("TestData|target: %s|address: %lu|TX: %s|\t RX: %s|data size: %d|result: failed \r\n","M24C02",TargetAddress,tx,rx,Size);
  }

  if (TargetName == EEPRMA1_M24256_0) {
    if ( (writeStatus == expWriteStatus) && (readstatus == expReadStatus) )
      printf("TestData|target: %s|address: %lu|TX: %s|\t RX: %s|data size: %d|result: passed \r\n","M24256",TargetAddress,tx,rx,Size);
    else
      printf("TestData|target: %s|address: %lu|TX: %s|\t RX: %s|data size: %d|result: failed  \r\n","M24256",TargetAddress,tx,rx,Size);
  }

  if (TargetName == EEPRMA1_M24M01_0) {
    if ( (writeStatus == expWriteStatus) && (readstatus == expReadStatus) )
      printf("TestData|target: %s|address: %lu|TX: %s|\t RX: %s|data size: %d|result: passed \r\n","M24M01",TargetAddress,tx,rx,Size);
    else
      printf("TestData|target: %s|address: %lu|TX: %s|\t RX: %s|data size: %d|result: failed\r\n","M24M01",TargetAddress,tx,rx,Size);
  }
}

/**
  * @brief  Test Byte Write and Byte Read in the memory at specific address.
  * @param  TargetAddress : I2C/SPI data memory address to write.
  * @param  TargetName : memory name to write.
  * @param  expWriteStatus : Expected Write EEPROM enum Status according to parameter passed.
  * @param  expReadStatus : Expected Read EEPROM enum Status according to parameter passed.
  * @retval None
  */
void M24_TestSingleByte(uint32_t  TargetAddress,int32_t TargetName,int32_t expWriteStatus,int32_t expReadStatus)
{
  uint8_t tx[] = "k";
  uint8_t rx[1];
  EEPROMEX_CTRL_LOW(WC);
  int32_t writeStatus = EEPRMA1_M24_WriteByte(TargetName, tx, TargetAddress);
  HAL_Delay(10);
  EEPROMEX_CTRL_HIGH(WC);
  int32_t readstatus = EEPRMA1_M24_ReadByte(TargetName, rx, TargetAddress);
  HAL_Delay(10);

  switch (TargetName)
  {
  case EEPRMA1_M24C02_0:
    if ( (writeStatus == expWriteStatus) && (readstatus == expReadStatus) )       /* to check whether roll over case */
      printf("TestByte|target: %s|address: %lu|TX: %s|\t RX: %s|result: passed \r\n","M24C02",TargetAddress, tx, rx);
    else
      printf("TestByte|target: %s|address: %lu|result: failed \r\n","M24C02",TargetAddress);
    break;
  case EEPRMA1_M24256_0:
    if ( (writeStatus == expWriteStatus) && (readstatus == expReadStatus) )       /* to check whether roll over case */
      printf("TestByte|target: %s|address: %lu|TX: %s|\t RX: %s|result: passed \r\n","M24256",TargetAddress, tx, rx);
    else
      printf("TestByte|target: %s|address: %lu|result: failed \r\n","M24256",TargetAddress);
    break;
  case EEPRMA1_M24M01_0:
    if ( (writeStatus == expWriteStatus) && (readstatus == expReadStatus) )       /* to check whether roll over case */
      printf("TestByte|target: %s|address: %lu|TX: %s|\t RX: %s|result: passed \r\n","M24M01",TargetAddress,tx, rx);
    else
      printf("TestByte|target: %s|address: %lu|TX: %s|\t RX: %s|result: failed \r\n","M24M01",TargetAddress,tx, rx);
    break;
  default:
    break;
  }
}

/**
  * @brief  Test Byte Write and Byte Read in the memory at specific address.
  * @param  TargetAddress : I2C/SPI data memory address to write.
  * @param  TargetName : memory name to write.
  * @param  expWriteStatus : Expected Write EEPROM enum Status according to parameter passed.
  * @param  expReadStatus : Expected Read EEPROM enum Status according to parameter passed.
  * @retval None
  */
void M95_TestSingleByte(uint32_t  TargetAddress,uint32_t TargetName,int32_t expWriteStatus,int32_t expReadStatus)
{
  uint8_t tx[] = "b";
  uint8_t rx[1];

  int32_t writeStatus = EEPRMA1_M95_WriteByte(TargetName, tx, TargetAddress);
  HAL_Delay(10);

  int32_t readstatus = EEPRMA1_M95_ReadByte(TargetName, rx, TargetAddress);
  HAL_Delay(10);

  switch (TargetName)
  {
  case EEPRMA1_M95M01_0:
    if ( (writeStatus == expWriteStatus) && (readstatus == expReadStatus) )       /* to check whether roll over case */
      printf("TestByte|target: %s|address: %lu|TX: %s|\t RX: %s|result: passed \r\n","M95M01",TargetAddress, tx, rx);
    else
      printf("TestByte|target: %s|address: %lu|result: failed \r\n","M95M01",TargetAddress);
    break;
  case EEPRMA1_M95256_0:
    if ( (writeStatus == expWriteStatus) && (readstatus == expReadStatus) )       /* to check whether roll over case */
      printf("TestByte|target: %s|address: %lu|result: passed \r\n","M95256",TargetAddress);
    else
      printf("TestByte|target: %s|address: %lu|result: failed \r\n","M95256",TargetAddress);
    break;
  case EEPRMA1_M95040_0:
    if ( (writeStatus == expWriteStatus) && (readstatus == expReadStatus) )       /* to check whether roll over case */
      printf("TestByte|target: %s|address: %lu|TX: %s|\t RX: %s|result: passed \r\n","M95040",TargetAddress,tx, rx);
    else
      printf("TestByte|target: %s|address: %lu|TX: %s|\t RX: %s|result: failed \r\n","M95040",TargetAddress,tx, rx);
    break;

  default:
    break;
  }
}

/**
  * @brief  Test Page Write/Read in the memory at specific address.
  * @param  TargetAddress : I2C/SPI data memory address to write.Its pointing to pageIndex Number.
  * @param  TargetName : memory name to write.
  * @param  tx : Input Buffer to Write.
  * @param  rx : Output Buffer to Read.
  * @param  Size : Size in bytes of the value to be written.
  * @param  expWriteStatus : Expected Write EEPROM enum Status according to parameter passed.
  * @param  expReadStatus : Expected Read EEPROM enum Status according to parameter passed.
  * @retval None
  */
void M24_TestPage(uint32_t TargetAddress,uint32_t TargetName,uint8_t tx[],uint8_t rx[],uint16_t Size,int32_t expWriteStatus,int32_t expReadStatus)
{

  EEPROMEX_CTRL_LOW(WC); /*Only for I2C*/
  int32_t writeStatus = EEPRMA1_M24_WritePage(TargetName, tx, TargetAddress, Size);
  HAL_Delay(5);
  EEPROMEX_CTRL_HIGH(WC); /*Only for I2C*/
  int32_t readstatus = EEPRMA1_M24_ReadPage(TargetName, rx,TargetAddress,Size) ;
  HAL_Delay(5);

 if (TargetName == EEPRMA1_M24C02_0) {
  if ( (writeStatus == expWriteStatus) && (readstatus == expReadStatus) )         /*To check whether Actual status is same as Expected status,so as to verify roll over case   */
    printf("TestPage|target: %s|address: %lu|data size: %d|result: passed \r\n","M24C02",TargetAddress,Size);
  else
    printf("TestPage|target: %s|address: %lu|data size: %d|result: failed \r\n","M24C02",TargetAddress,Size);
  }
 else if (TargetName == EEPRMA1_M24256_0) {
  if ( (writeStatus == expWriteStatus) && (readstatus == expReadStatus) )
    printf("TestPage|target: %s|address: %lu|data size: %d|result: passed \r\n","M24256",TargetAddress, Size);
  else
    printf("TestPage|target: %s|address: %lu|data size: %d|result: failed \r\n","M24256",TargetAddress, Size);
  }
 else if (TargetName == EEPRMA1_M24M01_0) {
  if ( (writeStatus == expWriteStatus) && (readstatus == expReadStatus) )
    printf("TestPage|target: %s|address: %lu|data size: %d|result: passed \r\n","M24M01",TargetAddress,Size);
  else
    printf("TestPage|target: %s|address: %lu|data size: %d|result: failed \r\n","M24M01",TargetAddress,Size);
  }
}

/**
  * @brief  Test Page Write/Read in the memory at specific address.
  * @param  TargetAddress : I2C/SPI data memory address to write.Its pointing to pageIndex Number.
  * @param  TargetName : memory name to write.
  * @param  tx : Input Buffer to Write.
  * @param  rx : Output Buffer to Read.
  * @param  Size : Size in bytes of the value to be written.
  * @param  expWriteStatus : Expected Write EEPROM enum Status according to parameter passed.
  * @param  expReadStatus : Expected Read EEPROM enum Status according to parameter passed.
  * @retval None
  */
void M95_TestPage(uint32_t TargetAddress,uint32_t TargetName,uint8_t tx[],uint8_t rx[],uint16_t Size,int32_t expWriteStatus,int32_t expReadStatus)
{
  int32_t writeStatus = EEPRMA1_M95_WritePage(TargetName, tx, TargetAddress, Size);
  HAL_Delay(5);
  int32_t readstatus = EEPRMA1_M95_ReadPage(TargetName, rx,TargetAddress,Size) ;
  HAL_Delay(5);

 if (TargetName == EEPRMA1_M95M01_0) {
  if ( (writeStatus == expWriteStatus) && (readstatus == expReadStatus) )
    printf("TestPage|target: %s|address: %lu|data size: %d|result: passed \r\n","M95M01",TargetAddress,Size);
  else
    printf("TestPage|target: %s|address: %lu|data size: %d|result: failed \r\n","M95M01",TargetAddress,Size);
  }
 else if (TargetName == EEPRMA1_M95040_0) {
  if ( (writeStatus == expWriteStatus) && (readstatus == expReadStatus) )
    printf("TestPage|target: %s|address: %lu|data size: %d|result: passed \r\n","M95040",TargetAddress,Size);
  else
    printf("TestPage|target: %s|address: %lu|data size: %d|result: failed \r\n","M95040",TargetAddress,Size);
  }
 else if (TargetName == EEPRMA1_M95256_0) {
  if ( (writeStatus == expWriteStatus) && (readstatus == expReadStatus) )
    printf("TestPage|target: %s|address: %lu|data size: %d|result: passed \r\n","M95256",TargetAddress, Size);
  else
    printf("TestPage|target: %s|address: %lu|data size: %d|result: failed \r\n","M95256",TargetAddress, Size);
  }
}

/**
  * @brief  Bytes Write/Read in the memory at specific address.
  * @param  TargetAddress : I2C/SPI data memory address to write.
  * @param  TargetName : memory name to write.
  * @param  tx : Input Buffer to Write.
  * @param  rx : Output Buffer to Read.
  * @param  Size : Size in bytes of the value to be written.
  * @param  expWriteStatus : Expected Write EEPROM enum Status according to parameter passed.
  * @param  expReadStatus : Expected Read EEPROM enum Status according to parameter passed.
  * @retval None
  */
void M24_TestData(uint32_t  TargetAddress,uint32_t TargetName, uint8_t tx[],uint8_t rx[],uint16_t Size,int32_t expWriteStatus,int32_t expReadStatus)
{
  int32_t writeStatus = EEPRMA1_M24_WriteData(TargetName, tx, TargetAddress, Size);
  HAL_Delay(5);
  int32_t readstatus = EEPRMA1_M24_ReadData(TargetName, rx, TargetAddress, Size);
  HAL_Delay(5);

 if (TargetName == EEPRMA1_M24C02_0) {
  if ( (writeStatus == expWriteStatus) && (readstatus == expReadStatus) )         /*To check whether Actual status is same as Expected status,so as to verify roll over case   */
    printf("TestData|target: %s|address: %lu|TX: %s|\t RX: %s|data size: %d|result: passed \r\n","M24C02",TargetAddress,tx,rx, Size);
  else
    printf("TestData|target: %s|address: %lu|data size: %d|result: failed \r\n","M24C02",TargetAddress,Size);
  }
 else if (TargetName == EEPRMA1_M24256_0) {
  if ( (writeStatus == expWriteStatus) && (readstatus == expReadStatus) )
    printf("TestData|target: %s|address: %lu|data size: %d|result: passed \r\n","M24256",TargetAddress,Size);
  else
    printf("TestData|target: %s|address: %lu|data size: %d|result: failed \r\n","M24256",TargetAddress,Size);
  }
 else if (TargetName == EEPRMA1_M24M01_0) {
  if ( (writeStatus == expWriteStatus) && (readstatus == expReadStatus) )
    printf("TestData|target: %s|address: %lu|data size: %d|result: passed \r\n","M24M01",TargetAddress,Size);
  else
    printf("TestData|target: %s|address: %lu|data size: %d|result: failed \r\n","M24M01",TargetAddress,Size);
  }
}

/**
  * @brief  Bytes Write/Read in the memory at specific address.
  * @param  TargetAddress : I2C/SPI data memory address to write.
  * @param  TargetName : memory name to write.
  * @param  tx : Input Buffer to Write.
  * @param  rx : Output Buffer to Read.
  * @param  Size : Size in bytes of the value to be written.
  * @param  expWriteStatus : Expected Write EEPROM enum Status according to parameter passed.
  * @param  expReadStatus : Expected Read EEPROM enum Status according to parameter passed.
  * @retval None
  */
void M95_TestData(uint32_t  TargetAddress,uint32_t TargetName, uint8_t tx[],uint8_t rx[],uint16_t Size,int32_t expWriteStatus,int32_t expReadStatus)
{
  int32_t writeStatus = EEPRMA1_M95_WriteData(TargetName, tx, TargetAddress, Size);
  HAL_Delay(5);
  int32_t readstatus = EEPRMA1_M95_ReadData(TargetName, rx, TargetAddress, Size);
  HAL_Delay(5);

 if (TargetName == EEPRMA1_M95256_0) {
  if ( (writeStatus == expWriteStatus) && (readstatus == expReadStatus) )         /*To check whether Actual status is same as Expected status,so as to verify roll over case   */
    printf("TestData|target: %s|address: %lu|TX: %s|\t RX: %s|data size: %d|result: passed \r\n","M95256",TargetAddress,tx,rx, Size);
  else
    printf("TestData|target: %s|address: %lu|data size: %d|result: failed \r\n","M95256",TargetAddress,Size);
  }
  if (TargetName == EEPRMA1_M95040_0) {
  if ( (writeStatus == expWriteStatus) && (readstatus == expReadStatus) )         /*To check whether Actual status is same as Expected status,so as to verify roll over case   */
    printf("TestData|target: %s|address: %lu|TX: %s|\t RX: %s|data size: %d|result: passed \r\n","M95040",TargetAddress,tx,rx, Size);
  else
    printf("TestData|target: %s|address: %lu|data size: %d|result: failed \r\n","M95040",TargetAddress,Size);
  }
 if (TargetName == EEPRMA1_M95M01_0) {
  if ( (writeStatus == expWriteStatus) && (readstatus == expReadStatus) )         /*To check whether Actual status is same as Expected status,so as to verify roll over case   */
    printf("TestData|target: %s|address: %lu|TX: %s|\t RX: %s|data size: %d|result: passed \r\n","M95M01",TargetAddress,tx,rx, Size);
  else
    printf("TestData|target: %s|address: %lu|data size: %d|result: failed \r\n","M95M01",TargetAddress,Size);
  }

}

#ifdef __cplusplus
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/