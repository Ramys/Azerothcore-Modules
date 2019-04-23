/*
*
* Copyright (C) 2013 Emu-Devstore <http://emu-devstore.com/>
* Written by Teiby <http://www.teiby.de/>
* Adjusted by fr4z3n for azerothcore
* Reworked by XDev
*/
    
    #ifndef ARENA_1V1_H
    #define ARENA_1V1_H

#include "Config.h"
#include "ScriptMgr.h"
#include "Player.h"


  // TalentTab.dbc -> TalentTabID
const uint32 FORBIDDEN_TALENTS_IN_1V1_ARENA[] =
{
    // Healer
    //201, // PriestDiscipline
    //202, // PriestHoly
    //382, // PaladinHoly
    //262, // ShamanRestoration
    //282, // DruidRestoration

         // Tanks
         //383, // PaladinProtection
         //163, // WarriorProtection

         0 // End
};

static bool Arena1v1CheckTalents(Player* player)
{
    if (!player)
        return false;

    if (sConfigMgr->GetBoolDefault("Arena1v1BlockForbiddenTalents", true) == false)
        return true;

    uint32 count = 0;
    for (uint32 talentId = 0; talentId < sTalentStore.GetNumRows(); ++talentId)
    {
        TalentEntry const* talentInfo = sTalentStore.LookupEntry(talentId);

        if (!talentInfo)
            continue;

        for (int8 rank = MAX_TALENT_RANK - 1; rank >= 0; --rank)
        {
            if (talentInfo->RankID[rank] == 0)
                continue;

            if (player->HasTalent(talentInfo->RankID[rank], player->GetActiveSpec()))
            {
                for (int8 i = 0; FORBIDDEN_TALENTS_IN_1V1_ARENA[i] != 0; i++)
                    if (FORBIDDEN_TALENTS_IN_1V1_ARENA[i] == talentInfo->TalentTab)
                        count += rank + 1;
            }
        }
    }

    if (count >= 36)
    {
        ChatHandler(player->GetSession()).SendSysMessage("You can not join because you have too many talent points in a forbidden tree. (Heal / Tank)");
        return false;
    }
    else
        return true;
}

#endif
