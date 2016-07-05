/**
 * Author: Lothar Wendehals - lothar.wendehals@itemis.de
 *
 * Eclipse Public License - v 1.0
 */
#ifndef TIMEEVENT_H_
#define TIMEEVENT_H_

#include "TimedStatemachineInterface.h"

class TimeEvent {

public:
	TimedStatemachineInterface *timedStatemachine;
	sc_eventid eventId;
	sc_boolean periodic;
	unsigned int overflows;
	unsigned int overflowCounter;
	bool eventRaised;
};

#endif /* TIMEEVENT_H_ */
