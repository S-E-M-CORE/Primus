#ifndef MEMBERTRAININGRELDTO_HPP
#define MEMBERTRAININGRELDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class MemberTrainingRelDTO : public oatpp::DTO
{
	DTO_INIT(MemberTrainingRelDTO, DTO /* extends */);

	DTO_FIELD(Int64, memberID);
	DTO_FIELD(Int64, trainingID);
};

#include OATPP_CODEGEN_END(DTO)

#endif // MEMBERTRAININGRELDTO_HPP