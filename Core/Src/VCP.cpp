/*
 * VCP.cpp
 *
 *  Created on: 29 Sep 2020
 *      Author: Jonathan Bramble
 */

#include <VCP.h>
#include "usbd_cdc_if.h"

VCP::VCP(cbuf_handle_t cbuf) {
	reset();
    m_cbuf = cbuf;
}

VCP::~VCP() {

}

void VCP::reset() {
	circular_buffer_reset(m_cbuf);
}

bool VCP::empty() const {
	return circular_buffer_empty(m_cbuf);
}

bool VCP::full() const {
	return circular_buffer_full(m_cbuf);
}

size_t VCP::size() const {
	return circular_buffer_size(m_cbuf);
}

bool VCP::hasBytes(size_t datasize) const{
	return (size() > datasize);
}

void VCP::readHeader(std::array<uint8_t, DataPacket::HeaderSize> &buffer_rx){
	const size_t buffer_size = size();
	uint8_t value;

	if(buffer_size > DataPacket::HeaderSize){
	  for(uint8_t i=0; i< DataPacket::HeaderSize; i++){
		int rv = circular_buffer_get(m_cbuf, &value);
		if(rv == 1){
			buffer_rx[i] = value;
		}
	  }
    }
}

void VCP::readDataPacket(std::vector<uint8_t> &buffer_rx, size_t bytesToRead){
	const size_t buffer_size = size();
	uint8_t value;
	if(buffer_size >= bytesToRead){
	for(uint8_t i=0; i< bytesToRead; i++){
		int rv = circular_buffer_get(m_cbuf, &value);
		  if(rv==1) {
			  buffer_rx[i] = value;
		  }
		  // check this has completed
		}
	}
}

//another circular buffer to write data out?
void VCP::writeHeader(std::array<uint8_t, DataPacket::HeaderSize> &buffer_tx){
	uint8_t usbrv;
	do {
	  usbrv = CDC_Transmit_FS(buffer_tx.data(), buffer_tx.size());
	} while(usbrv != USBD_OK);

}

void VCP::writeDataPacket(std::vector<uint8_t> &buffer_tx, size_t bytesToWrite){
	uint8_t usbrv;
	do {
	  usbrv = CDC_Transmit_FS(buffer_tx.data(), bytesToWrite);
	} while(usbrv != USBD_OK);
}



