#ifndef ADDRESSCONTROLLER_HPP
#define ADDRESSCONTROLLER_HPP

// Controller to handle Address related requests.

// Oatpp includes
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "database/DatabaseClient.hpp"

// App includes
#include "service/AddressService.hpp"
#include "dto/database/AddressDTO.hpp"
#include "dto/StatusDTO.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) // Begin API Controller codegen

class AddressController : public oatpp::web::server::api::ApiController {
private:
    AddressService m_addressService;

public:
    AddressController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper) {}

    static std::shared_ptr<AddressController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
    )
    {
        return std::make_shared<AddressController>(objectMapper);
    }

    // Endpoint to create a new address
    ENDPOINT_INFO(createAddress) {
        info->summary = "Create new Address";
        info->addConsumes<Object<AddressDTO>>("application/json");
        info->addResponse<Object<AddressDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("AddressController");
    }
    ENDPOINT("POST", "addresses", createAddress,
        BODY_DTO(Object<AddressDTO>, addressDTO))
    {
        return createDtoResponse(Status::CODE_200, m_addressService.createAddress(addressDTO));
    }

    // Endpoint to update an existing address
    ENDPOINT_INFO(updateAddress) {
        info->summary = "Update an existing Address";
        info->addConsumes<Object<AddressDTO>>("application/json");
        info->addResponse<Object<AddressDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("AddressController");
    }
    ENDPOINT("PUT", "addresses", updateAddress,
        BODY_DTO(Object<AddressDTO>, addressDTO))
    {
        return createDtoResponse(Status::CODE_200, m_addressService.updateAddress(addressDTO));
    }

    // Endpoint to get an address by ID
    ENDPOINT_INFO(getAddressById) {
        info->summary = "Get Address by ID";
        info->addResponse<Object<AddressDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");

        info->addTag("AddressController");
    }
    ENDPOINT("GET", "addresses/{id}", getAddressById,
        PATH(Int64, id))
    {
        return createDtoResponse(Status::CODE_200, m_addressService.getAddressById(id));
    }

    // Endpoint to delete an address by ID
    ENDPOINT_INFO(deleteAddressById) {
        info->summary = "Delete Address by ID";
        info->addResponse<Object<StatusDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
        info->addTag("AddressController");
    }
    ENDPOINT("DELETE", "addresses/{id}", deleteAddressById,
        PATH(Int64, id))
    {
        return createDtoResponse(Status::CODE_200, m_addressService.deleteAddressById(id));
    }


};

#include OATPP_CODEGEN_END(ApiController) // End API Controller codegen

#endif // ADDRESSCONTROLLER_HPP
