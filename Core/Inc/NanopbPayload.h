/*
 * NanopbPayload.h
 *
 *  Created on: 3 Oct 2020
 *      Author: Jonathan Bramble
 */

#ifndef INC_NANOPBPAYLOAD_H_
#define INC_NANOPBPAYLOAD_H_

// encode and decode datapackets and turn into byte arrays
// do crc checks here

#include <vector>
#include "pb_decode.h"
#include "pb_encode.h"

namespace DataPacket {

class NanopbPayload {

public:
	NanopbPayload()=delete;

	// encode message in byte stream using nanopb
	// @param buffer -preallocated buffer upto max length of message
	// @param len - encoded message length output
	// @param message fields eg Example_fields see nanopb
	// @param message - nanopb message instance
	template<typename T>
    static bool encode(std::vector<uint8_t> &buffer, uint16_t &len, const pb_msgdesc_t* fields, const T &message)
    {
	    pb_ostream_t stream_tx = pb_ostream_from_buffer(buffer.data(), 128); //check max length ...
	    bool status_encode = pb_encode(&stream_tx, fields, &message);
	    len = stream_tx.bytes_written;
    	return status_encode;
    }

	//decode a byte stream into a nanopb message
    template<typename T>
    static bool decode(const std::vector<uint8_t> &buffer, const uint16_t len, const pb_msgdesc_t* fields, T &message)
	{
    	pb_istream_t stream_rx = pb_istream_from_buffer(buffer.data(), len);
    	bool status_decode = pb_decode(&stream_rx, fields, &message);
    	return status_decode;
	}
};

}



#endif /* INC_NANOPBPAYLOAD_H_ */
