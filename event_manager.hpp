#ifndef EVENT_MANAGER
#define EVENT_MANAGER

#include "event_deque.hpp"
#include "noise_controller.hpp"

#include <Arduino.h>

// Represents noise timings
enum Sound { BUZZER, SHORT_HORN, REGULAR_HORN, LONG_HORN };

// Defines an ActionManager which seperates action checks and performance from the main loop
class EventManager {
private:
  EventDeque *queue;
  NoiseController *hornController, *buzzerController;
  bool looping;
  bool active;
  unsigned int loopLengthDS;
  unsigned long startTimeDS;
  unsigned long currentTimeDS;
public:
  EventManager(int buzzerPin, int hornPin);
  ~EventManager();

  unsigned long programTimeDS();

  bool checkAndPerformAction();

  void addSound(unsigned int startOffsetDS, Sound sound);
  
  void loadTestSequence();

  void startSequence();
  bool isActive();
};

#endif
