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

    //entering team names
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

    //sorting them by rating
    std::cout << "Enter table spot for each Team:" << std::endl;
    for (const std::string& l_teamName : l_mainTournament.getTeamNames())
    {
        bool l_spotEntered = false;

        do
        {
            std::cout << l_teamName << ": ";
            std::size_t l_spot;
            std::cin >> l_spot;
            if (l_spot > l_mainTournament.getNumOfTeams())
            {
                std::cerr << "table spot too high!" << std::endl;
                l_spotEntered = false;
            }
            else if (!l_mainTournament.setCurSpot(l_teamName, l_spot))
            {
                std::cerr << "table spot already taken!" << std::endl;
                l_spotEntered = false;
            }
            else
            {
                l_spotEntered = true;
            }
        } while (!l_spotEntered);
    }

    l_mainTournament.printTeamTable(std::cout);



    std::cout << "cioa!" << std::endl;
}
