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
import <map>;
import <string>;

//b3m
import b3m.common;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
export namespace b3m::database
{



using participant_t = b3m::common::Participant;
using participantAttributes_t = b3m::common::ParticipantAttributes;
using attribute_t = b3m::common::Attribute;

class ParticipantsDepot
{
public:

    void newParticipant(const participant_t&, const participantAttributes_t& = {});
    bool updateParticipantsAttributes(const participant_t&, const attribute_t&, const std::string&);

private:
        std::map< participant_t, participantAttributes_t> m_participants{};
};



} //namespace b3m::database


//END OF FILE --------------------------------------------------------------------------------------