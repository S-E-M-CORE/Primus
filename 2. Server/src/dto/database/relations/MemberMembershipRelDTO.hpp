#ifndef MEMBERMEMBERSHIPRELDTO_HPP
#define MEMBERMEMBERSHIPRELDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class MemberMembershipRelDTO : public oatpp::DTO
{
	DTO_INIT(MemberMembershipRelDTO, DTO /* extends */);

	DTO_FIELD(Int64, memberID);
	DTO_FIELD(Int64, membershipID);
};

#include OATPP_CODEGEN_END(DTO)

#endif // MEMBERMEMBERSHIPRELDTO_HPP