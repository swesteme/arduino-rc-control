#ifndef LOOPHANDLER_HPP
#define LOOPHANDLER_HPP

#include "systemincludes.h"

class GroupBundle;

class LoopHandler {
  public:
    // constructor
    LoopHandler(GroupBundle *bundle, bool debugOutput) : m_bundle(bundle), m_debugOutput(debugOutput), m_errorState(false) {}

    // public method to start loop handling
    void loop();

    // retrieve error state
    bool isError() { return m_errorState; }

  protected:
    // internal loop method for subclasses
    virtual void loopInternal() = 0;
    // set error state, log message and highlight error LED
    void error(String message);
  protected:
    // group bundle pointer
    GroupBundle *m_bundle;
    // debug output desired?
    bool m_debugOutput;
    // the error state
    bool m_errorState;
};

#endif
