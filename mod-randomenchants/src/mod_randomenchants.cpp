/*

# Random Enchants

_This module was adapted for[StygianCore](https://rebrand.ly/stygiancoreproject). A World of Warcraft 3.3.5a Solo/LAN repack by StygianTheBest | [GitHub](https://rebrand.ly/stygiangithub) | [Website](https://rebrand.ly/stygianthebest))_

### Description
------------------------------------------------------------------------------------------------------------------
This module adds random enchantments to gear the player acquires.

### Data
------------------------------------------------------------------------------------------------------------------
- Type: Script
- Config : Yes
- SQL : Yes

### Version
------------------------------------------------------------------------------------------------------------------
- v2018.12.10 - Added Config Options : % Chance to Enchant, Item Quality to Enchant
- v2017.07.29 - Added Module Announce, Updated Strings


### CREDITS
------------------------------------------------------------------------------------------------------------------
![Styx](https://stygianthebest.github.io/assets/img/avatar/avatar-128.jpg "Styx")
![StygianCore](https ://stygianthebest.github.io/assets/img/projects/stygiancore/StygianCore.png "StygianCore")

##### This module was adapted for [StygianCore](https://rebrand.ly/stygiancoreproject). A World of Warcraft 3.3.5a Solo/LAN repack by StygianTheBest | [GitHub](https://rebrand.ly/stygiangithub) | [Website](https://rebrand.ly/stygianthebest))

#### Additional Credits
-[Blizzard Entertainment](http ://blizzard.com)
-[TrinityCore](https ://github.com/TrinityCore/TrinityCore/blob/3.3.5/THANKS)
-[SunwellCore](http ://www.azerothcore.org/pages/sunwell.pl/)
-[AzerothCore](https ://github.com/AzerothCore/azerothcore-wotlk/graphs/contributors)
-[OregonCore](https ://wiki.oregon-core.net/)
-[Wowhead.com](http ://wowhead.com)
-[OwnedCore](http ://ownedcore.com/)
-[ModCraft.io](http ://modcraft.io/)
-[MMO Society](https ://www.mmo-society.com/)
-[AoWoW](https ://wotlk.evowow.com/)
-[More credits are cited in the sources](https ://github.com/StygianTheBest)

### LICENSE
------------------------------------------------------------------------------------------------------------------
This code and content is released under the[GNU AGPL v3](https ://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3).

*/

#include "ScriptMgr.h"
#include "Configuration/Config.h"
#include "ObjectMgr.h"
#include "Chat.h"
#include "Player.h"
#include "Object.h"

bool RandomEnchantEnabled = true;
bool RandomEnchantAnnounce = true;
bool Crafted = 1;
bool Looted = 1;
bool QuestReward = 1;
uint32 HighQuality = 5;
uint32 LowQuality = 1;
uint32 Chance1 = 70;
uint32 Chance2 = 65;
uint32 Chance3 = 60;

class REConfig : public WorldScript
{
public:
	REConfig() : WorldScript("REConfig") { }

	void OnBeforeConfigLoad(bool reload) override
	{
		if (!reload) {
			std::string conf_path = _CONF_DIR;
			std::string cfg_file = conf_path + "/mod_randomenchants.conf";
#ifdef WIN32
			cfg_file = "mod_randomenchants.conf";
#endif

			std::string cfg_def_file = cfg_file + ".dist";
			sConfigMgr->LoadMore(cfg_def_file.c_str());
			sConfigMgr->LoadMore(cfg_file.c_str());

			// Load Configuration Settings
			SetInitialWorldSettings();
		}
	}

	// Load Configuration Settings
	void SetInitialWorldSettings()
	{
		RandomEnchantEnabled = sConfigMgr->GetBoolDefault("RandomEnchants.Enabled", true);
		RandomEnchantAnnounce = sConfigMgr->GetBoolDefault("RandomEnchants.Announce", true);
		Crafted = sConfigMgr->GetBoolDefault("RandomEnchants.OnCreate", 1);
		Looted = sConfigMgr->GetBoolDefault("RandomEnchants.OnLoot", 1);
		QuestReward = sConfigMgr->GetBoolDefault("RandomEnchants.OnQuestReward", 1);
		HighQuality = sConfigMgr->GetIntDefault("RandomEnchants.HighQuality", 1);
		LowQuality = sConfigMgr->GetIntDefault("RandomEnchants.LowQuality", 1);
		Chance1 = sConfigMgr->GetIntDefault("RandomEnchants.Chance1", 70);
		Chance2 = sConfigMgr->GetIntDefault("RandomEnchants.Chance2", 65);
		Chance3 = sConfigMgr->GetIntDefault("RandomEnchants.Chance3", 60);

		// Sanitize
		if (HighQuality > 5) { HighQuality = 5; }
		
	}
};

class RandomEnchantsPlayer : public PlayerScript {
public:

	RandomEnchantsPlayer() : PlayerScript("RandomEnchantsPlayer") { }

	void OnLogin(Player* player)  override
	{
		if (sConfigMgr->GetBoolDefault("RandomEnchants.Announce", true)) {
			ChatHandler(player->GetSession()).SendSysMessage("This server is running the |cff4CFF00RandomEnchants |rmodule.");
		}
	}

	void OnLootItem(Player* player, Item* item, uint32 count, uint64 /*lootguid*/) override
	{
		if (RandomEnchantEnabled)
		{
			RollPossibleEnchant(player, item);
		}
	}

	void OnCreateItem(Player* player, Item* item, uint32 count) override
	{
		if (RandomEnchantEnabled)
		{
			if (Crafted == true)
			{
				RollPossibleEnchant(player, item);
			}
		}
	}

	void OnQuestRewardItem(Player* player, Item* item, uint32 count) override
	{
		if (RandomEnchantEnabled)
		{
			if (QuestReward == true)
			{
				RollPossibleEnchant(player, item);
			}
		}
	}

	void RollPossibleEnchant(Player* player, Item* item)
	{
		uint32 Quality = item->GetTemplate()->Quality;
		uint32 Class = item->GetTemplate()->Class;

		// Weed out items ( needs more testing )
		if ((Quality < LowQuality && Quality > HighQuality) || (Class != 2 && Class != 4))
		{
			// Eliminate enchanting anything that isn't a designated quality.
			// Eliminate enchanting anything but weapons(2) and armor(4).
			return;
		}

		// It's what we want..
		int slotRand[3] = { -1, -1, -1 };
		uint32 slotEnch[3] = { 0, 1, 5 };
		double roll1 = rand_chance();
		if (roll1 >= Chance1) //
			slotRand[0] = getRandEnchantment(item);
		if (slotRand[0] != -1)
		{
			double roll2 = rand_chance();
			if (roll2 >= Chance2) //
				slotRand[1] = getRandEnchantment(item);
			if (slotRand[1] != -1)
			{
				double roll3 = rand_chance();
				if (roll3 >= Chance3) //
					slotRand[2] = getRandEnchantment(item);
			}
		}
		for (int i = 0; i < 2; i++)
		{
			if (slotRand[i] != -1)
			{
				if (sSpellItemEnchantmentStore.LookupEntry(slotRand[i])) //Make sure enchantment id exists
				{
					player->ApplyEnchantment(item, EnchantmentSlot(slotEnch[i]), false);
					item->SetEnchantment(EnchantmentSlot(slotEnch[i]), slotRand[i], 0, 0);
					player->ApplyEnchantment(item, EnchantmentSlot(slotEnch[i]), true);
				}
			}
		}
		ChatHandler chathandle = ChatHandler(player->GetSession());
		if (slotRand[2] != -1)
			chathandle.PSendSysMessage("|cffDA70D6 The |cff71C671%s |cffDA70D6is marked with ancient runes that emit a radiant glow.", item->GetTemplate()->Name1.c_str());
		else if (slotRand[1] != -1)
			chathandle.PSendSysMessage("|cffDA70D6 The |cff71C671%s |cffDA70D6glows brightly as you pick it up.", item->GetTemplate()->Name1.c_str());
		else if (slotRand[0] != -1)
			chathandle.PSendSysMessage("|cffDA70D6 The |cff71C671%s |cffDA70D6is clearly a cut above the rest.", item->GetTemplate()->Name1.c_str());
	}

	int getRandEnchantment(Item* item)
	{
		uint32 Class = item->GetTemplate()->Class;
		std::string ClassQueryString = "";
		switch (Class)
		{
		case 2:
			ClassQueryString = "WEAPON";
			break;
		case 4:
			ClassQueryString = "ARMOR";
			break;
		}
		if (ClassQueryString == "")
			return -1;
		uint32 Quality = item->GetTemplate()->Quality;
		int rarityRoll = -1;
		switch (Quality)
		{
		case 0://grey
			rarityRoll = 51 + rand_norm() * 5;
			break;
		case 1://white
			rarityRoll = 56 + rand_norm() * 10;
			break;
		case 2://green
			rarityRoll = 52 + (rand_norm() * 15);
			break;
		case 3://blue
			rarityRoll = 52 + (rand_norm() * 35);
			break;
		case 4://purple
			rarityRoll = 56 + (rand_norm() * 25);
			break;
		case 5://orange
			rarityRoll = 61 + (rand_norm() * 30);
			break;
		}
		if (rarityRoll < 0)
			return -1;
		int tier = 0;
		if (rarityRoll <= 45)
			tier = 1;
		else if (rarityRoll <= 51)
			tier = 2;
		else if (rarityRoll <= 61)
			tier = 3;
		else if (rarityRoll <= 71)
			tier = 4;
		else
			tier = 5;

		QueryResult qr = WorldDatabase.PQuery("SELECT enchantID FROM item_enchantment_random_tiers WHERE tier='%d' AND exclusiveSubClass=NULL AND class='%s' OR exclusiveSubClass='%u' OR class='ANY' ORDER BY RAND() LIMIT 1", tier, ClassQueryString.c_str(), item->GetTemplate()->SubClass);
		return qr->Fetch()[0].GetUInt32();
	}
};

void AddRandomEnchantsScripts()
{
	new REConfig();
	new RandomEnchantsPlayer();
}