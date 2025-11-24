#ifndef POKEPLATINUM_UNK_0202C9F4_H
#define POKEPLATINUM_UNK_0202C9F4_H

#include "struct_defs/seal_case.h"

#include "savedata.h"

int SealCase_SaveSize(void);
void SealCase_Init(SealCase *sealCase);
void BallCapsule_Copy(const BallCapsule *src, BallCapsule *dst);
SealCase *SaveData_GetSealCase(SaveData *saveData);
BallCapsule *SealCase_GetCapsuleById(SealCase *sealCase, int capsuleId);
void SealCase_CopyCapsuleFromId(SealCase *sealCase, BallCapsule *dst, int capsuleId);
BallSeal *BallCapsule_GetBallSeals(BallCapsule *ballCapsule, int sealNum);
u8 BallSeal_GetSealType(const BallSeal *seal);
u8 BallSeal_GetX(const BallSeal *seal);
u8 BallSeal_GetY(const BallSeal *seal);
SealCounts *SealCase_GetSealsObtained(SealCase *sealCase);
u8 SealCase_GetSealCount(const SealCounts *seals, int sealNum);
BOOL BallCapsule_IsSealApplied(const BallCapsule *ballCapsule, int sealNum);
int SealCase_GetAppliedSealCount(const SealCase *sealCase, int sealNum);
void SealCase_SetSealCount(SealCounts *seals, int sealNum, int sealCount);
BOOL SealCase_TryChangeSealCount(SealCase *sealCase, int sealID, s16 changeAmount);
BOOL sub_0202CB20(SealCase *sealCase, int sealID, s16 changeAmount);
BOOL SealCase_CanChangeSealAmount(SealCase *sealCase, int sealID, s16 changeAmount);
int SealCase_GetObtainedSealCount(const SealCase *sealCase);
int SealCase_GetTotalSealCount(const SealCase *sealCase, int sealID);

#endif // POKEPLATINUM_UNK_0202C9F4_H
