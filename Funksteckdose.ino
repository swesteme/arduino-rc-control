#include <RCSwitch.h>
#include <NanoESP.h>
#include <NanoESP_HTTP.h>
#include <CapacitiveSensor.h>
#include <Time.h>

#include "RcActor.hpp"
#include "GroupActor.hpp"
#include "GroupBundle.hpp"
#include "GroupPresenter.hpp"
#include "passwords.h"

unsigned long previousMillis = 0;   // will store last time a msg was sent

RCSwitch sender = RCSwitch();

NanoESP nanoesp = NanoESP();
NanoESP_HTTP http = NanoESP_HTTP(nanoesp);

#define RC_DEBUG_OUT false
#define WS_DEBUG_OUT false
#define SN_DEBUG_OUT true

#define SENSOR_PIN_INPUT  3
#define SENSOR_PIN_OUTPUT 14
#define SENSOR_THRESHOLD  8000
#define SENSOR_DELAY      600

// define the capacitive sensor pin definition
CapacitiveSensor sensor = CapacitiveSensor(SENSOR_PIN_OUTPUT, SENSOR_PIN_INPUT);

// Bundle for all groups of actors
GroupBundle *bundle = NULL;

void setup() {
  Serial.begin(19200);
  Serial.println(F("Init start"));

  // initalise nano esp
  nanoesp.init(WS_DEBUG_OUT);

  // initialise WIFI
  if (initWifi()) 
  {
    // initialise RC sender
    initSender();

    // initialise groups
    bundle = new GroupBundle(&sender);

#if WS_DEBUG_OUT
    OutputPresenter presenter;
    bundle->printConfig(&presenter);
#endif
  }

  // disable auto calibration
  sensor.set_CS_AutocaL_Millis(0xFFFFFFFF);
  
  Serial.println(F("Init end"));
}

void initSender() {
  // sender settings
  sender.enableTransmit(6); //Pin D6
  sender.setProtocol(1);
  sender.setPulseLength(321);
  // receiver settings
  sender.enableReceive(digitalPinToInterrupt(2));  // Receiver on interrupt 0 => that is pin #2
}

bool initWifi() {
  Serial.println(F("Trying to connect WIFI"));
  
  // Only station mode for web service
  nanoesp.configWifiStation(SSID, PASSWORD);

  // Wait till connected to WiFi
  if (nanoesp.wifiConnected()) {
    Serial.println(F("WIFI connected")); 

    // Print IP in terminal
    Serial.println("IP-address: " + nanoesp.getIp());

    //Start TCP server
    if (nanoesp.startTcpServer(80)) {
      Serial.println(F("TCP server active"));
    } else {
      errorLED(F("TCP server error"));
      return false;
    }
  } else {
    errorLED(F("WIFI connection failed"));
    return false;
  }

  return true;
}

void errorLED(String errorMsg) {
  Serial.println(errorMsg);
  digitalWrite(LED_BUILTIN, HIGH);
}

/**
 * Check for incoming RC codes.
 */
void loopSender() {
  // check, whether new rc input is available
  if (bundle != NULL && sender.available()) {
    #if RC_DEBUG_OUT
      dec2tristate(sender.getReceivedValue(), sender.getReceivedBitlength(), sender.getReceivedDelay(), sender.getReceivedProtocol());
    #endif

    // check group bundle for codes
    bundle->handleSwitchCode(sender.getReceivedValue());

    // reset state
    sender.resetAvailable();
  }
}

/**
 * Check for incoming webservice requests.
 */
void loopWebservice() {
  String method, resource, parameter;
  int id;

  if (http.recvRequest(id, method, resource, parameter)) {
    #if WS_DEBUG_OUT
      Serial.println("New Request from id :" + String(id) + ", method: " + method +  ", resource: " + resource +  " parameter: " + parameter);
    #endif

    // send config
    WebservicePresenter presenter(id, &http);
    // print configuration to webservice
    bundle->printConfig(&presenter);
    // close HTTP connection
    nanoesp.closeConnection(id);
    #if WS_DEBUG_OUT
      Serial.println(F("Connection closed."));
    #endif

    // check for GET parameter content
    if (parameter != "") {
      // id=31
      String sId = parameter.substring(parameter.indexOf('=') + 1, parameter.indexOf('&'));
      String sNewState = parameter.substring(parameter.indexOf('&') + 1);
      sNewState = sNewState.substring(sNewState.indexOf('=') + 1);
      bundle->switchGroup(sId.toInt(), sNewState.equals(String(F("on"))));
      #if WS_DEBUG_OUT
        Serial.println(String(F("Switch ID: ")) + sId + String(F(" to state: ")) + sNewState);
      #endif
    }
  }
}

void loopButton() {
  // measure capacitive sensor
  long measurement = sensor.capacitiveSensor(30);
  // check the capacitive sensor
  if (previousMillis == 0 && measurement > SENSOR_THRESHOLD) {
    // keep milliseconds
    previousMillis = millis();
    #if SN_DEBUG_OUT
      Serial.println(String(measurement));
    #endif
    // toggle group
    bundle->toggle(43);
  }

  // check whether to reset after delay
  if (previousMillis > 0 && millis() - previousMillis > SENSOR_DELAY) {
    digitalWrite(SENSOR_PIN_INPUT, LOW);
    previousMillis = 0;
    #if SN_DEBUG_OUT
      Serial.println(F("RESET!"));
    #endif
  }
}

void loop() {
  if (bundle != NULL) {
    // Check for incoming RC codes.
    loopSender();
    // no way to print debug information when webservice is active?
    if (!RC_DEBUG_OUT) {
      // Check for incoming webservice requests.
      loopWebservice();
    }
    // loop button checks
    loopButton();
  }
}

