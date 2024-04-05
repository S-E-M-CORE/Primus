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
                // TODO - Add more migrations here.
                migration.migrate(); // <-- run migrations. This guy will throw on error.

                auto version = executor->getSchemaVersion();
                OATPP_LOGI(primus::constants::databaseclient::logName,"Migration - OK. Version=%lld.", version);
            }

            // GET /api/members/training/most-often
            QUERY(getMembersWithMostTrainings,
                "SELECT m.* FROM Member m "
                "JOIN MemberTrainingRel mt ON m.id = mt.memberID "
                "GROUP BY m.id "
                "ORDER BY COUNT(mt.trainingID) DESC "
                "LIMIT :limit OFFSET :offset;",
                PARAM(oatpp::UInt32, limit),
                PARAM(oatpp::UInt32, offset));

            // GET /api/member/{id}/department
            QUERY(getDepartmentsOfMember,
                "SELECT d.* FROM Department d "
                "JOIN MemberDepartmentRel mdr ON d.id = mdr.departmentID "
                "WHERE mdr.memberID = :id;",
                PARAM(oatpp::UInt32, id));

            // GET /api/member/list/birthday
            QUERY(getMembersWithUpcomingBirthday,
                "SELECT * from Member m "
                "WHERE active = 1 AND strftime('%m-%d', m.birthDate) >= strftime('%m-%d', 'now') "
                "ORDER BY strftime('%m-%d', m.birthDate) ASC; ",
                PARAM(oatpp::UInt32, limit),
                PARAM(oatpp::UInt32, offset));

            // GET /api/member/list/all
            QUERY(getAllMembers,
                "SELECT * FROM Member LIMIT :limit OFFSET :offset;",
                PARAM(oatpp::UInt32, limit),
                PARAM(oatpp::UInt32, offset));


            // GET /api/member/list/active
            QUERY(getActiveMembers,
                "SELECT * FROM Member WHERE active = 1 LIMIT :limit OFFSET :offset;",
                PARAM(oatpp::UInt32, limit),
                PARAM(oatpp::UInt32, offset));

            // GET /api/member/list/inactive
            QUERY(getInactiveMembers,
                "SELECT * FROM Member WHERE active = 0 LIMIT :limit OFFSET :offset;",
                PARAM(oatpp::UInt32, limit),
                PARAM(oatpp::UInt32, offset));

            // UPDATE /api/member/{id}/activate
            QUERY(activateMember,
                "UPDATE Member SET active = 1 WHERE id = :id;",
                PARAM(oatpp::UInt32, id));

            // UPDATE /api/member/{id}/deactivate
            QUERY(deactivateMember,
                "UPDATE Member SET active = 0 WHERE id = :id;",
                PARAM(oatpp::UInt32, id));

            //GET /api/member/{id}
            QUERY(getMemberById,
                "SELECT * from Member WHERE id = :id;",
                PARAM(oatpp::UInt32, id));

            // CREATE /api/member/
            QUERY(createMember,
                "INSERT INTO Member (firstName, lastName, email, phoneNumber, birthDate, createDate, notes, active) "
                "VALUES (:member.firstName, :member.lastName, :member.email, :member.phoneNumber, :member.birthDate, DATE('now'), :member.notes, :member.active);",
                PARAM(oatpp::Object<MemberDto>, member));

            // Update /api/member/
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


            // GET /api/member/{id}/address
            QUERY(getMemberAddress,
                "SELECT * FROM Address WHERE id = (SELECT addressID FROM Address_Member WHERE memberID = :id);",
                PARAM(oatpp::UInt32, id));

            // GET /api/members/all/count
            QUERY(getMemberCountAll, "SELECT COUNT(*) as count FROM Member");

            // GET /api/members/active/count
            QUERY(getMemberCountActive, "SELECT COUNT(*) as count FROM Member WHERE active=1");

            // GET /api/members/inactive/count
            QUERY(getMemberCountInactive, "SELECT COUNT(*) as count FROM Member WHERE active=0");

        };

#include OATPP_CODEGEN_END(DbClient) ///< End code-gen section


    } // namespace component
} // namespace primus

#endif //DATABASE_CLIENT