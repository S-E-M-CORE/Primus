#include "AddressService.hpp"

oatpp::Object<AddressDTO> AddressService::createAddress(const oatpp::Object<AddressDTO>& dto) {
    auto dbResult = m_database->createAddress(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto addressId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

    return getAddressById(addressId);
}

oatpp::Object<AddressDTO> AddressService::updateAddress(const oatpp::Object<AddressDTO>& dto) {
    auto dbResult = m_database->updateAddress(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    return getAddressById(dto->id);
}

oatpp::Object<AddressDTO> AddressService::getAddressById(const oatpp::Int64& id) {
    auto dbResult = m_database->getAddressById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Address not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<AddressDTO>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];
}

oatpp::Object<PageDTO<oatpp::Object<AddressDTO>>> AddressService::getAllAddresses(const oatpp::UInt32& offset, const oatpp::UInt32& limit) {
    size_t offsetSize = offset;
    size_t limitSize = limit;
    oatpp::UInt32 countToFetch = limit;

    if (limitSize > 10) {
        countToFetch = 10;
    }

    auto dbResult = m_database->getAllAddresses(offsetSize, countToFetch);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<AddressDTO>>>();

    auto page = PageDTO<oatpp::Object<AddressDTO>>::createShared();
    page->offset = offset;
    page->limit = countToFetch;
    page->count = items->size();
    page->items = items;

    return page;
}

oatpp::Object<StatusDTO> AddressService::deleteAddressById(const oatpp::Int64& id) {
    auto dbResult = m_database->deleteAddressById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto status = StatusDTO::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Address was successfully deleted";
    return status;
}
