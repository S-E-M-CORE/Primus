#ifndef MEMBERSHIPDEPARTMENTRELDTO_HPP
#define MEMBERSHIPDEPARTMENTRELDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class MembershipDepartmentRelDTO : public oatpp::DTO
{
	DTO_INIT(MembershipDepartmentRelDTO, DTO /* extends */);

	DTO_FIELD(Int64, membershipID);
	DTO_FIELD(Int64, departmentID);
};

#include OATPP_CODEGEN_END(DTO)

#endif // MEMBERSHIPDEPARTMENTRELDTO_HPP