#ifndef MEMBERSHIPFEEDTO_HPP
#define MEMBERSHIPFEEDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)
class MembershipFeeDto : public oatpp::DTO
{

    DTO_INIT(MembershipFeeDto, DTO)

        DTO_FIELD(oatpp::Int32, fee);

};

#include OATPP_CODEGEN_END(DTO)

#endif // MEMBERSHIPFEEDTO_HPP