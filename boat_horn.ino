#include "event_manager.hpp"

// Global Variables
EventManager* manager;

void setup() {
	// put your setup code here, to run once:
  Serial.begin(9600);
  manager = new EventManager(2, 3);
  manager->loadTestSequence();
  manager->startSequence();
}

void loop() {
	// put your main code here, to run repeatedly:
	manager->checkAndPerformAction();
}

// Start and Stop instead of Activate/Silence
// ActionManager: currentTimeDS = millis() / 100;
// ActionManager: eventTimeDS = getFront()->offsetDS + startTime;
// The queue is a sequence of events
// insertAdvancedAction ==> addSound
// AdvancedAction timings should be constants
