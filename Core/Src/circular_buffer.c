/*
 * circ_buffer.c
 *
 *  Created on: 12 Sep 2020
 *      Author: Jonathan Bramble
 */


#include "circular_buffer.h"

cbuf_handle_t circular_buffer_initialise(uint8_t *buffer, size_t size){

   cbuf_handle_t cbuf;
   //allocate memory for struct not buffer
   cbuf = malloc(sizeof(circular_buffer_t));
   cbuf->buffer = buffer;
   cbuf->max = size;

   circular_buffer_reset(cbuf);

   return cbuf;

}

void circular_buffer_free(cbuf_handle_t cbuf){
	free(cbuf);
};

size_t circular_buffer_size(cbuf_handle_t cbuf){
	size_t size = cbuf->max;
	if(!cbuf->full)
	{
		if(cbuf->head >= cbuf->tail)
		{
			size = (cbuf->head - cbuf->tail);
		}
		else
		{
			size = (cbuf->max + cbuf->head - cbuf->tail);
		}
	}

	return size;
}


void circular_buffer_reset(cbuf_handle_t cbuf){
    cbuf->head = 0;
    cbuf->tail = 0;
    cbuf->full = false;
};

void circular_buffer_put(cbuf_handle_t cbuf, uint8_t data)
{
   cbuf->buffer[cbuf->head]= data;
   if(cbuf->full)
   {
		cbuf->tail = (cbuf->tail + 1) % cbuf->max;
   }

   cbuf->head = (cbuf->head + 1) % cbuf->max;
   cbuf->full = (cbuf->head == cbuf->tail);
};

void circular_buffer_put_array(cbuf_handle_t cbuf, uint8_t *data, size_t size){
	//possibly a more efficient way without the loop
	for(size_t i = 0; i<size; i++){
		circular_buffer_put(cbuf, data[i]);
	}
}

int circular_buffer_get(cbuf_handle_t cbuf, uint8_t *data){
	int retval = 0;
	if(!circular_buffer_empty(cbuf)){
		   *data = cbuf->buffer[cbuf->tail];
		   	cbuf->full = false;
	        cbuf->tail = (cbuf->tail + 1) % cbuf->max;
		    retval = 1;
	}
	return retval;

};

int circular_buffer_get_array(cbuf_handle_t cbuf, uint8_t *data, size_t size){
	int retval = -1;
	if(circular_buffer_size(cbuf) >= size){
		for(size_t i=0; i<size; i++){
          retval = circular_buffer_get(cbuf, &data[i]);
		  if(retval == -1){
			  break;
		  }
		}
	}
    return retval;
}

bool circular_buffer_full(cbuf_handle_t cbuf)
{
	return cbuf->full;
};

bool circular_buffer_empty(cbuf_handle_t cbuf){
	return (!cbuf->full && (cbuf->head == cbuf->tail));
}

size_t circular_buffer_capacity(cbuf_handle_t cbuf){
	return cbuf->max - (cbuf->head-cbuf->tail);
}



