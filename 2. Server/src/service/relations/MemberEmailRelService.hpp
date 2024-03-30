#ifndef MEMBER_EMAIL_REL_SERVICE_HPP
#define MEMBER_EMAIL_REL_SERVICE_HPP

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include "database/DatabaseClient.hpp"
#include "dto/PageDTO.hpp"
#include "dto/StatusDTO.hpp"

/**
 * Service class for handling operations related to member-email relations.
 */
class MemberEmailRelService {
private:
    typedef oatpp::web::protocol::http::Status Status;            // Define a type alias for HTTP status codes
    OATPP_COMPONENT(std::shared_ptr<DatabaseClient>, m_database); // Inject database component

public:
    /**
     * Creates a new member-email relation.
     * @param rel The member-email relation DTO.
     * @return The created member-email relation.
     */
    oatpp::Object<MemberEmailRelDTO> createMemberEmailRel(const oatpp::Object<MemberEmailRelDTO>& rel);

    /**
     * Deletes a member-email relation.
     * @param memberId The ID of the member.
     * @param emailId The ID of the email.
     * @return The status of the operation.
     */
    oatpp::Object<StatusDTO> deleteMemberEmailRel(const oatpp::Int64& memberId, const oatpp::Int64& emailId);

    /**
     * Retrieves all email IDs associated with a member.
     * @param memberId The ID of the member.
     * @return A list of email IDs.
     */
    oatpp::Vector<oatpp::Int64> getEmailIdsByMemberId(const oatpp::Int64& memberId);

    /**
     * Retrieves all member IDs associated with an email.
     * @param emailId The ID of the email.
     * @return A list of member IDs.
     */
    oatpp::Vector<oatpp::Int64> getMemberIdsByEmailId(const oatpp::Int64& emailId);
};

#endif // MEMBER_EMAIL_REL_SERVICE_HPP
