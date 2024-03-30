#ifndef MEMBERPHONENUMBERRELDTO_HPP
#define MEMBERPHONENUMBERRELDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class MemberPhonenumberRelDTO : public oatpp::DTO
{
	DTO_INIT(MemberPhonenumberRelDTO, DTO /* extends */);

	DTO_FIELD(Int64, memberID);
	DTO_FIELD(Int64, phoneNumberID);
};

#include OATPP_CODEGEN_END(DTO)

#endif // MEMBERPHONENUMBERRELDTO_HPP