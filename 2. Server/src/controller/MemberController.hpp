#ifndef MEMBERCONTROLLER_HPP
#define MEMBERCONTROLLER_HPP

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "dto/StatusDto.hpp"
#include "dto/PageDto.hpp"
#include "dto/CountDto.hpp"
#include "dto/MembershipFeeDto.hpp"
#include "dto/BooleanDto.hpp"
#include "general/constants.hpp"

namespace primus {
    namespace apicontroller {
        namespace member_endpoint {

#include OATPP_CODEGEN_BEGIN(ApiController) // Begin API Controller codegen

            using primus::dto::database::MemberDto;
            using primus::dto::database::DepartmentDto;
            using primus::dto::database::TrainingDto;
            using primus::dto::database::AddressDto;
            using primus::dto::PageDto;
            using primus::dto::MemberPageDto;
            using primus::dto::CountDto;
            using primus::dto::MembershipFeeDto;
            using primus::dto::BooleanDto;

            class MemberController : public oatpp::web::server::api::ApiController
            {
            private:
                OATPP_COMPONENT(std::shared_ptr<primus::component::DatabaseClient>, m_database);
            public:
                MemberController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
                    : oatpp::web::server::api::ApiController(objectMapper)
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "MemberController (oatpp::web::server::api::ApiController) initialized");
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);

                }

                static std::shared_ptr<MemberController> createShared(
                    OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
                )
                {
                    return std::make_shared<MemberController>(objectMapper);
                }

                ENDPOINT("GET", "/api/members/birthday/upcoming", getMembersWithUpcomingBirthday,
                    QUERY(oatpp::UInt32, limit))
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request for upcoming birthdays with limit: %d", limit.operator v_uint32());
                    auto dbResult = m_database->getMembersWithUpcomingBirthday(limit);
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

                    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<MemberDto>>>();

                    auto page = PageDto<oatpp::Object<MemberDto>>::createShared();
                    page->limit = limit;
                    page->count = items->size();
                    page->items = items;

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Processed request. Returned %d items", page->count.operator v_uint32());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    return createDtoResponse(Status::CODE_200, page);
                }

                ENDPOINT("GET", "/api/members/training/most-often", getMembersWithMostTrainings,
                    QUERY(oatpp::UInt32, limit), QUERY(oatpp::UInt32, offset))
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request for members with most trainings. Limit: %d, Offset: %d", limit.operator v_uint32(), offset.operator v_uint32());

                    auto dbResult = m_database->getMembersWithMostTrainings(limit, offset);
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

                    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<primus::dto::database::MemberDto>>>();

                    auto page = PageDto<oatpp::Object<primus::dto::database::MemberDto>>::createShared();
                    page->offset = offset;
                    page->limit = limit;
                    page->count = items->size();
                    page->items = items;

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Processed request. Returned %d items", page->count.operator v_uint32());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);

                    return createDtoResponse(Status::CODE_200, page);
                }

                ENDPOINT("GET", "/api/member/{id}/department", getDepartmentsOfMember,
                    PATH(oatpp::UInt32, id))
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get departments of member with id: %d", id.operator v_uint32());

                    auto dbResult = m_database->getDepartmentsOfMember(id);
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

                    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<DepartmentDto>>>();

                    auto page = PageDto<oatpp::Object<DepartmentDto>>::createShared();
                    page->count = items->size();
                    page->items = items;

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Processed request to get departments of member with id: %d. Returned %d items", id.operator v_uint32(), page->count.operator v_uint32());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);

                    return createDtoResponse(Status::CODE_200, page);
                }

                ENDPOINT("GET", "/api/members/all", getAllMembers,
                    QUERY(oatpp::UInt32, limit), QUERY(oatpp::UInt32, offset))
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get all members. Limit: %d, Offset: %d", limit.operator v_uint32(), offset.operator v_uint32());
                    auto dbResult = m_database->getAllMembers(offset, limit);
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

                    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<primus::dto::database::MemberDto>>>();

                    auto page = PageDto<oatpp::Object<primus::dto::database::MemberDto>>::createShared();
                    page->offset = offset;
                    page->limit = limit;
                    page->count = items->size();
                    page->items = items;

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Processed request to get all members. Returned %d items", page->count.operator v_uint32());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    return createDtoResponse(Status::CODE_200, page);
                }

                ENDPOINT("GET", "/api/members/active", getActiveMembers,
                    QUERY(oatpp::UInt32, limit), QUERY(oatpp::UInt32, offset))
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get active members. Limit: %d, Offset: %d", limit.operator v_uint32(), offset.operator v_uint32());

                    auto dbResult = m_database->getActiveMembers(limit, offset);

                    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<primus::dto::database::MemberDto>>>();

                    auto page = PageDto<oatpp::Object<primus::dto::database::MemberDto>>::createShared();

                    page->offset = offset;
                    page->limit = limit;
                    page->count = items->size();
                    page->items = items;

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Processed request to get active members. Returned %d items", page->count.operator v_uint32());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    return createDtoResponse(Status::CODE_200, page);
                }

                ENDPOINT("GET", "/api/members/inactive", getInactiveMembers,
                    QUERY(oatpp::UInt32, limit), QUERY(oatpp::UInt32, offset))
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get inactive members. Limit: %d, Offset: %d", limit.operator v_uint32(), offset.operator v_uint32());

                    auto dbResult = m_database->getInactiveMembers(limit, offset);

                    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<primus::dto::database::MemberDto>>>();

                    auto page = PageDto<oatpp::Object<primus::dto::database::MemberDto>>::createShared();

                    page->offset = offset;
                    page->limit = limit;
                    page->count = items->size();
                    page->items = items;

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Processed request to get inactive members. Returned %d items", page->count.operator v_uint32());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    return createDtoResponse(Status::CODE_200, page);
                }

                ENDPOINT("UPDATE", "/api/member/{id}/activate", activateMember,
                    PATH(oatpp::UInt32, id))
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to activate member with id: %d", id);

                    auto dbResult = m_database->activateMember(id);
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_404, "User was not found");

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Member with id: %d activated", id);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    return createResponse(Status::CODE_200, "Member activated");
                }

                ENDPOINT("UPDATE", "/api/member/{id}/deactivate", deactivateMember,
                    PATH(oatpp::UInt32, id))
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to deactivate member with id: %d", id);

                    auto dbResult = m_database->deactivateMember(id);
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_404, "User was not found");

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Member with id: %d deactivated", id);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    return createResponse(Status::CODE_200, "Member deactivated");
                }

                ENDPOINT("GET", "/api/member/{id}", getMemberById,
                    PATH(oatpp::UInt32, id))
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get member by id: %d", id.operator v_uint32());

                    auto dbResult = m_database->getMemberById(id);

                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
                    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Member not found");

                    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<primus::dto::database::MemberDto>>>();
                    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Processed request to get member by id: %d", id.operator v_uint32());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    return createDtoResponse(Status::CODE_200, result);
                }

                ENDPOINT("POST", "/api/member", createMember,
                    BODY_DTO(Object<primus::dto::database::MemberDto>, member))
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to create member");

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Member data:");
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - First Name: %s", member->firstName->c_str());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - Last Name: %s", member->lastName->c_str());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - Email: %s", member->email->c_str());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - Phone Number: %s", member->phoneNumber->c_str());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - Birth Date: %s", member->birthDate->c_str());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - Create Date: %s", member->createDate->c_str());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - Notes: %s", member->notes->c_str());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - Active: %s", member->active ? "true" : "false");

                    auto dbResult = m_database->createMember(member);
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, "Bad Request");

                    auto memberId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Created member with id: %d", memberId);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    return getMemberById(memberId);
                }

                ENDPOINT("PUT", "/api/member", updateMember,
                    BODY_DTO(Object<primus::dto::database::MemberDto>, member))
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to update member with id: %d", member->id.operator v_uint32());

                    {
                        auto dbResult = m_database->getMemberById(member->id);
                        OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
                        auto memberArray = dbResult->fetch<oatpp::Vector<oatpp::Object<primus::dto::database::MemberDto>>>();
                        auto currentMember = memberArray[0];

                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Old member data:");
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - ID: %d", currentMember->id.operator v_uint32());
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - First Name: %s", currentMember->firstName->c_str());
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - Last Name: %s", currentMember->lastName->c_str());
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - Email: %s", currentMember->email->c_str());
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - Phone Number: %s", currentMember->phoneNumber->c_str());
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - Birth Date: %s", currentMember->birthDate->c_str());
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - Create Date: %s", currentMember->createDate->c_str());
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - Notes: %s", currentMember->notes->c_str());
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - Active: %s", currentMember->active ? "true" : "false");

                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "New member data:");
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - ID: %d", member->id.operator v_uint32());
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - First Name: %s", member->firstName->c_str());
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - Last Name: %s", member->lastName->c_str());
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - Email: %s", member->email->c_str());
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - Phone Number: %s", member->phoneNumber->c_str());
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - Birth Date: %s", member->birthDate->c_str());
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - Create Date: %s", member->createDate->c_str());
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - Notes: %s", member->notes->c_str());
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "  - Active: %s", member->active ? "true" : "false");
                    }

                    auto dbResult = m_database->updateMember(member);
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Updated member with id: %d", member->id.operator v_uint32());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    return getMemberById(member->id);
                }

                ENDPOINT("GET", "/api/member/{id}/address", getMemberAddress,
                    PATH(UInt32, id))
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get address of member with id: %d", id.operator v_uint32());

                    auto dbResult = m_database->getMemberAddress(id);

                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_404, "User was not found");

                    auto adress = dbResult->fetch<oatpp::Object<AddressDto>>();

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Processed request to get address of member with id: %d", id.operator v_uint32());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    return createDtoResponse(Status::CODE_200, adress);
                }

                ENDPOINT("GET", "/api/member/{id}/membership-fee", getMembershipFee,
                    PATH(UInt32, id))
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get membership fee of member with id: %d", id.operator v_uint32());

                    auto dbResult = m_database->getMembershipFee(id);
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_404, "User was not found");

                    auto fee = dbResult->fetch<oatpp::Object<MembershipFeeDto>>();

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Processed request to get membership fee of member with id: %d", id.operator v_uint32());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    return createDtoResponse(Status::CODE_200, fee);
                }

                ENDPOINT("GET", "/api/member/{id}/trainings", getMemberTrainings,
                    PATH(oatpp::UInt32, id), QUERY(oatpp::UInt32, limit), QUERY(oatpp::UInt32, offset))
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get trainings of member with id: %d", id.operator v_uint32());

                    auto dbResult = m_database->getMemberTrainings(id, limit, offset);
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_404, "User was not found");

                    auto trainings = dbResult->fetch<oatpp::Vector<oatpp::Object<TrainingDto>>>();

                    auto page = PageDto<oatpp::Object<TrainingDto>>::createShared();
                    page->offset = offset;
                    page->limit = limit;
                    page->count = trainings->size();
                    page->items = trainings;

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Processed request to get trainings of member with id: %d. Returned %d trainings", id, page->count.operator v_uint32());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    return createDtoResponse(Status::CODE_200, page);
                }

                ENDPOINT("GET", "/api/member/{id}/purchase/weapons/allowed", isWeaponPurchaseAllowed,
                    PATH(UInt32, id))
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to check if weapon purchase is allowed for member with id: %d", id.operator v_uint32());

                    auto dbResult = m_database->isWeaponPurchaseAllowed(id);
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_404, "User was not found");

                    auto allowed = dbResult->fetch<oatpp::Object<BooleanDto>>();

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Processed request to check if weapon purchase is allowed for member with id: %d. Purchase allowed: %s", id.operator v_uint32(), allowed->value ? "true" : "false");
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    return createDtoResponse(Status::CODE_200, allowed);
                }

                ENDPOINT("GET", "/api/members/all/count", getMemberCountAll)
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get count of all members");

                    auto dbResult = m_database->getMemberCountAll();
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

                    auto count = dbResult->fetch<oatpp::Object<CountDto>>();

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Processed request to get count of all members. Total count: %d", count->count.operator v_uint32());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    return createDtoResponse(Status::CODE_200, count);
                }

                ENDPOINT("GET", "/api/members/active/count", getMemberCountActive)
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get count of active members");

                    auto dbResult = m_database->getMemberCountActive();
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

                    auto count = dbResult->fetch<oatpp::Object<CountDto>>();

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Processed request to get count of active members. Total active count: %d", count->count.operator v_uint32());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    return createDtoResponse(Status::CODE_200, count);
                }

                ENDPOINT("GET", "/api/members/inactive/count", getMemberCountInactive)
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get count of inactive members");

                    auto dbResult = m_database->getMemberCountInactive();
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

                    auto count = dbResult->fetch<oatpp::Object<CountDto>>();

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Processed request to get count of inactive members. Total inactive count: %d", count->count.operator v_uint32());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    return createDtoResponse(Status::CODE_200, count);
                }



                // Endpoint Infos

                ENDPOINT_INFO(getMembersWithUpcomingBirthday) {
                    info->name = "getMembersWithUpcomingBirthday";
                    info->summary = "Get members with upcoming birthdays";
                    info->description = "Retrieves a list of members whose birthdays are upcoming within a specified limit.";
                    info->path = "/api/members/birthday/upcoming";
                    info->method = "GET";
                    info->tags = { "Members" };
                    info->consumes = {};
                    info->pathParams = {};
                    info->queryParams["limit"].description = "Limit the number of results to fetch";
                    info->addResponse<oatpp::Object<PageDto<oatpp::Object<primus::dto::database::MemberDto>>>>(
                        Status::CODE_200, "application/json", "List of members with upcoming birthdays"
                    );
                    info->addResponse<String>(Status::CODE_500, "text/plain", "Internal server error");
                }

                ENDPOINT_INFO(getMembersWithMostTrainings) {
                    info->name = "getMembersWithMostTrainings";
                    info->summary = "Get members with most trainings";
                    info->description = "Retrieves a list of members who have participated in the most trainings.";
                    info->path = "/api/members/training/most-often";
                    info->method = "GET";
                    info->tags = { "Members" };
                    info->consumes = {};
                    info->pathParams = {};
                    info->queryParams["limit"].description = "Limit the number of results to fetch";
                    info->queryParams["offset"].description = "Offset the starting position of results";
                    info->addResponse<oatpp::Object<PageDto<oatpp::Object<primus::dto::database::MemberDto>>>>(
                        Status::CODE_200, "application/json", "List of members with most trainings"
                    );
                    info->addResponse<String>(Status::CODE_500, "text/plain", "Internal server error");
                }

                ENDPOINT_INFO(getDepartmentsOfMember) {
                    info->name = "getDepartmentsOfMember";
                    info->summary = "Get departments of a member";
                    info->description = "Retrieves a list of departments that a member belongs to.";
                    info->path = "/api/member/{id}/department";
                    info->method = "GET";
                    info->tags = { "Members" };
                    info->consumes = {};
                    info->pathParams["id"].description = "Identifier of the member";
                    info->addResponse<oatpp::Object<PageDto<oatpp::Object<DepartmentDto>>>>(
                        Status::CODE_200, "application/json", "List of departments of the member"
                    );
                    info->addResponse<String>(Status::CODE_500, "text/plain", "Internal server error");
                }

                ENDPOINT_INFO(getAllMembers) {
                    info->name = "getAllMembers";
                    info->summary = "Get all members";
                    info->description = "Retrieves a list of all members.";
                    info->path = "/api/members/all";
                    info->method = "GET";
                    info->tags = { "Members" };
                    info->consumes = {};
                    info->queryParams["limit"].description = "Limit the number of results to fetch";
                    info->queryParams["offset"].description = "Offset the starting position of results";
                    info->addResponse<oatpp::Object<PageDto<oatpp::Object<primus::dto::database::MemberDto>>>>(
                        Status::CODE_200, "application/json", "List of all members"
                    );
                    info->addResponse<String>(Status::CODE_500, "text/plain", "Internal server error");
                }

                ENDPOINT_INFO(getActiveMembers) {
                    info->name = "getActiveMembers";
                    info->summary = "Get active members";
                    info->description = "Retrieves a list of active members.";
                    info->path = "/api/members/active";
                    info->method = "GET";
                    info->tags = { "Members" };
                    info->consumes = {};
                    info->queryParams["limit"].description = "Limit the number of results to fetch";
                    info->queryParams["offset"].description = "Offset the starting position of results";
                    info->addResponse<oatpp::Object<PageDto<oatpp::Object<primus::dto::database::MemberDto>>>>(
                        Status::CODE_200, "application/json", "List of active members"
                    );
                    info->addResponse<String>(Status::CODE_500, "text/plain", "Internal server error");
                }

                ENDPOINT_INFO(getInactiveMembers) {
                    info->name = "getInactiveMembers";
                    info->summary = "Get inactive members";
                    info->description = "Retrieves a list of inactive members.";
                    info->path = "/api/members/inactive";
                    info->method = "GET";
                    info->tags = { "Members" };
                    info->consumes = {};
                    info->queryParams["limit"].description = "Limit the number of results to fetch";
                    info->queryParams["offset"].description = "Offset the starting position of results";
                    info->addResponse<oatpp::Object<PageDto<oatpp::Object<primus::dto::database::MemberDto>>>>(
                        Status::CODE_200, "application/json", "List of inactive members"
                    );
                    info->addResponse<String>(Status::CODE_500, "text/plain", "Internal server error");
                }

                ENDPOINT_INFO(activateMember) {
                    info->name = "activateMember";
                    info->summary = "Activate member";
                    info->description = "Activates a member.";
                    info->path = "/api/member/{id}/activate";
                    info->method = "UPDATE";
                    info->tags = { "Members" };
                    info->consumes = {};
                    info->pathParams["id"].description = "Identifier of the member";
                    info->addResponse<String>(Status::CODE_200, "text/plain", "Member activated");
                    info->addResponse<String>(Status::CODE_404, "text/plain", "User was not found");
                }

                ENDPOINT_INFO(deactivateMember) {
                    info->name = "deactivateMember";
                    info->summary = "Deactivate member";
                    info->description = "Deactivates a member.";
                    info->path = "/api/member/{id}/deactivate";
                    info->method = "UPDATE";
                    info->tags = { "Members" };
                    info->consumes = {};
                    info->pathParams["id"].description = "Identifier of the member";
                    info->addResponse<String>(Status::CODE_200, "text/plain", "Member deactivated");
                    info->addResponse<String>(Status::CODE_404, "text/plain", "User was not found");
                }

                ENDPOINT_INFO(getMemberById) {
                    info->name = "getMemberById";
                    info->summary = "Get member by ID";
                    info->description = "Retrieves a member by its ID.";
                    info->path = "/api/member/{id}";
                    info->method = "GET";
                    info->tags = { "Members" };
                    info->consumes = {};
                    info->pathParams["id"].description = "Identifier of the member";
                    info->addResponse<oatpp::Object<primus::dto::database::MemberDto>>(
                        Status::CODE_200, "application/json", "Member details"
                    );
                    info->addResponse<String>(Status::CODE_404, "text/plain", "User was not found");
                }

                ENDPOINT_INFO(createMember) {
                    info->name = "createMember";
                    info->summary = "Create a new member";
                    info->description = "Creates a new member.";
                    info->path = "/api/member";
                    info->method = "POST";
                    info->tags = { "Members" };
                    info->addConsumes<oatpp::Object<primus::dto::database::MemberDto>>("application/json", "Input data as JSON");
                    info->pathParams = {};
                    info->queryParams = {};
                    info->addResponse<oatpp::Object<primus::dto::database::MemberDto>>(
                        Status::CODE_200, "application/json", "Created member details"
                    );
                    info->addResponse<String>(Status::CODE_500, "text/plain", "Bad Request");
                }

                ENDPOINT_INFO(updateMember) {
                    info->name = "updateMember";
                    info->summary = "Update an existing member";
                    info->description = "Updates an existing member with new information.";
                    info->path = "/api/member";
                    info->method = "PUT";
                    info->tags = { "Members" };
                    info->addConsumes<oatpp::Object<primus::dto::database::MemberDto>>("application/json", "Input data as JSON");
                    info->pathParams = {};
                    info->queryParams = {};
                    info->addResponse<oatpp::Object<primus::dto::database::MemberDto>>(
                        Status::CODE_200, "application/json", "Updated member details"
                    );
                    info->addResponse<String>(Status::CODE_404, "text/plain", "User was not found");
                }


                ENDPOINT_INFO(getMemberAddress) {
                    info->name = "getMemberAddress";
                    info->summary = "Get the address of a member";
                    info->description = "Retrieves the address of a member by their ID.";
                    info->path = "/api/member/{id}/address";
                    info->method = "GET";
                    info->tags = { "Members" };
                    info->addConsumes<oatpp::UInt32>("text/plain", "Member ID as plain text");
                    info->pathParams["id"].description = "Member Identifier";
                    info->queryParams = {};
                    info->addResponse<oatpp::Object<AddressDto>>(
                        Status::CODE_200, "application/json", "Member's address details"
                    );
                    info->addResponse<String>(Status::CODE_404, "text/plain", "User was not found");
                }

                ENDPOINT_INFO(getMembershipFee) {
                    info->name = "getMembershipFee";
                    info->summary = "Get the membership fee of a member";
                    info->description = "Retrieves the membership fee of a member by their ID.";
                    info->path = "/api/member/{id}/membership-fee";
                    info->method = "GET";
                    info->tags = { "Members" };
                    info->addConsumes<oatpp::UInt32>("text/plain", "Member ID as plain text");
                    info->pathParams["id"].description = "Member Identifier";
                    info->queryParams = {};
                    info->addResponse<oatpp::Object<MembershipFeeDto>>(
                        Status::CODE_200, "application/json", "Membership fee details"
                    );
                    info->addResponse<String>(Status::CODE_404, "text/plain", "User was not found");
                }

                ENDPOINT_INFO(getMemberTrainings) {
                    info->name = "getMemberTrainings";
                    info->summary = "Get trainings of a member";
                    info->description = "Retrieves the trainings of a member by their ID.";
                    info->path = "/api/member/{id}/trainings";
                    info->method = "GET";
                    info->tags = { "Members" };
                    info->addConsumes<oatpp::UInt32>("text/plain", "Member ID as plain text");
                    info->pathParams["id"].description = "Member Identifier";
                    info->queryParams["limit"].description = "Limit the number of trainings returned";
                    info->queryParams["offset"].description = "Offset the starting point of trainings returned";
                    info->addResponse<oatpp::Object<PageDto<oatpp::Object<TrainingDto>>>>(
                        Status::CODE_200, "application/json", "Page containing member trainings"
                    );
                    info->addResponse<String>(Status::CODE_404, "text/plain", "User was not found");
                }

                ENDPOINT_INFO(isWeaponPurchaseAllowed) {
                    info->name = "isWeaponPurchaseAllowed";
                    info->summary = "Check if weapon purchase is allowed for a member";
                    info->description = "Checks whether a member is allowed to purchase weapons based on their ID.";
                    info->path = "/api/member/{id}/purchase/weapons/allowed";
                    info->method = "GET";
                    info->tags = { "Members" };
                    info->addConsumes<oatpp::UInt32>("text/plain", "Member ID as plain text");
                    info->pathParams["id"].description = "Member Identifier";
                    info->addResponse<oatpp::Object<BooleanDto>>(
                        Status::CODE_200, "application/json", "Indicates whether weapon purchase is allowed"
                    );
                    info->addResponse<String>(Status::CODE_404, "text/plain", "User was not found");
                }

                ENDPOINT_INFO(getMemberCountAll) {
                    info->name = "getMemberCountAll";
                    info->summary = "Get the total count of all members";
                    info->description = "Retrieves the total count of all members.";
                    info->path = "/api/members/all/count";
                    info->method = "GET";
                    info->tags = { "Members" };
                    info->addResponse<oatpp::Object<CountDto>>(
                        Status::CODE_200, "application/json", "Total count of all members"
                    );
                    info->addResponse<String>(Status::CODE_500, "text/plain", "Internal Server Error");
                }

                ENDPOINT_INFO(getMemberCountActive) {
                    info->name = "getMemberCountActive";
                    info->summary = "Get the total count of active members";
                    info->description = "Retrieves the total count of active members.";
                    info->path = "/api/members/active/count";
                    info->method = "GET";
                    info->tags = { "Members" };
                    info->addResponse<oatpp::Object<CountDto>>(
                        Status::CODE_200, "application/json", "Total count of active members"
                    );
                    info->addResponse<String>(Status::CODE_500, "text/plain", "Internal Server Error");
                }

                ENDPOINT_INFO(getMemberCountInactive) {
                    info->name = "getMemberCountInactive";
                    info->summary = "Get the total count of inactive members";
                    info->description = "Retrieves the total count of inactive members.";
                    info->path = "/api/members/inactive/count";
                    info->method = "GET";
                    info->tags = { "Members" };
                    info->addResponse<oatpp::Object<CountDto>>(
                        Status::CODE_200, "application/json", "Total count of inactive members"
                    );
                    info->addResponse<String>(Status::CODE_500, "text/plain", "Internal Server Error");
                }
            };

#include OATPP_CODEGEN_END(ApiController) // End API Controller codegen

        } // namespace member_endpoint
    } // apicontroller
} // namespace namespace primus

#endif // MEMBERCONTROLLER_HPP
