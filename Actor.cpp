//
//  Actor.cpp
//  Actor
//
//  Created by Sebastian Westemeyer on 06.01.18.
//

#include "Actor.hpp"
#include "GroupBundle.hpp"

Actor::Actor(GroupBundle *bundle, unsigned long codeOn, unsigned long codeOff) : m_codeOn(codeOn), m_codeOff(codeOff) {
    // add this actor to list of actors
    bundle->addActor(this);
//    Serial.println("Actor On: " + String(codeOn) + "/" + String(m_codeOn) + ", Off: " + String(codeOff) + "/" + m_codeOff);
}

bool Actor::matchesCode(unsigned long code) {
  // check, whether we have to switch on this actor
  if (m_codeOn == code) {
    switchOn();
    return true;
  }

  // check, whether we have to switch off this actor
  if (m_codeOff == code) {
    switchOff();
    return true;
  }

  // nothing to do
  return false;
}

