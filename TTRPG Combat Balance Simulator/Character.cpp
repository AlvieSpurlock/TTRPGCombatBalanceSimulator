#include "Character.h"
#include <vector>
#include <algorithm>
#include <iostream>

Character::Character(bool determine, std::string cName, int cLVL, int cHP, int cAC, int cHealthD, int cDamageA, int cDamageB, int cArmorBonus = 0, int cStr, int cDex, int cCon, int cWis, int cChar)
{
	name = cName;
	LVL = cLVL;
	SetHP(determine, cHP);
	SetAC(determine, cAC);
	healthD_Type = cHealthD;
	damageD_TypeA = cDamageA;
	damageD_TypeB = cDamageB;
	ArmorBonus = cArmorBonus;
	SetStat(determine, str, cStr);
	strB = str - 10 / 2;
	SetStat(determine, dex, cDex);
	dexB = dex - 10 / 2;
	SetStat(determine, con, cCon);
	conB = con - 10 / 2;
	SetStat(determine, wis, cWis);
	wisB = wis - 10 / 2;
	SetStat(determine, chari, cChar);
	chariB = chari - 10 / 2;
}

void Character::SetHP(bool determine, int cHP = 0)
{
	if (!determine) { HP = cHP; }
	else
	{
		if (LVL == 1) { HP = healthD_Type + conB; }
		else
		{
			int baseHealthAdd = 0;
			for (size_t index = 0; index < LVL; index++)
			{
				baseHealthAdd = baseHealthAdd + rand() % 10 + conB;
			}
			HP = baseHealthAdd;
		}
	}
}

void Character::SetAC(bool determine, int cAC = 0)
{
	if (!determine) { AC = cAC; }
	else { AC = AC + dexB + ArmorBonus; }
}

void Character::SetStat(bool determine, int& stat, int cStat)
{
	if (!determine) { stat = cStat; }
	else
	{
		std::vector<int> rolls;
		for (size_t index = 0; index < 4; index++)
		{
			rolls.push_back(rand() % 6);
		}

		std::sort(rolls.begin(), rolls.end(), std::greater<int>());
		rolls.pop_back();

		int placeHolder;

		for (size_t index = 0; index < 3; index++)
		{
			placeHolder = placeHolder + rolls[index];
		}
		stat = placeHolder;
	}
};

int Character::RollInitiative()
{
	return rand() % 20;
}

bool Character::Damage(int hit, int damage)
{
	if (hit >= AC)
	{
		HP -= damage;
		if (HP <= 0) { return false; }
		else { return true; }
	}
}

void Character::Heal(int healthAdd)
{
	HP += healthAdd;
}

int Character::RollForAttack()
{
	return rand() % 20;
}
int Character::RollForDamage(bool damageType)
{
	if (damageType){ return rand() % damageD_TypeA; }
	else { return rand() % damageD_TypeB; }
	
}