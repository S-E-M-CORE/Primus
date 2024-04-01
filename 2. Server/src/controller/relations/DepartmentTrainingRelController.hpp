#ifndef DEPARTMENT_TRAINING_REL_CONTROLLER_HPP
#define DEPARTMENT_TRAINING_REL_CONTROLLER_HPP

// Controller to handle Department-Training relation related requests.

// Oatpp includes
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "database/DatabaseClient.hpp"

// App includes
#include "service/relations/DepartmentTrainingRelService.hpp"
#include "dto/database/relations/DepartmentTrainingRelDTO.hpp"
#include "dto/StatusDTO.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) // Begin API Controller codegen

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

    // Endpoint to create a new department-training relation
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

    // Endpoint to delete a department-training relation
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

    // Endpoint to get all training IDs associated with a department
    ENDPOINT_INFO(getTrainingIdsByDepartmentId) {
        info->summary = "Get all Training IDs associated with a Department";
        info->addResponse<List<Int64>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("DepartmentTrainingRelController");
    }
    ENDPOINT("GET", "department-training-relations/department/{departmentId}/trainings", getTrainingIdsByDepartmentId,
        PATH(Int64, departmentId))
    {
        return createDtoResponse(Status::CODE_200, m_departmentTrainingRelService.getTrainingIdsByDepartmentId(departmentId));
    }

    // Endpoint to get all department IDs associated with a training
    ENDPOINT_INFO(getDepartmentIdsByTrainingId) {
        info->summary = "Get all Department IDs associated with a Training";
        info->addResponse<List<Int64>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("DepartmentTrainingRelController");
    }
    ENDPOINT("GET", "department-training-relations/training/{trainingId}/departments", getDepartmentIdsByTrainingId,
        PATH(Int64, trainingId))
    {
        return createDtoResponse(Status::CODE_200, m_departmentTrainingRelService.getDepartmentIdsByTrainingId(trainingId));
    }
};

#include OATPP_CODEGEN_END(ApiController) // End API Controller codegen

#endif // DEPARTMENT_TRAINING_REL_CONTROLLER_HPP
