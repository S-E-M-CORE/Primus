#ifndef BOOLEANDTO_HPP
#define BOOLEANDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)
class BooleanDto : public oatpp::DTO {

    DTO_INIT(BooleanDto, DTO)

        DTO_FIELD(oatpp::Boolean, value);

};

#include OATPP_CODEGEN_END(DTO)

#endif // BOOLEANDTO_HPP