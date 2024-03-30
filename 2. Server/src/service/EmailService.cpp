#include "EmailService.hpp"

oatpp::Object<EmailDTO> EmailService::createEmail(const oatpp::Object<EmailDTO>& dto) {
    auto dbResult = m_database->createEmail(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto emailId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

    return getEmailById(emailId);
}

oatpp::Object<EmailDTO> EmailService::updateEmail(const oatpp::Object<EmailDTO>& dto) {
    auto dbResult = m_database->updateEmail(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    return getEmailById(dto->id);
}

oatpp::Object<EmailDTO> EmailService::getEmailById(const oatpp::Int64& id) {
    auto dbResult = m_database->getEmailById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Email not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<EmailDTO>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];
}

oatpp::Object<PageDTO<oatpp::Object<EmailDTO>>> EmailService::getAllEmails(const oatpp::UInt32& offset, const oatpp::UInt32& limit) {
    oatpp::UInt32 countToFetch = limit;

    if (limit > 10) {
        countToFetch = 10;
    }

    auto dbResult = m_database->getAllEmails(offset, countToFetch);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<EmailDTO>>>();

    auto page = PageDTO<oatpp::Object<EmailDTO>>::createShared();
    page->offset = offset;
    page->limit = countToFetch;
    page->count = items->size();
    page->items = items;

    return page;
}

oatpp::Object<StatusDTO> EmailService::deleteEmailById(const oatpp::Int64& id) {
    auto dbResult = m_database->deleteEmailById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto status = StatusDTO::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Email was successfully deleted";
    return status;
}
