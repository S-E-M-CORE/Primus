#ifndef MEMBERCONTROLLER_HPP
#define MEMBERCONTROLLER_HPP

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "service/MemberService.hpp"
#include "dto/database/MemberDTO.hpp"
#include "dto/StatusDTO.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) // Begin API Controller codegen

class MemberController : public oatpp::web::server::api::ApiController {
private:
    MemberService m_memberService;

public:
    MemberController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper) {}

    static std::shared_ptr<MemberController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
    )
    {
        return std::make_shared<MemberController>(objectMapper);
    }

    ENDPOINT_INFO(createMember) {
        info->summary = "Create new Member";
        info->addConsumes<Object<MemberDTO>>("application/json");
        info->addResponse<Object<MemberDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("MemberController");
    }
    ENDPOINT("POST", "api/member", createMember,
        BODY_DTO(Object<MemberDTO>, memberDTO))
    {
        return createDtoResponse(Status::CODE_200, m_memberService.createMember(memberDTO));
    }

    ENDPOINT_INFO(updateMember) {
        info->summary = "Update an existing Member";
        info->addConsumes<Object<MemberDTO>>("application/json");
        info->addResponse<Object<MemberDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("MemberController");
    }

    ENDPOINT("PUT", "api/member", updateMember,
        BODY_DTO(Object<MemberDTO>, memberDTO))
    {
        return createDtoResponse(Status::CODE_200, m_memberService.updateMember(memberDTO));
    }

    ENDPOINT_INFO(getMemberById) {
        info->summary = "Get Member by ID";
        info->addResponse<Object<MemberDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("MemberController");
    }

    ENDPOINT("GET", "api/member/{id}", getMemberById,
        PATH(Int64, id))
    {
        return createDtoResponse(Status::CODE_200, m_memberService.getMemberById(id));
    }

    ENDPOINT_INFO(getTotalMemberCount) {
        info->summary = "Get total count of all members";
        info->addResponse<String>(Status::CODE_200, "text/plain");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("MemberController");
    }
    ENDPOINT("GET", "api/members/total/count", getTotalMemberCount) {
        auto count = m_memberService.getMemberCountTotal();
        auto response = createResponse(Status::CODE_200, oatpp::utils::conversion::int32ToStr(count));
        response->putHeader(Header::CONTENT_TYPE, "text/plain");
        return response;
    }

    ENDPOINT_INFO(getMemberCountActive) {
        info->summary = "Get total count of active members";
        info->addResponse<Object<MemberCountDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("MemberController");
    }
    ENDPOINT("GET", "api/members/active/count", getMemberCountActive) {
        return createDtoResponse(
            Status::CODE_200,
            m_memberService.getMemberCountActive()
        );
    }

    ENDPOINT_INFO(getMemberCountInactive) {
        info->summary = "Get total count of inactive members";
        info->addResponse<Object<MemberCountDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("MemberController");
    }
    ENDPOINT("GET", "api/members/inactive/count", getMemberCountInactive) {
        return createDtoResponse(
            Status::CODE_200,
            m_memberService.getMemberCountInactive()
        );
    }

    ENDPOINT_INFO(getAllMembers) {
        info->summary = "Get all Members";
        info->addResponse<Object<PageDTO<oatpp::Object<MemberDTO>>>>(
            Status::CODE_200, "application/json"
        );
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("MemberController");
    }
    ENDPOINT("GET", "api/members/total/all", getAllMembers,
        QUERY(Int32, offset), QUERY(Int32, limit))
    {
        return createDtoResponse(
            Status::CODE_200,
            m_memberService.getAllMembers(static_cast<oatpp::UInt32>(offset), static_cast<oatpp::UInt32>(limit))
        );
    }

    ENDPOINT_INFO(deactivateMemberById) {
        info->summary = "Deactivate Member by ID";
        info->addResponse<Object<StatusDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("MemberController");
    }
    ENDPOINT("PUT", "api/members/{id}/deactivate", deactivateMemberById,
        PATH(Int64, id))
    {
        return createDtoResponse(
            Status::CODE_200,
            m_memberService.deactivateMemberById(id)
        );
    }

    ENDPOINT_INFO(activateMemberById) {
        info->summary = "Activate Member by ID";
        info->addResponse<Object<StatusDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("MemberController");
    }
    ENDPOINT("PUT", "api/members/{id}/activate", activateMemberById,
        PATH(Int64, id))
    {
        return createDtoResponse(
            Status::CODE_200,
            m_memberService.activateMemberById(id)
        );
    }

};

#include OATPP_CODEGEN_END(ApiController) // End API Controller codegen

#endif // MEMBERCONTROLLER_HPP
