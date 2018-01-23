#include "LoopHandlerWebservice.hpp"
#include "GroupPresenter.hpp"
#include "GroupBundle.hpp"

#include "passwords.h"

LoopHandlerWebservice::LoopHandlerWebservice(GroupBundle* bundle, bool debugOutput) : LoopHandler(bundle, debugOutput), m_nanoesp(), m_http(m_nanoesp)
{
  // initalise nano esp
  m_nanoesp.init(debugOutput);

  Serial.println(F("Trying to connect WIFI"));
  
  // Only station mode for web service
  m_nanoesp.configWifiStation(SSID, PASSWORD);

  // Wait till connected to WiFi
  if (m_nanoesp.wifiConnected()) {
    Serial.println(F("WIFI connected")); 

    // Print IP in terminal
    Serial.println("IP-address: " + m_nanoesp.getIp());

    //Start TCP server
    if (m_nanoesp.startTcpServer(80)) {
      Serial.println(F("TCP server active"));
    } else {
      error(F("TCP server error"));
    }
  } else {
    error(F("WIFI connection failed"));
  }
}

void LoopHandlerWebservice::loopInternal() {
  String method, resource, parameter;
  int id;

  if (m_http.recvRequest(id, method, resource, parameter)) {
    if (m_debugOutput) {
      Serial.println("New Request from id :" + String(id) + ", method: " + method +  ", resource: " + resource +  " parameter: " + parameter);
    }

    // send config
    WebservicePresenter presenter(id, &m_http);
    // print configuration to webservice
    m_bundle->printConfig(&presenter);
    // close HTTP connection
    m_nanoesp.closeConnection(id);
    if (m_debugOutput) {
      Serial.println(F("Connection closed."));
    }

    // check for GET parameter content
    if (parameter != "") {
      // id=31
      String sId = parameter.substring(parameter.indexOf('=') + 1, parameter.indexOf('&'));
      String sNewState = parameter.substring(parameter.indexOf('&') + 1);
      sNewState = sNewState.substring(sNewState.indexOf('=') + 1);
      m_bundle->switchGroup(sId.toInt(), sNewState.equals(String(F("on"))));
      if (m_debugOutput) {
        Serial.println(String(F("Switch ID: ")) + sId + String(F(" to state: ")) + sNewState);
      }
    }
  }
}

