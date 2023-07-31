//--------------------------------------------------------------------------------------------------
/**
 * \brief Module Interface Unit for the ParticipantDepot class. ParticipantDepot is a class meant to
 *        be a central place to collect participants to be accessible from sub applications
 *        (registration, tournament registration, statistics, ...)
 *
 */


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;


//--------------------------------------------------------------------------------------------------
//------ MODULE CONTENT                                                                       ------
//--------------------------------------------------------------------------------------------------
export module b3m.database:ParticipantsDepot;


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//std
import <optional>;
import <map>;
import <string>;

//b3m
import b3m.common;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
export namespace b3m::database
{



using ParticipantName = std::string;
using Attribute = std::string;
using ParticipantsDepot = std::map< ParticipantName, std::map< Attribute, std::string >>;

//class ParticipantsDepot
//{
//public:
//    using participant_t = b3m::common::Participant;
//
//    void addParticipant(const participant_t::name_t&);
//    void addParticipant(const participant_t&);
//
//    [[nodiscard]] std::optional< participant_t > getParticipantByName(const participant_t::name_t&) const;
//    [[nodiscard]] bool isParticipantExisting(const participant_t::name_t&) const;
//
//    [[nodiscard]] std::size_t numOfParticipants() const;
//};



} //namespace b3m::database


//END OF FILE --------------------------------------------------------------------------------------