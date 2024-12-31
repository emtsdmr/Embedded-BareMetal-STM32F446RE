/*
 * CanDriver.h
 *
 *  Created on: Dec 28, 2024
 *      Author: emrullah
 */

#ifndef SRC_CANDRIVER_H_
#define SRC_CANDRIVER_H_

#include "stm32f4xx_hal.h"
#include "GPIODevice.h"

class CanDriver {
public:
  // CAN Modes
  enum class Mode {
    Normal = 0b00,
    Loopback = 0b01,
    Silent = 0b10,
    SilentLoopback = 0b11
  };

  struct CanPinConfig {
    GPIO_TypeDef* port;        // GPIO Port name
    uint16_t pin;              // GPIO Pin number
    uint8_t alternateFunction; // Alternate Function
  };

  CanDriver(CAN_TypeDef* canInstance, Mode mode = Mode::Normal, uint32_t baudRate = DEFAULT_BAUD_RATE);

  void configurePins();
  void configureCAN(uint32_t prescaler, Mode mode, uint32_t sjw, uint32_t bs1, uint32_t bs2);

private:
  CAN_TypeDef* _canInstance;
  uint32_t _baudRate;
  Mode _mode;

  static constexpr uint32_t DEFAULT_BAUD_RATE = 500000; // Default 500 kbps

  void enableClock(); // Enable the CAN peripheral's clock

  // Static map for CAN GPIO pin mapping
  static const std::map<CAN_TypeDef*, std::vector<CanPinConfig>> canPinMap;
};

#endif /* SRC_CANDRIVER_H_ */