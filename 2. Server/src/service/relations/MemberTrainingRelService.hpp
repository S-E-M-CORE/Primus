#ifndef MEMBER_TRAINING_REL_SERVICE_HPP
#define MEMBER_TRAINING_REL_SERVICE_HPP

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include "database/DatabaseClient.hpp"
#include "dto/PageDTO.hpp"
#include "dto/StatusDTO.hpp"
#include "dto/database/relations/MemberTrainingRelDTO.hpp"

/**
 * Service class for handling operations related to member-training relations.
 */
class MemberTrainingRelService {
private:
    typedef oatpp::web::protocol::http::Status Status;            // Define a type alias for HTTP status codes
    OATPP_COMPONENT(std::shared_ptr<DatabaseClient>, m_database); // Inject database component

public:
    /**
     * Creates a new member-training relation.
     * @param rel The member-training relation DTO.
     * @return The created member-training relation.
     */
    oatpp::Object<MemberTrainingRelDTO> createMemberTrainingRel(const oatpp::Object<MemberTrainingRelDTO>& rel);

    /**
     * Deletes a member-training relation.
     * @param memberId The ID of the member.
     * @param trainingId The ID of the training.
     * @return The status of the operation.
     */
    oatpp::Object<StatusDTO> deleteMemberTrainingRel(const oatpp::Int64& memberId, const oatpp::Int64& trainingId);

    /**
     * Retrieves all training IDs associated with a member.
     * @param memberId The ID of the member.
     * @return A list of training IDs.
     */
    oatpp::Vector<oatpp::Int64> getTrainingIdsByMemberId(const oatpp::Int64& memberId);

    /**
     * Retrieves all member IDs associated with a training.
     * @param trainingId The ID of the training.
     * @return A list of member IDs.
     */
    oatpp::Vector<oatpp::Int64> getMemberIdsByTrainingId(const oatpp::Int64& trainingId);
};

#endif // MEMBER_TRAINING_REL_SERVICE_HPP
