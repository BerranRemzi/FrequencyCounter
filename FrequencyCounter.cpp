#include "FrequencyCounter.h"

FrequencyCounter::FrequencyCounter(int _inputPin, int _mode){
    inputPin = _inputPin;
    mode = _mode;
    Init();
}

void FrequencyCounter::Init(void){
    pinMode(inputPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(inputPin), EdgeDetected, mode);
}

uint32_t FrequencyCounter::GetPeriodAverage(void){
    uint32_t sum = 0;

    for(uint8_t i = 0; i < BUFFER_SIZE;i++){
        sum+=period[i];
    }
    return (sum/BUFFER_SIZE);
}

uint32_t FrequencyCounter::ReadPeriod(void){
    uint32_t p = GetPeriodAverage();

    if(p > MAX_PERIOD_US){
        p = STOPPED_PERIOD_US;
    }else if(p < MIN_PERIOD_US){
        p = OVERRANGE_PERIOD_US;
    }
    return (p);
}

uint32_t FrequencyCounter::ReadRPM(void){
    uint32_t f = ReadFrequency();
    uint32_t rpm = f/60;
    return (rpm);
}

uint32_t FrequencyCounter::ReadFrequency(void){
    uint32_t p = ReadPeriod();
    uint32_t f = STOP_FREQ;

    switch (p){
    case OVERRANGE_PERIOD_US:
        f = STOP_FREQ;
        break;
    case STOPPED_PERIOD_US:
        f = MAX_FREQ;
        break;
    default:
        f = 1000000/p;
        break;
    }

    return (f);
}

void FrequencyCounter::EdgeDetected(void){
    uint32_t currentMicros = micros();
    uint32_t p = (uint32_t)(currentMicros - previousMicros);
    period[position] = p;
    position++;
    if(position>BUFFER_SIZE){
        position = 0;
    }
}