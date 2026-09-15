/*
* ============================================================================
* Common main program.
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

#define BUFFERSIZE 1024

FILE *inFile, *outFile;
unsigned char *readBuffer;
unsigned char *writeBuffer;
unsigned int file_offset, file_size, read_size, output_size;

void usage(void);
int process(unsigned char *ibuff, unsigned char *obuff, unsigned int lenght);

int main(int argc, char **argv)
{
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
        fprintf(stderr,"Error: Can't allocate memory.\n");
        exit(1);
    }
    if ((writeBuffer = malloc(BUFFERSIZE)) == NULL)
    {
        fprintf(stderr,"Error: Can't allocate memory.\n");
        exit(1);
    }

    /* get input file size */
    fseek(inFile, 0, SEEK_END);
    file_size = ftell(inFile);
    fseek(inFile, 0, SEEK_SET);

    /* Convert every BUFFERSIZE bytes */
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

        /* process the data */
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
