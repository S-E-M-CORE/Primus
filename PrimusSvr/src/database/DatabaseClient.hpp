#ifndef DATABASE_CLIENT
#define DATABASE_CLIENT

#include "oatpp-sqlite/orm.hpp"
#include "oatpp/orm/SchemaMigration.hpp"
#include "oatpp/orm/DbClient.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include "dto/DatabaseDtos.hpp"
#include "general/constants.hpp"

namespace primus
{
    namespace component
    {
#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen
        /**
         * @brief DatabaseClient class represents a client to interact with the database.
         */
        class DatabaseClient : public oatpp::orm::DbClient
        {
            typedef primus::dto::database::AddressDto       AddressDto;
            typedef primus::dto::database::TrainingDto      TrainingDto;
            typedef primus::dto::database::DepartmentDto    DepartmentDto;
            typedef primus::dto::database::MemberDto        MemberDto;
        public:

            /**
             * Constructor to initialize the DatabaseClient.
             * @param executor - shared pointer to oatpp executor.
             */
            DatabaseClient(const std::shared_ptr<oatpp::orm::Executor>& executor)
                : oatpp::orm::DbClient(executor)
            {
                OATPP_LOGI(primus::constants::databaseclient::logName, primus::constants::databaseclient::logSeperation);
                OATPP_LOGI(primus::constants::databaseclient::logName, "DatabaseClient(oatpp::orm::DbClient) initialized");
                OATPP_LOGI(primus::constants::databaseclient::logName, primus::constants::databaseclient::logSeperation);

                oatpp::orm::SchemaMigration migration(executor);
                migration.addFile(1 /* start from version 1 */, DATABASE_MIGRATIONS "/001_init.sql");
                migration.migrate(); // <-- run migrations. This guy will throw on error.

                auto version = executor->getSchemaVersion();
                OATPP_LOGI(primus::constants::databaseclient::logName,"Migration - OK. Version=%lld.", version);
            }

            // Member
            QUERY(getMemberById, "SELECT * from Member WHERE id = :id;", PARAM(oatpp::UInt32, id));

            QUERY(createMember,
                "INSERT INTO Member (firstName, lastName, email, phoneNumber, birthDate, createDate, notes, active) "
                "VALUES (:member.firstName, :member.lastName, :member.email, :member.phoneNumber, :member.birthDate, DATE('now'), :member.notes, :member.active);",
                PARAM(oatpp::Object<MemberDto>, member));

            QUERY(updateMember,
                "UPDATE Member SET "
                "firstName = :member.firstName, "
                "lastName = :member.lastName, "
                "email = :member.email, "
                "phoneNumber = :member.phoneNumber, "
                "birthDate = :member.birthDate, "
                "notes = :member.notes, "
                "active = :member.active "
                "WHERE id = :member.id;",
                PARAM(oatpp::Object<MemberDto>, member));

            QUERY(getMemberCountAll, "SELECT COUNT(*) as count FROM Member");

            QUERY(getMemberCountActive, "SELECT COUNT(*) as count FROM Member WHERE active=1");

            QUERY(getMemberCountInactive, "SELECT COUNT(*) as count FROM Member WHERE active=0");

            QUERY(getMembersWithUpcomingBirthday,
                "SELECT * from Member m "
                "WHERE active = 1 AND strftime('%m-%d', m.birthDate) >= strftime('%m-%d', 'now') "
                "ORDER BY strftime('%m-%d', m.birthDate) ASC; ",
                PARAM(oatpp::UInt32, limit),
                PARAM(oatpp::UInt32, offset));

            QUERY(getAllMembers,
                "SELECT * FROM Member LIMIT :limit OFFSET :offset;", PARAM(oatpp::UInt32, limit), PARAM(oatpp::UInt32, offset));

            QUERY(getActiveMembers,
                "SELECT * FROM Member WHERE active = 1 LIMIT :limit OFFSET :offset;", PARAM(oatpp::UInt32, limit), PARAM(oatpp::UInt32, offset));

            QUERY(getInactiveMembers, "SELECT * FROM Member WHERE active = 0 LIMIT :limit OFFSET :offset;", PARAM(oatpp::UInt32, limit), PARAM(oatpp::UInt32, offset));

            QUERY(activateMember, "UPDATE Member SET active = 1 WHERE id = :id;", PARAM(oatpp::UInt32, id));

            QUERY(deactivateMember, "UPDATE Member SET active = 0 WHERE id = :id;", PARAM(oatpp::UInt32, id));

            QUERY(getMembersWithMostTrainings,
                "SELECT m.* FROM Member m "
                "JOIN MemberTrainingRel mt ON m.id = mt.memberID "
                "GROUP BY m.id "
                "ORDER BY COUNT(mt.trainingID) DESC "
                "LIMIT :limit OFFSET :offset;",
                PARAM(oatpp::UInt32, limit),
                PARAM(oatpp::UInt32, offset));

            QUERY(getDepartmentsOfMember,
                "SELECT d.* FROM Department d "
                "JOIN MemberDepartmentRel mdr ON d.id = mdr.departmentID "
                "WHERE mdr.memberID = :id;",
                PARAM(oatpp::UInt32, id));

            QUERY(getMemberAddress,
                "SELECT * FROM Address WHERE id = (SELECT addressID FROM Address_Member WHERE memberID = :id);",
                PARAM(oatpp::UInt32, id));

            // Address
            QUERY(createAddress,
                "INSERT INTO Address (street, city, postalCode, country) "
                "VALUES (:address.street, :address.city, :address.postalCode, :address.country);",
                PARAM(oatpp::Object<AddressDto>, address));

            // READ
            QUERY(getAddressById,
                "SELECT * FROM Address WHERE id = :id;",
                PARAM(oatpp::UInt32, id));

            // UPDATE
            QUERY(updateAddress,
                "UPDATE Address SET "
                "street = :address.street, "
                "city = :address.city, "
                "postalCode = :address.postalCode, "
                "country = :address.country "
                "WHERE id = :address.id;",
                PARAM(oatpp::Object<AddressDto>, address));

            // DELETE
            QUERY(deleteAddress,
                "DELETE FROM Address WHERE id = :id;",
                PARAM(oatpp::UInt32, id));


            // Training
            QUERY(createTraining,
                "INSERT INTO Training (memberID, trainingDate) "
                "SELECT :training.memberID, DATE('now') "
                "WHERE NOT EXISTS ("
                "   SELECT 1 FROM Training WHERE memberID = :training.memberID AND trainingDate = DATE('now')"
                ");",
                PARAM(oatpp::Object<TrainingDto>, training));

            QUERY(getTrainingById,
                "SELECT * FROM Training WHERE id = :id;",
                PARAM(oatpp::UInt32, id));

            QUERY(getTrainingByMemberIdAndDate,
                "SELECT * FROM Training WHERE memberID = :memberID AND trainingDate = :trainingDate;",
                PARAM(oatpp::UInt32, memberID),
                PARAM(oatpp::String, trainingDate));

            QUERY(updateTraining,
                "UPDATE Training SET "
                "memberID = :training.memberID, "
                "trainingDate = :training.trainingDate "
                "WHERE id = :training.id;",
                PARAM(oatpp::Object<TrainingDto>, training));

            QUERY(deleteTraining,
                "DELETE FROM Training WHERE id = :id;",
                PARAM(oatpp::UInt32, id));

        };

#include OATPP_CODEGEN_END(DbClient) ///< End code-gen section


    } // namespace component
} // namespace primus

#endif //DATABASE_CLIENT