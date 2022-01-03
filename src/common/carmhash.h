#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

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
hash_reset(c2_state_t *state);

void
hash_update(c2_state_t *state, const char *txt);

void
hash_digest(const c2_state_t *state, c2_hash_t *hash);

#ifdef __cplusplus
} // extern "C"
#endif
