#include "DepartmentTrainingRelService.hpp"

oatpp::Object<DepartmentTrainingRelDTO> DepartmentTrainingRelService::createDepartmentTrainingRel(const oatpp::Object<DepartmentTrainingRelDTO>& rel) {
    auto dbResult = m_database->createDepartmentTrainingRel(rel);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    return rel;
}

oatpp::Object<StatusDTO> DepartmentTrainingRelService::deleteDepartmentTrainingRel(const oatpp::Int64& departmentId, const oatpp::Int64& trainingId) {
    auto dbResult = m_database->deleteDepartmentTrainingRel(departmentId, trainingId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto status = StatusDTO::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Department-training relation was successfully deleted";
    return status;
}

oatpp::Vector<oatpp::Int64> DepartmentTrainingRelService::getTrainingIdsByDepartmentId(const oatpp::Int64& departmentId) {
    auto dbResult = m_database->getTrainingIdsByDepartmentId(departmentId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    return dbResult->fetch<oatpp::Vector<oatpp::Int64>>();
}

oatpp::Vector<oatpp::Int64> DepartmentTrainingRelService::getDepartmentIdsByTrainingId(const oatpp::Int64& trainingId) {
    auto dbResult = m_database->getDepartmentIdsByTrainingId(trainingId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    return dbResult->fetch<oatpp::Vector<oatpp::Int64>>();
}
