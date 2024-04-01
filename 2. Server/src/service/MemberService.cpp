#include "MemberService.hpp"

oatpp::Object<MemberDTO> MemberService::createMember(const oatpp::Object<MemberDTO>& dto) {
    auto dbResult = m_database->createMember(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto memberId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

    return getMemberById(memberId);
}

oatpp::Object<MemberDTO> MemberService::updateMember(const oatpp::Object<MemberDTO>& dto) {
    auto dbResult = m_database->updateMember(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    return getMemberById(dto->id);
}

oatpp::Object<MemberDTO> MemberService::getMemberById(const oatpp::Int64& id) {
    auto dbResult = m_database->getMemberById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Member not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<MemberDTO>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];
}

oatpp::Object<PageDTO<oatpp::Object<MemberDTO>>> MemberService::getAllMembers(const oatpp::UInt32& offset, const oatpp::UInt32& limit) {
    oatpp::UInt32 countToFetch = limit;

    if (limit > 10) {
        countToFetch = 10;
    }

    auto dbResult = m_database->getAllMembers(offset, countToFetch);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<MemberDTO>>>();

    auto page = PageDTO<oatpp::Object<MemberDTO>>::createShared();
    page->offset = offset;
    page->limit = countToFetch;
    page->count = items->size();
    page->items = items;

    return page;
}

oatpp::Object<StatusDTO> MemberService::deleteMemberById(const oatpp::Int64& id) {
    auto dbResult = m_database->deleteMemberById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto status = StatusDTO::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Member was successfully deleted";
    return status;
}

oatpp::Object<StatusDTO> MemberService::deactivateMemberById(const oatpp::Int64& id) {
    auto dbResult = m_database->deactivateMember(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto status = StatusDTO::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Member was successfully deactivated";
    return status;
}

oatpp::Object<StatusDTO> MemberService::activateMemberById(const oatpp::Int64& id) {
    auto dbResult = m_database->activateMember(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto status = StatusDTO::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Member was successfully activated";
    return status;
}
