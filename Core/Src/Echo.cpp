/*
 * Echo.cpp
 *
 *  Created on: 29 Sep 2020
 *      Author: Jonathan Bramble
 */

#include "Echo.h"
#include "OnitronicsHeader.h"
#include <string>

Echo::Echo(VCP _vcp): vcp(_vcp) {
  buffer_tx.resize(Example_size,0);
}

Echo::~Echo() {
}

void Echo::receiveEventData(std::vector<uint8_t> pb_buffer_rx, uint16_t pb_size_rx)
{
	bool status  = DataPacket::NanopbPayload::decode<Example>(pb_buffer_rx, pb_size_rx, Example_fields, message);
	if(status){
		transmitData(); // do the echo of the decoded packet
	}
};

void Echo::transmitData(){

	uint16_t message_length = 0;
    bool status = DataPacket::NanopbPayload::encode<Example>(buffer_tx, message_length, Example_fields, message);

    if(status){
	  DataPacket::OnitronicsHeader hdr(2, message_length, 1, 0);
	  hdr.toBytes(buffer_payload);

	  vcp.writeHeader(buffer_payload);
	  vcp.writeDataPacket(buffer_tx, message_length);
    }
}

