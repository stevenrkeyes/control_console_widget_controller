#ifndef BIG_BUTTON_H
#define BIG_BUTTON_H

#include "ConsoleWidget.h"

class BigButton : public ConsoleWidget {
public:
  BigButton();
  void setup() override;
  void CheckDataSendHID() override;
  void UpdateAnimationFrame() override;

private:
    bool _lastState;
};

#endif
