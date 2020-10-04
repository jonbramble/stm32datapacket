/*
 * LEDController.cpp
 *
 *  Created on: 4 Oct 2020
 *      Author: Jonathan Bramble
 */

#include <LEDController.h>
#include "gpio.h"

LEDController::LEDController(VCP _vcp): vcp(_vcp) {

}

LEDController::~LEDController() {

}

void LEDController::receiveEventData(std::vector<uint8_t> pb_buffer_rx, uint16_t pb_size_rx)
{
	bool status  = DataPacket::NanopbPayload::decode<Example>(pb_buffer_rx, pb_size_rx, Example_fields, message);
	if(status){
		if(message.value==1){
			//turn light on
			HAL_GPIO_WritePin(LD2_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
			HAL_Delay(100);
		}
		else if(message.value==2){
			HAL_GPIO_WritePin(LD2_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
		}
		else if(message.value==3){
			//turn light on
			HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
			HAL_Delay(100);
		}
		else if(message.value==4){
			HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
		}
		else if(message.value==5){
			//turn light on
			HAL_GPIO_WritePin(LD2_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
			HAL_Delay(100);
		}
		else if(message.value==6){
			HAL_GPIO_WritePin(LD2_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
		}
	}
};

