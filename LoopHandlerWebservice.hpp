#ifndef LOOP_HANDLER_WS
#define LOOP_HANDLER_WS

#include <NanoESP.h>
#include <NanoESP_HTTP.h>

#include "LoopHandler.hpp"

class LoopHandlerWebservice : public LoopHandler {
  public:
    LoopHandlerWebservice(GroupBundle* bundle, bool debugOutput);

  protected:
    virtual void loopInternal();

  private:
    NanoESP m_nanoesp;
    NanoESP_HTTP m_http;
};

#endif

