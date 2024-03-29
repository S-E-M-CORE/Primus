#ifndef ADRESSDTO_HPP
#define ADRESSDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class AddressDTO : public oatpp::DTO
{
	DTO_INIT(AddressDTO, DTO /* extends */);

	DTO_FIELD(Int64,  id);		 // Unique identifier
	DTO_FIELD(String, zipCode);		 // ZIP code of the address
	DTO_FIELD(String, city);		 // City of the address
	DTO_FIELD(String, state);		 // State of the address
	DTO_FIELD(String, houseNumber);  // House number of the address
	DTO_FIELD(String, street);		 // Street of the address
};

#include OATPP_CODEGEN_END(DTO)

#endif // ADRESSDTO_HPP