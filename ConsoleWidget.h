#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

class ConsoleWidget {
public:
  virtual void setup() = 0;
  virtual void CheckDataSendHID() = 0;
  virtual void UpdateAnimationFrame() = 0;
  virtual ~ConsoleWidget() = default;
};

#endif
