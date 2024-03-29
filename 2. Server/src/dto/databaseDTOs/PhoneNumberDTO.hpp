#ifndef PHONENUMBERDTO_HPP
#define PHONENUMBERDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class PhoneNumberDTO : public oatpp::DTO
{
	DTO_INIT(PhoneNumberDTO, DTO /* extends */);

	DTO_FIELD(Int64, phoneNumberID); // Unique identifier for each phone number
	DTO_FIELD(String, phoneNumber);  // Phone number
};


#include OATPP_CODEGEN_END(DTO)

#endif // PHONENUMBERDTO_HPP