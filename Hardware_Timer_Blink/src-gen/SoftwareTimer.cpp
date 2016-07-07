/**
 * Author: Lothar Wendehals - lothar.wendehals@itemis.de
 *
 * Eclipse Public License - v 1.0
 */
#include "SoftwareTimer.h"

extern bool runCycleFlag;

SoftwareTimer::SoftwareTimer(StatemachineInterface* statemachine, HardwareConnector* hardware,
		unsigned short maxParallelTimeEvents, unsigned int period) :
		AbstractTimer(statemachine, hardware, maxParallelTimeEvents, period) {
	lastCycle = 0;
}

void SoftwareTimer::init() {
	lastCycle = millis();
}

void SoftwareTimer::runCycle() {
	unsigned long current = millis();
	if (current>=lastCycle+this->period){
		runCycleFlag = true;
		AbstractTimer::runCycle();
		lastCycle = current;
	}
}

void SoftwareTimer::sleep() {
	// nothing to do
}

void SoftwareTimer::stop() {
	// nothing to do
}
