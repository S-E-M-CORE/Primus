#ifndef PHONENUMBERSERVICE_HPP
#define PHONENUMBERSERVICE_HPP

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include "dto/database/PhoneNumberDTO.hpp"
#include "dto/StatusDTO.hpp"
#include "dto/PageDTO.hpp"
#include "database/DatabaseClient.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * @brief Service class to handle operations related to phone numbers.
 */
class PhoneNumberService {
private:
    typedef oatpp::web::protocol::http::Status Status; // Define a type alias for HTTP status codes

private:
    OATPP_COMPONENT(std::shared_ptr<DatabaseClient>, m_database); // Inject database component

public:
    oatpp::Object<PhoneNumberDTO> createPhoneNumber(const oatpp::Object<PhoneNumberDTO>& dto);
    oatpp::Object<PhoneNumberDTO> updatePhoneNumber(const oatpp::Object<PhoneNumberDTO>& dto);
    oatpp::Object<PhoneNumberDTO> getPhoneNumberById(const oatpp::Int64& id);
    oatpp::Object<PageDTO<oatpp::Object<PhoneNumberDTO>>> getAllPhoneNumbers(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
    oatpp::Object<StatusDTO> deletePhoneNumberById(const oatpp::Int64& id);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* PHONENUMBERSERVICE_HPP */
