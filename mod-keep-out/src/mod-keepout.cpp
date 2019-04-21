#include "Configuration/Config.h"
#include "Player.h"
#include "Creature.h"
#include "AccountMgr.h"
#include "ScriptMgr.h"
#include "Define.h"
#include "GossipDef.h"

uint32 maxwarnings;
bool KeepoutEnabled;

class Playerwarning : public DataMap::Base
{
public:
    Playerwarning() {}
    Playerwarning(uint32 warning) : warning(warning) {}
    uint32 warning = 1;
};

class Keepout : public PlayerScript
{
public:
    Keepout() : PlayerScript("Keepout") { }

    std::string playername;
    std::string mapname;
    std::string maparea;

    void OnLogin(Player* player)
    {
        ChatHandler(player->GetSession()).PSendSysMessage("This server is running the |cff4CFF00Keepout |rmodule.");
    }

    void OnMapChanged(Player* player)
    {
        if (KeepoutEnabled)
        {
            if (player->GetSession()->GetSecurity() >= SEC_GAMEMASTER)
                return;

            QueryResult result = WorldDatabase.PQuery("SELECT `mapId` FROM `MapLock` WHERE `mapId` = '%u'", player->GetMapId());

            playername = player->GetName();
            mapname = player->GetMap()->GetMapName();
            maparea = player->GetZoneId();

            if (!result)
                return;

            do
            {
                CharacterDatabase.PQuery("INSERT INTO `mapexploit` (`player`, `map`, `area`) VALUES ('%s', '%s', '%u')", playername.c_str(), mapname.c_str(), player->GetAreaId());
                ChatHandler(player->GetSession()).PSendSysMessage("You have gone to a forbidden place your actions have been logged.");

                uint32& warninggiven = player->CustomData.GetDefault<Playerwarning>("warning")->warning;

                if (warninggiven == maxwarnings)
                    player->GetSession()->KickPlayer();
                else
                    warninggiven++;

                if (player->GetTeamId() == TEAM_HORDE)
                    player->TeleportTo(1, 1484.36f, -4417.93f, 24.4709f, 0.00f);
                else
                    player->TeleportTo(0, -9075.6650f, 425.8427f, 93.0560f, 0.00f);

            } while (result->NextRow());
        }
    }

    void OnUpdateZone(Player* player, uint32 /*newZone */,  uint32 /*newArea*/)
    {
        if (KeepoutEnabled)
        {
            if (player->GetSession()->GetSecurity() >= SEC_GAMEMASTER)
                return;

            QueryResult result = WorldDatabase.PQuery("SELECT `zoneID` FROM `MapLock` WHERE `zoneID` = '%u'", player->GetZoneId());

            if (!result)
                return;

            do
            {
                CharacterDatabase.PQuery("INSERT INTO `mapexploit` (`player`, `map`, `area`) VALUES ('%s', '%s', '%u')", playername.c_str(), mapname.c_str(), player->GetAreaId());

                ChatHandler(player->GetSession()).PSendSysMessage("You have gone to a forbidden place your actions have been logged.");

                uint32& warninggiven = player->CustomData.GetDefault<Playerwarning>("warning")->warning;

                if (warninggiven == maxwarnings)
                    player->GetSession()->KickPlayer();
                else
                    warninggiven++;

                if (player->GetTeamId() == TEAM_HORDE)
                    player->TeleportTo(1, 1484.36f, -4417.93f, 24.4709f, 0.00f);
                else
                    player->TeleportTo(0, -9075.6650f, 425.8427f, 93.0560f, 0.00f);

            } while (result->NextRow());

        }
    }
};

class Keepout_conf : public WorldScript
{
public:
    Keepout_conf() : WorldScript("Keepout_conf") { }

    void OnBeforeConfigLoad(bool reload) override
    {
        if (!reload) {
            std::string conf_path = _CONF_DIR;
            std::string cfg_file = conf_path + "/mod-keepout.conf";
#ifdef WIN32
            cfg_file = "mod-keepout.conf";
#endif
            std::string cfg_def_file = cfg_file + ".dist";

            sConfigMgr->LoadMore(cfg_def_file.c_str());

            sConfigMgr->LoadMore(cfg_file.c_str());
            maxwarnings = sConfigMgr->GetIntDefault("MaxWarnings", 3);
            KeepoutEnabled = sConfigMgr->GetBoolDefault("KeepOutEnabled", true);

        }
    }
};

void AddKeepOutScripts()
{
    new Keepout_conf();
    new Keepout();
}