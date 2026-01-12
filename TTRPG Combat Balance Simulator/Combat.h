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

	void AddToGroup(bool isMonster);
	void DetermineTurns();
	void DuplicateCheck(std::vector<Character>& cArray);

	void BeginCombat();
	bool Turn(std::vector<Character>& cArray);
};