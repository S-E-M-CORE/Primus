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

class MemberAdressRelController : public oatpp::web::server::api::ApiController {
private:
    MemberAddressRelService m_memberAddressRelService;

public:
    MemberAdressRelController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper) {}

    static std::shared_ptr<MemberAdressRelController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
    )
    {
        return std::make_shared<MemberAdressRelController>(objectMapper);
    }

    // Endpoint to create a new member-address relation
    ENDPOINT_INFO(createMemberAddressRel) {
        info->summary = "Create new Member-Address relation";
        info->addConsumes<Object<MemberAddressRelDTO>>("application/json");
        info->addResponse<Object<MemberAddressRelDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("MemberAdressRelController");
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
        info->addTag("MemberAdressRelController");
    }
    ENDPOINT("DELETE", "member-address-relations/{memberId}/{addressId}", deleteMemberAddressRel,
        PATH(Int64, memberId),
        PATH(Int64, addressId))
    {
        return createDtoResponse(Status::CODE_200, m_memberAddressRelService.deleteMemberAddressRel(memberId, addressId));
    }
};

#include OATPP_CODEGEN_END(ApiController) // End API Controller codegen

#endif // MEMBER_ADDRESS_REL_CONTROLLER_HPP
