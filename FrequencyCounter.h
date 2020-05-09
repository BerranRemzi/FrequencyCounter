/**
 * @file       FrequencyCounter.h
 * @author     Berran Remzi
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2020 Berran Remzi
 * @date       May 2020
 * @brief
 *
 */

#ifndef FREQUENCY_COUNTER_H
#define FREQUENCY_COUNTER_H

#include <Arduino.h>

#define BUFFER_SIZE         (10)
#define MAX_FREQ            (1000)  /* 60000 RPM */
#define MIN_FREQ            (10)    /*    10 RPM */
#define STOP_FREQ           (0)
#define MAX_PERIOD_US       (1000000/MIN_FREQ)
#define MIN_PERIOD_US       (1000000/MAX_FREQ)
#define STOPPED_PERIOD_US   (0xFFFFFFFF)
#define OVERRANGE_PERIOD_US (0)

static uint32_t period[BUFFER_SIZE];
static uint8_t position;
static uint32_t previousMicros;

class FrequencyCounter {
  public:
    FrequencyCounter(int _inputPin, int _mode);
    uint32_t GetPeriodAverage(void);
    uint32_t ReadPeriod(void);
    uint32_t ReadRPM(void);
    uint32_t ReadFrequency(void);
    static void EdgeDetected(void);
    
  
  private:
    void Init(void);
    int inputPin = -1;
    uint32_t freq[BUFFER_SIZE];
    int mode = RISING;
};

#endif /* FREQUENCY_COUNTER_H */
