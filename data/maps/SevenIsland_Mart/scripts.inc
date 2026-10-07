SevenIsland_Mart_MapScripts::
	.byte 0

SevenIsland_Mart_EventScript_Clerk::
	goto_if_questlog EventScript_ReleaseEnd
	lock
	faceplayer
	message Text_MayIHelpYou
	waitmessage
	pokemart SevenIsland_Mart_Items
	msgbox Text_PleaseComeAgain
	release
	end

	.align 2
SevenIsland_Mart_Items::
	.2byte ITEM_POKE_BALL
	.2byte ITEM_MENTAL_HERB
	.2byte ITEM_WHITE_HERB
	.2byte ITEM_HEAL_POWDER
	.2byte ITEM_ENERGY_ROOT
	.2byte ITEM_REVIVAL_HERB
	.2byte ITEM_POMEG_BERRY
	.2byte ITEM_KELPSY_BERRY
	.2byte ITEM_QUALOT_BERRY
	.2byte ITEM_HONDEW_BERRY
	.2byte ITEM_GREPA_BERRY
	.2byte ITEM_TAMATO_BERRY
	.2byte ITEM_REPEL
	.2byte ITEM_NONE
	release
	end

SevenIsland_Mart_EventScript_Lass::
	msgbox SevenIsland_Mart_Text_MonHavePersonalitiesOfTheirOwn, MSGBOX_NPC
	end

SevenIsland_Mart_EventScript_Hiker::
	msgbox SevenIsland_Mart_Text_PreparationsCompleteForRuins, MSGBOX_NPC
	end

SevenIsland_Mart_EventScript_Fisher::
	msgbox SevenIsland_Mart_Text_NeedToFishOnSevenIsland, MSGBOX_NPC
	end
