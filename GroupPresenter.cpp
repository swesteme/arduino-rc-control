#include "GroupPresenter.hpp"

#include "NanoESP_HTTP.h"

// did not find a way to create this dynamically ;-(
const char index[] PROGMEM = { "HTTP/1.1 200 OK\nConnection: close\nContent-Type: application/json\n\n[\n { \"id\" : \"30\", \"sct\" : \"1\" },\n { \"id\" : \"31\", \"sct\" : \"1\" },\n { \"id\" : \"32\", \"sct\" : \"1\" },\n { \"id\" : \"33\", \"sct\" : \"1\" },\n { \"id\" : \"40\", \"sct\" : \"2\" },\n { \"id\" : \"41\", \"sct\" : \"2\" },\n { \"id\" : \"42\", \"sct\" : \"2\" },\n { \"id\" : \"43\", \"sct\" : \"2\" } \n]\0" };

void OutputPresenter::print() {
  Serial.println(index);
}

WebservicePresenter::WebservicePresenter(int client, NanoESP_HTTP* nanoEsp) : m_client(client), m_nanoEsp(nanoEsp) {
}

void WebservicePresenter::print() {
  m_nanoEsp->sendFromFlash(m_client, index, sizeof(index));
}

