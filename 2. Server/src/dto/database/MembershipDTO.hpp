#ifndef MEMBERSHIPDTO_HPP
#define MEMBERSHIPDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class MembershipDTO : public oatpp::DTO {
	DTO_INIT(MembershipDTO, DTO /* extends */);

	DTO_FIELD(Int64  , id);				// Unique identifier for each membership
	DTO_FIELD(Float32, membershipFee);  // Membership fee for the membership
	DTO_FIELD(Boolean, active);			// Whether or not the membership is active
};


#include OATPP_CODEGEN_END(DTO)

#endif // MEMBERSHIPDTO_HPP