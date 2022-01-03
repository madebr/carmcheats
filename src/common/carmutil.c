#include "carmutil.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
#define PATHSEP '\\'
#else
#define PATHSEP '/'
#endif

char *
carm_basename(const char *path) {
    const char *lastOcc = strrchr(path, PATHSEP);
    if (lastOcc == NULL) {
        char *basePath = (char *)malloc(strlen(path) + 1);
        strcpy(basePath, path);
        return basePath;
    } else {
        char *basePath = (char *)malloc(strlen(lastOcc + 1) + 1);
        strcpy(basePath, lastOcc + 1);
        return basePath;
    }
}

int
carm_copy_file(const char *src, const char *dst) {
    struct stat srcstat;
    char buffer[2048];
    int res = stat(src, &srcstat);
    if (res != 0) {
        return res;
    }
    FILE *fsrc = fopen(src, "rb");
    if (fsrc == NULL) {
        return 1;
    }
    FILE *fdst = fopen(dst, "wb");
    if (fdst == NULL) {
        return 1;
    }
    int nbread;
    while ((nbread = fread(buffer, 1, sizeof(buffer), fsrc)) != 0) {
        fwrite(buffer, 1, nbread, fdst);
    }
    fclose(fsrc);
    fclose(fdst);
    res = chmod(dst, srcstat.st_mode);
    return res;
}
