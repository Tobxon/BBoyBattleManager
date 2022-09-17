// B3M_Testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include <sst_functions.h>

#include <Tournament.hpp>
#include <Team.hpp>

void printLineSeperator(std::ostream&);

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

    printLineSeperator(std::cout);

    //put teams in their starting spot
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

    printLineSeperator(std::cout);

    l_mainTournament.printTeamTable(std::cout);
    
    printLineSeperator(std::cout);
    printLineSeperator(std::cout);
    printLineSeperator(std::cout);

    auto l_firstMatches = l_mainTournament.createCurMatches();

    std::cout << "Matches of Round 1:" << std::endl;
    for (const auto& l_match : l_firstMatches)
    {
        std::cout << "#" << l_match.first << l_match.second.first << " vs. " << l_match.second.second << std::endl;
    }
    printLineSeperator(std::cout);

    std::cout << "Input results of Matches of Round 1:" << std::endl;
    do
    {
        b3m::MatchId l_curId;
        std::cout << "Match Nr:";
        std::cin >> l_curId;

        try
        {
            const auto& l_curMatch = l_firstMatches.at(l_curId);
            
            b3m::Result l_res;
            
            std::cout << l_curMatch.first << ": ";
            std::cin >> l_res.first;
            std::cout << l_curMatch.second << ": ";
            std::cin >> l_res.second;

            if (l_mainTournament.finishMatch(l_curId, l_curMatch, l_res, 1))//TODO roundId
            {
                l_firstMatches.erase(l_curId);
            }
        }
        catch (const std::out_of_range&)
        {
            //not a valid id
            std::cout << "Match Id not found!" << std::endl;
        }
    } while (!l_firstMatches.empty());


    printLineSeperator(std::cout);
    std::cout << "cioa!" << std::endl;
}

void printLineSeperator(std::ostream& i_printSink)
{
    i_printSink << "-----" << std::endl;
}