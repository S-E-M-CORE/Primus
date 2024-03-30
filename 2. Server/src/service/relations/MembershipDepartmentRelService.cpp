#include "MembershipDepartmentRelService.hpp"

oatpp::Object<MembershipDepartmentRelDTO> MembershipDepartmentRelService::createMembershipDepartmentRel(const oatpp::Object<MembershipDepartmentRelDTO>& rel) {
    auto dbResult = m_database->createMembershipDepartmentRel(rel);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    return rel;
}

oatpp::Object<StatusDTO> MembershipDepartmentRelService::deleteMembershipDepartmentRel(const oatpp::Int64& membershipId, const oatpp::Int64& departmentId) {
    auto dbResult = m_database->deleteMembershipDepartmentRel(membershipId, departmentId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto status = StatusDTO::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Membership-department relation was successfully deleted";
    return status;
}

oatpp::Vector<oatpp::Int64> MembershipDepartmentRelService::getDepartmentIdsByMembershipId(const oatpp::Int64& membershipId) {
    auto dbResult = m_database->getDepartmentIdsByMembershipId(membershipId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    return dbResult->fetch<oatpp::Vector<oatpp::Int64>>();
}

oatpp::Vector<oatpp::Int64> MembershipDepartmentRelService::getMembershipIdsByDepartmentId(const oatpp::Int64& departmentId) {
    auto dbResult = m_database->getMembershipIdsByDepartmentId(departmentId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    return dbResult->fetch<oatpp::Vector<oatpp::Int64>>();
}
