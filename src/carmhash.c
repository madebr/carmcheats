#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  uint32_t sum;
  uint32_t code1;
  uint32_t code2;
} c2_state_t;

typedef struct {
  uint32_t code1;
  uint32_t code2;
} c2_hash_t;

void
hash_reset(c2_state_t *state) {
  memset(state, 0, sizeof(c2_state_t));
}

void
hash_update(c2_state_t *state, const char *txt) {
  while (*txt != '\0') {
    uint8_t letterCode = tolower(*txt) - 'a' + 22;
    state->sum += letterCode;
    state->code1 += letterCode << 11;
    state->code1 = (state->code1 >> 17) + (state->code1 << 4);
    state->code2 = (state->code2 >> 29) + (state->code2 << 3) + letterCode * letterCode;
    txt += 1;
  }
}

void
hash_digest(const c2_state_t *state, c2_hash_t *hash) {
	hash->code1 = (state->code1 >> 11) + (state->sum << 21);
	hash->code2 = state->code2;
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
#ifdef _WIN32
    fprintf(stderr, "Need at least one argument\n");
    return 1;
#else
    char *line = NULL;
    size_t lineSize = 0;
    while (!feof(stdin)) {
      ssize_t nb = getline(&line, &lineSize, stdin);
      line[nb - 1] = '\0';
      printf("got '%s'\n", line);
    }
    free(line);
    return 0;
#endif
  }
  c2_state_t state;
  c2_hash_t hash;
  for (int i = 1; i < argc; i += 1) {
    hash_reset(&state);
    hash_update(&state, argv[i]);
    hash_digest(&state, &hash);
    printf("%08x:%08x %s\n", hash.code1, hash.code2, argv[i]);
  }
  return 0;
}
