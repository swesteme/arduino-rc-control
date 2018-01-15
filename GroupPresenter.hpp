#ifndef GROUP_PRESENTER_H
#define GROUP_PRESENTER_H

#include "Arduino.h"

class NanoESP_HTTP;

class GroupPresenter {
  public:
    // print content
    virtual void print() = 0;
};

class OutputPresenter : public GroupPresenter {
  public:
    // print content
    virtual void print();
};

class WebservicePresenter : public GroupPresenter {
  public:
    // constructor
    WebservicePresenter(int client, NanoESP_HTTP* nanoEsp);
    // print content
    virtual void print();

  private:
    // client number
    int m_client;
    // service object
    NanoESP_HTTP* m_nanoEsp;
};

#endif

