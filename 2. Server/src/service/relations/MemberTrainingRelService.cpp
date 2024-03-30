#include "MemberTrainingRelService.hpp"

oatpp::Object<MemberTrainingRelDTO> MemberTrainingRelService::createMemberTrainingRel(const oatpp::Object<MemberTrainingRelDTO>& rel) {
    auto dbResult = m_database->createMemberTrainingRel(rel);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    return rel;
}

oatpp::Object<StatusDTO> MemberTrainingRelService::deleteMemberTrainingRel(const oatpp::Int64& memberId, const oatpp::Int64& trainingId) {
    auto dbResult = m_database->deleteMemberTrainingRel(memberId, trainingId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto status = StatusDTO::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Member-training relation was successfully deleted";
    return status;
}

oatpp::Vector<oatpp::Int64> MemberTrainingRelService::getTrainingIdsByMemberId(const oatpp::Int64& memberId) {
    auto dbResult = m_database->getTrainingIdsByMemberId(memberId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    return dbResult->fetch<oatpp::Vector<oatpp::Int64>>();
}

oatpp::Vector<oatpp::Int64> MemberTrainingRelService::getMemberIdsByTrainingId(const oatpp::Int64& trainingId) {
    auto dbResult = m_database->getMemberIdsByTrainingId(trainingId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    return dbResult->fetch<oatpp::Vector<oatpp::Int64>>();
}
