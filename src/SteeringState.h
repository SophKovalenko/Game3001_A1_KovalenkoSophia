#pragma once
#ifndef __STEERING_STATE__
#define __STEERING_STATE__
enum SteeringState {
	IDLE,
	SEEK,
	FLEE,
	ARRIVE,
	AVOID,
	NUM_OF_STATES
};

#endif /*defined (__STEERING_STATE__*/
