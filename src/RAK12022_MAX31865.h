/**
   @file RAK12022_MAX31865.h
   @author rakwireless.com
   @brief  This code is designed to config MAX31865 device and handle the sensor data
   @version 0.1
   @date 2022-02-10
   @copyright Copyright (c) 2022
**/

#ifndef RAK12022_MAX31865_h
#define RAK12022_MAX31865_h

#include <Arduino.h>
#include "RAK_SPI.h"
#include <stdlib.h>
#include <SPI.h>

#define MAX31865_CONFIG_REG 0x00
#define MAX31865_RTD_REG 0x01
#define MAX31865_HIGHFAULT_REG 0x03
#define MAX31865_LOWFAULT_REG 0x05
#define MAX31865_FAULTSTATUS_REG 0x07

#define MAX31865_FAULT_REFIN_LOW_OPEN 0x10
#define MAX31865_FAULT_RTDIN_LOW_OPEN 0x08
#define MAX31865_FAULT_VOLTAGE_OOR 0x04
#define MAX31865_FAULT_TEMP_HIGH 0x80
#define MAX31865_FAULT_TEMP_LOW 0x40
#define MAX31865_FAULT_REFIN_HIGH 0x20

#define MAX31865_2WIRE 2
#define MAX31865_3WIRE 3
#define MAX31865_4WIRE 4
#define MAX31865_PT100 400
#define MAX31865_PT1000 4000

class MAX31865
{
public:
  bool begin(int8_t cs, uint8_t Max31865_Wires = MAX31865_3WIRE, uint16_t Max31865_Type = MAX31865_PT100);
  void MAX31865_GetTemperatureAndStatus(float &maxTemp, float &maxResistance, uint8_t &maxStatus);
  void MAX31865_SetLowFaultThreshold(float data);
  void MAX31865_SetHighFaultThreshold(float data);
  void MAX31865_SendByte(uint8_t reg, uint8_t data);
  void MAX31865_SendWord(uint8_t reg, uint16_t data);

  uint8_t MAX31865_ReceiveByte(uint8_t reg);
  uint16_t MAX31865_ReceiveWord(uint8_t reg);


private:
  void MAX31865_Config();
  uint16_t max_Rtd;
  uint8_t max_Status; //  status - full status code
  uint16_t max_HighFaultThreshold = 65535;
  uint16_t max_LowFaultThreshold = 0;
  uint8_t _spi_cs;
  uint8_t max_wires;
  uint16_t max_Type; // 1 = PT100; 2 = PT1000
};

#endif
