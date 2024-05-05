#ifndef STATUSDTO_HPP
#define STATUSDTO_HPP

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

namespace primus
{
    namespace dto
    {
#include OATPP_CODEGEN_BEGIN(DTO)
        //  ____  _        _             ____  _        
        // / ___|| |_ __ _| |_ _   _ ___|  _ \| |_ ___  
        // \___ \| __/ _` | __| | | / __| | | | __/ _ \ 
        //  ___) | || (_| | |_| |_| \__ \ |_| | || (_) |
        // |____/ \__\__,_|\__|\__,_|___/____/ \__\___/ 
        /**
        * @brief Data transfer object (DTO) class for representing status information.
        */
        class StatusDto : public oatpp::DTO
        {
            using Int32 = oatpp::Int32;
            using String = oatpp::String;

            DTO_INIT(StatusDto, DTO); /**< Macro to initialize the DTO. */

            DTO_FIELD(Int32, code); /**< HTML status code field. */
            DTO_FIELD_INFO(code) {  /**< Information about the code field. */
                info->description = "Status code";
            }

            DTO_FIELD(String, status); /**< Short status text field. */
            DTO_FIELD_INFO(status) {   /**< Information about the status field. */
                info->description = "Short status text";
            }

            DTO_FIELD(String, message); /**< Verbose message field. */
            DTO_FIELD_INFO(message) {   /**< Information about the message field. */
                info->description = "Verbose message";
            }
        };
#include OATPP_CODEGEN_END(DTO)

    } // namespace dto
} // namespace primus
#endif // STATUSDTO_HPP
