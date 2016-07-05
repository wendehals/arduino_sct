/**
 * Author: Lothar Wendehals - lothar.wendehals@itemis.de
 *
 * Eclipse Public License - v 1.0
 */
#ifndef SCT_BLINKCONNECTOR_H_
#define SCT_BLINKCONNECTOR_H_

#include "../src-gen/AbstractTimer.h"
#include "../src-gen/Sct_blink.h"
#include "../src-gen/ATmega168_328Timer.h"

class Sct_blinkConnector: public HardwareConnector {
public:
	Sct_blinkConnector(Sct_blink* statemachine);

	inline virtual ~Sct_blinkConnector();

	virtual void init();

	virtual void runCycle();

private:
	Sct_blink* statemachine;
};

Sct_blinkConnector::~Sct_blinkConnector() {
}

#endif /* SCT_BLINKCONNECTOR_H_ */
