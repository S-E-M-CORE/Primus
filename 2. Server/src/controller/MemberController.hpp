#ifndef MEMBERCONTROLLER_HPP
#define MEMBERCONTROLLER_HPP

//  __  __                _                      
// |  \/  | ___ _ __ ___ | |__   ___ _ __        
// | |\/| |/ _ \ '_ ` _ \| '_ \ / _ \ '__|       
// | |  | |  __/ | | | | | |_) |  __/ |          
// |_|__|_|\___|_| |_| |_|_.__/ \___|_|          
//  / ___|___  _ __ | |_ _ __ ___ | | | ___ _ __ 
// | |   / _ \| '_ \| __| '__/ _ \| | |/ _ \ '__|
// | |__| (_) | | | | |_| | | (_) | | |  __/ |   
//  \____\___/|_| |_|\__|_|  \___/|_|_|\___|_|   

// Controller to handle Member related requests.

// Oatpp includes
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "sqlite/DatabaseClient.hpp"

// App includes
#include "service/MemberService.hpp"
#include "dto/databaseDTOs/MemberDTO.hpp"
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
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
    }

    ENDPOINT("POST", "members", createMember,
        BODY_DTO(Object<MemberDTO>, memberDTO))
    {
        return createDtoResponse(Status::CODE_200, m_memberService.createMember(memberDTO));
    }

};

#include OATPP_CODEGEN_END(ApiController) // End API Controller codegen

#endif // MEMBERCONTROLLER_HPP
