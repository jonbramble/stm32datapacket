/*
 * DefaultHandler.cpp
 *
 *  Created on: 4 Oct 2020
 *      Author: Jonathan Bramble
 */

#include <DefaultHandler.h>

DefaultHandler::DefaultHandler(VCP _vcp): vcp(_vcp) {

}

void DefaultHandler::receiveEventData(std::vector<uint8_t> pb_buffer_rx, uint16_t pb_size_rx){
	transmitData();
}

void DefaultHandler::transmitData(){
	uint16_t message_length = 0;
	DataPacket::OnitronicsHeader hdr(3, message_length, 2, 0); //decide on status and system messages
	hdr.toBytes(buffer_header);
	vcp.writeHeader(buffer_header);
}

