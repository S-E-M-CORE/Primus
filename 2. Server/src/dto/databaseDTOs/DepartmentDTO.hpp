#ifndef DEPARTMENTDTO_HPP
#define DEPARTMENTDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class DepartmentDTO : public oatpp::DTO
{
	DTO_INIT(DepartmentDTO, DTO /* extends */)

	DTO_FIELD(Int64	 , departmentID);	// Unique identifier for each department
	DTO_FIELD(String , name);			// Name of the department
	DTO_FIELD(Float32, monthlyFee);		// Monthly fee for the department
	DTO_FIELD(Boolean, active);			// Whether or not the department is active
};


#include OATPP_CODEGEN_END(DTO)

#endif // DEPARTMENTDTO_HPP