#include "MemberService.hpp"

#pragma warning(suppress: 4267)

oatpp::Object<MemberDTO> MemberService::createMember(const oatpp::Object<MemberDTO>& DTO)
{
    auto dbResult = m_database->createMember(DTO);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto MemberId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

    return getMemberById((v_int64)MemberId);

}

oatpp::Object<MemberDTO> MemberService::updateMember(const oatpp::Object<MemberDTO>& DTO)
{

    auto dbResult = m_database->updateMember(DTO);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    return getMemberById(DTO->id);

}

oatpp::Object<MemberDTO> MemberService::getMemberById(const oatpp::Int64& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection)
{
    auto dbResult = m_database->getMemberById(id, connection);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Member not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<MemberDTO>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];

}


oatpp::Object<StatusDTO> MemberService::deleteMemberById(const oatpp::Int64& id)
{
    auto dbResult = m_database->deleteMemberById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto status = StatusDTO::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Member was successfully deleted";
    return status;
}

oatpp::Object<StatusDTO> MemberService::deactivateMemberById(const oatpp::Int64& id)
{
    auto dbResult = m_database->deactivateMember(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto status = StatusDTO::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Member was successfully deactivated";
    return status;
}

