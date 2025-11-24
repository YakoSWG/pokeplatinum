#include "unk_0202C9F4.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/seal_case.h"

#include "savedata.h"

int SealCase_SaveSize(void)
{
    return sizeof(SealCase);
}

void SealCase_Init(SealCase *sealCase)
{
    int size = SealCase_SaveSize();
    MI_CpuFill8(sealCase, 0, size);
}

void BallCapsule_Copy(const BallCapsule *src, BallCapsule *dst)
{
    MI_CpuCopy8(src, dst, sizeof(BallCapsule));
}

SealCase *SaveData_GetSealCase(SaveData *saveData)
{
    return SaveData_SaveTable(saveData, SAVE_TABLE_ENTRY_SEAL_CASE);
}

BallCapsule *SealCase_GetCapsuleById(SealCase *sealCase, int capsuleId)
{
    GF_ASSERT(capsuleId < TOTAL_CAPSULES);
    return &sealCase->capsules[capsuleId];
}

void SealCase_CopyCapsuleFromId(SealCase *sealCase, BallCapsule *dst, int capsuleId)
{
    GF_ASSERT(capsuleId < TOTAL_CAPSULES);
    BallCapsule_Copy(dst, SealCase_GetCapsuleById(sealCase, capsuleId));
}

BallSeal *BallCapsule_GetBallSeals(BallCapsule *ballCapsule, int sealNum)
{
    GF_ASSERT(sealNum < SEALS_PER_CAPSULE);
    return &ballCapsule->seals[sealNum];
}

u8 BallSeal_GetSealType(const BallSeal *seal)
{
    return seal->type;
}

u8 BallSeal_GetX(const BallSeal *seal)
{
    return seal->x;
}

u8 BallSeal_GetY(const BallSeal *seal)
{
    return seal->y;
}

SealCounts *SealCase_GetSealsObtained(SealCase *sealCase)
{
    return &sealCase->seals;
}

u8 SealCase_GetSealCount(const SealCounts *seals, int sealNum)
{
    return seals->count[sealNum];
}

BOOL BallCapsule_IsSealApplied(const BallCapsule *ballCapsule, int sealNum)
{
    int unused, i;

    for (i = 0; i < SEALS_PER_CAPSULE; i++) {
        if (ballCapsule->seals[i].type == (sealNum + 1)) {
            return TRUE;
        }
    }

    return FALSE;
}

int SealCase_GetAppliedSealCount(const SealCase *sealCase, int sealNum)
{
    int i, j;
    int count = 0;

    for (i = 0; i < TOTAL_CAPSULES; i++) {
        for (j = 0; j < SEALS_PER_CAPSULE; j++) {
            if (sealCase->capsules[i].seals[j].type == (sealNum + 1)) {
                count++;
            }
        }
    }

    return count;
}

void SealCase_SetSealCount(SealCounts *seals, int sealNum, int sealCount)
{
    seals->count[sealNum] = sealCount;
}

BOOL SealCase_TryChangeSealCount(SealCase *sealCase, int sealID, s16 changeAmount)
{
    int appliedSealCount;
    int totalSealCount;

    appliedSealCount = SealCase_GetAppliedSealCount(sealCase, sealID - 1);
    totalSealCount = appliedSealCount + sealCase->seals.count[sealID - 1];

    if (changeAmount < 0) {
        if (sealCase->seals.count[sealID - 1] + changeAmount >= 0) {
            sealCase->seals.count[sealID - 1] += changeAmount;
        } else {
            return FALSE;
        }
    } else {
        if (totalSealCount + changeAmount <= MAX_SEALS_PER_TYPE) {
            sealCase->seals.count[sealID - 1] += changeAmount;
        } else {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL sub_0202CB20(SealCase *sealCase, int sealID, s16 changeAmount)
{
    int appliedSealCount;
    int stillAppliedSealCount;

    appliedSealCount = SealCase_GetAppliedSealCount(sealCase, sealID - 1);
    stillAppliedSealCount = appliedSealCount;

    if (changeAmount < 0) {
        if (sealCase->seals.count[sealID - 1] + changeAmount >= 0) {
            sealCase->seals.count[sealID - 1] += changeAmount;
        } else {
            return FALSE;
        }
    } else {
        if (stillAppliedSealCount + changeAmount <= MAX_SEALS_PER_TYPE) {
            sealCase->seals.count[sealID - 1] += changeAmount;

            if (sealCase->seals.count[sealID - 1] >= MAX_SEALS_PER_TYPE) {
                sealCase->seals.count[sealID - 1] = MAX_SEALS_PER_TYPE;
            }
        } else {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL SealCase_CanChangeSealAmount(SealCase *sealCase, int sealID, s16 changeAmount)
{
    int appliedSealCount = SealCase_GetAppliedSealCount(sealCase, sealID - 1);
    int totalSealCount = appliedSealCount + sealCase->seals.count[sealID - 1];

    if (changeAmount < 0) {
        if (sealCase->seals.count[sealID - 1] + changeAmount >= 0) {
            return TRUE;
        } else {
            return FALSE;
        }
    } else {
        if (totalSealCount + changeAmount <= MAX_SEALS_PER_TYPE) {
            return TRUE;
        } else {
            return FALSE;
        }
    }

    return TRUE;
}

int SealCase_GetObtainedSealCount(const SealCase *sealCase)
{
    int i;
    int count = 0;

    for (i = 1; i < SEAL_ID_MAX; i++) {
        if (SealCase_GetTotalSealCount(sealCase, i) != 0) {
            count++;
        }
    }

    return count;
}

int SealCase_GetTotalSealCount(const SealCase *sealCase, int sealID)
{
    int appliedSealCount;
    int totalSealCount;

    appliedSealCount = SealCase_GetAppliedSealCount(sealCase, sealID - 1);
    totalSealCount = appliedSealCount + sealCase->seals.count[sealID - 1];

    return totalSealCount;
}
