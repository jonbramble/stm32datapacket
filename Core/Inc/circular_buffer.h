
/*
 * circ_buffer.h
 *
 *  Created on: 12 Sep 2020
 *      Author: Jonathan Bramble
 */

#ifndef INC_CIRC_BUFFER_H_
#define INC_CIRC_BUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct circular_buffer_t circular_buffer_t;
typedef circular_buffer_t* cbuf_handle_t;

struct circular_buffer_t {
	uint8_t *buffer; //pointer to internal buffer
	size_t head;
	size_t tail;
	size_t max;
	bool full;
};

//FIFO for datapackets containing header and data payload
//Size will be in multiples of uint8_t so use this for FIFO type

//creates circular_buffer struct but not memory for the buffer
cbuf_handle_t circular_buffer_initialise(uint8_t *buffer, size_t size);
void circular_buffer_free(cbuf_handle_t cbuf);
void circular_buffer_reset(cbuf_handle_t cbuf);
void circular_buffer_put(cbuf_handle_t cbuf, uint8_t data);
void circular_buffer_put_array(cbuf_handle_t cbuf, uint8_t *data, size_t size);
int circular_buffer_get(cbuf_handle_t cbuf, uint8_t *data);
int circular_buffer_get_array(cbuf_handle_t cbuf, uint8_t *data, size_t size);
bool circular_buffer_full(cbuf_handle_t cbuf);
bool circular_buffer_empty(cbuf_handle_t cbuf);
size_t circular_buffer_capacity(cbuf_handle_t cbuf);
size_t circular_buffer_size(cbuf_handle_t cbuf);

#ifdef __cplusplus
}
#endif


#endif /* INC_CIRC_BUFFER_H_ */
