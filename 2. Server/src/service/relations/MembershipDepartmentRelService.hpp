#ifndef MEMBERSHIP_DEPARTMENT_REL_SERVICE_HPP
#define MEMBERSHIP_DEPARTMENT_REL_SERVICE_HPP

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include "database/DatabaseClient.hpp"
#include "dto/database/relations/MembershipDepartmentRelDTO.hpp"
#include "dto/PageDTO.hpp"
#include "dto/StatusDTO.hpp"

/**
 * Service class for handling operations related to membership-department relations.
 */
class MembershipDepartmentRelService {
private:
    typedef oatpp::web::protocol::http::Status Status;            // Define a type alias for HTTP status codes
    OATPP_COMPONENT(std::shared_ptr<DatabaseClient>, m_database); // Inject database component

public:
    /**
     * Creates a new membership-department relation.
     * @param rel The membership-department relation DTO.
     * @return The created membership-department relation.
     */
    oatpp::Object<MembershipDepartmentRelDTO> createMembershipDepartmentRel(const oatpp::Object<MembershipDepartmentRelDTO>& rel);

    /**
     * Deletes a membership-department relation.
     * @param membershipId The ID of the membership.
     * @param departmentId The ID of the department.
     * @return The status of the operation.
     */
    oatpp::Object<StatusDTO> deleteMembershipDepartmentRel(const oatpp::Int64& membershipId, const oatpp::Int64& departmentId);

    /**
     * Retrieves all department IDs associated with a membership.
     * @param membershipId The ID of the membership.
     * @return A list of department IDs.
     */
    oatpp::Vector<oatpp::Int64> getDepartmentIdsByMembershipId(const oatpp::Int64& membershipId);

    /**
     * Retrieves all membership IDs associated with a department.
     * @param departmentId The ID of the department.
     * @return A list of membership IDs.
     */
    oatpp::Vector<oatpp::Int64> getMembershipIdsByDepartmentId(const oatpp::Int64& departmentId);
};

#endif // MEMBERSHIP_DEPARTMENT_REL_SERVICE_HPP
