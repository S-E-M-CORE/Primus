#ifndef DATABASE_CLIENT
#define DATABASE_CLIENT

#include "oatpp/orm/SchemaMigration.hpp"
#include "oatpp/orm/DbClient.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include "dto/DTOs.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

class DatabaseClient : public oatpp::orm::DbClient {
public:

    DatabaseClient(const std::shared_ptr<oatpp::orm::Executor>& executor)
        : oatpp::orm::DbClient(executor)
    {}

    //  __  __                _                  ___                            
    // |  \/  | ___ _ __ ___ | |__   ___ _ __   / _ \ _   _  ___ _ __ _   _ ___ 
    // | |\/| |/ _ \ '_ ` _ \| '_ \ / _ \ '__| | | | | | | |/ _ \ '__| | | / __|
    // | |  | |  __/ | | | | | |_) |  __/ |    | |_| | |_| |  __/ |  | |_| \__ \
    // |_|  |_|\___|_| |_| |_|_.__/ \___|_|     \__\_\\__,_|\___|_|   \__, |___/
    //                                                                |___/     

    QUERY(createMember, "INSERT INTO members (memberID, firstName, lastName, birthDate, joinDate, active) " "VALUES (:memberID, :firstName, :lastName, :birthDate, :joinDate, :active);",
        PARAM(oatpp::Int64, memberID),
        PARAM(oatpp::String, firstName),
        PARAM(oatpp::String, lastName),
        PARAM(oatpp::String, birthDate),
        PARAM(oatpp::String, joinDate),
        PARAM(oatpp::Boolean, active));

    QUERY(getMemberByID,
        "SELECT * FROM members WHERE memberID=:memberID;",
        PARAM(oatpp::Int64, memberID));

    QUERY(updateMember,
        "UPDATE members SET firstName=:firstName, lastName=:lastName, "
        "birthDate=:birthDate, joinDate=:joinDate, active=:active "
        "WHERE memberID=:memberID;",
        PARAM(oatpp::String, firstName),
        PARAM(oatpp::String, lastName),
        PARAM(oatpp::String, birthDate),
        PARAM(oatpp::String, joinDate),
        PARAM(oatpp::Boolean, active),
        PARAM(oatpp::Int64, memberID));

    QUERY(deleteMember,
        "DELETE FROM members WHERE memberID=:memberID;",
        PARAM(oatpp::Int64, memberID));

    QUERY(getActiveMembers,
        "SELECT * FROM members WHERE active=true;");

    QUERY(countMembers,
        "SELECT COUNT(*) FROM members;");

    QUERY(getMembersJoinedAfterDate,
        "SELECT * FROM members WHERE joinDate > :date;",
        PARAM(oatpp::String, date));

    QUERY(getMembersOlderThanAge,
        "SELECT * FROM members WHERE birthDate < DATE(:currentDate, '-' || :age || ' years');",
        PARAM(oatpp::String, currentDate),
        PARAM(oatpp::Int32, age));

    QUERY(getMembersByLastName,
        "SELECT * FROM members WHERE lastName=:lastName;",
        PARAM(oatpp::String, lastName));

    QUERY(countActiveMembersInCity,
        "SELECT COUNT(*) FROM members m "
        "INNER JOIN addresses a ON m.addressID = a.addressID "
        "WHERE a.city=:city AND m.active=true;",
        PARAM(oatpp::String, city));

    QUERY(getMembersByDepartment,
        "SELECT * FROM members m "
        "INNER JOIN memberships mem ON m.memberID = mem.memberID "
        "WHERE mem.departmentId=:departmentId;",
        PARAM(oatpp::Int64, departmentId));

    QUERY(averageMembersPerDepartment,
        "SELECT AVG(numMembers) FROM ("
        "   SELECT COUNT(*) AS numMembers FROM memberships "
        "   GROUP BY departmentId"
        ");");



    //     _       _                      ___                            
    //    / \   __| |_ __ ___  ___ ___   / _ \ _   _  ___ _ __ _   _ ___ 
    //   / _ \ / _` | '__/ _ \/ __/ __| | | | | | | |/ _ \ '__| | | / __|
    //  / ___ \ (_| | | |  __/\__ \__ \ | |_| | |_| |  __/ |  | |_| \__ \
    // /_/   \_\__,_|_|  \___||___/___/  \__\_\\__,_|\___|_|   \__, |___/
    //                                                         |___/     

    QUERY(createAddress,
        "INSERT INTO addresses (addressID, zipCode, city, state, houseNumber, street) "
        "VALUES (:addressID, :zipCode, :city, :state, :houseNumber, :street);",
        PARAM(oatpp::Int64, addressID),
        PARAM(oatpp::String, zipCode),
        PARAM(oatpp::String, city),
        PARAM(oatpp::String, state),
        PARAM(oatpp::String, houseNumber),
        PARAM(oatpp::String, street));

    QUERY(getAddressByID,
        "SELECT * FROM addresses WHERE addressID=:addressID;",
        PARAM(oatpp::Int64, addressID));

    QUERY(updateAddress,
        "UPDATE addresses SET zipCode=:zipCode, city=:city, state=:state, "
        "houseNumber=:houseNumber, street=:street "
        "WHERE addressID=:addressID;",
        PARAM(oatpp::String, zipCode),
        PARAM(oatpp::String, city),
        PARAM(oatpp::String, state),
        PARAM(oatpp::String, houseNumber),
        PARAM(oatpp::String, street),
        PARAM(oatpp::Int64, addressID));

    QUERY(deleteAddress,
        "DELETE FROM addresses WHERE addressID=:addressID;",
        PARAM(oatpp::Int64, addressID));

    QUERY(getAddressesInCity,
        "SELECT * FROM addresses WHERE city=:city;",
        PARAM(oatpp::String, city));

    QUERY(getAddressesInState,
        "SELECT * FROM addresses WHERE state=:state;",
        PARAM(oatpp::String, state));

    QUERY(getAddressesByZipCode,
        "SELECT * FROM addresses WHERE zipCode=:zipCode;",
        PARAM(oatpp::String, zipCode));

    QUERY(updateZipCodeInCity,
        "UPDATE addresses SET zipCode=:newZipCode WHERE city=:city;",
        PARAM(oatpp::String, newZipCode),
        PARAM(oatpp::String, city));

    //  ____  _                      _   _                 _               
    // |  _ \| |__   ___  _ __   ___| \ | |_   _ _ __ ___ | |__   ___ _ __ 
    // | |_) | '_ \ / _ \| '_ \ / _ \  \| | | | | '_ ` _ \| '_ \ / _ \ '__|
    // |  __/| | | | (_) | | | |  __/ |\  | |_| | | | | | | |_) |  __/ |   
    // |_|__ |_| |_|\___/|_| |_|\___|_| \_|\__,_|_| |_| |_|_.__/ \___|_|   
    //  / _ \ _   _  ___ _ __ _   _ ___                                    
    // | | | | | | |/ _ \ '__| | | / __|                                   
    // | |_| | |_| |  __/ |  | |_| \__ \                                   
    //  \__\_\\__,_|\___|_|   \__, |___/                                   
    //                        |___/                                        

    QUERY(createPhoneNumber,
        "INSERT INTO phone_numbers (phoneNumberID, phoneNumber) "
        "VALUES (:phoneNumberID, :phoneNumber);",
        PARAM(oatpp::Int64, phoneNumberID),
        PARAM(oatpp::String, phoneNumber));

    QUERY(getPhoneNumberByID,
        "SELECT * FROM phone_numbers WHERE phoneNumberID=:phoneNumberID;",
        PARAM(oatpp::Int64, phoneNumberID));

    QUERY(updatePhoneNumber,
        "UPDATE phone_numbers SET phoneNumber=:phoneNumber "
        "WHERE phoneNumberID=:phoneNumberID;",
        PARAM(oatpp::String, phoneNumber),
        PARAM(oatpp::Int64, phoneNumberID));

    QUERY(deletePhoneNumber,
        "DELETE FROM phone_numbers WHERE phoneNumberID=:phoneNumberID;",
        PARAM(oatpp::Int64, phoneNumberID));

    QUERY(getAllPhoneNumbers,
        "SELECT * FROM phone_numbers;");

    //  _____      __  __       _ _    ___                            
    // | ____|    |  \/  | __ _(_) |  / _ \ _   _  ___ _ __ _   _ ___ 
    // |  _| _____| |\/| |/ _` | | | | | | | | | |/ _ \ '__| | | / __|
    // | |__|_____| |  | | (_| | | | | |_| | |_| |  __/ |  | |_| \__ \
    // |_____|    |_|  |_|\__,_|_|_|  \__\_\\__,_|\___|_|   \__, |___/
    //                                                      |___/     

    QUERY(createEmail,
        "INSERT INTO emails (emailID, email) "
        "VALUES (:emailID, :email);",
        PARAM(oatpp::Int64, emailID),
        PARAM(oatpp::String, email));

    QUERY(getEmailByID,
        "SELECT * FROM emails WHERE emailID=:emailID;",
        PARAM(oatpp::Int64, emailID));

    // SQL-Abfrage zum Aktualisieren einer E-Mail
    QUERY(updateEmail,
        "UPDATE emails SET email=:email "
        "WHERE emailID=:emailID;",
        PARAM(oatpp::String, email),
        PARAM(oatpp::Int64, emailID));

    QUERY(deleteEmail,
        "DELETE FROM emails WHERE emailID=:emailID;",
        PARAM(oatpp::Int64, emailID));

    QUERY(getAllEmails,
        "SELECT * FROM emails;");

    //  __  __                _                   _     _       
    // |  \/  | ___ _ __ ___ | |__   ___ _ __ ___| |__ (_)_ __  
    // | |\/| |/ _ \ '_ ` _ \| '_ \ / _ \ '__/ __| '_ \| | '_ \ 
    // | |  | |  __/ | | | | | |_) |  __/ |  \__ \ | | | | |_) |
    // |_|__|_|\___|_| |_| |_|_.__/ \___|_|  |___/_| |_|_| .__/ 
    //  / _ \ _   _  ___ _ __ _   _ ___                  |_|    
    // | | | | | | |/ _ \ '__| | | / __|                        
    // | |_| | |_| |  __/ |  | |_| \__ \                        
    //  \__\_\\__,_|\___|_|   \__, |___/                        
    //                        |___/                             

    QUERY(createMembership,
        "INSERT INTO memberships (membershipID, departmentId, membershipFee, active) "
        "VALUES (:membershipID, :departmentId, :membershipFee, :active);",
        PARAM(oatpp::Int64, membershipID),
        PARAM(oatpp::Int64, departmentId),
        PARAM(oatpp::Float32, membershipFee),
        PARAM(oatpp::Boolean, active));

    QUERY(getMembershipByID,
        "SELECT * FROM memberships WHERE membershipID=:membershipID;",
        PARAM(oatpp::Int64, membershipID));

    QUERY(updateMembership,
        "UPDATE memberships SET departmentId=:departmentId, membershipFee=:membershipFee, "
        "active=:active WHERE membershipID=:membershipID;",
        PARAM(oatpp::Int64, departmentId),
        PARAM(oatpp::Float32, membershipFee),
        PARAM(oatpp::Boolean, active),
        PARAM(oatpp::Int64, membershipID));

    QUERY(deleteMembership,
        "DELETE FROM memberships WHERE membershipID=:membershipID;",
        PARAM(oatpp::Int64, membershipID));

    QUERY(getActiveMemberships,
        "SELECT * FROM memberships WHERE active=true;");

    QUERY(getMembershipsByDepartment,
        "SELECT * FROM memberships WHERE departmentId=:departmentId;",
        PARAM(oatpp::Int64, departmentId));

    QUERY(updateMembershipFee,
        "UPDATE memberships SET membershipFee=:membershipFee WHERE membershipID=:membershipID;",
        PARAM(oatpp::Float32, membershipFee),
        PARAM(oatpp::Int64, membershipID));

    QUERY(deactivateMembershipsByDepartment,
        "UPDATE memberships SET active=false WHERE departmentId=:departmentId;",
        PARAM(oatpp::Int64, departmentId));

    QUERY(activateMembershipsByDepartment,
        "UPDATE memberships SET active=true WHERE departmentId=:departmentId;",
        PARAM(oatpp::Int64, departmentId));

    QUERY(updateMembershipStatusByJoinDate,
        "UPDATE memberships SET active=:active WHERE joinDate=:joinDate;",
        PARAM(oatpp::Boolean, active),
        PARAM(oatpp::String, joinDate));

    QUERY(getActiveMembershipsByFeeRange,
        "SELECT * FROM memberships WHERE active=true AND membershipFee BETWEEN :minFee AND :maxFee;",
        PARAM(oatpp::Float32, minFee),
        PARAM(oatpp::Float32, maxFee));

    QUERY(countActiveMemberships,
        "SELECT COUNT(*) FROM memberships WHERE active=true;");

    QUERY(getTotalMembershipFees,
        "SELECT SUM(membershipFee) FROM memberships WHERE active=true;");

    QUERY(getMembershipsByStatus,
        "SELECT * FROM memberships WHERE active=:active;",
        PARAM(oatpp::Boolean, active));

    QUERY(getExpiredMemberships,
        "SELECT * FROM memberships WHERE active=true AND expirationDate < :currentDate;",
        PARAM(oatpp::String, currentDate));

    //  ____                        _                        _   
    // |  _ \  ___ _ __   __ _ _ __| |_ _ __ ___   ___ _ __ | |_ 
    // | | | |/ _ \ '_ \ / _` | '__| __| '_ ` _ \ / _ \ '_ \| __|
    // | |_| |  __/ |_) | (_| | |  | |_| | | | | |  __/ | | | |_ 
    // |____/ \___| .__/ \__,_|_|   \__|_| |_| |_|\___|_| |_|\__|
    //  / _ \ _   |_|___ _ __ _   _ ___                          
    // | | | | | | |/ _ \ '__| | | / __|                         
    // | |_| | |_| |  __/ |  | |_| \__ \                         
    //  \__\_\\__,_|\___|_|   \__, |___/                         
    //                        |___/                              

    QUERY(createDepartment,
        "INSERT INTO departments (departmentID, name, monthlyFee, active) "
        "VALUES (:departmentID, :name, :monthlyFee, :active);",
        PARAM(oatpp::Int64, departmentID),
        PARAM(oatpp::String, name),
        PARAM(oatpp::Float32, monthlyFee),
        PARAM(oatpp::Boolean, active));

    QUERY(getDepartmentByID,
        "SELECT * FROM departments WHERE departmentID=:departmentID;",
        PARAM(oatpp::Int64, departmentID));

    QUERY(updateDepartment,
        "UPDATE departments SET name=:name, monthlyFee=:monthlyFee, active=:active "
        "WHERE departmentID=:departmentID;",
        PARAM(oatpp::String, name),
        PARAM(oatpp::Float32, monthlyFee),
        PARAM(oatpp::Boolean, active),
        PARAM(oatpp::Int64, departmentID));

    QUERY(deleteDepartment,
        "DELETE FROM departments WHERE departmentID=:departmentID;",
        PARAM(oatpp::Int64, departmentID));

    QUERY(getActiveDepartments,
        "SELECT * FROM departments WHERE active=true;");

    QUERY(deactivateDepartment,
        "UPDATE departments SET active=false WHERE departmentID=:departmentID;",
        PARAM(oatpp::Int64, departmentID));

    //  _____          _       _                ___                            
    // |_   _| __ __ _(_)_ __ (_)_ __   __ _   / _ \ _   _  ___ _ __ _   _ ___ 
    //   | || '__/ _` | | '_ \| | '_ \ / _` | | | | | | | |/ _ \ '__| | | / __|
    //   | || | | (_| | | | | | | | | | (_| | | |_| | |_| |  __/ |  | |_| \__ \
    //   |_||_|  \__,_|_|_| |_|_|_| |_|\__, |  \__\_\\__,_|\___|_|   \__, |___/
    //                                 |___/                         |___/     

    QUERY(createTraining,
        "INSERT INTO trainings (trainingID, date, startTime, room, notes) "
        "VALUES (:trainingID, :date, :startTime, :room, :notes);",
        PARAM(oatpp::Int64, trainingID),
        PARAM(oatpp::String, date),
        PARAM(oatpp::String, startTime),
        PARAM(oatpp::String, room),
        PARAM(oatpp::String, notes));

    QUERY(getTrainingByID,
        "SELECT * FROM trainings WHERE trainingID=:trainingID;",
        PARAM(oatpp::Int64, trainingID));

    QUERY(updateTraining,
        "UPDATE trainings SET date=:date, startTime=:startTime, room=:room, notes=:notes "
        "WHERE trainingID=:trainingID;",
        PARAM(oatpp::String, date),
        PARAM(oatpp::String, startTime),
        PARAM(oatpp::String, room),
        PARAM(oatpp::String, notes),
        PARAM(oatpp::Int64, trainingID));

    QUERY(deleteTraining,
        "DELETE FROM trainings WHERE trainingID=:trainingID;",
        PARAM(oatpp::Int64, trainingID));

    QUERY(getAllTrainings,
        "SELECT * FROM trainings;");

    //  ____      _       _   _                   _ 
    // |  _ \ ___| | __ _| |_(_) ___  _ __   __ _| |
    // | |_) / _ \ |/ _` | __| |/ _ \| '_ \ / _` | |
    // |  _ <  __/ | (_| | |_| | (_) | | | | (_| | |
    // |_|_\_\___|_|\__,_|\__|_|\___/|_| |_|\__,_|_|
    //  / _ \ _   _  ___ _ __ _   _ ___             
    // | | | | | | |/ _ \ '__| | | / __|            
    // | |_| | |_| |  __/ |  | |_| \__ \            
    //  \__\_\\__,_|\___|_|   \__, |___/            
    //                        |___/                 

    // Querys requesting stuff from multiple tables

    //  __  __                _                      _       _                   
    // |  \/  | ___ _ __ ___ | |__   ___ _ __       / \   __| |_ __ ___  ___ ___ 
    // | |\/| |/ _ \ '_ ` _ \| '_ \ / _ \ '__|____ / _ \ / _` | '__/ _ \/ __/ __|
    // | |  | |  __/ | | | | | |_) |  __/ | |_____/ ___ \ (_| | | |  __/\__ \__ \
    // |_|__|_|\___|_| |_| |_|_.__/ \___|_|      /_/   \_\__,_|_|  \___||___/___/
    //  / _ \ _   _  ___ _ __ _   _ ___                                          
    // | | | | | | |/ _ \ '__| | | / __|                                         
    // | |_| | |_| |  __/ |  | |_| \__ \                                         
    //  \__\_\\__,_|\___|_|   \__, |___/                                         
    //                        |___/                                              

    QUERY(createMemberAddressRelation,
        "INSERT INTO member_address_relation (memberID, addressID) "
        "VALUES (:memberID, :addressID);",
        PARAM(oatpp::Int64, memberID),
        PARAM(oatpp::Int64, addressID));

    QUERY(deleteMemberAddressRelation,
        "DELETE FROM member_address_relation "
        "WHERE memberID=:memberID AND addressID=:addressID;",
        PARAM(oatpp::Int64, memberID),
        PARAM(oatpp::Int64, addressID));

    QUERY(getAddressesByMemberID,
        "SELECT a.* FROM addresses a INNER JOIN member_address_relation mar "
        "ON a.adressID = mar.addressID WHERE mar.memberID=:memberID;",
        PARAM(oatpp::Int64, memberID));

    QUERY(getMembersByAddressID,
        "SELECT m.* FROM members m INNER JOIN member_address_relation mar "
        "ON m.memberID = mar.memberID WHERE mar.addressID=:addressID;");

    //  __  __                _                    _____                 _ _ 
    // |  \/  | ___ _ __ ___ | |__   ___ _ __     | ____|_ __ ___   __ _(_) |
    // | |\/| |/ _ \ '_ ` _ \| '_ \ / _ \ '__|____|  _| | '_ ` _ \ / _` | | |
    // | |  | |  __/ | | | | | |_) |  __/ | |_____| |___| | | | | | (_| | | |
    // |_|__|_|\___|_| |_| |_|_.__/ \___|_|       |_____|_| |_| |_|\__,_|_|_|
    //  / _ \ _   _  ___ _ __ _   _ ___                                      
    // | | | | | | |/ _ \ '__| | | / __|                                     
    // | |_| | |_| |  __/ |  | |_| \__ \                                     
    //  \__\_\\__,_|\___|_|   \__, |___/                                     
    //                        |___/                                          

    QUERY(createMemberEmailRelation,
        "INSERT INTO member_email_relation (memberID, emailID) "
        "VALUES (:memberID, :emailID);",
        PARAM(oatpp::Int64, memberID),
        PARAM(oatpp::Int64, emailID));

    QUERY(deleteMemberEmailRelation,
        "DELETE FROM member_email_relation "
        "WHERE memberID=:memberID AND emailID=:emailID;",
        PARAM(oatpp::Int64, memberID),
        PARAM(oatpp::Int64, emailID));

    QUERY(getEmailsByMemberID,
        "SELECT e.* FROM emails e INNER JOIN member_email_relation mer "
        "ON e.emailID = mer.emailID WHERE mer.memberID=:memberID;",
        PARAM(oatpp::Int64, memberID));

    QUERY(getMembersByEmailID,
        "SELECT m.* FROM members m INNER JOIN member_email_relation mer "
        "ON m.memberID = mer.memberID WHERE mer.emailID=:emailID;");

    //  __  __                _                    ____  _                            
    // |  \/  | ___ _ __ ___ | |__   ___ _ __     |  _ \| |__   ___  _ __   ___ _ __  
    // | |\/| |/ _ \ '_ ` _ \| '_ \ / _ \ '__|____| |_) | '_ \ / _ \| '_ \ / _ \ '_ \ 
    // | |  | |  __/ | | | | | |_) |  __/ | |_____|  __/| | | | (_) | | | |  __/ | | |
    // |_|  |_|\___|_| |_| |_|_.__/ \___|_|___    |_|   |_| |_|\___/|_| |_|\___|_| |_|
    //  _   _ _ __ ___ | |__   ___ _ __   / _ \ _   _  ___ _ __ _   _ ___             
    // | | | | '_ ` _ \| '_ \ / _ \ '__| | | | | | | |/ _ \ '__| | | / __|            
    // | |_| | | | | | | |_) |  __/ |    | |_| | |_| |  __/ |  | |_| \__ \            
    //  \__,_|_| |_| |_|_.__/ \___|_|     \__\_\\__,_|\___|_|   \__, |___/            
    //                                                          |___/                 

    QUERY(createMemberPhoneNumberRelation,
        "INSERT INTO member_phonenumber_relation (memberID, phoneNumberID) "
        "VALUES (:memberID, :phoneNumberID);",
        PARAM(oatpp::Int64, memberID),
        PARAM(oatpp::Int64, phoneNumberID));

    QUERY(deleteMemberPhoneNumberRelation,
        "DELETE FROM member_phonenumber_relation "
        "WHERE memberID=:memberID AND phoneNumberID=:phoneNumberID;",
        PARAM(oatpp::Int64, memberID),
        PARAM(oatpp::Int64, phoneNumberID));

    QUERY(getPhoneNumbersByMemberID,
        "SELECT pn.* FROM phonenumbers pn INNER JOIN member_phonenumber_relation mpn "
        "ON pn.phoneNumberID = mpn.phoneNumberID WHERE mpn.memberID=:memberID;",
        PARAM(oatpp::Int64, memberID));

    QUERY(getMembersByPhoneNumberID,
        "SELECT m.* FROM members m INNER JOIN member_phonenumber_relation mpn "
        "ON m.memberID = mpn.memberID WHERE mpn.phoneNumberID=:phoneNumberID;");

    //  __  __                _                    __  __                _                   _     _       
    // |  \/  | ___ _ __ ___ | |__   ___ _ __     |  \/  | ___ _ __ ___ | |__   ___ _ __ ___| |__ (_)_ __  
    // | |\/| |/ _ \ '_ ` _ \| '_ \ / _ \ '__|____| |\/| |/ _ \ '_ ` _ \| '_ \ / _ \ '__/ __| '_ \| | '_ \ 
    // | |  | |  __/ | | | | | |_) |  __/ | |_____| |  | |  __/ | | | | | |_) |  __/ |  \__ \ | | | | |_) |
    // |_|__|_|\___|_| |_| |_|_.__/ \___|_|       |_|  |_|\___|_| |_| |_|_.__/ \___|_|  |___/_| |_|_| .__/ 
    //  / _ \ _   _  ___ _ __ _   _ ___                                                             |_|    
    // | | | | | | |/ _ \ '__| | | / __|                                                                   
    // | |_| | |_| |  __/ |  | |_| \__ \                                                                   
    //  \__\_\\__,_|\___|_|   \__, |___/                                                                   
    //                        |___/                                                                        

    QUERY(createMemberMembershipRelation,
        "INSERT INTO member_membership_relation (memberID, membershipID) "
        "VALUES (:memberID, :membershipID);",
        PARAM(oatpp::Int64, memberID),
        PARAM(oatpp::Int64, membershipID));

    QUERY(deleteMemberMembershipRelation,
        "DELETE FROM member_membership_relation "
        "WHERE memberID=:memberID AND membershipID=:membershipID;",
        PARAM(oatpp::Int64, memberID),
        PARAM(oatpp::Int64, membershipID));

    QUERY(getMembershipsByMemberID,
        "SELECT m.* FROM memberships m INNER JOIN member_membership_relation mmr "
        "ON m.membershipID = mmr.membershipID WHERE mmr.memberID=:memberID;",
        PARAM(oatpp::Int64, memberID));

    QUERY(getMembersByMembershipID,
        "SELECT m.* FROM members m INNER JOIN member_membership_relation mmr "
        "ON m.memberID = mmr.memberID WHERE mmr.membershipID=:membershipID;");

    //  __  __                _                  _____          _       _             
    // |  \/  | ___ _ __ ___ | |__   ___ _ __   |_   _| __ __ _(_)_ __ (_)_ __   __ _ 
    // | |\/| |/ _ \ '_ ` _ \| '_ \ / _ \ '__|____| || '__/ _` | | '_ \| | '_ \ / _` |
    // | |  | |  __/ | | | | | |_) |  __/ | |_____| || | | (_| | | | | | | | | | (_| |
    // |_|__|_|\___|_| |_| |_|_.__/ \___|_|       |_||_|  \__,_|_|_| |_|_|_| |_|\__, |
    //  / _ \ _   _  ___ _ __ _   _ ___                                         |___/ 
    // | | | | | | |/ _ \ '__| | | / __|                                              
    // | |_| | |_| |  __/ |  | |_| \__ \                                              
    //  \__\_\\__,_|\___|_|   \__, |___/                                              
    //                        |___/                                                   

    QUERY(createMemberTrainingRelation,
        "INSERT INTO member_training_relation (memberID, trainingID) "
        "VALUES (:memberID, :trainingID);",
        PARAM(oatpp::Int64, memberID),
        PARAM(oatpp::Int64, trainingID));

    QUERY(deleteMemberTrainingRelation,
        "DELETE FROM member_training_relation "
        "WHERE memberID=:memberID AND trainingID=:trainingID;",
        PARAM(oatpp::Int64, memberID),
        PARAM(oatpp::Int64, trainingID));

    QUERY(getTrainingsByMemberID,
        "SELECT t.* FROM trainings t INNER JOIN member_training_relation mtr "
        "ON t.trainingID = mtr.trainingID WHERE mtr.memberID=:memberID;",
        PARAM(oatpp::Int64, memberID));

    QUERY(getMembersByTrainingID,
        "SELECT m.* FROM members m INNER JOIN member_training_relation mtr "
        "ON m.memberID = mtr.memberID WHERE mtr.trainingID=:trainingID;");

    //  ____                        _                        _      _____          _       _             
    // |  _ \  ___ _ __   __ _ _ __| |_ _ __ ___   ___ _ __ | |_   |_   _| __ __ _(_)_ __ (_)_ __   __ _ 
    // | | | |/ _ \ '_ \ / _` | '__| __| '_ ` _ \ / _ \ '_ \| __|____| || '__/ _` | | '_ \| | '_ \ / _` |
    // | |_| |  __/ |_) | (_| | |  | |_| | | | | |  __/ | | | ||_____| || | | (_| | | | | | | | | | (_| |
    // |____/ \___| .__/ \__,_|_|   \__|_| |_| |_|\___|_| |_|\__|    |_||_|  \__,_|_|_| |_|_|_| |_|\__, |
    //  / _ \ _   |_|___ _ __ _   _ ___                                                            |___/ 
    // | | | | | | |/ _ \ '__| | | / __|                                                                 
    // | |_| | |_| |  __/ |  | |_| \__ \                                                                 
    //  \__\_\\__,_|\___|_|   \__, |___/                                                                 
    //                        |___/                                                                      

    QUERY(createDepartmentTrainingRelation,
        "INSERT INTO department_training_relation (departmentID, trainingID) "
        "VALUES (:departmentID, :trainingID);",
        PARAM(oatpp::Int64, departmentID),
        PARAM(oatpp::Int64, trainingID));

    QUERY(deleteDepartmentTrainingRelation,
        "DELETE FROM department_training_relation "
        "WHERE departmentID=:departmentID AND trainingID=:trainingID;",
        PARAM(oatpp::Int64, departmentID),
        PARAM(oatpp::Int64, trainingID));

    QUERY(getTrainingsByDepartmentID,
        "SELECT t.* FROM trainings t INNER JOIN department_training_relation dtr "
        "ON t.trainingID = dtr.trainingID WHERE dtr.departmentID=:departmentID;",
        PARAM(oatpp::Int64, departmentID));

    QUERY(getDepartmentsByTrainingID,
        "SELECT d.* FROM departments d INNER JOIN department_training_relation dtr "
        "ON d.departmentID = dtr.departmentID WHERE dtr.trainingID=:trainingID;");
};

#include OATPP_CODEGEN_END(DbClient) ///< End code-gen section

#endif //DATABASE_CLIENT