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
    ENDPOINT("POST", "members", createMember,
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
    ENDPOINT("PUT", "members", updateMember,
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
    ENDPOINT("GET", "members/{id}", getMemberById,
        PATH(Int64, id))
    {
        return createDtoResponse(Status::CODE_200, m_memberService.getMemberById(id));
    }

    // ENDPOINT_INFO(deleteMemberById) {
    //     info->summary = "Delete Member by ID";
    //     info->addResponse<Object<StatusDTO>>(Status::CODE_200, "application/json");
    //     info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
    //     info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
    //     info->addTag("MemberController");
    // }
    // ENDPOINT("DELETE", "members/{id}", deleteMemberById,
    //     PATH(Int64, id))
    // {
    //     return createDtoResponse(Status::CODE_200, m_memberService.deleteMemberById(id));
    // }

    ENDPOINT_INFO(getAllMembers) {
        info->summary = "Get all Members";
        info->addResponse<Object<PageDTO<oatpp::Object<MemberDTO>>>>(
            Status::CODE_200, "application/json"
        );
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("MemberController");
    }
    ENDPOINT("GET", "members", getAllMembers,
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
    ENDPOINT("PUT", "members/{id}/deactivate", deactivateMemberById,
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
    ENDPOINT("PUT", "members/{id}/activate", activateMemberById,
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
