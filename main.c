#include "DllHeader.h"
#include "Pi_i.h"


DLLEXPORT void plecsSetSizes(struct SimulationSizes* aSizes)
{
   aSizes->numInputs = 3;
   aSizes->numOutputs = 1;
   aSizes->numStates = 0;
   aSizes->numParameters = 1; //number of user parameters passed in
}

struct PI_STRUCT pi_current, pi_voltage;
double sampling_time_Ts;
float kp_i = 0.02;
float Ti_i = 320/0.02;
float min_i = 0;
float max_i = 0.5;

float kp_v = 0.5;
float Ti_v = 100;
float min_v = 0;
float max_v = 1;

//This function is automatically called at the beginning of the simulation
DLLEXPORT void plecsStart(struct SimulationState* aState)
{
	//Example error message box
	//if (aState->parameters[0] < 0 )
	//	aState->errorMessage = "kp cannot be less than 0";
	
	sampling_time_Ts = aState->parameters[0];

	Pi_Init(&pi_current, sampling_time_Ts, kp_i, Ti_i, min_i, max_i); // regulator pradu
	Pi_Init(&pi_voltage, sampling_time_Ts, kp_v, Ti_v, min_v, max_v); // regulator napiecia

}


//This function is automatically called every sample time
//output is written to DLL output port after the output delay
DLLEXPORT void plecsOutput(struct SimulationState* aState)
{
	/*
	inputs[0] - napiecie zadane
	inputs[1] - napiecie zmierzone
	inputs[2] - prad zmierzony
	*/

	Pi_Calc(&pi_voltage, aState->inputs[0], aState->inputs[1]);
	Pi_Calc(&pi_current, pi_voltage.out_limit, aState->inputs[2]);

	aState->outputs[0] = pi_current.out_limit;

}
