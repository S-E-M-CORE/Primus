#ifndef MEMBERSHIPSERVICE_HPP
#define MEMBERSHIPSERVICE_HPP

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"


#include "dto/database/MembershipDTO.hpp"
#include "dto/StatusDTO.hpp"
#include "dto/PageDTO.hpp"
#include "database/DatabaseClient.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * @brief Service class to handle operations related to memberships.
 */
class MembershipService {
private:
    typedef oatpp::web::protocol::http::Status Status; // Define a type alias for HTTP status codes

private:
    OATPP_COMPONENT(std::shared_ptr<DatabaseClient>, m_database); // Inject database component

public:
    oatpp::Object<MembershipDTO> createMembership(const oatpp::Object<MembershipDTO>& dto);
    oatpp::Object<MembershipDTO> updateMembership(const oatpp::Object<MembershipDTO>& dto);
    oatpp::Object<MembershipDTO> getMembershipById(const oatpp::Int64& id);
    oatpp::Object<PageDTO<oatpp::Object<MembershipDTO>>> getAllMemberships(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
    oatpp::Object<StatusDTO> deleteMembershipById(const oatpp::Int64& id);
    oatpp::Object<StatusDTO> deactivateMembershipById(const oatpp::Int64& id);
    oatpp::Object<StatusDTO> activateMembershipById(const oatpp::Int64& id);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* MEMBERSHIPSERVICE_HPP */
