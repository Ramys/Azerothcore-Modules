/*
<--------------------------------------------------------------------------->
- Developer(s): NuskyDev and VhiperDev
- Complete: 100%
- Atualizado: 14/05/2018
<--------------------------------------------------------------------------->
*/

#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "DBCStores.h"

enum eTitles
{
	JUSTICAR            = 48,
	PROPHET             = 89,
	STALKER				= 91,
	ASSASSIN			= 95,
	DOCTOR				= 101,
	THE_FORSAKEN		= 119,
	AMBASSADOR          = 130,
	THE_IMMORTAL		= 141,
	THE_UNDYING			= 142,
	JENKINS             = 143,
	THE_INSANE			= 145,
	THE_NOBLE           = 155,
	STARCALLER          = 164,
};

enum eTokens
{
	// Item ID
	TOKEN_ID     = 37711,

	// Cost
	TITLE1_COST  = 1,
	TITLE2_COST  = 2,
	TITLE3_COST  = 5,
	TITLE4_COST  = 10,
	TITLE5_COST  = 15,
	TITLE6_COST  = 20,
	TITLE7_COST  = 25,
	TITLE8_COST  = 30,
	TITLE9_COST  = 35,
	TITLE10_COST = 40,
	TITLE11_COST = 45,
	TITLE12_COST = 50,
	TITLE13_COST = 100
};

class NPC_Title_Tokens : public CreatureScript
{
public:
	NPC_Title_Tokens() : CreatureScript("NPC_Title_Tokens") { }

	bool OnGossipHello(Player * player, Creature * creature)
	{
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_PVP_P_10:24:24:-18:0|tJenkins (1 Tokens)|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 0);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_PVP_P_01:24:24:-18:0|tJusticar (2 Tokens)|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_PVP_P_02:24:24:-18:0|tThe Noble (5 Tokens)|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_PVP_P_13:24:24:-18:0|tStarcaller (10 Tokens)|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_PVP_P_05:24:24:-18:0|tDoctor (15 Tokens)|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_PVP_P_06:24:24:-18:0|tThe Forsaken (20 Tokens)|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_PVP_P_07:24:24:-18:0|tAmbassador (25 Tokens)|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_PVP_P_03:24:24:-18:0|tStalker (30 Tokens)|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_PVP_P_11:24:24:-18:0|tThe Insane (35 Tokens)|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_PVP_P_12:24:24:-18:0|tProphet (40 Tokens)|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_PVP_P_04:24:24:-18:0|tAssassin (45 Tokens)|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_PVP_P_08:24:24:-18:0|tThe Imortal (50 Tokens)|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_PVP_P_09:24:24:-18:0|tThe Undying (100 Tokens)|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|TInterface/ICONS/Ability_Spy:24:24:-18:0|t|r Back|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 999);
		player->SEND_GOSSIP_MENU(1, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player * player, Creature * creature, uint32 /*senders*/, uint32 actions)
	{
		switch(actions)
		{
			case GOSSIP_ACTION_INFO_DEF + 0:
				AddTitle(player, TOKEN_ID, TITLE1_COST, JENKINS);
				break;

			case GOSSIP_ACTION_INFO_DEF + 1:
				AddTitle(player, TOKEN_ID, TITLE2_COST, JUSTICAR);
				break;

			case GOSSIP_ACTION_INFO_DEF + 2:
				AddTitle(player, TOKEN_ID, TITLE3_COST, THE_NOBLE);
				break;

			case GOSSIP_ACTION_INFO_DEF + 3:
				AddTitle(player, TOKEN_ID, TITLE4_COST, STARCALLER);
				break;

			case GOSSIP_ACTION_INFO_DEF + 4:
				AddTitle(player, TOKEN_ID, TITLE5_COST, DOCTOR);
				break;

			case GOSSIP_ACTION_INFO_DEF + 5:
				AddTitle(player, TOKEN_ID, TITLE6_COST, THE_FORSAKEN);
				break;

			case GOSSIP_ACTION_INFO_DEF + 6:
				AddTitle(player, TOKEN_ID, TITLE7_COST, AMBASSADOR);
				break;

			case GOSSIP_ACTION_INFO_DEF + 7:
				AddTitle(player, TOKEN_ID, TITLE8_COST, STALKER);
				break;

			case GOSSIP_ACTION_INFO_DEF + 8:
				AddTitle(player, TOKEN_ID, TITLE9_COST, THE_INSANE);
				break;

			case GOSSIP_ACTION_INFO_DEF + 9:
				AddTitle(player, TOKEN_ID, TITLE10_COST, PROPHET);
				break;

			case GOSSIP_ACTION_INFO_DEF + 10:
				AddTitle(player, TOKEN_ID, TITLE11_COST, ASSASSIN);
				break;

			case GOSSIP_ACTION_INFO_DEF + 11:
				AddTitle(player, TOKEN_ID, TITLE12_COST, THE_IMMORTAL);
				break;

			case GOSSIP_ACTION_INFO_DEF + 12:
				AddTitle(player, TOKEN_ID, TITLE13_COST, THE_UNDYING);
				break;

			case GOSSIP_ACTION_INFO_DEF + 999:
		        creature->MonsterWhisper("Check back often!", player);
			    player->PlayerTalkClass->SendCloseGossip();  
			    break; 
		}
		return true;
	}

	static void AddTitle(Player* player, uint32 token, uint32 quantity, uint32 title)
    {
		if (player->HasItemCount(token, quantity, true))
	    {
		    if (player->HasTitle(title)) 
		    {
		    	player->GetSession()->SendNotification("|cffe84118[ERRO] \n |cfff5f6faYou can not buy titles you already own.");
		    }
		    else
		    {
				CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(title);
                player->SetTitle(titleInfo, false);
                player->DestroyItemCount(token, quantity, true, false);
			    player->GetSession()->SendNotification("|cff44bd32Congratulations! \n |cfff5f6faTitle successfully purchased.");
		    }
	        player->PlayerTalkClass->SendCloseGossip();
	    }
	    else
	    {
	    	player->GetSession()->SendNotification("|cffe84118[ERRO] \n |cfff5f6faYou do not have enough tokens.");
	        player->PlayerTalkClass->SendCloseGossip();
	    }
    }
};

void AddSC_NPC_Title_Tokens()
{
	new NPC_Title_Tokens();
}
