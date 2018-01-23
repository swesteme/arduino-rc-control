//
//  RcActor.hpp
//  RcActor
//
//  Created by Sebastian Westemeyer on 06.01.18.
//

#ifndef RcActor_hpp
#define RcActor_hpp

#include <RCSwitch.h>

#include "Actor.hpp"

class RcActor : public Actor {
public:
    RcActor(GroupBundle *bundle, const RCSwitch* sender, unsigned long codeOn, unsigned long codeOff);
    
    // switch actor on
    virtual void switchOn();

    // switch actor off
    virtual void switchOff();

// private methods
private:
    void sendCode(unsigned long code);

// private members
private:
    // RC sender reference
    RCSwitch* m_sender;
};

#endif /* RcActor_hpp */
