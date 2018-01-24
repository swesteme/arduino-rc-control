#include <RCSwitch.h>

#include "GroupBundle.hpp"

#include "LoopHandlerWebservice.hpp"
#include "LoopHandlerRc.hpp"
#include "LoopHandlerSensor.hpp"

RCSwitch sender = RCSwitch();

#define RC_DEBUG_OUT false
#define WS_DEBUG_OUT false
#define SN_DEBUG_OUT true

// Bundle for all groups of actors
GroupBundle *bundle = NULL;
// handler for webservice activity
LoopHandlerWebservice *wsHandler = NULL;
// handler for 433 MHz transmissions
LoopHandlerRc *rcHandler = NULL;
// handler for capacitive touch sensor
LoopHandlerSensor *sensorHandler = NULL;

void setup() {
  Serial.begin(19200);
  Serial.println(F("Init start"));

  // initialise groups
  bundle = new GroupBundle(&sender);

  // initialise WIFI and webservice
  wsHandler = new LoopHandlerWebservice(bundle, WS_DEBUG_OUT);
  
  if (!wsHandler->isError()) 
  {
    // initialise RC sender
    rcHandler = new LoopHandlerRc(bundle, RC_DEBUG_OUT, &sender);

    // initialise capacitive sensor handler
    sensorHandler = new LoopHandlerSensor(bundle, SN_DEBUG_OUT);
    
#if WS_DEBUG_OUT
    OutputPresenter presenter;
    bundle->printConfig(&presenter);
#endif
  }
  
  Serial.println(F("Init end"));
}

void loop() {
  // Check for incoming RC codes.
  rcHandler->loop();
  // no way to print debug information when webservice is active?
  if (!RC_DEBUG_OUT) {
    // Check for incoming webservice requests.
    wsHandler->loop();
  }
  // loop button checks
  sensorHandler->loop();
}

