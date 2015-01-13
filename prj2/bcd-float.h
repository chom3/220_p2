#ifndef _BCD_FLOAT_H_
#define _BCD_FLOAT_H_

#include <inttypes.h> //defines uint_least64_t (at least 64 bits unsigned)
#include <stdbool.h>  //defines bool, true, false

/** BCD Floats implemented as per comment for blog post at
 *  <http://aplawrence.com/Basics/packedbcd.html>.
 *
 *  Specifically, a BcdFloat consists of a 64-bit word containing 16
 *  4-bit nybbles.  15 BCD digits are packed into the 15 least
 *  significant nybbles of the word.  The most significant nybble is
 *  a special nybble interpreted as follows:
 *
 *    + The MSB of the nybble contains the sign for the BcdFloat:
 *      0: non-negative; 1: negative.
 *
 *    + The other 3 bits of the nybble give the position of the
 *      decimal point within the above 15 BCD digits.  Specifically,
 *      those 3 bits are interpreted as an unsigned binary number 0 -
 *      7, giving the number of digits to the right of the decimal
 *      point.
 *
 *  It follows that this representation can exactly represent all
 *  decimal numbers with non-zero magnitudes having representations
 *  between 0.000_000_1 and 999_999_999_999_999 (the underscores are
 *  for readability).
 *
 *  With the above implementation of a BcdFloat, there are 16 possible
 *  representations for 0.  To disambiguate, we require 0 be
 *  represented by only one of these representations: the
 *  one with all bits 0.  The other 15 representations of
 *  0 are in error and referred to as error-0's.
 *
 *  Note that the BcdFloat with value 123 can be represented as
 *  "123", "123.0", "123.00", etc.  We say that a BcdFloat is
 *  normalized if there is no sequence of trailing 0's after
 *  the decimal point.  Hence, the normalized representation
 *  of 123 is "123"; similarly, the normalized representation
 *  of "1.2300" is "1.23".
 */

/** Define BcdFloat type as an unsigned int type which is at least
 *  64-bits (uint_least64_t is a C99 type which makes that guarantee).
 */
typedef uint_least64_t BcdFloat;

/** Important BcdFloat parameters */
enum {
  BCD_FLOAT_BITS = 64,          /** total # of bits in a BCD float */
  BCD_FLOAT_MAX_DECIMALS = 7,   /** max # of digits after decimal point */
  BCD_FLOAT_MAX_DIGITS =        /** max # of digits in a BCD float */
    BCD_FLOAT_BITS/4 - 1,
  BCD_FLOAT_MAX_STRING_LENGTH = /** max string length for BcdFloat */
    1 +                         // sign
    BCD_FLOAT_MAX_DIGITS +      // max # of digits
    1                           // optional decimal point within digits
};

/** The canonical representation of 0 */
#define BCD_FLOAT_ZERO (UINT64_C(0))

/** An error-0 which is used as a canonical representation of an error */
#define BCD_FLOAT_ERROR  ((UINT64_C(0x1)) << (BCD_FLOAT_BITS - 1))


/** Return true iff f is an error-0. */
inline bool
is_bcd_float_error_0(BcdFloat f)
{
  const unsigned long mask = UINT64_C(0xF) << (BCD_FLOAT_BITS - 4);
  return (f & ~mask) == 0 && (f & mask) != 0;
}

/** Return BcdFloat for the decimal number specified by the
 *  '\0'-terminated string text which should specify a optionally
 *  signed ('+' or '-') decimal number which may or may not
 *  contain a single decimal point.
 *
 *  The number of digits after the decimal point in the returned value
 *  should be equal to the number of digits after the decimal point
 *  in text[].
 *
 *  If text[] is not valid or the number represented by text is not
 *  exactly representable by a BcdFloat, then return BCD_FLOAT_ERROR.
 */
BcdFloat text_to_bcd_float(const char text[]);

/** Convert the BcdFloat f to its nul-terminated string representation
 *  in text[] (which is assumed to have space for at least
 *  BCD_FLOAT_MAX_STRING_LENGTH + 1 characters).  Avoid non-significant
 *  zero's before the decimal point.
 */
void bcd_float_to_text(const BcdFloat f, char text[]);

#endif //ifndef _BCD_FLOAT_H_