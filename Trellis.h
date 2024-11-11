#ifndef LED_TRELLIS_H
#define LED_TRELLIS_H

#include "ConsoleWidget.h"

class Trellis : public ConsoleWidget {
public:
  Trellis();
  void setup() override;
  void CheckDataSendHID() override;
  void UpdateAnimationFrame() override;

private:
  // TODO remove.
  bool was_high = false;
};

#endif
