// TODO: Also use GlobalState here
#ifndef TRELLIS_H
#define TRELLIS_H

#include "ConsoleWidget.h"
#include "GlobalState.h" 

class Trellis : public ConsoleWidget {
  GlobalState& state;
public:
  Trellis(GlobalState& state);
  
  // ConsoleWidget interface implementations
  void setup() override;
  void CheckDataSendHID() override;
  void UpdateAnimationFrame() override;

  // Snake game public interface
  void DrawSnake();      // Renders current game state
  void ResetSnake();     // Resets game to initial state
  void StartSnake();     // Initializes and starts new game
  void initializeSnake(); // Initializes snake vector
  // Game control methods
  void setDirection(char direction); // Sets movement direction
  bool isGameActive() const { return _gameActive; }
private:
  uint32_t _lastMoveTime = 0;
  bool _gameActive = true;
  char _direction;
};

#endif
