#ifndef MEMBERCONTROLLER_HPP
#define MEMBERCONTROLLER_HPP

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "dto/DatabaseDtos.hpp"
#include "dto/StatusDto.hpp"
#include "dto/PageDto.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) // Begin API Controller codegen

class MemberController : public oatpp::web::server::api::ApiController {
private:
    OATPP_COMPONENT(std::shared_ptr<DatabaseClient>, m_database);
public:
    MemberController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper) {}

    static std::shared_ptr<MemberController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
    )
    {
        return std::make_shared<MemberController>(objectMapper);
    }

    ENDPOINT("GET", "/api/members/birthday/upcoming", getMembersWithUpcomingBirthday,
        QUERY(oatpp::UInt32, limit))
    {
        auto dbResult = m_database->getMembersWithUpcomingBirthday(limit);
        OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

        auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<MemberDto>>>();

        auto page = PageDto<oatpp::Object<MemberDto>>::createShared();
        page->limit = limit;
        page->count = items->size();
        page->items = items;

        return createDtoResponse(Status::CODE_200, page);
    }
    
    ENDPOINT("GET", "/api/members/training/most-often", getMembersWithMostTrainings,
        QUERY(oatpp::UInt32, limit), QUERY(oatpp::UInt32, offset))
    {
        auto dbResult = m_database->getMembersWithMostTrainings(limit, offset);
        OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

        auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<MemberDto>>>();

        auto page = PageDto<oatpp::Object<MemberDto>>::createShared();
        page->offset = offset;
        page->limit = limit;
        page->count = items->size();
        page->items = items;

        return createDtoResponse(Status::CODE_200, page);
    }
    
    ENDPOINT("GET", "/api/member/{id}/department", getDepartmentsOfMember,
        PATH(oatpp::UInt32, id))
    {
        auto dbResult = m_database->getDepartmentsOfMember(id);
        OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

        auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<DepartmentDto>>>();

        auto page = PageDto<oatpp::Object<DepartmentDto>>::createShared();
        page->count = items->size();
        page->items = items;

        return createDtoResponse(Status::CODE_200, page);
    }

    ENDPOINT("GET", "/api/members/all", getAllMembers,
        QUERY(oatpp::UInt32, limit), QUERY(oatpp::UInt32, offset))
    {
        auto dbResult = m_database->getAllMembers(offset, limit);
        OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

        auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<MemberDto>>>();

        auto page = PageDto<oatpp::Object<MemberDto>>::createShared();
        page->offset = offset;
        page->limit = limit;
        page->count = items->size();
        page->items = items;

        return createDtoResponse(Status::CODE_200, page);
    }

    ENDPOINT("GET", "/api/members/active", getActiveMembers,
        QUERY(oatpp::UInt32, limit), QUERY(oatpp::UInt32, offset))
    {
        auto dbResult = m_database->getActiveMembers(limit, offset);

        auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<MemberDto>>>();

        auto page = PageDto<oatpp::Object<MemberDto>>::createShared();

        page->offset = offset;
        page->limit = limit;
        page->count = items->size();
        page->items = items;

        return createDtoResponse(Status::CODE_200, page);
    }

    ENDPOINT("GET", "/api/members/inactive", getInactiveMembers,
        QUERY(oatpp::UInt32, limit), QUERY(oatpp::UInt32, offset))
    {
        auto dbResult = m_database->getInactiveMembers(limit, offset);

        auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<MemberDto>>>();

        auto page = PageDto<oatpp::Object<MemberDto>>::createShared();

        page->offset = offset;
        page->limit = limit;
        page->count = items->size();
        page->items = items;

        return createDtoResponse(Status::CODE_200, page);
    }

    ENDPOINT("UPDATE", "/api/member/{id}/activate", activateMember,
        PATH(oatpp::UInt32, id))
    {
        auto dbResult = m_database->activateMember(id);
        OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_404, "User was not found");
        return createResponse(Status::CODE_200, "Member activated");
    }

    ENDPOINT("UPDATE", "/api/member/{id}/deactivate", deactivateMember,
        PATH(oatpp::UInt32, id))
    {
        auto dbResult = m_database->deactivateMember(id);
        OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_404, "User was not found");
        return createResponse(Status::CODE_200, "Member deactivated");
    }

    ENDPOINT("GET", "/api/member/{id}", getMemberById,
        PATH(oatpp::UInt32, id))
    {
        auto dbResult = m_database->getMemberById(id);
        OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_404, "User was not found");

        auto user = dbResult->fetch<oatpp::Object<MemberDto>>();

        return createDtoResponse(Status::CODE_200, user);
    }

    ENDPOINT("POST", "/api/member", createMember,
        BODY_DTO(Object<MemberDto>, member))
    {
        auto dbResult = m_database->createMember(member);
        OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, "Bad Request");

        auto memberRet = dbResult->fetch<oatpp::Object<MemberDto>>();

        return createDtoResponse(Status::CODE_200, memberRet);
    }

    ENDPOINT("PUT", "/api/member", updateMember,
        BODY_DTO(Object<MemberDto>, member))
    {
        auto userCheck = m_database->getMemberById(member->id);

        OATPP_ASSERT_HTTP(userCheck->isSuccess(), Status::CODE_404, "User was not found");
        
        m_database->updateMember(member);

        return createDtoResponse(Status::CODE_200, member);
    }

    ENDPOINT("GET", "/api/member/{id}/address", getMemberAddress,
        PATH(UInt32, id))
    {
        auto dbResult = m_database->getMemberAddress(id);

        OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_404, "User was not found");

        auto adress = dbResult->fetch<oatpp::Object<AddressDto>>();

        return createDtoResponse(Status::CODE_200, adress);
    }

    ENDPOINT("GET", "/api/member/{id}/membership-fee", getMembershipFee,
        PATH(UInt32, id))
    {
        return createResponse(Status::CODE_501, "Not Implemented");
    }

    ENDPOINT("GET", "/api/member/{id}/trainings", getMemberTrainings,
        PATH(oatpp::UInt32, id), QUERY(oatpp::UInt32, limit), QUERY(oatpp::UInt32, offset))
    {
        return createResponse(Status::CODE_501, "Not Implemented");
    }

    ENDPOINT("GET", "/api/member/{id}/purchase/weapons/allowed", isWeaponPurchaseAllowed,
        PATH(UInt32, id))
    {
        return createResponse(Status::CODE_501, "Not Implemented");
    }

    ENDPOINT("GET", "/api/members/all/count", getMemberCountAll)
    {
        return createResponse(Status::CODE_501, "Not Implemented");
    }

    ENDPOINT("GET", "/api/members/active/count", getMemberCountActive)
    {
        return createResponse(Status::CODE_501, "Not Implemented");
    }

    ENDPOINT("GET", "/api/members/inactive/count", getMemberCountInactive)
    {
        return createResponse(Status::CODE_501, "Not Implemented");
    }

};

#include OATPP_CODEGEN_END(ApiController) // End API Controller codegen

#endif // MEMBERCONTROLLER_HPP
