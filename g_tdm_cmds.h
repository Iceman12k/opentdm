/**
 * TDM command stuff
 */

#define COMMAND_SPECLOCK        0x1

void TDM_Accept_f(edict_t *ent);
void TDM_Acommands_f(edict_t *ent);
void TDM_Admin_f(edict_t *ent);
void TDM_ArmorTimer_f(edict_t *ent);
void TDM_Ban_f(edict_t *ent);
void TDM_Bans_f(edict_t *ent);
void TDM_Bfg_f(edict_t *ent);
void TDM_Break_f(edict_t *ent);
void TDM_Captain_f(edict_t *ent);
void TDM_Captains_f(edict_t *ent);
void TDM_Changemap_f(edict_t *ent);
void TDM_Changeteamstatus_f(edict_t *ent, qboolean ready);
void TDM_CheckSafety(void);
qboolean TDM_Command(const char *cmd, edict_t *ent);
void TDM_Commands_f(edict_t *ent);
void TDM_Forceteam_f(edict_t *ent);
void TDM_Ghost_f(edict_t *ent);
void TDM_Id_f(edict_t *ent);
void TDM_Ignore_f(edict_t *ent, int level);
void TDM_Invite_f(edict_t *ent);
void TDM_Kick_f(edict_t *ent);
void TDM_Kickban_f(edict_t *ent);
void TDM_KickPlayer_f(edict_t *ent);
void TDM_Lockteam_f(edict_t *ent, qboolean lock);
void TDM_Maplist_f(edict_t *ent);
void TDM_Motd_f(edict_t *ent);
void TDM_Mute_f(edict_t *ent);
void TDM_NotReady_f(edict_t *ent);
void TDM_Obsmode_f(edict_t *ent);
void TDM_OldScores_f(edict_t *ent);
void TDM_Overtime_f(edict_t *ent);
void TDM_PickPlayer_f(edict_t *ent);
void TDM_PlayerConfigDisplay_f(edict_t *ent);
void TDM_Powerups_f(edict_t *ent);
void TDM_PrintPlayers(edict_t *ent);
void TDM_SmartMap_f(edict_t *ent);
qboolean TDM_RateLimited(edict_t *ent, int penalty);
void TDM_Ready_f(edict_t *ent);
qboolean TDM_ServerCommand(const char *cmd);
void TDM_ServerDemoRecord_f(edict_t *ent);
void TDM_ServerDemoStop_f(edict_t *ent);
void TDM_Settings_f(edict_t *ent);
char* TDM_SettingsString(void);
void TDM_Shuffle_f(edict_t *ent);
void TDM_ShuffleSmartMaps_f(edict_t *ent);
void TDM_Specinvite_f(edict_t *ent);
void TDM_Speclock_f(edict_t *ent);
void TDM_Spectate_f(edict_t *ent);
void TDM_SV_ApplySettings_f(void);
void TDM_SV_DemoStatus_f(void);
void TDM_SV_SaveDefaults_f(void);
void TDM_SV_Settings_f(void);
void TDM_Talk_f(edict_t *ent);
void TDM_Team_f(edict_t *ent);
void TDM_TeamEnemySkin_f(edict_t *ent, qboolean team);
void TDM_Teamname_f(edict_t *ent);
void TDM_Teamskin_f(edict_t *ent);
void TDM_Test_f(edict_t *ent);
void TDM_Timelimit_f(edict_t *ent);
void TDM_Timeout_f(edict_t *ent);
void TDM_Unban_f(edict_t *ent);
void TDM_Unmute_f(edict_t *ent);
qboolean TDM_ValidateModelSkin(const char *value);
void TDM_WeaponTimer_f(edict_t *ent);
void TDM_Win_f(edict_t *ent);

// reki stuff
void OpenConfigMenu(edict_t *ent);