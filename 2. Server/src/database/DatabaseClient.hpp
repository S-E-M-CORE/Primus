#ifndef DATABASE_CLIENT
#define DATABASE_CLIENT

#include "oatpp-sqlite/orm.hpp"
#include "oatpp/orm/SchemaMigration.hpp"
#include "oatpp/orm/DbClient.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include "dto/DatabaseDtos.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * @brief DatabaseClient class represents a client to interact with the database.
 */
class DatabaseClient : public oatpp::orm::DbClient {
public:

    /**
     * Constructor to initialize the DatabaseClient.
     * @param executor - shared pointer to oatpp executor.
     */
    DatabaseClient(const std::shared_ptr<oatpp::orm::Executor>& executor)
        : oatpp::orm::DbClient(executor)
    {
        oatpp::orm::SchemaMigration migration(executor);
        migration.addFile(1 /* start from version 1 */, DATABASE_MIGRATIONS "/001_init.sql");
        // TODO - Add more migrations here.
        migration.migrate(); // <-- run migrations. This guy will throw on error.

        auto version = executor->getSchemaVersion();
        OATPP_LOGD("UserDb", "Migration - OK. Version=%lld.", version);
    }

    // GET /api/members/birthday/most-recent
    QUERY(getMembersWithUpcomingBirthday,
        "SELECT * FROM Member WHERE birthDate > DATE('now') ORDER BY birthDate LIMIT :limit OFFSET :offset;",
        PARAM(oatpp::Int32, limit),
        PARAM(oatpp::Int32, offset));

    // GET /api/members/training/most-often
    QUERY(getMembersWithMostTrainings,
        "SELECT m.* FROM Member m "
        "JOIN MemberTrainingRel mt ON m.id = mt.memberID "
        "GROUP BY m.id "
        "ORDER BY COUNT(mt.trainingID) DESC "
        "LIMIT :limit OFFSET :offset;",
        PARAM(oatpp::Int32, limit),
        PARAM(oatpp::Int32, offset));

    // GET /api/member/{id}/department
    QUERY(getDepartmentsOfMember,
        "SELECT d.* FROM Department d "
        "JOIN MemberDepartmentRel mdr ON d.id = mdr.departmentID "
        "WHERE mdr.memberID = :id;",
        PARAM(oatpp::Int32, id));

    // GET /api/members/all
    QUERY(getAllMembers,
        "SELECT * FROM Member LIMIT :limit OFFSET :offset;",
        PARAM(oatpp::Int32, limit),
        PARAM(oatpp::Int32, offset));

    // GET /api/members/active
    QUERY(getActiveMembers,
        "SELECT * FROM Member WHERE active = 1 LIMIT :limit OFFSET :offset;",
        PARAM(oatpp::Int32, limit),
        PARAM(oatpp::Int32, offset));

    // GET /api/members/inactive
    QUERY(getInactiveMembers,
        "SELECT * FROM Member WHERE active = 0 LIMIT :limit OFFSET :offset;",
        PARAM(oatpp::Int32, limit),
        PARAM(oatpp::Int32, offset));

    // GET /api/members/filter/firstname/
    QUERY(filterMembersByFirstName,
        "SELECT * FROM Member WHERE firstName LIKE '%' || :name || '%' LIMIT :limit OFFSET :offset;",
        PARAM(oatpp::String, name),
        PARAM(oatpp::Int32, limit),
        PARAM(oatpp::Int32, offset));

    // GET /api/members/filter/lastname/
    QUERY(filterMembersByLastName,
        "SELECT * FROM Member WHERE lastName LIKE '%' || :name || '%' LIMIT :limit OFFSET :offset;",
        PARAM(oatpp::String, name),
        PARAM(oatpp::Int32, limit),
        PARAM(oatpp::Int32, offset));

    // UPDATE /api/member/{id}/activate
    QUERY(activateMember,
        "UPDATE Member SET active = 1 WHERE id = :id;",
        PARAM(oatpp::Int32, id));

    // UPDATE /api/member/{id}/deactivate
    QUERY(deactivateMember,
        "UPDATE Member SET active = 0 WHERE id = :id;",
        PARAM(oatpp::Int32, id));

    //GET /api/member/{id}
    QUERY(getMemberById,
        "SELECT * from Member WHERE id = :id;",
        PARAM(oatpp::Int32, id));

    // CREATE /api/member/
    QUERY(createMember,
        "INSERT INTO Member (firstName, lastName, email, phoneNumber, birthDate, createDate, active) "
        "VALUES (:member.firstName, :member.lastName, :member.email, :member.phoneNumber, :member.birthDate, DATE('now'), :member.active);",
        PARAM(oatpp::Object<MemberDto>, member));

    // Update /api/member/
    QUERY(updateMember,
        "UPDATE Member SET firstName = :member.firstName, lastName = :member.lastName, "
        "email = :member.email, phoneNumber = :member.phoneNumber, birthDate = :member.birthDate, "
        "active = :member.active WHERE id = :member.id;",
        PARAM(oatpp::Object<MemberDto>, member));

    // GET /api/member/{id}/address
    QUERY(getMemberAddress,
        "SELECT * FROM Address WHERE id = (SELECT addressID FROM MemberAddressRel WHERE memberID = :id);",
        PARAM(oatpp::Int32, id));

    // GET /api/member/{id}/membership-fee
    QUERY(getMembershipFee,
        "SELECT SUM(CASE WHEN d.name = 'Bogenschießen' THEN 8 "
        "WHEN d.name = 'Luftdruck' THEN 10 "
        "WHEN d.name = 'Schusswaffen' THEN 15 ELSE 0 END) AS fee "
        "FROM Department d "
        "JOIN MemberDepartmentRel mdr ON d.id = mdr.departmentID "
        "WHERE mdr.memberID = :id;",
        PARAM(oatpp::Int32, id));

    // GET /api/member/{id}/trainings
    QUERY(getMemberTrainings,
        "SELECT t.* FROM Training t "
        "JOIN MemberTrainingRel mt ON t.id = mt.trainingID "
        "WHERE mt.memberID = :id LIMIT :limit OFFSET :offset;",
        PARAM(oatpp::Int32, id),
        PARAM(oatpp::Int32, limit),
        PARAM(oatpp::Int32, offset));

    // GET /api/member/{id}/purchase/weapons/allowed
    QUERY(isWeaponPurchaseAllowed,
        "SELECT COUNT(*) >= 1 AS allowed FROM ( "
        "SELECT COUNT(*) AS trainingCount FROM Training "
        "JOIN MemberTrainingRel ON Training.id = MemberTrainingRel.trainingID "
        "WHERE MemberTrainingRel.memberID = :id AND Training.date > DATE('now', '-1 year') "
        "GROUP BY strftime('%m', Training.date) "
        "HAVING trainingCount >= CASE "
        "WHEN COUNT(DISTINCT strftime('%Y-%m', Training.date)) >= 12 THEN 1 "
        "ELSE 18 "
        "END "
        ");",
        PARAM(oatpp::Int32, id));
};

#include OATPP_CODEGEN_END(DbClient) ///< End code-gen section

#endif //DATABASE_CLIENT