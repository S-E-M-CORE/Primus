#ifndef DATABASE_CLIENT
#define DATABASE_CLIENT

#include "oatpp-sqlite/orm.hpp"
#include "oatpp/orm/SchemaMigration.hpp"
#include "oatpp/orm/DbClient.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include "dto/databaseDTOs/MemberDTO.hpp"
#include "dto/databaseDTOs/AdressDTO.hpp"
#include "dto/databaseDTOs/DatabaseDTOs.hpp"
#include "dto/databaseDTOs/DepartmentDTO.hpp"
#include "dto/databaseDTOs/EmailDTO.hpp"
#include "dto/databaseDTOs/MemberDTO.hpp"
#include "dto/databaseDTOs/MembershipDTO.hpp"
#include "dto/databaseDTOs/PhoneNumberDTO.hpp"
#include "dto/databaseDTOs/TrainingDTO.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

class DatabaseClient : public oatpp::orm::DbClient {
public:

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

    //  __  __                _                  ___                            
    // |  \/  | ___ _ __ ___ | |__   ___ _ __   / _ \ _   _  ___ _ __ _   _ ___ 
    // | |\/| |/ _ \ '_ ` _ \| '_ \ / _ \ '__| | | | | | | |/ _ \ '__| | | / __|
    // | |  | |  __/ | | | | | |_) |  __/ |    | |_| | |_| |  __/ |  | |_| \__ \
    // |_|  |_|\___|_| |_| |_|_.__/ \___|_|     \__\_\\__,_|\___|_|   \__, |___/
    //                                                                |___/     

    QUERY(createMember,
        "INSERT INTO members"
        "(firstName, lastName, birthDate, joinDate, active) "
        "VALUES (:member.firstName, :member.lastName, :member.birthDate, :member.joinDate, :member.active);",
        PARAM(oatpp::Object<MemberDTO>, member));

    QUERY(updateMember,
        "UPDATE members "
        "SET "
        "firstName=:member.firstName"
        "lastName =:member.lastName "
        "birthDate=:member.birthDate"
        "joinDate =:member.joinDate "
        "active   =:member.active   "
        "WHERE "
        " id=:member.id;",
        PARAM(oatpp::Object<MemberDTO>, member));

    QUERY(getMemberById,
        "SELECT * FROM members WHERE id=:id;",
        PARAM(oatpp::Int64, id));

    QUERY(getAllMembers,
        "SELECT * FROM members LIMIT :limit OFFSET :offset;",
        PARAM(oatpp::UInt32, offset),
        PARAM(oatpp::UInt32, limit));

    QUERY(deleteMemberById,
        "DELETE FROM members WHERE id=:id;",
        PARAM(oatpp::Int64, id));


    //     _       _                      ___                            
    //    / \   __| |_ __ ___  ___ ___   / _ \ _   _  ___ _ __ _   _ ___ 
    //   / _ \ / _` | '__/ _ \/ __/ __| | | | | | | |/ _ \ '__| | | / __|
    //  / ___ \ (_| | | |  __/\__ \__ \ | |_| | |_| |  __/ |  | |_| \__ \
    // /_/   \_\__,_|_|  \___||___/___/  \__\_\\__,_|\___|_|   \__, |___/
    //                                                         |___/     

    QUERY(createAddress,
        "INSERT INTO addresses (zipCode, city, state, houseNumber, street)"
        "VALUES (:adress.zipCode, :adress.city, :adress.state, :adress.houseNumber, :adress.street);",
        PARAM(oatpp::Object<AddressDTO>, adress));

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
        "INSERT INTO phone_numbers (phoneNumber) "
        "VALUES (:phoneNumber.number);",
        PARAM(oatpp::Object<PhoneNumberDTO>, phoneNumber));

    //  _____      __  __       _ _    ___                            
    // | ____|    |  \/  | __ _(_) |  / _ \ _   _  ___ _ __ _   _ ___ 
    // |  _| _____| |\/| |/ _` | | | | | | | | | |/ _ \ '__| | | / __|
    // | |__|_____| |  | | (_| | | | | |_| | |_| |  __/ |  | |_| \__ \
    // |_____|    |_|  |_|\__,_|_|_|  \__\_\\__,_|\___|_|   \__, |___/
    //                                                      |___/     

    QUERY(createEmail,
        "INSERT INTO emails (email) "
        "VALUES (:email.email);",
        PARAM(oatpp::Object<EmailDTO>, email));

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
        "INSERT INTO memberships (membershipFee, active) "
        "VALUES (:membership.membershipFee, :membership.active);",
        PARAM(oatpp::Object<MembershipDTO>, membership));

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
        "INSERT INTO departments (name, active) "
        "VALUES (:department.name, :department.active);",
        PARAM(oatpp::Object<DepartmentDTO>, department));

    //  _____          _       _                ___                            
    // |_   _| __ __ _(_)_ __ (_)_ __   __ _   / _ \ _   _  ___ _ __ _   _ ___ 
    //   | || '__/ _` | | '_ \| | '_ \ / _` | | | | | | | |/ _ \ '__| | | / __|
    //   | || | | (_| | | | | | | | | | (_| | | |_| | |_| |  __/ |  | |_| \__ \
    //   |_||_|  \__,_|_|_| |_|_|_| |_|\__, |  \__\_\\__,_|\___|_|   \__, |___/
    //                                 |___/                         |___/     

    QUERY(createTraining,
        "INSERT INTO trainings (date, startTime, room, notes) "
        "VALUES (:training.date, :training.startTime, :training.room, :training.notes);",
        PARAM(oatpp::Object<TrainingDTO>, training));

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


};

#include OATPP_CODEGEN_END(DbClient) ///< End code-gen section

#endif //DATABASE_CLIENT