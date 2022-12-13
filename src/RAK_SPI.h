
/**
   @file RAK_SPI.h
   @author rakwireless.com
   @brief  This code is designed to config SPI device 
   @version 0.1
   @date 2022-02-10
   @copyright Copyright (c) 2022
**/
#pragma once

#include <Arduino.h>

enum class SPIClock
{
    SLOW,
    FAST
};

namespace RAK_SPI
{
    /**
    Initializes the SPI bus.
    */
    void SPIinit();

    /**
    This basically just frees SPI and the previously used pins.
    */
    void SPIend();

    /**
     Used in case you switched SPI to another device.
    */
    void SPIselect(uint8_t slaveSelectPIN);

    /**
    Arduino function to write to the SPI.
    Takes two separate byte buffers for write header and write data

    @param [in] Header lenght
    @param [in] Header array built before
    @param [in] Data lenght
    @param [in] Data array
    */
    void writeToSPI(uint8_t slaveSelectPIN, uint8_t headerLen, byte header[], uint16_t dataLen, byte data[]);

    /**
    Arduino function to read from the SPI.
    Takes two separate byte buffers for write header and write data

    @param [in] Header lenght
    @param [in] Header array built before
    @param [in] Data lenght
    @param [in] Data array
    */
    void readFromSPI(uint8_t slaveSelectPIN, uint8_t headerLen, byte header[], uint16_t dataLen, byte data[]);

    /**
    Sets speed of SPI clock, fast or slow(20MHz or 2MHz)

    @param [in] SPIClock FAST or SLOW
    */
    void setSPIspeed(SPIClock speed);
}
