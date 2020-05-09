#include "FrequencyCounter.h"

void FrequencyCounter_Init(int _inputPin, int _mode){
    inputPin = _inputPin;
    mode = _mode;

    pinMode(inputPin, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(inputPin), FrequencyCounter_EdgeDetected, mode);
    
    position = 0;
    previousMicros = micros();
}

uint32_t FrequencyCounter_GetPeriodAverage(void){
    uint32_t sum = 0;

    for(uint8_t i = 0; i < BUFFER_SIZE;i++){
        sum += period[i];
    }
    return (sum/BUFFER_SIZE);
}

uint32_t FrequencyCounter_ReadPeriod(void){
    uint32_t p = FrequencyCounter_GetPeriodAverage();

    uint32_t currentMicros = micros();
    uint32_t lastPeriod = (uint32_t)(currentMicros - previousMicros);

    if(p > MAX_PERIOD_US || lastPeriod > MAX_PERIOD_US){
        p = STOPPED_PERIOD_US;
    }else if(p < MIN_PERIOD_US){
        p = OVERRANGE_PERIOD_US;
    }
    return (p);
}

uint32_t FrequencyCounter_ReadRPM(void){
    uint32_t f = FrequencyCounter_ReadFrequency();
    uint32_t rpm = f*60;
    return (rpm);
}

uint32_t FrequencyCounter_ReadFrequency(void){
    uint32_t p = FrequencyCounter_ReadPeriod();
    uint32_t f = STOP_FREQ;

    switch (p){
    case OVERRANGE_PERIOD_US:
        f = MAX_FREQ;
        break;
    case STOPPED_PERIOD_US:
        f = STOP_FREQ;
        break;
    default:
        f = 1000000/p;
        break;
    }

    return (f);
}

void FrequencyCounter_EdgeDetected(void){
    uint32_t currentMicros = micros();
    uint32_t p = (uint32_t)(currentMicros - previousMicros);

    previousMicros = currentMicros;

    period[position] = p;
    position++;

    if(position>=BUFFER_SIZE){
        position = 0;
    }
    
}