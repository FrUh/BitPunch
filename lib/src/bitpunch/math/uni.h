/*
This file is part of BitPunch
Copyright (C) 2016 Frantisek Uhrecky <frantisek.uhrecky[what here]gmail.com>
Copyright (C) 2016 Marek Klein  <kleinmrk[what here]gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef BPU_UNI_H
#define BPU_UNI_H

#include "unitypes.h"

#include <bitpunch/config.h>
#include <string.h>
#include <stdlib.h>

#ifdef BPU_CONF_PRINT
/* ==================================== Print functions ==================================== */
// TODO: Be enable to turn off print function, to not compile in in code
/**
* Print number as binary string in big endian so msb is first printed. Do not print new line at the end.
* Example: number 21 -> 0001 0101
* @param in input of max 64 bits
* @param len print len
*/
/// Print number as binary string in big endian so msb is first printed.
void BPU_printBinaryMsb(uint32_t in, int len);

/**
* Print number as binary string in big endian so msb is first printed. Print also new line at the end.
* Example: number 21 -> 0001 0101
* @param in input of max 64 bits
* @param len print len
*/
/// Print number as binary string in big endian so msb is first printed.
void BPU_printBinaryMsbLn(uint32_t in, int len);

/**
* Print number as binary string in big endian so msb is first printed. Do not print new line at the end.
* Example: number 21 -> 0001 0101
* It will be padded to 64 bits.
* @param in input of max 64 bits
*/
/// Print number as binary string in big endian so msb is first printed.
void BPU_printBinaryMsb32(uint32_t in);

/**
* Print number as binary string in big endian so msb is first printed. Print also new line at the end.
* Example: number 21 -> 0001 0101
* It will be padded 64 bits.
* @param in input of max 64 bits
*/
/// Print number as binary string in big endian so msb is first printed.
void BPU_printBinaryMsb32Ln(uint32_t in);

/**
* Print number as binary string in little endian so lsb is first printed. Do not print new line at the end.
* Example: number 21 -> 1010 1000
* @param in input of max 64 bits
* @param len print len
*/
/// Print number as binary string in little endian so lsb is first printed.
void BPU_printBinaryLsb(uint32_t in, int len);

/**
* Print number as binary string in little endian so lsb is first printed. Print also new line at the end.
* Example: number 21 -> 1010 1000
* @param in input of max 64 bits
* @param len print len
*/
/// Print number as binary string in little endian so lsb is first printed.
void BPU_printBinaryLsbLn(uint32_t in, int len);

/**
* Print number as binary string in little endian so lsb is first printed. Do not print new line at the end.
* Example: number 21 -> 1010 1000
* It will be padded to 64 bits.
* @param in input of max 64 bits
*/
/// Print number as binary string in little endian so lsb is first printed.
void BPU_printBinaryLsb32(uint32_t in);

/**
* Print number as binary string in little endian so lsb is first printed. Print also new line at the end.
* Example: number 21 -> 1010 1000
* It will be padded 64 bits.
* @param in input of max 64 bits
*/
/// Print number as binary string in little endian so lsb is first printed.
void BPU_printBinary32LsbLn(uint32_t in);

/**
* Print vector GF2 with new line.
* @param v vector
*/
void BPU_printElementArray(const BPU_T_Element_Array *a);

/**
 * @brief BPU_printElementArrayMsb Most significant bit is printed first.
 * @param v
 */
void BPU_printElementArrayMsb(const BPU_T_Element_Array* a);

/**
 * @brief BPU_printElementArrayOnes Print only ones.
 * @param vec
 */
void BPU_printElementArrayOnes(const BPU_T_Element_Array *a);

/* ------------------------------------ Print functions ------------------------------------ */
#endif // BPU_CONF_PRINT

/**
 * Check if is set bit at n-th index makro.
 * @param w bit word to check
 * @param n index of bit to check, starts from 0
 * @return 1 - is set, else zero
 */
 /// Check if is set bit at n-th index.
#define BPU_getBit(w, n) ((int)((((uint32_t)w) >> (n)) & 1u))

/**
* Check if is set bit at s, t position in vector.
* @param v_pointer GF2 vector address
* @param t is col
* @return 1 - is set, else zero
*/
/// Check if is set bit at i-th position in vector.
#define BPU_elementArrayGetBit(a_pointer, i) (BPU_getBit((a_pointer)->elements[(i) / (a_pointer)->element_bit_size], (i) % (a_pointer)->element_bit_size))

/**
 * Set bit in vector GF2 at index i
 * @param  v_pointer address to matrix GF2
 * @param  i         col index
 * @param  bit       bit value 0 or 1
 */
#define BPU_elementArraySetBit(a_pointer, i, bit)  if (bit) { \
                                                (a_pointer)->elements[(i) / (a_pointer)->element_bit_size] |= ((BPU_T_Element) 1) << ((i) % (a_pointer)->element_bit_size);\
                                                } \
                                                else { \
                                                    /* this is like: 00101111 ^ 00000100 = 00101011 */\
                                                    (a_pointer)->elements[(i) / (a_pointer)->element_bit_size] &= ((BPU_T_Element) (0xFFFFFFFFu)) ^ (((BPU_T_Element) 1) << ((i) % (a_pointer)->element_bit_size));\
                                                }

/**
 * Null element array.
 * @param[out]  a_pointer pointer to element array
 */
/// Null element array.
#define BPU_elementArrayNull(a_pointer) memset((void *) ((a_pointer)->elements), 0, (a_pointer)->element_bit_size / 8 * (a_pointer)->array_length)

/**
 * Free dynamically element array.
 * @param[out] *m address of vector object
 */
/// Free dynamically or statically allocated element array
void BPU_elementArrayFree(BPU_T_Element_Array **a);

/**
 * Allocate memory for element array. It also nulls array.
 * @param len len of vector
 * @return on succes 0, else error
 */
int BPU_elementArrayMalloc(BPU_T_Element_Array **a, int len);

/**
 * @brief Resize element array.
 * @param v
 * @param len
 * @return
 */
int BPU_elementArrayResize(BPU_T_Element_Array *a, int len);

/**
 * @brief Malloc array elements and set to zero.
 * @param v
 * @param len
 * @return
 */
int BPU_elementArrayMallocElements(BPU_T_Element_Array *a, int len);

#endif // BPU_UNI_H
