/*
 * OnitronicsHeader.h
 *
 *  Created on: 29 Sep 2020
 *      Author: Jonathan Bramble
 */

#ifndef INC_ONITRONICSHEADER_H_
#define INC_ONITRONICSHEADER_H_

#include <stdint.h>
#include <array>

namespace DataPacket {

typedef struct {
  uint16_t msg_id;   	// message id number //python H
  uint16_t datasize; 	// number of bytes in payload // python H
  uint8_t status; 	// tbc bit array of message state and priority // python B
  uint8_t vmajor; 	// python B
  uint8_t vminor; 	// message versioning python B
  uint8_t vpatch; 	// python B
  uint32_t crc;   	// crc of pseudo header + data // I
} __attribute__((packed)) header;


static constexpr size_t HeaderSize = sizeof(header);

class OnitronicsHeader {
public:
	OnitronicsHeader(const uint16_t msg_id, const uint16_t datasize, const uint8_t status, const uint32_t crc);
	OnitronicsHeader(const std::array<uint8_t,HeaderSize> &buffer_rx); //create header from buffer
	void toBytes(std::array<uint8_t,HeaderSize> &buffer_tx);
	uint16_t payloadSize() const;
	uint16_t msgID() const;
	bool crcCheck() const; // returns crc status
	virtual ~OnitronicsHeader();
private:
	header h;
};



} /* namespace DataPacket */

#endif /* INC_ONITRONICSHEADER_H_ */
