# Ring Buffer in C

Simple ring buffer implementation for embedded systems

This implementation is more suitable for embedded systems (non-os) systems.

One may create the ring-buffer as follows
```
ring_buffer_create(buffer, len_of_buffer, rb_obj)
```
RB can be written with data having size less than or equal to size of the RB.
```
ring_buffer_write(rb, data, len, &bytes_written);
```

Please note that one can not write bytes to RB if it is FULL. So consumer must be fast than producer.
Please check the example in test directory for example code.
