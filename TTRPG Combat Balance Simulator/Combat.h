#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>

#include "Character.h"
#include "Console.h"

class Combat
{
private:
	std::vector<Character> Party;
	std::vector<Character> Enemies;

public:
	Combat(){ Console::enableANSI(); }

    bool CanCombat()
    {
        if (Party.empty())
        {
            Console::PrintError("No one in Party! Add someone.");
            return false;
        }

        if (Enemies.empty())
        {
            Console::PrintError("No one to fight! Add someone to fight.");
            return false;
        }

        return true;
    }


	void AddToGroup(bool isMonster);
	void DetermineTurns();
    
    bool AnyPartyDead();
    
    bool IsEnemy(Character* c);
    bool IsPartyMember(Character* c);
   
    bool AllEnemiesDead();
	
    int BeginCombat(bool single);
	int Turn(std::vector<Character*>& cArray);
};