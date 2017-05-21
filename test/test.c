#include <stdio.h>
#include <ring_buffer.h>
#include <assert.h>
#include <stdlib.h>
int main()
{
    uint8_t buffer[10] = {0};
    uint8_t data1[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 18, 19, 20};
    uint8_t data2[10] = {0};
    struct ring_buffer *rb = (struct ring_buffer*) malloc(sizeof(struct ring_buffer));
    uint32_t tmp = 0;
    int retval = 0;
    int i = 0;

    assert(ring_buffer_create(buffer, 10, rb) == 0);

    retval = ring_buffer_write(rb, data1, 5, &tmp);
    assert(retval == 0);
    printf("wrote %d bytes\n", tmp);

    tmp = 0;
    retval = ring_buffer_read(rb, data2, 3, &tmp);
    assert(retval == 0);
    printf("read %d bytes\n", tmp);

    for(i = 0; i < tmp; i++) printf("%d ",data2[i]);
    printf("\n");

    retval = ring_buffer_write(rb, data1+10, 10, &tmp);
    assert(retval == 0);
    assert(tmp == 8);
    printf("wrote %d bytes\n", tmp);

    tmp = 0;
    retval = ring_buffer_read(rb, data2, 7, &tmp);
    assert(retval == 0);
    assert(tmp == 7);
    printf("read %d bytes\n", tmp);
    for(i = 0; i < tmp; i++) printf("%d ",data2[i]);
    printf("\n");

    /*dummy read*/
    tmp = 0;
    retval = ring_buffer_dummy_read(rb, data2, 3, &tmp);
    assert(retval == 0);
    assert(tmp == 3);
    printf("\n dummy read %d bytes\n", tmp);
    for(i = 0; i < tmp; i++) printf("%d ",data2[i]);
    for(i = 0; i < tmp; i++) data2[i] = 0;
    printf("\n");

    tmp = 0;
    retval = ring_buffer_read(rb, data2, 3, &tmp);
    assert(retval == 0);
    assert(tmp == 3);
    printf("\n read %d bytes\n", tmp);
    for(i = 0; i < tmp; i++) printf("%d ",data2[i]);
    printf("\n");

    tmp = 0;
    retval = ring_buffer_read(rb, data2, 3, &tmp);
    assert(retval == 0);
    assert(tmp == 0);
    printf("\nread %d bytes as buffer is empty\n", tmp);
    for(i = 0; i < tmp; i++) printf("%d ",data2[i]);
    printf("\n");

    free(rb);
    return 0;
}