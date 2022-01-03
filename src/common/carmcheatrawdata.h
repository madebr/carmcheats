#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>

#include "carmhash.h"

enum {
    CCT_CODE_OFFSET_UNUSED = 0xffffffff,
};

typedef struct {
    uint32_t fileOffset;
    const uint8_t *rawData;
    size_t rawDataSize;
    const char *cheat;
    const char *description;
    uint32_t code1Offset;
    uint32_t code2Offset;
} CarmCheatFragment;

typedef struct {
    const uint8_t *rawData;
    const char *cheat;
    const char *description;
} CarmCheatTableItem;

typedef struct {
    uint32_t fileOffset;
    const CarmCheatTableItem *items;
    size_t nbItems;
} CarmCheatTable;

typedef struct CarmGameCheats {
    const char *gameDescription;
    const CarmCheatTable *table;
    const CarmCheatFragment *fragments;
    size_t nbFragments;
} CarmGameCheats;

typedef enum {
    CARM_CHEAT_VERIFY_TABLE_ITEM,
    CARM_CHEAT_VERIFY_FRAGMENT,
} CarmCheatVerifyType;

enum {
    CARM_CHEAT_VERIFY_RESULT_OK             = 0x0,
    CARM_CHEAT_VERIFY_RESULT_NOTFOUND       = 0x1,
    CARM_CHEAT_VERIFY_RESULT_HASH_DIFFERS   = 0x2,
};

typedef struct {
    const CarmGameCheats *cheatData;
    CarmCheatVerifyType cheatType;
    int index;
    int type;
    c2_hash_t hash;
} CarmCheatVerifyResult;

typedef void (*carm_list_callback_fn)(CarmCheatVerifyResult* result, void *userData);

int
carm_list_cheats(FILE *f, const CarmGameCheats *cheatData, carm_list_callback_fn callback, void *userData);

typedef struct {
    CarmCheatVerifyType type;
    int index;
    char *cheat;
} CarmModifierType;

typedef struct {
    size_t nb;
    CarmModifierType *items;
} CarmModifiersType;

CarmModifiersType *
alloc_CarmModifersType(size_t nb);

void
free_CarmModifersType(CarmModifiersType *modifiers);

void
carm_patch_executable(FILE *f, const CarmModifiersType *modifiers, const CarmGameCheats *cheatData);

#ifdef __cplusplus
} // extern "C"
#endif
