#ifndef COUNTDTO_HPP
#define COUNTDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)
class CountDto : public oatpp::DTO {

    DTO_INIT(CountDto, DTO)

        DTO_FIELD(oatpp::Int32, count);

};

#include OATPP_CODEGEN_END(DTO)

#endif // COUNTDTO_HPP