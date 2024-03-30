#ifndef MEMBER_TRAINING_REL_CONTROLLER_HPP
#define MEMBER_TRAINING_REL_CONTROLLER_HPP

// Controller to handle Member-Training relation related requests.

// Oatpp includes
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "database/DatabaseClient.hpp"

// App includes
#include "service/relations/MemberTrainingRelService.hpp"
#include "dto/database/relations/MemberTrainingRelDTO.hpp"
#include "dto/StatusDTO.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) // Begin API Controller codegen

class MemberTrainingRelController : public oatpp::web::server::api::ApiController {
private:
    MemberTrainingRelService m_memberTrainingRelService;

public:
    MemberTrainingRelController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper) {}

    static std::shared_ptr<MemberTrainingRelController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
    )
    {
        return std::make_shared<MemberTrainingRelController>(objectMapper);
    }

    // Endpoint to create a new member-training relation
    ENDPOINT_INFO(createMemberTrainingRel) {
        info->summary = "Create new Member-Training relation";
        info->addConsumes<Object<MemberTrainingRelDTO>>("application/json");
        info->addResponse<Object<MemberTrainingRelDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("MemberTrainingRelController");
    }
    ENDPOINT("POST", "member-training-relations", createMemberTrainingRel,
        BODY_DTO(Object<MemberTrainingRelDTO>, relDTO))
    {
        return createDtoResponse(Status::CODE_200, m_memberTrainingRelService.createMemberTrainingRel(relDTO));
    }

    // Endpoint to delete a member-training relation
    ENDPOINT_INFO(deleteMemberTrainingRel) {
        info->summary = "Delete Member-Training relation";
        info->addResponse<Object<StatusDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("MemberTrainingRelController");
    }
    ENDPOINT("DELETE", "member-training-relations/{memberId}/{trainingId}", deleteMemberTrainingRel,
        PATH(Int64, memberId),
        PATH(Int64, trainingId))
    {
        return createDtoResponse(Status::CODE_200, m_memberTrainingRelService.deleteMemberTrainingRel(memberId, trainingId));
    }
};

#include OATPP_CODEGEN_END(ApiController) // End API Controller codegen

#endif // MEMBER_TRAINING_REL_CONTROLLER_HPP
