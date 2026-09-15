/*
* ============================================================================
* Convert TIS-620 CW to Loxley Thai character code.
* By Khralkatorrix <https://github.com/kytulendu>.
*
* This is free and unencumbered software released into the public domain.
*
* Anyone is free to copy, modify, publish, use, compile, sell, or
* distribute this software, either in source code form or as a compiled
* binary, for any purpose, commercial or non-commercial, and by any
* means.

* In jurisdictions that recognize copyright laws, the author or authors
* of this software dedicate any and all copyright interest in the
* software to the public domain. We make this dedication for the benefit
* of the public at large and to the detriment of our heirs and
* successors. We intend this dedication to be an overt act of
* relinquishment in perpetuity of all present and future rights to this
* software under copyright law.

* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*
* For more information, please refer to <http://unlicense.org/>
*
* ============================================================================
*/

#define UNDEF 0x020

/* TIS-620 CW (TIS-620 CU-Writer) to Loxley conversion table */
const unsigned char std_to_ly[] = {
    UNDEF, UNDEF, UNDEF, UNDEF, UNDEF, UNDEF, UNDEF, UNDEF, UNDEF, UNDEF, UNDEF, UNDEF, UNDEF, UNDEF, UNDEF, 0x08a,
    0x088, 0x089, 0x087, 0x086, UNDEF, 0x085, 0x084, UNDEF, 0x080, 0x081, 0x082, 0x083, UNDEF, UNDEF, UNDEF, UNDEF,
    0x020, 0x0a1, 0x0a2, UNDEF, 0x0a3, UNDEF, 0x0a4, 0x0a5, 0x0a6, 0x0a7, 0x0a8, 0x0a9, 0x0aa, 0x0ab, 0x0ac, 0x0ad,
    0x0ae, 0x0af, 0x0b0, 0x0b1, 0x0b2, 0x0b3, 0x0b4, 0x0b5, 0x0b6, 0x0b7, 0x0b8, 0x0b9, 0x0ba, 0x0bb, 0x0bc, 0x0bd,
    0x0be, 0x0bf, 0x0c0, 0x0c1, 0x0cb, 0x0c2, 0x0cc, 0x0c3, 0x0c4, 0x0c5, 0x0c6, 0x0c7, 0x0c8, 0x0c9, 0x0ca, 0x0e3,
    0x0cd, 0x0d0, 0x0ce, 0x0cf, 0x0d2, 0x0d3, 0x0d4, 0x0d5, 0x0d6, 0x0d7, UNDEF, UNDEF, UNDEF, UNDEF, UNDEF, UNDEF,
    0x0d8, 0x0d9, 0x0da, 0x0db, 0x0dc, UNDEF, 0x0e2, 0x0d1, 0x0dd, 0x0de, 0x0df, 0x0e0, 0x0e1, 0x0e4, UNDEF, UNDEF,
    0x090, 0x091, 0x092, 0x093, 0x094, 0x095, 0x096, 0x097, 0x098, 0x099, UNDEF, UNDEF, UNDEF, UNDEF, UNDEF, UNDEF,
};

/** Convert TIS-620 CW (TIS-620 CU-Writer) to Loxley.
*  \param[in]  p_stdcode        TIS-620 character code.
*  \return unsigned char        Loxley character code. */
unsigned char std2ly(unsigned char p_stdcode)
{
    return ((p_stdcode >= 0x80) ? std_to_ly[p_stdcode - 0x80] : p_stdcode);
}
