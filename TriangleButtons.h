#ifndef TRIANGLEBUTTONS_H
#define TRIANGLEBUTTONS_H

#include "limits.h"
#include <Bounce2.h>
#include "ConsoleWidget.h"
#include "pins.h"

#define TRIANGLE_BUTTONS_NUM 6

constexpr int TRIANGLE_BUTTONS_PINS[] = { TRIANGLE_BUTTONS_BUTTON1_PIN,
                                          TRIANGLE_BUTTONS_BUTTON2_PIN,
                                          TRIANGLE_BUTTONS_BUTTON3_PIN,
                                          TRIANGLE_BUTTONS_BUTTON4_PIN,
                                          TRIANGLE_BUTTONS_BUTTON5_PIN,
                                          TRIANGLE_BUTTONS_BUTTON6_PIN };

constexpr int TRIANGLE_BUTTONS_LED_PINS[] = { TRIANGLE_BUTTONS_LED1_PIN,
                                              TRIANGLE_BUTTONS_LED2_PIN,
                                              TRIANGLE_BUTTONS_LED3_PIN,
                                              TRIANGLE_BUTTONS_LED4_PIN,
                                              TRIANGLE_BUTTONS_LED5_PIN,
                                              TRIANGLE_BUTTONS_LED6_PIN };

class TriangleButtons : public ConsoleWidget {
public:
  TriangleButtons();
  void setup() override;
  void CheckDataSendHID() override;
  void UpdateAnimationFrame() override;

private:
  bool activated[TRIANGLE_BUTTONS_NUM] = { false };
  unsigned long pressTimesMs[TRIANGLE_BUTTONS_NUM] = { ULONG_MAX };
  Bounce buttons[TRIANGLE_BUTTONS_NUM];
};

#endif
