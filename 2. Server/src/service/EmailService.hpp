#ifndef EMAILSERVICE_HPP
#define EMAILSERVICE_HPP

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include "dto/database/EmailDTO.hpp"
#include "dto/StatusDTO.hpp"
#include "dto/PageDTO.hpp"
#include "database/DatabaseClient.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * @brief Service class to handle operations related to emails.
 */
class EmailService {
private:
    typedef oatpp::web::protocol::http::Status Status; // Define a type alias for HTTP status codes

private:
    OATPP_COMPONENT(std::shared_ptr<DatabaseClient>, m_database); // Inject database component

public:
    oatpp::Object<EmailDTO> createEmail(const oatpp::Object<EmailDTO>& dto);
    oatpp::Object<EmailDTO> updateEmail(const oatpp::Object<EmailDTO>& dto);
    oatpp::Object<EmailDTO> getEmailById(const oatpp::Int64& id);
    oatpp::Object<PageDTO<oatpp::Object<EmailDTO>>> getAllEmails(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
    oatpp::Object<StatusDTO> deleteEmailById(const oatpp::Int64& id);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* EMAILSERVICE_HPP */
