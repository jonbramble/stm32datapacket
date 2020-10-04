/*
 * Echo.h
 *
 *  Created on: 29 Sep 2020
 *      Author: Jonathan Bramble
 */

// echo from board

#ifndef ECHO_H_
#define ECHO_H_



#include "message.pb.h"
#include "NanopbPayload.h"
#include "VCP.h"

#include <vector>

class Echo {
public:
	Echo()=delete;
	Echo(VCP vcp);
	void receiveEventData(std::vector<uint8_t> pb_buffer_rx, uint16_t pb_size_rx);
	void transmitData();
	virtual ~Echo();

private:
	std::vector<uint8_t> buffer_tx;
	std::array<uint8_t,DataPacket::HeaderSize> buffer_header;

	//one of many possible messages - defined by nanopb headers
	Example message = Example_init_zero;  // the struct for this hardware element

	VCP &vcp;
};

#endif /* ECHO_H_ */
