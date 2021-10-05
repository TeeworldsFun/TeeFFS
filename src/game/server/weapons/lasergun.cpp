#include "lasergun.h"
#include <game/generated/server_data.h>
#include <game/server/entities/laser.h>

CLaserGun::CLaserGun(CCharacter *pOwnerChar) :
	CWeapon(pOwnerChar)
{
	m_MaxAmmo = 100;
	m_AmmoRegenTime = 5;
	m_FireDelay = 100;
	m_FullAuto = true;
}

bool CLaserGun::LaserHit(CLaser *pLaser, vec2 HitPoint, CCharacter *pHit, bool OutOfEnergy)
{
	if(pHit)
	{
		if(pHit->GetPlayer()->GetCID() == pLaser->GetOwner())
			return false;

		pHit->TakeDamage(vec2(0, 0), g_pData->m_Weapons.m_aId[WEAPON_LASER].m_Damage, pLaser->GetOwner(), WEAPON_LASER, pLaser->GetWeaponID(), false);
		return true;
	}

	return false;
}

void CLaserGun::Fire(vec2 Direction)
{
	int ClientID = Character()->GetPlayer()->GetCID();

	new CLaser(
		GameWorld(),
		WEAPON_GUN, //Type
		GetWeaponID(), //WeaponID
		ClientID, //Owner
		Pos(), //Pos
		Direction, //Dir
		g_pData->m_Weapons.m_Laser.m_Reach, // StartEnergy
		LaserHit);

	GameWorld()->CreateSound(Character()->m_Pos, SOUND_WEAPON_SWITCH);
}