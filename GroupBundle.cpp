//
//  GroupBundle.cpp
//  GroupBundle
//
//  Created by Sebastian Westemeyer on 06.01.18.
//

#include <RCSwitch.h>

#include "GroupBundle.hpp"
#include "GroupActor.hpp"
#include "RcActor.hpp"
#include "GroupPresenter.hpp"

GroupBundle::GroupBundle(RCSwitch *sender) : m_actors(NULL), m_groups(NULL), m_numberOfActors(0), m_numberOfGroups(0) {
  // Garden
  // Actor On: 00F000000FFF/262165, Off: 00F000000FF0/262164 Garten-Steckdose I
  RcActor *garden1 = new RcActor(this, sender, 262165, 262164);
  // Actor On: 00F0FF000FFF/282645, Off: 00F0FF000FF0/282644 Garten-Steckdose II
  RcActor *garden2 = new RcActor(this, sender, 282645, 282644);
  // Actor On: 00F0F0000FFF/278549, Off: 00F0F0000FF0/278548 Garten-Steckdose III
  RcActor *garden3 = new RcActor(this, sender, 278549, 278548);

  // living room
  // Actor On: 000000FFFF0F/1361, Off: 000000FFFFF0/1364 Stehlampe
  RcActor *living1 = new RcActor(this, sender, 1361, 1364);
  // Actor On: 00000F0FFF0F/4433, Off: 00000F0FFFF0/4436 Eiswürfel
  RcActor *living2 = new RcActor(this, sender, 4433, 4436);
  // Actor On: 00000FF0FF0F/5201, Off: 00000FF0FFF0/5204 Vitrine
  RcActor *living3 = new RcActor(this, sender, 5201, 5204);

/*
//B ON:  FFFF0F0FFF0F
//B OFF: FFFF0F0FFFF0
  
  RcActor *experimentActor1 = new RcActor(this, sender, triState2Decimal("F00000FFFF0F"), triState2Decimal("F00000FFFFF0"));
//  RcActor *experimentActor2 = new RcActor(this, sender, 5592415, 5592415);
  GroupActor *experimentGroup = new GroupActor(this, 20, 1, 1, 1);
  experimentGroup->addActor(experimentActor1);//->addActor(experimentActor2);
  // AN:  5510417 5510495 FFF00FFF0F0F
  // AUS: 5510420 5510495 FFF00FFF0FFF
*/
  // Group 1 garden (DIP 01111, switch A) Alle Gartendosen gleichzeitig
  // Id: 30 On: F00000FFFF0F/4195665, Off: F00000FFFFF0/4195668
  GroupActor *groupGarden1 = new GroupActor(this, 30, 1, 4195665, 4195668);
  // Group 2 garden (DIP 01111, switch B) Brunnen
  // Id: 31 On: F0000F0FFF0F/4198737, Off: F0000F0FFFF0/4198740
  GroupActor *groupGarden2 = new GroupActor(this, 31, 1, 4198737, 4198740);
  // Group 3 garden (DIP 01111, switch C) Lampe
  // Id: 32 On: F0000FF0FF0F/4199505, Off: F0000FF0FFF0/4199508
  GroupActor *groupGarden3 = new GroupActor(this, 32, 1, 4199505, 4199508);
  // Group 4 garden (DIP 01111, switch D) Steckdose
  // Id: 33 On: F0000FFF0F0F/4199697, Off: F0000FFF0FF0/4199700
  GroupActor *groupGarden4 = new GroupActor(this, 33, 1, 4199697, 4199700);

  // Group 1 living room (DIP 00111, switch A) Stehlampe
  // Id: 40 On: FF0000FFFF0F/5244241, Off: FF0000FFFFF0/5244244
  GroupActor *groupLivingRoom1 = new GroupActor(this, 40, 2, 5244241, 5244244);
  // Group 2 living room (DIP 00111, switch B) Eiswürfel
  // Id: 41 On: FF000F0FFF0F/5247313, Off: FF000F0FFFF0/5247316
  GroupActor *groupLivingRoom2 = new GroupActor(this, 41, 2, 5247313, 5247316);
  // Group 3 living room (DIP 00111, switch C) Vitrine
  // Id: 42 On: FF000FF0FF0F/5248081, Off: FF000FF0FFF0/5248084
  GroupActor *groupLivingRoom3 = new GroupActor(this, 42, 2, 5248081, 5248084);
  // Group 4 living room (DIP 00111, switch D) Stehlampe und Eiswürfel
  // Id: 43 On: FF000FFF0F0F/5248273, Off: FF000FFF0FF0/5248276
  GroupActor *groupLivingRoom4 = new GroupActor(this, 43, 2, 5248273, 5248276);

  // fill garden groups with actors
  groupGarden1->addActor(garden1)->addActor(garden2)->addActor(garden3);
  groupGarden2->addActor(garden1);
  groupGarden3->addActor(garden2);
  groupGarden4->addActor(garden3);

  // fill living room groups with actors
  groupLivingRoom1->addActor(living1);
  groupLivingRoom2->addActor(living2);
  groupLivingRoom3->addActor(living3);
  groupLivingRoom4->addActor(living1)->addActor(living2)->addActor(living3);
}

void GroupBundle::addGroup(GroupActor *actor) {
  GroupActor** prevVector = m_groups;
  m_groups = new GroupActor*[m_numberOfGroups + 1];
  for (int i = 0; i < m_numberOfGroups; ++i) {
    m_groups[i] = prevVector[i];
  }

  m_groups[m_numberOfGroups++] = actor;

  if (prevVector != NULL) {
    delete prevVector;
  }
}

void GroupBundle::addActor(Actor *actor) {
  Actor** prevVector = m_actors;
  m_actors = new Actor*[m_numberOfActors + 1];
  for (int i = 0; i < m_numberOfActors; ++i) {
    m_actors[i] = prevVector[i];
  }

  m_actors[m_numberOfActors++] = actor;

  if (prevVector != NULL) {
    delete prevVector;
  }
}

void GroupBundle::handleSwitchCode(unsigned long code) {
  // iterate vector of actors...
  for (int i = 0; i < m_numberOfActors ; ++i) {
    // ... and check all of them
    if (m_actors[i]->matchesCode(code)) {
      // until one of them matches
      return;
    }
  }
}

void GroupBundle::printConfig(GroupPresenter* presenter) {
  presenter->print();
}

void GroupBundle::toggle(const byte id) {
  // iterate vector of actors...
  for (int i = 0; i < m_numberOfGroups ; ++i) {
    // ... and check all of them
    if (m_groups[i]->toggle(id)) {
      // until one of them matches
      return;
    }
  }
}

void GroupBundle::switchGroup(const byte id, bool toState) {
  // iterate vector of actors...
  for (int i = 0; i < m_numberOfGroups ; ++i) {
    // ... and check all of them
    if (m_groups[i]->switchGroup(id, toState)) {
      // until one of them matches
      return;
    }
  }
}

static unsigned long GroupBundle::triState2Decimal(const char *sCodeWord) {
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


