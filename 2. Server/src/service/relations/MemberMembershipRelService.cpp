#include "MemberMembershipRelService.hpp"

oatpp::Object<MemberMembershipRelDTO> MemberMembershipRelService::createMemberMembershipRel(const oatpp::Object<MemberMembershipRelDTO>& rel) {
    auto dbResult = m_database->createMemberMembershipRel(rel);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    return rel;
}

oatpp::Object<StatusDTO> MemberMembershipRelService::deleteMemberMembershipRel(const oatpp::Int64& memberId, const oatpp::Int64& membershipId) {
    auto dbResult = m_database->deleteMemberMembershipRel(memberId, membershipId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto status = StatusDTO::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Member-membership relation was successfully deleted";
    return status;
}

oatpp::Vector<oatpp::Int64> MemberMembershipRelService::getMembershipIdsByMemberId(const oatpp::Int64& memberId) {
    auto dbResult = m_database->getMembershipIdsByMemberId(memberId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    return dbResult->fetch<oatpp::Vector<oatpp::Int64>>();
}

oatpp::Vector<oatpp::Int64> MemberMembershipRelService::getMemberIdsByMembershipId(const oatpp::Int64& membershipId) {
    auto dbResult = m_database->getMemberIdsByMembershipId(membershipId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    return dbResult->fetch<oatpp::Vector<oatpp::Int64>>();
}
