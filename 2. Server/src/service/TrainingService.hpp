#ifndef TRAININGSERVICE_HPP
#define TRAININGSERVICE_HPP

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include "dto/database/TrainingDTO.hpp"
#include "dto/StatusDTO.hpp"
#include "dto/PageDTO.hpp"
#include "database/DatabaseClient.hpp"

/**
 * @brief Service class to handle operations related to trainings.
 */
class TrainingService {
private:
    typedef oatpp::web::protocol::http::Status Status; // Define a type alias for HTTP status codes

private:
    OATPP_COMPONENT(std::shared_ptr<DatabaseClient>, m_database); // Inject database component

public:
    oatpp::Object<TrainingDTO> createTraining(const oatpp::Object<TrainingDTO>& dto);
    oatpp::Object<TrainingDTO> updateTraining(const oatpp::Object<TrainingDTO>& dto);
    oatpp::Object<TrainingDTO> getTrainingById(const oatpp::Int64& id);
    oatpp::Object<PageDTO<oatpp::Object<TrainingDTO>>> getAllTrainings(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
    oatpp::Object<StatusDTO> deleteTrainingById(const oatpp::Int64& id);
};

#endif /* TRAININGSERVICE_HPP */
