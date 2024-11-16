#ifndef LEVER_H
#define LEVER_H

#include "ConsoleWidget.h"

constexpr int LEVER_BUTTON = 7;

class Lever : public ConsoleWidget {
public:
  Lever();
  void setup() override;
  void CheckDataSendHID() override;
  void UpdateAnimationFrame() override;

private:
    // Maybe not needed?
    bool _lastState;
};

#endif
