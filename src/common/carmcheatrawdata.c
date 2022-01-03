#include "carmcheatrawdata.h"

#include "carmhash.h"

#include <stdlib.h>

static uint32_t
buffer_to_uint32(const uint8_t *buffer) {
    return (buffer[0] << 0) | (buffer[1] << 8) | (buffer[2] << 16) | (buffer[3] << 24);
}

static void
uint32_to_buffer(uint8_t *buffer, uint32_t v) {
    buffer[0] = v;
    buffer[1] = v >> 8;
    buffer[2] = v >> 16;
    buffer[3] = v >> 24;
}

int
carm_list_cheats(FILE *f, const CarmGameCheats *cheatData, carm_list_callback_fn callback, void *userData) {
    int allOk = 1;
    CarmCheatVerifyResult result;
    result.cheatData = cheatData;
    result.cheatType = CARM_CHEAT_VERIFY_FRAGMENT;
    for(size_t fragment_i = 0; fragment_i < cheatData->nbFragments; fragment_i += 1) {
        uint8_t buffer[256];
        result.index = fragment_i;
        result.type = CARM_CHEAT_VERIFY_RESULT_OK;
        const CarmCheatFragment *fragment = &cheatData->fragments[fragment_i];
        int res = fseek(f, fragment->fileOffset, SEEK_SET);
        if ((res < 0) || (fragment->rawDataSize > sizeof(buffer))) {
            result.type |= CARM_CHEAT_VERIFY_RESULT_NOTFOUND;
        } else {
            size_t nbRead = fread(buffer, 1, fragment->rawDataSize, f);
            if (nbRead != fragment->rawDataSize) {
                result.type |= CARM_CHEAT_VERIFY_RESULT_NOTFOUND;
            } else {
                if (fragment->code1Offset != CCT_CODE_OFFSET_UNUSED) {
                    result.hash.code1 = buffer_to_uint32(buffer + fragment->code1Offset);
                }
                if (fragment->code2Offset != CCT_CODE_OFFSET_UNUSED) {
                    result.hash.code2 = buffer_to_uint32(buffer + fragment->code2Offset);
                }
                for (uint32_t offset = 0; offset < fragment->rawDataSize; offset += 1) {
                    uint8_t c = buffer[offset];
                    if ((fragment->code1Offset != CCT_CODE_OFFSET_UNUSED) &&
                        ((offset >= fragment->code1Offset) && (offset < fragment->code1Offset + 4))) {
                        if (c != fragment->rawData[offset]) {
                            result.type |= CARM_CHEAT_VERIFY_RESULT_HASH_DIFFERS;
                        }
                    } else if ((fragment->code2Offset != CCT_CODE_OFFSET_UNUSED) &&
                        ((offset >= fragment->code2Offset) && (offset < fragment->code2Offset + 4))) {
                        if (c != fragment->rawData[offset]) {
                            result.type |= CARM_CHEAT_VERIFY_RESULT_HASH_DIFFERS;
                        }
                    } else if (c != fragment->rawData[offset]) {
                        result.type |= CARM_CHEAT_VERIFY_RESULT_NOTFOUND;
                    }
                }
            }
        }
        if (callback) {
            (*callback)(&result, userData);
        }
        allOk = allOk && ((result.type & CARM_CHEAT_VERIFY_RESULT_NOTFOUND) == 0);
    }

    result.cheatType = CARM_CHEAT_VERIFY_TABLE_ITEM;
    for(size_t tableItem_i = 0; tableItem_i < cheatData->table->nbItems; tableItem_i += 1) {
        uint8_t buffer[16];
        result.index = tableItem_i;
        result.type = CARM_CHEAT_VERIFY_RESULT_OK;
        const CarmCheatTableItem *tableItem = &cheatData->table->items[tableItem_i];
        int res = fseek(f, cheatData->table->fileOffset + tableItem_i * 16, SEEK_SET);
        if (res < 0) {
            result.type |= CARM_CHEAT_VERIFY_RESULT_NOTFOUND;
        } else {
            size_t nbRead = fread(buffer, 1, 16, f);
            if (nbRead != 16) {
                result.type |= CARM_CHEAT_VERIFY_RESULT_NOTFOUND;
            } else {
                result.hash.code1 = buffer_to_uint32(buffer + 0);
                result.hash.code2 = buffer_to_uint32(buffer + 4);
                for (int offset = 0; offset < 8; ++offset) {
                    uint8_t c = buffer[offset];
                    if (c != tableItem->rawData[offset]) {
                        result.type |= CARM_CHEAT_VERIFY_RESULT_HASH_DIFFERS;
                    }
                }
                for (int offset = 8; offset < 16; ++offset) {
                    uint8_t c = buffer[offset];
                    if (c != tableItem->rawData[offset]) {
                        result.type |= CARM_CHEAT_VERIFY_RESULT_NOTFOUND;
                    }
                }
            }
        }
        if (callback) {
            (*callback)(&result, userData);
        }
        allOk = allOk && ((result.type & CARM_CHEAT_VERIFY_RESULT_NOTFOUND) == 0);
    }
    return !allOk;
}

CarmModifiersType *
alloc_CarmModifersType(size_t nb) {
    CarmModifierType *items = (CarmModifierType *)calloc(nb, sizeof(CarmModifierType));
    CarmModifiersType *result = (CarmModifiersType *)malloc(sizeof(CarmModifiersType));
    result->nb = nb;
    result->items = items;
    return result;
}

void
free_CarmModifersType(CarmModifiersType *modifiers) {
    if (modifiers == NULL) {
        return;
    }
    for (size_t index = 0; index < modifiers->nb; index += 1) {
        free(modifiers->items[index].cheat);
    }
    free(modifiers->items);
    free(modifiers);
}

void
carm_patch_executable(FILE *f, const CarmModifiersType *modifiers, const CarmGameCheats *cheatData) {
    uint8_t buffer[4];
    for (size_t mod_i = 0; mod_i < modifiers->nb; mod_i += 1) {
        CarmModifierType *modifier = &modifiers->items[mod_i];
        c2_state_t state;
        c2_hash_t hash;
        hash_reset(&state);
        hash_update(&state, modifier->cheat);
        hash_digest(&state, &hash);
        switch (modifier->type) {
            case CARM_CHEAT_VERIFY_TABLE_ITEM:
                fseek(f, cheatData->table->fileOffset + 16 * modifier->index, SEEK_SET);
                uint32_to_buffer(buffer, hash.code1);
                fwrite(buffer, 4, 1, f);
                uint32_to_buffer(buffer, hash.code2);
                fwrite(buffer, 4, 1, f);
                break;
            case CARM_CHEAT_VERIFY_FRAGMENT:
                if (cheatData->fragments[modifier->index].code1Offset != CCT_CODE_OFFSET_UNUSED) {
                    fseek(f, cheatData->fragments[modifier->index].fileOffset + cheatData->fragments[modifier->index].code1Offset, SEEK_SET);
                    uint32_to_buffer(buffer, hash.code1);
                    fwrite(buffer, 4, 1, f);
                }
                if (cheatData->fragments[modifier->index].code2Offset != CCT_CODE_OFFSET_UNUSED) {
                    fseek(f, cheatData->fragments[modifier->index].fileOffset + cheatData->fragments[modifier->index].code2Offset, SEEK_SET);
                    uint32_to_buffer(buffer, hash.code2);
                    fwrite(buffer, 4, 1, f);
                }
                break;
        }
    }
}
