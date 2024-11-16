#ifndef TRELLIS_H
#define TRELLIS_H

#include "ConsoleWidget.h"
#include "GlobalState.h"

class Trellis : public ConsoleWidget {
  GlobalState& state;
public:
  Trellis(GlobalState& state);
  void setup() override;
  void CheckDataSendHID() override;
  void UpdateAnimationFrame() override;

private:
  void FlashRed();
};

#endif
