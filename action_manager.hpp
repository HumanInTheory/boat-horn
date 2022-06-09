#ifndef ACTION_MANAGER
#define ACTION_MANAGER

#include "action_deque.hpp"
#include "noise_controller.hpp"

#include <Arduino.h>

// Represents noise timings
enum AdvancedAction { BUZZER, SHORT_HORN, REGULAR_HORN, LONG_HORN };

// Defines an ActionManager which seperates action checks and performance from the main loop
class ActionManager {
private:
  ActionDeque *queue;
  NoiseController *hornController, *buzzerController;
  bool looping;
  bool active;
  int loopLength;
  unsigned long startTime;
public:
  ActionManager(int buzzerPin, int hornPin);
  ~ActionManager();

  unsigned long deciseconds();

  bool checkAndPerformAction();

  void insertAdvancedAction(unsigned int timeToStart, AdvancedAction toInsert);
  
  void loadTestSet();

  void startSet();
  bool isActive();
};

#endif
