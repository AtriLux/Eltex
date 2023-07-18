#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char* prog;
    if (!strcmp(argv[1],"max") || !strcmp(argv[1],"sum")) {
        prog = argv[1];
    }
    else {
        char path[30] = "/usr/bin/";
        strcat(path, argv[1]);
        prog = path;
    }
    argv[1] = "";
    execv(prog, argv);
}