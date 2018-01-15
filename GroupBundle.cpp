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
  RcActor *garden1 = new RcActor(this, sender, "00F000000FFF", "00F000000FF0"); // Garten-Steckdose I
  RcActor *garden2 = new RcActor(this, sender, "00F0FF000FFF", "00F0FF000FF0"); // Garten-Steckdose II
  RcActor *garden3 = new RcActor(this, sender, "00F0F0000FFF", "00F0F0000FF0"); // Garten-Steckdose III

  // living room
  RcActor *living1 = new RcActor(this, sender, "000000FFFF0F", "000000FFFFF0"); // Stehlampe
  RcActor *living2 = new RcActor(this, sender, "00000F0FFF0F", "00000F0FFFF0"); // Eiswürfel
  RcActor *living3 = new RcActor(this, sender, "00000FF0FF0F", "00000FF0FFF0"); // Vitrine

  // Group 1 garden (DIP 01111, switch A)
  GroupActor *groupGarden1 = new GroupActor(this, 30, 1, "F00000FFFF0F", "F00000FFFFF0"); // Alle Gartendosen gleichzeitig
  // Group 2 garden (DIP 01111, switch B)
  GroupActor *groupGarden2 = new GroupActor(this, 31, 1, "F0000F0FFF0F", "F0000F0FFFF0"); // Brunnen
  // Group 3 garden (DIP 01111, switch C)
  GroupActor *groupGarden3 = new GroupActor(this, 32, 1, "F0000FF0FF0F", "F0000FF0FFF0"); // Lampe
  // Group 4 garden (DIP 01111, switch D)
  GroupActor *groupGarden4 = new GroupActor(this, 33, 1, "F0000FFF0F0F", "F0000FFF0FF0"); // Steckdose

  // Group 1 living room (DIP 00111, switch A)
  GroupActor *groupLivingRoom1 = new GroupActor(this, 40, 2, "FF0000FFFF0F", "FF0000FFFFF0"); // Stehlampe
  // Group 2 living room (DIP 00111, switch B)
  GroupActor *groupLivingRoom2 = new GroupActor(this, 41, 2, "FF000F0FFF0F", "FF000F0FFFF0"); // Eiswürfel
  // Group 3 living room (DIP 00111, switch C)
  GroupActor *groupLivingRoom3 = new GroupActor(this, 42, 2, "FF000FF0FF0F", "FF000FF0FFF0"); // Vitrine
  // Group 4 living room (DIP 00111, switch D)
  GroupActor *groupLivingRoom4 = new GroupActor(this, 43, 2, "FF000FFF0F0F", "FF000FFF0FF0"); // Stehlampe und Eiswürfel

  // fill garden groups with actors
  groupGarden1->addActor(garden1)->addActor(garden2)->addActor(garden3);
  groupGarden2->addActor(garden1);
  groupGarden3->addActor(garden2);
  groupGarden4->addActor(garden3);

  // fill living room groups with actors
  groupLivingRoom1->addActor(living1);
  groupLivingRoom2->addActor(living2);
  groupLivingRoom3->addActor(living3);
  groupLivingRoom4->addActor(living1)->addActor(living2);
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

void GroupBundle::handleSwitchCode(unsigned long code) const {
  // iterate vector of actors...
  for (int i = 0; i < m_numberOfActors ; ++i) {
    // ... and check all of them
    if (m_actors[i]->matchesCode(code)) {
      // until one of them matches
      return;
    }
  }
}

void GroupBundle::printConfig(GroupPresenter& presenter) {
  presenter.print();
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

