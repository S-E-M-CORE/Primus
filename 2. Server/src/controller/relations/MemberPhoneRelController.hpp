#ifndef MEMBER_PHONE_REL_CONTROLLER_HPP
#define MEMBER_PHONE_REL_CONTROLLER_HPP

// Controller to handle Member-Phone relation related requests.

// Oatpp includes
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "database/DatabaseClient.hpp"

// App includes
#include "service/relations/MemberPhoneNumberRelService.hpp"
#include "dto/database/relations/MemberPhonenumberRelDTO.hpp"
#include "dto/StatusDTO.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) // Begin API Controller codegen

class MemberPhoneRelController : public oatpp::web::server::api::ApiController {
private:
    MemberPhoneNumberRelService m_memberPhoneRelService;

public:
    MemberPhoneRelController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper) {}

    static std::shared_ptr<MemberPhoneRelController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
    )
    {
        return std::make_shared<MemberPhoneRelController>(objectMapper);
    }

    // Endpoint to create a new member-phone relation
    ENDPOINT_INFO(createMemberPhoneRel) {
        info->summary = "Create new Member-Phone relation";
        info->addConsumes<Object<MemberPhonenumberRelDTO>>("application/json");
        info->addResponse<Object<MemberPhonenumberRelDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("MemberPhoneRelController");
    }
    ENDPOINT("POST", "member-phone-relations", createMemberPhoneRel,
        BODY_DTO(Object<MemberPhonenumberRelDTO>, relDTO))
    {
        return createDtoResponse(Status::CODE_200, m_memberPhoneRelService.createMemberPhoneNumberRel(relDTO));
    }

    // Endpoint to delete a member-phone relation
    ENDPOINT_INFO(deleteMemberPhoneRel) {
        info->summary = "Delete Member-Phone relation";
        info->addResponse<Object<StatusDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("MemberPhoneRelController");
    }
    ENDPOINT("DELETE", "member-phone-relations/{memberId}/{phoneId}", deleteMemberPhoneRel,
        PATH(Int64, memberId),
        PATH(Int64, phoneId))
    {
        return createDtoResponse(Status::CODE_200, m_memberPhoneRelService.deleteMemberPhoneNumberRel(memberId, phoneId));
    }
};

#include OATPP_CODEGEN_END(ApiController) // End API Controller codegen

#endif // MEMBER_PHONE_REL_CONTROLLER_HPP
