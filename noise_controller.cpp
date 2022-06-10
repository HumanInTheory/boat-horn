#include "noise_controller.hpp"

#include <Arduino.h>

NoiseController::NoiseController(int _devicePin) : devicePin(_devicePin) {
	pinMode(devicePin, OUTPUT);
}

NoiseController::~NoiseController() {}

void NoiseController::activate() {
	tone(devicePin, 440);
}

void NoiseController::silence() {
	noTone(devicePin);
}
