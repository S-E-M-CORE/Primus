
#ifndef MEMBER_SERVICE_HPP
#define MEMBER_SERVICE_HPP

#include "sqlite/DatabaseClient.hpp"
#include "dto/DTOs.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class MemberService {
private:
	typedef oatpp::web::protocol::http::Status Status;
private:
	OATPP_COMPONENT(std::shared_ptr<DatabaseClient>, DBClient); // Inject database component
public:

	oatpp::Object<MemberDTO> createUser(const oatpp::Object<MemberDTO>& dto);
	oatpp::Object<MemberDTO> updateUser(const oatpp::Object<MemberDTO>& dto);
	oatpp::Object<MemberDTO> getUserById(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection = nullptr);
	oatpp::Object<PageDTO<oatpp::Object<MemberDTO>>> getAllUsers(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
	oatpp::Object<StatusDTO> deleteUserById(const oatpp::Int32& id);

};

#endif //CRUD_USERSERVICE_HPP
