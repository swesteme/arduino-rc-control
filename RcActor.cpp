//
//  RcActor.cpp
//  RcActor
//
//  Created by Sebastian Westemeyer on 06.01.18.
//

#include "RcActor.hpp"

RcActor::RcActor(GroupBundle *bundle, const RCSwitch* sender, unsigned long codeOn, unsigned long codeOff) : Actor(bundle, codeOn, codeOff), m_sender(sender) {
}

void RcActor::switchOn() {
  Serial.println(String("Switch on ") + m_codeOn);
  sendCode(m_codeOn);
}

void RcActor::switchOff() {
  Serial.println("Switch off " + String(m_codeOff));
  sendCode(m_codeOff);
}

void RcActor::sendCode(unsigned long code) {
  m_sender->send(code, 24);
  delay(5);
  m_sender->send(code, 24);
  delay(5);
}

