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
    retval = ring_buffer_read(rb, data2, 5, &tmp);
    assert(retval == 0);
    printf("read %d bytes\n", tmp);
    for(i = 0; i < 5; i++) printf("%d ",data2[i]);
    printf("\n");

    retval = ring_buffer_write(rb, data1+10, 8, &tmp);
    assert(retval == 0);
    printf("wrote %d bytes\n", tmp);

    tmp = 0;
    retval = ring_buffer_read(rb, data2, 5, &tmp);
    assert(retval == 0);
    printf("read %d bytes\n", tmp);
    for(i = 0; i < 5; i++) printf("%d ",data2[i]);
    printf("\n");

    tmp = 0;
    retval = ring_buffer_read(rb, data2, 3, &tmp);
    assert(retval == 0);
    printf("\nread %d bytes\n", tmp);
    for(i = 0; i < 3; i++) printf("%d ",data2[i]);
    printf("\n");

    free(rb);
    return 0;
}