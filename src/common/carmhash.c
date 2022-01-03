#include "carmhash.h"

#include <ctype.h>
#include <string.h>

void
hash_reset(c2_state_t *state) {
    memset(state, 0, sizeof(c2_state_t));
}

void
hash_update(c2_state_t *state, const char *txt) {
    while (*txt != '\0') {
        uint8_t letterCode = (uint8_t)tolower(*txt) - 'a' + 22;
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
