//
//  GroupActor.cpp
//  GroupActor
//
//  Created by Sebastian Westemeyer on 06.01.18.
//

#include "GroupActor.hpp"
#include "GroupBundle.hpp"

GroupActor::GroupActor(GroupBundle *bundle, const byte id, const byte section, const char *codeOn, const char *codeOff) : Actor(bundle, codeOn, codeOff), m_id(id), m_section(section), m_actors(NULL), m_numberOfActors(0), m_state(false) {
  bundle->addGroup(this);
}

GroupActor* GroupActor::addActor(Actor *newActor) {
  Actor** prevVector = m_actors;
  m_actors = new Actor*[m_numberOfActors + 1];
  for (int i = 0; i < m_numberOfActors; ++i) {
    m_actors[i] = prevVector[i];
  }
  m_actors[m_numberOfActors++] = newActor;

  if (prevVector != NULL) {
    delete prevVector;
  }

  return this;
}

void GroupActor::switchOn() const {
  // iterate vector of actors...
  for (int i = 0; i < m_numberOfActors ; ++i) {
    // ... and switch all of them on
    m_actors[i]->switchOn();
  }
}

void GroupActor::switchOff() const {
  // iterate vector of actors...
  for (int i = 0; i < m_numberOfActors ; ++i) {
    // ... and switch all of them on
    m_actors[i]->switchOff();
  }
}

bool GroupActor::toggle(const byte id) {
  // check, whether this is the group to switch...
  if (m_id == id) {
    // toggle state
    m_state = !m_state;
    // ... either on...
    if(m_state) {
      switchOn();
      return true;
    } 
    // ... or off
    switchOff();
  }
  return false;
}

