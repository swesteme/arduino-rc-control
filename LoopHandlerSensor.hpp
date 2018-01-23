#ifndef LOOP_HANDLER_SENSOR
#define LOOP_HANDLER_SENSOR

#include <CapacitiveSensor.h>
#include "LoopHandler.hpp"

class LoopHandlerSensor : public LoopHandler {
  public:
    LoopHandlerSensor(GroupBundle* bundle, bool debugOutput);

  protected:
    virtual void loopInternal();

  private:
    // define the capacitive sensor pin definition
    CapacitiveSensor m_sensor;
    // will store last time the button was touched
    unsigned long m_previousMillis;
};

#endif

