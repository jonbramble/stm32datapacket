/*
 * LEDController.h
 *
 *  Created on: 4 Oct 2020
 *      Author: Jonathan Bramble
 */

#ifndef INC_LEDCONTROLLER_H_
#define INC_LEDCONTROLLER_H_

#include "VCP.h"
#include "NanopbPayload.h"

// test for the dev board... flash some lights
// reuse the Example field
#include "message.pb.h"

class LEDController {
public:
	LEDController()=delete;
	LEDController(VCP vcp);
	void receiveEventData(std::vector<uint8_t> pb_buffer_rx, uint16_t pb_size_rx);
	virtual ~LEDController();

private:
	//std::vector<uint8_t> buffer_tx;
	//std::array<uint8_t,DataPacket::HeaderSize> buffer_payload;

	VCP &vcp;
	Example message = Example_init_zero;
};

#endif /* INC_LEDCONTROLLER_H_ */
