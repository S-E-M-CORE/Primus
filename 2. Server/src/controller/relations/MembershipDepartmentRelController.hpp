#ifndef MEMBERSHIP_DEPARTMENT_REL_CONTROLLER_HPP
#define MEMBERSHIP_DEPARTMENT_REL_CONTROLLER_HPP

// Controller to handle Membership-Department relation related requests.

// Oatpp includes
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "database/DatabaseClient.hpp"

// App includes
#include "service/relations/MembershipDepartmentRelService.hpp"
#include "dto/database/relations/MembershipDepartmentRelDTO.hpp"
#include "dto/StatusDTO.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) // Begin API Controller codegen

class MembershipDepartmentRelController : public oatpp::web::server::api::ApiController {
private:
    MembershipDepartmentRelService m_membershipDepartmentRelService;

public:
    MembershipDepartmentRelController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper) {}

    static std::shared_ptr<MembershipDepartmentRelController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
    )
    {
        return std::make_shared<MembershipDepartmentRelController>(objectMapper);
    }

    // Endpoint to create a new membership-department relation
    ENDPOINT_INFO(createMembershipDepartmentRel) {
        info->summary = "Create new Membership-Department relation";
        info->addConsumes<Object<MembershipDepartmentRelDTO>>("application/json");
        info->addResponse<Object<MembershipDepartmentRelDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("MembershipDepartmentRelController");
    }
    ENDPOINT("POST", "membership-department-relations", createMembershipDepartmentRel,
        BODY_DTO(Object<MembershipDepartmentRelDTO>, relDTO))
    {
        return createDtoResponse(Status::CODE_200, m_membershipDepartmentRelService.createMembershipDepartmentRel(relDTO));
    }

    // Endpoint to delete a membership-department relation
    ENDPOINT_INFO(deleteMembershipDepartmentRel) {
        info->summary = "Delete Membership-Department relation";
        info->addResponse<Object<StatusDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("MembershipDepartmentRelController");
    }
    ENDPOINT("DELETE", "membership-department-relations/{membershipId}/{departmentId}", deleteMembershipDepartmentRel,
        PATH(Int64, membershipId),
        PATH(Int64, departmentId))
    {
        return createDtoResponse(Status::CODE_200, m_membershipDepartmentRelService.deleteMembershipDepartmentRel(membershipId, departmentId));
    }
};

#include OATPP_CODEGEN_END(ApiController) // End API Controller codegen

#endif // MEMBERSHIP_DEPARTMENT_REL_CONTROLLER_HPP
