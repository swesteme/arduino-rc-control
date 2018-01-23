//
//  GroupActor.hpp
//  GroupActor
//
//  Created by Sebastian Westemeyer on 06.01.18.
//

#ifndef GroupActor_hpp
#define GroupActor_hpp

#include <RCSwitch.h>

#include "Actor.hpp"

class GroupBundle;

class GroupActor : public Actor {
public:
    GroupActor(GroupBundle *bundle, const byte id, const byte section, unsigned long codeOn, unsigned long codeOff);

    // get bundle id
    const byte getId() const;
    
    // get bundle section id
    const byte getSectionId() const;
    
    // switch actor on
    virtual void switchOn();

    // switch actor off
    virtual void switchOff();

    // add an additional actor to group
    GroupActor* addActor(Actor *newActor);

    // toggle state
    bool toggle(const byte id);

    // switch this group to a state if it matches
    bool switchGroup(const byte id, bool toState);

// private methods
private:

// private members
private:
    // group actor id
    const byte m_id;
    // webservice section key
    const byte m_section;
    
    // list of actors in this group
    Actor** m_actors;
    // number of items in list of actors
    int m_numberOfActors;

    // current group state
    bool m_state;
};

#endif /* GroupActor_hpp */
