#ifndef MEMBER_MEMBERSHIP_REL_SERVICE_HPP
#define MEMBER_MEMBERSHIP_REL_SERVICE_HPP

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "database/DatabaseClient.hpp"
#include "dto/database/relations/MemberMembershipRelDTO.hpp"
#include "dto/StatusDTO.hpp"

/**
 * Service class for handling operations related to member-membership relations.
 */
class MemberMembershipRelService {
private:
    typedef oatpp::web::protocol::http::Status Status;            // Define a type alias for HTTP status codes
    OATPP_COMPONENT(std::shared_ptr<DatabaseClient>, m_database); // Inject database component

public:
    /**
     * Creates a new member-membership relation.
     * @param rel The member-membership relation DTO.
     * @return The created member-membership relation.
     */
    oatpp::Object<MemberMembershipRelDTO> createMemberMembershipRel(const oatpp::Object<MemberMembershipRelDTO>& rel);

    /**
     * Deletes a member-membership relation.
     * @param memberId The ID of the member.
     * @param membershipId The ID of the membership.
     * @return The status of the operation.
     */
    oatpp::Object<StatusDTO> deleteMemberMembershipRel(const oatpp::Int64& memberId, const oatpp::Int64& membershipId);

    /**
     * Retrieves all membership IDs associated with a member.
     * @param memberId The ID of the member.
     * @return A list of membership IDs.
     */
    oatpp::Vector<oatpp::Int64> getMembershipIdsByMemberId(const oatpp::Int64& memberId);

    /**
     * Retrieves all member IDs associated with a membership.
     * @param membershipId The ID of the membership.
     * @return A list of member IDs.
     */
    oatpp::Vector<oatpp::Int64> getMemberIdsByMembershipId(const oatpp::Int64& membershipId);
};

#endif // MEMBER_MEMBERSHIP_REL_SERVICE_HPP
