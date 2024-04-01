#ifndef MEMBER_ADDRESS_REL_CONTROLLER_HPP
#define MEMBER_ADDRESS_REL_CONTROLLER_HPP

// Controller to handle Member-Address relation related requests.

// Oatpp includes
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "database/DatabaseClient.hpp"

// App includes
#include "service/relations/MemberAddressRelService.hpp"
#include "dto/database/relations/MemberAddressRelDTO.hpp"
#include "dto/StatusDTO.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) // Begin API Controller codegen

class MemberAddressRelController : public oatpp::web::server::api::ApiController {
private:
    MemberAddressRelService m_memberAddressRelService;

public:
    MemberAddressRelController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper) {}

    static std::shared_ptr<MemberAddressRelController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
    )
    {
        return std::make_shared<MemberAddressRelController>(objectMapper);
    }

    // Endpoint to create a new member-address relation
    ENDPOINT_INFO(createMemberAddressRel) {
        info->summary = "Create new Member-Address relation";
        info->addConsumes<Object<MemberAddressRelDTO>>("application/json");
        info->addResponse<Object<MemberAddressRelDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("MemberAddressRelController");
    }
    ENDPOINT("POST", "member-address-relations", createMemberAddressRel,
        BODY_DTO(Object<MemberAddressRelDTO>, relDTO))
    {
        return createDtoResponse(Status::CODE_200, m_memberAddressRelService.createMemberAddressRel(relDTO));
    }

    // Endpoint to delete a member-address relation
    ENDPOINT_INFO(deleteMemberAddressRel) {
        info->summary = "Delete Member-Address relation";
        info->addResponse<Object<StatusDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("MemberAddressRelController");
    }
    ENDPOINT("DELETE", "member-address-relations/{memberId}/{addressId}", deleteMemberAddressRel,
        PATH(Int64, memberId),
        PATH(Int64, addressId))
    {
        return createDtoResponse(Status::CODE_200, m_memberAddressRelService.deleteMemberAddressRel(memberId, addressId));
    }

    // Endpoint to get all address IDs associated with a member
    ENDPOINT_INFO(getAddressIdsByMemberId) {
        info->summary = "Get all Address IDs associated with a Member";
        info->addResponse<List<Int64>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("MemberAddressRelController");
    }
    ENDPOINT("GET", "member-address-relations/member/{memberId}/addresses", getAddressIdsByMemberId,
        PATH(Int64, memberId))
    {
        return createDtoResponse(Status::CODE_200, m_memberAddressRelService.getAddressIdsByMemberId(memberId));
    }

    // Endpoint to get all member IDs associated with an address
    ENDPOINT_INFO(getMemberIdsByAddressId) {
        info->summary = "Get all Member IDs associated with an Address";
        info->addResponse<List<Int64>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("MemberAddressRelController");
    }
    ENDPOINT("GET", "member-address-relations/address/{addressId}/members", getMemberIdsByAddressId,
        PATH(Int64, addressId))
    {
        return createDtoResponse(Status::CODE_200, m_memberAddressRelService.getMemberIdsByAddressId(addressId));
    }
};

#include OATPP_CODEGEN_END(ApiController) // End API Controller codegen

#endif // MEMBER_ADDRESS_REL_CONTROLLER_HPP
