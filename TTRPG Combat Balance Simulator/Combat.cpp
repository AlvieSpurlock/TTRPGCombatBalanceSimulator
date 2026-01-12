#include "Combat.h"

void Combat::AddToGroup(bool isMonster)
{
	if (!isMonster) { Console::PrintHeader("Character Maker"); }
	else { Console::PrintHeader("Monster Maker"); }
	
	int determineComp = 0;
	int val;
	bool determine;

	Console::SetQuestion();
	std::cout << "\n" << "Do you need stats determined?";

	Console::PrintNumber(1);
	Console::PrintData("Y, ");
	
	Console::PrintNumber(2);
	Console::PrintData("N, ");
	
	Console::SetAnswer();
	std::cin >> val;
	std::cout << "\n";

	if (determineComp == 1) { determine = true; }
	else { determine = false; }

	Character placeHolder(determine, Console::sUserInput("Character Name"), Console::iUserInput("Character Level"), Console::iUserInput("HP"), Console::iUserInput("AC"), Console::iUserInput("Health Dice"), Console::iUserInput("Damage Dice - A"), Console::iUserInput("Enemies Only - Damage Dice - B"), Console::iUserInput("Armor Bonus"), Console::iUserInput("Strength"), Console::iUserInput("Dexterity"), Console::iUserInput("Consitution"), Console::iUserInput("Wisdom"), Console::iUserInput("Charisma"));
	
	if (!isMonster) { Party.push_back(placeHolder); }
	else { Enemies.push_back(placeHolder); }
	
}

void Combat::DuplicateCheck(std::vector<Character>& cArray)
{
	std::vector<int> tempArray;
	int tempInit = 0;
	for (auto& character : cArray)
	{
		tempInit = character.RollInitiative();
		for (auto& num : tempArray)
		{
			if (tempInit == num) { DuplicateCheck(cArray); }
		}
		tempArray.push_back(tempInit);
		std::sort(tempArray.begin(), tempArray.end(), std::greater<int>());
		for (size_t index = 0; index < tempArray.size() - 1; index++)
		{
			character.turn = index;
		}
	}

}

void Combat::DetermineTurns()
{
	DuplicateCheck(Party);
	DuplicateCheck(Enemies);
}

bool Combat::BeginCombat()
{
	std::vector<Character>& combatOrder = Party;
	combatOrder.clear();
	combatOrder.shrink_to_fit();
	int size = Party.size() + Enemies.size();
	combatOrder.resize(size);
	DetermineTurns();
	for (auto& character : Party)
	{
		combatOrder[character.turn] = character;
	}
	for (auto& character : Enemies)
	{
		combatOrder[character.turn] = character;
	}
}
