#ifndef TRAININGCONTROLLER_HPP
#define TRAININGCONTROLLER_HPP

// Controller to handle Training related requests.

// Oatpp includes
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "database/DatabaseClient.hpp"

// App includes
#include "service/TrainingService.hpp"
#include "dto/database/TrainingDTO.hpp"
#include "dto/StatusDTO.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) // Begin API Controller codegen

class TrainingController : public oatpp::web::server::api::ApiController {
private:
    TrainingService m_trainingService;

public:
    TrainingController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper) {}

    static std::shared_ptr<TrainingController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
    )
    {
        return std::make_shared<TrainingController>(objectMapper);
    }

    // Endpoint to create a new training
    ENDPOINT_INFO(createTraining) {
        info->summary = "Create new Training";
        info->addConsumes<Object<TrainingDTO>>("application/json");
        info->addResponse<Object<TrainingDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("TrainingController");
    }
    ENDPOINT("POST", "trainings", createTraining,
        BODY_DTO(Object<TrainingDTO>, trainingDTO))
    {
        return createDtoResponse(Status::CODE_200, m_trainingService.createTraining(trainingDTO));
    }

    // Endpoint to update an existing training
    ENDPOINT_INFO(updateTraining) {
        info->summary = "Update an existing Training";
        info->addConsumes<Object<TrainingDTO>>("application/json");
        info->addResponse<Object<TrainingDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("TrainingController");
    }
    ENDPOINT("PUT", "trainings", updateTraining,
        BODY_DTO(Object<TrainingDTO>, trainingDTO))
    {
        return createDtoResponse(Status::CODE_200, m_trainingService.updateTraining(trainingDTO));
    }

    // Endpoint to get a training by ID
    ENDPOINT_INFO(getTrainingById) {
        info->summary = "Get Training by ID";
        info->addResponse<Object<TrainingDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("TrainingController");
    }
    ENDPOINT("GET", "trainings/{id}", getTrainingById,
        PATH(Int64, id))
    {
        return createDtoResponse(Status::CODE_200, m_trainingService.getTrainingById(id));
    }

    // Endpoint to delete a training by ID
    ENDPOINT_INFO(deleteTrainingById) {
        info->summary = "Delete Training by ID";
        info->addResponse<Object<StatusDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("TrainingController");
    }
    ENDPOINT("DELETE", "trainings/{id}", deleteTrainingById,
        PATH(Int64, id))
    {
        return createDtoResponse(Status::CODE_200, m_trainingService.deleteTrainingById(id));
    }
};

#include OATPP_CODEGEN_END(ApiController) // End API Controller codegen

#endif // TRAININGCONTROLLER_HPP
