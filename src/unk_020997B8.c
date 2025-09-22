#include "unk_020997B8.h"

#include <nitro.h>
#include <string.h>

#include "constants/moves.h"

#include "struct_defs/species.h"
#include "struct_defs/struct_020997B8.h"

#include "heap.h"
#include "moves.h"
#include "pokemon.h"

RelearnMoveData *RelearnMoveData_New(u32 heapID)
{
    RelearnMoveData *relearnData = Heap_Alloc(heapID, sizeof(RelearnMoveData));

    memset(relearnData, 0, sizeof(RelearnMoveData));
    return relearnData;
}

void RelearnMoveData_Free(RelearnMoveData *relearnData)
{
    Heap_Free(relearnData);
}

u16 *GetRelearnableMoves(Pokemon *mon, u32 heapID)
{
    u16 *learnset;
    u16 *relearnList;
    u16 knownMoves[LEARNED_MOVES_MAX];
    u16 species;
    u8 level;
    u8 form;
    u8 moveIdx, learnsetIdx, relearnIdx;

    species = (u16)Pokemon_GetValue(mon, MON_DATA_SPECIES, NULL);
    form = (u8)Pokemon_GetValue(mon, MON_DATA_FORM, NULL);
    level = (u8)Pokemon_GetValue(mon, MON_DATA_LEVEL, NULL);

    for (learnsetIdx = 0; learnsetIdx < LEARNED_MOVES_MAX; learnsetIdx++) {
        knownMoves[learnsetIdx] = (u16)Pokemon_GetValue(mon, MON_DATA_MOVE1 + learnsetIdx, NULL);
    }

    learnset = Heap_Alloc(heapID, sizeof(SpeciesLearnset));
    relearnList = Heap_Alloc(heapID, sizeof(SpeciesLearnset));

    Pokemon_LoadLevelUpMovesOf(species, form, learnset);

    relearnIdx = 0;

    for (learnsetIdx = 0; learnsetIdx < sizeof(SpeciesLearnset) / 2; learnsetIdx++) {
        if (learnset[learnsetIdx] == LEARNSET_ALL_SLOTS_FILLED) {
            relearnList[relearnIdx] = LEARNSET_ALL_SLOTS_FILLED;
            break;
        } else if (((learnset[learnsetIdx] & 0xFE00) >> 9) > level) {
            continue;
        } else {
            learnset[learnsetIdx] &= 0x1FF;

            // Check if move is already known
            for (moveIdx = 0; moveIdx < LEARNED_MOVES_MAX; moveIdx++) {
                if (learnset[learnsetIdx] == knownMoves[moveIdx]) {
                    break;
                }
            }

            // True if move is not known
            if (moveIdx == LEARNED_MOVES_MAX) {

                // Check if move is already in relearnable list
                for (moveIdx = 0; moveIdx < relearnIdx; moveIdx++) {
                    if (relearnList[moveIdx] == learnset[learnsetIdx]) {
                        break;
                    }
                }

                // True if move is not already in relearnable list so add it
                if (moveIdx == relearnIdx) {
                    relearnList[relearnIdx] = learnset[learnsetIdx];
                    relearnIdx++;
                }
            }
        }
    }

    Heap_Free(learnset);

    return relearnList;
}

BOOL HasRelearnableMoves(u16 *relearnableMoves)
{
    if (relearnableMoves[0] == LEARNSET_ALL_SLOTS_FILLED) {
        return FALSE;
    }

    return TRUE;
}
