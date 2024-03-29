#ifndef DATABASEDTOS_HPP
#define DATABASEDTOS_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include "AdressDTO.hpp"
#include "DepartmentDTO.hpp"
#include "EmailDTO.hpp"
#include "MemberDTO.hpp"
#include "MembershipDTO.hpp"
#include "PhoneNumberDTO.hpp"
#include "TrainingDTO.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class MemberAdressRelDTO : public oatpp::DTO
{
	DTO_INIT(MemberAdressRelDTO, DTO /* extends */);

	DTO_FIELD(Int64, memberID);
	DTO_FIELD(Int64, adressID);
};

class MemberEmailRelDTO : public oatpp::DTO
{
	DTO_INIT(MemberEmailRelDTO, DTO /* extends */);

	DTO_FIELD(Int64, memberID);
	DTO_FIELD(Int64, emailID);
};

class MemberPhonenumberRelDTO : public oatpp::DTO
{
	DTO_INIT(MemberPhonenumberRelDTO, DTO /* extends */);

	DTO_FIELD(Int64, memberID);
	DTO_FIELD(Int64, phoneNumberID);
};

class MemberMembershipRelDTO : public oatpp::DTO
{
	DTO_INIT(MemberMembershipRelDTO, DTO /* extends */);

	DTO_FIELD(Int64, memberID);
	DTO_FIELD(Int64, membershipID);
};

class MemberTrainingRelDTO : public oatpp::DTO
{
	DTO_INIT(MemberTrainingRelDTO, DTO /* extends */);

	DTO_FIELD(Int64, memberID);
	DTO_FIELD(Int64, trainingID);
};

class DepartmentTrainingRelDTO : public oatpp::DTO
{
	DTO_INIT(DepartmentTrainingRelDTO, DTO /* extends */);

	DTO_FIELD(Int64, departmentID);
	DTO_FIELD(Int64, trainingID);
};

#include OATPP_CODEGEN_END(DTO)

#endif // DATABASEDTOS_HPP