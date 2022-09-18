// B3M_Testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//--------------------------------------------------------------------------------------------------
//Includes                                                                                     -----
//--------------------------------------------------------------------------------------------------

//stl
#include <iostream>
#include <string>

//b3m
#include <Tournament.hpp>
#include <SwissStyleMM.hpp>

//--------------------------------------------------------------------------------------------------
//Declarations                                                                                 -----
//--------------------------------------------------------------------------------------------------

void printLineSeperator(std::ostream&);

//--------------------------------------------------------------------------------------------------
//Implementations                                                                              -----
//--------------------------------------------------------------------------------------------------

int main()
{
    std::cout << "Welcome to B-Boy Battle Manager (B3M)" << std::endl;

    b3m::Tournament l_mainTournament{std::make_unique< b3m::SwissStyleMM >()};

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

        l_mainTournament.addContestant(l_userInput);
    }

    //print Team Names
    std::cout << "Listing all currently registered teams:" << std::endl;
    for (const auto& l_teamName : l_mainTournament.showTeams())
    {
        std::cout << l_teamName << ", ";
    }
    std::cout << std::endl;

    printLineSeperator(std::cout);

    //put teams in their starting spot
    std::cout << "Enter ranking spot for each Team:" << std::endl;
    for (const auto& l_contestant : l_mainTournament.showTeams())
    {
        bool l_spotEntered = false;

        do
        {
            std::cout << l_contestant << ": ";
            unsigned int l_spot;
            std::cin >> l_spot;
            if (!l_mainTournament.setInitialRanking(l_contestant, l_spot))
            {
                std::cout << "Invalid spot entered! Please try again:";
            }
            else
            {
                l_spotEntered = true;
            }
        } while (!l_spotEntered);
    }

    printLineSeperator(std::cout);

    std::cout << "Current ranking:" << std::endl;
    for (const auto& l_contantWithRanking : l_mainTournament.getCurRankings())
    {
        std::cout << "# " << l_contantWithRanking.first << "\t" << l_contantWithRanking.second << std::endl;
    }

    printLineSeperator(std::cout);

    std::cout << "press Enter to start Tournament" << std::endl;
    std::cin.get();
    if (l_mainTournament.start())
    {
        std::cout << "Tournament started!" << std::endl;
    }
    else
    {
        throw;
    }

    const auto l_round = l_mainTournament.startNewRound();

    //auto l_firstMatches = l_mainTournament.createCurMatches();

    //std::cout << "Matches of Round 1:" << std::endl;
    //for (const auto& l_match : l_firstMatches)
    //{
    //    std::cout << "#" << l_match.first << l_match.second.first << " vs. " << l_match.second.second << std::endl;
    //}
    //printLineSeperator(std::cout);

    //std::cout << "Input results of Matches of Round 1:" << std::endl;
    //do
    //{
    //    b3m::MatchId l_curId;
    //    std::cout << "Match Nr:";
    //    std::cin >> l_curId;

    //    try
    //    {
    //        const auto& l_curMatch = l_firstMatches.at(l_curId);
    //        
    //        b3m::Result l_res;
    //        
    //        std::cout << l_curMatch.first << ": ";
    //        std::cin >> l_res.first;
    //        std::cout << l_curMatch.second << ": ";
    //        std::cin >> l_res.second;

    //        if (l_mainTournament.finishMatch(l_curId, l_curMatch, l_res, 1))//TODO roundId
    //        {
    //            l_firstMatches.erase(l_curId);
    //        }
    //    }
    //    catch (const std::out_of_range&)
    //    {
    //        //not a valid id
    //        std::cout << "Match Id not found!" << std::endl;
    //    }
    //} while (!l_firstMatches.empty());


    printLineSeperator(std::cout);
    std::cout << "cioa!" << std::endl;
}

void printLineSeperator(std::ostream& i_printSink)
{
    i_printSink << std::endl << "-----" << std::endl << std::endl;
}