#ifndef NOISE_CONTROLLER
#define NOISE_CONTROLLER

// Defines a pin controller intended for activating speakers/horns
class NoiseController {
private:
	int devicePin;

public:
	NoiseController(int _devicePin);
	~NoiseController();

	void activate();
	void silence();
};

#endif
