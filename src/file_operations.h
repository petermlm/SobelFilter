#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "macros.h"

void readFile(char *file_name, byte **buffer, int buffer_size);
void writeFile(char *file_name, byte *buffer, int buffer_size);

#endif

