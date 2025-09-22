#include "scrcmd_move_relearner.h"

#include <nitro.h>
#include <string.h>

#include "constants/moves.h"

#include "struct_defs/struct_020997B8.h"

#include "field_script_context.h"
#include "field_system.h"
#include "heap.h"
#include "inlines.h"
#include "party.h"
#include "pokemon.h"
#include "save_player.h"
#include "scrcmd.h"
#include "script_manager.h"
#include "unk_0203D1B8.h"
#include "unk_020997B8.h"

static void ShowMoveRelearner(ScriptContext *param0, u16 param1, Pokemon *param2, u16 *param3);

BOOL ScrCmd_SelectPartyMonMove(ScriptContext *ctx)
{
    u16 partySlot = ScriptContext_GetVar(ctx);
    void **partyData = FieldSystem_GetScriptMemberPtr(ctx->fieldSystem, SCRIPT_MANAGER_PARTY_MANAGEMENT_DATA);
    *partyData = FieldSystem_OpenSummaryScreenSelectMove(HEAP_ID_FIELD3, ctx->fieldSystem, partySlot);

    ScriptContext_Pause(ctx, ScriptContext_WaitForApplicationExit);
    return TRUE;
}

BOOL ScrCmd_GetSelectedPartyMonMove(ScriptContext *ctx)
{
    u16 *destVar = ScriptContext_GetVarPointer(ctx);
    void **partyData = FieldSystem_GetScriptMemberPtr(ctx->fieldSystem, SCRIPT_MANAGER_PARTY_MANAGEMENT_DATA);
    GF_ASSERT(*partyData != 0);
    *destVar = PokemonSummary_GetSelectedMoveSlot(*partyData);

    if (*destVar == LEARNED_MOVES_MAX) {
        *destVar = MOVE_NOT_SELECTED;
    }

    Heap_Free(*partyData);
    *partyData = NULL;

    return FALSE;
}

BOOL ScrCmd_Dummy21E(ScriptContext *ctx)
{
    return FALSE;
}

BOOL ScrCmd_HasRelearnableMove(ScriptContext *ctx)
{
    Pokemon *mon;
    u16 *relearnableMoves;
    u16 *result = ScriptContext_GetVarPointer(ctx);
    u16 partySlot = ScriptContext_GetVar(ctx);

    mon = Party_GetPokemonBySlotIndex(SaveData_GetParty(ctx->fieldSystem->saveData), partySlot);
    relearnableMoves = GetRelearnableMoves(mon, HEAP_ID_FIELD3);
    *result = HasRelearnableMoves(relearnableMoves);

    Heap_Free(relearnableMoves);
    return FALSE;
}

static void ShowMoveRelearner(ScriptContext *ctx, u16 param1, Pokemon *mon, u16 *relearnList)
{
    void **partyData = FieldSystem_GetScriptMemberPtr(ctx->fieldSystem, SCRIPT_MANAGER_PARTY_MANAGEMENT_DATA);
    RelearnMoveData *relearnData = RelearnMoveData_New(HEAP_ID_FIELD3);
    *partyData = relearnData;

    relearnData->mon = mon;
    relearnData->trainerInfo = SaveData_GetTrainerInfo(FieldSystem_GetSaveData(ctx->fieldSystem));
    relearnData->options = SaveData_GetOptions(ctx->fieldSystem->saveData);
    relearnData->relearnList = relearnList;
    relearnData->unk_15 = param1;

    FieldSystem_LaunchMoveRelearnApp(ctx->fieldSystem, relearnData);
    ScriptContext_Pause(ctx, ScriptContext_WaitForApplicationExit);
    Heap_Free(relearnList);
}

BOOL ScrCmd_Dummy220(ScriptContext *ctx)
{
    return TRUE;
}

BOOL ScrCmd_ShowMoveRelearner(ScriptContext *ctx)
{
    Pokemon *mon;
    u16 partySlot = ScriptContext_GetVar(ctx);
    u16 *relearnList;

    mon = Party_GetPokemonBySlotIndex(SaveData_GetParty(ctx->fieldSystem->saveData), partySlot);
    relearnList = GetRelearnableMoves(mon, HEAP_ID_FIELD3);

    ShowMoveRelearner(ctx, 1, mon, relearnList);

    return TRUE;
}

BOOL ScrCmd_224(ScriptContext *param0)
{
    Pokemon *v0;
    u16 v1 = ScriptContext_GetVar(param0);
    u16 v2 = ScriptContext_GetVar(param0);
    u16 *v3;

    v0 = Party_GetPokemonBySlotIndex(SaveData_GetParty(param0->fieldSystem->saveData), v1);
    v3 = Heap_Alloc(HEAP_ID_FIELD3, (1 + 1) * 2);

    *(v3 + 0) = v2;
    *(v3 + 1) = 0xffff;

    ShowMoveRelearner(param0, 0, v0, v3);

    return 1;
}

BOOL ScrCmd_222(ScriptContext *param0)
{
    return 0;
}

BOOL ScrCmd_223(ScriptContext *param0)
{
    RelearnMoveData *v0;
    u16 *v1 = ScriptContext_GetVarPointer(param0);
    void **v2 = FieldSystem_GetScriptMemberPtr(param0->fieldSystem, 19);

    v0 = *v2;

    GF_ASSERT(*v2 != 0);

    if ((v0->unk_16) == 0) {
        *v1 = 0;
    } else {
        *v1 = 0xff;
    }

    RelearnMoveData_Free(v0);

    return 0;
}

BOOL ScrCmd_225(ScriptContext *param0)
{
    RelearnMoveData *v0;
    u16 *v1 = ScriptContext_GetVarPointer(param0);
    void **v2 = FieldSystem_GetScriptMemberPtr(param0->fieldSystem, 19);

    v0 = *v2;

    GF_ASSERT(*v2 != 0);

    if ((v0->unk_16) == 0) {
        *v1 = 0;
    } else {
        *v1 = 0xff;
    }

    RelearnMoveData_Free(v0);

    return 0;
}
