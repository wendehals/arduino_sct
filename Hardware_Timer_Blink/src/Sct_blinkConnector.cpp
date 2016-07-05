/**
 * Author: Lothar Wendehals - lothar.wendehals@itemis.de
 *
 * Eclipse Public License - v 1.0
 */
#include "Sct_blinkConnector.h"

const unsigned short LED_PIN = 13;

Sct_blinkConnector::Sct_blinkConnector(Sct_blink* statemachine) {
	this->statemachine = statemachine;
}

void Sct_blinkConnector::init() {
	pinMode(LED_PIN, OUTPUT);
}

void Sct_blinkConnector::runCycle() {
	digitalWrite(LED_PIN, this->statemachine->get_on());
}
