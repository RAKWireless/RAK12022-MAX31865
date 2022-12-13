/**
   @file RAK12022_Max31865_Example.ino
   @author rakwireless.com
   @brief  This code is designed to get the sensor data
   @version 0.1
   @date 2022-02-10
   @copyright Copyright (c) 2022
**/
#include "RAK12022_MAX31865.h"     //http://librarymanager/All#RAK12022-MAX31865

// use hardware SPI,just pass in the CS pin
const int Max_CS = SS;
MAX31865 maxTemp;

void setup() {
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH);
  delay(300);
  time_t timeout = millis();
  Serial.begin(115200);
  while (!Serial)
  {
    if ((millis() - timeout) < 5000)
    {
      delay(100);
    }
    else
    {
      break;
    }
  }
  Serial.println("RAK12022 Max31865 Test");

  // configure rtd sensor
  if (maxTemp.begin(Max_CS, MAX31865_4WIRE, MAX31865_PT100)) //if use 2-wire,choose MAX31865_2WIRE (MAX31865_2WIRE,MAX31865_3WIRE，MAX31865_4WIRE)
  {
    Serial.println("Found MAX31865");
  } else {
    Serial.println("MAX31865 is not connected, Please check your connections\r\n");
    while (1)
    {
      delay(500);
    }
  }
  maxTemp.MAX31865_SetLowFaultThreshold(29);  // Set the low fault threshold to 29 degrees C
  maxTemp.MAX31865_SetHighFaultThreshold(34); // Set the high fault threshold to 34 degrees C
  delay(1000);
}

void loop()
{
  float mTemp, mResistance;
  uint8_t mStatus = 0;
  maxTemp.MAX31865_GetTemperatureAndStatus(mTemp, mResistance, mStatus);

  Serial.print("Resistance = ");
  Serial.print(mResistance);
  Serial.print(" Ohms,   ");

  Serial.print("Temperature = ");
  Serial.print(mTemp);
  Serial.print(" °C,   ");
  if (mStatus)
  {
    if (mStatus & MAX31865_FAULT_TEMP_HIGH)
    {
      Serial.print("RTD High Threshold");
    }
    if (mStatus & MAX31865_FAULT_TEMP_LOW)
    {
      Serial.print("RTD Low Threshold");
    }
    if (mStatus & MAX31865_FAULT_REFIN_HIGH)
    {
      Serial.print("REFIN- > 0.85 x Bias");
    }
    if (mStatus & MAX31865_FAULT_REFIN_LOW_OPEN)
    {
      Serial.print("REFIN- < 0.85 x Bias - FORCE- open");
    }
    if (mStatus & MAX31865_FAULT_RTDIN_LOW_OPEN)
    {
      Serial.print("RTDIN- < 0.85 x Bias - FORCE- open");
    }
    if (mStatus & MAX31865_FAULT_VOLTAGE_OOR)
    {
      Serial.print("Voltage out of range fault");
    }
  }
  Serial.println();
  delay(500);
}
