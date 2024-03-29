#ifndef TRAININGDTO_HPP
#define TRAININGDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class TrainingDTO : public oatpp::DTO
{
	DTO_INIT(TrainingDTO, DTO /* extends */)

	DTO_FIELD(Int64 , id);		// Unique identifier for each training
	DTO_FIELD(String, date);			// Date when the training took place
	DTO_FIELD(String, startTime);		// Start time of the training
	DTO_FIELD(String, room);			// Room where the training took place
	DTO_FIELD(String, notes);			// Notes about the training
};

#include OATPP_CODEGEN_END(DTO)

#endif // TRAININGDTO_HPP