/**
 * Author: Lothar Wendehals - lothar.wendehals@itemis.de
 *
 * Eclipse Public License - v 1.0
 */
#include "AbstractTimer.h"

volatile bool runCycleFlag = false;

/* period in milliseconds */
AbstractTimer::AbstractTimer(StatemachineInterface* statemachine, HardwareConnector* hardware,
		unsigned short maxParallelTimeEvents, unsigned int period) {
	this->statemachine = statemachine;
	this->hardware = hardware;
	this->maxParallelTimeEvents = maxParallelTimeEvents;
	this->period = period;

	this->events = new TimeEvent[this->maxParallelTimeEvents];
	for (unsigned short i = 0; i < this->maxParallelTimeEvents; i++) {
		this->events[i].eventId = NULL;
	}
}

AbstractTimer::~AbstractTimer() {
	delete this->events;
}

void AbstractTimer::start() {
	this->hardware->init();
	this->statemachine->init();
	this->statemachine->enter();
	this->init();
}

void AbstractTimer::setTimer(TimedStatemachineInterface* timedStatemachine, sc_eventid eventId, sc_integer duration,
		sc_boolean isPeriodic) {
	for (unsigned short i = 0; i < this->maxParallelTimeEvents; i++) {
		if (events[i].eventId == NULL) {
			events[i].timedStatemachine = timedStatemachine;
			events[i].eventId = eventId;
			events[i].overflows = duration / this->period;
			events[i].periodic = isPeriodic;
			events[i].overflowCounter = 0;
			events[i].eventRaised = false;
			break;
		}
	}
}

void AbstractTimer::unsetTimer(TimedStatemachineInterface* timedStatemachine, sc_eventid eventId) {
	for (unsigned short i = 0; i < this->maxParallelTimeEvents; i++) {
		if (events[i].eventId == eventId) {
			events[i].eventId = NULL;
			break;
		}
	}
}

void AbstractTimer::runCycle() {
	if (runCycleFlag) {
		this->raiseTimeEvents();
		this->statemachine->runCycle();
		this->hardware->runCycle();
		runCycleFlag = false;
	}
	this->sleep();
}

void AbstractTimer::raiseTimeEvents() {
	for (unsigned short i = 0; i < this->maxParallelTimeEvents; i++) {
		if (events[i].eventId == NULL) {
			continue;
		}

		if ((events[i].overflowCounter >= events[i].overflows) && !events[i].eventRaised) {
			events[i].timedStatemachine->raiseTimeEvent(events[i].eventId);
			events[i].overflowCounter = 0;

			if (!events[i].periodic) {
				events[i].eventRaised = true;
			}
		}

		events[i].overflowCounter++;
	}
}

void AbstractTimer::cancel() {
	this->stop();
}
