#ifndef DATABASEDTOS_HPP
#define DATABASEDTOS_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace primus
{
    namespace dto
    {
        namespace database
        {
            class AddressDto : public oatpp::DTO
            {
                /**
                 * @brief DTO representing an address in the database.
                 */
                DTO_INIT(AddressDto, DTO /* extends */)

                    DTO_FIELD_INFO(id) {
                    info->description = "Unique identifier for the address";
                }
                DTO_FIELD(oatpp::UInt32, id);

                DTO_FIELD_INFO(zipCode) {
                    info->description = "ZIP code of the address";
                }
                DTO_FIELD(oatpp::String, zipCode);

                DTO_FIELD_INFO(city) {
                    info->description = "City of the address";
                }
                DTO_FIELD(oatpp::String, city);

                DTO_FIELD_INFO(state) {
                    info->description = "State of the address";
                }
                DTO_FIELD(oatpp::String, state);

                DTO_FIELD_INFO(houseNumber) {
                    info->description = "House number of the address";
                }
                DTO_FIELD(oatpp::String, houseNumber);

                DTO_FIELD_INFO(street) {
                    info->description = "Street of the address";
                }
                DTO_FIELD(oatpp::String, street);

            };

            /**
             * @brief DTO class representing a department.
             */
            class DepartmentDto : public oatpp::DTO
            {

                DTO_INIT(DepartmentDto, DTO /* extends */)

                    DTO_FIELD_INFO(id) {
                    info->description = "Unique identifier for each department";
                }
                DTO_FIELD(oatpp::UInt32, id);

                DTO_FIELD_INFO(name) {
                    info->description = "Name of the department";
                }
                DTO_FIELD(oatpp::String, name);

            };

            /**
             * @brief DTO class representing a member.
             */
            class MemberDto : public oatpp::DTO
            {

                DTO_INIT(MemberDto, DTO /* extends */)

                    DTO_FIELD_INFO(id) {
                    info->description = "Unique identifier for each member";
                }
                DTO_FIELD(oatpp::UInt32, id);

                DTO_FIELD_INFO(firstName) {
                    info->description = "First name of the member";
                }
                DTO_FIELD(oatpp::String, firstName);

                DTO_FIELD_INFO(lastName) {
                    info->description = "Last name of the member";
                }
                DTO_FIELD(oatpp::String, lastName);

                DTO_FIELD_INFO(email) {
                    info->description = "Email address of the member";
                }
                DTO_FIELD(oatpp::String, email);

                DTO_FIELD_INFO(phoneNumber) {
                    info->description = "Phone number of the member";
                }
                DTO_FIELD(oatpp::String, phoneNumber);

                DTO_FIELD_INFO(birthDate) {
                    info->description = "Birth date of the member";
                }
                DTO_FIELD(oatpp::String, birthDate);

                DTO_FIELD_INFO(createDate) {
                    info->description = "Date when the member was created";
                }
                DTO_FIELD(oatpp::String, createDate);

                DTO_FIELD_INFO(notes) {
                    info->description = "Additional notes about the member";
                }
                DTO_FIELD(oatpp::String, notes);

                DTO_FIELD_INFO(active) {
                    info->description = "Whether or not the member is activated";
                }
                DTO_FIELD(oatpp::Boolean, active) = true;

            };


            class TrainingDto : public oatpp::DTO {

                DTO_INIT(TrainingDto, DTO /* extends */)

                    DTO_FIELD_INFO(id) {
                    info->description = "Training ID";
                }
                DTO_FIELD(oatpp::UInt32, id);

                DTO_FIELD_INFO(date) {
                    info->description = "Date of the training";
                }
                DTO_FIELD(oatpp::String, date);

                DTO_FIELD_INFO(createDate) {
                    info->description = "Date when the training record was created";
                }
                DTO_FIELD(oatpp::String, createDate);

            };

            /**
             * @brief DTO class representing detailed information about a member.
             */
            class MemberDetailsDto : public oatpp::DTO
            {

                DTO_INIT(MemberDetailsDto, DTO /* extends */)

                    DTO_FIELD_INFO(memberID) {
                    info->description = "Member ID";
                }
                DTO_FIELD(oatpp::UInt32, memberID);

                DTO_FIELD_INFO(firstName) {
                    info->description = "First name of the member";
                }
                DTO_FIELD(oatpp::String, firstName);

                DTO_FIELD_INFO(lastName) {
                    info->description = "Last name of the member";
                }
                DTO_FIELD(oatpp::String, lastName);

                DTO_FIELD_INFO(email) {
                    info->description = "Email address of the member";
                }
                DTO_FIELD(oatpp::String, email);

                DTO_FIELD_INFO(phoneNumber) {
                    info->description = "Phone number of the member";
                }
                DTO_FIELD(oatpp::String, phoneNumber);

                DTO_FIELD_INFO(birthDate) {
                    info->description = "Birth date of the member";
                }
                DTO_FIELD(oatpp::String, birthDate);

                DTO_FIELD_INFO(memberCreateDate) {
                    info->description = "Date when the member joined the organization";
                }
                DTO_FIELD(oatpp::String, memberCreateDate);

                DTO_FIELD_INFO(active) {
                    info->description = "Active status of the member";
                }
                DTO_FIELD(oatpp::Boolean, active);

                DTO_FIELD_INFO(addressID) {
                    info->description = "Address ID of the member";
                }
                DTO_FIELD(oatpp::UInt32, addressID);

                DTO_FIELD_INFO(zipCode) {
                    info->description = "Zip code of the member's address";
                }
                DTO_FIELD(oatpp::String, zipCode);

                DTO_FIELD_INFO(city) {
                    info->description = "City of the member's address";
                }
                DTO_FIELD(oatpp::String, city);

                DTO_FIELD_INFO(state) {
                    info->description = "State of the member's address";
                }
                DTO_FIELD(oatpp::String, state);

                DTO_FIELD_INFO(houseNumber) {
                    info->description = "House number of the member's address";
                }
                DTO_FIELD(oatpp::String, houseNumber);

                DTO_FIELD_INFO(street) {
                    info->description = "Street of the member's address";
                }
                DTO_FIELD(oatpp::String, street);

                DTO_FIELD_INFO(departmentID) {
                    info->description = "Department ID of the member";
                }
                DTO_FIELD(oatpp::UInt32, departmentID);

                DTO_FIELD_INFO(departmentName) {
                    info->description = "Department name of the member";
                }
                DTO_FIELD(oatpp::String, departmentName);

            };
#include OATPP_CODEGEN_END(DTO)
        } // namespace database
    } // namespace dto
} // namespace primus

#endif // DATABASEDDTOS_HPP