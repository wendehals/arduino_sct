#include "Arduino.h"
#include "libs/sc_timer_service.h"
#include "src-gen/Sct_blink.h"
#include "src-gen/Sct_blinkRequired.h"

#define MAX_TIMERS 1
#define CYCLE_PERIOD (10)

const int led_pin = 13;

static unsigned long cycle_count = 0L;
static unsigned long last_cycle_time = 0L;

static Sct_blink sct_blink;
static sc_timer_t timers[MAX_TIMERS];
static sc_timer_service_t timer_service;

void sct_blink_setTimer(Sct_blink* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic) {
	sc_timer_start(&timer_service, handle, evid, time_ms, periodic);
}

void sct_blink_unsetTimer(Sct_blink* handle, const sc_eventid evid) {
	sc_timer_cancel(&timer_service, evid);
}
// runCycle() and connection to hardware
static void execute_cycle() {
	sct_blink_runCycle(&sct_blink);

	digitalWrite(led_pin, sct_blinkIface_get_on(&sct_blink));
}

// The setup function is called once at startup of the sketch
void setup() {
	// set up the pins on arduino
	pinMode(led_pin, OUTPUT);

	// We initialize the timer service with everything it requires.
	sc_timer_service_init(&timer_service, timers, MAX_TIMERS,
			(sc_raise_time_event_fp) &sct_blink_raiseTimeEvent);

	// initialize the state machine
	sct_blink_init(&sct_blink);

	// enter the state machine
	sct_blink_enter(&sct_blink);

	// enable interrupts
	sei();
}

// The loop function is called in an endless loop
void loop() {
	unsigned long current_millies = millis();
	if (cycle_count == 0L || (current_millies >= last_cycle_time + CYCLE_PERIOD)) {
		sc_timer_service_proceed(&timer_service, current_millies - last_cycle_time);
		execute_cycle();
		last_cycle_time = current_millies;
		cycle_count++;
	}

	// reenable interrupts
	sei();
}
