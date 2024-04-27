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
            /**
            * @brief Data transfer object (DTO) class for representing an address in the database.
            */
            class AddressDto : public oatpp::DTO
            {
                DTO_INIT(AddressDto, DTO) /**< Macro to initialize the DTO. */

                DTO_FIELD(oatpp::UInt32, id) = static_cast<uint32_t>(0); /**< Unique identifier field. */
                DTO_FIELD_INFO(id) { /**< Information about the id field. */
                    info->description = "Unique identifier for the address";
                }

                DTO_FIELD(oatpp::String, postalCode); /**< Postal code field. */
                DTO_FIELD_INFO(postalCode) { /**< Information about the postalCode field. */
                    info->description = "ZIP code of the address";
                }

                DTO_FIELD(oatpp::String, city); /**< City field. */
                DTO_FIELD_INFO(city) { /**< Information about the city field. */
                    info->description = "City of the address";
                }

                DTO_FIELD(oatpp::String, country) = "Germany"; /**< Country field. */
                DTO_FIELD_INFO(country) { /**< Information about the country field. */
                    info->description = "State of the address";
                }

                DTO_FIELD(oatpp::UInt32, houseNumber); /**< House number field. */
                DTO_FIELD_INFO(houseNumber) { /**< Information about the houseNumber field. */
                    info->description = "House number of the address";
                }

                DTO_FIELD(oatpp::String, street); /**< Street field. */
                DTO_FIELD_INFO(street) { /**< Information about the street field. */
                    info->description = "Street of the address";
                }
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

                DTO_INIT(DepartmentDto, DTO /* extends */);

                DTO_FIELD(oatpp::UInt32, id) = static_cast<uint32_t>(0);
                DTO_FIELD_INFO(id) {
                info->description = "Unique identifier for each department";
                }

                DTO_FIELD(oatpp::String, name) = "";
                DTO_FIELD_INFO(name) {
                    info->description = "Name of the department";
                }

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

                DTO_FIELD(oatpp::UInt32, id) = static_cast<uint32_t>(0);
                DTO_FIELD_INFO(id) {
                    info->description = "Unique identifier for each member";
                }

                DTO_FIELD(oatpp::String, firstName);
                DTO_FIELD_INFO(firstName) {
                    info->description = "First name of the member";
                    info->required = true;
                }

                DTO_FIELD(oatpp::String, lastName);
                DTO_FIELD_INFO(lastName) {
                    info->description = "Last name of the member";
                    info->required = true;
                }

                DTO_FIELD(oatpp::String, email);
                DTO_FIELD_INFO(email) {
                    info->description = "Email address of the member";
                    info->required = true;
                }

                DTO_FIELD(oatpp::String, phoneNumber);
                DTO_FIELD_INFO(phoneNumber) {
                    info->description = "Phone number of the member";
                    info->required = true;
                }

                DTO_FIELD(oatpp::String, birthDate);
                DTO_FIELD_INFO(birthDate) {
                    info->description = "Birth date of the member";
                }

                DTO_FIELD(oatpp::String, createDate);
                DTO_FIELD_INFO(createDate) {
                    info->description = "Date when the member was created";
                }

                DTO_FIELD(oatpp::String, notes);
                DTO_FIELD_INFO(notes) {
                    info->description = "Additional notes about the member";
                }

                DTO_FIELD(oatpp::Boolean, active) = true;
                DTO_FIELD_INFO(active) {
                    info->description = "Whether or not the member is activated";
                }
            };
#include OATPP_CODEGEN_END(DTO)
        } // namespace database
    } // namespace dto
} // namespace primus

#endif // DATABASEDDTOS_HPP