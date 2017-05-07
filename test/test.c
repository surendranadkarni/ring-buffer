#include <stdio.h>
#include <ring_buffer.h>
#include <assert.h>
int main()
{
    uint8_t buffer[100] = {0};
    uint8_t data1[5] = {1,2,3,4,5};
    uint8_t data2[5] = {0};
    struct ring_buffer* rb = ring_buffer_new(buffer, 100);
    uint32_t tmp = 0;

    assert(ring_buffer_write(rb, data1, 5, &tmp) == 0);

    assert(ring_buffer_read(rb, data2, 5, &tmp) == 0);

    return 0;
}