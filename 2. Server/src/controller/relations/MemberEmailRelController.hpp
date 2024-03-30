#ifndef MEMBER_EMAIL_REL_CONTROLLER_HPP
#define MEMBER_EMAIL_REL_CONTROLLER_HPP

// Controller to handle Member-Email relation related requests.

// Oatpp includes
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "database/DatabaseClient.hpp"

// App includes
#include "service/relations/MemberEmailRelService.hpp"
#include "dto/database/relations/MemberEmailRelDTO.hpp"
#include "dto/StatusDTO.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) // Begin API Controller codegen

class MemberEmailRelController : public oatpp::web::server::api::ApiController {
private:
    MemberEmailRelService m_memberEmailRelService;

public:
    MemberEmailRelController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper) {}

    static std::shared_ptr<MemberEmailRelController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
    )
    {
        return std::make_shared<MemberEmailRelController>(objectMapper);
    }

    // Endpoint to create a new member-email relation
    ENDPOINT_INFO(createMemberEmailRel) {
        info->summary = "Create new Member-Email relation";
        info->addConsumes<Object<MemberEmailRelDTO>>("application/json");
        info->addResponse<Object<MemberEmailRelDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("MemberEmailRelController");
    }
    ENDPOINT("POST", "member-email-relations", createMemberEmailRel,
        BODY_DTO(Object<MemberEmailRelDTO>, relDTO))
    {
        return createDtoResponse(Status::CODE_200, m_memberEmailRelService.createMemberEmailRel(relDTO));
    }

    // Endpoint to delete a member-email relation
    ENDPOINT_INFO(deleteMemberEmailRel) {
        info->summary = "Delete Member-Email relation";
        info->addResponse<Object<StatusDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("MemberEmailRelController");
    }
    ENDPOINT("DELETE", "member-email-relations/{memberId}/{emailId}", deleteMemberEmailRel,
        PATH(Int64, memberId),
        PATH(Int64, emailId))
    {
        return createDtoResponse(Status::CODE_200, m_memberEmailRelService.deleteMemberEmailRel(memberId, emailId));
    }
};

#include OATPP_CODEGEN_END(ApiController) // End API Controller codegen

#endif // MEMBER_EMAIL_REL_CONTROLLER_HPP
