#pragma once
#include "Character.h"
#include "Console.h"

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

Character::Character(bool determine, bool cIsMonster)
{
	if(cIsMonster)
	{
		
		LVL = Console::iUserInput("Enemy Level");
		healthD_Type = Console::iUserInput("Health Die");
		damageD_TypeA = Console::iUserInput("Damage Die - Attack One");
		damageD_TypeB = Console::iUserInput("Damage Die - Attack One");
		ArmorBonus = Console::iUserInput("Armor Bonus");
		SetStat(determine, str, Strength);
		strB = (str - 10) / 2;
		SetStat(determine, dex, Dex);
		dexB = (dex - 10) / 2;
		SetStat(determine, con, Con);
		conB = (con - 10) / 2;
		SetStat(determine, wis, Wisdom);
		wisB = (wis - 10) / 2;
		SetStat(determine, chari, Charisma);
		chariB = (chari - 10) / 2;
		SetAC(determine);
		SetHP(determine);
		name = Console::sUserInput("Enemy Name");
	}
	else
	{
		LVL = Console::iUserInput("Character Level");
		healthD_Type = Console::iUserInput("Health Die");
		damageD_TypeA = Console::iUserInput("Damage Die");
		ArmorBonus = Console::iUserInput("Armor Bonus");
		SetStat(determine, str, Strength);
		strB = (str - 10) / 2;
		SetStat(determine, dex, Dex);
		dexB = (dex - 10) / 2;
		SetStat(determine, con, Con);
		conB = (con - 10) / 2;
		SetStat(determine, wis, Wisdom);
		wisB = (wis - 10) / 2;
		SetStat(determine, chari, Charisma);
		chariB = (chari - 10) / 2;
		SetAC(determine);
		SetHP(determine);
		name = Console::sUserInput("Character Name");
	}

	isMonster = isMonster;
}

void Character::SetHP(bool determine)
{
	if (!determine) { HP = Console::iUserInput("HP"); }
	else
	{
		if (LVL == 1) { HP = healthD_Type + conB; }
		else
		{
			int baseHealthAdd = 0;
			for (size_t index = 0; index < LVL; index++)
			{
				baseHealthAdd = baseHealthAdd + (rand() % healthD_Type) + 1 + conB;
			}
			HP = baseHealthAdd;
		}
	}
}

void Character::SetAC(bool determine)
{
	if (!determine) { AC = Console::iUserInput("AC"); }
	else { AC = AC + dexB + ArmorBonus; }
}

void Character::SetStat(bool determine, int& stat, Stats cStat)
{
	if (!determine) 
	{ 
		switch(cStat)
		{
		case Strength:
			stat = Console::iUserInput("Strength");
			break;
		case Dex:
			stat = Console::iUserInput("Dexterity");
			break;
		case Con:
			stat = Console::iUserInput("Constitution");
			break;
		case Wisdom:
			stat = Console::iUserInput("Wisdom");
			break;
		case Charisma:
			stat = Console::iUserInput("Charisma");
			break;
		}
		
	}
	else
	{
		std::vector<int> rolls;
		for (size_t index = 0; index < 4; index++)
		{
			rolls.push_back((rand() % 6) + 1);
		}

		std::sort(rolls.begin(), rolls.end(), std::greater<int>());
		rolls.pop_back();

		int placeHolder = 0;

		for (size_t index = 0; index < 3; index++)
		{
			placeHolder = placeHolder + rolls[index];
		}
		stat = placeHolder;
	}
};

int Character::RollInitiative()
{
	return (rand() % 20) + 1;
}

bool Character::Damage(int hit, int damage)
{
	if (hit >= AC)
	{
		HP -= damage;
		if (HP <= 0) { HP = 0; return false; }
		else { return true; }
	}
	else { return true; }
}

void Character::Heal(int healthAdd)
{
	HP += healthAdd;
}

int Character::RollForAttack()
{
	return (rand() % 20) + 1;
}
int Character::RollForDamage(bool damageType)
{
	if (damageType){ return (rand() % damageD_TypeA) + 1; }
	else { return (rand() % damageD_TypeB) + 1; }
	
}