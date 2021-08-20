#include <Arduino.h>
#include "custom_led_pins.h"

// none of this fuckin works

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ledpins_init();
  for (int i=0; i<6; i++) ledpins_set_value(i, 255/i);
}

void loop() {
  // put your main code here, to run repeatedly:
  //led_matrix_driver.flush();
  ledpins_flush();
  //writePinHigh(B7);
  delay(1000);
  //writePinLow(B7);
  delay(1000);
  Serial.println("x");
}
