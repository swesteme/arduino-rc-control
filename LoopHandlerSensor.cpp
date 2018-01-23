#include "LoopHandlerSensor.hpp"
#include "GroupBundle.hpp"

#define SENSOR_PIN_INPUT  3
#define SENSOR_PIN_OUTPUT 14
#define SENSOR_THRESHOLD  7000
#define SENSOR_DELAY      600

LoopHandlerSensor::LoopHandlerSensor(GroupBundle* bundle, bool debugOutput) : LoopHandler(bundle, debugOutput), m_sensor(SENSOR_PIN_OUTPUT, SENSOR_PIN_INPUT), m_previousMillis(0) {
  // disable auto calibration
  m_sensor.set_CS_AutocaL_Millis(0xFFFFFFFF);
}

void LoopHandlerSensor::loopInternal() {
  // measure capacitive sensor
  long measurement = m_sensor.capacitiveSensor(30);
  // check the capacitive sensor
  if (m_previousMillis == 0 && measurement > SENSOR_THRESHOLD) {
    // keep milliseconds
    m_previousMillis = millis();
    if (m_debugOutput) {
      Serial.println(String(measurement));
    }
    // toggle group
    m_bundle->toggle(43);
  }

  // check whether to reset after delay
  if (m_previousMillis > 0 && millis() - m_previousMillis > SENSOR_DELAY) {
    digitalWrite(SENSOR_PIN_INPUT, LOW);
    m_previousMillis = 0;
    if (m_debugOutput) {
      Serial.println(F("RESET!"));
    }
  }
}

