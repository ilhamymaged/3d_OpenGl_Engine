#include <stdio.h>
#include <stdlib.h>
#include <utility.h>

char* read_file(char* path) {
    FILE* file = fopen(path, "rb");
    if (!file) {
        printf("Failed to open file: %s\n", path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    if (length <= 0) {
        printf("File is empty: %s\n", path);
        fclose(file);
        return NULL;
    }

    char* buffer = malloc(length + 1);
    if (!buffer) {
        printf("Malloc failed while reading file: %s\n", path);
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0'; 

    fclose(file);
    return buffer;
}
