
#ifndef MEMBER_SERVICE_HPP
#define MEMBER_SERVICE_HPP

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include "database/DatabaseClient.hpp"
#include "dto/database/MemberDTO.hpp"
#include "dto/PageDTO.hpp"
#include "dto/StatusDTO.hpp"

/**
 * @brief Service class to handle operations related to members.
 */
class MemberService
{
private:
    typedef oatpp::web::protocol::http::Status Status; // Define a type alias for HTTP status codes

private:
    OATPP_COMPONENT(std::shared_ptr<DatabaseClient>, m_database); // Inject database component

public:
    /**
     * @brief Creates a new member.
     *
     * @param dto Data transfer object containing member information.
     * @return Object representing the created member.
     */
    oatpp::Object<MemberDTO> createMember(const oatpp::Object<MemberDTO>& dto);

    /**
     * @brief Updates an existing member.
     *
     * @param dto Data transfer object containing updated member information.
     * @return Object representing the updated member.
     */
    oatpp::Object<MemberDTO> updateMember(const oatpp::Object<MemberDTO>& dto);

    /**
     * @brief Retrieves a member by ID.
     *
     * @param id ID of the member to retrieve.
     * @param connection Optional database connection handle.
     * @return Object representing the retrieved member.
     */
    oatpp::Object<MemberDTO> getMemberById(const oatpp::Int64& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection = nullptr);

    /**
     * @brief Deletes a member by ID.
     *
     * @param id ID of the member to delete.
     * @return Object representing the status of the operation.
     */
    oatpp::Object<StatusDTO> deleteMemberById(const oatpp::Int64& id);

    /**
     * @brief Deactivates a member by their ID.
     *
     * @param id The ID of the member to deactivate.
     * @return Object representing the status of the deactivation operation.
     */
    oatpp::Object<StatusDTO> deactivateMemberById(const oatpp::Int64& id);

};

#endif //CRUD_USERSERVICE_HPP
