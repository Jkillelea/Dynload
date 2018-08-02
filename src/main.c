#include <stdio.h>
#include <dlfcn.h>
#include <bfd.h>

int main(int argc, char const *argv[]) {
    void *lib_handle;
    char *error_msg;
    int (*double_me)(int);
    void (*potato)();

    if ((lib_handle = dlopen("./lib/libfunction.so", RTLD_LAZY)) == NULL) {
        puts(dlerror());
        return 1;
    }

    double_me = dlsym(lib_handle, "double_me");
    if ((error_msg = dlerror()) != NULL) {
        puts(error_msg);
        dlclose(lib_handle);
        return 2;
    }

    potato = dlsym(lib_handle, "potato");
    if ((error_msg = dlerror()) != NULL) {
        puts(error_msg);
        dlclose(lib_handle);
        return 2;
    }

    for (int i = 0; i <= 10; i++) {
        printf("%d doubled is %d\n", i, double_me(i));
        potato();
    }

    dlclose(lib_handle);
    return 0;
}
