/**
 * Author: Lothar Wendehals - lothar.wendehals@itemis.de
 *
 * Eclipse Public License - v 1.0
 */
#ifndef ABSTRACTTIMER_H_
#define ABSTRACTTIMER_H_

#include <stdio.h>
#include "sc_types.h"
#include "TimerInterface.h"
#include "StatemachineInterface.h"
#include "TimedStatemachineInterface.h"
#include "TimeEvent.h"
#include "HardwareConnector.h"

class AbstractTimer: public TimerInterface {

public:
	/* period in milliseconds */
	AbstractTimer(StatemachineInterface* statemachine, HardwareConnector* hardware,
			unsigned short maxParallelTimeEvents, unsigned int period);

	virtual ~AbstractTimer();

	void start();

	void setTimer(TimedStatemachineInterface* timedStatemachine, sc_eventid eventId, sc_integer time,
			sc_boolean isPeriodic);

	void unsetTimer(TimedStatemachineInterface* timedStatemachine, sc_eventid eventId);

	virtual void runCycle();

	void cancel();

protected:
	StatemachineInterface* statemachine;

	HardwareConnector* hardware;

	unsigned int period;

	virtual void init() = 0;

	virtual void sleep() = 0;

	virtual void stop() = 0;

private:
	unsigned short maxParallelTimeEvents;

	TimeEvent* events;

	void raiseTimeEvents();
};

#endif /* ABSTRACTTIMER_H_ */
