#ifndef POKEPLATINUM_UNK_020997B8_H
#define POKEPLATINUM_UNK_020997B8_H

#include "struct_defs/struct_020997B8.h"

RelearnMoveData *RelearnMoveData_New(u32 heapID);
void RelearnMoveData_Free(RelearnMoveData *relearnData);
u16 *GetRelearnableMoves(Pokemon *mon, u32 heapID);
BOOL HasRelearnableMoves(u16 *relearnList);

#endif // POKEPLATINUM_UNK_020997B8_H
