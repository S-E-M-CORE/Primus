#ifndef DEPARTMENTTRAININGRELDTO_DTO
#define DEPARTMENTTRAININGRELDTO_DTO

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class DepartmentTrainingRelDTO : public oatpp::DTO
{
	DTO_INIT(DepartmentTrainingRelDTO, DTO /* extends */);

	DTO_FIELD(Int64, departmentID);
	DTO_FIELD(Int64, trainingID);
};

#include OATPP_CODEGEN_END(DTO)

#endif // DEPARTMENTTRAININGRELDTO_DTO