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

#include <stdio.h>
#include <stdlib.h>

#include "std2ly.h"

void usage(void)
{
    puts("Convert TIS-620 CW to Loxley Thai character code.");
    puts("By Khralkatorrix.\n\n");
    puts("Usage: STD2LY [input file] [output file]");
}

int main(int argc, char *argv[])
{
    FILE *inFile, *outFile;
    unsigned char character;

    if (argc != 3)
    {
        usage();
        exit(0);
    }

    if ((inFile = fopen(argv[1], "rb")) == NULL)
    {
        puts("Can't open input file.");
        exit(0);
    }
    if ((outFile = fopen(argv[2], "wb")) == NULL)
    {
        puts("Can't open output file.");
        exit(0);
    }

    do {
        character = fgetc(inFile);
        if (feof(inFile))
        {
            break;
        }
        fprintf(outFile, "%c", std2ly(character));
    } while (1);

    puts("Finished!");

    fclose(inFile);
    fclose(outFile);
    return 0;
}
