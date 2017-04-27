/**
 * tcoap_helpers.h
 *
 * Author: Serge Maslyakov, rusoil.9@gmail.com
 * Copyright 2017 Serge Maslyakov. All rights reserved.
 *
 */


#ifndef __TCOAP_HELPERS_H
#define __TCOAP_HELPERS_H


#include <stdint.h>
#include "tcoap.h"


typedef enum {

    TCOPA_BLOCK_SZX_VAL_0       = 16,
    TCOPA_BLOCK_SZX_VAL_1       = 32,
    TCOPA_BLOCK_SZX_VAL_2       = 64,
    TCOPA_BLOCK_SZX_VAL_3       = 128,
    TCOPA_BLOCK_SZX_VAL_4       = 256,
    TCOPA_BLOCK_SZX_VAL_5       = 512,
    TCOPA_BLOCK_SZX_VAL_6       = 1024,

    /**
     * Reserved, i.e., MUST NOT be sent and
     * MUST lead to a 4.00 Bad Request response
     * code upon reception in a request.
     */
    TCOPA_BLOCK_SZX_VAL_7       = 0

} tcoap_blockwise_szx;


typedef struct tcoap_blockwise_data {

    struct {
        /**
        * size of block = 2 ^ (szx + 4)
        * szx from 0 to 6
        * szx 7 is reserved (should not use it)
        */
        uint8_t block_szx   : 3;

        uint8_t more        : 1;         /* more (not last block) */
    } opt;

    union {
        uint8_t num8[4];
        uint32_t num32;
    } number;                            /* number of block, from 0 */

} tcoap_blockwise_data;



/**
 * @brief Get block size by SZX value
 *
 * @param szx - a three-bit unsigned integer indicating the size of a block to the power of two.
 *
 */
uint16_t tcoap_decode_szx_to_size(const uint8_t szx);


/**
 * @brief Fill block2 option
 *
 * @param option - pointer on the 'tcoap_option_data' struct
 * @param bw - pointer on the block2 data
 * @param value - buffer for storing encoded value (max length is 3)
 *
 */
void tcoap_fill_block2_opt(tcoap_option_data * const option, const tcoap_blockwise_data * const bw, uint8_t * const value);


/**
 * @brief Extract block2 value from option
 *
 * @param block2 - raw option contains block2
 * @param bw - pointer on the block2 data to store value
 *
 */
void tcoap_extract_block2_from_opt(const tcoap_option_data * const block2, tcoap_blockwise_data * const bw);



/**
 * @brief Find an option by its number
 *
 * @param options - list of options
 * @param opt_num - number of option
 *
 * @return pointer to the found option or NULL if option is absent
 */
const tcoap_option_data * tcoap_find_option_by_number(const tcoap_option_data * options, const uint16_t opt_num);



#endif /* __TCOAP_HELPERS_H */
