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
#include <map>
#include <memory>


//--------------------------------------------------------------------------------------------------
//------ MODULE CONTENT                                                                       ------
//--------------------------------------------------------------------------------------------------
export module b3m.database:participants_container;


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

import b3m.common;

//std
//import <map>;
//import <memory>;


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
	using participant = b3m::common::IParticipant;

	virtual ~IParticipantsContainer() noexcept = default; //interface class - meant for polymorphic use

	virtual bool createParticipant(const participant::name_t&) = 0;
	virtual bool removeParticipant(const participant::name_t&) = 0;
};


export class SimpleParticipantsContainer : public IParticipantsContainer
{
public:
	bool createParticipant(const participant::name_t&) override;
	bool removeParticipant(const participant::name_t&) override;

private:
	std::map< participant::name_t, std::unique_ptr< participant >> m_data;
};



} //namespace database
} //namespace b3m


//END OF FILE --------------------------------------------------------------------------------------