#ifndef PAGEDTO_HPP
#define PAGEDTO_HPP

#include "databaseDTOs/MemberDTO.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

template<class T>
class PageDTO : public oatpp::DTO {

	DTO_INIT(PageDTO, DTO)

	DTO_FIELD(UInt32, offset);
	DTO_FIELD(UInt32, limit);
	DTO_FIELD(UInt32, count);
	DTO_FIELD(Vector<T>, items);

};

class MemberPageDTO : public PageDTO<oatpp::Object<MemberDTO>> {

	DTO_INIT(MemberPageDTO, PageDTO<oatpp::Object<MemberDTO>>)

};

#include OATPP_CODEGEN_END(DTO)

#endif // PAGEDTO_HPP
