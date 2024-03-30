#include "MemberEmailRelService.hpp"

oatpp::Object<MemberEmailRelDTO> MemberEmailRelService::createMemberEmailRel(const oatpp::Object<MemberEmailRelDTO>& rel) {
    auto dbResult = m_database->createMemberEmailRel(rel);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    return rel;
}

oatpp::Object<StatusDTO> MemberEmailRelService::deleteMemberEmailRel(const oatpp::Int64& memberId, const oatpp::Int64& emailId) {
    auto dbResult = m_database->deleteMemberEmailRel(memberId, emailId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto status = StatusDTO::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Member-email relation was successfully deleted";
    return status;
}

oatpp::Vector<oatpp::Int64> MemberEmailRelService::getEmailIdsByMemberId(const oatpp::Int64& memberId) {
    auto dbResult = m_database->getEmailIdsByMemberId(memberId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    return dbResult->fetch<oatpp::Vector<oatpp::Int64>>();
}

oatpp::Vector<oatpp::Int64> MemberEmailRelService::getMemberIdsByEmailId(const oatpp::Int64& emailId) {
    auto dbResult = m_database->getMemberIdsByEmailId(emailId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    return dbResult->fetch<oatpp::Vector<oatpp::Int64>>();
}
