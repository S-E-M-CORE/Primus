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
                "SELECT :member.firstName, :member.lastName, :member.email, :member.phoneNumber, :member.birthDate, DATE('now'), :member.notes, :member.active "
                "WHERE NOT EXISTS (SELECT 1 FROM Member WHERE firstName = :member.firstName AND lastName = :member.lastName AND email = :member.email AND birthDate = :member.birthDate);",
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

            QUERY(findMemberIdByDetails,
                "SELECT * FROM Member WHERE firstName = :firstName AND lastName = :lastName AND email = :email AND birthDate = :birthDate;",
                PARAM(oatpp::String, firstName),
                PARAM(oatpp::String, lastName),
                PARAM(oatpp::String, email),
                PARAM(oatpp::String, birthDate));


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
                " SELECT * FROM Member m "
                " ORDER BY id ASC "
                " LIMIT :limit OFFSET : offset;",
                PARAM(oatpp::UInt32, limit),
                PARAM(oatpp::UInt32, offset));

            QUERY(getActiveMembers,
                " SELECT * FROM Member "
                " ORDER BY id ASC "
                " WHERE active = 1 "
                " LIMIT :limit OFFSET :offset;",
                PARAM(oatpp::UInt32, limit),
                PARAM(oatpp::UInt32, offset));

            QUERY(getInactiveMembers,
                " SELECT * FROM Member "
                " WHERE active = 0 "
                " ORDER BY id ASC "
                " LIMIT :limit OFFSET :offset;",
                PARAM(oatpp::UInt32, limit),
                PARAM(oatpp::UInt32, offset));

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

            QUERY(getMemberAddresses,
                " SELECT a.* FROM Address a "
                " INNER JOIN Address_Member am ON a.id = am.address_id "
                " WHERE am.member_id = :id "
                " ORDER BY a.id "
                " LIMIT :limit OFFSET :offset;",
                PARAM(oatpp::UInt32, id),
                PARAM(oatpp::UInt32, limit),
                PARAM(oatpp::UInt32, offset));

            QUERY(getDepartmentById,
                " SELECT * FROM Department "
                " WHERE id = :id; "
                " ORDER BY id ASC",
                PARAM(oatpp::UInt32, id));

            QUERY(getMemberDepartments,
                " SELECT d.* FROM Department d "
                " INNER JOIN Department_Member dm ON d.id = dm.department_id "
                " WHERE dm.member_id = :id "
                " ORDER BY d.id ASC"
                " LIMIT :limit OFFSET :offset;",
                PARAM(oatpp::UInt32, id),
                PARAM(oatpp::UInt32, limit),
                PARAM(oatpp::UInt32, offset));

            QUERY(createAddress,
                " INSERT INTO Address (postalCode, city, country, houseNumber, street) "
                " SELECT :address.postalCode, :address.city, :address.country, :address.houseNumber, :address.street "
                " WHERE NOT EXISTS (SELECT 1 FROM Address WHERE postalCode = :address.postalCode AND city = :address.city AND country = :address.country AND houseNumber = :address.houseNumber AND street = :address.street);",
                PARAM(oatpp::Object<AddressDto>, address));

            QUERY(findAddressByDetails,
                "SELECT * FROM Address WHERE street = :street AND city = :city AND postalCode = :postalCode AND country = :country;",
                PARAM(oatpp::String, street),
                PARAM(oatpp::String, city),
                PARAM(oatpp::String, postalCode),
                PARAM(oatpp::String, country));

            // READ
            QUERY(getAddressById,
                "SELECT * FROM Address WHERE id = :id;",
                PARAM(oatpp::UInt32, id));

            // UPDATE
            QUERY(updateAddress,
                "UPDATE Address SET "
                "street = :address.street, "
                "city = :address.city, "
                "zipCode = :address.zipCode, "
                "country = :address.country "
                "WHERE id = :address.id;",
                PARAM(oatpp::Object<AddressDto>, address));

            // DELETE
            QUERY(deleteAddress,
                "DELETE FROM Address WHERE id = :id AND id NOT IN (SELECT address_id FROM Address_Member);",
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

            QUERY(associateAddressWithMember, "INSERT INTO Address_Member (address_id, member_id) VALUES (:addressId, :memberId);", PARAM(oatpp::UInt32, addressId), PARAM(oatpp::UInt32, memberId));
            QUERY(disassociateAddressFromMember, "DELETE FROM Address_Member WHERE address_id = :addressId AND member_id = :memberId;", PARAM(oatpp::UInt32, addressId), PARAM(oatpp::UInt32, memberId));

            QUERY(getMembersByAddress, "SELECT Member.* FROM Member INNER JOIN Address_Member ON Member.id = Address_Member.member_id WHERE Address_Member.address_id = :addressId;", PARAM(oatpp::UInt32, addressId));

            QUERY(associateDepartmentWithMember, "INSERT INTO Department_Member (department_id, member_id) VALUES (:departmentId, :memberId);", PARAM(oatpp::UInt32, departmentId), PARAM(oatpp::UInt32, memberId));
            QUERY(disassociateDepartmentFromMember, "DELETE FROM Department_Member WHERE department_id = :departmentId AND member_id = :memberId;", PARAM(oatpp::UInt32, departmentId), PARAM(oatpp::UInt32, memberId));

            QUERY(getMembersByDepartment, "SELECT Member.* FROM Member INNER JOIN Department_Member ON Member.id = Department_Member.member_id WHERE Department_Member.department_id = :departmentId;", PARAM(oatpp::UInt32, departmentId));

            QUERY(associateTrainingWithMember, "INSERT INTO Training_Member (training_id, member_id) VALUES (:trainingId, :memberId);", PARAM(oatpp::UInt32, trainingId), PARAM(oatpp::UInt32, memberId));
            QUERY(disassociateTrainingFromMember, "DELETE FROM Training_Member WHERE training_id = :trainingId AND member_id = :memberId;", PARAM(oatpp::UInt32, trainingId), PARAM(oatpp::UInt32, memberId));

            QUERY(getMembersByTraining, "SELECT Member.* FROM Member INNER JOIN Training_Member ON Member.id = Training_Member.member_id WHERE Training_Member.training_id = :trainingId;", PARAM(oatpp::UInt32, trainingId));

            QUERY(associateTrainingWithDepartment, "INSERT INTO Training_Department (training_id, department_id) VALUES (:trainingId, :departmentId);", PARAM(oatpp::UInt32, trainingId), PARAM(oatpp::UInt32, departmentId));
            QUERY(disassociateTrainingFromDepartment, "DELETE FROM Training_Department WHERE training_id = :trainingId AND department_id = :departmentId;", PARAM(oatpp::UInt32, trainingId), PARAM(oatpp::UInt32, departmentId));

            QUERY(getDepartmentsByTraining, "SELECT Department.* FROM Department INNER JOIN Training_Department ON Department.id = Training_Department.department_id WHERE Training_Department.training_id = :trainingId;", PARAM(oatpp::UInt32, trainingId));

        };

#include OATPP_CODEGEN_END(DbClient) ///< End code-gen section


    } // namespace component
} // namespace primus

#endif //DATABASE_CLIENT