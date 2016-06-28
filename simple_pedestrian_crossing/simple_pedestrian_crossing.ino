#include "Arduino.h"

#include "libs/sc_timer_service.h"
#include "src-gen/Simple_pedestrian_crossing.h"
#include "src-gen/Simple_pedestrian_crossingRequired.h"

// number of timers in the statecharts (after, every, ... actions)
#define MAX_TIMERS 4

// the cycle period in ms
#define CYCLE_PERIOD (10)

// the pins used for button and leds
const int button_pin = 2;
const int led_green_pin = 8;
const int led_yellow_pin = 9;
const int led_red_pin = 10;

static unsigned long cycle_count = 0L;
static unsigned long last_cycle_time = 0L;

// allocation of statechart, timers, and timer service
static Simple_pedestrian_crossing simple_pedestrian_crossing;
static sc_timer_t timers[MAX_TIMERS];
static sc_timer_service_t timer_service;

// callback implementation for the setting up time events
void simple_pedestrian_crossing_setTimer(Simple_pedestrian_crossing* handle, const sc_eventid evid, const sc_integer time_ms,
		const sc_boolean periodic) {
	sc_timer_start(&timer_service, handle, evid, time_ms, periodic);
}

// callback implementation for canceling time events.
void simple_pedestrian_crossing_unsetTimer(Simple_pedestrian_crossing* handle, const sc_eventid evid) {
	sc_timer_cancel(&timer_service, evid);
}

// runCycle() and connection to hardware
static void execute_cycle() {
	simple_pedestrian_crossing_runCycle(&simple_pedestrian_crossing);

	digitalWrite(led_green_pin, simple_pedestrian_crossingIface_get_green(&simple_pedestrian_crossing));
	digitalWrite(led_yellow_pin, simple_pedestrian_crossingIface_get_wait(&simple_pedestrian_crossing));
	digitalWrite(led_red_pin, simple_pedestrian_crossingIface_get_red(&simple_pedestrian_crossing));
}

// will be called to handle input changes
void button_interrupt() {
	simple_pedestrian_crossingIface_raise_button_pushed(&simple_pedestrian_crossing);
}

// The setup function is called once at startup of the sketch
void setup() {
	// set up the pins on arduino
	pinMode(led_green_pin, OUTPUT);
	pinMode(led_yellow_pin, OUTPUT);
	pinMode(led_red_pin, OUTPUT);

	pinMode(button_pin, INPUT);
	attachInterrupt(digitalPinToInterrupt(button_pin), button_interrupt, RISING);

	// We initialize the timer service with everything it requires.
	sc_timer_service_init(&timer_service, timers, MAX_TIMERS,
			(sc_raise_time_event_fp) &simple_pedestrian_crossing_raiseTimeEvent);

	// initialize the state machine
	simple_pedestrian_crossing_init(&simple_pedestrian_crossing);

	// enter the state machine
	simple_pedestrian_crossing_enter(&simple_pedestrian_crossing);

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
