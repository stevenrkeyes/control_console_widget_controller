#ifndef ORB_READER_H
#define ORB_READER_H

#include "ConsoleWidget.h"
#include "pins.h"

class OrbReader : public ConsoleWidget {
public:
  OrbReader();
  void setup() override;
  void CheckDataSendHID() override;
  void UpdateAnimationFrame() override;
private:
  bool _orb_inserted = false;
};

#endif
