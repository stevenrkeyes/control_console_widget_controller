#ifndef TRELLIS_H
#define TRELLIS_H

#include "ConsoleWidget.h"

class Trellis : public ConsoleWidget {
public:
  Trellis();
  void setup() override;
  void CheckDataSendHID() override;
  void UpdateAnimationFrame() override;

private:
};

#endif
