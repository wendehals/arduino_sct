/**
 * Author: Lothar Wendehals - lothar.wendehals@itemis.de
 *
 * Eclipse Public License - v 1.0
 */
#ifndef HARDWARECONNECTOR_H_
#define HARDWARECONNECTOR_H_

class HardwareConnector {
public:
	inline virtual ~HardwareConnector();

	virtual void init() = 0;

	virtual void runCycle() = 0;
};

HardwareConnector::~HardwareConnector() {
}

#endif /* HARDWARECONNECTOR_H_ */
