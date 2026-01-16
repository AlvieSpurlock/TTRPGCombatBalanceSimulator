#include "Combat.h"
#include <algorithm>
#include <iostream>

void Combat::AddToGroup(bool isMonster)
{
    if (!isMonster) 
    { Console::PrintHeader("Character Maker"); }
   
    else 
    { Console::PrintHeader("Monster Maker"); }

    int determineComp = 0;
    bool determine = true;

    Console::SetQuestion();
    std::cout << "\nDo you need stats determined?";

    Console::PrintNumber(1); Console::PrintData("Y ");
    Console::PrintNumber(2); Console::PrintData("N ");

    Console::SetAnswer();
    determineComp = Console::iUserInput("Answer");
    std::cout << "\n";

    determine = (determineComp == 1);

    Character placeHolder(determine, isMonster);

    if (!isMonster)
    { Party.push_back(placeHolder); }
    else { Enemies.push_back(placeHolder); }
}

void Combat::DetermineTurns()
{
    std::vector<Character*> all;

    for (auto& c : Party) 
    { all.push_back(&c); }
    
    for (auto& c : Enemies) 
    { all.push_back(&c); }

    std::vector<int> used;

    for (auto* c : all)
    {
        int init = c->RollInitiative();
        while (std::find(used.begin(), used.end(), init) != used.end())
        { init = c->RollInitiative(); }

        used.push_back(init);
        c->turn = init;
    }

    std::sort(all.begin(), all.end(),
        [](const Character* a, const Character* b)
        {return a->turn > b->turn;
        });

    for (int i = 0; i < static_cast<int>(all.size()); ++i)
    { all[i]->turn = i; }
}

bool Combat::AllEnemiesDead()
{
    for (auto& e : Enemies)
        if (e.GetHealth() > 0) { return false; }
    return true;
}

bool Combat::AnyPartyDead()
{
    for (auto& p : Party)
        if (p.GetHealth() <= 0) { return true; }
    return false;
}

bool Combat::IsPartyMember(Character* c)
{
    for (auto& p : Party)
        if (&p == c) { return true; }
    return false;
}

bool Combat::IsEnemy(Character* c)
{
    for (auto& e : Enemies)
        if (&e == c) { return true; }
    return false;
}

int Combat::BeginCombat(bool single)
{
    std::vector<int> PartyHealth;
    std::vector<int> EnemyHealth;

    for (auto& c : Party) 
    { PartyHealth.push_back(c.GetHealth()); }
    for (auto& c : Enemies) 
    { EnemyHealth.push_back(c.GetHealth()); }

    DetermineTurns();

    int size = static_cast<int>(Party.size() + Enemies.size());
    std::vector<Character*> combatOrder(size);

    for (auto& c : Party)
    { combatOrder[c.turn] = &c; }

    for (auto& c : Enemies)
    { combatOrder[c.turn] = &c; }

    int result = 2;
    while (result == 2) { result = Turn(combatOrder); }

    if (single)
    {
        if (result == 0)
        {
            for (auto& c : Party)
                Console::PrintData(c.GetName() + ": " + std::to_string(c.GetHealth()));
            for (auto& c : Enemies)
                Console::PrintData(c.GetName() + ": " + std::to_string(c.GetHealth()));
        }
    }

    for (size_t i = 0; i < Party.size(); ++i)
    { Party[i].SetHP_Debug(PartyHealth[i]); }
       
    for (size_t i = 0; i < Enemies.size(); ++i)
    { Enemies[i].SetHP_Debug(EnemyHealth[i]); }

    return result;
}

int Combat::Turn(std::vector<Character*>& cArray)
{
    for (Character* actor : cArray)
    {
        if (!actor) continue;
        if (actor->GetHealth() <= 0) continue;

        if (IsPartyMember(actor))
        {
            if (AllEnemiesDead()) { return 1; }

            int idx = -1;
            for (int tries = 0; tries < 10; ++tries)
            {
                int candidate = rand() % Enemies.size();
                if (Enemies[candidate].GetHealth() > 0)
                {
                    idx = candidate;
                    break;
                }
            }
            if (idx == -1)
                continue;

            Enemies[idx].Damage(
                actor->RollForAttack(),
                actor->RollForDamage(true));

            if (AllEnemiesDead()) { return 1; }
        }

        else if (IsEnemy(actor))
        {
            if (AnyPartyDead()) { return 0; }

            int idx = -1;
            for (int tries = 0; tries < 10; ++tries)
            {
                int candidate = rand() % Party.size();
                if (Party[candidate].GetHealth() > 0)
                {
                    idx = candidate;
                    break;
                }
            }
            if (idx == -1) { continue; }

            bool alive = Party[idx].Damage(
                actor->RollForAttack(),
                actor->RollForDamage(rand() % 2 == 0));

            if (!alive) { return 0; }
        }
    }

    return 2;
}
