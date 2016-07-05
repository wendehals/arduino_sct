/**
 * Author: Lothar Wendehals - lothar.wendehals@itemis.de
 *
 * Eclipse Public License - v 1.0
 */
#include "Hardware_Timer_Blink.h"

#define PERIOD 10
#define MAX_PARALLEL_TIMERS 2

Sct_blink* statemachine;
Sct_blinkConnector* connector;
ATmega168_328Timer* timer;

void setup() {
	statemachine = new Sct_blink();
	connector = new Sct_blinkConnector(statemachine);
	timer = new ATmega168_328Timer(statemachine, connector, MAX_PARALLEL_TIMERS, PERIOD);

	statemachine->setTimer(timer);
	timer->start();
}

void loop() {
	timer->runCycle();
}

