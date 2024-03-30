#include "TrainingService.hpp"

oatpp::Object<TrainingDTO> TrainingService::createTraining(const oatpp::Object<TrainingDTO>& dto) {
    auto dbResult = m_database->createTraining(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto trainingId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

    return getTrainingById(trainingId);
}

oatpp::Object<TrainingDTO> TrainingService::updateTraining(const oatpp::Object<TrainingDTO>& dto) {
    auto dbResult = m_database->updateTraining(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    return getTrainingById(dto->id);
}

oatpp::Object<TrainingDTO> TrainingService::getTrainingById(const oatpp::Int64& id) {
    auto dbResult = m_database->getTrainingById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Training not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<TrainingDTO>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];
}

oatpp::Object<PageDTO<oatpp::Object<TrainingDTO>>> TrainingService::getAllTrainings(const oatpp::UInt32& offset, const oatpp::UInt32& limit) {
    oatpp::UInt32 countToFetch = limit;

    if (limit > 10) {
        countToFetch = 10;
    }

    auto dbResult = m_database->getAllTrainings(offset, countToFetch);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<TrainingDTO>>>();

    auto page = PageDTO<oatpp::Object<TrainingDTO>>::createShared();
    page->offset = offset;
    page->limit = countToFetch;
    page->count = items->size();
    page->items = items;

    return page;
}

oatpp::Object<StatusDTO> TrainingService::deleteTrainingById(const oatpp::Int64& id) {
    auto dbResult = m_database->deleteTrainingById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto status = StatusDTO::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Training was successfully deleted";
    return status;
}
