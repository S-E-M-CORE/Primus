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
            //     _       _     _                   ____  _        
            //    / \   __| | __| |_ __ ___  ___ ___|  _ \| |_ ___  
            //   / _ \ / _` |/ _` | '__/ _ \/ __/ __| | | | __/ _ \ 
            //  / ___ \ (_| | (_| | | |  __/\__ \__ \ |_| | || (_) |
            // /_/   \_\__,_|\__,_|_|  \___||___/___/____/ \__\___/ 
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

                DTO_FIELD_INFO(postalCode) {
                    info->description = "ZIP code of the address";
                }
                DTO_FIELD(oatpp::String, postalCode);

                DTO_FIELD_INFO(city) {
                    info->description = "City of the address";
                }
                DTO_FIELD(oatpp::String, city);

                DTO_FIELD_INFO(country) {
                    info->description = "State of the address";
                }
                DTO_FIELD(oatpp::String, country);

                DTO_FIELD_INFO(houseNumber) {
                    info->description = "House number of the address";
                }
                DTO_FIELD(oatpp::UInt32, houseNumber);

                DTO_FIELD_INFO(street) {
                    info->description = "Street of the address";
                }
                DTO_FIELD(oatpp::String, street);

            };

            //  ____        _       ____  _        
            // |  _ \  __ _| |_ ___|  _ \| |_ ___  
            // | | | |/ _` | __/ _ \ | | | __/ _ \ 
            // | |_| | (_| | ||  __/ |_| | || (_) |
            // |____/ \__,_|\__\___|____/ \__\___/ 
            /**
             * @brief DTO class representing a single Date.
             */
            class DateDto : public oatpp::DTO
            {

                DTO_INIT(DateDto, DTO)

                    DTO_FIELD(oatpp::String, date);
            };

            //  ____                        _                        _   ____  _        
            // |  _ \  ___ _ __   __ _ _ __| |_ _ __ ___   ___ _ __ | |_|  _ \| |_ ___  
            // | | | |/ _ \ '_ \ / _` | '__| __| '_ ` _ \ / _ \ '_ \| __| | | | __/ _ \ 
            // | |_| |  __/ |_) | (_| | |  | |_| | | | | |  __/ | | | |_| |_| | || (_) |
            // |____/ \___| .__/ \__,_|_|   \__|_| |_| |_|\___|_| |_|\__|____/ \__\___/ 
            //            |_|                                                           
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

            //  __  __                _               ____  _        
            // |  \/  | ___ _ __ ___ | |__   ___ _ __|  _ \| |_ ___  
            // | |\/| |/ _ \ '_ ` _ \| '_ \ / _ \ '__| | | | __/ _ \ 
            // | |  | |  __/ | | | | | |_) |  __/ |  | |_| | || (_) |
            // |_|  |_|\___|_| |_| |_|_.__/ \___|_|  |____/ \__\___/ 
            /**
             * @brief DTO class representing a member.
             */
            class MemberDto : public oatpp::DTO
            {
                DTO_INIT(MemberDto, DTO /* extends */);

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
#include OATPP_CODEGEN_END(DTO)
        } // namespace database
    } // namespace dto
} // namespace primus

#endif // DATABASEDDTOS_HPP