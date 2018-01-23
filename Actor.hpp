//
//  Actor.hpp
//  Actor
//
//  Created by Sebastian Westemeyer on 06.01.18.
//

#ifndef Actor_hpp
#define Actor_hpp

class GroupBundle;

class Actor {
public:
    Actor(GroupBundle *bundle, unsigned long codeOn, unsigned long codeOff);
    
    // get actor name
    const char * getName() const;

    // switch actor on
    virtual void switchOn() = 0;

    // switch actor off
    virtual void switchOff() = 0;

    // check, whether a supplied code matches this actor
    bool matchesCode(unsigned long code);

    // convert tri-state to decimal
    static unsigned long triState2Decimal(const char *code);

private:
//    void setString(char **target, const char* source, int num);
    
protected:
    // code to switch on actor
    unsigned long m_codeOn;
    // code to switch off actor
    unsigned long m_codeOff;
};

#endif /* Actor_hpp */
