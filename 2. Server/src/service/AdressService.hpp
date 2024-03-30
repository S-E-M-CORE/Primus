#ifndef ADDRESS_SERVICE_HPP
#define ADDRESS_SERVICE_HPP

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include "database/DatabaseClient.hpp"
#include "dto/database/AdressDTO.hpp"
#include "dto/PageDTO.hpp"
#include "dto/StatusDTO.hpp"

/**
 * @brief Service class to handle operations related to addresses.
 */
class AddressService {
private:
    typedef oatpp::web::protocol::http::Status Status; // Define a type alias for HTTP status codes

private:
    OATPP_COMPONENT(std::shared_ptr<DatabaseClient>, m_database); // Inject database component

public:

    /**
     * @brief Creates a new address.
     *
     * @param dto Data transfer object containing address information.
     * @return Object representing the created address.
     */
    oatpp::Object<AddressDTO> createAddress(const oatpp::Object<AddressDTO>& dto);

    /**
     * @brief Updates an existing address.
     *
     * @param dto Data transfer object containing updated address information.
     * @return Object representing the updated address.
     */
    oatpp::Object<AddressDTO> updateAddress(const oatpp::Object<AddressDTO>& dto);

    /**
     * @brief Retrieves an address by ID.
     *
     * @param id ID of the address to retrieve.
     * @return Object representing the retrieved address.
     */
    oatpp::Object<AddressDTO> getAddressById(const oatpp::Int64& id);

    /**
     * @brief Retrieves all addresses with pagination.
     *
     * @param offset Offset for pagination.
     * @param limit Maximum number of items to retrieve.
     * @return Object representing a page of addresses.
     */
    oatpp::Object<PageDTO<oatpp::Object<AddressDTO>>> getAllAddresses(const oatpp::UInt32& offset, const oatpp::UInt32& limit);

    /**
     * @brief Deletes an address by ID.
     *
     * @param id ID of the address to delete.
     * @return Object representing the status of the operation.
     */
    oatpp::Object<StatusDTO> deleteAddressById(const oatpp::Int64& id);
};

#endif // ADDRESS_SERVICE_HPP
