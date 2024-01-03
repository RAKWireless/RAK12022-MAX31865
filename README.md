| <center><img src="./assets/rakstar.jpg" alt="RAKstar" width=25%></center>  | ![RAKWireless](./assets/RAK-Whirls.png) | [![Build Status](https://github.com/RAKWireless/RAK13005-TLE7259-Library/workflows/RAK%20Library%20Build%20CI/badge.svg)](https://github.com/RAKWireless/RAK12022-MAX31865/actions) |
| -- | -- | -- |

# RAK12022

The MAX31865 is an easy-to-use resistance-to-digital converter optimized for platinum resistance temperature detectors (RTDs).This library provides basic support for configuring functions and reading data.

[*RAKwireless <RAK12022> <Inductive>*](https://store.rakwireless.com/products/RAK12022_MAX31865)


# Documentation

* **[Product Repository](https://github.com/RAKWireless/RAK12022_MAX31865)** - Product repository for the RAKWireless RAK12022_MAX31865 module.
* **[Documentation](https://docs.rakwireless.com/Product-Categories/WisBlock/12022/Overview/)** - Documentation and Quick Start Guide for the  RAK12022_MAX31865 module.

# Installation

In Arduino IDE open Sketch->Include Library->Manage Libraries then search for RAK12022.    

In PlatformIO open PlatformIO Home, switch to libraries and search for RAK12022. 
Or install the library project depend by adding 

```log
lib_deps = rakwireless/RAK12022_MAX31865 library
```
into **`platformio.ini`**

For manual installation download the archive, unzip it and place the RAK12022_MAX31865  folder into the library directory.  
In Arduino IDE this is usually <arduinosketchfolder>/libraries/    
In PlatformIO this is usually <user/.platformio/lib>     

# Usage

The library provides an MAX31865 class that allows you to communicate with MAX31865 and get the chip data,Check out the examples how to get the chip data.

## This class provides the following methods:
**void begin(int8_t cs, uint8_t Max31865_Wires = MAX31865_3WIRE, uint16_t Max31865_Type = MAX31865_PT100);**
Create the interface object using hardware SPI and Initialize max31865.
Parameters:    

| Direction | Name | Function |
| --------- | ---- | -------- |
| in        | cs | The SPI CS pin to use |
| in | Max31865_Wires | Connection mode(2/3/4) |
| in | Max31865_Type | Sensor type (PT100/PT1000) |



**void MAX31865_GetTemperatureAndStatus(float &maxTemp, float &maxResistance, uint8_t &maxStatus);**
Get temperature,Resistance and status.
Parameters:    

| Direction | Name | Function |
| --------- | ---- | -------- |
| out     | maxTemp | The converted temperature value |
| out | maxResistance | The resistance value |
| out | maxStatus | The chip status |



**void MAX31865_SetLowFaultThreshold(float data);**
Set the low temperature fault threshold.
Parameters:    

| Direction | Name | Function |
| --------- | ---- | -------- |
| in | data | Temperature value |



**void MAX31865_SetHighFaultThreshold(float data);**
Set the high temperature fault threshold.
Parameters:    

| Direction | Name | Function          |
| --------- | ---- | ----------------- |
| in        | data | Temperature value |



**void MAX31865_SendByte(uint8_t reg, uint8_t data);**
Max31865 send byte function.
Parameters:    

| Direction | Name | Function              |
| --------- | ---- | --------------------- |
| in        | reg  | Register address      |
| in        | data | Send one byte of data |



**void MAX31865_SendWord(uint8_t reg, uint16_t data);**
Max31865 send word function.
Parameters:    

| Direction | Name | Function              |
| --------- | ---- | --------------------- |
| in        | reg  | Register address      |
| in        | data | Send one word of data |



**uint8_t MAX31865_ReceiveByte(uint8_t reg);**
Max31865 Receive byte function.
Parameters:    

| Direction | Name | Function         |
| --------- | ---- | ---------------- |
| in        | reg  | Register address |
| return    |      | one byte of data |



**uint16_t MAX31865_ReceiveByte(uint8_t reg);**
Max31865 Receive word function.
Parameters:    

| Direction | Name | Function         |
| --------- | ---- | ---------------- |
| in        | reg  | Register address |
| return    |      | one word of data |
