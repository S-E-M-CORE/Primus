#ifndef PAGEDTO_HPP
#define PAGEDTO_HPP

#include "DatabaseDtos.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

template<class T>
class PageDto : public oatpp::DTO {

	DTO_INIT(PageDto, DTO)

	DTO_FIELD(UInt32, offset);
	DTO_FIELD(UInt32, limit);
	DTO_FIELD(UInt32, count);
	DTO_FIELD(Vector<T>, items);

};

class MemberPageDto : public PageDto<oatpp::Object<MemberDto>> {

	DTO_INIT(MemberPageDto, PageDto<oatpp::Object<MemberDto>>)

};

#include OATPP_CODEGEN_END(DTO)

#endif // PAGEDTO_HPP
