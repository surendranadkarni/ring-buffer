/*
    Header for ring buffer
    Copyright (C) {{ 2017 }} {{ Surendra Nadkarni suren.nadkarni@gmail.com }}

    All rights reserved.
    Please check LICENSE file for details
*/

/***************************************************************************************************************************************************/
//                                    INCLUDE FILES
/***************************************************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <ring_buffer.h>


/***************************************************************************************************************************************************/
//                                    LOCAL DEFINITION
/***************************************************************************************************************************************************/
#define MIN(a,b) ((a)<(b)?(a):(b))


/***************************************************************************************************************************************************/
//                                    API
/***************************************************************************************************************************************************/
/**
    ring_buffer_create()-
        This function wraps buffer into the ring buffer

    \overview   pseudocode-
        \verbatim

          check if buffer not null
          cook the ring buffer structure

        \endverbatim
*/
int ring_buffer_create(uint8_t *buffer, size_t size, struct ring_buffer *rb)
{
    if(NULL == buffer)
    {
        return -1;
    }
    rb->buffer = buffer;
    rb->size = size;
    rb->write_ptr = rb->read_ptr = buffer;
    return 0;
}


/**
    ring_buffer_write()-
        This function wraps buffer into the ring buffer

    \overview   pseudocode-
        \verbatim

          check if rb is not null
          if there is sufficient space to write then
            write complete
          else
            write till end and then wrap the wrt ptr and write remaining

        \endverbatim
*/
int ring_buffer_write(struct ring_buffer *rb, const uint8_t *data, size_t len, uint32_t *bytes_wrote)
{
    if(rb == NULL)
        return -1;
    size_t contiguous_space_available = (rb->buffer + rb->size) - rb->write_ptr;

    if(contiguous_space_available > len)
    {
        memcpy(rb->write_ptr, data, len);
        *bytes_wrote = len;
        rb->write_ptr = rb->write_ptr + len;
    }
    else if (contiguous_space_available == len)
    {
        memcpy(rb->write_ptr, data, contiguous_space_available);
        rb->write_ptr = rb->buffer;
        *bytes_wrote = len;
    }
    else if (contiguous_space_available < len)
    {
        memcpy(rb->write_ptr, data, contiguous_space_available);
        memcpy(rb->buffer, data+contiguous_space_available, len-contiguous_space_available);
        rb->write_ptr = rb->buffer + len-contiguous_space_available;
        *bytes_wrote = len;
    }
    return 0;
}


/**
    ring_buffer_read()-

    \overview   pseudocode-
        \verbatim

          check if rb is not null
          if rd_ptr > wr_ptr then no case of contiguous read
            read till end
            and then till wr ptr
          else
            read till wr_ptr

        \endverbatim
*/
int ring_buffer_read(struct ring_buffer *rb, uint8_t *data, size_t len, uint32_t *bytes_read)
{
    if(rb == NULL)
        return -1;

    if(rb->read_ptr < rb->write_ptr)
    {
        size_t contiguous_space_available = rb->write_ptr - rb->read_ptr;
        size_t read_len = MIN(len, contiguous_space_available);
        memcpy(data, rb->read_ptr, read_len);
        rb->read_ptr = rb->read_ptr + len;
        *bytes_read = len;
    }
    else
    {
        size_t contiguous_space_available = (rb->buffer + rb->size) - rb->read_ptr;
        if(contiguous_space_available > len)
        {
             memcpy(data, rb->read_ptr, contiguous_space_available);
             rb->read_ptr = rb->read_ptr + len;
        }
        else if(contiguous_space_available == len)
        {
             memcpy(data, rb->read_ptr, len);
             rb->read_ptr = rb->buffer;
        }
        else if(contiguous_space_available < len)
        {
             memcpy(data, rb->read_ptr, contiguous_space_available);
             memcpy(data+contiguous_space_available, rb->buffer, len-contiguous_space_available);
             rb->read_ptr = rb->buffer + len-contiguous_space_available;
        }
        *bytes_read = len;
    }
    return 0;
}