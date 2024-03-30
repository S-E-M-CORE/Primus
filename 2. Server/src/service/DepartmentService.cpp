#include "DepartmentService.hpp"

oatpp::Object<DepartmentDTO> DepartmentService::createDepartment(const oatpp::Object<DepartmentDTO>& dto) {
    auto dbResult = m_database->createDepartment(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto departmentId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

    return getDepartmentById(departmentId);
}

oatpp::Object<DepartmentDTO> DepartmentService::updateDepartment(const oatpp::Object<DepartmentDTO>& dto) {
    auto dbResult = m_database->updateDepartment(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    return getDepartmentById(dto->id);
}

oatpp::Object<DepartmentDTO> DepartmentService::getDepartmentById(const oatpp::Int64& id) {
    auto dbResult = m_database->getDepartmentById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Department not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<DepartmentDTO>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];
}

oatpp::Object<PageDTO<oatpp::Object<DepartmentDTO>>> DepartmentService::getAllDepartments(const oatpp::UInt32& offset, const oatpp::UInt32& limit) {
    oatpp::UInt32 countToFetch = limit;

    if (limit > 10) {
        countToFetch = 10;
    }

    auto dbResult = m_database->getAllDepartments(offset, countToFetch);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<DepartmentDTO>>>();

    auto page = PageDTO<oatpp::Object<DepartmentDTO>>::createShared();
    page->offset = offset;
    page->limit = countToFetch;
    page->count = items->size();
    page->items = items;

    return page;
}

oatpp::Object<StatusDTO> DepartmentService::deleteDepartmentById(const oatpp::Int64& id) {
    auto dbResult = m_database->deleteDepartmentById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto status = StatusDTO::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Department was successfully deleted";
    return status;
}
