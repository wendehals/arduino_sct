/**
 * Author: Lothar Wendehals - lothar.wendehals@itemis.de
 *
 * Eclipse Public License - v 1.0
 */
#ifndef ATMEGA168_328TIMER_H_
#define ATMEGA168_328TIMER_H_

#include <Arduino.h>
#include <avr/sleep.h>
#include "AbstractTimer.h"

class ATmega168_328Timer: public AbstractTimer {
public:
	/* period in milliseconds */
	ATmega168_328Timer(StatemachineInterface* statemachine, HardwareConnector* hardware,
			unsigned short maxParallelTimeEvents, unsigned int period);

	inline virtual ~ATmega168_328Timer();

protected:
	virtual void init();

	virtual void sleep();

	virtual void stop();
};

ATmega168_328Timer::~ATmega168_328Timer() {
}

#endif /* ATMEGA168_328TIMER_H_ */
