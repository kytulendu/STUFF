/*
* ============================================================================
* Convert Thai Easy Writer to CU-Writer (TIS-620).
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
#include <string.h>

#include "ku2std.h"

#define CR              0x0D            /* Return */
#define LF              0x0A            /* Line feed */
#define SPACE           0x20

#define BUFFERSIZE 1280

FILE *inFile, *outFile;
unsigned char *readBuffer;
unsigned char *writeBuffer;
unsigned int file_offset, file_size, read_size, output_size;

int process(unsigned char *ibuff, unsigned char *obuff, unsigned int lenght)
{
    unsigned char *middle;
    unsigned char *lower;
    unsigned char *upper;
    unsigned int i, tmp;
    int count = 0;
    int c = 0;

    if (lenght < 256)
    {
        return 0;
    }

    for (i = 0; i < lenght; i++)
    {
        middle = ibuff + 80;
        lower = ibuff + 160;
        upper = ibuff;

        /*
        * middle character
        */

        switch (*middle)
        {
            case CR:
            {
                *obuff = CR;            obuff++; count++;
                *obuff = LF;            obuff++; count++;
                /* next line record */
                tmp = (80 + (80 - c) + 80 + 16);
                ibuff += tmp;
                i += tmp;
                c = 0;
                continue;
            }

            /* control code */
            case 0x9f:
            {
                switch (*(middle + 1))
                {
                    /* enlarge character */
                    case 'A':
                        *obuff = 0x05;  obuff++; count++;
                        break;
                    /* bold character */
                    case 'B':
                        *obuff = 0x02;  obuff++; count++;
                        break;
                    /* small character */
                    case 'E':
                        //fprintf(stderr, "small\n");
                        break;
                    /* condensed character */
                    case 'Q':
                        //fprintf(stderr, "condensed\n");
                        break;
                    /* underline character */
                    case 'S':
                        *obuff = 0x13;  obuff++; count++;
                        break;
                }

                /* skip character following 0x9f */
                ibuff++; i++; c++;

                ibuff++;
                c++;

                continue;
            }

            case 0x20:
            {
                /* superscript */
                if ((*upper >= 0x30) && (*upper <= 0x39))
                {
                    *obuff = 0x14;      obuff++; count++;
                    *obuff = *upper;    obuff++; count++;
                    *obuff = 0x14;      obuff++; count++;
                    break;
                }
                /* subscript */
                else if ((*lower >= 0x30) && (*lower <= 0x39))
                {
                    *obuff = 0x16;      obuff++; count++;
                    *obuff = *lower;    obuff++; count++;
                    *obuff = 0x16;      obuff++; count++;
                    break;
                }
                /* fall through */
            }
            default:
            {
                *obuff = *middle;       obuff++; count++;
            }
        }

        /*
        * lower character
        */

        if ((*lower == 0xd7) || (*lower == 0xd8))
        {
            *obuff = *lower;            obuff++; count++;
        }

        /*
        * upper character
        */

        /* upper character is not combined character */
        if ((*upper >= 0xd9) && (*upper <= 0xe4))
        {
            *obuff = *upper;            obuff++; count++;
        }
        /* upper character is combined character */
        else if ((*upper >= 0xe6) && (*upper <= 0xfe))
        {
            /* de-combine combined character */
            if ((*upper >= 0xe6) && (*upper <= 0xe9))
            {
                *obuff = 0xde;          obuff++; count++;
                *obuff = *upper - 6;    obuff++; count++;
            }
            else if ((*upper >= 0xea) && (*upper <= 0xed))
            {
                *obuff = 0xdd;          obuff++; count++;
                *obuff = *upper - 10;   obuff++; count++;
            }
            else if ((*upper >= 0xee) && (*upper <= 0xf2))
            {
                *obuff = 0xd9;          obuff++; count++;
                *obuff = *upper - 14;   obuff++; count++;
            }
            else if ((*upper >= 0xf3) && (*upper <= 0xf6))
            {
                *obuff = 0xda;          obuff++; count++;
                *obuff = *upper - 19;   obuff++; count++;
            }
            else if ((*upper >= 0xf7) && (*upper <= 0xfa))
            {
                *obuff = 0xdb;          obuff++; count++;
                *obuff = *upper - 23;   obuff++; count++;
            }
            else if ((*upper >= 0xfb) && (*upper <= 0xfe))
            {
                *obuff = 0xdc;          obuff++; count++;
                *obuff = *upper - 27;   obuff++; count++;
            }
        }

        ibuff++;
        c++;
    }

    /* rewind obuff pointer */
    obuff -= count;

    /* convert from Kaset to TIS-620 */
    for (i = 0; i < count; i++)
    {
        *obuff = ku2std(*obuff);
        obuff++;
    }

    return count;
}

void usage(void)
{
    fprintf(stderr, "Convert Thai Easy Writer to CU-Writer (TIS-620).\n");
    fprintf(stderr, "By Khralkatorrix.\n\n");
    fprintf(stderr, "Usage: thi2cw <input file> <output file>\n");
}

int main(int argc, char **argv)
{
    int hreaded = 0, f_recs, f_lines, f_pages, f_rmargin;

    if (argc != 3)
    {
        usage();
        exit(1);
    }

    if (strcmp(argv[1], argv[2]) == 0)
    {
        fprintf(stderr, "Error: Can't use same file name.\n");
        exit(1);
    }

    if ((inFile = fopen(argv[1], "rb")) == NULL)
    {
        fprintf(stderr, "Error: Can't open %s for reading.\n", argv[1]);
        exit(1);
    }
    if ((outFile = fopen(argv[2], "wb")) == NULL)
    {
        fprintf(stderr, "Error: Can't open %s for writing.\n", argv[2]);
        exit(1);
    }

    if ((readBuffer = malloc(BUFFERSIZE)) == NULL)
    {
        fprintf(stderr, "Error: Can't allocate memory.\n");
        exit(1);
    }
    if ((writeBuffer = malloc(BUFFERSIZE)) == NULL)
    {
        fprintf(stderr, "Error: Can't allocate memory.\n");
        exit(1);
    }

    /* get input file size */
    fseek(inFile, 0, SEEK_END);
    file_size = ftell(inFile);
    fseek(inFile, 0, SEEK_SET);

    /* process 5 records (1280 bytes) each */
    for (file_offset = 0; file_offset < file_size ; file_offset += BUFFERSIZE)
    {
        if ((file_size - file_offset) < BUFFERSIZE)
        {
            read_size = file_size - file_offset;
        }
        else
        {
            read_size = BUFFERSIZE;
        }

        if (fread(readBuffer, sizeof(unsigned char), read_size, inFile) != read_size)
        {
            fprintf(stderr, "Error: Reading file failed.\n");
            exit(1);
        }

        /* file header have been read? */
        if (!hreaded)
        {
            f_recs = (unsigned int) readBuffer[0];
            f_lines = f_recs - 5;               /* 5 records are file header */
            f_pages = (unsigned int) readBuffer[80];
            f_rmargin = (unsigned int) readBuffer[256]; /* usually is 75 */
            fprintf(stderr, "%d bytes, %d records, %d lines, %d pages, right margin %d.\n",
                    file_size, f_recs, f_lines, f_pages, f_rmargin);
            hreaded = 1;
            continue;                           /* skip */
        }

        /* process the records */
        output_size = process(readBuffer, writeBuffer, read_size);

        if (fwrite(writeBuffer, sizeof(unsigned char), output_size, outFile) != output_size)
        {
            fprintf(stderr, "Error: Writing file failed.\n");
            exit(1);
        }
    }

    fprintf(stderr, "Finished!\n");

    fclose(inFile);
    fclose(outFile);
    free(readBuffer);
    free(writeBuffer);

    return 0;
}
