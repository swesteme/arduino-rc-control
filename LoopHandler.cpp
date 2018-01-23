#include "LoopHandler.hpp"
#include "GroupBundle.hpp"

void LoopHandler::loop() {
  if (m_bundle != NULL && !isError()) {
    loopInternal();
  }
}

void LoopHandler::error(String message) {
  m_errorState = true;
  Serial.println(message);
  digitalWrite(LED_BUILTIN, HIGH);
}

