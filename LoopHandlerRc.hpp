#ifndef LOOP_HANDLER_RC
#define LOOP_HANDLER_RC

#include "LoopHandler.hpp"

class RCSwitch;

class LoopHandlerRc : public LoopHandler {
  public:
    LoopHandlerRc(GroupBundle* bundle, bool debugOutput, RCSwitch *sender);

    // methods taken from RCSwitch example code
    static const char* dec2tristate(unsigned long decimal, unsigned int length, unsigned int delay, unsigned int protocol);
    static const char* bin2tristate(const char* bin);
    static char * dec2binWzerofill(unsigned long Dec, unsigned int bitLength);
    
  protected:
    // internal loop method
    virtual void loopInternal();

  private:
    RCSwitch *m_sender;
};

#endif

