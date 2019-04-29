/* Copyright 
Author : Callmephil
Reworked : Poszer
Version : 3.3.5 / 4.3.4
Dynamic Resurrection is a simple script that add a "Resurrection Waypoint" near the latest boss killed in dungeon or raid. for faster Resurrection.
Updated : 28/04/2019
*/

#include "DynamicResurrection.h"

class Dynamic_Resurrections : public PlayerScript
{
public:
	Dynamic_Resurrections() : PlayerScript("Dynamic_Resurrections") {}

	void OnCreatureKill(Player* player, Creature* boss) override
	{
		if (sDynRes->IsInDungeonOrRaid(player) && (boss->isWorldBoss() || boss->IsDungeonBoss()))
			player->SummonCreature(C_Resurrection_ENTRY, boss->GetPositionX(), boss->GetPositionY(), boss->GetPositionZ(), 0, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, C_SPAWN_TIMER_TWO_HOURS);
	}
};

bool Dynamic_Resurrection::IsInDungeonOrRaid(Player* player)
{
	if (sMapStore.LookupEntry(player->GetMapId())->Instanceable())
		return true; // boolean need to return to a value
	return false;
}

bool Dynamic_Resurrection::CheckForSpawnPoint(Player* player)
{
	// Find Nearest Creature And Teleport.
	if (Creature* creature = player->FindNearestCreature(C_Resurrection_ENTRY, C_DISTANCE_CHECK_RANGE))
		return true;
	return false;
}

void AddSC_Dynamic_ResurrectionScripts()
{
    new Dynamic_Resurrections();
    new Dynamic_Resurrection();
}
