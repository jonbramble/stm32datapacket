/*
 * VCP.h
 *
 *  Created on: 29 Sep 2020
 *      Author: Jonathan Bramble
 */

#ifndef INC_VCP_H_
#define INC_VCP_H_

//wrapper around the circular buffer

#include "circular_buffer.h"
#include "OnitronicsHeader.h"

#include <array>
#include <vector>

class VCP {
public:
	VCP()=delete;
	VCP(cbuf_handle_t);

	void readHeader(std::array<uint8_t, DataPacket::HeaderSize> &buffer_rx);
	void readDataPacket(std::vector<uint8_t> &buffer_rx, size_t bytesToRead);

	void writeHeader(std::array<uint8_t, DataPacket::HeaderSize> &buffer_tx);
	void writeDataPacket(std::vector<uint8_t> &buffer_tx, size_t bytesToWrite);

	size_t size() const;
	void reset();
	bool empty() const;
	bool hasBytes(size_t size) const;

	virtual ~VCP();

private:
	cbuf_handle_t m_cbuf;
	bool full() const;
};

#endif /* INC_VCP_H_ */
