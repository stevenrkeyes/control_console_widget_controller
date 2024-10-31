#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

class ConsoleWidget {
public:
  virtual void setup() = 0;
  virtual void CheckDataSendMIDI() = 0;
  virtual void UpdateAnimationFrame() = 0;
  virtual ~ConsoleWidget() = default;
};

#endif
