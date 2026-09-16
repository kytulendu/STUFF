/*
* ============================================================================
* Convert CU-Writer (TIS-620) to iRC Standard Word.
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

#include <stdio.h>

#include "cw2stw.h"

#define __EOF 0x1A /* End of file */

int process(unsigned char *ibuff, unsigned char *obuff, unsigned int lenght)
{
    unsigned char c;
    unsigned int i;
    int count = 0;

    for (i = 0; i < lenght; i++)
    {
        c = *ibuff;
        /* skip option at the end of file */
        if (c == __EOF)
        {
            break;
        }

        /* convert CU-Writer control code to iRC Standard Word */
        if (c == 0x05)              /* enlarge */
        {
            c = 0x04;
        }
        else if (c == 0x12)         /* double-underline */
        {
            c = 0x13;
        }
        else if (c == 0x17)         /* italic */
        {
            c = 0x0c;
        }

        *obuff = cw2stw(c);

        ibuff++;
        obuff++;
        count++;
    }
    return count;
}

void usage(void)
{
    fprintf(stderr, "Convert CU-Writer (TIS-620) to iRC Standard Word.\n");
    fprintf(stderr, "By Khralkatorrix.\n\n");
    fprintf(stderr, "Usage: cw2stw <input file> <output file>\n");
}
