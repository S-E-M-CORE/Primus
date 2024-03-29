
#ifndef MEMBER_SERVICE_HPP
#define MEMBER_SERVICE_HPP

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include "sqlite/DatabaseClient.hpp"
#include "dto/databaseDTOs/MemberDTO.hpp"
#include "dto/PageDTO.hpp"
#include "dto/StatusDTO.hpp"

class MemberService {
private:
	typedef oatpp::web::protocol::http::Status Status;
private:
	OATPP_COMPONENT(std::shared_ptr<DatabaseClient>, m_database); // Inject database component
public:

	oatpp::Object<MemberDTO> createMember(const oatpp::Object<MemberDTO>& dto);
	oatpp::Object<MemberDTO> updateMember(const oatpp::Object<MemberDTO>& dto);
	oatpp::Object<MemberDTO> getMemberById(const oatpp::Int64& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection = nullptr);
	oatpp::Object<PageDTO<oatpp::Object<MemberDTO>>> getAllMembers(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
	oatpp::Object<StatusDTO> deleteMemberById(const oatpp::Int64& id);
};

#endif //CRUD_USERSERVICE_HPP
