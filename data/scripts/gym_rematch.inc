BrockRematch_Text_RematchIntro::
    .string "Rematch?$"

BrockRematch_Text_ChoosePrize::
    .string "(GG) GOOD GAME.$"

BrockRematch_Text_ChoosePrizeSimple::
    .string "Choose your prize.$"

BrockRematch_EventScript_GiveReward::
    lock
    faceplayer
    message BrockRematch_Text_ChoosePrizeSimple
    multichoice 0, 0, MULTICHOICE_GYM_REWARD, FALSE
    switch VAR_RESULT
    case 0, BrockRematch_EventScript_HeldItem
    case 1, BrockRematch_EventScript_MoveTutorMenu
    case 2, BrockRematch_EventScript_TMMenu
    case SCR_MENU_CANCEL, BrockRematch_EventScript_Cancel
    end

BrockRematch_EventScript_Cancel::
    release
    end

BrockRematch_EventScript_HeldItem::
    checkitemspace ITEM_HARD_STONE
    goto_if_eq VAR_RESULT, FALSE, BrockRematch_EventScript_NoRoom
    giveitem ITEM_HARD_STONE
    release
    end

BrockRematch_EventScript_NoRoom::
    msgbox PewterCity_Gym_Text_DontHaveRoomForThis
    release
    end

BrockRematch_EventScript_MoveTutorMenu::
    multichoice 0, 0, MULTICHOICE_BROCK_TUTOR, FALSE
    goto BrockRematch_EventScript_DoTutor

BrockRematch_EventScript_DoTutor::
    goto_if_eq VAR_RESULT, SCR_MENU_CANCEL, BrockRematch_EventScript_GiveReward
    goto_if_eq VAR_RESULT, 0, BrockRematch_DoTutor_Ancient
    goto_if_eq VAR_RESULT, 1, BrockRematch_DoTutor_RockSlide
    goto_if_eq VAR_RESULT, 2, BrockRematch_DoTutor_RockThrow
    @ case 3 = Rollout
    setvar VAR_0x8005, MOVETUTOR_ROLLOUT
    goto BrockRematch_DoTutor_Choose
BrockRematch_DoTutor_Ancient:
    setvar VAR_0x8005, MOVETUTOR_ANCIENT_POWER
    goto BrockRematch_DoTutor_Choose
BrockRematch_DoTutor_RockSlide:
    setvar VAR_0x8005, MOVETUTOR_ROCK_SLIDE
    goto BrockRematch_DoTutor_Choose
BrockRematch_DoTutor_RockThrow:
    setvar VAR_0x8005, MOVETUTOR_ROCK_THROW
    goto BrockRematch_DoTutor_Choose
BrockRematch_DoTutor_Choose:
    special ChooseMonForMoveTutor
    waitstate
    release
    end

BrockRematch_EventScript_TMMenu::
    multichoice 0, 0, MULTICHOICE_BROCK_TM, FALSE
    switch VAR_RESULT
    case 0, BrockRematch_EventScript_TMSandstorm
    case 1, BrockRematch_EventScript_TMRockTomb
    case SCR_MENU_CANCEL, BrockRematch_EventScript_GiveReward
    end

BrockRematch_EventScript_TMSandstorm::
    checkitemspace ITEM_TM37
    goto_if_eq VAR_RESULT, FALSE, BrockRematch_EventScript_NoRoom
    giveitem ITEM_TM37
    release
    end

BrockRematch_EventScript_TMRockTomb::
    checkitemspace ITEM_TM39
    goto_if_eq VAR_RESULT, FALSE, BrockRematch_EventScript_NoRoom
    giveitem ITEM_TM39
    release
    end

PewterCity_Gym_EventScript_BrockRematchDefeated::
    goto BrockRematch_EventScript_GiveReward
    end

MistyRematch_Text_RematchIntro::
    .string "Rematch?$"

MistyRematch_Text_ChoosePrize::
    .string "(GG) GOOD GAME.$"

MistyRematch_Text_ChoosePrizeSimple::
    .string "Choose your prize.$"

MistyRematch_EventScript_GiveReward::
    lock
    faceplayer
    message MistyRematch_Text_ChoosePrizeSimple
    multichoice 0, 0, MULTICHOICE_GYM_REWARD, FALSE
    switch VAR_RESULT
    case 0, MistyRematch_EventScript_HeldItem
    case 1, MistyRematch_EventScript_MoveTutorMenu
    case 2, MistyRematch_EventScript_TMMenu
    case SCR_MENU_CANCEL, MistyRematch_EventScript_Cancel
    end

MistyRematch_EventScript_Cancel::
    release
    end

MistyRematch_EventScript_HeldItem::
    checkitemspace ITEM_MYSTIC_WATER
    goto_if_eq VAR_RESULT, FALSE, MistyRematch_EventScript_NoRoom
    giveitem ITEM_MYSTIC_WATER
    release
    end

MistyRematch_EventScript_NoRoom::
    msgbox CeruleanCity_Gym_Text_BetterMakeRoomForThis
    release
    end

MistyRematch_EventScript_MoveTutorMenu::
    multichoice 0, 0, MULTICHOICE_MISTY_TUTOR, FALSE
    goto MistyRematch_EventScript_DoTutor

MistyRematch_EventScript_DoTutor::
    goto_if_eq VAR_RESULT, SCR_MENU_CANCEL, MistyRematch_EventScript_GiveReward
    goto_if_eq VAR_RESULT, 0, MistyRematch_DoTutor_Bubble
    goto_if_eq VAR_RESULT, 1, MistyRematch_DoTutor_HydroCannon
    @ case 2 = Hydro Pump
    setvar VAR_0x8005, MOVETUTOR_HYDRO_PUMP
    goto MistyRematch_DoTutor_Choose
MistyRematch_DoTutor_Bubble:
    setvar VAR_0x8005, MOVETUTOR_BUBBLE
    goto MistyRematch_DoTutor_Choose
MistyRematch_DoTutor_HydroCannon:
    setvar VAR_0x8005, MOVETUTOR_HYDRO_CANNON
    goto MistyRematch_DoTutor_Choose
MistyRematch_DoTutor_Choose:
    special ChooseMonForMoveTutor
    waitstate
    release
    end

MistyRematch_EventScript_TMMenu::
    multichoice 0, 0, MULTICHOICE_MISTY_TM, FALSE
    switch VAR_RESULT
    case 0, MistyRematch_EventScript_TMRainDance
    case 1, MistyRematch_EventScript_TMWaterPulse
    case SCR_MENU_CANCEL, MistyRematch_EventScript_GiveReward
    end

MistyRematch_EventScript_TMRainDance::
    checkitemspace ITEM_TM18
    goto_if_eq VAR_RESULT, FALSE, MistyRematch_EventScript_NoRoom
    giveitem ITEM_TM18
    release
    end

MistyRematch_EventScript_TMWaterPulse::
    checkitemspace ITEM_TM03
    goto_if_eq VAR_RESULT, FALSE, MistyRematch_EventScript_NoRoom
    giveitem ITEM_TM03
    release
    end

CeruleanCity_Gym_EventScript_MistyRematchDefeated::
    goto MistyRematch_EventScript_GiveReward
    end

SurgeRematch_Text_RematchIntro::
    .string "Rematch?$"

SurgeRematch_Text_ChoosePrize::
    .string "(GG) GOOD GAME.$"

SurgeRematch_Text_ChoosePrizeSimple::
    .string "Choose your prize.$"

SurgeRematch_EventScript_GiveReward::
    lock
    faceplayer
    message SurgeRematch_Text_ChoosePrizeSimple
    multichoice 0, 0, MULTICHOICE_GYM_REWARD, FALSE
    switch VAR_RESULT
    case 0, SurgeRematch_EventScript_HeldItem
    case 1, SurgeRematch_EventScript_MoveTutorMenu
    case 2, SurgeRematch_EventScript_TMMenu
    case SCR_MENU_CANCEL, SurgeRematch_EventScript_Cancel
    end

SurgeRematch_EventScript_Cancel::
    release
    end

SurgeRematch_EventScript_HeldItem::
    checkitemspace ITEM_MAGNET
    goto_if_eq VAR_RESULT, FALSE, SurgeRematch_EventScript_NoRoom
    giveitem ITEM_MAGNET
    release
    end

SurgeRematch_EventScript_NoRoom::
    msgbox VermilionCity_Gym_Text_MakeRoomInYourBag
    release
    end

SurgeRematch_EventScript_MoveTutorMenu::
    multichoice 0, 0, MULTICHOICE_SURGE_TUTOR, FALSE
    goto SurgeRematch_EventScript_DoTutor

SurgeRematch_EventScript_DoTutor::
    goto_if_eq VAR_RESULT, SCR_MENU_CANCEL, SurgeRematch_EventScript_GiveReward
    goto_if_eq VAR_RESULT, 0, SurgeRematch_DoTutor_ThunderPunch
    goto_if_eq VAR_RESULT, 1, SurgeRematch_DoTutor_ThunderWave
    @ case 2 = Zap Cannon
    setvar VAR_0x8005, MOVETUTOR_ZAP_CANNON
    goto SurgeRematch_DoTutor_Choose
SurgeRematch_DoTutor_ThunderPunch:
    setvar VAR_0x8005, MOVETUTOR_THUNDER_PUNCH
    goto SurgeRematch_DoTutor_Choose
SurgeRematch_DoTutor_ThunderWave:
    setvar VAR_0x8005, MOVETUTOR_THUNDER_WAVE
    goto SurgeRematch_DoTutor_Choose
SurgeRematch_DoTutor_Choose:
    special ChooseMonForMoveTutor
    waitstate
    release
    end

SurgeRematch_EventScript_TMMenu::
    multichoice 0, 0, MULTICHOICE_SURGE_TM, FALSE
    switch VAR_RESULT
    case 0, SurgeRematch_EventScript_TMShockWave
    case 1, SurgeRematch_EventScript_TMThunder
    case 2, SurgeRematch_EventScript_TMThunderbolt
    case SCR_MENU_CANCEL, SurgeRematch_EventScript_GiveReward
    end

SurgeRematch_EventScript_TMShockWave::
    checkitemspace ITEM_TM34
    goto_if_eq VAR_RESULT, FALSE, SurgeRematch_EventScript_NoRoom
    giveitem ITEM_TM34
    release
    end

SurgeRematch_EventScript_TMThunder::
    checkitemspace ITEM_TM25
    goto_if_eq VAR_RESULT, FALSE, SurgeRematch_EventScript_NoRoom
    giveitem ITEM_TM25
    release
    end

SurgeRematch_EventScript_TMThunderbolt::
    checkitemspace ITEM_TM24
    goto_if_eq VAR_RESULT, FALSE, SurgeRematch_EventScript_NoRoom
    giveitem ITEM_TM24
    release
    end

VermilionCity_Gym_EventScript_SurgeRematchDefeated::
    goto SurgeRematch_EventScript_GiveReward
    end

ErikaRematch_Text_RematchIntro::
    .string "Rematch?$"

ErikaRematch_Text_ChoosePrize::
    .string "(GG) GOOD GAME.$"

ErikaRematch_Text_ChoosePrizeSimple::
    .string "Choose your prize.$"

ErikaRematch_EventScript_GiveReward::
    lock
    faceplayer
    message ErikaRematch_Text_ChoosePrizeSimple
    multichoice 0, 0, MULTICHOICE_GYM_REWARD, FALSE
    switch VAR_RESULT
    case 0, ErikaRematch_EventScript_HeldItem
    case 1, ErikaRematch_EventScript_MoveTutorMenu
    case 2, ErikaRematch_EventScript_TMMenu
    case SCR_MENU_CANCEL, ErikaRematch_EventScript_Cancel
    end

ErikaRematch_EventScript_Cancel::
    release
    end

ErikaRematch_EventScript_HeldItem::
    checkitemspace ITEM_MIRACLE_SEED
    goto_if_eq VAR_RESULT, FALSE, ErikaRematch_EventScript_NoRoom
    giveitem ITEM_MIRACLE_SEED
    release
    end

ErikaRematch_EventScript_NoRoom::
    msgbox CeladonCity_Gym_Text_ShouldMakeRoomForThis
    release
    end

ErikaRematch_EventScript_MoveTutorMenu::
    multichoice 0, 0, MULTICHOICE_ERIKA_TUTOR, FALSE
    goto ErikaRematch_EventScript_DoTutor

ErikaRematch_EventScript_DoTutor::
    goto_if_eq VAR_RESULT, SCR_MENU_CANCEL, ErikaRematch_EventScript_GiveReward
    goto_if_eq VAR_RESULT, 0, ErikaRematch_DoTutor_Absorb
    goto_if_eq VAR_RESULT, 1, ErikaRematch_DoTutor_FrenzyPlant
    goto_if_eq VAR_RESULT, 2, ErikaRematch_DoTutor_LeechSeed
    goto_if_eq VAR_RESULT, 3, ErikaRematch_DoTutor_PetalDance
    @ case 4 = Synthesis
    setvar VAR_0x8005, MOVETUTOR_SYNTHESIS
    goto ErikaRematch_DoTutor_Choose
ErikaRematch_DoTutor_Absorb:
    setvar VAR_0x8005, MOVETUTOR_ABSORB
    goto ErikaRematch_DoTutor_Choose
ErikaRematch_DoTutor_FrenzyPlant:
    setvar VAR_0x8005, MOVETUTOR_FRENZY_PLANT
    goto ErikaRematch_DoTutor_Choose
ErikaRematch_DoTutor_LeechSeed:
    setvar VAR_0x8005, MOVETUTOR_LEECH_SEED
    goto ErikaRematch_DoTutor_Choose
ErikaRematch_DoTutor_PetalDance:
    setvar VAR_0x8005, MOVETUTOR_PETAL_DANCE
    goto ErikaRematch_DoTutor_Choose
ErikaRematch_DoTutor_Choose:
    special ChooseMonForMoveTutor
    waitstate
    release
    end

ErikaRematch_EventScript_TMMenu::
    multichoice 0, 0, MULTICHOICE_ERIKA_TM, FALSE
    switch VAR_RESULT
    case 0, ErikaRematch_EventScript_TMBulletSeed
    case 1, ErikaRematch_EventScript_TMGigaDrain
    case 2, ErikaRematch_EventScript_TMSolarBeam
    case SCR_MENU_CANCEL, ErikaRematch_EventScript_GiveReward
    end

ErikaRematch_EventScript_TMBulletSeed::
    checkitemspace ITEM_TM09
    goto_if_eq VAR_RESULT, FALSE, ErikaRematch_EventScript_NoRoom
    giveitem ITEM_TM09
    release
    end

ErikaRematch_EventScript_TMGigaDrain::
    checkitemspace ITEM_TM19
    goto_if_eq VAR_RESULT, FALSE, ErikaRematch_EventScript_NoRoom
    giveitem ITEM_TM19
    release
    end

ErikaRematch_EventScript_TMSolarBeam::
    checkitemspace ITEM_TM22
    goto_if_eq VAR_RESULT, FALSE, ErikaRematch_EventScript_NoRoom
    giveitem ITEM_TM22
    release
    end

CeladonCity_Gym_EventScript_ErikaRematchDefeated::
    goto ErikaRematch_EventScript_GiveReward
    end

KogaRematch_Text_RematchIntro::
    .string "Rematch?$"

KogaRematch_Text_ChoosePrize::
    .string "(GG) GOOD GAME.$"

KogaRematch_Text_ChoosePrizeSimple::
    .string "Choose your prize.$"

KogaRematch_EventScript_GiveReward::
    lock
    faceplayer
    message KogaRematch_Text_ChoosePrizeSimple
    multichoice 0, 0, MULTICHOICE_GYM_REWARD, FALSE
    switch VAR_RESULT
    case 0, KogaRematch_EventScript_HeldItem
    case 1, KogaRematch_EventScript_MoveTutorMenu
    case 2, KogaRematch_EventScript_TMMenu
    case SCR_MENU_CANCEL, KogaRematch_EventScript_Cancel
    end

KogaRematch_EventScript_Cancel::
    release
    end

KogaRematch_EventScript_HeldItem::
    checkitemspace ITEM_POISON_BARB
    goto_if_eq VAR_RESULT, FALSE, KogaRematch_EventScript_NoRoom
    giveitem ITEM_POISON_BARB
    release
    end

KogaRematch_EventScript_NoRoom::
    msgbox FuchsiaCity_Gym_Text_MakeSpaceForThis
    release
    end

KogaRematch_EventScript_MoveTutorMenu::
    multichoice 0, 0, MULTICHOICE_KOGA_TUTOR, FALSE
    goto KogaRematch_EventScript_DoTutor

KogaRematch_EventScript_DoTutor::
    goto_if_eq VAR_RESULT, SCR_MENU_CANCEL, KogaRematch_EventScript_GiveReward
    @ case 0 = Poison Tail
    setvar VAR_0x8005, MOVETUTOR_POISON_TAIL
    goto KogaRematch_DoTutor_Choose
KogaRematch_DoTutor_Choose:
    special ChooseMonForMoveTutor
    waitstate
    release
    end

KogaRematch_EventScript_TMMenu::
    multichoice 0, 0, MULTICHOICE_KOGA_TM, FALSE
    switch VAR_RESULT
    case 0, KogaRematch_EventScript_TMSludgeBomb
    case 1, KogaRematch_EventScript_TMToxic
    case SCR_MENU_CANCEL, KogaRematch_EventScript_GiveReward
    end

KogaRematch_EventScript_TMSludgeBomb::
    checkitemspace ITEM_TM36
    goto_if_eq VAR_RESULT, FALSE, KogaRematch_EventScript_NoRoom
    giveitem ITEM_TM36
    release
    end

KogaRematch_EventScript_TMToxic::
    checkitemspace ITEM_TM06
    goto_if_eq VAR_RESULT, FALSE, KogaRematch_EventScript_NoRoom
    giveitem ITEM_TM06
    release
    end

FuchsiaCity_Gym_EventScript_KogaRematchDefeated::
    goto KogaRematch_EventScript_GiveReward
    end
