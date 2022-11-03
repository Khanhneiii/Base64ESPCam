#include "cam.h"

esp_sleep_wakeup_cause_t sleep() {
  while (Serial.available()) Serial.read();
  delay(100);
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0RXD_U, FUNC_U0RXD_GPIO3);
  gpio_wakeup_enable(GPIO_NUM_3, GPIO_INTR_LOW_LEVEL);
  esp_sleep_enable_gpio_wakeup();
  // Enter light sleep mode
  esp_err_t check_sleep = esp_light_sleep_start();
  // Restore GPIO3 function as U0RXD
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0RXD_U, FUNC_U0RXD_U0RXD);
  esp_sleep_wakeup_cause_t wakeup_cause;
  wakeup_cause = esp_sleep_get_wakeup_cause();
  //Serial.println("Wakeup");
  return wakeup_cause;
}

String Photo2JSON(String Base64){
  return "{\"img\":\"" + Base64 + "\"}";
}

void setup() {
  Serial.begin(115200);
  camera_init();
}

void loop() {
  sleep();
  String mess = Serial.readString();
  if (mess.indexOf("Img"))
    Serial.println(Photo2JSON(Photo2Base64()));
}
