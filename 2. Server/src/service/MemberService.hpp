#ifndef MEMBER_SERVICE_HPP
#define MEMBER_SERVICE_HPP

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/Types.hpp"

#include "database/DatabaseClient.hpp"
#include "dto/DatabaseDtos.hpp"
#include "dto/PageDto.hpp"
#include "dto/MembershipFeeDto.hpp"
#include "dto/BooleanDto.hpp"

class MemberService {
private:
    typedef oatpp::web::protocol::http::Status Status;

private:
    OATPP_COMPONENT(std::shared_ptr<DatabaseClient>, m_database);

public:
    oatpp::Vector < oatpp::Object<MemberPageDto>> getAllMembers(oatpp::Int32 limit, oatpp::Int32 offset);

    oatpp::Vector < oatpp::Object<MemberPageDto>> getActiveMembers(oatpp::Int32 limit, oatpp::Int32 offset);

    oatpp::Vector < oatpp::Object<MemberPageDto>> getInactiveMembers(oatpp::Int32 limit, oatpp::Int32 offset);

    oatpp::Vector < oatpp::Object<MemberPageDto>> filterMembersByFirstName(const oatpp::String& name, oatpp::Int32 limit, oatpp::Int32 offset);

    oatpp::Vector < oatpp::Object<MemberPageDto>> filterMembersByLastName(const oatpp::String& name, oatpp::Int32 limit, oatpp::Int32 offset);

    void activateMember(oatpp::Int32 id);

    void deactivateMember(oatpp::Int32 id);

    oatpp::Object<MemberDto> getMemberById(oatpp::Int32 id);

    oatpp::Vector<oatpp::Object<AddressDto>> getMemberAddress(oatpp::Int32 id);

    oatpp::Object<MembershipFeeDto> getMembershipFee(oatpp::Int32 id);

    oatpp::Object<PageDto<oatpp::Object<TrainingDto>>> getMemberTrainings(oatpp::Int32 id, oatpp::Int32 limit, oatpp::Int32 offset);

    oatpp::Object<BooleanDto> isWeaponPurchaseAllowed(oatpp::Int32 id);
};

#endif // MEMBER_SERVICE_HPP
