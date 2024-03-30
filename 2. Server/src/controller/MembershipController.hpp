#ifndef MEMBERSHIPCONTROLLER_HPP
#define MEMBERSHIPCONTROLLER_HPP

// Controller to handle Membership related requests.

// Oatpp includes
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "database/DatabaseClient.hpp"

// App includes
#include "service/MembershipService.hpp"
#include "dto/database/MembershipDTO.hpp"
#include "dto/StatusDTO.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) // Begin API Controller codegen

class MembershipController : public oatpp::web::server::api::ApiController {
private:
    MembershipService m_membershipService;

public:
    MembershipController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper) {}

    static std::shared_ptr<MembershipController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
    )
    {
        return std::make_shared<MembershipController>(objectMapper);
    }

    // Endpoint to create a new membership
    ENDPOINT_INFO(createMembership) {
        info->summary = "Create new Membership";
        info->addConsumes<Object<MembershipDTO>>("application/json");
        info->addResponse<Object<MembershipDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("MembershipController");
    }
    ENDPOINT("POST", "memberships", createMembership,
        BODY_DTO(Object<MembershipDTO>, membershipDTO))
    {
        return createDtoResponse(Status::CODE_200, m_membershipService.createMembership(membershipDTO));
    }

    // Endpoint to update an existing membership
    ENDPOINT_INFO(updateMembership) {
        info->summary = "Update an existing Membership";
        info->addConsumes<Object<MembershipDTO>>("application/json");
        info->addResponse<Object<MembershipDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("MembershipController");
    }
    ENDPOINT("PUT", "memberships", updateMembership,
        BODY_DTO(Object<MembershipDTO>, membershipDTO))
    {
        return createDtoResponse(Status::CODE_200, m_membershipService.updateMembership(membershipDTO));
    }

    // Endpoint to get a membership by ID
    ENDPOINT_INFO(getMembershipById) {
        info->summary = "Get Membership by ID";
        info->addResponse<Object<MembershipDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("MembershipController");
    }
    ENDPOINT("GET", "memberships/{id}", getMembershipById,
        PATH(Int64, id))
    {
        return createDtoResponse(Status::CODE_200, m_membershipService.getMembershipById(id));
    }

    // Endpoint to delete a membership by ID
    ENDPOINT_INFO(deleteMembershipById) {
        info->summary = "Delete Membership by ID";
        info->addResponse<Object<StatusDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("MembershipController");
    }
    ENDPOINT("DELETE", "memberships/{id}", deleteMembershipById,
        PATH(Int64, id))
    {
        return createDtoResponse(Status::CODE_200, m_membershipService.deleteMembershipById(id));
    }
};

#include OATPP_CODEGEN_END(ApiController) // End API Controller codegen

#endif // MEMBERSHIPCONTROLLER_HPP
