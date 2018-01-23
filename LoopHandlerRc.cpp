#include <RCSwitch.h>

#include "LoopHandlerRc.hpp"
#include "GroupBundle.hpp"

LoopHandlerRc::LoopHandlerRc(GroupBundle* bundle, bool debugOutput, RCSwitch *sender) : LoopHandler(bundle, debugOutput), m_sender(sender) {
  // sender settings
  m_sender->enableTransmit(6); //Pin D6
  m_sender->setProtocol(1);
  m_sender->setPulseLength(321);
  // receiver settings
  m_sender->enableReceive(digitalPinToInterrupt(2));  // Receiver on interrupt 0 => that is pin #2
}

void LoopHandlerRc::loopInternal() {
  // check, whether new rc input is available
  if (m_sender->available()) {
    if (m_debugOutput) {
      dec2tristate(m_sender->getReceivedValue(), m_sender->getReceivedBitlength(), m_sender->getReceivedDelay(), m_sender->getReceivedProtocol());
    }

    // check group bundle for codes
    m_bundle->handleSwitchCode(m_sender->getReceivedValue());

    // reset state
    m_sender->resetAvailable();
  }
}


static const char* LoopHandlerRc::dec2tristate(unsigned long decimal, unsigned int length, unsigned int delay, unsigned int protocol) {
  const char* b = dec2binWzerofill(decimal, length);
  const char *t = bin2tristate(b);
  Serial.print("Decimal: ");
  Serial.print(decimal);
  Serial.print(" (");
  Serial.print( length );
  Serial.print("Bit) Binary: ");
  Serial.print( b );
  Serial.print(" Tri-State: ");
  Serial.print( t );
  Serial.print(" PulseLength: ");
  Serial.print(delay);
  Serial.print(" microseconds");
  Serial.print(" Protocol: ");
  Serial.println(protocol);

  return t;
}

static const char* LoopHandlerRc::bin2tristate(const char* bin) {
  static char returnValue[50];
  int pos = 0;
  int pos2 = 0;
  while (bin[pos]!='\0' && bin[pos+1]!='\0') {
    if (bin[pos]=='0' && bin[pos+1]=='0') {
      returnValue[pos2] = '0';
    } else if (bin[pos]=='1' && bin[pos+1]=='1') {
      returnValue[pos2] = '1';
    } else if (bin[pos]=='0' && bin[pos+1]=='1') {
      returnValue[pos2] = 'F';
    } else {
      return "not applicable";
    }
    pos = pos+2;
    pos2++;
  }
  returnValue[pos2] = '\0';
  return returnValue;
}

static char * LoopHandlerRc::dec2binWzerofill(unsigned long Dec, unsigned int bitLength) {
  static char bin[64]; 
  unsigned int i=0;

  while (Dec > 0) {
    bin[32+i++] = ((Dec & 1) > 0) ? '1' : '0';
    Dec = Dec >> 1;
  }

  for (unsigned int j = 0; j< bitLength; j++) {
    if (j >= bitLength - i) {
      bin[j] = bin[ 31 + i - (j - (bitLength - i)) ];
    } else {
      bin[j] = '0';
    }
  }
  bin[bitLength] = '\0';
  
  return bin;
}

