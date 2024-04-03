#ifndef DATABASEDTOS_HPP
#define DATABASEDTOS_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class AddressDto : public oatpp::DTO {

    DTO_INIT(AddressDto, DTO /* extends */)

        DTO_FIELD(oatpp::UInt32 , id);          // Address ID
        DTO_FIELD(oatpp::String, zipCode);     // Zip code
        DTO_FIELD(oatpp::String, city);        // City
        DTO_FIELD(oatpp::String, state);       // State
        DTO_FIELD(oatpp::String, houseNumber); // House number
        DTO_FIELD(oatpp::String, street);      // Street
};

class DepartmentDto : public oatpp::DTO {

    DTO_INIT(DepartmentDto, DTO /* extends */)

        DTO_FIELD(oatpp::UInt32, id);  
        DTO_FIELD(oatpp::String, name);

};

class MemberDto : public oatpp::DTO {

    DTO_INIT(MemberDto, DTO /* extends */)

    DTO_FIELD(UInt32, id);
    DTO_FIELD(String, firstName);
    DTO_FIELD(String, lastName);
    DTO_FIELD(String, email);
    DTO_FIELD(String, phoneNumber);
    DTO_FIELD(String, birthDate);
    DTO_FIELD(String, createDate);
    DTO_FIELD(String, notes);
    DTO_FIELD(Boolean, active);

};

class TrainingDto : public oatpp::DTO {

    DTO_INIT(TrainingDto, DTO /* extends */)

        DTO_FIELD(oatpp::UInt32, id);           // Training ID
        DTO_FIELD(oatpp::String, date);        // Date
        DTO_FIELD(oatpp::String, createDate);  // Create date
};

class MemberDetailsDto : public oatpp::DTO {

    DTO_INIT(MemberDetailsDto, DTO /* extends */)

        DTO_FIELD(oatpp::UInt32, memberID);         // Member ID
        DTO_FIELD(oatpp::String, firstName);       // First name
        DTO_FIELD(oatpp::String, lastName);        // Last name
        DTO_FIELD(oatpp::String, email);           // Email
        DTO_FIELD(oatpp::String, phoneNumber);     // Phone number
        DTO_FIELD(oatpp::String, birthDate);       // Birth date
        DTO_FIELD(oatpp::String, memberCreateDate);// Member create date
        DTO_FIELD(oatpp::Boolean, active);         // Active status

        DTO_FIELD(oatpp::UInt32, addressID);        // Address ID
        DTO_FIELD(oatpp::String, zipCode);         // Zip code
        DTO_FIELD(oatpp::String, city);            // City
        DTO_FIELD(oatpp::String, state);           // State
        DTO_FIELD(oatpp::String, houseNumber);     // House number
        DTO_FIELD(oatpp::String, street);          // Street

        DTO_FIELD(oatpp::UInt32, departmentID);     // Department ID
        DTO_FIELD(oatpp::String, departmentName);  // Department name

};

#include OATPP_CODEGEN_END(DTO)


#endif // DATABASEDDTOS_HPP