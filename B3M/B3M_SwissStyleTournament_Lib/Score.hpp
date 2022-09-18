#pragma once

//--------------------------------------------------------------------------------------------------
//Includes                                                                                     -----
//--------------------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------------------
//Declarations                                                                                 -----
//--------------------------------------------------------------------------------------------------

namespace b3m
{
//namespace b3m ------------------------------------------------------------------------------------

class Score;

namespace sst {

bool operator==(const Score&, const Score&);
//bool operator>(const Score&, const Score&);

}


//won matches, points from match, free tickets in even tournaments
struct Score
{
	Score() = default;
	explicit Score(int i_wins) : m_wins(i_wins) {}

	friend Score operator+=(Score& i_a, const Score& i_b) 
	{
		i_a.m_wins = i_a.m_wins + i_b.m_wins;
		i_a.m_freeTickets = i_a.m_freeTickets + i_b.m_freeTickets;
		return i_a;
	}

	friend bool sst::operator==(const Score&, const Score&);
	//friend bool sst::operator>(const Score&, const Score&);

	int m_wins{ 0 };
	int m_freeTickets{ 0 };
	//int m_points{ 0 };
};


//end of namespace b3m -----------------------------------------------------------------------------
}
