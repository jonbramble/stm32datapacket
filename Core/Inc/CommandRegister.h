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

using receiveFunction_t = std::function<void(std::vector<uint8_t>, uint16_t)>;

class CommandRegister {
public:
	CommandRegister();
	void addDevice(uint16_t msgid, receiveFunction_t func){
		m_register.insert({msgid, func});
	}

	//what if it is not found? return an error message but empty the buffer...
	receiveFunction_t findDevice(uint16_t msg_id)
	{
		return m_register.find(msg_id)->second;
	}

	virtual ~CommandRegister();


private:

	std::unordered_map<uint16_t, receiveFunction_t> m_register;
};

#endif /* SRC_COMMANDREGISTER_H_ */
