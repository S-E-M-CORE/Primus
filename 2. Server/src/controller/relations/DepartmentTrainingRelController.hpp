#ifndef DEPARTMENT_TRAINING_REL_CONTROLLER_HPP
#define DEPARTMENT_TRAINING_REL_CONTROLLER_HPP

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "database/DatabaseClient.hpp"
#include "service/relations/DepartmentTrainingRelService.hpp"
#include "dto/database/relations/DepartmentTrainingRelDTO.hpp"
#include "dto/StatusDTO.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class DepartmentTrainingRelController : public oatpp::web::server::api::ApiController {
private:
    DepartmentTrainingRelService m_departmentTrainingRelService;

public:
    DepartmentTrainingRelController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper) {}

    static std::shared_ptr<DepartmentTrainingRelController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
    )
    {
        return std::make_shared<DepartmentTrainingRelController>(objectMapper);
    }

    ENDPOINT_INFO(createDepartmentTrainingRel) {
        info->summary = "Create new Department-Training relation";
        info->addConsumes<Object<DepartmentTrainingRelDTO>>("application/json");
        info->addResponse<Object<DepartmentTrainingRelDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("DepartmentTrainingRelController");
    }
    ENDPOINT("POST", "department-training-relations", createDepartmentTrainingRel,
        BODY_DTO(Object<DepartmentTrainingRelDTO>, relDTO))
    {
        return createDtoResponse(Status::CODE_200, m_departmentTrainingRelService.createDepartmentTrainingRel(relDTO));
    }

    ENDPOINT_INFO(deleteDepartmentTrainingRel) {
        info->summary = "Delete Department-Training relation";
        info->addResponse<Object<StatusDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("DepartmentTrainingRelController");
    }
    ENDPOINT("DELETE", "department-training-relations/{departmentId}/{trainingId}", deleteDepartmentTrainingRel,
        PATH(Int64, departmentId),
        PATH(Int64, trainingId))
    {
        return createDtoResponse(Status::CODE_200, m_departmentTrainingRelService.deleteDepartmentTrainingRel(departmentId, trainingId));
    }

};

#include OATPP_CODEGEN_END(ApiController)

#endif // DEPARTMENT_TRAINING_REL_CONTROLLER_HPP
