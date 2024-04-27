#ifndef PAGEDTO_HPP
#define PAGEDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "DatabaseDtos.hpp"

namespace primus
{
    namespace dto
    {
#include OATPP_CODEGEN_BEGIN(DTO)
        //  ____                  ____  _        
        // |  _ \ __ _  __ _  ___|  _ \| |_ ___  
        // | |_) / _` |/ _` |/ _ \ | | | __/ _ \ 
        // |  __/ (_| | (_| |  __/ |_| | || (_) |
        // |_|   \__,_|\__, |\___|____/ \__\___/ 
        //             |___/                     
        template<class T>
        class PageDto : public oatpp::DTO {

            DTO_INIT(PageDto, DTO);

            DTO_FIELD(UInt32, offset);
            DTO_FIELD_INFO(offset) {
                info->description = "Offset value for pagination";
                info->required = true;
            }

            DTO_FIELD(UInt32, limit);
            DTO_FIELD_INFO(limit) {
                info->description = "Limit value for pagination";
                info->required = true;
            }

            DTO_FIELD(UInt32, count);
            DTO_FIELD_INFO(count) {
                info->description = "Total count of items";
                info->required = true;
            }

            DTO_FIELD(Vector<T>, items);
            DTO_FIELD_INFO(items) {
                info->description = "List of items";
            }

        };

        using MemberPageDto     = primus::dto::PageDto<oatpp::Object<primus::dto::database::MemberDto>>;
        using AddressPageDto    = primus::dto::PageDto<oatpp::Object<primus::dto::database::AddressDto>>;
        using DepartmentPageDto = primus::dto::PageDto<oatpp::Object<primus::dto::database::DepartmentDto>>;
        using DatePageDto       = primus::dto::PageDto<oatpp::Object<primus::dto::database::DateDto>>;

#include OATPP_CODEGEN_END(DTO)

    } // namespace dto
} // namespace primus

#endif // PAGEDTO_HPP
