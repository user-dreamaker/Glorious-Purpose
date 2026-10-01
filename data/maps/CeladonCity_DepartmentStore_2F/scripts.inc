CeladonCity_DepartmentStore_2F_MapScripts::
	.byte 0

CeladonCity_DepartmentStore_2F_EventScript_UnusedNPC::
	msgbox CeladonCity_DepartmentStore_2F_Text_SuperRepelMorePowerfulRepel, MSGBOX_NPC
	end

CeladonCity_DepartmentStore_2F_EventScript_Lass::
	msgbox CeladonCity_DepartmentStore_2F_Text_BuyReviveForLongOutings, MSGBOX_NPC
	end

CeladonCity_DepartmentStore_2F_EventScript_FloorSign::
	msgbox CeladonCity_DepartmentStore_2F_Text_FloorSign, MSGBOX_SIGN
	end

CeladonCity_DepartmentStore_2F_EventScript_ClerkItems::
	goto_if_questlog EventScript_ReleaseEnd
	lock
	faceplayer
	message Text_MayIHelpYou
	waitmessage
	pokemart CeladonCity_DepartmentStore_2F_Items
	msgbox Text_PleaseComeAgain
	release
	end

	.align 2
CeladonCity_DepartmentStore_2F_Items::
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_DIVE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_TIMER_BALL 
	.2byte ITEM_LUXURY_BALL 
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_NONE
	release
	end

CeladonCity_DepartmentStore_2F_EventScript_ClerkTMs::
	goto_if_questlog EventScript_ReleaseEnd
	lock
	faceplayer
	message Text_MayIHelpYou
	waitmessage
	pokemart CeladonCity_DepartmentStore_2F_TMs
	msgbox Text_PleaseComeAgain
	release
	end

	.align 2
CeladonCity_DepartmentStore_2F_TMs::
	.2byte ITEM_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_NONE
	release
	end
