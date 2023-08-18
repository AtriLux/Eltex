#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

extern double power2(double num);
extern double sqrt2(double num);

int main(int argc, char* argv[]) {
    double num = atof(argv[1]);

    void *lib = dlopen("/home/osboxes/Eltex/Module 5/Lab1/libdynamic.so", RTLD_LAZY);
    if (!lib) {
        fprintf(stderr, "dlopen() error: %s\n", dlerror());
        return 1;
    }

    double (*libfunc)(double x);
    libfunc = dlsym(lib, "power2");
    printf("power2(%0.3f) = ", num);
    printf("%0.3f\n", (*libfunc)(num));

    libfunc = dlsym(lib, "sqrt2");
    printf("sqrt2(%0.3f) = ", num);
    printf("%0.3f\n", (*libfunc)(num));

    dlclose(lib);
    return 0;
}