/**
 * Author: Lothar Wendehals - lothar.wendehals@itemis.de
 *
 * Eclipse Public License - v 1.0
 */
#include "ATmega168_328Timer.h"

extern bool runCycleFlag;

ISR(TIMER1_COMPA_vect) {
	runCycleFlag = true;
}

ATmega168_328Timer::ATmega168_328Timer(StatemachineInterface* statemachine, HardwareConnector* hardware,
		unsigned short maxParallelTimeEvents, unsigned int period) :
		AbstractTimer(statemachine, hardware, maxParallelTimeEvents, period) {
}

void ATmega168_328Timer::init() {
	// initialize Timer1
	noInterrupts();
	TCCR1A = 0;     // set entire TCCR1A register to 0
	TCCR1B = 0;     // same for TCCR1B

	// set compare match register to desired timer count:
	// period in ms, Arduino runs at 16 MHz, prescaler at 1024
	OCR1A = (this->period * 0.001f * (16000000 / 1024)) - 1;

	// turn on CTC mode
	TCCR1B |= (1 << WGM12);

	// Set CS10 and CS12 bits for 1024 prescaler
	TCCR1B |= (1 << CS10);
	TCCR1B |= (1 << CS12);

	// enable timer compare interrupt
	TIMSK1 |= (1 << OCIE1A);

	// enable global interrupts
	interrupts();
}

void ATmega168_328Timer::sleep() {
	set_sleep_mode(SLEEP_MODE_IDLE);
	noInterrupts();
	sleep_enable();
	interrupts();
	sleep_cpu();
	sleep_disable();
}

void ATmega168_328Timer::stop() {
	TCCR1B = 0; // turn off the timer
}
