#ifndef EMAILCONTROLLER_HPP
#define EMAILCONTROLLER_HPP

// Controller to handle Email related requests.

// Oatpp includes
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

// App includes
#include "service/EmailService.hpp"
#include "dto/database/EmailDTO.hpp"
#include "dto/StatusDTO.hpp"
#include "database/DatabaseClient.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) // Begin API Controller codegen

class EmailController : public oatpp::web::server::api::ApiController {
private:
    EmailService m_emailService;

public:
    EmailController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper) {}

    static std::shared_ptr<EmailController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
    )
    {
        return std::make_shared<EmailController>(objectMapper);
    }

    // Endpoint to create a new email
    ENDPOINT_INFO(createEmail) {
        info->summary = "Create new Email";
        info->addConsumes<Object<EmailDTO>>("application/json");
        info->addResponse<Object<EmailDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("EmailController");
    }
    ENDPOINT("POST", "emails", createEmail,
        BODY_DTO(Object<EmailDTO>, emailDTO))
    {
        return createDtoResponse(Status::CODE_200, m_emailService.createEmail(emailDTO));
    }

    // Endpoint to update an existing email
    ENDPOINT_INFO(updateEmail) {
        info->summary = "Update an existing Email";
        info->addConsumes<Object<EmailDTO>>("application/json");
        info->addResponse<Object<EmailDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("EmailController");
    }
    ENDPOINT("PUT", "emails", updateEmail,
        BODY_DTO(Object<EmailDTO>, emailDTO))
    {
        return createDtoResponse(Status::CODE_200, m_emailService.updateEmail(emailDTO));
    }

    // Endpoint to get an email by ID
    ENDPOINT_INFO(getEmailById) {
        info->summary = "Get Email by ID";
        info->addResponse<Object<EmailDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("EmailController");
    }
    ENDPOINT("GET", "emails/{id}", getEmailById,
        PATH(Int64, id))
    {
        return createDtoResponse(Status::CODE_200, m_emailService.getEmailById(id));
    }

    // Endpoint to delete an email by ID
    ENDPOINT_INFO(deleteEmailById) {
        info->summary = "Delete Email by ID";
        info->addResponse<Object<StatusDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("EmailController");
    }
    ENDPOINT("DELETE", "emails/{id}", deleteEmailById,
        PATH(Int64, id))
    {
        return createDtoResponse(Status::CODE_200, m_emailService.deleteEmailById(id));
    }
};

#include OATPP_CODEGEN_END(ApiController) // End API Controller codegen

#endif // EMAILCONTROLLER_HPP
