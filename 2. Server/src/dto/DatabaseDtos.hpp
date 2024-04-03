#ifndef DATABASEDTOS_HPP
#define DATABASEDTOS_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class AddressDto : public oatpp::DTO {

    DTO_INIT(AddressDto, DTO /* extends */)

<<<<<<< HEAD
        DTO_FIELD(oatpp::UInt32 , id);          // Address ID
=======
        DTO_FIELD(oatpp::Int32 , id);          // Address ID
>>>>>>> db1965b318089d88d214892967e8600fa806f9c6
        DTO_FIELD(oatpp::String, zipCode);     // Zip code
        DTO_FIELD(oatpp::String, city);        // City
        DTO_FIELD(oatpp::String, state);       // State
        DTO_FIELD(oatpp::String, houseNumber); // House number
        DTO_FIELD(oatpp::String, street);      // Street
};

class DepartmentDto : public oatpp::DTO {

    DTO_INIT(DepartmentDto, DTO /* extends */)

<<<<<<< HEAD
        DTO_FIELD(oatpp::UInt32, id);  
        DTO_FIELD(oatpp::String, name);
=======
        DTO_FIELD(oatpp::Int32, id);       // Department ID
        DTO_FIELD(oatpp::String, name);    // Department name
>>>>>>> db1965b318089d88d214892967e8600fa806f9c6

};

class MemberDto : public oatpp::DTO {

    DTO_INIT(MemberDto, DTO /* extends */)

<<<<<<< HEAD
    DTO_FIELD(UInt32, id);
    DTO_FIELD(String, firstName);
    DTO_FIELD(String, lastName);
    DTO_FIELD(String, email);
    DTO_FIELD(String, phoneNumber);
    DTO_FIELD(String, birthDate);
    DTO_FIELD(String, createDate);
    DTO_FIELD(String, notes);
    DTO_FIELD(Boolean, active);

=======
        DTO_FIELD(oatpp::Int32, id);           // Member ID
        DTO_FIELD(oatpp::String, firstName);   // First name
        DTO_FIELD(oatpp::String, lastName);    // Last name
        DTO_FIELD(oatpp::String, email);       // Email
        DTO_FIELD(oatpp::String, phoneNumber); // Phone number
        DTO_FIELD(oatpp::String, birthDate);   // Birth date
        DTO_FIELD(oatpp::String, createDate);  // Create date
        DTO_FIELD(oatpp::String, notes);       // Notes
        DTO_FIELD(oatpp::Boolean, active);     // Active status
>>>>>>> db1965b318089d88d214892967e8600fa806f9c6
};

class TrainingDto : public oatpp::DTO {

    DTO_INIT(TrainingDto, DTO /* extends */)

<<<<<<< HEAD
        DTO_FIELD(oatpp::UInt32, id);           // Training ID
=======
        DTO_FIELD(oatpp::Int32, id);           // Training ID
>>>>>>> db1965b318089d88d214892967e8600fa806f9c6
        DTO_FIELD(oatpp::String, date);        // Date
        DTO_FIELD(oatpp::String, createDate);  // Create date
};

class MemberDetailsDto : public oatpp::DTO {

    DTO_INIT(MemberDetailsDto, DTO /* extends */)

<<<<<<< HEAD
        DTO_FIELD(oatpp::UInt32, memberID);         // Member ID
=======
        DTO_FIELD(oatpp::Int32, memberID);         // Member ID
>>>>>>> db1965b318089d88d214892967e8600fa806f9c6
        DTO_FIELD(oatpp::String, firstName);       // First name
        DTO_FIELD(oatpp::String, lastName);        // Last name
        DTO_FIELD(oatpp::String, email);           // Email
        DTO_FIELD(oatpp::String, phoneNumber);     // Phone number
        DTO_FIELD(oatpp::String, birthDate);       // Birth date
        DTO_FIELD(oatpp::String, memberCreateDate);// Member create date
        DTO_FIELD(oatpp::Boolean, active);         // Active status

<<<<<<< HEAD
        DTO_FIELD(oatpp::UInt32, addressID);        // Address ID
=======
        DTO_FIELD(oatpp::Int32, addressID);        // Address ID
>>>>>>> db1965b318089d88d214892967e8600fa806f9c6
        DTO_FIELD(oatpp::String, zipCode);         // Zip code
        DTO_FIELD(oatpp::String, city);            // City
        DTO_FIELD(oatpp::String, state);           // State
        DTO_FIELD(oatpp::String, houseNumber);     // House number
        DTO_FIELD(oatpp::String, street);          // Street

<<<<<<< HEAD
        DTO_FIELD(oatpp::UInt32, departmentID);     // Department ID
=======
        DTO_FIELD(oatpp::Int32, departmentID);     // Department ID
>>>>>>> db1965b318089d88d214892967e8600fa806f9c6
        DTO_FIELD(oatpp::String, departmentName);  // Department name

};

#include OATPP_CODEGEN_END(DTO)


#endif // DATABASEDDTOS_HPP