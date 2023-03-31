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
#include <unordered_map>
#include <memory>
#include <optional>




//--------------------------------------------------------------------------------------------------
//------ MODULE CONTENT                                                                       ------
//--------------------------------------------------------------------------------------------------
export module b3m.database:participants_container;


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

import b3m.common;

//std
//import <unordered_map>;
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

	virtual ~IParticipantsContainer() noexcept = default;

	virtual std::size_t numOfParticipant() const = 0;
	virtual std::size_t numOfAttributes() const = 0;

	virtual std::optional< participant::attribute_data_t > readAttributeOfParticipant(
		const participant::name_t&, const participant::attribute_name_t&) = 0; //TODO return std::expected

	virtual bool createParticipant(const participant::name_t&) = 0;
	virtual bool removeParticipant(const participant::name_t&) = 0;

	virtual bool setAttributeOfParticipant(const participant::name_t&,
		const participant::attribute_name_t&, const participant::attribute_element_t&) = 0;
	virtual bool setAttributeOfParticipant(const participant::name_t&, 
		const participant::attribute_name_t&, const participant::attribute_data_t&) = 0;
};


export class SimpleParticipantsContainer : public IParticipantsContainer
{
public:
	std::size_t numOfParticipant() const override;
	std::size_t numOfAttributes() const override;

	std::optional< participant::attribute_data_t > readAttributeOfParticipant(
		const participant::name_t&, const participant::attribute_name_t&) override; 

	bool createParticipant(const participant::name_t&) override;
	bool removeParticipant(const participant::name_t&) override;

	bool setAttributeOfParticipant(const participant::name_t&,
		const participant::attribute_name_t&, const participant::attribute_element_t&);
	bool setAttributeOfParticipant(const participant::name_t&, const participant::attribute_name_t&,
		const participant::attribute_data_t&) override;

private:
	std::vector< std::unique_ptr< participant >> m_participants;
};



} //namespace database
} //namespace b3m


//END OF FILE --------------------------------------------------------------------------------------