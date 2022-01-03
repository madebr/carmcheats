#include "carmcheatrawdata.h"
#include "carm2cheatrawdata.h"

#include <carmhash.h>
#include <carmutil.h>

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void
list_print_callback(CarmCheatVerifyResult* result, void *rawUserData) {
    (void)rawUserData;
    if ((result->type & CARM_CHEAT_VERIFY_RESULT_NOTFOUND) != 0) {
    } else {
        const char *cheat = "(unknown)";
        const char *description;
        char cheatIndexChar;
        switch (result->cheatType) {
        case CARM_CHEAT_VERIFY_TABLE_ITEM:
            if ((result->type & CARM_CHEAT_VERIFY_RESULT_HASH_DIFFERS) == 0) {
                cheat = result->cheatData->table->items[result->index].cheat;
            }
            description = result->cheatData->table->items[result->index].description;
            cheatIndexChar = 'T';
            break;
        case CARM_CHEAT_VERIFY_FRAGMENT:
            if ((result->type & CARM_CHEAT_VERIFY_RESULT_HASH_DIFFERS) == 0) {
                cheat = result->cheatData->fragments[result->index].cheat;
            }
            description = result->cheatData->fragments[result->index].description;
            cheatIndexChar = 'F';
            break;
        }
        char cheatIndex[8];
        sprintf(cheatIndex, "%c%02d", cheatIndexChar, result->index);
        printf("%-3s %08x:%08x:%-40s %s\n",
            cheatIndex,
            result->hash.code1,
            result->hash.code2,
            cheat,
            description);
    }
}

static CarmModifiersType *
parse_cheat_modifiers(const char *modifierStrings[], size_t nb, const CarmGameCheats *cheatData) {
    CarmModifiersType *modifiers = alloc_CarmModifersType(nb);
    for (size_t modIndex = 0; modIndex < nb; modIndex += 1) {
        char typeChar;
        unsigned index;
        char cheat[256];
        int nb = sscanf(modifierStrings[modIndex], "%c%u:%s", &typeChar, &index, cheat);

        if (nb != 3) {
            fprintf(stderr, "Error: %s -> Invalid format.\n", modifierStrings[modIndex]);
            goto err;
        }
        switch(typeChar) {
        case 'F':
            if (index >= cheatData->nbFragments) {
                fprintf(stderr, "Error: %s -> Index too high. (There are %zu fragments)\n", modifierStrings[modIndex], cheatData->nbFragments);
                goto err;
            }
            modifiers->items[modIndex].type = CARM_CHEAT_VERIFY_FRAGMENT;
            break;
        case 'T':
            if (index >= cheatData->table->nbItems) {
                fprintf(stderr, "Error: %s -> Index too high. (There are %zu table items)\n", modifierStrings[modIndex], cheatData->table->nbItems);
                goto err;
            }
            modifiers->items[modIndex].type = CARM_CHEAT_VERIFY_TABLE_ITEM;
            break;
        default:
            fprintf(stderr, "Error: %s -> Unknown type\n", modifierStrings[modIndex]);
            goto err;
        }
        modifiers->items[modIndex].index = index;
        modifiers->items[modIndex].cheat = strdup(cheat);
    }
    return modifiers;
err:
    free_CarmModifersType(modifiers);
    return NULL;
}

int main(int argc, char *argv[]) {
    int verbose = 1;
    int create_backup = 1;
    static struct option long_options[] = {
        {"brief",       no_argument, NULL, 'b'},
        {"no-backup",   no_argument, NULL, 'n'},
        {0, 0, 0, 0},
    };
    while (1) {
        int option_index;
        int c = getopt_long(argc, argv, "bn", long_options, &option_index);
        if (c == -1) {
            break;
        }
        switch (c) {
        case 'b':
            verbose = 0;
            break;
        case 'n':
            create_backup = 0;
            break;
        default:
            fprintf(stderr, "Unknown option\n");
            return 1;
        }
    }
    if (optind == argc) {
        fprintf(stderr, "Need filepath.\n");
        return 1;
    }
    const char *exePath = argv[optind];

    if (verbose) {
        printf("path: %s\n", exePath);
    }
    FILE *f = fopen(exePath, "rb");
    if (f == NULL) {
        printf("Could not open %s\n", exePath);
        return 1;
    }
    const CarmGameCheats *cheatData = carm2_game_cheats();
    if (verbose) {
        printf("%-3s %-17s %-40s %s\n", "id", "hash", "cheat", "description");
        for(int width = 100; width != 0; width -= 1) {
            putchar('=');
        }
        putchar('\n');
    }
    int res = carm_list_cheats(f, cheatData, verbose ? list_print_callback : NULL, NULL);
    if (verbose) {
        if (res == 0) {
            printf("File ok.\n");
        } else {
            printf("File was not ok.\n");
        }
    }
    fclose(f);
    CarmModifiersType *modifiers = parse_cheat_modifiers((const char **)(argv + optind + 1), argc - optind - 1, cheatData);
    if (modifiers == NULL) {
        return 1;
    }

    if (modifiers->nb == 0) {
        if (verbose) {
            printf("Don't create backup as no modifications are performed.\n");
        }
    } else if (create_backup) {
        char *exeFilename = carm_basename(exePath);
        char *backupFilename = (char *)malloc(strlen(exeFilename)+4+4+1);
        sprintf(backupFilename, "%s.bak", exeFilename);
        int retryCount = 0;
        while (1) {
            if (access(backupFilename, F_OK) != 0) {
                break;
            }
            sprintf(backupFilename, "%s.bak.%03d", exeFilename, retryCount);
            retryCount += 1;
        }
        printf("Writing backup: %s...", backupFilename);
        res = carm_copy_file(exePath, backupFilename);
        if (res != 0) {
            printf(" Fail\n");
            return 1;
        }
        printf(" Success\n");
        free(backupFilename);
        free(exeFilename);
    }

    f = fopen(exePath, "r+");
    if (f == NULL) {
        fprintf(stderr, "Could not open executable in read/update mode\n");
        return 1;
    }
    carm_patch_executable(f, modifiers, cheatData);
    if (ferror(f)) {
        fprintf(stderr, "Something went bad.\n");
        fclose(f);
    }
    fflush(f);
    fclose(f);

    free_CarmModifersType(modifiers);

    return res;
}
