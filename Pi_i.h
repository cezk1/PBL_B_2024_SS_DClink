#pragma once
#ifndef PII_H_
#define PII_H_

#include <math.h>

struct PI_STRUCT {
	float proportional;
	float integrator;
	float kp;
	float out;
	float integrator_prev;
	float x_ki;
	float out_limit;
	float y_1;
	float Ts;
	float T;
	float min;
	float max;
};

void Pi_Init(struct PI_STRUCT* Pi, float Ts, float kp, float T, float min, float max);
void Pi_Calc(struct PI_STRUCT* Pi, float x, float x_zmierzone);
void Pi_Reset(struct PI_STRUCT* Pi);

#endif /* PII_H_ */