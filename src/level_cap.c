#include "global.h"
#include "gflib.h"
#include "event_data.h"
#include "constants/flags.h"
#include "pokemon.h"
#include "strings.h"
#include "string_util.h"
#include "text_window.h"
#include "menu.h"
#include "new_menu_helpers.h"
#include "level_cap.h"

static const u8 sLevelCapsByBadge[NUM_BADGES] = {16, 20, 25, 30, 35, 40, 45, 50};

EWRAM_DATA u8 sPopupWindowId = 0xFF;

static u16 LevelCapPopupCreateWindow(void);
static void LevelCapPopupPrint(u16 windowId);

u8 GetBadgeCount(void)
{
    u8 i, count = 0;
    for (i = 0; i < NUM_BADGES; i++)
    {
        if (FlagGet(FLAG_BADGE01_GET + i))
            count++;
    }
    return count;
}

u8 GetCurrentLevelCap(void)
{
    u8 count = GetBadgeCount();
    if (count == 0)
        return sLevelCapsByBadge[0];
    if (count > NUM_BADGES)
        count = NUM_BADGES;
    return sLevelCapsByBadge[count - 1];
}

bool8 IsLevelCapMaxed(void)
{
    return GetBadgeCount() >= NUM_BADGES;
}

bool8 CanUseRareCandy(struct Pokemon *mon)
{
    u8 cap;
    if (IsLevelCapMaxed())
        return TRUE;
    cap = GetCurrentLevelCap();
    if (GetMonData(mon, MON_DATA_LEVEL) >= cap + 1)
        return FALSE;
    return TRUE;
}

void CreateLevelCapPopupWindow(void)
{
    if (IsLevelCapMaxed())
        return;
    if (sPopupWindowId != 0xFF)
    {
        if (sPopupWindowId < 32 && GetWindowAttribute(sPopupWindowId, WINDOW_WIDTH) == 7)
            return;
        sPopupWindowId = 0xFF;
    }
    sPopupWindowId = LevelCapPopupCreateWindow();
}

void DestroyLevelCapPopupWindow(void)
{
    if (sPopupWindowId == 0xFF)
        return;
    ClearStdWindowAndFrameToTransparent(sPopupWindowId, FALSE);
    CopyWindowToVram(sPopupWindowId, COPYWIN_MAP);
    RemoveWindow(sPopupWindowId);
    sPopupWindowId = 0xFF;
}

#define WIN_PAL_NUM  13

static u16 LevelCapPopupCreateWindow(void)
{
    struct WindowTemplate windowTemplate;
    u16 windowId;

    windowTemplate.bg = 0;
    windowTemplate.tilemapLeft = 13;
    windowTemplate.tilemapTop = 1;
    windowTemplate.width = 7;
    windowTemplate.height = 4;
    windowTemplate.paletteNum = WIN_PAL_NUM;
    windowTemplate.baseBlock = 0x1C0;
    windowId = AddWindow(&windowTemplate);
    if (windowId == 0xFF)
        return 0xFF;
    LoadStdWindowGfx(windowId, 0x21D, BG_PLTT_ID(WIN_PAL_NUM));
    DrawStdWindowFrame(windowId, FALSE);
    LevelCapPopupPrint(windowId);
    CopyWindowToVram(windowId, COPYWIN_FULL);
    return windowId;
}

static void LevelCapPopupPrint(u16 windowId)
{
    u8 cap;
    u8 x;
    u8 width;
    u8 i;
    u8 *secondLine;
    cap = GetCurrentLevelCap();
    ConvertIntToDecimalStringN(gStringVar2, cap, STR_CONV_MODE_LEFT_ALIGN, 3);
    StringExpandPlaceholders(gStringVar4, gText_LevelCapPopup);
    FillWindowPixelBuffer(windowId, PIXEL_FILL(1));
    width = GetWindowAttribute(windowId, WINDOW_WIDTH);
    secondLine = NULL;
    for (i = 0; gStringVar4[i] != EOS; i++)
    {
        if (gStringVar4[i] == 0xFE)
        {
            gStringVar4[i] = EOS;
            secondLine = &gStringVar4[i + 1];
            break;
        }
    }
    x = width * 8 - GetStringWidth(FONT_SMALL, gStringVar4, -1) - 2;
    AddTextPrinterParameterized(windowId, FONT_SMALL, gStringVar4, x, 1, TEXT_SKIP_DRAW, NULL);
    if (secondLine != NULL)
    {
        x = width * 8 - GetStringWidth(FONT_SMALL, secondLine, -1) - 2;
        AddTextPrinterParameterized(windowId, FONT_SMALL, secondLine, x, 14, TEXT_SKIP_DRAW, NULL);
    }
}
