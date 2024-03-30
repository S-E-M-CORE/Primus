#include "MemberAddressRelService.hpp"

oatpp::Object<MemberAddressRelDTO> MemberAddressRelService::createMemberAddressRel(const oatpp::Object<MemberAddressRelDTO>& rel) {
    auto dbResult = m_database->createMemberAddressRel(rel);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    return rel;
}

oatpp::Object<StatusDTO> MemberAddressRelService::deleteMemberAddressRel(const oatpp::Int64& memberId, const oatpp::Int64& addressId) {
    auto dbResult = m_database->deleteMemberAddressRel(memberId, addressId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto status = StatusDTO::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Member-address relation was successfully deleted";
    return status;
}

oatpp::Vector<oatpp::Int64> MemberAddressRelService::getAddressIdsByMemberId(const oatpp::Int64& memberId) {
    auto dbResult = m_database->getAddressIdsByMemberId(memberId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    return dbResult->fetch<oatpp::Vector<oatpp::Int64>>();
}

oatpp::Vector<oatpp::Int64> MemberAddressRelService::getMemberIdsByAddressId(const oatpp::Int64& addressId) {
    auto dbResult = m_database->getMemberIdsByAddressId(addressId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    return dbResult->fetch<oatpp::Vector<oatpp::Int64>>();
}
