#include "PhoneNumberService.hpp"

oatpp::Object<PhoneNumberDTO> PhoneNumberService::createPhoneNumber(const oatpp::Object<PhoneNumberDTO>& dto) {
    auto dbResult = m_database->createPhoneNumber(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto phoneNumberId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

    return getPhoneNumberById(phoneNumberId);
}

oatpp::Object<PhoneNumberDTO> PhoneNumberService::updatePhoneNumber(const oatpp::Object<PhoneNumberDTO>& dto) {
    auto dbResult = m_database->updatePhoneNumber(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    return getPhoneNumberById(dto->id);
}

oatpp::Object<PhoneNumberDTO> PhoneNumberService::getPhoneNumberById(const oatpp::Int64& id) {
    auto dbResult = m_database->getPhoneNumberById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Phone number not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<PhoneNumberDTO>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];
}

oatpp::Object<PageDTO<oatpp::Object<PhoneNumberDTO>>> PhoneNumberService::getAllPhoneNumbers(const oatpp::UInt32& offset, const oatpp::UInt32& limit) {
    oatpp::UInt32 countToFetch = limit;

    if (limit > 10) {
        countToFetch = 10;
    }

    auto dbResult = m_database->getAllPhoneNumbers(offset, countToFetch);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<PhoneNumberDTO>>>();

    auto page = PageDTO<oatpp::Object<PhoneNumberDTO>>::createShared();
    page->offset = offset;
    page->limit = countToFetch;
    page->count = items->size();
    page->items = items;

    return page;
}

oatpp::Object<StatusDTO> PhoneNumberService::deletePhoneNumberById(const oatpp::Int64& id) {
    auto dbResult = m_database->deletePhoneNumberById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto status = StatusDTO::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Phone number was successfully deleted";
    return status;
}
