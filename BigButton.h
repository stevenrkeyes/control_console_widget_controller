#ifndef BIG_BUTTON_H
#define BIG_BUTTON_H

#include "ConsoleWidget.h"
#include "GlobalState.h"

class BigButton : public ConsoleWidget {
  GlobalState& state;
public:
  BigButton(GlobalState& state);
  void setup() override;
  void CheckDataSendHID() override;
  void UpdateAnimationFrame() override;

private:
    bool _lastState;
};

#endif
