#include <FrequencyCounter.h>

#define PWM_PIN   9
#define INPUT_PIN 2

void setup() {
  // put your setup code here, to run once:
  FrequencyCounter_Init(INPUT_PIN, FALLING);
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);  
  /* Connect pin 2 to pin 9, PWM freq is 490Hz */
  pinMode(PWM_PIN, OUTPUT);
  analogWrite(PWM_PIN, 127);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint32_t rpm = FrequencyCounter_ReadRPM();
  uint32_t freq = FrequencyCounter_ReadFrequency();
  uint32_t period = FrequencyCounter_ReadPeriod();

  Serial.print("RPM = ");
  Serial.print(rpm);
  Serial.print(", Period = ");
  Serial.print(period);
  Serial.print(", Freq = ");
  Serial.println(freq); 
  
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  delay(1000);
}