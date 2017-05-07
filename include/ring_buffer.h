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
struct ring_buffer;

/***************************************************************************************************************************************************/
//                                                                 APIs
/***************************************************************************************************************************************************/

/**
* \brief his api is used to create new ring buffer.
*
* \param [in] buffer  byte-array
* \param [in] size  size of the buffer
*
* \return ring_buffer  returns ring_buffer object
* \verbatim
    NULL - if not successful
    non_NULL - if successful
  \endverbatim
*/
struct ring_buffer* ring_buffer_new(uint8_t *buffer, size_t size);


/**
* \brief This api is used to write data to ring buffer.
*
* \param [in] rb  ring-buffer object
* \param [in] data  byte-array
* \param [in] size  size of the buffer
* \param [out] bytes_wrote  size of bytes wrote to buffer
*
* \return int  returns status
* \verbatim
    error code - if not successfully
    0 - if successfully
  \endverbatim
*/
int ring_buffer_write(struct ring_buffer *rb, const uint8_t *data, size_t size, uint32_t *bytes_wrote);


/**
* \brief This api is used to read data from ring buffer.
*
* \param [in] rb  ring-buffer object
* \param [in] data  byte-array
* \param [in] size  size of the buffer
* \param [out] bytes_read  size of bytes read to buffer
*
* \return int  returns status
* \verbatim
    error code - if not successfully
    0 - if successfully
  \endverbatim
*/
int ring_buffer_read(struct ring_buffer *rb, uint8_t *data, size_t size, uint32_t *bytes_read);
/*@}*/
//  Local Variables:
//    mode: c++
//    tab-width: 4
//    c-basic-offset: 4
//    indent-tabs-mode: nil
//  End: