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

static int inputPin = -1;
static uint32_t freq[BUFFER_SIZE];
static int mode = RISING;
static uint32_t filterFactorLevel = 6;
static uint32_t periodFiltered = 0;
static uint8_t position;
static uint32_t previousMicros;
static uint32_t buffer = 0;

void FrequencyCounter_Init(int _inputPin, int _mode);
uint32_t FrequencyCounter_GetPeriodAverage(void);
uint32_t FrequencyCounter_ReadPeriod(void);
uint32_t FrequencyCounter_ReadRPM(void);
uint32_t FrequencyCounter_ReadFrequency(void);
void FrequencyCounter_EdgeDetected(void);
uint32_t Average(uint32_t _newSample, uint8_t _filterFactorLevel);
    

#endif /* FREQUENCY_COUNTER_H */
