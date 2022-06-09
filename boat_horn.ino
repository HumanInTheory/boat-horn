#include "action_manager.hpp"

// Global Variables
ActionManager* manager;

void setup() {
	// put your setup code here, to run once:
  Serial.begin(9600);
  manager = new ActionManager(2, 3);
  manager->loadTestSet();
  manager->startSet();
}

void loop() {
	// put your main code here, to run repeatedly:
	manager->checkAndPerformAction();
}
