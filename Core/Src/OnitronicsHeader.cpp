/*
 * OnitronicsHeader.cpp
 *
 *  Created on: 29 Sep 2020
 *      Author: Jonathan Bramble
 */

#include <OnitronicsHeader.h>
#include <cstring>

namespace DataPacket {

//update if the header packet changes size, form or function
namespace VERSION {
  static constexpr uint8_t VMAJOR = 1;
  static constexpr uint8_t VMINOR = 0;
  static constexpr uint8_t VPATCH = 0;
}

OnitronicsHeader::OnitronicsHeader(const uint16_t msg_id, const uint16_t datasize, const uint8_t status, const uint32_t crc){
	h.msg_id = msg_id;
	h.datasize = datasize;
	h.status = status;
	h.vmajor=  VERSION::VMAJOR;
	h.vminor = VERSION::VMINOR;
	h.vpatch = VERSION::VPATCH;
	h.crc = crc;
}

OnitronicsHeader::OnitronicsHeader(const std::array<uint8_t, HeaderSize> &buffer_rx) {
	memcpy(&h, buffer_rx.data(), HeaderSize);
}

void OnitronicsHeader::toBytes(std::array<uint8_t,HeaderSize> &buffer_tx){
	memcpy(buffer_tx.data(), &h, HeaderSize);
}


OnitronicsHeader::~OnitronicsHeader() {
}

uint16_t OnitronicsHeader::payloadSize() const{
	return h.datasize;

}

uint16_t OnitronicsHeader::msgID() const{
	return h.msg_id;

}

} /* namespace DataPacket */

