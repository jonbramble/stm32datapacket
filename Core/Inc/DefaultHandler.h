/*
 * DefaultHandler.h
 *
 *  Created on: 4 Oct 2020
 *      Author: Jonathan Bramble
 */

#ifndef INC_DEFAULTHANDLER_H_
#define INC_DEFAULTHANDLER_H_

#include "VCP.h"
#include <vector>

class DefaultHandler {
public:
	DefaultHandler()=delete;
	DefaultHandler(VCP);
	//called when message id is not found in the register of hardware devices
	void receiveEventData(std::vector<uint8_t> pb_buffer_rx, uint16_t pb_size_rx);
	void transmitData();

private:
	std::array<uint8_t,DataPacket::HeaderSize> buffer_header;
	VCP &vcp;
};

#endif /* INC_DEFAULTHANDLER_H_ */
