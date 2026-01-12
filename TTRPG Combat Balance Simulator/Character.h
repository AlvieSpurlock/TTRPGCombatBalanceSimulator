#pragma once
#include <stdlib.h>
class Character
{
private:
	//Basic Stats
	std::string name;
	int LVL = 1;
	int HP = 0;
	int AC = 10;
	int healthD_Type = 4;
	int damageD_TypeA = 4;
	int damageD_TypeB = 4;
	int ArmorBonus = 0;

	//Advanced Stats
	int str = 0;
	int strB = str - 10 / 2;
	int dex = 0;
	int dexB = dex - 10 / 2;
	int con = 0;
	int conB = con - 10 / 2;
	int wis = 0;
	int wisB = wis - 10 / 2;
	int chari = 0;
	int chariB = chari - 10 / 2;

public:
	int turn = 0;

	Character()
	{
		name = "Character";
		LVL = 1;
		HP = 0;
		AC = 10;
		healthD_Type = 4;
		damageD_TypeA = 4;
		damageD_TypeB = 4;
		ArmorBonus = 0;
		str = 0;
		strB = str - 10 / 2;
		dex = 0;
		dexB = dex - 10 / 2;
		con = 0;
		conB = con - 10 / 2;
		wis = 0;
		wisB = wis - 10 / 2;
		chari = 0;
		chariB = chari - 10 / 2;
	}

	Character(bool determine, std::string cName, int cLVL, int cHP, int cAC, int cHealthD, int cDamageA, int cDamageB, int cArmorBonus, int cStr, int cDex, int cCon, int cWis, int cChar);

	void SetHP(bool determine, int cHP = 0);

	void SetAC(bool determine, int cAC = 0);

	void SetStat(bool determine, int& stat, int cStat);

	int RollInitiative();
	bool Damage(int hit, int damage);
	void Heal(int healthAdd);

	int RollForAttack();
	int RollForDamage(bool damageType);

	std::string GetName() { return name; }
	int GetHealth() { return HP; }
};

