#ifndef DEPARTMENTCONTROLLER_HPP
#define DEPARTMENTCONTROLLER_HPP

// Controller to handle Department related requests.

// Oatpp includes
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

// App includes
#include "service/DepartmentService.hpp"
#include "dto/database/DepartmentDTO.hpp"
#include "dto/StatusDTO.hpp"
#include "database/DatabaseClient.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) // Begin API Controller codegen

class DepartmentController : public oatpp::web::server::api::ApiController {
private:
    DepartmentService m_departmentService;

public:
    DepartmentController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper) {}

    static std::shared_ptr<DepartmentController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
    )
    {
        return std::make_shared<DepartmentController>(objectMapper);
    }

    // Endpoint to create a new department
    ENDPOINT_INFO(createDepartment) {
        info->summary = "Create new Department";
        info->addConsumes<Object<DepartmentDTO>>("application/json");
        info->addResponse<Object<DepartmentDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("DepartmentController");
    }
    ENDPOINT("POST", "departments", createDepartment,
        BODY_DTO(Object<DepartmentDTO>, departmentDTO))
    {
        return createDtoResponse(Status::CODE_200, m_departmentService.createDepartment(departmentDTO));
    }

    // Endpoint to update an existing department
    ENDPOINT_INFO(updateDepartment) {
        info->summary = "Update an existing Department";
        info->addConsumes<Object<DepartmentDTO>>("application/json");
        info->addResponse<Object<DepartmentDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("DepartmentController");
    }
    ENDPOINT("PUT", "departments", updateDepartment,
        BODY_DTO(Object<DepartmentDTO>, departmentDTO))
    {
        return createDtoResponse(Status::CODE_200, m_departmentService.updateDepartment(departmentDTO));
    }

    // Endpoint to get a department by ID
    ENDPOINT_INFO(getDepartmentById) {
        info->summary = "Get Department by ID";
        info->addResponse<Object<DepartmentDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("DepartmentController");
    }
    ENDPOINT("GET", "departments/{id}", getDepartmentById,
        PATH(Int64, id))
    {
        return createDtoResponse(Status::CODE_200, m_departmentService.getDepartmentById(id));
    }

    // Endpoint to delete a department by ID
    ENDPOINT_INFO(deleteDepartmentById) {
        info->summary = "Delete Department by ID";
        info->addResponse<Object<StatusDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("DepartmentController");
    }
    ENDPOINT("DELETE", "departments/{id}", deleteDepartmentById,
        PATH(Int64, id))
    {
        return createDtoResponse(Status::CODE_200, m_departmentService.deleteDepartmentById(id));
    }
};

#include OATPP_CODEGEN_END(ApiController) // End API Controller codegen

#endif // DEPARTMENTCONTROLLER_HPP
