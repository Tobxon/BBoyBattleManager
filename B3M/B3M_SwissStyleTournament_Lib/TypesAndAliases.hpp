#pragma once

//--------------------------------------------------------------------------------------------------
//Includes                                                                                     -----
//--------------------------------------------------------------------------------------------------

//stl
#include <string>

namespace b3m
{


//ALiases
using Contestant = std::string; //TODO
using Ranking = unsigned int;
using Match = std::pair< Contestant, Contestant >; //TODO maybe to class to show if a match is running or finished + MatchId?


}