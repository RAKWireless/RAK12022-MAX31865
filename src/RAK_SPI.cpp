/**
   @file RAK_SPI.cpp
   @author rakwireless.com
   @brief  This code is designed to config SPI device
   @version 0.1
   @date 2022-02-10
   @copyright Copyright (c) 2022
**/

#include <Arduino.h>
#include <SPI.h>
#include "RAK_SPI.h"

const uint8_t RAK_SCK = SCK;
const uint8_t RAK_MOSI = MOSI;
const uint8_t RAK_MISO = MISO;
const uint8_t RAK_CS = SS;

#if defined RUI_SDK
SPIClass SPI_USER((udrv_spimst_port)0);
#pragma message "RUI3"
#else
#if defined (_VARIANT_RAK4630_)
SPIClass SPI_USER(NRF_SPIM3, RAK_MISO, RAK_SCK, RAK_MOSI);
#elif defined (_VARIANT_RAK11300_)
MbedSPI SPI_USER(RAK_MISO, RAK_MOSI, RAK_SCK);
#else
SPI_CLASS SPI_USER;
#endif
#endif

namespace RAK_SPI
{
	namespace
	{
		constexpr uint32_t EspSPImaximumSpeed = 20000000; // 20MHz
		constexpr uint32_t NrfSPImaximumSpeed = 8000000;  // 8MHz
		constexpr uint32_t RaspSPImaximumSpeed = 8000000; // 8MHz
		constexpr uint32_t SPIminimumSpeed = 2000000;	  // 2MHz
		constexpr uint32_t RUI3SPImaximumSpeed = 8000000; // 8MHz

/* SPI relative variables */
#if defined (RUI_SDK)
		const SPISettings _fastSPI = SPISettings(RUI3SPImaximumSpeed, MSBFIRST, SPI_MODE3);
#else
#if defined(_VARIANT_RAK4630_)
		const SPISettings _fastSPI = SPISettings(NrfSPImaximumSpeed, MSBFIRST, SPI_MODE3);
#elif defined(_VARIANT_RAK11300_)
		const SPISettings _fastSPI = SPISettings(RaspSPImaximumSpeed, MSBFIRST, SPI_MODE3);
#else
		const SPISettings _fastSPI = SPISettings(EspSPImaximumSpeed, MSBFIRST, SPI_MODE3);
#endif
#endif
		const SPISettings _slowSPI = SPISettings(SPIminimumSpeed, MSBFIRST, SPI_MODE3);
		const SPISettings *_currentSPI = &_fastSPI;

		void _openSPI(uint8_t slaveSelectPIN)
		{
			SPI_USER.beginTransaction(*_currentSPI);
			// take the chip select low to select the device
			digitalWrite(slaveSelectPIN, LOW);
		}

		void _closeSPI(uint8_t slaveSelectPIN)
		{
			// take the chip select high to de-select, finish config write
			digitalWrite(slaveSelectPIN, HIGH);
			SPI_USER.endTransaction();
		}
	}

	void SPIinit()
	{
#if defined(RUI_SDK)
		SPI_USER.begin();
#else
#if defined(_VARIANT_RAK4630_)
		SPI_USER.begin();
#elif defined(_VARIANT_RAK11300_)
		SPI_USER.begin();
#else
		SPI_USER.begin(RAK_SCK, RAK_MISO, RAK_MOSI);
#endif
#endif
	}

	void SPIend()
	{
		SPI_USER.end();
	}

	void SPIselect(uint8_t slaveSelectPIN)
	{
		pinMode(slaveSelectPIN, OUTPUT);
		digitalWrite(slaveSelectPIN, HIGH);
	}

	void writeToSPI(uint8_t slaveSelectPIN, uint8_t headerLen, byte header[], uint16_t dataLen, byte data[])
	{
		_openSPI(slaveSelectPIN);
		for (auto i = 0; i < headerLen; i++)
		{
			SPI_USER.transfer(header[i]); // send header
		}
		for (auto i = 0; i < dataLen; i++)
		{
			SPI_USER.transfer(data[i]); // write values
		}
		delayMicroseconds(5);
		_closeSPI(slaveSelectPIN);
	}

	void readFromSPI(uint8_t slaveSelectPIN, uint8_t headerLen, byte header[], uint16_t dataLen, byte data[])
	{
		_openSPI(slaveSelectPIN);
		for (auto i = 0; i < headerLen; i++)
		{
			SPI_USER.transfer(header[i]); // send header
		}
		for (auto i = 0; i < dataLen; i++)
		{
			data[i] = SPI_USER.transfer(0x00); // read values
		}
		delayMicroseconds(5);
		_closeSPI(slaveSelectPIN);
	}

	void setSPIspeed(SPIClock speed)
	{
		if (speed == SPIClock::FAST)
		{
			_currentSPI = &_fastSPI;
		}
		else if (speed == SPIClock::SLOW)
		{
			_currentSPI = &_slowSPI;
		}
	}
}
