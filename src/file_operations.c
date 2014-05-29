#include "file_operations.h"

#include <stdio.h>
#include <stdlib.h>

#include "macros.h"

/*
 * Reads file to *buffer. Returns file size.
 */

int readFile(char *file_name, byte **buffer) {
    // Open
    FILE *file = fopen(file_name, "r");

    // Take file size
    fseek(file, 0, SEEK_END);
    int buffer_size = ftell(file);
    rewind(file);

    // Allocate memory for buffer
    *buffer = malloc(sizeof(byte) * buffer_size);

    // Read every char of file ONE BY ONE (not the whole thing at once)
    // We do this because this should look closer to the assembly implementation
    for(int i=0; i<buffer_size; i++) {
        (*buffer)[i] = fgetc(file);
    }

    // Close
    fclose(file);

    // Return
    return buffer_size;
}

/*
 * Writes the buffer to a file
 */

void writeFile(char *file_name, byte *buffer, int buffer_size) {
    // Open
    FILE *file = fopen(file_name, "w");

    // Write all
    for(int i=0; i<buffer_size; i++) {
        fputc(buffer[i], file);
    }

    // Close
    fclose(file);
}

