#include <FrequencyCounter.h>

FrequencyCounter RPM(2, FALLING);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint32_t rpm = RPM.ReadRPM();
  Serial.print("RPM = ");
  Serial.println(rpm);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(500);
}
