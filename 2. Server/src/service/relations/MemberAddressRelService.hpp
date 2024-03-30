#ifndef MEMBER_ADDRESS_REL_SERVICE_HPP
#define MEMBER_ADDRESS_REL_SERVICE_HPP

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include "database/DatabaseClient.hpp"
#include "dto/PageDTO.hpp"
#include "dto/StatusDTO.hpp"

/**
 * Service class for handling operations related to member-address relations.
 */
class MemberAddressRelService {
private:
    typedef oatpp::web::protocol::http::Status Status;            // Define a type alias for HTTP status codes
    OATPP_COMPONENT(std::shared_ptr<DatabaseClient>, m_database); // Inject database component

public:
    /**
     * Creates a new member-address relation.
     * @param rel The member-address relation DTO.
     * @return The created member-address relation.
     */
    oatpp::Object<MemberAddressRelDTO> createMemberAddressRel(const oatpp::Object<MemberAddressRelDTO>& rel);

    /**
     * Deletes a member-address relation.
     * @param memberId The ID of the member.
     * @param addressId The ID of the address.
     * @return The status of the operation.
     */
    oatpp::Object<StatusDTO> deleteMemberAddressRel(const oatpp::Int64& memberId, const oatpp::Int64& addressId);

    /**
     * Retrieves all address IDs associated with a member.
     * @param memberId The ID of the member.
     * @return A list of address IDs.
     */
    oatpp::Vector<oatpp::Int64> getAddressIdsByMemberId(const oatpp::Int64& memberId);

    /**
     * Retrieves all member IDs associated with an address.
     * @param addressId The ID of the address.
     * @return A list of member IDs.
     */
    oatpp::Vector<oatpp::Int64> getMemberIdsByAddressId(const oatpp::Int64& addressId);
};

#endif // MEMBER_ADDRESS_REL_SERVICE_HPP
