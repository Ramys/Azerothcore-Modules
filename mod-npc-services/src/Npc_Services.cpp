#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedGossip.h"

class Npc_Services : public CreatureScript
{
public:
        Npc_Services() : CreatureScript("Npc_Services") { }
 
        bool OnGossipHello(Player *player, Creature *creature)
        {
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\Spell_Nature_Regenerate:40:40:-18|t Restore HP and MP", GOSSIP_SENDER_MAIN, 1);			// Restore Health and Mana
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\Achievement_BG_winAB_underXminutes:40:40:-18|t Reset Instances", GOSSIP_SENDER_MAIN, 2);	// Reset Instances
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\SPELL_HOLY_BORROWEDTIME:40:40:-18|t Reset Cooldowns", GOSSIP_SENDER_MAIN, 3);				// Reset Cooldowns
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\Achievement_BG_AB_defendflags:40:40:-18|t Reset Combat", GOSSIP_SENDER_MAIN, 4);			// Leave Combat
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\Spell_Shadow_DeathScream:40:40:-18|t Remove Sickness", GOSSIP_SENDER_MAIN, 5);				// Remove Sickness
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Hammer_24:40:40:-18|t Repair Items", GOSSIP_SENDER_MAIN, 6);							// Repair Items
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\Achievement_WorldEvent_Lunar:40:40:-18|t Reset Talents", GOSSIP_SENDER_MAIN, 7);			// Reset Talents
		player->ADD_GOSSIP_ITEM(10, "|TInterface/Icons/INV_Misc_Bag_07:40:40:-18|t Bank", GOSSIP_SENDER_MAIN, 8);                                   // Open Bank
		//player->ADD_GOSSIP_ITEM(10, "|TInterface/Icons/INV_Letter_11:40:40:-18|t Mail", GOSSIP_SENDER_MAIN, 9);                                     // Open Mailbox
        player->ADD_GOSSIP_ITEM(10, "|TInterface/Icons/achievement_general:40:40:-18|t Learn Dual Talents", GOSSIP_SENDER_MAIN, 10);                                     // Learn Dualspec
		player->SEND_GOSSIP_MENU(1, creature->GetGUID());
        return true;
	}
	bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*sender*/, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();

		switch (action)
		{
		case 1: // Restore HP and MP
				player->CLOSE_GOSSIP_MENU();
			if (player->IsInCombat())
			{
				player->CLOSE_GOSSIP_MENU();
				player->GetSession()->SendNotification("You are in combat!");
				return false;
				}
				else if(player->getPowerType() == POWER_MANA)
						player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));

				player->SetHealth(player->GetMaxHealth());
				player->GetSession()->SendNotification("|cffFFFF00NPC SERVICES \n |cffFFFFFFHP & MP succesfully restored!");
				player->CastSpell(player, 31726);
				break;

	    case 2: // Reset Instances
				player->CLOSE_GOSSIP_MENU();
				for (uint8 i = 0; i < MAX_DIFFICULTY; ++i)
				{
                    BoundInstancesMap const& m_boundInstances = sInstanceSaveMgr->PlayerGetBoundInstances(player->GetGUIDLow(), Difficulty(i));
                    for (BoundInstancesMap::const_iterator itr = m_boundInstances.begin(); itr != m_boundInstances.end();)
                    {
                        InstanceSave* save = itr->second.save;
                        if (itr->first != player->GetMapId())
                        {
                            uint32 resetTime = itr->second.extended ? save->GetExtendedResetTime() : save->GetResetTime();
                            uint32 ttr = (resetTime >= time(nullptr) ? resetTime - time(nullptr) : 0);
                            sInstanceSaveMgr->PlayerUnbindInstance(player->GetGUIDLow(), itr->first, Difficulty(i), true, player);
                            itr = m_boundInstances.begin();
                        }
                        else
                            ++itr;
                    }
				}

				player->GetSession()->SendNotification("|cffFFFF00NPC SERVICES \n |cffFFFFFFInstances succesfully reseted!");
				player->CastSpell(player, 59908);
                return true;
				break;

		case 3: // Reset Cooldowns
				player->CLOSE_GOSSIP_MENU();
				if (player->IsInCombat())
				{
				player->CLOSE_GOSSIP_MENU();
				player->GetSession()->SendNotification("You are in combat!");
				return false;
				}

				player->RemoveAllSpellCooldown();
				player->GetSession()->SendNotification("|cffFFFF00NPC SERVICES \n |cffFFFFFFCooldowns succesfully reseted!");
				player->CastSpell(player, 31726);
				break;

		case 4: // Leave Combat
				player->CLOSE_GOSSIP_MENU();
				player->CombatStop();
				player->GetSession()->SendNotification("|cffFFFF00NPC SERVICES \n |cffFFFFFFCombat succesfully removed!");
				player->CastSpell(player, 31726);
				break;

		case 5: // Remove Sickness
				player->CLOSE_GOSSIP_MENU();
				if(player->HasAura(15007))
				player->RemoveAura(15007);
				player->GetSession()->SendNotification("|cffFFFF00NPC SERVICES \n |cffFFFFFFSickness succesfully removed!");
				player->CastSpell(player, 31726);
				break;

		case 6: // Repair Items
				player->CLOSE_GOSSIP_MENU();
				player->DurabilityRepairAll(false, 0, false);
				player->GetSession()->SendNotification("|cffFFFF00NPC SERVICES \n |cffFFFFFFItems repaired succesfully!");
				player->CastSpell(player, 31726);
				break;

	   case 7: // Reset Talents
				player->CLOSE_GOSSIP_MENU();
				player->resetTalents(true);
				player->SendTalentsInfoData(false);
				player->GetSession()->SendNotification("|cffFFFF00NPC SERVICES \n |cffFFFFFFTalents reseted succesfully!");
				player->CastSpell(player, 31726);
				break;
				
		case 8:	// BANK
				player->CLOSE_GOSSIP_MENU();
				player->GetSession()->SendShowBank(player->GetGUID());
				break;
				
/*	    case 9: // MAIL
				player->CLOSE_GOSSIP_MENU();
				player->GetSession()->SendShowMailBox(player->GetGUID());
				break;
*/
		case 10: // Learn Dual Talent Specialization
				player->CLOSE_GOSSIP_MENU();
				if (player->IsInCombat())
				{
				player->CLOSE_GOSSIP_MENU();
				player->GetSession()->SendNotification("You are in combat!");
				return false;
				}

				player->CastSpell(player, 63624);
				player->CastSpell(player, 63680);
				player->GetSession()->SendNotification("|cffFFFF00NPC SERVICES \n |cffFFFFFFDual Talents Learned Succesfully!");
				return true;
				break;

             }
                return true;
        }
};
 
void AddSC_Npc_Services()
{
        new Npc_Services();
}
