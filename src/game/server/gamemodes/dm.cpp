/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include "dm.h"

#include <game/server/entities/character.h>
#include <game/server/gamecontext.h>
#include <game/server/weapons.h>

CGameControllerDM::CGameControllerDM() :
	IGameController()
{
	m_pGameType = "WTF??";
	m_GameFlags = IGF_SUDDENDEATH;
}

void CGameControllerDM::OnCharacterSpawn(CCharacter *pChr)
{
	pChr->IncreaseHealth(-1);

	pChr->GiveWeapon(WEAPON_GUN, WEAPON_ID_PISTOL, -1);
	pChr->GiveWeapon(WEAPON_HAMMER, WEAPON_ID_HAMMER, -1);
	pChr->GiveWeapon(WEAPON_GRENADE, WEAPON_ID_GRENADE, -1);
	pChr->GiveWeapon(WEAPON_SHOTGUN, WEAPON_ID_SHOTGUN, -1);
	pChr->GiveWeapon(WEAPON_LASER, WEAPON_ID_EXPLODINGLASER, -1);
}
