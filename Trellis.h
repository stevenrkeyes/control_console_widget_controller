#ifndef TRELLIS_H
#define TRELLIS_H

#include "ConsoleWidget.h"

// TODO define trellis note use.

class Trellis : public ConsoleWidget {
public:
  Trellis();
  void setup() override;
  void CheckDataSendMIDI() override;
  void UpdateAnimationFrame() override;

private:
  // TODO remove.
  bool was_high = false;
};

#endif
