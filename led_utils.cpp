#include "led_utils.h"

unsigned char RampToValue(char startValue, char endValue, long endTime, long currentTime) {
  if (currentTime < 0) {
    return 0;
  } else if (currentTime >= 0 && currentTime < endTime) {
    // Interpolate on the line from (0, startValue) to (endTime, endValue)
    return (unsigned char)(startValue - (1.0 * (startValue - endValue) * currentTime / endTime));
  } else {
    return endValue;
  }
}
