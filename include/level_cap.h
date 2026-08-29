#ifndef GUARD_LEVEL_CAP_H
#define GUARD_LEVEL_CAP_H

#include "global.h"

struct Pokemon;

u8 GetBadgeCount(void);
u8 GetCurrentLevelCap(void);
bool8 IsLevelCapMaxed(void);
bool8 CanUseRareCandy(struct Pokemon *mon);
void CreateLevelCapPopupWindow(void);
void DestroyLevelCapPopupWindow(void);

extern u8 sPopupWindowId;

#endif // GUARD_LEVEL_CAP_H
