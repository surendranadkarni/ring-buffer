/*
    Header for ring buffer
    Copyright (C) {{ 2017 }} {{ Surendra Nadkarni suren.nadkarni@gmail.com }}

    All rights reserved.
    Please check LICENSE file for details
*/
#include <stdio.h>
#include <ring_buffer.h>

struct ring_buffer
{
    int a;
};

struct ring_buffer* ring_buffer_new(uint8_t *buffer, size_t size)
{
    return NULL;
}

int ring_buffer_write(struct ring_buffer *rb, const uint8_t *data, size_t size, uint32_t *bytes_wrote)
{
    return -1;
}

int ring_buffer_read(struct ring_buffer *rb, uint8_t *data, size_t size, uint32_t *bytes_read)
{
    return -1;
}