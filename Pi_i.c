#include "Pi_i.h"

void Pi_Init(struct PI_STRUCT* Pi, float Ts, float kp, float T, float min, float max) {
    Pi->out_limit = 0;
    Pi->out = 0;
    Pi->integrator_prev = 0;
    Pi->x_ki = 0;
    Pi->integrator = 0;
    Pi->proportional = 0;
    Pi->kp = kp;
    Pi->Ts = Ts;
    Pi->T = T; // stała czasowa
    Pi->min = min;
    Pi->max = max;
}

void Pi_Calc(struct PI_STRUCT* Pi, float x, float x_zmierzone) {
	//czlon proporcjonalny
	Pi->proportional = (x - x_zmierzone) * Pi->kp;
	
	// clamping
	if ((Pi->out - Pi->out_limit) > 0) { // przy wartościach typu float nie daje sie "=="
		Pi->x_ki = 0;
	}
	else if ((Pi->out - Pi->out_limit) < 0) {
		Pi->x_ki = 0;
	}
	else {
		Pi->x_ki = Pi->proportional; 
	}

	//czlon calkujacy
	Pi->integrator = Pi->x_ki * Pi->Ts * Pi->T + Pi->integrator_prev;
	Pi->integrator_prev = Pi->integrator; // poprzednia próbka

	//wyjscie
	Pi->out = Pi->proportional + Pi->integrator;

	// saturacja
	Pi->out_limit = Pi->out;
	if (Pi->out > Pi->max) {
		Pi->out_limit = Pi->max;
	}
	else if (Pi->out < Pi->min) {
		Pi->out_limit = Pi->min;
	}
}


void Pi_Reset(struct PI_STRUCT* Pi) {
	Pi->out_limit = 0;
	Pi->out = 0;
	Pi->integrator_prev = 0;
	Pi->x_ki = 0;
	Pi->integrator = 0;
	Pi->proportional = 0;
}