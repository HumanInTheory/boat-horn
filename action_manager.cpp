#include "action_manager.hpp"

// Initializes the Deque and NoiseControllers, and sets the other values to defaults
ActionManager::ActionManager(int buzzerPin, int hornPin) {
  queue = new ActionDeque();
  hornController = new NoiseController(buzzerPin);
  buzzerController = new NoiseController(hornPin);
  looping = false;
  active = false;
  loopLength = 0;
  startTime = 0;
}

// Returns the time since the program started in tenths of a second
unsigned long ActionManager::deciseconds() {
  return (unsigned long)( millis() / 100 );
}

// If the manager is active, checks if it is time to perform the next action in the Deque
// If it is time, call the relevant function then delete the ActionNode, placing it at end if looping
bool ActionManager::checkAndPerformAction() {
  if (!active) {
    return false;
  }
  
  Action toPerform = queue->getFrontAction();
  unsigned int timing = queue->getFrontTime();
  
  if ( ( timing + startTime ) < deciseconds() ) {
    Serial.println("Will perform " + String(toPerform) + " at " + String( timing + startTime ));
    return false;
  }

  switch(toPerform) {
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

  Serial.println("Performed " + String(toPerform) + " at " + String( millis() / 100 ));

  queue->deleteFront();

  if (looping) {
    queue->insertRear(timing + loopLength, toPerform);
  }

  return true;
}

// Inserts an on and off action, with timing based on the input AdvancedAction
void ActionManager::insertAdvancedAction(unsigned int decisecondsToStart, AdvancedAction toInsert) {
  switch(toInsert) {
    case BUZZER:
      queue->insertRear(decisecondsToStart, ACTIVATE_BUZZER);
      queue->insertRear(decisecondsToStart + 2, SILENCE_BUZZER);
      break;
    case SHORT_HORN:
      queue->insertRear(decisecondsToStart, ACTIVATE_HORN);
      queue->insertRear(decisecondsToStart + 5, SILENCE_HORN);
      break;
    case REGULAR_HORN:
      queue->insertRear(decisecondsToStart, ACTIVATE_HORN);
      queue->insertRear(decisecondsToStart + 10, SILENCE_HORN);
      break;
    case LONG_HORN:
      queue->insertRear(decisecondsToStart, ACTIVATE_HORN);
      queue->insertRear(decisecondsToStart + 15, SILENCE_HORN);
      break;
  }
}

/*
 * Clears the ActionDeque, then loads a new set of Actions
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

void ActionManager::loadTestSet() {
  // Clear queue, disable looping
  queue->erase();
  looping = false;
  
  // Beep, then play 3 warning beeps followed by each horn (short, long, extra long)
  insertAdvancedAction(0, BUZZER);
  insertAdvancedAction(560, BUZZER);
  insertAdvancedAction(570, BUZZER);
  insertAdvancedAction(580, BUZZER);
  insertAdvancedAction(590, BUZZER);
  insertAdvancedAction(600, SHORT_HORN);
  insertAdvancedAction(1160, BUZZER);
  insertAdvancedAction(1170, BUZZER);
  insertAdvancedAction(1180, BUZZER);
  insertAdvancedAction(1190, BUZZER);
  insertAdvancedAction(1200, REGULAR_HORN);
  insertAdvancedAction(1760, BUZZER);
  insertAdvancedAction(1770, BUZZER);
  insertAdvancedAction(1780, BUZZER);
  insertAdvancedAction(1790, BUZZER);
  insertAdvancedAction(1800, LONG_HORN);
}

// Sets a new start time and activates the manager
void ActionManager::startSet() {
  startTime = (millis() / 100);
  active = true;
  Serial.println("Activated set at: " + String(startTime));
}

bool ActionManager::isActive() {
  return active;
}
