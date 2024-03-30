#ifndef MEMBERDTO_HPP
#define MEMBERDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class MemberDTO : public oatpp::DTO
{
	DTO_INIT(MemberDTO, DTO /* extends */)

	DTO_FIELD(oatpp::Int64  , id);			// Unique identifier for each member
	DTO_FIELD(oatpp::String , firstName);	// First name of the member
	DTO_FIELD(oatpp::String , lastName);	// Last name of the member
	DTO_FIELD(oatpp::String , birthDate);	// Birth date of the member
	DTO_FIELD(oatpp::String , joinDate);	// Date when the member joined the organization
	DTO_FIELD(oatpp::Boolean, active);		// Whether or not the member is active
};

#include OATPP_CODEGEN_END(DTO)

#endif // MEMBERDTO_HPP