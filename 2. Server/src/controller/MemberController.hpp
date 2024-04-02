#ifndef MEMBERCONTROLLER_HPP
#define MEMBERCONTROLLER_HPP

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "service/MemberService.hpp"
#include "dto/StatusDto.hpp"
#include "dto/DatabaseDtos.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) // Begin API Controller codegen

class MemberController : public oatpp::web::server::api::ApiController
{
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



};

#include OATPP_CODEGEN_END(ApiController) // End API Controller codegen

#endif // MEMBERCONTROLLER_HPP
