#include "global.h"
#include "gflib.h"
#include "menu.h"
#include "task.h"
#include "script_menu.h"
#include "quest_log.h"
#include "new_menu_helpers.h"
#include "event_data.h"
#include "script.h"
#include "strings.h"
#include "field_effect.h"
#include "event_scripts.h"
#include "constants/songs.h"
#include "constants/seagallop.h"
#include "constants/menu.h"

#define GFXTAG_FOSSIL 7000

#define MULTICHOICE(name) {.list = name, .count = ARRAY_COUNT(name)}
#define SCROLLING_MULTICHOICE_THRESHOLD  6
#define SCROLLING_MULTICHOICE_MAX_VISIBLE 6
#define SCROLLING_MULTICHOICE_ARROW_PADDING 2

struct MultichoiceListStruct
{
    const struct MenuAction * list;
    u8 count;
};

static EWRAM_DATA u8 sDelay = 0;

static void DrawVerticalMultichoiceMenu(u8 left, u8 top, u8 mcId, u8 ignoreBpress, u8 initPos);
static u8 GetMCWindowHeight(u8 count);
static void CreateMCMenuInputHandlerTask(u8 ignoreBpress, u8 count, u8 windowId, u8 mcId);
static void Task_MultichoiceMenu_HandleInput(u8 taskId);
static void DrawScrollingMultichoiceMenu(u8 left, u8 top, u8 mcId, u8 ignoreBpress, u8 count, const struct MenuAction *list, u8 width);
static void Task_ScrollingMultichoiceMenu_HandleInput(u8 taskId);
static void MultiChoicePrintHelpDescription(u8 mcId);
static void Task_YesNoMenu_HandleInput(u8 taskId);
static void Hask_MultichoiceGridMenu_HandleInput(u8 taskId);
static void CreatePCMenuWindow(void);
static bool8 PicboxWait(void);
static void DestroyScriptMenuWindow(u8 windowId);
static u8 CreateWindowFromRect(u8 left, u8 top, u8 width, u8 height);


static const struct MenuAction sMultichoiceList_YesNo[] = {
    { gText_Yes },
    { gText_No }
};

static const struct MenuAction sMultichoiceList_TrainerCardIconTint[] = {
    { gText_Normal },
    { gText_Black },
    { gText_Pink },
    { gText_Sepia }
};

static const struct MenuAction sMultichoiceList_HOF_Quit[] = {
    { gText_HallOfFame },
    { gText_Quit }
};

static const struct MenuAction sMultichoiceList_Eggs_Quit[] = {
    { gText_Eggs },
    { gText_Quit }
};

static const struct MenuAction sMultichoiceList_Victories_Quit[] = {
    { gText_Victories },
    { gText_Quit }
};

static const struct MenuAction sMultichoiceList_HOF_Eggs_Quit[] = {
    { gText_HallOfFame },
    { gText_Eggs },
    { gText_Quit }
};

static const struct MenuAction sMultichoiceList_HOF_Victories_Quit[] = {
    { gText_HallOfFame },
    { gText_Victories },
    { gText_Quit }
};

static const struct MenuAction sMultichoiceList_Eggs_Victories_Quit[] = {
    { gText_Eggs },
    { gText_Victories },
    { gText_Quit }
};

static const struct MenuAction sMultichoiceList_HOF_Eggs_Victories_Quit[] = {
    { gText_HallOfFame },
    { gText_Eggs },
    { gText_Victories },
    { gText_Quit }
};

static const struct MenuAction sMultichoiceList_TrainerSchoolWhiteboard[] = {
    { gText_Slp },
    { gText_Psn },
    { gText_Par },
    { gText_Brn },
    { gText_Frz },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_YesNoInfo[] = {
    { gText_Yes },
    { gText_No },
    { gText_Info }
};

static const struct MenuAction sMultichoiceList_SingleDoubleMultiInfoExit[] = {
    { gText_SingleBattle },
    { gText_DoubleBattle },
    { gText_MultiBattle },
    { gText_Info },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_YesNoInfo2[] = {
    { gText_Yes },
    { gText_No },
    { gText_Info }
};

static const struct MenuAction sMultichoiceList_ChallengeInfoExit[] = {
    { gText_MakeAChallenge },
    { gText_Info_2 },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_RooftopB1F[] = {
    { gText_Rooftop },
    { gText_B1F },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_Helix[] = {
    { gText_HelixFossil },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_Dome[] = {
    { gText_DomeFossil },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_Amber[] = {
    { gText_OldAmber },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_HelixAmber[] = {
    { gText_HelixFossil },
    { gText_OldAmber },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_DomeAmber[] = {
    { gText_DomeFossil },
    { gText_OldAmber },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_CeladonVendingMachine[] = {
    { gText_FreshWater_200 },
    { gText_SodaPop_300 },
    { gText_Lemonade_350 },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_GameCornerTMPrizes[] = {
    { gText_Tm13_4000Coins },
    { gText_Tm23_3500Coins },
    { gText_Tm24_4000Coins },
    { gText_Tm30_4500Coins },
    { gText_Tm35_4000Coins },
    { gText_NoThanks_2 }
};

static const struct MenuAction sMultichoiceList_GameCornerBattleItemPrizes[] = {
    { gText_SmokeBall_800Coins },
    { gText_MiracleSeed_1000Coins },
    { gText_Charcoal_1000Coins },
    { gText_MysticWater_1000Coins },
    { gText_YellowFlute_1600Coins },
    { gText_NoThanks_2 }
};

static const struct MenuAction sMultichoiceList_GameCornerCoinPurchaseCounter[] = {
    { gText_50Coins_1000 },
    { gText_500Coins_10000 },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_Excellent_NotSoBad[] = {
    { gText_Excellent },
    { gText_NotSoBad }
};

static const struct MenuAction sMultichoiceList_RightLeft[] = {
    { gText_Right },
    { gText_Left }
};

static const struct MenuAction sMultichoiceList_DeptStoreElevator[] = {
    { gText_5F_2 },
    { gText_4F_2 },
    { gText_3F_2 },
    { gText_2F_2 },
    { gText_1F_2 },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_ThirstyGirlFreshWater[] = {
    { gText_FreshWater },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_ThirstyGirlSodaPop[] = {
    { gText_SodaPop },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_ThirstyGirlFreshWaterSodaPop[] = {
    { gText_FreshWater },
    { gText_SodaPop },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_ThirstyGirlLemonade[] = {
    { gText_Lemonade },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_ThirstyGirlFreshWaterLemonade[] = {
    { gText_FreshWater },
    { gText_Lemonade },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_ThirstyGirlSodaPopLemonade[] = {
    { gText_SodaPop },
    { gText_Lemonade },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_ThirstyGirlFreshWaterSodaPopLemonade[] = {
    { gText_FreshWater },
    { gText_SodaPop },
    { gText_Lemonade },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_Unref_Shards_0[] = {
    { gText_GreenShard },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_Unref_Shards_1[] = {
    { gText_RedShard },
    { gText_GreenShard },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_Unref_Shards_2[] = {
    { gText_YellowShard },
    { gText_GreenShard },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_Unref_Shards_3[] = {
    { gText_RedShard },
    { gText_YellowShard },
    { gText_GreenShard },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_Unref_Shards_4[] = {
    { gText_BlueShard },
    { gText_GreenShard },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_Unref_Shards_5[] = {
    { gText_RedShard },
    { gText_BlueShard },
    { gText_GreenShard },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_Unref_Shards_6[] = {
    { gText_YellowShard },
    { gText_BlueShard },
    { gText_GreenShard },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_Unref_Shards_7[] = {
    { gText_RedShard },
    { gText_YellowShard },
    { gText_BlueShard },
    { gText_GreenShard },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_Eeveelutions[] = {
    { gText_Eevee },
    { gText_Flareon },
    { gText_Jolteon },
    { gText_Vaporeon },
    { gText_QuitLooking }
};

static const struct MenuAction sMultichoiceList_BikeShop[] = {
    { gText_Bicycle_Price },
    { gText_NoThanks }
};

static const struct MenuAction sMultichoiceList_GameCornerPokemonPrizes[] = {
#if defined(FIRERED)
    { gText_Abra_180Coins },
    { gText_Clefairy_500Coins },
    { gText_Dratini_2800Coins },
    { gText_Scyther_5500Coins },
    { gText_Porygon_9999Coins },
#elif defined(LEAFGREEN)
    { gText_Abra_120Coins },
    { gText_Clefairy_750Coins },
    { gText_Pinsir_2500Coins },
    { gText_Dratini_4600Coins },
    { gText_Porygon_6500Coins },
#endif
    { gText_NoThanks_2 }
};

static const struct MenuAction sMultichoiceList_TradeCenter_Colosseum[] = {
    { gText_TradeCenter },
    { gText_Colosseum },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_Link_Wireless[] = {
    { gText_GameLinkCable },
    { gText_Wireless },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_RocketHideoutElevator[] = {
    { gText_B1F },
    { gText_B2F },
    { gText_B4F },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_LinkedDirectUnion[] = {
    { gText_LinkedGamePlay },
    { gText_DirectCorner },
    { gText_UnionRoom },
    { gOtherText_Quit }
};

static const struct MenuAction sMultichoiceList_Island23[] = {
    { gText_TwoIsland },
    { gText_ThreeIsland },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_Island13[] = {
    { gText_OneIsland },
    { gText_ThreeIsland },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_Island12[] = {
    { gText_OneIsland },
    { gText_TwoIsland },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_TradeColosseumCrush[] = {
    { gText_TradeCenter },
    { gText_Colosseum_2 },
    { gText_BerryCrush },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_48[] = {
    { gText_EmptyLinkService1 },
    { gText_EmptyLinkService2 },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_TradeColosseum_2[] = {
    { gText_TradeCenter },
    { gText_Colosseum_2 },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_PokejumpDodrio[] = {
    { gText_PokemonJump },
    { gText_DodrioBerryPicking },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_Mushrooms[] = {
    { gText_2Tinymushrooms },
    { gText_1BigMushroom }
};

static const struct MenuAction sMultichoiceList_TradeColosseumBlankCrush[] = {
    { gText_TradeCenter },
    { gText_Colosseum_2 },
    { gText_RecordCorner },
    { gText_BerryCrush },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_TradeColosseumBlank[] = {
    { gText_TradeCenter },
    { gText_Colosseum_2 },
    { gText_RecordCorner },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_SeviiNavel[] = {
    { gText_SeviiIslands },
    { gText_NavelRock },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_SeviiBirth[] = {
    { gText_SeviiIslands },
    { gText_BirthIsland },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_SeviiNavelBirth[] = {
    { gText_SeviiIslands },
    { gText_NavelRock },
    { gText_BirthIsland },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_Seagallop123[] = {
    { gText_OneIsland },
    { gText_TwoIsland },
    { gText_ThreeIsland },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_SeagallopV23[] = {
    { gText_Vermilion },
    { gText_TwoIsland },
    { gText_ThreeIsland },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_SeagallopV13[] = {
    { gText_Vermilion },
    { gText_OneIsland },
    { gText_ThreeIsland },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_SeagallopV12[] = {
    { gText_Vermilion },
    { gText_OneIsland },
    { gText_TwoIsland },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_SeagallopVermilion[] = {
    { gText_Vermilion },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_62[] = {
    { gText_Multichoice_Empty1 },
    { gText_Multichoice_Empty2 },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_JoinOrLead[] = {
    { gText_JoinGroup },
    { gText_BecomeLeader },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_TrainerTowerMode[] = {
    { gOtherText_Single },
    { gOtherText_Double },
    { gOtherText_Knockout },
    { gOtherText_Mixed },
    { gOtherText_Exit }
};

static const struct MenuAction sMultichoiceList_Exit[] = {
    { gOtherText_Exit }
};

// Gym Rematch rewards
static const u8 sText_GymReward_HeldItem[] = _("HELD ITEM");
static const u8 sText_GymReward_MoveTutor[] = _("MOVE TUTOR");
static const u8 sText_GymReward_TM[] = _("TM");

static const struct MenuAction sMultichoiceList_GymReward[] = {
    { sText_GymReward_HeldItem },
    { sText_GymReward_MoveTutor },
    { sText_GymReward_TM }
};

static const u8 sText_BrockTutor_AncientPower[] = _("ANCIENT POWER");
static const u8 sText_BrockTutor_RockSlide[] = _("ROCK SLIDE");
static const u8 sText_BrockTutor_RockThrow[] = _("ROCK THROW");
static const u8 sText_BrockTutor_Rollout[] = _("ROLLOUT");

static const struct MenuAction sMultichoiceList_BrockTutor[] = {
    { sText_BrockTutor_AncientPower },
    { sText_BrockTutor_RockSlide },
    { sText_BrockTutor_RockThrow },
    { sText_BrockTutor_Rollout }
};

static const u8 sText_TM_HiddenPower[] = _("HIDDEN POWER");

static const u8 sText_BrockTM_Sandstorm[] = _("SANDSTORM");
static const u8 sText_BrockTM_RockTomb[] = _("ROCK TOMB");

static const struct MenuAction sMultichoiceList_BrockTM[] = {
    { sText_TM_HiddenPower },
    { sText_BrockTM_Sandstorm },
    { sText_BrockTM_RockTomb }
};

static const u8 sText_MistyTutor_Bubble[] = _("BUBBLE");
static const u8 sText_MistyTutor_HydroCannon[] = _("HYDRO CANNON");
static const u8 sText_MistyTutor_HydroPump[] = _("HYDRO PUMP");

static const struct MenuAction sMultichoiceList_MistyTutor[] = {
    { sText_MistyTutor_Bubble },
    { sText_MistyTutor_HydroCannon },
    { sText_MistyTutor_HydroPump }
};

static const u8 sText_MistyTM_RainDance[] = _("RAIN DANCE");
static const u8 sText_MistyTM_WaterPulse[] = _("WATER PULSE");

static const struct MenuAction sMultichoiceList_MistyTM[] = {
    { sText_TM_HiddenPower },
    { sText_MistyTM_RainDance },
    { sText_MistyTM_WaterPulse }
};

static const u8 sText_SurgeTutor_ThunderPunch[] = _("THUNDER PUNCH");
static const u8 sText_SurgeTutor_ThunderWave[] = _("THUNDER WAVE");
static const u8 sText_SurgeTutor_ZapCannon[] = _("ZAP CANNON");

static const struct MenuAction sMultichoiceList_SurgeTutor[] = {
    { sText_SurgeTutor_ThunderPunch },
    { sText_SurgeTutor_ThunderWave },
    { sText_SurgeTutor_ZapCannon }
};

static const u8 sText_SurgeTM_ShockWave[] = _("SHOCK WAVE");
static const u8 sText_SurgeTM_Thunder[] = _("THUNDER");
static const u8 sText_SurgeTM_Thunderbolt[] = _("THUNDERBOLT");

static const struct MenuAction sMultichoiceList_SurgeTM[] = {
    { sText_TM_HiddenPower },
    { sText_SurgeTM_ShockWave },
    { sText_SurgeTM_Thunder },
    { sText_SurgeTM_Thunderbolt }
};

static const u8 sText_ErikaTutor_Absorb[] = _("ABSORB");
static const u8 sText_ErikaTutor_FrenzyPlant[] = _("FRENZY PLANT");
static const u8 sText_ErikaTutor_LeechSeed[] = _("LEECH SEED");
static const u8 sText_ErikaTutor_PetalDance[] = _("PETAL DANCE");
static const u8 sText_ErikaTutor_Synthesis[] = _("SYNTHESIS");

static const struct MenuAction sMultichoiceList_ErikaTutor[] = {
    { sText_ErikaTutor_Absorb },
    { sText_ErikaTutor_FrenzyPlant },
    { sText_ErikaTutor_LeechSeed },
    { sText_ErikaTutor_PetalDance },
    { sText_ErikaTutor_Synthesis }
};

static const u8 sText_ErikaTM_BulletSeed[] = _("BULLET SEED");
static const u8 sText_ErikaTM_GigaDrain[] = _("GIGA DRAIN");
static const u8 sText_ErikaTM_SolarBeam[] = _("SOLAR BEAM");

static const struct MenuAction sMultichoiceList_ErikaTM[] = {
    { sText_TM_HiddenPower },
    { sText_ErikaTM_BulletSeed },
    { sText_ErikaTM_GigaDrain },
    { sText_ErikaTM_SolarBeam }
};

static const u8 sText_KogaTutor_PoisonTail[] = _("POISON TAIL");

static const struct MenuAction sMultichoiceList_KogaTutor[] = {
    { sText_KogaTutor_PoisonTail }
};

static const u8 sText_KogaTM_SludgeBomb[] = _("SLUDGE BOMB");
static const u8 sText_KogaTM_Toxic[] = _("TOXIC");

static const struct MenuAction sMultichoiceList_KogaTM[] = {
    { sText_TM_HiddenPower },
    { sText_KogaTM_SludgeBomb },
    { sText_KogaTM_Toxic }
};

static const u8 sText_SabrinaTutor_Agility[] = _("AGILITY");
static const u8 sText_SabrinaTutor_Amnesia[] = _("AMNESIA");
static const u8 sText_SabrinaTutor_Barrier[] = _("BARRIER");
static const u8 sText_SabrinaTutor_DreamEater[] = _("DREAM EATER");
static const u8 sText_SabrinaTutor_Extrasensory[] = _("EXTRASENSORY");
static const u8 sText_SabrinaTutor_FutureSight[] = _("FUTURE SIGHT");
static const u8 sText_SabrinaTutor_Hypnosis[] = _("HYPNOSIS");
static const u8 sText_SabrinaTutor_LightScreen[] = _("LIGHT SCREEN");
static const u8 sText_SabrinaTutor_PsychoBoost[] = _("PSYCHO BOOST");
static const u8 sText_SabrinaTutor_RolePlay[] = _("ROLE PLAY");

static const struct MenuAction sMultichoiceList_SabrinaTutor[] = {
    { sText_SabrinaTutor_Agility },
    { sText_SabrinaTutor_Amnesia },
    { sText_SabrinaTutor_Barrier },
    { sText_SabrinaTutor_DreamEater },
    { sText_SabrinaTutor_Extrasensory },
    { sText_SabrinaTutor_FutureSight },
    { sText_SabrinaTutor_Hypnosis },
    { sText_SabrinaTutor_LightScreen },
    { sText_SabrinaTutor_PsychoBoost },
    { sText_SabrinaTutor_RolePlay }
};

static const u8 sText_SabrinaTM_CalmMind[] = _("CALM MIND");
static const u8 sText_SabrinaTM_LightScreen[] = _("LIGHT SCREEN");
static const u8 sText_SabrinaTM_Psychic[] = _("PSYCHIC");
static const u8 sText_SabrinaTM_Reflect[] = _("REFLECT");
static const u8 sText_SabrinaTM_Rest[] = _("REST");
static const u8 sText_SabrinaTM_SkillSwap[] = _("SKILL SWAP");

static const struct MenuAction sMultichoiceList_SabrinaTM[] = {
    { sText_TM_HiddenPower },
    { sText_SabrinaTM_CalmMind },
    { sText_SabrinaTM_LightScreen },
    { sText_SabrinaTM_Psychic },
    { sText_SabrinaTM_Reflect },
    { sText_SabrinaTM_Rest },
    { sText_SabrinaTM_SkillSwap }
};

static const u8 sText_BlaineTutor_BlastBurn[] = _("BLAST BURN");
static const u8 sText_BlaineTutor_FirePunch[] = _("FIRE PUNCH");
static const u8 sText_BlaineTutor_WillOWisp[] = _("WILL-O-WISP");

static const struct MenuAction sMultichoiceList_BlaineTutor[] = {
    { sText_BlaineTutor_BlastBurn },
    { sText_BlaineTutor_FirePunch },
    { sText_BlaineTutor_WillOWisp }
};

static const u8 sText_BlaineTM_FireBlast[] = _("FIRE BLAST");
static const u8 sText_BlaineTM_Flamethrower[] = _("FLAMETHROWER");
static const u8 sText_BlaineTM_Overheat[] = _("OVERHEAT");
static const u8 sText_BlaineTM_SunnyDay[] = _("SUNNY DAY");

static const struct MenuAction sMultichoiceList_BlaineTM[] = {
    { sText_TM_HiddenPower },
    { sText_BlaineTM_FireBlast },
    { sText_BlaineTM_Flamethrower },
    { sText_BlaineTM_Overheat },
    { sText_BlaineTM_SunnyDay }
};

static const u8 sText_GiovanniTutor_MudSlap[] = _("MUD-SLAP");
static const u8 sText_GiovanniTutor_MudSport[] = _("MUD SPORT");
static const u8 sText_GiovanniTutor_Spikes[] = _("SPIKES");

static const struct MenuAction sMultichoiceList_GiovanniTutor[] = {
    { sText_GiovanniTutor_MudSlap },
    { sText_GiovanniTutor_MudSport },
    { sText_GiovanniTutor_Spikes }
};

static const u8 sText_GiovanniTM_Dig[] = _("DIG");
static const u8 sText_GiovanniTM_Earthquake[] = _("EARTHQUAKE");

static const struct MenuAction sMultichoiceList_GiovanniTM[] = {
    { sText_GiovanniTM_Dig },
    { sText_GiovanniTM_Earthquake }
};

static const u8 sText_FalknerTutor_FeatherDance[] = _("FEATHER DANCE");
static const u8 sText_FalknerTutor_Gust[] = _("GUST");
static const u8 sText_FalknerTutor_SkyAttack[] = _("SKY ATTACK");

static const struct MenuAction sMultichoiceList_FalknerTutor[] = {
    { sText_FalknerTutor_FeatherDance },
    { sText_FalknerTutor_Gust },
    { sText_FalknerTutor_SkyAttack }
};

static const u8 sText_FalknerTM_AerialAce[] = _("AERIAL ACE");

static const struct MenuAction sMultichoiceList_FalknerTM[] = {
    { sText_TM_HiddenPower },
    { sText_FalknerTM_AerialAce }
};

static const u8 sText_BugsyTutor_FuryCutter[] = _("FURY CUTTER");

static const struct MenuAction sMultichoiceList_BugsyTutor[] = {
    { sText_BugsyTutor_FuryCutter }
};

static const struct MenuAction sMultichoiceList_BugsyTM[] = {
    { sText_TM_HiddenPower }
};

static const u8 sText_WhitneyTutor_BatonPass[] = _("BATON PASS");
static const u8 sText_WhitneyTutor_BellyDrum[] = _("BELLY DRUM");
static const u8 sText_WhitneyTutor_BodySlam[] = _("BODY SLAM");
static const u8 sText_WhitneyTutor_Charm[] = _("CHARM");
static const u8 sText_WhitneyTutor_DefenseCurl[] = _("DEFENSE CURL");
static const u8 sText_WhitneyTutor_DizzyPunch[] = _("DIZZY PUNCH");
static const u8 sText_WhitneyTutor_DoubleEdge[] = _("DOUBLE-EDGE");
static const u8 sText_WhitneyTutor_DoubleSlap[] = _("DOUBLESLAP");
static const u8 sText_WhitneyTutor_Encore[] = _("ENCORE");
static const u8 sText_WhitneyTutor_Endure[] = _("ENDURE");
static const u8 sText_WhitneyTutor_Explosion[] = _("EXPLOSION");
static const u8 sText_WhitneyTutor_ExtremeSpeed[] = _("EXTREMESPEED");
static const u8 sText_WhitneyTutor_FalseSwipe[] = _("FALSE SWIPE");
static const u8 sText_WhitneyTutor_Flail[] = _("FLAIL");
static const u8 sText_WhitneyTutor_FollowMe[] = _("FOLLOW ME");
static const u8 sText_WhitneyTutor_Foresight[] = _("FORESIGHT");
static const u8 sText_WhitneyTutor_FuryAttack[] = _("FURY ATTACK");
static const u8 sText_WhitneyTutor_Growth[] = _("GROWTH");
static const u8 sText_WhitneyTutor_HealBell[] = _("HEAL BELL");
static const u8 sText_WhitneyTutor_HelpingHand[] = _("HELPING HAND");
static const u8 sText_WhitneyTutor_HornDrill[] = _("HORN DRILL");
static const u8 sText_WhitneyTutor_LovelyKiss[] = _("LOVELY KISS");
static const u8 sText_WhitneyTutor_MegaKick[] = _("MEGA KICK");
static const u8 sText_WhitneyTutor_MegaPunch[] = _("MEGA PUNCH");
static const u8 sText_WhitneyTutor_Metronome[] = _("METRONOME");
static const u8 sText_WhitneyTutor_Mimic[] = _("MIMIC");
static const u8 sText_WhitneyTutor_MindReader[] = _("MIND READER");
static const u8 sText_WhitneyTutor_Moonlight[] = _("MOONLIGHT");
static const u8 sText_WhitneyTutor_MorningSun[] = _("MORNING SUN");
static const u8 sText_WhitneyTutor_PayDay[] = _("PAY DAY");
static const u8 sText_WhitneyTutor_PsychUp[] = _("PSYCH UP");
static const u8 sText_WhitneyTutor_QuickAttack[] = _("QUICK ATTACK");
static const u8 sText_WhitneyTutor_Rage[] = _("RAGE");
static const u8 sText_WhitneyTutor_RapidSpin[] = _("RAPID SPIN");
static const u8 sText_WhitneyTutor_Refresh[] = _("REFRESH");
static const u8 sText_WhitneyTutor_Safeguard[] = _("SAFEGUARD");
static const u8 sText_WhitneyTutor_ScaryFace[] = _("SCARY FACE");
static const u8 sText_WhitneyTutor_SelfDestruct[] = _("SELFDESTRUCT");
static const u8 sText_WhitneyTutor_Sharpen[] = _("SHARPEN");
static const u8 sText_WhitneyTutor_Sing[] = _("SING");
static const u8 sText_WhitneyTutor_SleepTalk[] = _("SLEEP TALK");
static const u8 sText_WhitneyTutor_Snore[] = _("SNORE");
static const u8 sText_WhitneyTutor_SoftBoiled[] = _("SOFTBOILED");
static const u8 sText_WhitneyTutor_SonicBoom[] = _("SONICBOOM");
static const u8 sText_WhitneyTutor_Splash[] = _("SPLASH");
static const u8 sText_WhitneyTutor_Substitute[] = _("SUBSTITUTE");
static const u8 sText_WhitneyTutor_Swagger[] = _("SWAGGER");
static const u8 sText_WhitneyTutor_SweetKiss[] = _("SWEET KISS");
static const u8 sText_WhitneyTutor_SweetScent[] = _("SWEET SCENT");
static const u8 sText_WhitneyTutor_Swift[] = _("SWIFT");
static const u8 sText_WhitneyTutor_SwordsDance[] = _("SWORDS DANCE");
static const u8 sText_WhitneyTutor_TeeterDance[] = _("TEETER DANCE");
static const u8 sText_WhitneyTutor_Thrash[] = _("THRASH");
static const u8 sText_WhitneyTutor_Tickle[] = _("TICKLE");
static const u8 sText_WhitneyTutor_TriAttack[] = _("TRI ATTACK");
static const u8 sText_WhitneyTutor_Whirlwind[] = _("WHIRLWIND");
static const u8 sText_WhitneyTutor_Wish[] = _("WISH");
static const u8 sText_WhitneyTutor_Yawn[] = _("YAWN");

static const struct MenuAction sMultichoiceList_WhitneyTutor[] = {
    { sText_WhitneyTutor_BatonPass },
    { sText_WhitneyTutor_BellyDrum },
    { sText_WhitneyTutor_BodySlam },
    { sText_WhitneyTutor_Charm },
    { sText_WhitneyTutor_DefenseCurl },
    { sText_WhitneyTutor_DizzyPunch },
    { sText_WhitneyTutor_DoubleEdge },
    { sText_WhitneyTutor_DoubleSlap },
    { sText_WhitneyTutor_Encore },
    { sText_WhitneyTutor_Endure },
    { sText_WhitneyTutor_Explosion },
    { sText_WhitneyTutor_ExtremeSpeed },
    { sText_WhitneyTutor_FalseSwipe },
    { sText_WhitneyTutor_Flail },
    { sText_WhitneyTutor_FollowMe },
    { sText_WhitneyTutor_Foresight },
    { sText_WhitneyTutor_FuryAttack },
    { sText_WhitneyTutor_Growth },
    { sText_WhitneyTutor_HealBell },
    { sText_WhitneyTutor_HelpingHand },
    { sText_WhitneyTutor_HornDrill },
    { sText_WhitneyTutor_LovelyKiss },
    { sText_WhitneyTutor_MegaKick },
    { sText_WhitneyTutor_MegaPunch },
    { sText_WhitneyTutor_Metronome },
    { sText_WhitneyTutor_Mimic },
    { sText_WhitneyTutor_MindReader },
    { sText_WhitneyTutor_Moonlight },
    { sText_WhitneyTutor_MorningSun },
    { sText_WhitneyTutor_PayDay },
    { sText_WhitneyTutor_PsychUp },
    { sText_WhitneyTutor_QuickAttack },
    { sText_WhitneyTutor_Rage },
    { sText_WhitneyTutor_RapidSpin },
    { sText_WhitneyTutor_Refresh },
    { sText_WhitneyTutor_Safeguard },
    { sText_WhitneyTutor_ScaryFace },
    { sText_WhitneyTutor_SelfDestruct },
    { sText_WhitneyTutor_Sharpen },
    { sText_WhitneyTutor_Sing },
    { sText_WhitneyTutor_SleepTalk },
    { sText_WhitneyTutor_Snore },
    { sText_WhitneyTutor_SoftBoiled },
    { sText_WhitneyTutor_SonicBoom },
    { sText_WhitneyTutor_Splash },
    { sText_WhitneyTutor_Substitute },
    { sText_WhitneyTutor_Swagger },
    { sText_WhitneyTutor_SweetKiss },
    { sText_WhitneyTutor_SweetScent },
    { sText_WhitneyTutor_Swift },
    { sText_WhitneyTutor_SwordsDance },
    { sText_WhitneyTutor_TeeterDance },
    { sText_WhitneyTutor_Thrash },
    { sText_WhitneyTutor_Tickle },
    { sText_WhitneyTutor_TriAttack },
    { sText_WhitneyTutor_Whirlwind },
    { sText_WhitneyTutor_Wish },
    { sText_WhitneyTutor_Yawn }
};

static const u8 sText_WhitneyTM_Attract[] = _("ATTRACT");
static const u8 sText_WhitneyTM_DoubleTeam[] = _("DOUBLE TEAM");
static const u8 sText_WhitneyTM_Facade[] = _("FACADE");
static const u8 sText_WhitneyTM_Frustration[] = _("FRUSTRATION");
static const u8 sText_WhitneyTM_HyperBeam[] = _("HYPER BEAM");
static const u8 sText_WhitneyTM_Protect[] = _("PROTECT");
static const u8 sText_WhitneyTM_Return[] = _("RETURN");
static const u8 sText_WhitneyTM_Roar[] = _("ROAR");
static const u8 sText_WhitneyTM_Safeguard[] = _("SAFEGUARD");
static const u8 sText_WhitneyTM_SecretPower[] = _("SECRET POWER");

static const struct MenuAction sMultichoiceList_WhitneyTM[] = {
    { sText_WhitneyTM_Attract },
    { sText_WhitneyTM_DoubleTeam },
    { sText_WhitneyTM_Facade },
    { sText_WhitneyTM_Frustration },
    { sText_WhitneyTM_HyperBeam },
    { sText_WhitneyTM_Protect },
    { sText_WhitneyTM_Return },
    { sText_WhitneyTM_Roar },
    { sText_WhitneyTM_Safeguard },
    { sText_WhitneyTM_SecretPower }
};

static const u8 sText_MortyTutor_ConfuseRay[] = _("CONFUSE RAY");
static const u8 sText_MortyTutor_Nightmare[] = _("NIGHTMARE");
static const u8 sText_MortyTutor_NightShade[] = _("NIGHT SHADE");
static const u8 sText_MortyTutor_BeatUp[] = _("BEAT UP");
static const u8 sText_MortyTutor_Bite[] = _("BITE");
static const u8 sText_MortyTutor_Crunch[] = _("CRUNCH");
static const u8 sText_MortyTutor_FaintAttack[] = _("FAINT ATTACK");
static const u8 sText_MortyTutor_Pursuit[] = _("PURSUIT");

static const struct MenuAction sMultichoiceList_MortyTutor[] = {
    { sText_MortyTutor_ConfuseRay },
    { sText_MortyTutor_Nightmare },
    { sText_MortyTutor_NightShade },
    { sText_MortyTutor_BeatUp },
    { sText_MortyTutor_Bite },
    { sText_MortyTutor_Crunch },
    { sText_MortyTutor_FaintAttack },
    { sText_MortyTutor_Pursuit }
};

static const u8 sText_MortyTM_ShadowBall[] = _("SHADOW BALL");
static const u8 sText_MortyTM_Snatch[] = _("SNATCH");
static const u8 sText_MortyTM_Taunt[] = _("TAUNT");
static const u8 sText_MortyTM_Thief[] = _("THIEF");
static const u8 sText_MortyTM_Torment[] = _("TORMENT");

static const struct MenuAction sMultichoiceList_MortyTM[] = {
    { sText_TM_HiddenPower },
    { sText_MortyTM_ShadowBall },
    { sText_MortyTM_Snatch },
    { sText_MortyTM_Taunt },
    { sText_MortyTM_Thief },
    { sText_MortyTM_Torment }
};

static const u8 sText_MortyHeld_SpellTag[] = _("SPELL TAG");
static const u8 sText_MortyHeld_BlackGlasses[] = _("BLACKGLASSES");

static const struct MenuAction sMultichoiceList_MortyHeld[] = {
    { sText_MortyHeld_SpellTag },
    { sText_MortyHeld_BlackGlasses }
};

static const u8 sText_ChuckTutor_Counter[] = _("COUNTER");
static const u8 sText_ChuckTutor_DynamicPunch[] = _("DYNAMICPUNCH");
static const u8 sText_ChuckTutor_LowKick[] = _("LOW KICK");
static const u8 sText_ChuckTutor_Reversal[] = _("REVERSAL");
static const u8 sText_ChuckTutor_SeismicToss[] = _("SEISMIC TOSS");
static const u8 sText_ChuckTutor_Submission[] = _("SUBMISSION");

static const struct MenuAction sMultichoiceList_ChuckTutor[] = {
    { sText_ChuckTutor_Counter },
    { sText_ChuckTutor_DynamicPunch },
    { sText_ChuckTutor_LowKick },
    { sText_ChuckTutor_Reversal },
    { sText_ChuckTutor_SeismicToss },
    { sText_ChuckTutor_Submission }
};

static const u8 sText_ChuckTM_BrickBreak[] = _("BRICK BREAK");
static const u8 sText_ChuckTM_BulkUp[] = _("BULK UP");
static const u8 sText_ChuckTM_FocusPunch[] = _("FOCUS PUNCH");

static const struct MenuAction sMultichoiceList_ChuckTM[] = {
    { sText_TM_HiddenPower },
    { sText_ChuckTM_BrickBreak },
    { sText_ChuckTM_BulkUp },
    { sText_ChuckTM_FocusPunch }
};

static const u8 sText_JasmineTutor_MetalClaw[] = _("METAL CLAW");
static const u8 sText_JasmineTutor_MetalSound[] = _("METAL SOUND");

static const struct MenuAction sMultichoiceList_JasmineTutor[] = {
    { sText_JasmineTutor_MetalClaw },
    { sText_JasmineTutor_MetalSound }
};

static const u8 sText_JasmineTM_IronTail[] = _("IRON TAIL");
static const u8 sText_JasmineTM_SteelWing[] = _("STEEL WING");

static const struct MenuAction sMultichoiceList_JasmineTM[] = {
    { sText_TM_HiddenPower },
    { sText_JasmineTM_IronTail },
    { sText_JasmineTM_SteelWing }
};

static const u8 sText_PryceTutor_Haze[] = _("HAZE");
static const u8 sText_PryceTutor_IcePunch[] = _("ICE PUNCH");
static const u8 sText_PryceTutor_IcyWind[] = _("ICY WIND");
static const u8 sText_PryceTutor_Mist[] = _("MIST");

static const struct MenuAction sMultichoiceList_PryceTutor[] = {
    { sText_PryceTutor_Haze },
    { sText_PryceTutor_IcePunch },
    { sText_PryceTutor_IcyWind },
    { sText_PryceTutor_Mist }
};

static const u8 sText_PryceTM_Blizzard[] = _("BLIZZARD");
static const u8 sText_PryceTM_Hail[] = _("HAIL");
static const u8 sText_PryceTM_IceBeam[] = _("ICE BEAM");

static const struct MenuAction sMultichoiceList_PryceTM[] = {
    { sText_TM_HiddenPower },
    { sText_PryceTM_Blizzard },
    { sText_PryceTM_Hail },
    { sText_PryceTM_IceBeam }
};

static const u8 sText_ClairTutor_DragonRage[] = _("DRAGON RAGE");
static const u8 sText_ClairTutor_Twister[] = _("TWISTER");

static const struct MenuAction sMultichoiceList_ClairTutor[] = {
    { sText_ClairTutor_DragonRage },
    { sText_ClairTutor_Twister }
};

static const u8 sText_ClairTM_DragonClaw[] = _("DRAGON CLAW");

static const struct MenuAction sMultichoiceList_ClairTM[] = {
    { sText_TM_HiddenPower },
    { sText_ClairTM_DragonClaw }
};

static const struct MultichoiceListStruct sMultichoiceLists[] = {
    [MULTICHOICE_YES_NO]                                     = MULTICHOICE(sMultichoiceList_YesNo),
    [MULTICHOICE_EEVEELUTIONS]                               = MULTICHOICE(sMultichoiceList_Eeveelutions),
    [MULTICHOICE_TRAINER_CARD_ICON_TINT]                     = MULTICHOICE(sMultichoiceList_TrainerCardIconTint),
    [MULTICHOICE_HOF_QUIT]                                   = MULTICHOICE(sMultichoiceList_HOF_Quit),
    [MULTICHOICE_EGGS_QUIT]                                  = MULTICHOICE(sMultichoiceList_Eggs_Quit),
    [MULTICHOICE_VICTORIES_QUIT]                             = MULTICHOICE(sMultichoiceList_Victories_Quit),
    [MULTICHOICE_HOF_EGGS_QUIT]                              = MULTICHOICE(sMultichoiceList_HOF_Eggs_Quit),
    [MULTICHOICE_HOF_VICTORIES_QUIT]                         = MULTICHOICE(sMultichoiceList_HOF_Victories_Quit),
    [MULTICHOICE_EGGS_VICTORIES_QUIT]                        = MULTICHOICE(sMultichoiceList_Eggs_Victories_Quit),
    [MULTICHOICE_HOF_EGGS_VICTORIES_QUIT]                    = MULTICHOICE(sMultichoiceList_HOF_Eggs_Victories_Quit),
    [MULTICHOICE_EXIT]                                       = MULTICHOICE(sMultichoiceList_Exit),
    [MULTICHOICE_EXIT_2]                                     = MULTICHOICE(sMultichoiceList_Exit),
    [MULTICHOICE_EXIT_3]                                     = MULTICHOICE(sMultichoiceList_Exit),
    [MULTICHOICE_BIKE_SHOP]                                  = MULTICHOICE(sMultichoiceList_BikeShop),
    [MULTICHOICE_GAME_CORNER_POKEMON_PRIZES]                 = MULTICHOICE(sMultichoiceList_GameCornerPokemonPrizes),
    [MULTICHOICE_TRAINER_SCHOOL_WHITEBOARD]                  = MULTICHOICE(sMultichoiceList_TrainerSchoolWhiteboard),
    [MULTICHOICE_YES_NO_INFO]                                = MULTICHOICE(sMultichoiceList_YesNoInfo),
    [MULTICHOICE_SINGLE_DOUBLE_MULTI_INFO_EXIT]              = MULTICHOICE(sMultichoiceList_SingleDoubleMultiInfoExit),
    [MULTICHOICE_YES_NO_INFO_2]                              = MULTICHOICE(sMultichoiceList_YesNoInfo2),
    [MULTICHOICE_CHALLENGE_INFO_EXIT]                        = MULTICHOICE(sMultichoiceList_ChallengeInfoExit),
    [MULTICHOICE_ROOFTOP_B1F]                                = MULTICHOICE(sMultichoiceList_RooftopB1F),
    [MULTICHOICE_HELIX]                                      = MULTICHOICE(sMultichoiceList_Helix),
    [MULTICHOICE_DOME]                                       = MULTICHOICE(sMultichoiceList_Dome),
    [MULTICHOICE_AMBER]                                      = MULTICHOICE(sMultichoiceList_Amber),
    [MULTICHOICE_HELIX_AMBER]                                = MULTICHOICE(sMultichoiceList_HelixAmber),
    [MULTICHOICE_DOME_AMBER]                                 = MULTICHOICE(sMultichoiceList_DomeAmber),
    [MULTICHOICE_CELADON_VENDING_MACHINE]                    = MULTICHOICE(sMultichoiceList_CeladonVendingMachine),
    [MULTICHOICE_GAME_CORNER_COIN_PURCHASE_COUNTER]          = MULTICHOICE(sMultichoiceList_GameCornerCoinPurchaseCounter),
    [MULTICHOICE_EXCELLENT_NOT_SO_BAD]                       = MULTICHOICE(sMultichoiceList_Excellent_NotSoBad),
    [MULTICHOICE_RIGHT_LEFT]                                 = MULTICHOICE(sMultichoiceList_RightLeft),
    [MULTICHOICE_GAME_CORNER_TMPRIZES]                       = MULTICHOICE(sMultichoiceList_GameCornerTMPrizes),
    [MULTICHOICE_DEPT_STORE_ELEVATOR]                        = MULTICHOICE(sMultichoiceList_DeptStoreElevator),
    [MULTICHOICE_THIRSTY_GIRL_FRESH_WATER]                   = MULTICHOICE(sMultichoiceList_ThirstyGirlFreshWater),
    [MULTICHOICE_THIRSTY_GIRL_SODA_POP]                      = MULTICHOICE(sMultichoiceList_ThirstyGirlSodaPop),
    [MULTICHOICE_THIRSTY_GIRL_FRESH_WATER_SODA_POP]          = MULTICHOICE(sMultichoiceList_ThirstyGirlFreshWaterSodaPop),
    [MULTICHOICE_THIRSTY_GIRL_LEMONADE]                      = MULTICHOICE(sMultichoiceList_ThirstyGirlLemonade),
    [MULTICHOICE_THIRSTY_GIRL_FRESH_WATER_LEMONADE]          = MULTICHOICE(sMultichoiceList_ThirstyGirlFreshWaterLemonade),
    [MULTICHOICE_THIRSTY_GIRL_SODA_POP_LEMONADE]             = MULTICHOICE(sMultichoiceList_ThirstyGirlSodaPopLemonade),
    [MULTICHOICE_THIRSTY_GIRL_FRESH_WATER_SODA_POP_LEMONADE] = MULTICHOICE(sMultichoiceList_ThirstyGirlFreshWaterSodaPopLemonade),
    [MULTICHOICE_TRADE_CENTER_COLOSSEUM]                     = MULTICHOICE(sMultichoiceList_TradeCenter_Colosseum),
    [MULTICHOICE_LINK_WIRELESS]                              = MULTICHOICE(sMultichoiceList_Link_Wireless),
    [MULTICHOICE_GAME_CORNER_BATTLE_ITEM_PRIZES]             = MULTICHOICE(sMultichoiceList_GameCornerBattleItemPrizes),
    [MULTICHOICE_ROCKET_HIDEOUT_ELEVATOR]                    = MULTICHOICE(sMultichoiceList_RocketHideoutElevator),
    [MULTICHOICE_LINKED_DIRECT_UNION]                        = MULTICHOICE(sMultichoiceList_LinkedDirectUnion),
    [MULTICHOICE_ISLAND_23]                                  = MULTICHOICE(sMultichoiceList_Island23),
    [MULTICHOICE_ISLAND_13]                                  = MULTICHOICE(sMultichoiceList_Island13),
    [MULTICHOICE_ISLAND_12]                                  = MULTICHOICE(sMultichoiceList_Island12),
    [MULTICHOICE_TRADE_COLOSSEUM_CRUSH]                      = MULTICHOICE(sMultichoiceList_TradeColosseumCrush),
    [MULTICHOICE_48]                                         = MULTICHOICE(sMultichoiceList_48),
    [MULTICHOICE_POKEJUMP_DODRIO]                            = MULTICHOICE(sMultichoiceList_PokejumpDodrio),
    [MULTICHOICE_TRADE_COLOSSEUM_2]                          = MULTICHOICE(sMultichoiceList_TradeColosseum_2),
    [MULTICHOICE_MUSHROOMS]                                  = MULTICHOICE(sMultichoiceList_Mushrooms),
    [MULTICHOICE_TRADE_COLOSSEUM_BLANK_CRUSH]                = MULTICHOICE(sMultichoiceList_TradeColosseumBlankCrush),
    [MULTICHOICE_TRADE_COLOSSEUM_BLANK]                      = MULTICHOICE(sMultichoiceList_TradeColosseumBlank),
    [MULTICHOICE_SEVII_NAVEL]                                = MULTICHOICE(sMultichoiceList_SeviiNavel),
    [MULTICHOICE_SEVII_BIRTH]                                = MULTICHOICE(sMultichoiceList_SeviiBirth),
    [MULTICHOICE_SEVII_NAVEL_BIRTH]                          = MULTICHOICE(sMultichoiceList_SeviiNavelBirth),
    [MULTICHOICE_SEAGALLOP_123]                              = MULTICHOICE(sMultichoiceList_Seagallop123),
    [MULTICHOICE_SEAGALLOP_V23]                              = MULTICHOICE(sMultichoiceList_SeagallopV23),
    [MULTICHOICE_SEAGALLOP_V13]                              = MULTICHOICE(sMultichoiceList_SeagallopV13),
    [MULTICHOICE_SEAGALLOP_V12]                              = MULTICHOICE(sMultichoiceList_SeagallopV12),
    [MULTICHOICE_SEAGALLOP_VERMILION]                        = MULTICHOICE(sMultichoiceList_SeagallopVermilion),
    [MULTICHOICE_62]                                         = MULTICHOICE(sMultichoiceList_62),
    [MULTICHOICE_JOIN_OR_LEAD]                               = MULTICHOICE(sMultichoiceList_JoinOrLead),
    [MULTICHOICE_TRAINER_TOWER_MODE]                         = MULTICHOICE(sMultichoiceList_TrainerTowerMode),
    [MULTICHOICE_GYM_REWARD]                                 = MULTICHOICE(sMultichoiceList_GymReward),
    [MULTICHOICE_BROCK_TUTOR]                                = MULTICHOICE(sMultichoiceList_BrockTutor),
    [MULTICHOICE_BROCK_TM]                                   = MULTICHOICE(sMultichoiceList_BrockTM),
    [MULTICHOICE_MISTY_TUTOR]                                = MULTICHOICE(sMultichoiceList_MistyTutor),
    [MULTICHOICE_MISTY_TM]                                   = MULTICHOICE(sMultichoiceList_MistyTM),
    [MULTICHOICE_SURGE_TUTOR]                                = MULTICHOICE(sMultichoiceList_SurgeTutor),
    [MULTICHOICE_SURGE_TM]                                   = MULTICHOICE(sMultichoiceList_SurgeTM),
    [MULTICHOICE_ERIKA_TUTOR]                                = MULTICHOICE(sMultichoiceList_ErikaTutor),
    [MULTICHOICE_ERIKA_TM]                                   = MULTICHOICE(sMultichoiceList_ErikaTM),
    [MULTICHOICE_KOGA_TUTOR]                                 = MULTICHOICE(sMultichoiceList_KogaTutor),
    [MULTICHOICE_KOGA_TM]                                    = MULTICHOICE(sMultichoiceList_KogaTM),
    [MULTICHOICE_SABRINA_TUTOR]                              = MULTICHOICE(sMultichoiceList_SabrinaTutor),
    [MULTICHOICE_SABRINA_TM]                                 = MULTICHOICE(sMultichoiceList_SabrinaTM),
    [MULTICHOICE_BLAINE_TUTOR]                               = MULTICHOICE(sMultichoiceList_BlaineTutor),
    [MULTICHOICE_BLAINE_TM]                                  = MULTICHOICE(sMultichoiceList_BlaineTM),
    [MULTICHOICE_GIOVANNI_TUTOR]                             = MULTICHOICE(sMultichoiceList_GiovanniTutor),
    [MULTICHOICE_GIOVANNI_TM]                                = MULTICHOICE(sMultichoiceList_GiovanniTM),
    [MULTICHOICE_FALKNER_TUTOR]                              = MULTICHOICE(sMultichoiceList_FalknerTutor),
    [MULTICHOICE_FALKNER_TM]                                 = MULTICHOICE(sMultichoiceList_FalknerTM),
    [MULTICHOICE_BUGSY_TUTOR]                                = MULTICHOICE(sMultichoiceList_BugsyTutor),
    [MULTICHOICE_BUGSY_TM]                                   = MULTICHOICE(sMultichoiceList_BugsyTM),
    [MULTICHOICE_WHITNEY_TUTOR]                              = MULTICHOICE(sMultichoiceList_WhitneyTutor),
    [MULTICHOICE_WHITNEY_TM]                                 = MULTICHOICE(sMultichoiceList_WhitneyTM),
    [MULTICHOICE_MORTY_TUTOR]                                = MULTICHOICE(sMultichoiceList_MortyTutor),
    [MULTICHOICE_MORTY_TM]                                   = MULTICHOICE(sMultichoiceList_MortyTM),
    [MULTICHOICE_MORTY_HELD]                                 = MULTICHOICE(sMultichoiceList_MortyHeld),
    [MULTICHOICE_CHUCK_TUTOR]                                = MULTICHOICE(sMultichoiceList_ChuckTutor),
    [MULTICHOICE_CHUCK_TM]                                   = MULTICHOICE(sMultichoiceList_ChuckTM),
    [MULTICHOICE_JASMINE_TUTOR]                              = MULTICHOICE(sMultichoiceList_JasmineTutor),
    [MULTICHOICE_JASMINE_TM]                                 = MULTICHOICE(sMultichoiceList_JasmineTM),
    [MULTICHOICE_PRYCE_TUTOR]                                = MULTICHOICE(sMultichoiceList_PryceTutor),
    [MULTICHOICE_PRYCE_TM]                                   = MULTICHOICE(sMultichoiceList_PryceTM),
    [MULTICHOICE_CLAIR_TUTOR]                                = MULTICHOICE(sMultichoiceList_ClairTutor),
    [MULTICHOICE_CLAIR_TM]                                   = MULTICHOICE(sMultichoiceList_ClairTM),
};

// From Cool to Berries goes unused
const u8 *const gStdStringPtrs[] = {
    [STDSTRING_COOL]             = gText_Cool,
    [STDSTRING_BEAUTY]           = gText_Beauty,
    [STDSTRING_CUTE]             = gText_Cute,
    [STDSTRING_SMART]            = gText_Smart,
    [STDSTRING_TOUGH]            = gText_Tough,
    [STDSTRING_COOL2]            = gText_Cool_2,
    [STDSTRING_BEAUTY2]          = gText_Beauty_2,
    [STDSTRING_CUTE2]            = gText_Cute_2,
    [STDSTRING_SMART2]           = gText_Smart_2,
    [STDSTRING_TOUGH2]           = gText_Tough_2,
    [STDSTRING_ITEMS]            = gText_Items,
    [STDSTRING_KEY_ITEMS]        = gText_KeyItems,
    [STDSTRING_POKEBALLS]        = gText_PokeBalls,
    [STDSTRING_TMHMS]            = gText_TMsAndHMs,
    [STDSTRING_BERRIES]          = gText_Berries,
    [STDSTRING_BOULDER_BADGE]    = gText_Boulderbadge,
    [STDSTRING_CASCADE_BADGE]    = gText_Cascadebadge,
    [STDSTRING_THUNDER_BADGE]    = gText_Thunderbadge,
    [STDSTRING_RAINBOW_BADGE]    = gText_Rainbowbadge,
    [STDSTRING_SOUL_BADGE]       = gText_Soulbadge,
    [STDSTRING_MARSH_BADGE]      = gText_Marshbadge,
    [STDSTRING_VOLCANO_BADGE]    = gText_Volcanobadge,
    [STDSTRING_EARTH_BADGE]      = gText_Earthbadge,
    [STDSTRING_COINS]            = gText_Coins_2,
    [STDSTRING_ITEMS_POCKET]     = gText_ItemsPocket,
    [STDSTRING_KEY_ITEMS_POCKET] = gText_KeyItemsPocket,
    [STDSTRING_POKEBALLS_POCKET] = gText_PokeBallsPocket,
    [STDSTRING_TM_CASE]          = gText_TmCase,
    [STDSTRING_BERRY_POUCH]      = gText_BerryPouch_2
};

static const u8 *const sDescriptionPtrs_CableClub_TradeBattleCancel[] = {
    CableClub_Text_TradeMonsUsingLinkCable,
    CableClub_Text_BattleUsingLinkCable,
    CableClub_Text_CancelSelectedItem
};

static const u8 *const sDescriptionPtrs_WirelessCenter_TradeBattleCrushCancel[] = {
    CableClub_Text_YouMayTradeHere,
    CableClub_Text_YouMayBattleHere,
    CableClub_Text_CanMakeBerryPowder,
    CableClub_Text_CancelSelectedItem
};

static const u8 *const sDescriptionPtrs_WirelessCenter_TradeBattleCancel[] = {
    CableClub_Text_YouMayTradeHere,
    CableClub_Text_YouMayBattleHere,
    CableClub_Text_CancelSelectedItem
};

static const union AnimCmd sMuseumFossilAnim0[] = {
    ANIMCMD_FRAME(0, 10),
    ANIMCMD_END
};

static const union AnimCmd *const sMuseumFossilAnimCmdTable[] = {
    sMuseumFossilAnim0
};

static const struct OamData sMuseumFossilOamData = {
    .shape = SPRITE_SHAPE(64x64),
    .size = SPRITE_SIZE(64x64)
};

static const struct SpriteTemplate sMuseumFossilSprTemplate = {
    .tileTag = GFXTAG_FOSSIL,
    .paletteTag = TAG_NONE,
    .oam = &sMuseumFossilOamData,
    .anims = sMuseumFossilAnimCmdTable,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy
};

static const u16 sMuseumAerodactylSprTiles[] = INCBIN_U16("graphics/script_menu/aerodactyl_fossil.4bpp");
static const u16 sMuseumAerodactylSprPalette[] = INCBIN_U16("graphics/script_menu/aerodactyl_fossil.gbapal");
static const u16 sMuseumKabutopsSprTiles[] = INCBIN_U16("graphics/script_menu/kabutops_fossil.4bpp");
static const u16 sMuseumKabutopsSprPalette[] = INCBIN_U16("graphics/script_menu/kabutops_fossil.gbapal");

static const struct SpriteSheet sMuseumKabutopsSprSheets[] = {
    {sMuseumKabutopsSprTiles, sizeof(sMuseumKabutopsSprTiles), GFXTAG_FOSSIL},
    {}
};

static const struct SpriteSheet sMuseumAerodactylSprSheets[] = {
    {sMuseumAerodactylSprTiles, sizeof(sMuseumAerodactylSprTiles), GFXTAG_FOSSIL},
    {}
};


static const u8 *const sSeagallopDestStrings[] = {
    [SEAGALLOP_VERMILION_CITY] = gText_Vermilion,
    [SEAGALLOP_ONE_ISLAND]     = gText_OneIsland,
    [SEAGALLOP_TWO_ISLAND]     = gText_TwoIsland,
    [SEAGALLOP_THREE_ISLAND]   = gText_ThreeIsland,
    [SEAGALLOP_FOUR_ISLAND]    = gText_FourIsland,
    [SEAGALLOP_FIVE_ISLAND]    = gText_FiveIsland,
    [SEAGALLOP_SIX_ISLAND]     = gText_SixIsland,
    [SEAGALLOP_SEVEN_ISLAND]   = gText_SevenIsland,
};

static u16 GetStringTilesWide(const u8 *str)
{
    return (GetStringWidth(FONT_NORMAL_COPY_1, str, 0) + 7) / 8;
}

static u8 GetMenuWidthFromList(const struct MenuAction * items, u8 count)
{
    u16 i;
    u8 width = GetStringTilesWide(items[0].text);
    u8 tmp;

    for (i = 1; i < count; i++)
    {
        tmp = GetStringTilesWide(items[i].text);
        if (width < tmp)
            width = tmp;
    }
    return width;
}

bool8 ScriptMenu_Multichoice(u8 left, u8 top, u8 mcId, u8 ignoreBpress)
{
    if (FuncIsActiveTask(Task_MultichoiceMenu_HandleInput) == TRUE)
        return FALSE;
    gSpecialVar_Result = SCR_MENU_UNSET;
    DrawVerticalMultichoiceMenu(left, top, mcId, ignoreBpress, 0);
    return TRUE;
}

bool8 ScriptMenu_MultichoiceWithDefault(u8 left, u8 top, u8 mcId, u8 ignoreBpress, u8 cursorPos)
{
    if (FuncIsActiveTask(Task_MultichoiceMenu_HandleInput) == TRUE)
        return FALSE;
    gSpecialVar_Result = SCR_MENU_UNSET;
    DrawVerticalMultichoiceMenu(left, top, mcId, ignoreBpress, cursorPos);
    return TRUE;
}

static void DrawVerticalMultichoiceMenu(u8 left, u8 top, u8 mcId, u8 ignoreBpress, u8 initPos)
{
    s32 i;
    s32 strWidth;
    s32 tmp;
    u8 width;
    u8 height;
    u8 count;
    u8 windowId;
    const struct MenuAction * list;

    if ((ignoreBpress & 2) || QL_AvoidDisplay(QL_DestroyAbortedDisplay) != TRUE)
    {
        ignoreBpress &= 1;
        count = sMultichoiceLists[mcId].count;
        list = sMultichoiceLists[mcId].list;
        strWidth = 0;
        for (i = 0; i < count; i++)
        {
            tmp = GetStringWidth(FONT_NORMAL, list[i].text, 0);
            if (tmp > strWidth)
                strWidth = tmp;
        }
        width = (strWidth + 9) / 8 + 1;
        if (left + width > 28)
            left = 28 - width;
        if (count > SCROLLING_MULTICHOICE_THRESHOLD)
        {
            width += SCROLLING_MULTICHOICE_ARROW_PADDING;
            if (left + width > 28)
                left = 28 - width;
            DrawScrollingMultichoiceMenu(left, top, mcId, ignoreBpress, count, list, width);
        }
        else
        {
            height = GetMCWindowHeight(count);
            windowId = CreateWindowFromRect(left, top, width, height);
            SetStdWindowBorderStyle(windowId, FALSE);
            if (mcId == MULTICHOICE_GAME_CORNER_TMPRIZES
             || mcId == MULTICHOICE_BIKE_SHOP
             || mcId == MULTICHOICE_GAME_CORNER_BATTLE_ITEM_PRIZES)
                MultichoiceList_PrintItems(windowId, FONT_NORMAL, 8, 2, 14, count, list, 0, 2);
            else
                MultichoiceList_PrintItems(windowId, FONT_NORMAL, 8, 2, 14, count, list, 0, 2);
            Menu_InitCursor(windowId, FONT_NORMAL, 0, 2, 14, count, initPos);
            CreateMCMenuInputHandlerTask(ignoreBpress, count, windowId, mcId);
        }
        ScheduleBgCopyTilemapToVram(0);
    }
}

static u8 GetMCWindowHeight(u8 count)
{
    switch (count)
    {
    case 0:
        return 1;
    case 1:
        return 2;
    case 2:
        return 4;
    case 3:
        return 6;
    case 4:
        return 7;
    case 5:
        return 9;
    case 6:
        return 11;
    case 7:
        return 13;
    case 8:
        return 14;
    default:
        return 1;
    }
}

#define tTimer         data[2]
#define tIgnoreBPress  data[4]
#define tWrapAround    data[5]
#define tWindowId      data[6]
#define tMultichoiceId data[7]
#define tScrollCount   data[8]

static u16 sScrollingMultichoiceScrollOffset;

static void CreateMCMenuInputHandlerTask(u8 ignoreBpress, u8 count, u8 windowId, u8 mcId)
{
    u8 taskId;
    if (mcId == MULTICHOICE_TRADE_CENTER_COLOSSEUM
     || mcId == MULTICHOICE_TRADE_COLOSSEUM_CRUSH
     || mcId == MULTICHOICE_TRADE_COLOSSEUM_2)
        sDelay = 12;
    else
        sDelay = 0;

    taskId = CreateTask(Task_MultichoiceMenu_HandleInput, 80);
    gTasks[taskId].tIgnoreBPress = ignoreBpress;
    if (count > 3)
        gTasks[taskId].tWrapAround = TRUE;
    else
        gTasks[taskId].tWrapAround = FALSE;
    gTasks[taskId].tWindowId = windowId;
    gTasks[taskId].tMultichoiceId = mcId;
    MultiChoicePrintHelpDescription(mcId);
}

static void Task_MultichoiceMenu_HandleInput(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    s8 input;
    if (!gPaletteFade.active)
    {
        if (sDelay != 0)
            sDelay--;
        else
        {
            if (tWrapAround == FALSE)
                input = Menu_ProcessInputNoWrapAround();
            else
                input = Menu_ProcessInput();
            if (JOY_NEW(DPAD_UP | DPAD_DOWN))
                MultiChoicePrintHelpDescription(tMultichoiceId);
            switch (input)
            {
            case MENU_NOTHING_CHOSEN:
                return;
            case MENU_B_PRESSED:
                if (tIgnoreBPress)
                    return;
                PlaySE(SE_SELECT);
                gSpecialVar_Result = SCR_MENU_CANCEL;
                break;
            default:
                gSpecialVar_Result = input;
                break;
            }
            DestroyScriptMenuWindow(tWindowId);
            DestroyTask(taskId);
            ScriptContext_Enable();
        }
    }
}

static void ScrollingMultichoiceMenu_Close(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    DestroyScriptMenuWindow(tWindowId);
    DestroyTask(taskId);
    ScriptContext_Enable();
}

static void ScrollingMultichoiceMenu_MoveToSelection(u8 taskId, u8 newSel)
{
    s16 *data = gTasks[taskId].data;
    u8 windowId = tWindowId;
    u8 mcId = tMultichoiceId;
    const struct MenuAction *list = sMultichoiceLists[mcId].list;
    u8 newOffset = sScrollingMultichoiceScrollOffset;

    if (newSel < newOffset)
        newOffset = newSel;
    else if (newSel >= newOffset + SCROLLING_MULTICHOICE_MAX_VISIBLE)
        newOffset = newSel - SCROLLING_MULTICHOICE_MAX_VISIBLE + 1;

    if (newOffset != sScrollingMultichoiceScrollOffset)
    {
        sScrollingMultichoiceScrollOffset = newOffset;
        FillWindowPixelBuffer(windowId, PIXEL_FILL(1));
        MultichoiceList_PrintItems(windowId, FONT_NORMAL, 8, 2, 14, SCROLLING_MULTICHOICE_MAX_VISIBLE, &list[newOffset], 0, 2);
        Menu_InitCursor(windowId, FONT_NORMAL, 0, 2, 14, SCROLLING_MULTICHOICE_MAX_VISIBLE, newSel - newOffset);
        ScheduleBgCopyTilemapToVram(0);
    }
    else
    {
        Menu_MoveCursor((s8)newSel - (s8)(sScrollingMultichoiceScrollOffset + Menu_GetCursorPos()));
    }
}

static void DrawScrollingMultichoiceMenu(u8 left, u8 top, u8 mcId, u8 ignoreBpress, u8 count, const struct MenuAction *list, u8 width)
{
    u8 height;
    u8 windowId;
    u8 taskId;

    sScrollingMultichoiceScrollOffset = 0;
    height = GetMCWindowHeight(SCROLLING_MULTICHOICE_MAX_VISIBLE);
    windowId = CreateWindowFromRect(left, top, width, height);
    SetStdWindowBorderStyle(windowId, FALSE);
    MultichoiceList_PrintItems(windowId, FONT_NORMAL, 8, 2, 14, SCROLLING_MULTICHOICE_MAX_VISIBLE, list, 0, 2);
    Menu_InitCursor(windowId, FONT_NORMAL, 0, 2, 14, SCROLLING_MULTICHOICE_MAX_VISIBLE, 0);
    taskId = CreateTask(Task_ScrollingMultichoiceMenu_HandleInput, 80);
    gTasks[taskId].tIgnoreBPress = ignoreBpress;
    if (count > 3)
        gTasks[taskId].tWrapAround = TRUE;
    else
        gTasks[taskId].tWrapAround = FALSE;
    gTasks[taskId].tWindowId = windowId;
    gTasks[taskId].tMultichoiceId = mcId;
    gTasks[taskId].tScrollCount = count;
    MultiChoicePrintHelpDescription(mcId);
}

static void Task_ScrollingMultichoiceMenu_HandleInput(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    u8 count = tScrollCount;
    s16 sel;
    s16 newSel;

    if (!gPaletteFade.active)
    {
        if (sDelay != 0)
        {
            sDelay--;
            return;
        }
        sel = (s16)sScrollingMultichoiceScrollOffset + Menu_GetCursorPos();
        if (JOY_NEW(A_BUTTON))
        {
            PlaySE(SE_SELECT);
            gSpecialVar_Result = sel;
            ScrollingMultichoiceMenu_Close(taskId);
            return;
        }
        if (JOY_NEW(B_BUTTON))
        {
            if (tIgnoreBPress)
                return;
            PlaySE(SE_SELECT);
            gSpecialVar_Result = SCR_MENU_CANCEL;
            ScrollingMultichoiceMenu_Close(taskId);
            return;
        }
        if (JOY_NEW(DPAD_UP | DPAD_DOWN))
        {
            if (JOY_NEW(DPAD_UP))
                newSel = sel - 1;
            else
                newSel = sel + 1;
            if (tWrapAround)
            {
                if (newSel < 0)
                    newSel = count - 1;
                else if (newSel >= count)
                    newSel = 0;
            }
            else
            {
                if (newSel < 0)
                    newSel = 0;
                else if (newSel >= count)
                    newSel = count - 1;
            }
            if (newSel != sel)
            {
                PlaySE(SE_SELECT);
                ScrollingMultichoiceMenu_MoveToSelection(taskId, (u8)newSel);
            }
            MultiChoicePrintHelpDescription(tMultichoiceId);
        }
    }
}

static void MultiChoicePrintHelpDescription(u8 mcId)
{
    switch (mcId)
    {
    case MULTICHOICE_TRADE_CENTER_COLOSSEUM:
        FillWindowPixelBuffer(0, PIXEL_FILL(1));
        AddTextPrinterParameterized2(0, FONT_NORMAL, sDescriptionPtrs_CableClub_TradeBattleCancel[Menu_GetCursorPos()], 0, NULL, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GRAY);
        break;
    case MULTICHOICE_TRADE_COLOSSEUM_CRUSH:
        FillWindowPixelBuffer(0, PIXEL_FILL(1));
        AddTextPrinterParameterized2(0, FONT_NORMAL, sDescriptionPtrs_WirelessCenter_TradeBattleCrushCancel[Menu_GetCursorPos()], 0, NULL, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GRAY);
        break;
    case MULTICHOICE_TRADE_COLOSSEUM_2:
        FillWindowPixelBuffer(0, PIXEL_FILL(1));
        AddTextPrinterParameterized2(0, FONT_NORMAL, sDescriptionPtrs_WirelessCenter_TradeBattleCancel[Menu_GetCursorPos()], 0, NULL, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GRAY);
        break;
    }
}

bool8 ScriptMenu_YesNo(u8 unused, u8 stuff)
{
    if (FuncIsActiveTask(Task_YesNoMenu_HandleInput) == TRUE)
        return FALSE;
    gSpecialVar_Result = SCR_MENU_UNSET;

    if (QL_AvoidDisplay(QL_DestroyAbortedDisplay))
        return TRUE;

    DisplayYesNoMenuDefaultYes();
    CreateTask(Task_YesNoMenu_HandleInput, 80);
    return TRUE;
}

// Unused
static bool8 IsScriptActive(void)
{
    if (gSpecialVar_Result == SCR_MENU_UNSET)
        return FALSE;
    else
        return TRUE;
}

static void Task_YesNoMenu_HandleInput(u8 taskId)
{
    s8 input;
    if (gTasks[taskId].tTimer < 5)
    {
        gTasks[taskId].tTimer++;
    }
    else
    {
        input = Menu_ProcessInputNoWrapClearOnChoose();
        switch (input)
        {
        case MENU_NOTHING_CHOSEN:
            return;
        case MENU_B_PRESSED:
        case 1: // NO
            PlaySE(SE_SELECT);
            gSpecialVar_Result = FALSE;
            break;
        case 0: // YES
            gSpecialVar_Result = TRUE;
            break;
        }
        DestroyTask(taskId);
        ScriptContext_Enable();
    }
}

bool8 ScriptMenu_MultichoiceGrid(u8 left, u8 top, u8 multichoiceId, bool8 ignoreBpress, u8 columnCount)
{
    const struct MenuAction * list;
    u8 count;
    u8 width;
    u8 rowCount;
    u8 taskId;
    if (FuncIsActiveTask(Hask_MultichoiceGridMenu_HandleInput) == TRUE)
        return FALSE;
    gSpecialVar_Result = SCR_MENU_UNSET;

    if (QL_AvoidDisplay(QL_DestroyAbortedDisplay) == TRUE)
        return TRUE;

    list = sMultichoiceLists[multichoiceId].list;
    count = sMultichoiceLists[multichoiceId].count;
    width = GetMenuWidthFromList(list, count) + 1;
    rowCount = count / columnCount;
    taskId = CreateTask(Hask_MultichoiceGridMenu_HandleInput, 80);
    gTasks[taskId].tIgnoreBPress = ignoreBpress;
    gTasks[taskId].tWindowId = CreateWindowFromRect(left, top, width * columnCount, rowCount * 2);
    SetStdWindowBorderStyle(gTasks[taskId].tWindowId, FALSE);
    MultichoiceGrid_PrintItems(gTasks[taskId].tWindowId, FONT_NORMAL_COPY_1, width * 8, 16, columnCount, rowCount, list);
    MultichoiceGrid_InitCursor(gTasks[taskId].tWindowId, FONT_NORMAL_COPY_1, 0, 1, width * 8, columnCount, rowCount, 0);
    ScheduleBgCopyTilemapToVram(0);

    return TRUE;
}

static void Hask_MultichoiceGridMenu_HandleInput(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    s8 input = Menu_ProcessInputGridLayout();
    switch (input)
    {
    case MENU_NOTHING_CHOSEN:
        return;
    case MENU_B_PRESSED:
        if (tIgnoreBPress)
            return;
        PlaySE(SE_SELECT);
        gSpecialVar_Result = SCR_MENU_CANCEL;
        break;
    default:
        gSpecialVar_Result = input;
        break;
    }
    DestroyScriptMenuWindow(tWindowId);
    DestroyTask(taskId);
    ScriptContext_Enable();
}

#undef tIgnoreBPress
#undef tWrapAround
#undef tWindowId
#undef tMultichoiceId

#define tState        data[0]
#define tSpecies      data[1]
#define tSpriteId     data[2]
#define tWindowId     data[5]

bool8 CreatePCMenu(void)
{
    if (FuncIsActiveTask(Task_MultichoiceMenu_HandleInput) == TRUE)
        return FALSE;
    gSpecialVar_Result = SCR_MENU_UNSET;
    CreatePCMenuWindow();
    return TRUE;
}

static void CreatePCMenuWindow(void)
{
    u8 cursorWidth = GetMenuCursorDimensionByFont(FONT_NORMAL, 0);
    u8 height = GetFontAttribute(FONT_NORMAL, FONTATTR_MAX_LETTER_HEIGHT);
    u8 windowWidth;
    u8 numItems;
    u8 windowId;
    switch (GetStringTilesWide(gText_SPc))
    {
    default:
        if (FlagGet(FLAG_SYS_POKEDEX_GET))
            windowWidth = 14;
        else
            windowWidth = 13;
        break;
    case 9:
    case 10:
        windowWidth = 14;
        break;
    }
    if (FlagGet(FLAG_SYS_GAME_CLEAR))
    {
        numItems = 5;
        windowId = CreateWindowFromRect(0, 0, windowWidth, 10);
        SetStdWindowBorderStyle(windowId, FALSE);
        AddTextPrinterParameterized(windowId, FONT_NORMAL, gText_ProfOakSPc, cursorWidth, 34, TEXT_SKIP_DRAW, NULL);
        AddTextPrinterParameterized(windowId, FONT_NORMAL, gText_HallOfFame_2, cursorWidth, 50, TEXT_SKIP_DRAW, NULL);
        AddTextPrinterParameterized(windowId, FONT_NORMAL, gText_LogOff, cursorWidth, 66, TEXT_SKIP_DRAW, NULL);
    }
    else
    {
        if (FlagGet(FLAG_SYS_POKEDEX_GET))
            numItems = 4;
        else
            numItems = 3;
        windowId = CreateWindowFromRect(0, 0, windowWidth, numItems * 2);
        SetStdWindowBorderStyle(windowId, FALSE);
        if (FlagGet(FLAG_SYS_POKEDEX_GET))
            AddTextPrinterParameterized(windowId, FONT_NORMAL, gText_ProfOakSPc, cursorWidth, 34, TEXT_SKIP_DRAW, NULL);
        AddTextPrinterParameterized(windowId, FONT_NORMAL, gText_LogOff, cursorWidth, 2 + 16 * (numItems - 1), TEXT_SKIP_DRAW, NULL);
    }
    if (FlagGet(FLAG_SYS_NOT_SOMEONES_PC))
        AddTextPrinterParameterized(windowId, FONT_NORMAL, gText_BillSPc, cursorWidth, 2 , TEXT_SKIP_DRAW, NULL);
    else
        AddTextPrinterParameterized(windowId, FONT_NORMAL, gText_SomeoneSPc, cursorWidth, 2 , TEXT_SKIP_DRAW, NULL);
    StringExpandPlaceholders(gStringVar4, gText_SPc);
    Menu_PrintFormatIntlPlayerName(windowId, gStringVar4, cursorWidth, 18);
    Menu_InitCursor(windowId, FONT_NORMAL, 0, 2, 16, numItems, 0);
    CreateMCMenuInputHandlerTask(FALSE, numItems, windowId, MULTICHOICE_NONE);
    ScheduleBgCopyTilemapToVram(0);
}

void ScriptMenu_DisplayPCStartupPrompt(void)
{
    LoadMessageBoxAndFrameGfx(0, TRUE);
    AddTextPrinterParameterized2(0, FONT_NORMAL, Text_AccessWhichPC, 0, NULL, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GRAY);
}

static void Task_ScriptShowMonPic(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    switch (task->tState)
    {
    case 0:
        task->tState++;
        break;
    case 1:
        break;
    case 2:
        FreeResourcesAndDestroySprite(&gSprites[task->tSpriteId], task->tSpriteId);
        task->tState++;
        break;
    case 3:
        DestroyScriptMenuWindow(task->tWindowId);
        DestroyTask(taskId);
        break;
    }
}

bool8 ScriptMenu_ShowPokemonPic(u16 species, u8 x, u8 y)
{
    u8 spriteId;
    u8 taskId;
    if (QL_AvoidDisplay(QL_DestroyAbortedDisplay) == TRUE)
        return TRUE;
    if (FindTaskIdByFunc(Task_ScriptShowMonPic) != TASK_NONE)
        return FALSE;
    spriteId = CreateMonSprite_PicBox(species, 8 * x + 40, 8 * y + 40, FALSE);
    taskId = CreateTask(Task_ScriptShowMonPic, 80);
    gTasks[taskId].tWindowId = CreateWindowFromRect(x, y, 8, 8);
    gTasks[taskId].tState = 0;
    gTasks[taskId].tSpecies = species;
    gTasks[taskId].tSpriteId = spriteId;
    gSprites[spriteId].callback = SpriteCallbackDummy;
    gSprites[spriteId].oam.priority = 0;
    SetStdWindowBorderStyle(gTasks[taskId].tWindowId, TRUE);
    ScheduleBgCopyTilemapToVram(0);
    return TRUE;
}

bool8 (*ScriptMenu_HidePokemonPic(void))(void)
{
    u8 taskId = FindTaskIdByFunc(Task_ScriptShowMonPic);
    if (taskId == TASK_NONE)
        return NULL;
    gTasks[taskId].tState++;
    return PicboxWait;
}

static bool8 PicboxWait(void)
{
    if (FindTaskIdByFunc(Task_ScriptShowMonPic) == TASK_NONE)
        return TRUE;
    else
        return FALSE;
}

void PicboxCancel(void)
{
    u8 taskId = FindTaskIdByFunc(Task_ScriptShowMonPic);
    struct Task *task;
    if (taskId != TASK_NONE)
    {
        task = &gTasks[taskId];
        switch (task->tState)
        {
        case 0:
        case 1:
        case 2:
            FreeResourcesAndDestroySprite(&gSprites[task->tSpriteId], task->tSpriteId);
            DestroyScriptMenuWindow(task->tWindowId);
            DestroyTask(taskId);
            break;
        case 3:
            DestroyScriptMenuWindow(task->tWindowId);
            DestroyTask(taskId);
            break;
        }
    }
}

void Task_WaitMuseumFossilPic(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    switch (task->tState)
    {
    case 0:
        task->tState++;
        break;
    case 1:
        break;
    case 2:
        DestroySprite(&gSprites[task->tSpriteId]);
        FreeSpriteTilesByTag(GFXTAG_FOSSIL);
        task->tState++;
        break;
    case 3:
        DestroyScriptMenuWindow(task->tWindowId);
        DestroyTask(taskId);
        break;
    }
}

#define FOSSIL_PIC_PAL_NUM  13

bool8 OpenMuseumFossilPic(void)
{
    u8 spriteId;
    u8 taskId;
    if (QL_AvoidDisplay(QL_DestroyAbortedDisplay) == TRUE)
        return TRUE;
    if (FindTaskIdByFunc(Task_WaitMuseumFossilPic) != TASK_NONE)
        return FALSE;
    if (gSpecialVar_0x8004 == SPECIES_KABUTOPS)
    {
        LoadSpriteSheets(sMuseumKabutopsSprSheets);
        LoadPalette(sMuseumKabutopsSprPalette, OBJ_PLTT_ID(FOSSIL_PIC_PAL_NUM), sizeof(sMuseumKabutopsSprPalette));
    }
    else if (gSpecialVar_0x8004 == SPECIES_AERODACTYL)
    {
        LoadSpriteSheets(sMuseumAerodactylSprSheets);
        LoadPalette(sMuseumAerodactylSprPalette, OBJ_PLTT_ID(FOSSIL_PIC_PAL_NUM), sizeof(sMuseumAerodactylSprPalette));
    }
    else
    {
        return FALSE;
    }
    spriteId = CreateSprite(&sMuseumFossilSprTemplate, gSpecialVar_0x8005 * 8 + 40, gSpecialVar_0x8006 * 8 + 40, 0);
    gSprites[spriteId].oam.paletteNum = FOSSIL_PIC_PAL_NUM;
    taskId = CreateTask(Task_WaitMuseumFossilPic, 80);
    gTasks[taskId].tWindowId = CreateWindowFromRect(gSpecialVar_0x8005, gSpecialVar_0x8006, 8, 8);
    gTasks[taskId].tState = 0;
    gTasks[taskId].tSpriteId = spriteId;
    SetStdWindowBorderStyle(gTasks[taskId].tWindowId, TRUE);
    ScheduleBgCopyTilemapToVram(0);
    return TRUE;
}

bool8 CloseMuseumFossilPic(void)
{
    u8 taskId = FindTaskIdByFunc(Task_WaitMuseumFossilPic);
    if (taskId == TASK_NONE)
        return FALSE;
    gTasks[taskId].tState++;
    return TRUE;
}

static u8 CreateWindowFromRect(u8 left, u8 top, u8 width, u8 height)
{
    struct WindowTemplate template = SetWindowTemplateFields(0, left + 1, top + 1, width, height, 15, 0x038);
    u8 windowId = AddWindow(&template);
    PutWindowTilemap(windowId);
    return windowId;
}

static void DestroyScriptMenuWindow(u8 windowId)
{
    ClearWindowTilemap(windowId);
    ClearStdWindowAndFrameToTransparent(windowId, TRUE);
    RemoveWindow(windowId);
}

void QL_DestroyAbortedDisplay(void)
{
    u8 taskId;
    s16 *data;
    ScriptContext_SetupScript(EventScript_ReleaseEnd);

    taskId = FindTaskIdByFunc(Task_ScriptShowMonPic);
    if (taskId != TASK_NONE)
    {
        data = gTasks[taskId].data;
        if (tState < 2)
            FreeResourcesAndDestroySprite(&gSprites[tSpriteId], tSpriteId);
    }

    taskId = FindTaskIdByFunc(Task_WaitMuseumFossilPic);
    if (taskId != TASK_NONE)
    {
        data = gTasks[taskId].data;
        if (tState < 2)
        {
            DestroySprite(&gSprites[tSpriteId]);
            FreeSpriteTilesByTag(GFXTAG_FOSSIL);
        }
    }
}

void DrawSeagallopDestinationMenu(void)
{
    // 8004 = Starting location
    // 8005 = Page (0: Verm, One, Two, Three, Four, Other, Exit; 1: Four, Five, Six, Seven, Other, Exit)
    u8 destinationId;
    u8 top;
    u8 numItems;
    u8 cursorWidth;
    u8 fontHeight;
    u8 windowId;
    u8 i;
    gSpecialVar_Result = SCR_MENU_UNSET;

    if (QL_AvoidDisplay(QL_DestroyAbortedDisplay) == TRUE)
        return;

    if (gSpecialVar_0x8005 == 1)
    {
        if (gSpecialVar_0x8004 < SEAGALLOP_FIVE_ISLAND)
            destinationId = SEAGALLOP_FIVE_ISLAND;
        else
            destinationId = SEAGALLOP_FOUR_ISLAND;
        numItems = 5;
        top = 2;
    }
    else
    {
        destinationId = SEAGALLOP_VERMILION_CITY;
        numItems = 6;
        top = 0;
    }
    cursorWidth = GetMenuCursorDimensionByFont(FONT_NORMAL, 0);
    fontHeight = GetFontAttribute(FONT_NORMAL, FONTATTR_MAX_LETTER_HEIGHT);
    windowId = CreateWindowFromRect(17, top, 11, numItems * 2);
    SetStdWindowBorderStyle(windowId, FALSE);
    
    // -2 excludes "Other" and "Exit", appended after the loop
    for (i = 0; i < numItems - 2; i++)
    {
        if (destinationId != gSpecialVar_0x8004)
            AddTextPrinterParameterized(windowId, FONT_NORMAL, sSeagallopDestStrings[destinationId], cursorWidth, i * 16 + 2, TEXT_SKIP_DRAW, NULL);
        else
            i--;
        destinationId++;

        // Wrap around
        if (destinationId == SEAGALLOP_SEVEN_ISLAND + 1)
            destinationId = SEAGALLOP_VERMILION_CITY;
    }
    AddTextPrinterParameterized(windowId, FONT_NORMAL, gText_Other, cursorWidth, i * 16 + 2, TEXT_SKIP_DRAW, NULL);
    i++;
    AddTextPrinterParameterized(windowId, FONT_NORMAL, gOtherText_Exit, cursorWidth, i * 16 + 2, TEXT_SKIP_DRAW, NULL);
    Menu_InitCursor(windowId, FONT_NORMAL, 0, 2, 16, numItems, 0);
    CreateMCMenuInputHandlerTask(FALSE, numItems, windowId, MULTICHOICE_NONE);
    ScheduleBgCopyTilemapToVram(0);
}

u16 GetSelectedSeagallopDestination(void)
{
    // 8004 = Starting location
    // 8005 = Page (0: Verm, One, Two, Three, Four, Other, Exit; 1: Four, Five, Six, Seven, Other, Exit)
    if (gSpecialVar_Result == SCR_MENU_CANCEL)
        return SCR_MENU_CANCEL;
    if (gSpecialVar_0x8005 == 1)
    {
        if (gSpecialVar_Result == 3)
        {
            return SEAGALLOP_MORE;
        }
        else if (gSpecialVar_Result == 4)
        {
            return SCR_MENU_CANCEL;
        }
        else if (gSpecialVar_Result == 0)
        {
            if (gSpecialVar_0x8004 > SEAGALLOP_FOUR_ISLAND)
                return SEAGALLOP_FOUR_ISLAND;
            else
                return SEAGALLOP_FIVE_ISLAND;
        }
        else if (gSpecialVar_Result == 1)
        {
            if (gSpecialVar_0x8004 > SEAGALLOP_FIVE_ISLAND)
                return SEAGALLOP_FIVE_ISLAND;
            else
                return SEAGALLOP_SIX_ISLAND;
        }
        else if (gSpecialVar_Result == 2)
        {
            if (gSpecialVar_0x8004 > SEAGALLOP_SIX_ISLAND)
                return SEAGALLOP_SIX_ISLAND;
            else
                return SEAGALLOP_SEVEN_ISLAND;
        }
    }
    else
    {
        if (gSpecialVar_Result == 4)
            return SEAGALLOP_MORE;
        else if (gSpecialVar_Result == 5)
            return SCR_MENU_CANCEL;
        else if (gSpecialVar_Result >= gSpecialVar_0x8004)
            return gSpecialVar_Result + 1;
        else
            return gSpecialVar_Result;
    }
    return SEAGALLOP_VERMILION_CITY;
}
