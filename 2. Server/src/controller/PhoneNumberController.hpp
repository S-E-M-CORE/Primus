#ifndef PHONENUMBERCONTROLLER_HPP
#define PHONENUMBERCONTROLLER_HPP

// Controller to handle PhoneNumber related requests.

// Oatpp includes
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "database/DatabaseClient.hpp"

// App includes
#include "service/PhoneNumberService.hpp"
#include "dto/database/PhoneNumberDTO.hpp"
#include "dto/StatusDTO.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) // Begin API Controller codegen

class PhoneNumberController : public oatpp::web::server::api::ApiController {
private:
    PhoneNumberService m_phoneNumberService;

public:
    PhoneNumberController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper) {}

    static std::shared_ptr<PhoneNumberController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
    )
    {
        return std::make_shared<PhoneNumberController>(objectMapper);
    }

    // Endpoint to create a new phone number
    ENDPOINT_INFO(createPhoneNumber) {
        info->summary = "Create new PhoneNumber";
        info->addConsumes<Object<PhoneNumberDTO>>("application/json");
        info->addResponse<Object<PhoneNumberDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("PhoneNumberController");
    }
    ENDPOINT("POST", "phonenumbers", createPhoneNumber,
        BODY_DTO(Object<PhoneNumberDTO>, phoneNumberDTO))
    {
        return createDtoResponse(Status::CODE_200, m_phoneNumberService.createPhoneNumber(phoneNumberDTO));
    }

    // Endpoint to update an existing phone number
    ENDPOINT_INFO(updatePhoneNumber) {
        info->summary = "Update an existing PhoneNumber";
        info->addConsumes<Object<PhoneNumberDTO>>("application/json");
        info->addResponse<Object<PhoneNumberDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("PhoneNumberController");
    }
    ENDPOINT("PUT", "phonenumbers", updatePhoneNumber,
        BODY_DTO(Object<PhoneNumberDTO>, phoneNumberDTO))
    {
        return createDtoResponse(Status::CODE_200, m_phoneNumberService.updatePhoneNumber(phoneNumberDTO));
    }

    // Endpoint to get a phone number by ID
    ENDPOINT_INFO(getPhoneNumberById) {
        info->summary = "Get PhoneNumber by ID";
        info->addResponse<Object<PhoneNumberDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("PhoneNumberController");
    }
    ENDPOINT("GET", "phonenumbers/{id}", getPhoneNumberById,
        PATH(Int64, id))
    {
        return createDtoResponse(Status::CODE_200, m_phoneNumberService.getPhoneNumberById(id));
    }

    // Endpoint to delete a phone number by ID
    ENDPOINT_INFO(deletePhoneNumberById) {
        info->summary = "Delete PhoneNumber by ID";
        info->addResponse<Object<StatusDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("PhoneNumberController");
    }
    ENDPOINT("DELETE", "phonenumbers/{id}", deletePhoneNumberById,
        PATH(Int64, id))
    {
        return createDtoResponse(Status::CODE_200, m_phoneNumberService.deletePhoneNumberById(id));
    }
};

#include OATPP_CODEGEN_END(ApiController) // End API Controller codegen

#endif // PHONENUMBERCONTROLLER_HPP
