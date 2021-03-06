/*
    Header for ring buffer
    Copyright (C) {{ 2017 }} {{ Surendra Nadkarni suren.nadkarni@gmail.com }}

    All rights reserved.
    Please check LICENSE file for details
*/
/*@{*/

#include <stdint.h>

/***************************************************************************************************************************************************/
//                                                                   DEFINITIONS
/***************************************************************************************************************************************************/
struct ring_buffer
{
    uint8_t *start_of_buffer;
    uint8_t *end_of_buffer;
    size_t size;
    uint8_t *read_ptr;
    uint8_t *write_ptr;
    uint32_t flags;
};

/***************************************************************************************************************************************************/
//                                                                 APIs
/***************************************************************************************************************************************************/

/**
* \brief his api is used to create new ring buffer.
*
* \param [in] buffer  byte-array
* \param [in] size  size of the buffer
* \param [out] rb   pointer to ring-buffer object. Application will hold the object
*
* \return int  returns error status
* \verbatim
    error code - if not successful
    0 - if successful
  \endverbatim
*/
int ring_buffer_create(uint8_t *buffer, size_t size, struct ring_buffer *rb);


/**
* \brief This api is used to write data to ring buffer.
*
* \param [in] rb  ring-buffer object
* \param [in] data  byte-array
* \param [in] len  len of the buffer
* \param [out] bytes_wrote  len of bytes wrote to buffer
*
* \return int  returns status
* \verbatim
    error code - if not successful
    0 - if successful
  \endverbatim
*/
int ring_buffer_write(struct ring_buffer *rb, const uint8_t *data, size_t len, uint32_t *bytes_wrote);


/**
* \brief This api is used to read data from ring buffer.
*
* \param [in] rb  ring-buffer object
* \param [in] data  byte-array
* \param [in] len  len of the buffer
* \param [out] bytes_read  len of bytes read to buffer
*
* \return int  returns status
* \verbatim
    error code - if not successful
    0 - if successful
  \endverbatim
*/
int ring_buffer_read(struct ring_buffer *rb, uint8_t *data, size_t len, uint32_t *bytes_read);

/**
* \brief This api is used to dummy read data from ring buffer.
*        This operation will nor increment the read pointer
*
* \param [in] rb  ring-buffer object
* \param [in] data  byte-array
* \param [in] len  len of the buffer
* \param [out] bytes_read  len of bytes read to buffer
*
* \return int  returns status
* \verbatim
    error code - if not successful
    0 - if successful
  \endverbatim
*/
int ring_buffer_dummy_read(struct ring_buffer *rb, uint8_t *data, size_t len, uint32_t *bytes_read);
/*@}*/
//  Local Variables:
//    mode: c++
//    tab-width: 4
//    c-basic-offset: 4
//    indent-tabs-mode: nil
//  End: