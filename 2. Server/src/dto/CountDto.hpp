#ifndef COUNTDTO_HPP
#define COUNTDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace primus
{
    namespace dto
    {

#include OATPP_CODEGEN_BEGIN(DTO)

        /**
         * @brief DTO class representing single value. This dto may be used for counting database rows
         */
        class CountDto : public oatpp::DTO
        {

            DTO_INIT(CountDto, DTO);

            DTO_FIELD_INFO(count) {
                info->description = "Count value";
            }
            DTO_FIELD(oatpp::UInt32, count);

        };

#include OATPP_CODEGEN_END(DTO)

    } // namespace dto
} // namespace primus

#endif // COUNTDTO_HPP