#ifndef MEMBERSERVICE_HPP
#define MEMBERSERVICE_HPP

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include "dto/database/MemberDTO.hpp"
#include "dto/StatusDTO.hpp"
#include "dto/PageDTO.hpp"
#include "dto/MemberCountDTO.hpp"
#include "database/DatabaseClient.hpp"

class MemberService {
private:
    typedef oatpp::web::protocol::http::Status Status;

private:
    OATPP_COMPONENT(std::shared_ptr<DatabaseClient>, m_database);

public:
    oatpp::Object<MemberDTO> createMember(const oatpp::Object<MemberDTO>& dto);
    oatpp::Object<MemberDTO> updateMember(const oatpp::Object<MemberDTO>& dto);
    oatpp::Object<MemberDTO> getMemberById(const oatpp::Int64& id);
    oatpp::Object<PageDTO<oatpp::Object<MemberDTO>>> getAllMembers(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
    oatpp::Object<StatusDTO> deleteMemberById(const oatpp::Int64& id);
    oatpp::Object<StatusDTO> deactivateMemberById(const oatpp::Int64& id);
    oatpp::Object<StatusDTO> activateMemberById(const oatpp::Int64& id);
    oatpp::Int64 getMemberCountTotal();
    oatpp::Int64 getMemberCountActive();
    oatpp::Int64 getMemberCountInactive();
};

#endif /* MEMBERSERVICE_HPP */
