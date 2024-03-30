#ifndef DEPARTMENT_TRAINING_REL_SERVICE_HPP
#define DEPARTMENT_TRAINING_REL_SERVICE_HPP

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include "database/DatabaseClient.hpp"
#include "dto/database/relations/DepartmentTrainingRelDTO.hpp"
#include "dto/StatusDTO.hpp"

class DepartmentTrainingRelService {
private:
    typedef oatpp::web::protocol::http::Status Status;
    OATPP_COMPONENT(std::shared_ptr<DatabaseClient>, m_database);

public:
    oatpp::Object<DepartmentTrainingRelDTO> createDepartmentTrainingRel(const oatpp::Object<DepartmentTrainingRelDTO>& rel);

    oatpp::Object<StatusDTO> deleteDepartmentTrainingRel(const oatpp::Int64& departmentId, const oatpp::Int64& trainingId);

    oatpp::Vector<oatpp::Int64> getTrainingIdsByDepartmentId(const oatpp::Int64& departmentId);

    oatpp::Vector<oatpp::Int64> getDepartmentIdsByTrainingId(const oatpp::Int64& trainingId);
};

#endif // DEPARTMENT_TRAINING_REL_SERVICE_HPP
