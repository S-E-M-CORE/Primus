#include "MemberPhoneNumberRelService.hpp"

oatpp::Object<MemberPhonenumberRelDTO> MemberPhoneNumberRelService::createMemberPhoneNumberRel(const oatpp::Object<MemberPhonenumberRelDTO>& rel) {
    auto dbResult = m_database->createMemberPhoneNumberRel(rel);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    return rel;
}

oatpp::Object<StatusDTO> MemberPhoneNumberRelService::deleteMemberPhoneNumberRel(const oatpp::Int64& memberId, const oatpp::Int64& phoneNumberId) {
    auto dbResult = m_database->deleteMemberPhoneNumberRel(memberId, phoneNumberId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto status = StatusDTO::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Member-phonenumber relation was successfully deleted";
    return status;
}

oatpp::Vector<oatpp::Int64> MemberPhoneNumberRelService::getPhoneNumberIdsByMemberId(const oatpp::Int64& memberId) {
    auto dbResult = m_database->getPhoneNumberIdsByMemberId(memberId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    return dbResult->fetch<oatpp::Vector<oatpp::Int64>>();
}

oatpp::Vector<oatpp::Int64> MemberPhoneNumberRelService::getMemberIdsByPhoneNumberId(const oatpp::Int64& phoneNumberId) {
    auto dbResult = m_database->getMemberIdsByPhoneNumberId(phoneNumberId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    return dbResult->fetch<oatpp::Vector<oatpp::Int64>>();
}
