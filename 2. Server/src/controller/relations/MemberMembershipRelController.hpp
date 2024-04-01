#ifndef MEMBER_MEMBERSHIP_REL_CONTROLLER_HPP
#define MEMBER_MEMBERSHIP_REL_CONTROLLER_HPP

// Controller to handle Member-Membership relation related requests.

// Oatpp includes
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "database/DatabaseClient.hpp"

// App includes
#include "service/relations/MemberMembershipRelService.hpp"
#include "dto/database/relations/MemberMembershipRelDTO.hpp"
#include "dto/StatusDTO.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) // Begin API Controller codegen

class MemberMembershipRelController : public oatpp::web::server::api::ApiController {
private:
    MemberMembershipRelService m_memberMembershipRelService;

public:
    MemberMembershipRelController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper) {}

    static std::shared_ptr<MemberMembershipRelController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
    )
    {
        return std::make_shared<MemberMembershipRelController>(objectMapper);
    }

    // Endpoint to create a new member-membership relation
    ENDPOINT_INFO(createMemberMembershipRel) {
        info->summary = "Create new Member-Membership relation";
        info->addConsumes<Object<MemberMembershipRelDTO>>("application/json");
        info->addResponse<Object<MemberMembershipRelDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("MemberMembershipRelController");
    }
    ENDPOINT("POST", "member-membership-relations", createMemberMembershipRel,
        BODY_DTO(Object<MemberMembershipRelDTO>, relDTO))
    {
        return createDtoResponse(Status::CODE_200, m_memberMembershipRelService.createMemberMembershipRel(relDTO));
    }

    // Endpoint to delete a member-membership relation
    ENDPOINT_INFO(deleteMemberMembershipRel) {
        info->summary = "Delete Member-Membership relation";
        info->addResponse<Object<StatusDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("MemberMembershipRelController");
    }
    ENDPOINT("DELETE", "member-membership-relations/{memberId}/{membershipId}", deleteMemberMembershipRel,
        PATH(Int64, memberId),
        PATH(Int64, membershipId))
    {
        return createDtoResponse(Status::CODE_200, m_memberMembershipRelService.deleteMemberMembershipRel(memberId, membershipId));
    }

    // Endpoint to get all membership IDs associated with a member
    ENDPOINT_INFO(getMembershipIdsByMemberId) {
        info->summary = "Get all Membership IDs associated with a Member";
        info->addResponse<List<Int64>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("MemberMembershipRelController");
    }
    ENDPOINT("GET", "member-membership-relations/member/{memberId}/memberships", getMembershipIdsByMemberId,
        PATH(Int64, memberId))
    {
        return createDtoResponse(Status::CODE_200, m_memberMembershipRelService.getMembershipIdsByMemberId(memberId));
    }

    // Endpoint to get all member IDs associated with a membership
    ENDPOINT_INFO(getMemberIdsByMembershipId) {
        info->summary = "Get all Member IDs associated with a Membership";
        info->addResponse<List<Int64>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("MemberMembershipRelController");
    }
    ENDPOINT("GET", "member-membership-relations/membership/{membershipId}/members", getMemberIdsByMembershipId,
        PATH(Int64, membershipId))
    {
        return createDtoResponse(Status::CODE_200, m_memberMembershipRelService.getMemberIdsByMembershipId(membershipId));
    }
};

#include OATPP_CODEGEN_END(ApiController) // End API Controller codegen

#endif // MEMBER_MEMBERSHIP_REL_CONTROLLER_HPP
