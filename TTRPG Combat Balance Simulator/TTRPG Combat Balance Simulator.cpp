#include <iostream>

#include "Combat.h"
#include "Console.h"
Combat combat;

double Sim()
{
    double wins = 0;
    for (size_t index = 0; index < 1500; index++)
    {
        if (combat.BeginCombat(false) == 1)
            wins++;
    } return wins / 1500.0;
}

double MonteCarlo()
{
    std::vector<double> avs;
    double simResult = 0;

    for (size_t index = 0; index < 150; index++)
    {
        Console::PrintHeader("Simulation Batch " + std::to_string(index));

        simResult = Sim();
        double percent = simResult * 100.0;

        Console::PrintData(
            "Batch Win Rate: " +
            std::to_string(percent).substr(0, 5) + "%"
        );

        Console::PrintData("------------------------------");

        avs.push_back(simResult);
    }

    double total = 0;
    for (auto& avg : avs)
        total += avg;

    double finalAvg = total / 150.0;
    double finalPercent = finalAvg * 100.0;

    Console::PrintHeader("Monte Carlo Summary");
    Console::PrintData(
        "Overall Win Chance: " +
        std::to_string(finalPercent).substr(0, 5) + "%"
    );

    return finalAvg;
}

void UserInput()
{
    Console::PrintHeader("TTRPG Combat Balancer");
    Console::PrintNumber(1); Console::PrintData("Add Party Member");
    Console::PrintNumber(2); Console::PrintData("Add Enemy");
    Console::PrintNumber(3); Console::PrintData("Single Combat");
    Console::PrintNumber(4); Console::PrintData("Full Simulation");
    switch (Console::iUserInput("Answer(Number)"))
    {
    case 1:
    {
        combat.AddToGroup(false);
        UserInput();
        break;
    }
    case 2:
    {
        combat.AddToGroup(true);
        UserInput();
        break;
    }
    case 3:
    {
        int battle = combat.BeginCombat(true);

        if (battle == 1) { Console::PrintData("Balanced - Everyone Lived"); }
        else { if (battle == 0) { Console::PrintData("Unbalanced - Someone Died"); } }
        UserInput();
        break;
    }
    case 4:
    {
        if (combat.CanCombat()) { MonteCarlo(); }
        break;
    }
    default:
    {
        Console::PrintError("Nothing Entered. Try Again!");
        UserInput();
        break;
    }
    }
}

int main()
{
    UserInput();
}