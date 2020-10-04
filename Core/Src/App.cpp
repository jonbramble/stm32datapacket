
#include <App.h>
#include "usbd_cdc_if.h"
#include <cstring>

#include "OnitronicsHeader.h"

App::App(cbuf_handle_t buffer): vcp(buffer), echo(vcp){
	setupDevices();
}

void App::setupDevices(){
	// repeat this for all the message ids and functions to call, there may be more than one per device
	auto echoFunc = std::bind(&Echo::receiveEventData, &echo, std::placeholders::_1, std::placeholders::_2); // move this to cmd register to hide bind...
	cmdRegister.addDevice(1, echoFunc);

	// add more devices here ....
	// Lasers
	// uF systems
	// stages
	// temperature sensor
	// system messages eg version
}

void App::update() {
	processVCP();
}

void App::processVCP(){
	// some method to control the event checking update rate....
	uint16_t data_size;
	uint16_t msg_id;
	bool headerParsed = false;

	if(vcp.size() > DataPacket::HeaderSize){ // it might not contain all the data yet ....
      DataPacket::OnitronicsHeader hdr = readHeaderFromBuffer();
	  data_size = hdr.payloadSize();
	  msg_id = hdr.msgID();
	  headerParsed = true;
	}
	//else....

	if(headerParsed && !vcp.hasBytes(data_size)){
	  payloadData.resize(data_size); //is this needed?
	  readPayloadFromBuffer(data_size);
	  auto func = cmdRegister.findDevice(msg_id);
      func(payloadData, data_size); //call function on device
	}
	//else....
}

DataPacket::OnitronicsHeader App::readHeaderFromBuffer() {
	vcp.readHeader(buffer_rx);
	DataPacket::OnitronicsHeader hdr(buffer_rx);
	return hdr;
}

void App::readPayloadFromBuffer(const uint16_t bytesToRead){
	vcp.readDataPacket(payloadData, bytesToRead);
}

