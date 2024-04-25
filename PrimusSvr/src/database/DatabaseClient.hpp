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
        //  ____        _        _                     ____ _ _            _   
        // |  _ \  __ _| |_ __ _| |__   __ _ ___  ___ / ___| (_) ___ _ __ | |_ 
        // | | | |/ _` | __/ _` | '_ \ / _` / __|/ _ \ |   | | |/ _ \ '_ \| __|
        // | |_| | (_| | || (_| | |_) | (_| \__ \  __/ |___| | |  __/ | | | |_ 
        // |____/ \__,_|\__\__,_|_.__/ \__,_|___/\___|\____|_|_|\___|_| |_|\__|
        /**
         * @brief DatabaseClient class represents a client to interact with the database.
         */
        class DatabaseClient : public oatpp::orm::DbClient
        {
            typedef primus::dto::database::AddressDto       AddressDto;
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
                OATPP_LOGI(primus::constants::databaseclient::logName, "DatabaseClient(oatpp::orm::DbClient) initialized");

                oatpp::orm::SchemaMigration migration(executor);
                migration.addFile(1 /* start from version 1 */, DATABASE_MIGRATIONS "/001_init.sql");
                migration.migrate(); // <-- run migrations. This guy will throw on error.

                auto version = executor->getSchemaVersion();
                OATPP_LOGI(primus::constants::databaseclient::logName,"Migration - OK. Version=%lld.", version);
            }

            //                           _               
            //  _ __ ___   ___ _ __ ___ | |__   ___ _ __ 
            // | '_ ` _ \ / _ \ '_ ` _ \| '_ \ / _ \ '__|
            // | | | | | |  __/ | | | | | |_) |  __/ |   
            // |_| |_| |_|\___|_| |_| |_|_.__/ \___|_|   

            /**
            * Retrieves a member by id
            * 
            * @param id The member id
            * 
            */
            QUERY(getMemberById, "SELECT * from Member WHERE id = :id;", PARAM(oatpp::UInt32, id));


            /**
            * Creates a member in the database
            *
            * @param member A dto containing the mebers data
            *
            */
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

            QUERY(activateMember, "UPDATE Member SET active = 1 WHERE id = :id;", PARAM(oatpp::UInt32, id));

            QUERY(deactivateMember, "UPDATE Member SET active = 0 WHERE id = :id;", PARAM(oatpp::UInt32, id));

            //                           _                                       _       
            //  _ __ ___   ___ _ __ ___ | |__   ___ _ __    ___ ___  _   _ _ __ | |_ ___ 
            // | '_ ` _ \ / _ \ '_ ` _ \| '_ \ / _ \ '__|  / __/ _ \| | | | '_ \| __/ __|
            // | | | | | |  __/ | | | | | |_) |  __/ |    | (_| (_) | |_| | | | | |_\__ \
            // |_| |_| |_|\___|_| |_| |_|_.__/ \___|_|     \___\___/ \__,_|_| |_|\__|___/

            QUERY(getMemberCountAll, "SELECT COUNT(*) as value FROM Member");

            QUERY(getMemberCountActive, "SELECT COUNT(*) as value FROM Member WHERE active=1");

            QUERY(getMemberCountInactive, "SELECT COUNT(*) as value FROM Member WHERE active=0");

            //                           _                 _ _     _       
            //  _ __ ___   ___ _ __ ___ | |__   ___ _ __  | (_)___| |_ ___ 
            // | '_ ` _ \ / _ \ '_ ` _ \| '_ \ / _ \ '__| | | / __| __/ __|
            // | | | | | |  __/ | | | | | |_) |  __/ |    | | \__ \ |_\__ \
            // |_| |_| |_|\___|_| |_| |_|_.__/ \___|_|    |_|_|___/\__|___/

            QUERY(getMembersWithUpcomingBirthday,
                " SELECT * from Member m "
                " WHERE active = 1 AND strftime('%m-%d', m.birthDate) >= strftime('%m-%d', 'now') "
                " ORDER BY strftime('%m-%d', m.birthDate) ASC "
                " LIMIT :limit OFFSET :offset; ",
                PARAM(oatpp::UInt32, limit),
                PARAM(oatpp::UInt32, offset));

            QUERY(getAllMembers,
                " SELECT * FROM Member "
                " LIMIT :limit OFFSET :offset;",
                PARAM(oatpp::UInt32, limit),
                PARAM(oatpp::UInt32, offset));

            QUERY(getActiveMembers,
                " SELECT * FROM Member "
                " WHERE active = 1 "
                " ORDER BY id "
                " LIMIT :limit OFFSET :offset;",
                PARAM(oatpp::UInt32, limit),
                PARAM(oatpp::UInt32, offset));

            QUERY(getMembersByMostTraining,
                " SELECT m.* "
                " FROM Member m "
                " JOIN( "
                "     SELECT member_id, COUNT(*) AS attendance_count "
                "     FROM Attendance"
                "     WHERE date >= date('now', '-6 months') "
                "     GROUP BY member_id "
                "     ORDER BY attendance_count DESC "
                "     LIMIT :limit OFFSET :offset "
                " ) AS top_members ON m.id = top_members.member_id; ",
                PARAM(oatpp::UInt32, limit),
                PARAM(oatpp::UInt32, offset));

            QUERY(getInactiveMembers,
                " SELECT * FROM Member "
                " WHERE active = 0 "
                " ORDER BY id "
                " LIMIT :limit OFFSET :offset;",
                PARAM(oatpp::UInt32, limit),
                PARAM(oatpp::UInt32, offset));

            QUERY(getMembersByAddress, "SELECT Member.* FROM Member INNER JOIN Address_Member ON Member.id = Address_Member.member_id WHERE Address_Member.address_id = :addressId;", PARAM(oatpp::UInt32, addressId));
            
            QUERY(getMembersByDepartment, "SELECT Member.* FROM Member INNER JOIN Department_Member ON Member.id = Department_Member.member_id WHERE Department_Member.department_id = :departmentId;", PARAM(oatpp::UInt32, departmentId));

            //                           _                 _        __           
            //  _ __ ___   ___ _ __ ___ | |__   ___ _ __  (_)_ __  / _| ___  ___ 
            // | '_ ` _ \ / _ \ '_ ` _ \| '_ \ / _ \ '__| | | '_ \| |_ / _ \/ __|
            // | | | | | |  __/ | | | | | |_) |  __/ |    | | | | |  _| (_) \__ \
            // |_| |_| |_|\___|_| |_| |_|_.__/ \___|_|    |_|_| |_|_|  \___/|___/

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

            QUERY(getMemberDepartments,
                " SELECT d.* FROM Department d "
                " INNER JOIN Department_Member dm ON d.id = dm.department_id "
                " WHERE dm.member_id = :id "
                " ORDER BY d.id ASC"
                " LIMIT :limit OFFSET :offset;",
                PARAM(oatpp::UInt32, id),
                PARAM(oatpp::UInt32, limit),
                PARAM(oatpp::UInt32, offset));

            //      _                       _                        _   
            //   __| | ___ _ __   __ _ _ __| |_ _ __ ___   ___ _ __ | |_ 
            //  / _` |/ _ \ '_ \ / _` | '__| __| '_ ` _ \ / _ \ '_ \| __|
            // | (_| |  __/ |_) | (_| | |  | |_| | | | | |  __/ | | | |_ 
            //  \__,_|\___| .__/ \__,_|_|   \__|_| |_| |_|\___|_| |_|\__|
            //            |_|                                            

            QUERY(getDepartmentById,
                " SELECT * FROM Department "
                " WHERE id = :id; "
                " ORDER BY id ASC",
                PARAM(oatpp::UInt32, id));

            //            _     _                   
            //   __ _  __| | __| |_ __ ___  ___ ___ 
            //  / _` |/ _` |/ _` | '__/ _ \/ __/ __|
            // | (_| | (_| | (_| | | |  __/\__ \__ \
            //  \__,_|\__,_|\__,_|_|  \___||___/___/

            QUERY(createAddress,
                " INSERT INTO Address (postalCode, city, country, houseNumber, street) "
                " SELECT :address.postalCode, :address.city, :address.country, :address.houseNumber, :address.street "
                " WHERE NOT EXISTS (SELECT 1 FROM Address WHERE postalCode = :address.postalCode AND city = :address.city AND country = :address.country AND houseNumber = :address.houseNumber AND street = :address.street);",
                PARAM(oatpp::Object<AddressDto>, address));

            QUERY(getAddressById, "SELECT * FROM Address WHERE id = :id;", PARAM(oatpp::UInt32, id));

            QUERY(updateAddress,
                "UPDATE Address SET "
                "street = :address.street, "
                "city = :address.city, "
                "zipCode = :address.zipCode, "
                "country = :address.country "
                "WHERE id = :address.id;",
                PARAM(oatpp::Object<AddressDto>, address));

            QUERY(deleteAddress, "DELETE FROM Address WHERE id = :id AND id NOT IN (SELECT address_id FROM Address_Member);", PARAM(oatpp::UInt32, id));

            QUERY(findAddressByDetails,
                "SELECT * FROM Address WHERE street = :street AND city = :city AND postalCode = :postalCode AND country = :country;",
                PARAM(oatpp::String, street),
                PARAM(oatpp::String, city),
                PARAM(oatpp::String, postalCode),
                PARAM(oatpp::String, country));

            //        _   _                 _                      
            //   __ _| |_| |_ ___ _ __   __| | __ _ _ __   ___ ___ 
            //  / _` | __| __/ _ \ '_ \ / _` |/ _` | '_ \ / __/ _ \
            // | (_| | |_| ||  __/ | | | (_| | (_| | | | | (_|  __/
            //  \__,_|\__|\__\___|_| |_|\__,_|\__,_|_| |_|\___\___|

            QUERY(createMemberAttendance,
                "INSERT INTO Attendance (member_id, date) "
                "VALUES (:member_id, :date); ",
                PARAM(oatpp::UInt32, member_id),
                PARAM(oatpp::String, date));

            QUERY(deleteMemberAttendance,
                "DELETE FROM Attendance "
                "WHERE member_id = :member_id AND date = :date;",
                PARAM(oatpp::UInt32, member_id),
                PARAM(oatpp::String, date));

            QUERY(getAttendancesOfMember,
                " SELECT date FROM Attendance "
                " WHERE member_id = :member_id "
                " ORDER BY date DESC "
                " LIMIT :limit OFFSET :offset;",
                PARAM(oatpp::UInt32, member_id),
                PARAM(oatpp::UInt32, limit),
                PARAM(oatpp::UInt32, offset));

            QUERY(getCountOfAttendancesOfMember,
                " SELECT COUNT(*) as value FROM Attendance "
                " WHERE member_id = :member_id ",
                PARAM(oatpp::UInt32, member_id));

            QUERY(getMembersByAttendanceDate,
                " SELECT member_id as value FROM Attendance "
                " WHERE date = :date "
                " ORDER BY date "
                " LIMIT :limit OFFSET :offset;",
                PARAM(oatpp::String, dateOfAttendance),
                PARAM(oatpp::UInt32, limit),
                PARAM(oatpp::UInt32, offset));

            QUERY(hasMemberAttendedOnDate,
                " SELECT COUNT(*) as value FROM Attendance "
                " WHERE date = :date AND member_id = :member_id;",
                PARAM(oatpp::UInt32, member_id),
                PARAM(oatpp::String, date));

            //    _                  _   _               _        _     _           
            //   (_)_   _ _ __   ___| |_(_) ___  _ __   | |_ __ _| |__ | | ___  ___ 
            //   | | | | | '_ \ / __| __| |/ _ \| '_ \  | __/ _` | '_ \| |/ _ \/ __|
            //   | | |_| | | | | (__| |_| | (_) | | | | | || (_| | |_) | |  __/\__ \
            //  _/ |\__,_|_| |_|\___|\__|_|\___/|_| |_|  \__\__,_|_.__/|_|\___||___/
            // |__/                                                                 

            QUERY(associateAddressWithMember, "INSERT INTO Address_Member (address_id, member_id) VALUES (:addressId, :memberId);", PARAM(oatpp::UInt32, addressId), PARAM(oatpp::UInt32, memberId));
            QUERY(disassociateAddressFromMember, "DELETE FROM Address_Member WHERE address_id = :addressId AND member_id = :memberId;", PARAM(oatpp::UInt32, addressId), PARAM(oatpp::UInt32, memberId));

            QUERY(associateDepartmentWithMember, "INSERT INTO Department_Member (department_id, member_id) VALUES (:departmentId, :memberId);", PARAM(oatpp::UInt32, departmentId), PARAM(oatpp::UInt32, memberId));
            QUERY(disassociateDepartmentFromMember, "DELETE FROM Department_Member WHERE department_id = :departmentId AND member_id = :memberId;", PARAM(oatpp::UInt32, departmentId), PARAM(oatpp::UInt32, memberId));

            // __      _____  __ _ _ __   ___  _ __       
            // \ \ /\ / / _ \/ _` | '_ \ / _ \| '_ \      
            //  \ V  V /  __/ (_| | |_) | (_) | | | |     
            //   \_/\_/ \___|\__,_| .__/ \___/|_| |_|     
            //  _ __  _   _ _ __ _|_| |__   __ _ ___  ___ 
            // | '_ \| | | | '__/ __| '_ \ / _` / __|/ _ \
            // | |_) | |_| | | | (__| | | | (_| \__ \  __/
            // | .__/ \__,_|_|  \___|_| |_|\__,_|___/\___|
            // |_|                                        

            QUERY(getCountOfMemberAttendancesInLastYear,
                " SELECT COUNT(*) as value "
                " FROM Attendance WHERE member_id = :memberId AND date >= DATE('now', '-1 year');",
                PARAM(oatpp::UInt32, memberId));

            QUERY(countDistinctAttendentMontsWithinLastYear,
                " SELECT COUNT(DISTINCT strftime('%m', date)) AS value "
                " FROM Attendance "
                " WHERE date >= DATE('now', '-1 year') "
                " AND member_id = :memberId; ",
                PARAM(oatpp::UInt32, memberId));
        };

#include OATPP_CODEGEN_END(DbClient) ///< End code-gen section


    } // namespace component
} // namespace primus

#endif //DATABASE_CLIENT