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
    case 0, BrockRematch_EventScript_TMHiddenPower
    case 1, BrockRematch_EventScript_TMSandstorm
    case 2, BrockRematch_EventScript_TMRockTomb
    case SCR_MENU_CANCEL, BrockRematch_EventScript_GiveReward
    end

BrockRematch_EventScript_TMHiddenPower::
    checkitemspace ITEM_TM10
    goto_if_eq VAR_RESULT, FALSE, BrockRematch_EventScript_NoRoom
    giveitem ITEM_TM10
    release
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
    case 0, MistyRematch_EventScript_TMHiddenPower
    case 1, MistyRematch_EventScript_TMRainDance
    case 2, MistyRematch_EventScript_TMWaterPulse
    case SCR_MENU_CANCEL, MistyRematch_EventScript_GiveReward
    end

MistyRematch_EventScript_TMHiddenPower::
    checkitemspace ITEM_TM10
    goto_if_eq VAR_RESULT, FALSE, MistyRematch_EventScript_NoRoom
    giveitem ITEM_TM10
    release
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
    case 0, SurgeRematch_EventScript_TMHiddenPower
    case 1, SurgeRematch_EventScript_TMShockWave
    case 2, SurgeRematch_EventScript_TMThunder
    case 3, SurgeRematch_EventScript_TMThunderbolt
    case SCR_MENU_CANCEL, SurgeRematch_EventScript_GiveReward
    end

SurgeRematch_EventScript_TMHiddenPower::
    checkitemspace ITEM_TM10
    goto_if_eq VAR_RESULT, FALSE, SurgeRematch_EventScript_NoRoom
    giveitem ITEM_TM10
    release
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
    case 0, ErikaRematch_EventScript_TMHiddenPower
    case 1, ErikaRematch_EventScript_TMBulletSeed
    case 2, ErikaRematch_EventScript_TMGigaDrain
    case 3, ErikaRematch_EventScript_TMSolarBeam
    case SCR_MENU_CANCEL, ErikaRematch_EventScript_GiveReward
    end

ErikaRematch_EventScript_TMHiddenPower::
    checkitemspace ITEM_TM10
    goto_if_eq VAR_RESULT, FALSE, ErikaRematch_EventScript_NoRoom
    giveitem ITEM_TM10
    release
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
    case 0, KogaRematch_EventScript_TMHiddenPower
    case 1, KogaRematch_EventScript_TMSludgeBomb
    case 2, KogaRematch_EventScript_TMToxic
    case SCR_MENU_CANCEL, KogaRematch_EventScript_GiveReward
    end

KogaRematch_EventScript_TMHiddenPower::
    checkitemspace ITEM_TM10
    goto_if_eq VAR_RESULT, FALSE, KogaRematch_EventScript_NoRoom
    giveitem ITEM_TM10
    release
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

SabrinaRematch_Text_RematchIntro::
    .string "Rematch?$"

SabrinaRematch_Text_ChoosePrize::
    .string "(GG) GOOD GAME.$"

SabrinaRematch_Text_ChoosePrizeSimple::
    .string "Choose your prize.$"

SabrinaRematch_EventScript_GiveReward::
    lock
    faceplayer
    message SabrinaRematch_Text_ChoosePrizeSimple
    multichoice 0, 0, MULTICHOICE_GYM_REWARD, FALSE
    switch VAR_RESULT
    case 0, SabrinaRematch_EventScript_HeldItem
    case 1, SabrinaRematch_EventScript_MoveTutorMenu
    case 2, SabrinaRematch_EventScript_TMMenu
    case SCR_MENU_CANCEL, SabrinaRematch_EventScript_Cancel
    end

SabrinaRematch_EventScript_Cancel::
    release
    end

SabrinaRematch_EventScript_HeldItem::
    checkitemspace ITEM_TWISTED_SPOON
    goto_if_eq VAR_RESULT, FALSE, SabrinaRematch_EventScript_NoRoom
    giveitem ITEM_TWISTED_SPOON
    release
    end

SabrinaRematch_EventScript_NoRoom::
    msgbox SaffronCity_Gym_Text_BagFullOfOtherItems
    release
    end

SabrinaRematch_EventScript_MoveTutorMenu::
    multichoice 0, 0, MULTICHOICE_SABRINA_TUTOR, FALSE
    goto SabrinaRematch_EventScript_DoTutor

SabrinaRematch_EventScript_DoTutor::
    goto_if_eq VAR_RESULT, SCR_MENU_CANCEL, SabrinaRematch_EventScript_GiveReward
    goto_if_eq VAR_RESULT, 0, SabrinaRematch_DoTutor_Agility
    goto_if_eq VAR_RESULT, 1, SabrinaRematch_DoTutor_Amnesia
    goto_if_eq VAR_RESULT, 2, SabrinaRematch_DoTutor_Barrier
    goto_if_eq VAR_RESULT, 3, SabrinaRematch_DoTutor_DreamEater
    goto_if_eq VAR_RESULT, 4, SabrinaRematch_DoTutor_Extrasensory
    goto_if_eq VAR_RESULT, 5, SabrinaRematch_DoTutor_FutureSight
    goto_if_eq VAR_RESULT, 6, SabrinaRematch_DoTutor_Hypnosis
    goto_if_eq VAR_RESULT, 7, SabrinaRematch_DoTutor_LightScreen
    goto_if_eq VAR_RESULT, 8, SabrinaRematch_DoTutor_PsychoBoost
    @ case 9 = Role Play
    setvar VAR_0x8005, MOVETUTOR_ROLE_PLAY
    goto SabrinaRematch_DoTutor_Choose
SabrinaRematch_DoTutor_Agility:
    setvar VAR_0x8005, MOVETUTOR_AGILITY
    goto SabrinaRematch_DoTutor_Choose
SabrinaRematch_DoTutor_Amnesia:
    setvar VAR_0x8005, MOVETUTOR_AMNESIA
    goto SabrinaRematch_DoTutor_Choose
SabrinaRematch_DoTutor_Barrier:
    setvar VAR_0x8005, MOVETUTOR_BARRIER
    goto SabrinaRematch_DoTutor_Choose
SabrinaRematch_DoTutor_DreamEater:
    setvar VAR_0x8005, MOVETUTOR_DREAM_EATER
    goto SabrinaRematch_DoTutor_Choose
SabrinaRematch_DoTutor_Extrasensory:
    setvar VAR_0x8005, MOVETUTOR_EXTRASENSORY
    goto SabrinaRematch_DoTutor_Choose
SabrinaRematch_DoTutor_FutureSight:
    setvar VAR_0x8005, MOVETUTOR_FUTURE_SIGHT
    goto SabrinaRematch_DoTutor_Choose
SabrinaRematch_DoTutor_Hypnosis:
    setvar VAR_0x8005, MOVETUTOR_HYPNOSIS
    goto SabrinaRematch_DoTutor_Choose
SabrinaRematch_DoTutor_LightScreen:
    setvar VAR_0x8005, MOVETUTOR_LIGHT_SCREEN
    goto SabrinaRematch_DoTutor_Choose
SabrinaRematch_DoTutor_PsychoBoost:
    setvar VAR_0x8005, MOVETUTOR_PSYCHO_BOOST
    goto SabrinaRematch_DoTutor_Choose
SabrinaRematch_DoTutor_Choose:
    special ChooseMonForMoveTutor
    waitstate
    release
    end

SabrinaRematch_EventScript_TMMenu::
    multichoice 0, 0, MULTICHOICE_SABRINA_TM, FALSE
    switch VAR_RESULT
    case 0, SabrinaRematch_EventScript_TMHiddenPower
    case 1, SabrinaRematch_EventScript_TMCalmMind
    case 2, SabrinaRematch_EventScript_TMLightScreen
    case 3, SabrinaRematch_EventScript_TMPsychic
    case 4, SabrinaRematch_EventScript_TMReflect
    case 5, SabrinaRematch_EventScript_TMRest
    case 6, SabrinaRematch_EventScript_TMSkillSwap
    case SCR_MENU_CANCEL, SabrinaRematch_EventScript_GiveReward
    end

SabrinaRematch_EventScript_TMHiddenPower::
    checkitemspace ITEM_TM10
    goto_if_eq VAR_RESULT, FALSE, SabrinaRematch_EventScript_NoRoom
    giveitem ITEM_TM10
    release
    end

SabrinaRematch_EventScript_TMCalmMind::
    checkitemspace ITEM_TM04
    goto_if_eq VAR_RESULT, FALSE, SabrinaRematch_EventScript_NoRoom
    giveitem ITEM_TM04
    release
    end

SabrinaRematch_EventScript_TMLightScreen::
    checkitemspace ITEM_TM16
    goto_if_eq VAR_RESULT, FALSE, SabrinaRematch_EventScript_NoRoom
    giveitem ITEM_TM16
    release
    end

SabrinaRematch_EventScript_TMPsychic::
    checkitemspace ITEM_TM29
    goto_if_eq VAR_RESULT, FALSE, SabrinaRematch_EventScript_NoRoom
    giveitem ITEM_TM29
    release
    end

SabrinaRematch_EventScript_TMReflect::
    checkitemspace ITEM_TM33
    goto_if_eq VAR_RESULT, FALSE, SabrinaRematch_EventScript_NoRoom
    giveitem ITEM_TM33
    release
    end

SabrinaRematch_EventScript_TMRest::
    checkitemspace ITEM_TM44
    goto_if_eq VAR_RESULT, FALSE, SabrinaRematch_EventScript_NoRoom
    giveitem ITEM_TM44
    release
    end

SabrinaRematch_EventScript_TMSkillSwap::
    checkitemspace ITEM_TM48
    goto_if_eq VAR_RESULT, FALSE, SabrinaRematch_EventScript_NoRoom
    giveitem ITEM_TM48
    release
    end

SaffronCity_Gym_EventScript_SabrinaRematchDefeated::
    goto SabrinaRematch_EventScript_GiveReward
    end

BlaineRematch_Text_RematchIntro::
    .string "Rematch?$"

BlaineRematch_Text_ChoosePrize::
    .string "(GG) GOOD GAME.$"

BlaineRematch_Text_ChoosePrizeSimple::
    .string "Choose your prize.$"

BlaineRematch_EventScript_GiveReward::
    lock
    faceplayer
    message BlaineRematch_Text_ChoosePrizeSimple
    multichoice 0, 0, MULTICHOICE_GYM_REWARD, FALSE
    switch VAR_RESULT
    case 0, BlaineRematch_EventScript_HeldItem
    case 1, BlaineRematch_EventScript_MoveTutorMenu
    case 2, BlaineRematch_EventScript_TMMenu
    case SCR_MENU_CANCEL, BlaineRematch_EventScript_Cancel
    end

BlaineRematch_EventScript_Cancel::
    release
    end

BlaineRematch_EventScript_HeldItem::
    checkitemspace ITEM_CHARCOAL
    goto_if_eq VAR_RESULT, FALSE, BlaineRematch_EventScript_NoRoom
    giveitem ITEM_CHARCOAL
    release
    end

BlaineRematch_EventScript_NoRoom::
    msgbox CinnabarIsland_Gym_Text_MakeSpaceForThis
    release
    end

BlaineRematch_EventScript_MoveTutorMenu::
    multichoice 0, 0, MULTICHOICE_BLAINE_TUTOR, FALSE
    goto BlaineRematch_EventScript_DoTutor

BlaineRematch_EventScript_DoTutor::
    goto_if_eq VAR_RESULT, SCR_MENU_CANCEL, BlaineRematch_EventScript_GiveReward
    goto_if_eq VAR_RESULT, 0, BlaineRematch_DoTutor_BlastBurn
    goto_if_eq VAR_RESULT, 1, BlaineRematch_DoTutor_FirePunch
    @ case 2 = Will-O-Wisp
    setvar VAR_0x8005, MOVETUTOR_WILL_O_WISP
    goto BlaineRematch_DoTutor_Choose
BlaineRematch_DoTutor_BlastBurn:
    setvar VAR_0x8005, MOVETUTOR_BLAST_BURN
    goto BlaineRematch_DoTutor_Choose
BlaineRematch_DoTutor_FirePunch:
    setvar VAR_0x8005, MOVETUTOR_FIRE_PUNCH
    goto BlaineRematch_DoTutor_Choose
BlaineRematch_DoTutor_Choose:
    special ChooseMonForMoveTutor
    waitstate
    release
    end

BlaineRematch_EventScript_TMMenu::
    multichoice 0, 0, MULTICHOICE_BLAINE_TM, FALSE
    switch VAR_RESULT
    case 0, BlaineRematch_EventScript_TMHiddenPower
    case 1, BlaineRematch_EventScript_TMFireBlast
    case 2, BlaineRematch_EventScript_TMFlamethrower
    case 3, BlaineRematch_EventScript_TMOverheat
    case 4, BlaineRematch_EventScript_TMSunnyDay
    case SCR_MENU_CANCEL, BlaineRematch_EventScript_GiveReward
    end

BlaineRematch_EventScript_TMHiddenPower::
    checkitemspace ITEM_TM10
    goto_if_eq VAR_RESULT, FALSE, BlaineRematch_EventScript_NoRoom
    giveitem ITEM_TM10
    release
    end

BlaineRematch_EventScript_TMFireBlast::
    checkitemspace ITEM_TM38
    goto_if_eq VAR_RESULT, FALSE, BlaineRematch_EventScript_NoRoom
    giveitem ITEM_TM38
    release
    end

BlaineRematch_EventScript_TMFlamethrower::
    checkitemspace ITEM_TM35
    goto_if_eq VAR_RESULT, FALSE, BlaineRematch_EventScript_NoRoom
    giveitem ITEM_TM35
    release
    end

BlaineRematch_EventScript_TMOverheat::
    checkitemspace ITEM_TM50
    goto_if_eq VAR_RESULT, FALSE, BlaineRematch_EventScript_NoRoom
    giveitem ITEM_TM50
    release
    end

BlaineRematch_EventScript_TMSunnyDay::
    checkitemspace ITEM_TM11
    goto_if_eq VAR_RESULT, FALSE, BlaineRematch_EventScript_NoRoom
    giveitem ITEM_TM11
    release
    end

CinnabarIsland_Gym_EventScript_BlaineRematchDefeated::
    goto BlaineRematch_EventScript_GiveReward
    end

GiovanniRematch_Text_RematchIntro::
    .string "Rematch?$"

GiovanniRematch_Text_ChoosePrize::
    .string "(GG) GOOD GAME.$"

GiovanniRematch_Text_ChoosePrizeSimple::
    .string "Choose your prize.$"

GiovanniRematch_EventScript_GiveReward::
    lock
    faceplayer
    message GiovanniRematch_Text_ChoosePrizeSimple
    multichoice 0, 0, MULTICHOICE_GYM_REWARD, FALSE
    switch VAR_RESULT
    case 0, GiovanniRematch_EventScript_HeldItem
    case 1, GiovanniRematch_EventScript_MoveTutorMenu
    case 2, GiovanniRematch_EventScript_TMMenu
    case SCR_MENU_CANCEL, GiovanniRematch_EventScript_Cancel
    end

GiovanniRematch_EventScript_Cancel::
    release
    end

GiovanniRematch_EventScript_HeldItem::
    checkitemspace ITEM_SOFT_SAND
    goto_if_eq VAR_RESULT, FALSE, GiovanniRematch_EventScript_NoRoom
    giveitem ITEM_SOFT_SAND
    release
    end

GiovanniRematch_EventScript_NoRoom::
    msgbox ViridianCity_Gym_Text_YouDoNotHaveSpace
    release
    end

GiovanniRematch_EventScript_MoveTutorMenu::
    multichoice 0, 0, MULTICHOICE_GIOVANNI_TUTOR, FALSE
    goto GiovanniRematch_EventScript_DoTutor

GiovanniRematch_EventScript_DoTutor::
    goto_if_eq VAR_RESULT, SCR_MENU_CANCEL, GiovanniRematch_EventScript_GiveReward
    goto_if_eq VAR_RESULT, 0, GiovanniRematch_DoTutor_MudSlap
    goto_if_eq VAR_RESULT, 1, GiovanniRematch_DoTutor_MudSport
    @ case 2 = Spikes
    setvar VAR_0x8005, MOVETUTOR_SPIKES
    goto GiovanniRematch_DoTutor_Choose
GiovanniRematch_DoTutor_MudSlap:
    setvar VAR_0x8005, MOVETUTOR_MUD_SLAP
    goto GiovanniRematch_DoTutor_Choose
GiovanniRematch_DoTutor_MudSport:
    setvar VAR_0x8005, MOVETUTOR_MUD_SPORT
    goto GiovanniRematch_DoTutor_Choose
GiovanniRematch_DoTutor_Choose:
    special ChooseMonForMoveTutor
    waitstate
    release
    end

GiovanniRematch_EventScript_TMMenu::
    multichoice 0, 0, MULTICHOICE_GIOVANNI_TM, FALSE
    switch VAR_RESULT
    case 0, GiovanniRematch_EventScript_TMDig
    case 1, GiovanniRematch_EventScript_TMEarthquake
    case SCR_MENU_CANCEL, GiovanniRematch_EventScript_GiveReward
    end

GiovanniRematch_EventScript_TMDig::
    checkitemspace ITEM_TM28
    goto_if_eq VAR_RESULT, FALSE, GiovanniRematch_EventScript_NoRoom
    giveitem ITEM_TM28
    release
    end

GiovanniRematch_EventScript_TMEarthquake::
    checkitemspace ITEM_TM26
    goto_if_eq VAR_RESULT, FALSE, GiovanniRematch_EventScript_NoRoom
    giveitem ITEM_TM26
    release
    end

ViridianCity_Gym_EventScript_GiovanniRematchDefeated::
    goto GiovanniRematch_EventScript_GiveReward
    end

FalknerDuel_Text_Duel::
    .string "Duel?$"

FalknerRematch_Text_RematchIntro::
    .string "Rematch?$"

FalknerRematch_Text_ChoosePrize::
    .string "(GG) GOOD GAME.$"

FalknerRematch_Text_ChoosePrizeSimple::
    .string "Choose your prize.$"

FalknerRematch_Text_NoRoom::
    .string "You don't have room for this.$"

EventScript_Falkner::
    lock
    faceplayer
    goto_if_set FLAG_DEFEATED_FALKNER, EventScript_FalknerRematch
    msgbox FalknerDuel_Text_Duel, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, EventScript_FalknerDecline
    trainerbattle_no_intro TRAINER_LEADER_FALKNER, FalknerRematch_Text_ChoosePrize
    setflag FLAG_DEFEATED_FALKNER
    goto_if_unset FLAG_GOT_PRIZE_FROM_FALKNER, EventScript_FalknerGivePrize
    msgbox FalknerRematch_Text_RematchIntro
    release
    end

EventScript_FalknerDecline::
    release
    end

EventScript_FalknerGivePrize::
    checkitemspace ITEM_RARE_CANDY
    goto_if_eq VAR_RESULT, FALSE, FalknerRematch_EventScript_NoRoom
    giveitem ITEM_RARE_CANDY
    setflag FLAG_GOT_PRIZE_FROM_FALKNER
    release
    end

EventScript_FalknerRematch::
    msgbox FalknerRematch_Text_RematchIntro, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, EventScript_FalknerRematchDecline
    trainerbattle_no_intro TRAINER_LEADER_FALKNER_2, FalknerRematch_Text_ChoosePrize
    goto EventScript_FalknerRematchDefeated
    release
    end

EventScript_FalknerRematchDecline::
    release
    end

FalknerRematch_EventScript_GiveReward::
    lock
    faceplayer
    message FalknerRematch_Text_ChoosePrizeSimple
    multichoice 0, 0, MULTICHOICE_GYM_REWARD, FALSE
    switch VAR_RESULT
    case 0, FalknerRematch_EventScript_HeldItem
    case 1, FalknerRematch_EventScript_MoveTutorMenu
    case 2, FalknerRematch_EventScript_TMMenu
    case SCR_MENU_CANCEL, FalknerRematch_EventScript_Cancel
    end

FalknerRematch_EventScript_Cancel::
    release
    end

FalknerRematch_EventScript_HeldItem::
    checkitemspace ITEM_SHARP_BEAK
    goto_if_eq VAR_RESULT, FALSE, FalknerRematch_EventScript_NoRoom
    giveitem ITEM_SHARP_BEAK
    release
    end

FalknerRematch_EventScript_NoRoom::
    msgbox FalknerRematch_Text_NoRoom
    release
    end

FalknerRematch_EventScript_MoveTutorMenu::
    multichoice 0, 0, MULTICHOICE_FALKNER_TUTOR, FALSE
    goto FalknerRematch_EventScript_DoTutor

FalknerRematch_EventScript_DoTutor::
    goto_if_eq VAR_RESULT, SCR_MENU_CANCEL, FalknerRematch_EventScript_GiveReward
    goto_if_eq VAR_RESULT, 0, FalknerRematch_DoTutor_FeatherDance
    goto_if_eq VAR_RESULT, 1, FalknerRematch_DoTutor_Gust
    @ case 2 = Sky Attack
    setvar VAR_0x8005, MOVETUTOR_SKY_ATTACK
    goto FalknerRematch_DoTutor_Choose
FalknerRematch_DoTutor_FeatherDance:
    setvar VAR_0x8005, MOVETUTOR_FEATHER_DANCE
    goto FalknerRematch_DoTutor_Choose
FalknerRematch_DoTutor_Gust:
    setvar VAR_0x8005, MOVETUTOR_GUST
    goto FalknerRematch_DoTutor_Choose
FalknerRematch_DoTutor_Choose:
    special ChooseMonForMoveTutor
    waitstate
    release
    end

FalknerRematch_EventScript_TMMenu::
    multichoice 0, 0, MULTICHOICE_FALKNER_TM, FALSE
    switch VAR_RESULT
    case 0, FalknerRematch_EventScript_TMHiddenPower
    case 1, FalknerRematch_EventScript_TMAerialAce
    case SCR_MENU_CANCEL, FalknerRematch_EventScript_GiveReward
    end

FalknerRematch_EventScript_TMHiddenPower::
    checkitemspace ITEM_TM10
    goto_if_eq VAR_RESULT, FALSE, FalknerRematch_EventScript_NoRoom
    giveitem ITEM_TM10
    release
    end

FalknerRematch_EventScript_TMAerialAce::
    checkitemspace ITEM_TM40
    goto_if_eq VAR_RESULT, FALSE, FalknerRematch_EventScript_NoRoom
    giveitem ITEM_TM40
    release
    end

EventScript_FalknerRematchDefeated::
    goto FalknerRematch_EventScript_GiveReward
    end

BugsyDuel_Text_Duel::
    .string "Duel?$"

BugsyRematch_Text_RematchIntro::
    .string "Rematch?$"

BugsyRematch_Text_ChoosePrize::
    .string "(GG) GOOD GAME.$"

BugsyRematch_Text_ChoosePrizeSimple::
    .string "Choose your prize.$"

BugsyRematch_Text_NoRoom::
    .string "You don't have room for this.$"

EventScript_Bugsy::
    lock
    faceplayer
    goto_if_set FLAG_DEFEATED_BUGSY, EventScript_BugsyRematch
    msgbox BugsyDuel_Text_Duel, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, EventScript_BugsyDecline
    trainerbattle_no_intro TRAINER_LEADER_BUGSY, BugsyRematch_Text_ChoosePrize
    setflag FLAG_DEFEATED_BUGSY
    goto_if_unset FLAG_GOT_PRIZE_FROM_BUGSY, EventScript_BugsyGivePrize
    msgbox BugsyRematch_Text_RematchIntro
    release
    end

EventScript_BugsyDecline::
    release
    end

EventScript_BugsyGivePrize::
    checkitemspace ITEM_RARE_CANDY
    goto_if_eq VAR_RESULT, FALSE, BugsyRematch_EventScript_NoRoom
    giveitem ITEM_RARE_CANDY
    setflag FLAG_GOT_PRIZE_FROM_BUGSY
    release
    end

EventScript_BugsyRematch::
    msgbox BugsyRematch_Text_RematchIntro, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, EventScript_BugsyRematchDecline
    trainerbattle_no_intro TRAINER_LEADER_BUGSY_2, BugsyRematch_Text_ChoosePrize
    goto EventScript_BugsyRematchDefeated
    release
    end

EventScript_BugsyRematchDecline::
    release
    end

BugsyRematch_EventScript_GiveReward::
    lock
    faceplayer
    message BugsyRematch_Text_ChoosePrizeSimple
    multichoice 0, 0, MULTICHOICE_GYM_REWARD, FALSE
    switch VAR_RESULT
    case 0, BugsyRematch_EventScript_HeldItem
    case 1, BugsyRematch_EventScript_MoveTutorMenu
    case 2, BugsyRematch_EventScript_TMMenu
    case SCR_MENU_CANCEL, BugsyRematch_EventScript_Cancel
    end

BugsyRematch_EventScript_Cancel::
    release
    end

BugsyRematch_EventScript_HeldItem::
    checkitemspace ITEM_SILVER_POWDER
    goto_if_eq VAR_RESULT, FALSE, BugsyRematch_EventScript_NoRoom
    giveitem ITEM_SILVER_POWDER
    release
    end

BugsyRematch_EventScript_NoRoom::
    msgbox BugsyRematch_Text_NoRoom
    release
    end

BugsyRematch_EventScript_MoveTutorMenu::
    multichoice 0, 0, MULTICHOICE_BUGSY_TUTOR, FALSE
    goto BugsyRematch_EventScript_DoTutor

BugsyRematch_EventScript_DoTutor::
    goto_if_eq VAR_RESULT, SCR_MENU_CANCEL, BugsyRematch_EventScript_GiveReward
    @ case 0 = Fury Cutter
    setvar VAR_0x8005, MOVETUTOR_FURY_CUTTER
    goto BugsyRematch_DoTutor_Choose
BugsyRematch_DoTutor_Choose:
    special ChooseMonForMoveTutor
    waitstate
    release
    end

BugsyRematch_EventScript_TMMenu::
    multichoice 0, 0, MULTICHOICE_BUGSY_TM, FALSE
    switch VAR_RESULT
    case 0, BugsyRematch_EventScript_TMHiddenPower
    case SCR_MENU_CANCEL, BugsyRematch_EventScript_GiveReward
    end

BugsyRematch_EventScript_TMHiddenPower::
    checkitemspace ITEM_TM10
    goto_if_eq VAR_RESULT, FALSE, BugsyRematch_EventScript_NoRoom
    giveitem ITEM_TM10
    release
    end

EventScript_BugsyRematchDefeated::
    goto BugsyRematch_EventScript_GiveReward
    end

WhitneyDuel_Text_Duel::
    .string "Duel?$"

WhitneyRematch_Text_RematchIntro::
    .string "Rematch?$"

WhitneyRematch_Text_ChoosePrize::
    .string "(GG) GOOD GAME.$"

WhitneyRematch_Text_ChoosePrizeSimple::
    .string "Choose your prize.$"

WhitneyRematch_Text_NoRoom::
    .string "You don't have room for this.$"

EventScript_Whitney::
    lock
    faceplayer
    goto_if_set FLAG_DEFEATED_WHITNEY, EventScript_WhitneyRematch
    msgbox WhitneyDuel_Text_Duel, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, EventScript_WhitneyDecline
    trainerbattle_no_intro TRAINER_LEADER_WHITNEY, WhitneyRematch_Text_ChoosePrize
    setflag FLAG_DEFEATED_WHITNEY
    goto_if_unset FLAG_GOT_PRIZE_FROM_WHITNEY, EventScript_WhitneyGivePrize
    msgbox WhitneyRematch_Text_RematchIntro
    release
    end

EventScript_WhitneyDecline::
    release
    end

EventScript_WhitneyGivePrize::
    checkitemspace ITEM_RARE_CANDY
    goto_if_eq VAR_RESULT, FALSE, WhitneyRematch_EventScript_NoRoom
    giveitem ITEM_RARE_CANDY
    setflag FLAG_GOT_PRIZE_FROM_WHITNEY
    release
    end

EventScript_WhitneyRematch::
    msgbox WhitneyRematch_Text_RematchIntro, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, EventScript_WhitneyRematchDecline
    trainerbattle_no_intro TRAINER_LEADER_WHITNEY_2, WhitneyRematch_Text_ChoosePrize
    goto EventScript_WhitneyRematchDefeated
    release
    end

EventScript_WhitneyRematchDecline::
    release
    end

WhitneyRematch_EventScript_GiveReward::
    lock
    faceplayer
    message WhitneyRematch_Text_ChoosePrizeSimple
    multichoice 0, 0, MULTICHOICE_GYM_REWARD, FALSE
    switch VAR_RESULT
    case 0, WhitneyRematch_EventScript_HeldItem
    case 1, WhitneyRematch_EventScript_MoveTutorMenu
    case 2, WhitneyRematch_EventScript_TMMenu
    case SCR_MENU_CANCEL, WhitneyRematch_EventScript_Cancel
    end

WhitneyRematch_EventScript_Cancel::
    release
    end

WhitneyRematch_EventScript_HeldItem::
    checkitemspace ITEM_SILK_SCARF
    goto_if_eq VAR_RESULT, FALSE, WhitneyRematch_EventScript_NoRoom
    giveitem ITEM_SILK_SCARF
    release
    end

WhitneyRematch_EventScript_NoRoom::
    msgbox WhitneyRematch_Text_NoRoom
    release
    end

WhitneyRematch_EventScript_MoveTutorMenu::
    multichoice 0, 0, MULTICHOICE_WHITNEY_TUTOR, FALSE
    goto WhitneyRematch_EventScript_DoTutor

WhitneyRematch_EventScript_DoTutor::
    goto_if_eq VAR_RESULT, SCR_MENU_CANCEL, WhitneyRematch_EventScript_GiveReward
    goto_if_eq VAR_RESULT, 0, WhitneyRematch_DoTutor_BatonPass
    goto_if_eq VAR_RESULT, 1, WhitneyRematch_DoTutor_BellyDrum
    goto_if_eq VAR_RESULT, 2, WhitneyRematch_DoTutor_BodySlam
    goto_if_eq VAR_RESULT, 3, WhitneyRematch_DoTutor_Charm
    goto_if_eq VAR_RESULT, 4, WhitneyRematch_DoTutor_DefenseCurl
    goto_if_eq VAR_RESULT, 5, WhitneyRematch_DoTutor_DizzyPunch
    goto_if_eq VAR_RESULT, 6, WhitneyRematch_DoTutor_DoubleEdge
    goto_if_eq VAR_RESULT, 7, WhitneyRematch_DoTutor_DoubleSlap
    goto_if_eq VAR_RESULT, 8, WhitneyRematch_DoTutor_Encore
    goto_if_eq VAR_RESULT, 9, WhitneyRematch_DoTutor_Endure
    goto_if_eq VAR_RESULT, 10, WhitneyRematch_DoTutor_Explosion
    goto_if_eq VAR_RESULT, 11, WhitneyRematch_DoTutor_ExtremeSpeed
    goto_if_eq VAR_RESULT, 12, WhitneyRematch_DoTutor_FalseSwipe
    goto_if_eq VAR_RESULT, 13, WhitneyRematch_DoTutor_Flail
    goto_if_eq VAR_RESULT, 14, WhitneyRematch_DoTutor_FollowMe
    goto_if_eq VAR_RESULT, 15, WhitneyRematch_DoTutor_Foresight
    goto_if_eq VAR_RESULT, 16, WhitneyRematch_DoTutor_FuryAttack
    goto_if_eq VAR_RESULT, 17, WhitneyRematch_DoTutor_Growth
    goto_if_eq VAR_RESULT, 18, WhitneyRematch_DoTutor_HealBell
    goto_if_eq VAR_RESULT, 19, WhitneyRematch_DoTutor_HelpingHand
    goto_if_eq VAR_RESULT, 20, WhitneyRematch_DoTutor_HornDrill
    goto_if_eq VAR_RESULT, 21, WhitneyRematch_DoTutor_LovelyKiss
    goto_if_eq VAR_RESULT, 22, WhitneyRematch_DoTutor_MegaKick
    goto_if_eq VAR_RESULT, 23, WhitneyRematch_DoTutor_MegaPunch
    goto_if_eq VAR_RESULT, 24, WhitneyRematch_DoTutor_Metronome
    goto_if_eq VAR_RESULT, 25, WhitneyRematch_DoTutor_Mimic
    goto_if_eq VAR_RESULT, 26, WhitneyRematch_DoTutor_MindReader
    goto_if_eq VAR_RESULT, 27, WhitneyRematch_DoTutor_Moonlight
    goto_if_eq VAR_RESULT, 28, WhitneyRematch_DoTutor_MorningSun
    goto_if_eq VAR_RESULT, 29, WhitneyRematch_DoTutor_PayDay
    goto_if_eq VAR_RESULT, 30, WhitneyRematch_DoTutor_PsychUp
    goto_if_eq VAR_RESULT, 31, WhitneyRematch_DoTutor_QuickAttack
    goto_if_eq VAR_RESULT, 32, WhitneyRematch_DoTutor_Rage
    goto_if_eq VAR_RESULT, 33, WhitneyRematch_DoTutor_RapidSpin
    goto_if_eq VAR_RESULT, 34, WhitneyRematch_DoTutor_Refresh
    goto_if_eq VAR_RESULT, 35, WhitneyRematch_DoTutor_Safeguard
    goto_if_eq VAR_RESULT, 36, WhitneyRematch_DoTutor_ScaryFace
    goto_if_eq VAR_RESULT, 37, WhitneyRematch_DoTutor_SelfDestruct
    goto_if_eq VAR_RESULT, 38, WhitneyRematch_DoTutor_Sharpen
    goto_if_eq VAR_RESULT, 39, WhitneyRematch_DoTutor_Sing
    goto_if_eq VAR_RESULT, 40, WhitneyRematch_DoTutor_SleepTalk
    goto_if_eq VAR_RESULT, 41, WhitneyRematch_DoTutor_Snore
    goto_if_eq VAR_RESULT, 42, WhitneyRematch_DoTutor_SoftBoiled
    goto_if_eq VAR_RESULT, 43, WhitneyRematch_DoTutor_SonicBoom
    goto_if_eq VAR_RESULT, 44, WhitneyRematch_DoTutor_Splash
    goto_if_eq VAR_RESULT, 45, WhitneyRematch_DoTutor_Substitute
    goto_if_eq VAR_RESULT, 46, WhitneyRematch_DoTutor_Swagger
    goto_if_eq VAR_RESULT, 47, WhitneyRematch_DoTutor_SweetKiss
    goto_if_eq VAR_RESULT, 48, WhitneyRematch_DoTutor_SweetScent
    goto_if_eq VAR_RESULT, 49, WhitneyRematch_DoTutor_Swift
    goto_if_eq VAR_RESULT, 50, WhitneyRematch_DoTutor_SwordsDance
    goto_if_eq VAR_RESULT, 51, WhitneyRematch_DoTutor_TeeterDance
    goto_if_eq VAR_RESULT, 52, WhitneyRematch_DoTutor_Thrash
    goto_if_eq VAR_RESULT, 53, WhitneyRematch_DoTutor_Tickle
    goto_if_eq VAR_RESULT, 54, WhitneyRematch_DoTutor_TriAttack
    goto_if_eq VAR_RESULT, 55, WhitneyRematch_DoTutor_Whirlwind
    goto_if_eq VAR_RESULT, 56, WhitneyRematch_DoTutor_Wish
    @ case 57 = Yawn
    setvar VAR_0x8005, MOVETUTOR_YAWN
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_BatonPass:
    setvar VAR_0x8005, MOVETUTOR_BATON_PASS
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_BellyDrum:
    setvar VAR_0x8005, MOVETUTOR_BELLY_DRUM
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_BodySlam:
    setvar VAR_0x8005, MOVETUTOR_BODY_SLAM
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Charm:
    setvar VAR_0x8005, MOVETUTOR_CHARM
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_DefenseCurl:
    setvar VAR_0x8005, MOVETUTOR_DEFENSE_CURL
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_DizzyPunch:
    setvar VAR_0x8005, MOVETUTOR_DIZZY_PUNCH
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_DoubleEdge:
    setvar VAR_0x8005, MOVETUTOR_DOUBLE_EDGE
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_DoubleSlap:
    setvar VAR_0x8005, MOVETUTOR_DOUBLE_SLAP
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Encore:
    setvar VAR_0x8005, MOVETUTOR_ENCORE
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Endure:
    setvar VAR_0x8005, MOVETUTOR_ENDURE
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Explosion:
    setvar VAR_0x8005, MOVETUTOR_EXPLOSION
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_ExtremeSpeed:
    setvar VAR_0x8005, MOVETUTOR_EXTREME_SPEED
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_FalseSwipe:
    setvar VAR_0x8005, MOVETUTOR_FALSE_SWIPE
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Flail:
    setvar VAR_0x8005, MOVETUTOR_FLAIL
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_FollowMe:
    setvar VAR_0x8005, MOVETUTOR_FOLLOW_ME
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Foresight:
    setvar VAR_0x8005, MOVETUTOR_FORESIGHT
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_FuryAttack:
    setvar VAR_0x8005, MOVETUTOR_FURY_ATTACK
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Growth:
    setvar VAR_0x8005, MOVETUTOR_GROWTH
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_HealBell:
    setvar VAR_0x8005, MOVETUTOR_HEAL_BELL
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_HelpingHand:
    setvar VAR_0x8005, MOVETUTOR_HELPING_HAND
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_HornDrill:
    setvar VAR_0x8005, MOVETUTOR_HORN_DRILL
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_LovelyKiss:
    setvar VAR_0x8005, MOVETUTOR_LOVELY_KISS
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_MegaKick:
    setvar VAR_0x8005, MOVETUTOR_MEGA_KICK
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_MegaPunch:
    setvar VAR_0x8005, MOVETUTOR_MEGA_PUNCH
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Metronome:
    setvar VAR_0x8005, MOVETUTOR_METRONOME
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Mimic:
    setvar VAR_0x8005, MOVETUTOR_MIMIC
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_MindReader:
    setvar VAR_0x8005, MOVETUTOR_MIND_READER
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Moonlight:
    setvar VAR_0x8005, MOVETUTOR_MOONLIGHT
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_MorningSun:
    setvar VAR_0x8005, MOVETUTOR_MORNING_SUN
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_PayDay:
    setvar VAR_0x8005, MOVETUTOR_PAY_DAY
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_PsychUp:
    setvar VAR_0x8005, MOVETUTOR_PSYCH_UP
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_QuickAttack:
    setvar VAR_0x8005, MOVETUTOR_QUICK_ATTACK
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Rage:
    setvar VAR_0x8005, MOVETUTOR_RAGE
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_RapidSpin:
    setvar VAR_0x8005, MOVETUTOR_RAPID_SPIN
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Refresh:
    setvar VAR_0x8005, MOVETUTOR_REFRESH
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Safeguard:
    setvar VAR_0x8005, MOVETUTOR_SAFEGUARD
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_ScaryFace:
    setvar VAR_0x8005, MOVETUTOR_SCARY_FACE
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_SelfDestruct:
    setvar VAR_0x8005, MOVETUTOR_SELF_DESTRUCT
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Sharpen:
    setvar VAR_0x8005, MOVETUTOR_SHARPEN
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Sing:
    setvar VAR_0x8005, MOVETUTOR_SING
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_SleepTalk:
    setvar VAR_0x8005, MOVETUTOR_SLEEP_TALK
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Snore:
    setvar VAR_0x8005, MOVETUTOR_SNORE
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_SoftBoiled:
    setvar VAR_0x8005, MOVETUTOR_SOFT_BOILED
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_SonicBoom:
    setvar VAR_0x8005, MOVETUTOR_SONIC_BOOM
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Splash:
    setvar VAR_0x8005, MOVETUTOR_SPLASH
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Substitute:
    setvar VAR_0x8005, MOVETUTOR_SUBSTITUTE
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Swagger:
    setvar VAR_0x8005, MOVETUTOR_SWAGGER
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_SweetKiss:
    setvar VAR_0x8005, MOVETUTOR_SWEET_KISS
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_SweetScent:
    setvar VAR_0x8005, MOVETUTOR_SWEET_SCENT
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Swift:
    setvar VAR_0x8005, MOVETUTOR_SWIFT
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_SwordsDance:
    setvar VAR_0x8005, MOVETUTOR_SWORDS_DANCE
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_TeeterDance:
    setvar VAR_0x8005, MOVETUTOR_TEETER_DANCE
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Thrash:
    setvar VAR_0x8005, MOVETUTOR_THRASH
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Tickle:
    setvar VAR_0x8005, MOVETUTOR_TICKLE
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_TriAttack:
    setvar VAR_0x8005, MOVETUTOR_TRI_ATTACK
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Whirlwind:
    setvar VAR_0x8005, MOVETUTOR_WHIRLWIND
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Wish:
    setvar VAR_0x8005, MOVETUTOR_WISH
    goto WhitneyRematch_DoTutor_Choose
WhitneyRematch_DoTutor_Choose:
    special ChooseMonForMoveTutor
    waitstate
    release
    end

WhitneyRematch_EventScript_TMMenu::
    multichoice 0, 0, MULTICHOICE_WHITNEY_TM, FALSE
    switch VAR_RESULT
    case 0, WhitneyRematch_EventScript_TMAttract
    case 1, WhitneyRematch_EventScript_TMDoubleTeam
    case 2, WhitneyRematch_EventScript_TMFacade
    case 3, WhitneyRematch_EventScript_TMFrustration
    case 4, WhitneyRematch_EventScript_TMHyperBeam
    case 5, WhitneyRematch_EventScript_TMProtect
    case 6, WhitneyRematch_EventScript_TMReturn
    case 7, WhitneyRematch_EventScript_TMRoar
    case 8, WhitneyRematch_EventScript_TMSafeguard
    case 9, WhitneyRematch_EventScript_TMSecretPower
    case SCR_MENU_CANCEL, WhitneyRematch_EventScript_GiveReward
    end

WhitneyRematch_EventScript_TMAttract::
    checkitemspace ITEM_TM45
    goto_if_eq VAR_RESULT, FALSE, WhitneyRematch_EventScript_NoRoom
    giveitem ITEM_TM45
    release
    end

WhitneyRematch_EventScript_TMDoubleTeam::
    checkitemspace ITEM_TM32
    goto_if_eq VAR_RESULT, FALSE, WhitneyRematch_EventScript_NoRoom
    giveitem ITEM_TM32
    release
    end

WhitneyRematch_EventScript_TMFacade::
    checkitemspace ITEM_TM42
    goto_if_eq VAR_RESULT, FALSE, WhitneyRematch_EventScript_NoRoom
    giveitem ITEM_TM42
    release
    end

WhitneyRematch_EventScript_TMFrustration::
    checkitemspace ITEM_TM21
    goto_if_eq VAR_RESULT, FALSE, WhitneyRematch_EventScript_NoRoom
    giveitem ITEM_TM21
    release
    end

WhitneyRematch_EventScript_TMHyperBeam::
    checkitemspace ITEM_TM15
    goto_if_eq VAR_RESULT, FALSE, WhitneyRematch_EventScript_NoRoom
    giveitem ITEM_TM15
    release
    end

WhitneyRematch_EventScript_TMProtect::
    checkitemspace ITEM_TM17
    goto_if_eq VAR_RESULT, FALSE, WhitneyRematch_EventScript_NoRoom
    giveitem ITEM_TM17
    release
    end

WhitneyRematch_EventScript_TMReturn::
    checkitemspace ITEM_TM27
    goto_if_eq VAR_RESULT, FALSE, WhitneyRematch_EventScript_NoRoom
    giveitem ITEM_TM27
    release
    end

WhitneyRematch_EventScript_TMRoar::
    checkitemspace ITEM_TM05
    goto_if_eq VAR_RESULT, FALSE, WhitneyRematch_EventScript_NoRoom
    giveitem ITEM_TM05
    release
    end

WhitneyRematch_EventScript_TMSafeguard::
    checkitemspace ITEM_TM20
    goto_if_eq VAR_RESULT, FALSE, WhitneyRematch_EventScript_NoRoom
    giveitem ITEM_TM20
    release
    end

WhitneyRematch_EventScript_TMSecretPower::
    checkitemspace ITEM_TM43
    goto_if_eq VAR_RESULT, FALSE, WhitneyRematch_EventScript_NoRoom
    giveitem ITEM_TM43
    release
    end

EventScript_WhitneyRematchDefeated::
    goto WhitneyRematch_EventScript_GiveReward
    end

MortyDuel_Text_Duel::
    .string "Duel?$"

MortyRematch_Text_RematchIntro::
    .string "Rematch?$"

MortyRematch_Text_ChoosePrize::
    .string "(GG) GOOD GAME.$"

MortyRematch_Text_ChoosePrizeSimple::
    .string "Choose your prize.$"

MortyRematch_Text_NoRoom::
    .string "You don't have room for this.$"

EventScript_Morty::
    lock
    faceplayer
    goto_if_set FLAG_DEFEATED_MORTY, EventScript_MortyRematch
    msgbox MortyDuel_Text_Duel, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, EventScript_MortyDecline
    trainerbattle_no_intro TRAINER_LEADER_MORTY, MortyRematch_Text_ChoosePrize
    setflag FLAG_DEFEATED_MORTY
    goto_if_unset FLAG_GOT_PRIZE_FROM_MORTY, EventScript_MortyGivePrize
    msgbox MortyRematch_Text_RematchIntro
    release
    end

EventScript_MortyDecline::
    release
    end

EventScript_MortyGivePrize::
    checkitemspace ITEM_RARE_CANDY
    goto_if_eq VAR_RESULT, FALSE, MortyRematch_EventScript_NoRoom
    giveitem ITEM_RARE_CANDY
    setflag FLAG_GOT_PRIZE_FROM_MORTY
    release
    end

EventScript_MortyRematch::
    msgbox MortyRematch_Text_RematchIntro, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, EventScript_MortyRematchDecline
    trainerbattle_no_intro TRAINER_LEADER_MORTY_2, MortyRematch_Text_ChoosePrize
    goto EventScript_MortyRematchDefeated
    release
    end

EventScript_MortyRematchDecline::
    release
    end

MortyRematch_EventScript_GiveReward::
    lock
    faceplayer
    message MortyRematch_Text_ChoosePrizeSimple
    multichoice 0, 0, MULTICHOICE_GYM_REWARD, FALSE
    switch VAR_RESULT
    case 0, MortyRematch_EventScript_HeldItemMenu
    case 1, MortyRematch_EventScript_MoveTutorMenu
    case 2, MortyRematch_EventScript_TMMenu
    case SCR_MENU_CANCEL, MortyRematch_EventScript_Cancel
    end

MortyRematch_EventScript_Cancel::
    release
    end

MortyRematch_EventScript_HeldItemMenu::
    multichoice 0, 0, MULTICHOICE_MORTY_HELD, FALSE
    switch VAR_RESULT
    case 0, MortyRematch_EventScript_HeldSpellTag
    case 1, MortyRematch_EventScript_HeldBlackGlasses
    case SCR_MENU_CANCEL, MortyRematch_EventScript_GiveReward
    end

MortyRematch_EventScript_HeldSpellTag::
    checkitemspace ITEM_SPELL_TAG
    goto_if_eq VAR_RESULT, FALSE, MortyRematch_EventScript_NoRoom
    giveitem ITEM_SPELL_TAG
    release
    end

MortyRematch_EventScript_HeldBlackGlasses::
    checkitemspace ITEM_BLACK_GLASSES
    goto_if_eq VAR_RESULT, FALSE, MortyRematch_EventScript_NoRoom
    giveitem ITEM_BLACK_GLASSES
    release
    end

MortyRematch_EventScript_NoRoom::
    msgbox MortyRematch_Text_NoRoom
    release
    end

MortyRematch_EventScript_MoveTutorMenu::
    multichoice 0, 0, MULTICHOICE_MORTY_TUTOR, FALSE
    goto MortyRematch_EventScript_DoTutor

MortyRematch_EventScript_DoTutor::
    goto_if_eq VAR_RESULT, SCR_MENU_CANCEL, MortyRematch_EventScript_GiveReward
    goto_if_eq VAR_RESULT, 0, MortyRematch_DoTutor_ConfuseRay
    goto_if_eq VAR_RESULT, 1, MortyRematch_DoTutor_Nightmare
    goto_if_eq VAR_RESULT, 2, MortyRematch_DoTutor_NightShade
    goto_if_eq VAR_RESULT, 3, MortyRematch_DoTutor_BeatUp
    goto_if_eq VAR_RESULT, 4, MortyRematch_DoTutor_Bite
    goto_if_eq VAR_RESULT, 5, MortyRematch_DoTutor_Crunch
    goto_if_eq VAR_RESULT, 6, MortyRematch_DoTutor_FaintAttack
    @ case 7 = Pursuit
    setvar VAR_0x8005, MOVETUTOR_PURSUIT
    goto MortyRematch_DoTutor_Choose
MortyRematch_DoTutor_ConfuseRay:
    setvar VAR_0x8005, MOVETUTOR_CONFUSE_RAY
    goto MortyRematch_DoTutor_Choose
MortyRematch_DoTutor_Nightmare:
    setvar VAR_0x8005, MOVETUTOR_NIGHTMARE
    goto MortyRematch_DoTutor_Choose
MortyRematch_DoTutor_NightShade:
    setvar VAR_0x8005, MOVETUTOR_NIGHT_SHADE
    goto MortyRematch_DoTutor_Choose
MortyRematch_DoTutor_BeatUp:
    setvar VAR_0x8005, MOVETUTOR_BEAT_UP
    goto MortyRematch_DoTutor_Choose
MortyRematch_DoTutor_Bite:
    setvar VAR_0x8005, MOVETUTOR_BITE
    goto MortyRematch_DoTutor_Choose
MortyRematch_DoTutor_Crunch:
    setvar VAR_0x8005, MOVETUTOR_CRUNCH
    goto MortyRematch_DoTutor_Choose
MortyRematch_DoTutor_FaintAttack:
    setvar VAR_0x8005, MOVETUTOR_FAINT_ATTACK
    goto MortyRematch_DoTutor_Choose
MortyRematch_DoTutor_Choose:
    special ChooseMonForMoveTutor
    waitstate
    release
    end

MortyRematch_EventScript_TMMenu::
    multichoice 0, 0, MULTICHOICE_MORTY_TM, FALSE
    switch VAR_RESULT
    case 0, MortyRematch_EventScript_TMHiddenPower
    case 1, MortyRematch_EventScript_TMShadowBall
    case 2, MortyRematch_EventScript_TMSnatch
    case 3, MortyRematch_EventScript_TMTaunt
    case 4, MortyRematch_EventScript_TMThief
    case 5, MortyRematch_EventScript_TMTorment
    case SCR_MENU_CANCEL, MortyRematch_EventScript_GiveReward
    end

MortyRematch_EventScript_TMHiddenPower::
    checkitemspace ITEM_TM10
    goto_if_eq VAR_RESULT, FALSE, MortyRematch_EventScript_NoRoom
    giveitem ITEM_TM10
    release
    end

MortyRematch_EventScript_TMShadowBall::
    checkitemspace ITEM_TM30
    goto_if_eq VAR_RESULT, FALSE, MortyRematch_EventScript_NoRoom
    giveitem ITEM_TM30
    release
    end

MortyRematch_EventScript_TMSnatch::
    checkitemspace ITEM_TM49
    goto_if_eq VAR_RESULT, FALSE, MortyRematch_EventScript_NoRoom
    giveitem ITEM_TM49
    release
    end

MortyRematch_EventScript_TMTaunt::
    checkitemspace ITEM_TM12
    goto_if_eq VAR_RESULT, FALSE, MortyRematch_EventScript_NoRoom
    giveitem ITEM_TM12
    release
    end

MortyRematch_EventScript_TMThief::
    checkitemspace ITEM_TM46
    goto_if_eq VAR_RESULT, FALSE, MortyRematch_EventScript_NoRoom
    giveitem ITEM_TM46
    release
    end

MortyRematch_EventScript_TMTorment::
    checkitemspace ITEM_TM41
    goto_if_eq VAR_RESULT, FALSE, MortyRematch_EventScript_NoRoom
    giveitem ITEM_TM41
    release
    end

EventScript_MortyRematchDefeated::
    goto MortyRematch_EventScript_GiveReward
    end

ChuckDuel_Text_Duel::
    .string "Duel?$"

ChuckRematch_Text_RematchIntro::
    .string "Rematch?$"

ChuckRematch_Text_ChoosePrize::
    .string "(GG) GOOD GAME.$"

ChuckRematch_Text_ChoosePrizeSimple::
    .string "Choose your prize.$"

ChuckRematch_Text_NoRoom::
    .string "You don't have room for this.$"

EventScript_Chuck::
    lock
    faceplayer
    goto_if_set FLAG_DEFEATED_CHUCK, EventScript_ChuckRematch
    msgbox ChuckDuel_Text_Duel, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, EventScript_ChuckDecline
    trainerbattle_no_intro TRAINER_LEADER_CHUCK, ChuckRematch_Text_ChoosePrize
    setflag FLAG_DEFEATED_CHUCK
    goto_if_unset FLAG_GOT_PRIZE_FROM_CHUCK, EventScript_ChuckGivePrize
    msgbox ChuckRematch_Text_RematchIntro
    release
    end

EventScript_ChuckDecline::
    release
    end

EventScript_ChuckGivePrize::
    checkitemspace ITEM_RARE_CANDY
    goto_if_eq VAR_RESULT, FALSE, ChuckRematch_EventScript_NoRoom
    giveitem ITEM_RARE_CANDY
    setflag FLAG_GOT_PRIZE_FROM_CHUCK
    release
    end

EventScript_ChuckRematch::
    msgbox ChuckRematch_Text_RematchIntro, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, EventScript_ChuckRematchDecline
    trainerbattle_no_intro TRAINER_LEADER_CHUCK_2, ChuckRematch_Text_ChoosePrize
    goto EventScript_ChuckRematchDefeated
    release
    end

EventScript_ChuckRematchDecline::
    release
    end

ChuckRematch_EventScript_GiveReward::
    lock
    faceplayer
    message ChuckRematch_Text_ChoosePrizeSimple
    multichoice 0, 0, MULTICHOICE_GYM_REWARD, FALSE
    switch VAR_RESULT
    case 0, ChuckRematch_EventScript_HeldItem
    case 1, ChuckRematch_EventScript_MoveTutorMenu
    case 2, ChuckRematch_EventScript_TMMenu
    case SCR_MENU_CANCEL, ChuckRematch_EventScript_Cancel
    end

ChuckRematch_EventScript_Cancel::
    release
    end

ChuckRematch_EventScript_HeldItem::
    checkitemspace ITEM_BLACK_BELT
    goto_if_eq VAR_RESULT, FALSE, ChuckRematch_EventScript_NoRoom
    giveitem ITEM_BLACK_BELT
    release
    end

ChuckRematch_EventScript_NoRoom::
    msgbox ChuckRematch_Text_NoRoom
    release
    end

ChuckRematch_EventScript_MoveTutorMenu::
    multichoice 0, 0, MULTICHOICE_CHUCK_TUTOR, FALSE
    goto ChuckRematch_EventScript_DoTutor

ChuckRematch_EventScript_DoTutor::
    goto_if_eq VAR_RESULT, SCR_MENU_CANCEL, ChuckRematch_EventScript_GiveReward
    goto_if_eq VAR_RESULT, 0, ChuckRematch_DoTutor_Counter
    goto_if_eq VAR_RESULT, 1, ChuckRematch_DoTutor_DynamicPunch
    goto_if_eq VAR_RESULT, 2, ChuckRematch_DoTutor_LowKick
    goto_if_eq VAR_RESULT, 3, ChuckRematch_DoTutor_Reversal
    goto_if_eq VAR_RESULT, 4, ChuckRematch_DoTutor_SeismicToss
    @ case 5 = Submission
    setvar VAR_0x8005, MOVETUTOR_SUBMISSION
    goto ChuckRematch_DoTutor_Choose
ChuckRematch_DoTutor_Counter:
    setvar VAR_0x8005, MOVETUTOR_COUNTER
    goto ChuckRematch_DoTutor_Choose
ChuckRematch_DoTutor_DynamicPunch:
    setvar VAR_0x8005, MOVETUTOR_DYNAMIC_PUNCH
    goto ChuckRematch_DoTutor_Choose
ChuckRematch_DoTutor_LowKick:
    setvar VAR_0x8005, MOVETUTOR_LOW_KICK
    goto ChuckRematch_DoTutor_Choose
ChuckRematch_DoTutor_Reversal:
    setvar VAR_0x8005, MOVETUTOR_REVERSAL
    goto ChuckRematch_DoTutor_Choose
ChuckRematch_DoTutor_SeismicToss:
    setvar VAR_0x8005, MOVETUTOR_SEISMIC_TOSS
    goto ChuckRematch_DoTutor_Choose
ChuckRematch_DoTutor_Choose:
    special ChooseMonForMoveTutor
    waitstate
    release
    end

ChuckRematch_EventScript_TMMenu::
    multichoice 0, 0, MULTICHOICE_CHUCK_TM, FALSE
    switch VAR_RESULT
    case 0, ChuckRematch_EventScript_TMHiddenPower
    case 1, ChuckRematch_EventScript_TMBrickBreak
    case 2, ChuckRematch_EventScript_TMBulkUp
    case 3, ChuckRematch_EventScript_TMFocusPunch
    case SCR_MENU_CANCEL, ChuckRematch_EventScript_GiveReward
    end

ChuckRematch_EventScript_TMHiddenPower::
    checkitemspace ITEM_TM10
    goto_if_eq VAR_RESULT, FALSE, ChuckRematch_EventScript_NoRoom
    giveitem ITEM_TM10
    release
    end

ChuckRematch_EventScript_TMBrickBreak::
    checkitemspace ITEM_TM31
    goto_if_eq VAR_RESULT, FALSE, ChuckRematch_EventScript_NoRoom
    giveitem ITEM_TM31
    release
    end

ChuckRematch_EventScript_TMBulkUp::
    checkitemspace ITEM_TM08
    goto_if_eq VAR_RESULT, FALSE, ChuckRematch_EventScript_NoRoom
    giveitem ITEM_TM08
    release
    end

ChuckRematch_EventScript_TMFocusPunch::
    checkitemspace ITEM_TM01
    goto_if_eq VAR_RESULT, FALSE, ChuckRematch_EventScript_NoRoom
    giveitem ITEM_TM01
    release
    end

EventScript_ChuckRematchDefeated::
    goto ChuckRematch_EventScript_GiveReward
    end

JasmineDuel_Text_Duel::
    .string "Duel?$"

JasmineRematch_Text_RematchIntro::
    .string "Rematch?$"

JasmineRematch_Text_ChoosePrize::
    .string "(GG) GOOD GAME.$"

JasmineRematch_Text_ChoosePrizeSimple::
    .string "Choose your prize.$"

JasmineRematch_Text_NoRoom::
    .string "You don't have room for this.$"

EventScript_Jasmine::
    lock
    faceplayer
    goto_if_set FLAG_DEFEATED_JASMINE, EventScript_JasmineRematch
    msgbox JasmineDuel_Text_Duel, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, EventScript_JasmineDecline
    trainerbattle_no_intro TRAINER_LEADER_JASMINE, JasmineRematch_Text_ChoosePrize
    setflag FLAG_DEFEATED_JASMINE
    goto_if_unset FLAG_GOT_PRIZE_FROM_JASMINE, EventScript_JasmineGivePrize
    msgbox JasmineRematch_Text_RematchIntro
    release
    end

EventScript_JasmineDecline::
    release
    end

EventScript_JasmineGivePrize::
    checkitemspace ITEM_RARE_CANDY
    goto_if_eq VAR_RESULT, FALSE, JasmineRematch_EventScript_NoRoom
    giveitem ITEM_RARE_CANDY
    setflag FLAG_GOT_PRIZE_FROM_JASMINE
    release
    end

EventScript_JasmineRematch::
    msgbox JasmineRematch_Text_RematchIntro, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, EventScript_JasmineRematchDecline
    trainerbattle_no_intro TRAINER_LEADER_JASMINE_2, JasmineRematch_Text_ChoosePrize
    goto EventScript_JasmineRematchDefeated
    release
    end

EventScript_JasmineRematchDecline::
    release
    end

JasmineRematch_EventScript_GiveReward::
    lock
    faceplayer
    message JasmineRematch_Text_ChoosePrizeSimple
    multichoice 0, 0, MULTICHOICE_GYM_REWARD, FALSE
    switch VAR_RESULT
    case 0, JasmineRematch_EventScript_HeldItem
    case 1, JasmineRematch_EventScript_MoveTutorMenu
    case 2, JasmineRematch_EventScript_TMMenu
    case SCR_MENU_CANCEL, JasmineRematch_EventScript_Cancel
    end

JasmineRematch_EventScript_Cancel::
    release
    end

JasmineRematch_EventScript_HeldItem::
    checkitemspace ITEM_METAL_COAT
    goto_if_eq VAR_RESULT, FALSE, JasmineRematch_EventScript_NoRoom
    giveitem ITEM_METAL_COAT
    release
    end

JasmineRematch_EventScript_NoRoom::
    msgbox JasmineRematch_Text_NoRoom
    release
    end

JasmineRematch_EventScript_MoveTutorMenu::
    multichoice 0, 0, MULTICHOICE_JASMINE_TUTOR, FALSE
    goto JasmineRematch_EventScript_DoTutor

JasmineRematch_EventScript_DoTutor::
    goto_if_eq VAR_RESULT, SCR_MENU_CANCEL, JasmineRematch_EventScript_GiveReward
    goto_if_eq VAR_RESULT, 0, JasmineRematch_DoTutor_MetalClaw
    @ case 1 = Metal Sound
    setvar VAR_0x8005, MOVETUTOR_METAL_SOUND
    goto JasmineRematch_DoTutor_Choose
JasmineRematch_DoTutor_MetalClaw:
    setvar VAR_0x8005, MOVETUTOR_METAL_CLAW
    goto JasmineRematch_DoTutor_Choose
JasmineRematch_DoTutor_Choose:
    special ChooseMonForMoveTutor
    waitstate
    release
    end

JasmineRematch_EventScript_TMMenu::
    multichoice 0, 0, MULTICHOICE_JASMINE_TM, FALSE
    switch VAR_RESULT
    case 0, JasmineRematch_EventScript_TMHiddenPower
    case 1, JasmineRematch_EventScript_TMIronTail
    case 2, JasmineRematch_EventScript_TMSteelWing
    case SCR_MENU_CANCEL, JasmineRematch_EventScript_GiveReward
    end

JasmineRematch_EventScript_TMHiddenPower::
    checkitemspace ITEM_TM10
    goto_if_eq VAR_RESULT, FALSE, JasmineRematch_EventScript_NoRoom
    giveitem ITEM_TM10
    release
    end

JasmineRematch_EventScript_TMIronTail::
    checkitemspace ITEM_TM23
    goto_if_eq VAR_RESULT, FALSE, JasmineRematch_EventScript_NoRoom
    giveitem ITEM_TM23
    release
    end

JasmineRematch_EventScript_TMSteelWing::
    checkitemspace ITEM_TM47
    goto_if_eq VAR_RESULT, FALSE, JasmineRematch_EventScript_NoRoom
    giveitem ITEM_TM47
    release
    end

EventScript_JasmineRematchDefeated::
    goto JasmineRematch_EventScript_GiveReward
    end

PryceDuel_Text_Duel::
    .string "Duel?$"

PryceRematch_Text_RematchIntro::
    .string "Rematch?$"

PryceRematch_Text_ChoosePrize::
    .string "(GG) GOOD GAME.$"

PryceRematch_Text_ChoosePrizeSimple::
    .string "Choose your prize.$"

PryceRematch_Text_NoRoom::
    .string "You don't have room for this.$"

EventScript_Pryce::
    lock
    faceplayer
    goto_if_set FLAG_DEFEATED_PRYCE, EventScript_PryceRematch
    msgbox PryceDuel_Text_Duel, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, EventScript_PryceDecline
    trainerbattle_no_intro TRAINER_LEADER_PRYCE, PryceRematch_Text_ChoosePrize
    setflag FLAG_DEFEATED_PRYCE
    goto_if_unset FLAG_GOT_PRIZE_FROM_PRYCE, EventScript_PryceGivePrize
    msgbox PryceRematch_Text_RematchIntro
    release
    end

EventScript_PryceDecline::
    release
    end

EventScript_PryceGivePrize::
    checkitemspace ITEM_RARE_CANDY
    goto_if_eq VAR_RESULT, FALSE, PryceRematch_EventScript_NoRoom
    giveitem ITEM_RARE_CANDY
    setflag FLAG_GOT_PRIZE_FROM_PRYCE
    release
    end

EventScript_PryceRematch::
    msgbox PryceRematch_Text_RematchIntro, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, EventScript_PryceRematchDecline
    trainerbattle_no_intro TRAINER_LEADER_PRYCE_2, PryceRematch_Text_ChoosePrize
    goto EventScript_PryceRematchDefeated
    release
    end

EventScript_PryceRematchDecline::
    release
    end

PryceRematch_EventScript_GiveReward::
    lock
    faceplayer
    message PryceRematch_Text_ChoosePrizeSimple
    multichoice 0, 0, MULTICHOICE_GYM_REWARD, FALSE
    switch VAR_RESULT
    case 0, PryceRematch_EventScript_HeldItem
    case 1, PryceRematch_EventScript_MoveTutorMenu
    case 2, PryceRematch_EventScript_TMMenu
    case SCR_MENU_CANCEL, PryceRematch_EventScript_Cancel
    end

PryceRematch_EventScript_Cancel::
    release
    end

PryceRematch_EventScript_HeldItem::
    checkitemspace ITEM_NEVER_MELT_ICE
    goto_if_eq VAR_RESULT, FALSE, PryceRematch_EventScript_NoRoom
    giveitem ITEM_NEVER_MELT_ICE
    release
    end

PryceRematch_EventScript_NoRoom::
    msgbox PryceRematch_Text_NoRoom
    release
    end

PryceRematch_EventScript_MoveTutorMenu::
    multichoice 0, 0, MULTICHOICE_PRYCE_TUTOR, FALSE
    goto PryceRematch_EventScript_DoTutor

PryceRematch_EventScript_DoTutor::
    goto_if_eq VAR_RESULT, SCR_MENU_CANCEL, PryceRematch_EventScript_GiveReward
    goto_if_eq VAR_RESULT, 0, PryceRematch_DoTutor_Haze
    goto_if_eq VAR_RESULT, 1, PryceRematch_DoTutor_IcePunch
    goto_if_eq VAR_RESULT, 2, PryceRematch_DoTutor_IcyWind
    @ case 3 = Mist
    setvar VAR_0x8005, MOVETUTOR_MIST
    goto PryceRematch_DoTutor_Choose
PryceRematch_DoTutor_Haze:
    setvar VAR_0x8005, MOVETUTOR_HAZE
    goto PryceRematch_DoTutor_Choose
PryceRematch_DoTutor_IcePunch:
    setvar VAR_0x8005, MOVETUTOR_ICE_PUNCH
    goto PryceRematch_DoTutor_Choose
PryceRematch_DoTutor_IcyWind:
    setvar VAR_0x8005, MOVETUTOR_ICY_WIND
    goto PryceRematch_DoTutor_Choose
PryceRematch_DoTutor_Choose:
    special ChooseMonForMoveTutor
    waitstate
    release
    end

PryceRematch_EventScript_TMMenu::
    multichoice 0, 0, MULTICHOICE_PRYCE_TM, FALSE
    switch VAR_RESULT
    case 0, PryceRematch_EventScript_TMHiddenPower
    case 1, PryceRematch_EventScript_TMBlizzard
    case 2, PryceRematch_EventScript_TMHail
    case 3, PryceRematch_EventScript_TMIceBeam
    case SCR_MENU_CANCEL, PryceRematch_EventScript_GiveReward
    end

PryceRematch_EventScript_TMHiddenPower::
    checkitemspace ITEM_TM10
    goto_if_eq VAR_RESULT, FALSE, PryceRematch_EventScript_NoRoom
    giveitem ITEM_TM10
    release
    end

PryceRematch_EventScript_TMBlizzard::
    checkitemspace ITEM_TM14
    goto_if_eq VAR_RESULT, FALSE, PryceRematch_EventScript_NoRoom
    giveitem ITEM_TM14
    release
    end

PryceRematch_EventScript_TMHail::
    checkitemspace ITEM_TM07
    goto_if_eq VAR_RESULT, FALSE, PryceRematch_EventScript_NoRoom
    giveitem ITEM_TM07
    release
    end

PryceRematch_EventScript_TMIceBeam::
    checkitemspace ITEM_TM13
    goto_if_eq VAR_RESULT, FALSE, PryceRematch_EventScript_NoRoom
    giveitem ITEM_TM13
    release
    end

EventScript_PryceRematchDefeated::
    goto PryceRematch_EventScript_GiveReward
    end

ClairDuel_Text_Duel::
    .string "Duel?$"

ClairRematch_Text_RematchIntro::
    .string "Rematch?$"

ClairRematch_Text_ChoosePrize::
    .string "(GG) GOOD GAME.$"

ClairRematch_Text_ChoosePrizeSimple::
    .string "Choose your prize.$"

ClairRematch_Text_NoRoom::
    .string "You don't have room for this.$"

EventScript_Clair::
    lock
    faceplayer
    goto_if_set FLAG_DEFEATED_CLAIR, EventScript_ClairRematch
    msgbox ClairDuel_Text_Duel, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, EventScript_ClairDecline
    trainerbattle_no_intro TRAINER_LEADER_CLAIR, ClairRematch_Text_ChoosePrize
    setflag FLAG_DEFEATED_CLAIR
    goto_if_unset FLAG_GOT_PRIZE_FROM_CLAIR, EventScript_ClairGivePrize
    msgbox ClairRematch_Text_RematchIntro
    release
    end

EventScript_ClairDecline::
    release
    end

EventScript_ClairGivePrize::
    checkitemspace ITEM_RARE_CANDY
    goto_if_eq VAR_RESULT, FALSE, ClairRematch_EventScript_NoRoom
    giveitem ITEM_RARE_CANDY
    setflag FLAG_GOT_PRIZE_FROM_CLAIR
    release
    end

EventScript_ClairRematch::
    msgbox ClairRematch_Text_RematchIntro, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, EventScript_ClairRematchDecline
    trainerbattle_no_intro TRAINER_LEADER_CLAIR_2, ClairRematch_Text_ChoosePrize
    goto EventScript_ClairRematchDefeated
    release
    end

EventScript_ClairRematchDecline::
    release
    end

ClairRematch_EventScript_GiveReward::
    lock
    faceplayer
    message ClairRematch_Text_ChoosePrizeSimple
    multichoice 0, 0, MULTICHOICE_GYM_REWARD, FALSE
    switch VAR_RESULT
    case 0, ClairRematch_EventScript_HeldItem
    case 1, ClairRematch_EventScript_MoveTutorMenu
    case 2, ClairRematch_EventScript_TMMenu
    case SCR_MENU_CANCEL, ClairRematch_EventScript_Cancel
    end

ClairRematch_EventScript_Cancel::
    release
    end

ClairRematch_EventScript_HeldItem::
    checkitemspace ITEM_DRAGON_FANG
    goto_if_eq VAR_RESULT, FALSE, ClairRematch_EventScript_NoRoom
    giveitem ITEM_DRAGON_FANG
    release
    end

ClairRematch_EventScript_NoRoom::
    msgbox ClairRematch_Text_NoRoom
    release
    end

ClairRematch_EventScript_MoveTutorMenu::
    multichoice 0, 0, MULTICHOICE_CLAIR_TUTOR, FALSE
    goto ClairRematch_EventScript_DoTutor

ClairRematch_EventScript_DoTutor::
    goto_if_eq VAR_RESULT, SCR_MENU_CANCEL, ClairRematch_EventScript_GiveReward
    goto_if_eq VAR_RESULT, 0, ClairRematch_DoTutor_DragonRage
    @ case 1 = Twister
    setvar VAR_0x8005, MOVETUTOR_TWISTER
    goto ClairRematch_DoTutor_Choose
ClairRematch_DoTutor_DragonRage:
    setvar VAR_0x8005, MOVETUTOR_DRAGON_RAGE
    goto ClairRematch_DoTutor_Choose
ClairRematch_DoTutor_Choose:
    special ChooseMonForMoveTutor
    waitstate
    release
    end

ClairRematch_EventScript_TMMenu::
    multichoice 0, 0, MULTICHOICE_CLAIR_TM, FALSE
    switch VAR_RESULT
    case 0, ClairRematch_EventScript_TMHiddenPower
    case 1, ClairRematch_EventScript_TMDragonClaw
    case SCR_MENU_CANCEL, ClairRematch_EventScript_GiveReward
    end

ClairRematch_EventScript_TMHiddenPower::
    checkitemspace ITEM_TM10
    goto_if_eq VAR_RESULT, FALSE, ClairRematch_EventScript_NoRoom
    giveitem ITEM_TM10
    release
    end

ClairRematch_EventScript_TMDragonClaw::
    checkitemspace ITEM_TM02
    goto_if_eq VAR_RESULT, FALSE, ClairRematch_EventScript_NoRoom
    giveitem ITEM_TM02
    release
    end

EventScript_ClairRematchDefeated::
    goto ClairRematch_EventScript_GiveReward
    end
