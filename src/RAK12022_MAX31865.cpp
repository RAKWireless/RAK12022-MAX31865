/**
   @file RAK_MAX31865.cpp
   @author rakwireless.com
   @brief  This code is designed to config MAX31865 device and handle the sensor data
   @version 0.1
   @date 2022-02-10
   @copyright Copyright (c) 2022
**/

#include "RAK12022_MAX31865.h"

/**
   @brief Create the interface object using hardware SPI and Initialize max31865
   @param cs              The SPI CS pin to use
   @param Max31865_Wires  Connection mode(2/3/4)
   @param Max31865_Type   Sensor type (PT100/PT1000)
 **/
bool MAX31865::begin(int8_t cs, uint8_t Max31865_Wires, uint16_t Max31865_Type)
{
  _spi_cs = cs;
  max_wires = Max31865_Wires;
  max_Type = Max31865_Type;
  RAK_SPI::SPIinit();
  RAK_SPI::SPIselect(_spi_cs);
  RAK_SPI::setSPIspeed(SPIClock::SLOW);
  MAX31865_Config();
  uint16_t highFaultData = MAX31865_ReceiveWord(MAX31865_HIGHFAULT_REG);
  if (highFaultData == max_HighFaultThreshold)
    return true;
  else
    return false;
}

/**
   @brief Max31865 send byte function
   @param reg  Register address
   @param data Send one byte of data
 **/
void MAX31865::MAX31865_SendByte(uint8_t reg, uint8_t data)
{
  uint8_t wReg[2] = {0x00};
  wReg[0] = reg | 0x80;

  RAK_SPI::writeToSPI(_spi_cs, 0x01, wReg, 0x01, &data);
}

/**
   @brief Max31865 send word function
   @param reg  Register address
   @param data Send one word of data
 **/
void MAX31865::MAX31865_SendWord(uint8_t reg, uint16_t data)
{
  uint8_t wReg[2] = {0x00};
  uint8_t wData[2] = {0x00};
  wReg[0] = reg | 0x80;
  wData[0] = data >> 8;
  wData[1] = data & 0xFF;
  RAK_SPI::writeToSPI(_spi_cs, 0x01, wReg, 0x02, wData);
}

/**
   @brief Max31865 Receive byte function
   @param reg   Register address
   @return Receive one byte of data
 **/
uint8_t MAX31865::MAX31865_ReceiveByte(uint8_t reg)
{
  uint8_t wReg[2] = {0x00};
  uint8_t rData[2] = {0x00};
  wReg[0] = reg;
  RAK_SPI::readFromSPI(_spi_cs, 0x01, wReg, 0x01, rData);

  return rData[0];
}

/**
   @brief Max31865 Receive word function
   @param reg      Register address
   @return Receive one word of data
 **/
uint16_t MAX31865::MAX31865_ReceiveWord(uint8_t reg)
{
  uint8_t wReg[2] = {0x00};
  uint8_t rData[2] = {0x00};
  wReg[0] = reg;
  RAK_SPI::readFromSPI(_spi_cs, 0x01, wReg, 0x02, rData);
  uint16_t result = ((uint16_t)rData[0] << 8) | ((uint16_t)rData[1]);
  return result;
}

/**
   @brief MAX31865 Configured
 **/
void MAX31865::MAX31865_Config()
{
  uint8_t maxConfig;
  maxConfig = 0xC2 | ((max_wires == 3) ? 0x10 : 0x00);
  MAX31865_SendByte(MAX31865_CONFIG_REG, maxConfig);
  MAX31865_SendWord(MAX31865_HIGHFAULT_REG, max_HighFaultThreshold);
  MAX31865_SendWord(MAX31865_LOWFAULT_REG, max_LowFaultThreshold);
}

/**
   @brief Get temperature,Resistance and status
   @param maxTemp        The converted temperature value
   @param maxResistance  The resistance value
   @param maxStatus      The chip status
 **/
void MAX31865::MAX31865_GetTemperatureAndStatus(float &maxTemp, float &maxResistance, uint8_t &maxStatus)
{
  max_Rtd = MAX31865_ReceiveWord(MAX31865_RTD_REG) >> 1;
  max_Status = MAX31865_ReceiveByte(MAX31865_FAULTSTATUS_REG);

  //  Serial.printf("max_rtd= %02X-------------max_status=%02X\r\n", max_Rtd, max_Status);
  if ((0 == max_Rtd) || (0 != max_Status))
  {
    MAX31865_Config();
  }
  maxTemp = ((float)max_Rtd / 32.0f) - 256.0f;
  maxResistance = (float)((uint32_t)max_Rtd * (uint32_t)max_Type) / 32767.0f;
  maxStatus = max_Status;
}

/**
   @brief Set the high temperature fault threshold
   @param data  Temperature value
 **/
void MAX31865::MAX31865_SetHighFaultThreshold(float data)
{
  max_HighFaultThreshold = (uint16_t)((data + 256.0f) * 32.0f) << 1;
  MAX31865_SendWord(MAX31865_HIGHFAULT_REG, max_HighFaultThreshold);
}

/**
   @brief Set the low temperature fault threshold
   @param data  Temperature value
 **/
void MAX31865::MAX31865_SetLowFaultThreshold(float data)
{
  max_LowFaultThreshold = (uint16_t)((data + 256.0f) * 32.0f) << 1;
  MAX31865_SendWord(MAX31865_LOWFAULT_REG, max_LowFaultThreshold);
}
