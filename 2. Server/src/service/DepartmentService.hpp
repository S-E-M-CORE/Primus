#ifndef DEPARTMENT_SERVICE_HPP
#define DEPARTMENT_SERVICE_HPP

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include "dto/database/DepartmentDTO.hpp"
#include "dto/PageDTO.hpp"
#include "dto/StatusDTO.hpp"
#include "database/DatabaseClient.hpp"

/**
 * @brief Service class to handle operations related to departments.
 */
class DepartmentService {
private:
    typedef oatpp::web::protocol::http::Status Status; // Define a type alias for HTTP status codes

private:
    OATPP_COMPONENT(std::shared_ptr<DatabaseClient>, m_database); // Inject database component

public:

    /**
     * @brief Creates a new department.
     *
     * @param dto Data transfer object containing department information.
     * @return Object representing the created department.
     */
    oatpp::Object<DepartmentDTO> createDepartment(const oatpp::Object<DepartmentDTO>& dto);

    /**
     * @brief Updates an existing department.
     *
     * @param dto Data transfer object containing updated department information.
     * @return Object representing the updated department.
     */
    oatpp::Object<DepartmentDTO> updateDepartment(const oatpp::Object<DepartmentDTO>& dto);

    /**
     * @brief Retrieves a department by ID.
     *
     * @param id ID of the department to retrieve.
     * @return Object representing the retrieved department.
     */
    oatpp::Object<DepartmentDTO> getDepartmentById(const oatpp::Int64& id);

    /**
     * @brief Retrieves all departments with pagination.
     *
     * @param offset Offset for pagination.
     * @param limit Maximum number of items to retrieve.
     * @return Object representing a page of departments.
     */
    oatpp::Object<PageDTO<oatpp::Object<DepartmentDTO>>> getAllDepartments(const oatpp::UInt32& offset, const oatpp::UInt32& limit);

    /**
     * @brief Deletes a department by ID.
     *
     * @param id ID of the department to delete.
     * @return Object representing the status of the operation.
     */
    oatpp::Object<StatusDTO> deleteDepartmentById(const oatpp::Int64& id);
};

#endif // DEPARTMENT_SERVICE_HPP
