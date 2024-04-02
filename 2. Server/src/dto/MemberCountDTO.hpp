#ifndef MEMBERCOUNTDTO_HPP
#define MEMBERCOUNTDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)
class MemberCountDTO : public oatpp::DTO {

    DTO_INIT(MemberCountDTO, DTO)

        DTO_FIELD(oatpp::Int32, count);

};

#include OATPP_CODEGEN_END(DTO)

#endif // MEMBERCOUNTDTO_HPP