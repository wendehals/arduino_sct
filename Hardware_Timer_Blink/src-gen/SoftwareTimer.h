/**
 * Author: Lothar Wendehals - lothar.wendehals@itemis.de
 *
 * Eclipse Public License - v 1.0
 */
#ifndef SRC_GEN_SOFTWARETIMER_H_
#define SRC_GEN_SOFTWARETIMER_H_

#include <Arduino.h>
#include "AbstractTimer.h"

class SoftwareTimer: public AbstractTimer {
public:
	SoftwareTimer(StatemachineInterface* statemachine, HardwareConnector* hardware,
			unsigned short maxParallelTimeEvents, unsigned int period);

	inline virtual ~SoftwareTimer();

	virtual void runCycle();

protected:
	virtual void init();

	virtual void sleep();

	virtual void stop();

private:
	unsigned long lastCycle;
};

SoftwareTimer::~SoftwareTimer(){
}

#endif /* SRC_GEN_SOFTWARETIMER_H_ */
