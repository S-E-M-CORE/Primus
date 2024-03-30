#ifndef MEMBER_PHONENUMBER_REL_SERVICE_HPP
#define MEMBER_PHONENUMBER_REL_SERVICE_HPP

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include "database/DatabaseClient.hpp"
#include "dto/PageDTO.hpp"
#include "dto/StatusDTO.hpp"

/**
 * Service class for handling operations related to member-phonenumber relations.
 */
class MemberPhoneNumberRelService {
private:
    typedef oatpp::web::protocol::http::Status Status;            // Define a type alias for HTTP status codes
    OATPP_COMPONENT(std::shared_ptr<DatabaseClient>, m_database); // Inject database component

public:
    /**
     * Creates a new member-phonenumber relation.
     * @param rel The member-phonenumber relation DTO.
     * @return The created member-phonenumber relation.
     */
    oatpp::Object<MemberPhonenumberRelDTO> createMemberPhoneNumberRel(const oatpp::Object<MemberPhonenumberRelDTO>& rel);

    /**
     * Deletes a member-phonenumber relation.
     * @param memberId The ID of the member.
     * @param phoneNumberId The ID of the phonenumber.
     * @return The status of the operation.
     */
    oatpp::Object<StatusDTO> deleteMemberPhoneNumberRel(const oatpp::Int64& memberId, const oatpp::Int64& phoneNumberId);

    /**
     * Retrieves all phonenumber IDs associated with a member.
     * @param memberId The ID of the member.
     * @return A list of phonenumber IDs.
     */
    oatpp::Vector<oatpp::Int64> getPhoneNumberIdsByMemberId(const oatpp::Int64& memberId);

    /**
     * Retrieves all member IDs associated with a phonenumber.
     * @param phoneNumberId The ID of the phonenumber.
     * @return A list of member IDs.
     */
    oatpp::Vector<oatpp::Int64> getMemberIdsByPhoneNumberId(const oatpp::Int64& phoneNumberId);
};

#endif // MEMBER_PHONENUMBER_REL_SERVICE_HPP
