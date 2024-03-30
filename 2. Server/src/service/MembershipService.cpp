#include "MembershipService.hpp"

oatpp::Object<MembershipDTO> MembershipService::createMembership(const oatpp::Object<MembershipDTO>& dto) {
    auto dbResult = m_database->createMembership(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto membershipId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

    return getMembershipById(membershipId);
}

oatpp::Object<MembershipDTO> MembershipService::updateMembership(const oatpp::Object<MembershipDTO>& dto) {
    auto dbResult = m_database->updateMembership(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    return getMembershipById(dto->id);
}

oatpp::Object<MembershipDTO> MembershipService::getMembershipById(const oatpp::Int64& id) {
    auto dbResult = m_database->getMembershipById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Membership not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<MembershipDTO>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];
}

oatpp::Object<PageDTO<oatpp::Object<MembershipDTO>>> MembershipService::getAllMemberships(const oatpp::UInt32& offset, const oatpp::UInt32& limit) {
    oatpp::UInt32 countToFetch = limit;

    if (limit > 10) {
        countToFetch = 10;
    }

    auto dbResult = m_database->getAllMemberships(offset, countToFetch);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<MembershipDTO>>>();

    auto page = PageDTO<oatpp::Object<MembershipDTO>>::createShared();
    page->offset = offset;
    page->limit = countToFetch;
    page->count = items->size();
    page->items = items;

    return page;
}

oatpp::Object<StatusDTO> MembershipService::deleteMembershipById(const oatpp::Int64& id) {
    auto dbResult = m_database->deleteMembershipById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto status = StatusDTO::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Membership was successfully deleted";
    return status;
}

oatpp::Object<StatusDTO> MembershipService::deactivateMembershipById(const oatpp::Int64& id) {
    auto dbResult = m_database->deactivateMembership(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto status = StatusDTO::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Membership was successfully deactivated";
    return status;
}

oatpp::Object<StatusDTO> MembershipService::activateMembershipById(const oatpp::Int64& id) {
    auto dbResult = m_database->activateMembership(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto status = StatusDTO::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Membership was successfully activated";
    return status;
}
