#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "macros.h"

int readFile(char *file_name, byte **buffer);
void writeFile(char *file_name, byte *buffer, int buffer_size);

#endif

