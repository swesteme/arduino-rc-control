//
//  GroupBundle.hpp
//  GroupBundle
//
//  Created by Sebastian Westemeyer on 06.01.18.
//

#ifndef GroupBundle_hpp
#define GroupBundle_hpp

#include "systemincludes.h"

class Actor;
class GroupActor;
class RCSwitch;
class GroupPresenter;

class GroupBundle {
public:
    GroupBundle(RCSwitch *sender);

    // add a new group
    void addGroup(GroupActor *actor);
    
    // add a new actor
    void addActor(Actor *actor);

    // toggle the given actor
    void toggle(const byte id);
    
    // handle switch by code
    void handleSwitchCode(unsigned long code) const;

    // print current JSON configuration
    void printConfig(GroupPresenter& presenter);

private:
    // actor list
    Actor** m_actors;
    // group actor list
    GroupActor** m_groups;

    // number of actors
    int m_numberOfActors;
    // number of groups
    int m_numberOfGroups;
};

#endif /* GroupBundle_hpp */
