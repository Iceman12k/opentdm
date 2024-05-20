/*
 Copyright (C) 1997-2001 Id Software, Inc.

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

 */

#include "g_local.h"

game_locals_t game;
level_locals_t level;
game_import_t gi;
game_export_t globals;
game_import_ex_t gix;
game_export_ex_t globalsx;
spawn_temp_t st;

int sm_meat_index;
int snd_fry;
int meansOfDeath;

edict_t *g_edicts;
int g_max_clients;

cvar_t *dmflags;
cvar_t *fraglimit;
cvar_t *timelimit;
cvar_t *password;
cvar_t *spectator_password;
cvar_t *maxclients;
cvar_t *maxentities;
cvar_t *g_select_empty;
cvar_t *dedicated;

cvar_t *filterban;

cvar_t *sv_maxvelocity;
cvar_t *sv_gravity;

cvar_t *sv_rollspeed;
cvar_t *sv_rollangle;
cvar_t *gun_x;
cvar_t *gun_y;
cvar_t *gun_z;

cvar_t *run_pitch;
cvar_t *run_roll;
cvar_t *bob_up;
cvar_t *bob_pitch;
cvar_t *bob_roll;

cvar_t *sv_cheats;

cvar_t *flood_msgs;
cvar_t *flood_persecond;
cvar_t *flood_waitdelay;

cvar_t *flood_waves;
cvar_t *flood_waves_perminute;
cvar_t *flood_waves_waitdelay;

cvar_t *sv_maplist;

cvar_t *g_team_a_name;
cvar_t *g_team_b_name;
cvar_t *g_locked_names;

cvar_t *g_team_a_skin;
cvar_t *g_team_b_skin;
cvar_t *g_locked_skins;

cvar_t *g_admin_password;
cvar_t *g_admin_vote_decide;
cvar_t *g_match_time;
cvar_t *g_match_countdown;
cvar_t *g_vote_time;
cvar_t *g_vote_mask;
cvar_t *g_vote_attention;
cvar_t *g_vote_attention_sound;
cvar_t *g_ready_attention;
cvar_t *g_intermission_time;
cvar_t *g_force_screenshot;
cvar_t *g_force_record;
cvar_t *g_record_mvd;
cvar_t *g_weapon_hud;
cvar_t *g_armor_timer;
cvar_t *g_weapon_timer;
cvar_t *g_timeout_limit;
cvar_t *g_timeout_captain;
cvar_t *g_highlight_captain;
cvar_t *g_ping_handicap;

cvar_t *g_tdmflags;
cvar_t *g_itdmflags;
cvar_t *g_1v1flags;

cvar_t *g_itemflags;
cvar_t *g_powerupflags;

cvar_t *g_tdm_allow_pick;

cvar_t *g_fast_weap_switch;
cvar_t *g_teleporter_nofreeze;
cvar_t *g_overtime;
cvar_t *g_tie_mode;
cvar_t *g_gamemode;
cvar_t *g_respawn_time;
cvar_t *g_max_timeout;
cvar_t *g_1v1_timeout;
cvar_t *g_chat_mode;
cvar_t *g_idle_time;

cvar_t *g_http_enabled;
cvar_t *g_http_bind;
cvar_t *g_http_proxy;
cvar_t *g_http_debug;

cvar_t *g_http_path;
cvar_t *g_http_domain;

cvar_t *g_playerconfig_enabled;

cvar_t *g_debug_spawns;

cvar_t *g_max_players_per_team;

cvar_t *g_maplistfile;
cvar_t *g_smartmapfile;
cvar_t *g_motd_message;

cvar_t *g_bugs;

cvar_t *g_allow_name_change_during_match;

cvar_t *g_allow_vote_config;

cvar_t *g_command_mask;

cvar_t *g_auto_rejoin_match;
cvar_t *g_auto_rejoin_map;

cvar_t *g_1v1_spawn_mode;
cvar_t *g_tdm_spawn_mode;

cvar_t *g_respawn_weapon;
cvar_t *g_respawn_ammo;
cvar_t *g_respawn_armor;
cvar_t *g_respawn_health;
cvar_t *g_respawn_quad;
cvar_t *g_respawn_invuln;
cvar_t *g_respawn_backpack;
cvar_t *g_respawn_adren;
cvar_t *g_respawn_ps;
cvar_t *g_respawn_mega;

cvar_t *sv_mvd_enable;

void SpawnEntities(const char *mapname, const char *entities,
        const char *spawnpoint);
void ClientThink(edict_t *ent, usercmd_t *cmd);
qboolean ClientConnect(edict_t *ent, char *userinfo);
void ClientUserinfoChanged(edict_t *ent, char *userinfo);
void ClientDisconnect(edict_t *ent);
void ClientBegin(edict_t *ent);
void ClientCommand(edict_t *ent);
void RunEntity(edict_t *ent);
void DummyWrite(const char *filename, qboolean autosave);
void DummyRead(const char *filename);
void InitGame(void);
void G_RunFrame(void);
char* TDM_MakeServerDemoName(void);

/**
 *
 */
void ShutdownGame(void) {
    gi.dprintf("==== ShutdownGame ====\n");
    gi.cvar_forceset("g_features", "0");
    gi.FreeTags(TAG_LEVEL);
    gi.FreeTags(TAG_GAME);
}

/**
 * Returns a pointer to the structure with all entry points and global
 * variables
 */
DLL_EXPORT game_export_t* GetGameAPI(game_import_t *import) {
    gi = *import;
    globals.apiversion = GAME_API_VERSION;
    globals.Init = InitGame;
    globals.Shutdown = ShutdownGame;
    globals.SpawnEntities = SpawnEntities;
    globals.WriteGame = DummyWrite;
    globals.ReadGame = DummyRead;
    globals.WriteLevel = DummyRead;
    globals.ReadLevel = DummyRead;
    globals.ClientThink = ClientThink;
    globals.ClientConnect = ClientConnect;
    globals.ClientUserinfoChanged = ClientUserinfoChanged;
    globals.ClientDisconnect = ClientDisconnect;
    globals.ClientBegin = ClientBegin;
    globals.ClientCommand = ClientCommand;
    globals.RunFrame = G_RunFrame;
    globals.ServerCommand = ServerCommand;
    globals.edict_size = sizeof(edict_t);
    return &globals;
}

/**
 * Returns a pointer to the structure with all entry points and global
 * variables
 */
DLL_EXPORT game_export_ex_t* GetGameAPIEx(game_import_ex_t *importx) {
    gix = *importx;
    
    globalsx.apiversion = GAME_API_VERSION_EX;
    globalsx.structsize = sizeof(game_export_ex_t);
    globalsx.CustomizeEntityToClient = SV_CustomizeEntityToClient;
    globalsx.EntityVisibleToClient = SV_EntityVisibleToClient;

    return &globalsx;
}

#ifndef GAME_HARD_LINKED
// this is only here so the functions in q_shared.c and q_shwin.c can link
void Sys_Error(const char *error, ...) {
    va_list argptr;
    char text[1024];

    va_start(argptr, error);
    vsnprintf(text, sizeof(text) - 1, error, argptr);
    va_end(argptr);
    gi.error("%s", text);
}

/**
 *
 */
void Com_Printf(const char *msg, int level, ...) {
    va_list argptr;
    char text[1024];

    va_start(argptr, level);
    vsnprintf(text, sizeof(text) - 1, msg, argptr);
    va_end(argptr);
    gi.dprintf("%s", text);
}

#endif

static void G_PredrawGeneric(edict_t *clent, edict_t *ent, customize_entity_t *temp)
{
    if (ent->item && 0) // simple item check
    {
        if (ent->item->simple_model)
        {
            temp->s.modelindex = gi.modelindex(ent->item->simple_model);

            // move up a bit
            temp->s.origin[2] += 8;
            
            // effects
            temp->s.effects &= ~(EF_BOB | EF_ROTATE);
            temp->s.renderfx = RF_FULLBRIGHT;

            // fake billboard
            VectorCopy(clent->client->ps.viewangles, temp->s.angles);
            temp->s.angles[ROLL] = 0;
            temp->s.angles[PITCH] *= -1;
            temp->s.angles[YAW] += 180;
            return;
        }
    }

    if (temp->s.effects & EF_ROTATE)
        temp->s.effects |= EF_BOB;

    if (ent->movetype)
    {
        float xerp_amount = XERP_BASELINE;
        if (ent->owner != clent) // don't ping xerp your own projectiles
            xerp_amount += clent->client->ping / 1000.0; // lots of xerp for dodging
        else
            xerp_amount += min(clent->client->ping / 1000.0, XERP_MAX_XERPCLIENTS);
        xerp_amount = min(xerp_amount, XERP_MAX_PROJECTILEXERP);

        vec3_t start, end, velocity;
        VectorCopy(temp->s.origin, start);
        VectorCopy(ent->velocity, velocity);

        switch (ent->movetype)
        {
            case MOVETYPE_BOUNCE:
            //case MOVETYPE_TOSS:
                xerp_amount = min(xerp_amount, 0.1);
                velocity[2] -= ent->gravity * sv_gravity->value * xerp_amount;
            case MOVETYPE_FLY:
            case MOVETYPE_FLYMISSILE:
                VectorMA(start, xerp_amount, velocity, end);
                if (ent->owner == clent)
                    VectorMA(temp->s.old_origin, xerp_amount, velocity, temp->s.old_origin);
                break;
            default:
                return;
        }

        trace_t trace;
        trace = gi.trace(start, ent->mins, ent->maxs, end, ent, ent->clipmask ? ent->clipmask : MASK_SOLID);
        VectorCopy(trace.endpos, temp->s.origin);
    }
}

qboolean SV_EntityVisibleToClient(edict_t *client, edict_t *ent)
{
    return true;
}

qboolean SV_CustomizeEntityToClient(edict_t *clent, edict_t *ent, customize_entity_t *temp)
{
    if (!ent->client && !ent->movetype)
        return false;

    // copy over base state
    temp->s = ent->s;

    // do predraw if requested
    if (ent->predraw)
    {
        ent->predraw(clent, ent, temp);
    }
    else
    {
        G_PredrawGeneric(clent, ent, temp);
    }

    return true;
}

/**
 *
 */
void ClientEndServerFrames(void) {
    int i;
    edict_t *ent;

    //run now to copy results out to spectators
    for (i = 0; i < game.maxclients; i++) {
        ent = g_edicts + 1 + i;

        if (!ent->inuse || !ent->client) {
            continue;
        }

        if (ent->client->chase_mode == CHASE_LOCK) {
            UpdateLockCam(ent);
            continue;
        } else if (!ent->client->chase_target) {
            continue;
        }

        //this copies before the stats
        UpdateChaseCam(ent);
    }

    // calc the player views now that all pushing
    // and damage has been added
    for (i = 0; i < game.maxclients; i++) {
        ent = g_edicts + 1 + i;
        if (!ent->inuse || !ent->client) {
            continue;
        }
        ClientEndServerFrame(ent);
    }

    //run now to copy results out to spectators
    for (i = 0; i < game.maxclients; i++) {
        ent = g_edicts + 1 + i;

        if (!ent->inuse || !ent->client || !ent->client->chase_target) {
            continue;
        }

        //this copies after the stats
        G_SetSpectatorStats(ent);
    }
}

/**
 * Returns the created target changelevel
 */
edict_t* CreateTargetChangeLevel(char *map) {
    edict_t *ent;

    ent = G_Spawn();
    ent->classname = "target_changelevel";
    Com_sprintf(level.nextmap, sizeof(level.nextmap), "%s", map);
    ent->map = level.nextmap;
    return ent;
}

/**
 * The timelimit or fraglimit has been exceeded
 */
void EndDMLevel(void) {
    edict_t *ent;
    char *s, *t, *f;
    static const char *seps = " ,\n\r";

    // stay on same level flag
    if ((int) dmflags->value & DF_SAME_LEVEL) {
        BeginIntermission(CreateTargetChangeLevel(level.mapname));
        return;
    }

    // see if it's in the map list
    if (*sv_maplist->string) {
        s = strdup(sv_maplist->string);
        f = NULL;
        t = strtok(s, seps);
        while (t != NULL) {
            if (Q_stricmp(t, level.mapname) == 0) {
                // it's in the list, go to the next one
                t = strtok(NULL, seps);
                if (t == NULL) {
                    // end of list, go to first one
                    if (f == NULL) { // there isn't a first one, same level
                        BeginIntermission(
                                CreateTargetChangeLevel(level.mapname));
                    } else {
                        BeginIntermission(CreateTargetChangeLevel(f));
                    }
                } else {
                    BeginIntermission(CreateTargetChangeLevel(t));
                }
                free(s);
                return;
            }
            if (!f) {
                f = t;
            }
            t = strtok(NULL, seps);
        }
        free(s);
    }

    if (level.nextmap[0]) { // go to a specific map
        BeginIntermission(CreateTargetChangeLevel(level.nextmap));
    } else {
        // search for a changelevel
        ent = G_Find(NULL, FOFS(classname), "target_changelevel");
        if (!ent) {
            // the map designer didn't include a changelevel,
            // so create a fake ent that goes back to the same level
            BeginIntermission(CreateTargetChangeLevel(level.mapname));
            return;
        }
        BeginIntermission(ent);
    }
}

/**
 *
 */
void CheckDMRules(void) {
    int i;
    gclient_t *cl;

    if (tdm_match_status == MM_SCOREBOARD) {
        return;
    }

    if (timelimit->value) {
        if (level.framenum >= SECS_TO_FRAMES(timelimit->value * 600)) {
            gi.bprintf(PRINT_HIGH, "Timelimit hit.\n");
            EndDMLevel();
            return;
        }
    }

    if (fraglimit->value) {
        for (i = 0; i < game.maxclients; i++) {
            cl = game.clients + i;
            if (!g_edicts[i + 1].inuse) {
                continue;
            }

            if (cl->resp.score >= fraglimit->value) {
                gi.bprintf(PRINT_HIGH, "Fraglimit hit.\n");
                EndDMLevel();
                return;
            }
        }
    }
}

/**
 *
 */
void ExitLevel(void) {
    char command[256];

    if (level.changemap) {
        Com_sprintf(command, sizeof(command), "gamemap \"%s\"\n",
                level.changemap);
        gi.AddCommandString(command);
        level.exitintermission = 2;
    } else {
        level.exitintermission = 0;
    }
    level.intermissionframe = 0;
    ClientEndServerFrames();
}

/**
 * Advance the world by 0.1 seconds
 */
void G_RunFrame(void) {
    int i;
    edict_t *ent;

    // see if we need to start/stop a server demo
    if (g_record_mvd->modified && game.server_features) {
        g_record_mvd->modified = false;

        if (game.mvd.recording
                && game.mvd.matches >= (int) g_record_mvd->value) {
            gi.AddCommandString("mvdstop\n");
            memset(&game.mvd, 0x0, sizeof(server_demo_t));
        } else if (!game.mvd.recording && tdm_match_status > MM_WARMUP) {
            Q_strncpy(game.mvd.filename, TDM_MakeServerDemoName(),
                    sizeof(game.mvd.filename) - 1);
            gi.AddCommandString(va("mvdrecord %s\n", game.mvd.filename));
            game.mvd.recording = true;
        }
    }

    if (tdm_match_status != MM_TIMEOUT) {
        // exit intermissions
        if (level.exitintermission) {
            if (level.exitintermission == 2) {
                //if we got here, the map change from ExitLevel didn't work
                gi.bprintf(PRINT_CHAT,
                        "ERROR: Map '%s' was not found on the server.\n",
                        level.changemap);
                level.exitintermission = 0;
                TDM_ResetGameState();
            } else {
                ExitLevel();
                return;
            }
        }

        // Treat each object in turn, even the world gets a chance to think
        ent = &g_edicts[0];
        for (i = 0; i < globals.num_edicts; i++, ent++) {
            if (!ent->inuse) {
                continue;
            }
            level.current_entity = ent;
            VectorCopy(ent->old_origin, ent->s.old_origin);

            // if the ground entity moved, make sure we are still on it
            if ((ent->groundentity)
                    && (ent->groundentity->linkcount
                            != ent->groundentity_linkcount)) {
                ent->groundentity = NULL;
            }
            if (i > 0 && i <= game.maxclients) {
                ClientBeginServerFrame(ent);
                continue;
            }
            G_RunEntity(ent);
        }
    }

    HTTP_RunDownloads();
    TDM_UpdateConfigStrings(false);
    TDM_CheckTimes();
    ClientEndServerFrames();    // build the playerstate_t for all players
    level.realframenum++;

    if (tdm_match_status != MM_TIMEOUT) {
        // save old_origins for next frame
        ent = &g_edicts[0];
        for (i = 0; i < globals.num_edicts; i++, ent++) {
            if (ent->inuse) {
                VectorCopy(ent->s.origin, ent->old_origin);
            }
        }
        level.framenum++;
        level.time = level.framenum * FRAMETIME;
    }
}
