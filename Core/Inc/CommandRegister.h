/*
 * CommandRegister.h
 *
 *  Created on: 29 Sep 2020
 *      Author: Jonathan Bramble
 */

// Register of message ids against decoding Struct from nanopb

#ifndef SRC_COMMANDREGISTER_H_
#define SRC_COMMANDREGISTER_H_

#include <unordered_map>
#include <vector>
#include <functional>

// how can I ensure the default handler has been added, set a flag when the default handler is added to stop adding functions

using receiveFunction_t = std::function<void(std::vector<uint8_t>, uint16_t)>;

class CommandRegister {
public:
	CommandRegister();
	void addDevice(uint16_t msgid, receiveFunction_t func){
		m_register.insert({msgid, func});
	}

	void addDefaultHandler(receiveFunction_t func){
		m_defaultHandler = func;
		m_registerComplete = true;
	}

	receiveFunction_t findDevice(uint16_t msg_id)
	{
		auto it =  m_register.find(msg_id);
		if(it != m_register.end()){
			return it->second;
		}
		else {
			return m_defaultHandler;
		}
	}

	virtual ~CommandRegister();

private:
	bool m_registerComplete = false;
	std::unordered_map<uint16_t, receiveFunction_t> m_register;
	receiveFunction_t m_defaultHandler; // this must be set!
};

#endif /* SRC_COMMANDREGISTER_H_ */
