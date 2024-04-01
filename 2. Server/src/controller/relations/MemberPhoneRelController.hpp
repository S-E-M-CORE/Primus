#ifndef MEMBER_PHONE_REL_CONTROLLER_HPP
#define MEMBER_PHONE_REL_CONTROLLER_HPP

// Controller to handle Member-Phone relation related requests.

// Oatpp includes
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "database/DatabaseClient.hpp"

// App includes
#include "service/relations/MemberPhoneRelService.hpp"
#include "dto/database/relations/MemberPhoneRelDTO.hpp"
#include "dto/StatusDTO.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) // Begin API Controller codegen

class MemberPhoneRelController : public oatpp::web::server::api::ApiController {
private:
    MemberPhoneRelService m_memberPhoneRelService;

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
        info->addConsumes<Object<MemberPhoneRelDTO>>("application/json");
        info->addResponse<Object<MemberPhoneRelDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("MemberPhoneRelController");
    }
    ENDPOINT("POST", "member-phone-relations", createMemberPhoneRel,
        BODY_DTO(Object<MemberPhoneRelDTO>, relDTO))
    {
        return createDtoResponse(Status::CODE_200, m_memberPhoneRelService.createMemberPhoneRel(relDTO));
    }

    // Endpoint to delete a member-phone relation
    ENDPOINT_INFO(deleteMemberPhoneRel) {
        info->summary = "Delete Member-Phone relation";
        info->addResponse<Object<StatusDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("MemberPhoneRelController");
    }
    ENDPOINT("DELETE", "member-phone-relations/{memberId}/{phoneNumberId}", deleteMemberPhoneRel,
        PATH(Int64, memberId),
        PATH(Int64, phoneNumberId))
    {
        return createDtoResponse(Status::CODE_200, m_memberPhoneRelService.deleteMemberPhoneRel(memberId, phoneNumberId));
    }

    // Endpoint to get all phone numbers associated with a member
    ENDPOINT_INFO(getPhoneNumbersByMemberId) {
        info->summary = "Get all Phone Numbers associated with a Member";
        info->addResponse<List<Int64>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("MemberPhoneRelController");
    }
    ENDPOINT("GET", "member-phone-relations/member/{memberId}/phone-numbers", getPhoneNumbersByMemberId,
        PATH(Int64, memberId))
    {
        return createDtoResponse(Status::CODE_200, m_memberPhoneRelService.getPhoneIdsByMemberId(memberId));
    }

    // Endpoint to get all member IDs associated with a phone number
    ENDPOINT_INFO(getMemberIdsByPhoneNumberId) {
        info->summary = "Get all Member IDs associated with a Phone Number";
        info->addResponse<List<Int64>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("MemberPhoneRelController");
    }
    ENDPOINT("GET", "member-phone-relations/phone-number/{phoneNumberId}/members", getMemberIdsByPhoneNumberId,
        PATH(Int64, phoneNumberId))
    {
        return createDtoResponse(Status::CODE_200, m_memberPhoneRelService.getMemberIdsByPhoneId(phoneNumberId));
    }
};

#include OATPP_CODEGEN_END(ApiController) // End API Controller codegen

#endif // MEMBER_PHONE_REL_CONTROLLER_HPP
