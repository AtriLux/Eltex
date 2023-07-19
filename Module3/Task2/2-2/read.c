#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

int main(int argc, char* argv[]) {
    FILE* file = fopen(argv[1], "r");
    if (!file) {
        perror("Open file");
        exit(EXIT_FAILURE);
    }
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char* buf = (char*)malloc(sizeof(char)*size);
    fread(buf, 1, size, file);
    puts(buf);

    fclose(file);
    free(buf);
}