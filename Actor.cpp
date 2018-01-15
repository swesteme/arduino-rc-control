//
//  Actor.cpp
//  Actor
//
//  Created by Sebastian Westemeyer on 06.01.18.
//

#include "Actor.hpp"
#include "GroupBundle.hpp"

Actor::Actor(GroupBundle *bundle, const char *codeOn, const char *codeOff) : m_codeOn(triState2Decimal(codeOn)), m_codeOff(triState2Decimal(codeOff)) {
    // add this actor to list of actors
    bundle->addActor(this);
}

bool Actor::matchesCode(unsigned long code) const {
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


static unsigned long Actor::triState2Decimal(const char *sCodeWord) {
  // turn the tristate code word into the corresponding bit pattern, then send it
  unsigned long code = 0;
  unsigned int length = 0;
  for (const char* p = sCodeWord; *p; p++) {
    code <<= 2L;
    switch (*p) {
      case '0':
        // bit pattern 00
        break;
      case 'F':
        // bit pattern 01
        code |= 1L;
        break;
      case '1':
        // bit pattern 11
        code |= 3L;
        break;
    }
    length += 2;
  }
  return code;
}

