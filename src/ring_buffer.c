/*
    Module for ring buffer
    Copyright (C) {{ 2017 }} {{ Surendra Nadkarni suren.nadkarni@gmail.com }}

    All rights reserved.
    Please check LICENSE file for details. Refered Stuart Cording's code.
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
#define RB_EMPTY (0x01)
#define RB_FULL (0x01<<31)

#define SET_FLAG(flags, flag) do{ flags |= flag;} while(0)
#define RESET_FLAG(flags, flag) do{ flags &= ~flag;} while(0)


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
    rb->start_of_buffer = buffer;
    rb->end_of_buffer = rb->start_of_buffer + size - 1;
    rb->size = size;
    rb->write_ptr = rb->read_ptr = buffer;
    rb->flags = 0;
    SET_FLAG(rb->flags, RB_EMPTY);
    return 0;
}


/**
    ring_buffer_write()-
        This function wraps buffer into the ring buffer

    \overview   pseudocode-
        \verbatim
          write byte by byte until read_ptr equals write_ptr
          code may wrap the write pointer if it reaches end_of_buffer
        \endverbatim
*/
int ring_buffer_write(struct ring_buffer *rb, const uint8_t *data, size_t len, uint32_t *bytes_written)
{
    int cnt = 0;

    if(rb == NULL) return -1;

    if(rb->flags & RB_FULL)
    {
        *bytes_written = cnt;
        return 0;
    }

    while (!(rb->flags & RB_FULL))
    {
        *rb->write_ptr = *data;
        rb->write_ptr++;
        data++;
        cnt++;

        if (rb->write_ptr > rb->end_of_buffer)
        {
            rb->write_ptr = rb->start_of_buffer;
        }

        if(rb->write_ptr == rb->read_ptr)
        {
            SET_FLAG(rb->flags, RB_FULL);
        }
        if(cnt == len)
        {
            break;
        }
    }
    *bytes_written = cnt;
    RESET_FLAG(rb->flags, RB_EMPTY);
    return 0;
}


/**
    ring_buffer_read()-

    \overview   pseudocode-
        \verbatim
            read byte by byte until buffer becomes empty
            sometimes need to wrap if reaches end_of_buffer
        \endverbatim
*/
int ring_buffer_read(struct ring_buffer *rb, uint8_t *data, size_t len, uint32_t *bytes_read)
{
    int cnt = 0;

    if(rb == NULL) return -1;

    if(rb->flags & RB_EMPTY)
    {
        *bytes_read = 0;
        return 0;
    }

    while(!(rb->flags & RB_EMPTY))
    {
        *data = *rb->read_ptr;
        rb->read_ptr++;
        data++;
        cnt++;

        if (rb->read_ptr > rb->end_of_buffer)
        {
            rb->read_ptr = rb->start_of_buffer;
        }

        if(rb->write_ptr == rb->read_ptr)
        {
            SET_FLAG(rb->flags, RB_EMPTY);
        }

        if(cnt == len)
        {
            break;
        }
    }
    *bytes_read = cnt;
    RESET_FLAG(rb->flags, RB_FULL);
    return 0;
}