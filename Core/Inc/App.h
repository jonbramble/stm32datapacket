
#ifndef __APP_H
#define __APP_H

#include "circular_buffer.h"
#include "CommandRegister.h"
#include "VCP.h"
#include "Echo.h"
#include "LEDController.h"
#include "DefaultHandler.h"

#include <vector>
#include <unordered_map>
#include <functional>

//should this be a singleton?

using receiveFunction_t = std::function<void(std::vector<uint8_t>,uint16_t)>;

class App {
public:
	App()=delete;
	App(cbuf_handle_t);

	void update(); // replace with a scheduler

private:
	std::array<uint8_t, DataPacket::HeaderSize> buffer_rx;
	std::vector<uint8_t> payloadData;

    VCP vcp; //must come first

	CommandRegister cmdRegister;
	Echo echo;
	LEDController ledController;
	DefaultHandler defaultHandler;

	void setupDevices();
	DataPacket::OnitronicsHeader readHeaderFromBuffer();
	void readPayloadFromBuffer(const uint16_t bytesToRead);

	void processVCP();
};

#endif

