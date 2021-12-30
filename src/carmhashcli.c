#include "carmhash.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    c2_state_t state;
    c2_hash_t hash;
    if (argc == 1) {
#ifdef _WIN32
        fprintf(stderr, "Need at least one argument\n");
        return 1;
#else
        char *line = NULL;
        size_t lineSize = 0;
        while (1) {
            hash_reset(&state);
            ssize_t nb = getline(&line, &lineSize, stdin);
            if (feof(stdin)) {
                break;
            }
            line[nb - 1] = '\0';
            hash_update(&state, line);
            hash_digest(&state, &hash);
            printf("%08x:%08x:%s\n", hash.code1, hash.code2, line);
        }
        free(line);
        return 0;
#endif
    }
    for (int i = 1; i < argc; i += 1) {
        hash_reset(&state);
        hash_update(&state, argv[i]);
        hash_digest(&state, &hash);
        printf("%08x:%08x:%s\n", hash.code1, hash.code2, argv[i]);
    }
    return 0;
}
