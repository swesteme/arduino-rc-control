//
//  RcActor.cpp
//  RcActor
//
//  Created by Sebastian Westemeyer on 06.01.18.
//

#include "RcActor.hpp"

RcActor::RcActor(GroupBundle *bundle, const RCSwitch* sender, const char *codeOn, const char *codeOff) : Actor(bundle, codeOn, codeOff), m_sender(sender) {
}

void RcActor::switchOn() const {
  sendCode(m_codeOn);
}

void RcActor::switchOff() const {
  sendCode(m_codeOff);
}

void RcActor::sendCode(unsigned long code) const {
  m_sender->send(code, 24);
}

