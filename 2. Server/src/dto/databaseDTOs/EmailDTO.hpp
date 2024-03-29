#ifndef EMAILDTO_HPP
#define EMAILDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class EmailDTO : public oatpp::DTO
{
	DTO_INIT(EmailDTO, DTO /* extends */)

	DTO_FIELD(Int64, id);		// Unique identifier for each email
	DTO_FIELD(String, email);  // Email address
};

#include OATPP_CODEGEN_END(DTO)

#endif // EMAILDTO_HPP