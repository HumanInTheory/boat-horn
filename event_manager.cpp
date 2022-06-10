#include "event_manager.hpp"

// Initializes the Deque and NoiseControllers, and sets the other values to defaults
EventManager::EventManager(int buzzerPin, int hornPin) {
  queue = new EventDeque();
  buzzerController = new NoiseController(buzzerPin);
  hornController = new NoiseController(hornPin);
  looping = false;
  active = false;
  loopLengthDS = 0;
  startTimeDS = 0;
  currentTimeDS = 0;
}

// Returns the time since the program started in tenths of a second
unsigned long EventManager::programTimeDS() {
  return (unsigned long)( millis() / 100 );
}

// If the manager is active, checks if it is time to perform the next event in the Deque
// If it is time, call the relevant function then delete the EventNode, placing it at end if looping
bool EventManager::checkAndPerformAction() {
  if (!active || currentTimeDS == programTimeDS()) {
    return false;
  }

  EventNode* nextEvent = queue->getFront();
  unsigned long nextEventTimeDS = (unsigned long)( nextEvent->offsetDS + startTimeDS );
  currentTimeDS = programTimeDS();
  
  if (  currentTimeDS < nextEventTimeDS ) {
    Serial.println("Will perform " + String(nextEvent->event) + " at " + String(nextEventTimeDS));
    return false;
  }

  switch(nextEvent->event) {
    case ACTIVATE_BUZZER:
      buzzerController->activate();
      break;
    case ACTIVATE_HORN:
      hornController->activate();
      break;
    case SILENCE_BUZZER:
      buzzerController->silence();
      break;
    case SILENCE_HORN:
      hornController->silence();
      break;
    case NONE:
    default:
      // Do nothing
      break;
  }

  Serial.println("Performed " + String(nextEvent->event) + " at " + String(currentTimeDS));

  if (looping) {
    queue->insertRear(nextEvent->offsetDS, nextEvent->event);
  }

  nextEvent = NULL; // Delete the reference
  queue->deleteFront(); // Delete the node

  return true;
}

// Inserts an on and off action, with timing based on the input AdvancedAction
void EventManager::addSound(unsigned int startOffsetDS, Sound sound) {
  switch(sound) {
    case BUZZER:
      queue->insertRear(startOffsetDS, ACTIVATE_BUZZER);
      queue->insertRear(startOffsetDS + 2, SILENCE_BUZZER);
      break;
    case SHORT_HORN:
      queue->insertRear(startOffsetDS, ACTIVATE_HORN);
      queue->insertRear(startOffsetDS + 5, SILENCE_HORN);
      break;
    case REGULAR_HORN:
      queue->insertRear(startOffsetDS, ACTIVATE_HORN);
      queue->insertRear(startOffsetDS + 10, SILENCE_HORN);
      break;
    case LONG_HORN:
      queue->insertRear(startOffsetDS, ACTIVATE_HORN);
      queue->insertRear(startOffsetDS + 15, SILENCE_HORN);
      break;
  }
}

/*
 * Clears the EventDeque, then loads a new set of Events
 * 0:00 - Beep
 * 0:56 - Beep
 * 0:57 - Beep
 * 0:58 - Beep
 * 0:59 - Beep
 * 1:00 - 0.5 second blast
 * 1:56 - Beep
 * 1:57 - Beep
 * 1:58 - Beep
 * 1:59 - Beep
 * 2:00 - 1 second blast
 * 2:56 - Beep
 * 2:57 - Beep
 * 2:58 - Beep
 * 2:59 - Beep
 * 3:00 - 1.5 second blast
 */

void EventManager::loadTestSequence() {
  // Clear queue, disable looping
  queue->erase();
  looping = false;
  
  // Beep, then play 3 warning beeps followed by each horn (short, long, extra long)
  addSound(0, BUZZER);
  addSound(560, BUZZER);
  addSound(570, BUZZER);
  addSound(580, BUZZER);
  addSound(590, BUZZER);
  addSound(600, SHORT_HORN);
  addSound(1160, BUZZER);
  addSound(1170, BUZZER);
  addSound(1180, BUZZER);
  addSound(1190, BUZZER);
  addSound(1200, REGULAR_HORN);
  addSound(1760, BUZZER);
  addSound(1770, BUZZER);
  addSound(1780, BUZZER);
  addSound(1790, BUZZER);
  addSound(1800, LONG_HORN);
}

// Sets a new start time and activates the manager
void EventManager::startSequence() {
  startTimeDS = programTimeDS();
  currentTimeDS = 0;
  active = true;
  Serial.println("Activated sequence at: " + String(startTimeDS));
}

bool EventManager::isActive() {
  return active;
}
