#ifndef MEMBERADRESSRELDTO_HPP
#define MEMBERADRESSRELDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class MemberAddressRelDTO : public oatpp::DTO
{
	DTO_INIT(MemberAddressRelDTO, DTO /* extends */);

	DTO_FIELD(Int64, memberID);
	DTO_FIELD(Int64, adressID);
};

#include OATPP_CODEGEN_END(DTO)

#endif // MEMBERADRESSRELDTO_HPP