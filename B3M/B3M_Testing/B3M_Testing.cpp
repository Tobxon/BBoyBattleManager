// B3M_Testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include <sst_functions.h>

#include <Tournament.hpp>
#include <Team.hpp>

int main()
{
    b3m::sst::testPrint(std::cout);

    b3m::Tournament l_mainTournament;

    std::cout << "Enter Team Names - end with empty line:" << std::endl;
    while (true)
    {
        std::string l_userInput;
        std::getline(std::cin, l_userInput);
        if (l_userInput.empty())
        {
            break;
        }

        l_mainTournament.addTeam(l_userInput);
    }

    l_mainTournament.printAllTeamNames(std::cout);

    std::cout << "cioa!" << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
