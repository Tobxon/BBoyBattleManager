//--------------------------------------------------------------------------------------------------
/**
 * \brief Module Interface Unit for the ParticipantsContainer class.
 *
 */


 //--------------------------------------------------------------------------------------------------
 //------ GLOBAL MODULE FRAGMENT                                                               ------
 //--------------------------------------------------------------------------------------------------
module;

//std
#include <set>
#include <ranges>


//--------------------------------------------------------------------------------------------------
//------ MODULE CONTENT                                                                       ------
//--------------------------------------------------------------------------------------------------
export module b3m_database:participants_container;


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

import b3m_common;

//std
//import <set>;
//import <ranges>;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m
{
namespace database
{



export class IParticipantsContainer
{
public:
	virtual ~IParticipantsContainer() noexcept = default; //interface class - meant for polymorphic use

	virtual bool addParticipant(const b3m::common::Participant&) = 0;
	virtual bool removeParticipant(const b3m::common::Participant&) = 0;
};


export class SimpleParticipantsContainer : public IParticipantsContainer
{
public:
	using participant = b3m::common::Participant;

	bool addParticipant(const b3m::common::Participant&) override;
	bool removeParticipant(const b3m::common::Participant&) override;

private:
	static bool cmpParticipantsOnlyName(const participant& i_a, const participant& i_b);
	std::set<participant, bool(*)(const participant&, const participant&)> m_data{ &cmpParticipantsOnlyName };
};



} //namespace database
} //namespace b3m


//END OF FILE --------------------------------------------------------------------------------------