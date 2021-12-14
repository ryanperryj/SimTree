#pragma once
#include <math.h>

// integrates a signal using euler method
class Integrator {
public:
	Integrator(const float _y0, const float _dt) 
		: yPrev(_y0), dt(_dt) {}
	
	float Calculate(float u) {
		yPrev = yPrev + dt * u;
		return yPrev;
	}
private:
	float yPrev;
	const float dt;
};