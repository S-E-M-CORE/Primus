#ifndef MEMBEREMAILRELDTO_HPP
#define MEMBEREMAILRELDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class MemberEmailRelDTO : public oatpp::DTO
{
	DTO_INIT(MemberEmailRelDTO, DTO /* extends */);

	DTO_FIELD(Int64, memberID);
	DTO_FIELD(Int64, emailID);
};

#include OATPP_CODEGEN_END(DTO)

#endif // MEMBEREMAILRELDTO_HPP