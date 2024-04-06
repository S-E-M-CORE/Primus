#ifndef MEMBERCONTROLLER_HPP
#define MEMBERCONTROLLER_HPP

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "dto/StatusDto.hpp"
#include "dto/PageDto.hpp"
#include "dto/Int32Dto.hpp"
#include "dto/MembershipFeeDto.hpp"
#include "dto/BooleanDto.hpp"
#include "general/constants.hpp"

namespace primus {
    namespace apicontroller {
        namespace member_endpoint {

#include OATPP_CODEGEN_BEGIN(ApiController) // Begin API Controller codegen


            using primus::dto::PageDto;

            class MemberController : public oatpp::web::server::api::ApiController
            {
                typedef primus::dto::database::MemberDto MemberDto;
                typedef primus::dto::database::DepartmentDto DepartmentDto;
                typedef primus::dto::database::AddressDto AddressDto;
                typedef primus::dto::MemberPageDto MemberPageDto;
                typedef primus::dto::UInt32Dto UInt32Dto;
                typedef primus::dto::MembershipFeeDto MembershipFeeDto;
                typedef primus::dto::BooleanDto BooleanDto;
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

                ENDPOINT("GET", "/api/members/list/{attribute}", getMembersList,
                    PATH(oatpp::String, attribute), QUERY(oatpp::UInt32, limit), QUERY(oatpp::UInt32, offset))
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    std::shared_ptr<oatpp::orm::QueryResult> dbResult;
                    if (attribute == oatpp::String("all"))
                    {
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get a list of all members. Limit: %d, Offset: %d", limit.operator v_uint32(), offset.operator v_uint32());

                        dbResult = m_database->getAllMembers(limit, offset);
                    }
                    else if (attribute == oatpp::String("active"))
                    {
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get a list of all active members. Limit: %d, Offset: %d", limit.operator v_uint32(), offset.operator v_uint32());

                        dbResult = m_database->getActiveMembers(limit, offset);
                    }
                    else if (attribute == oatpp::String("inactive"))
                    {
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get a list of all inactive members. Limit: %d, Offset: %d", limit.operator v_uint32(), offset.operator v_uint32());

                        dbResult = m_database->getInactiveMembers(limit, offset);
                    }
                    else if (attribute == oatpp::String("birthday"))
                    {
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get a list of all members with upcomming birthdays. Limit: %d, Offset: %d", limit.operator v_uint32(), offset.operator v_uint32());

                        dbResult = m_database->getMembersWithUpcomingBirthday(limit, offset);
                    }
                    else
                    {
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get a list of members with %s, which is not an available attribute", attribute->c_str());
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Returning CODE 500: Bad Request. Available options: all, active or inactive");
                        return createResponse(Status::CODE_500, "BAD REQUEST");
                    }
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

                    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<MemberDto>>>();

                    auto page = PageDto<oatpp::Object<MemberDto>>::createShared();

                    page->offset = offset;
                    page->limit = limit;
                    page->count = items->size();
                    page->items = items;

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Processed request to get a list of members with %s. Limit: %d, Offset: %d. Returned %d items", attribute->c_str(), limit.operator v_uint32(), offset.operator v_uint32(), page->count.operator v_uint32());
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

                    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<MemberDto>>>();
                    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Processed request to get member by id: %d", id.operator v_uint32());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    return createDtoResponse(Status::CODE_200, result);
                }

                ENDPOINT("POST", "/api/member", createMember,
                    BODY_DTO(Object<MemberDto>, member))
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

                    std::shared_ptr<oatpp::orm::QueryResult> dbResult = m_database->createMember(member);
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, "Bad Request");

                    oatpp::UInt32 memberId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

                    oatpp::Vector<oatpp::Object<MemberDto>> foundMembers;
                    oatpp::Object<MemberDto> retMember;

                    if (memberId == 0)
                    {
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Member already exists. proceeding to return existing user");
                        
                        dbResult = m_database->findMemberIdByDetails(member->firstName, member->lastName, member->email, member->birthDate);
                        OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, "Unknown error");

                        foundMembers = dbResult->fetch<oatpp::Vector<oatpp::Object<MemberDto>>>();

                         retMember = foundMembers[0];
                    }
                    else
                    {
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Created member with id: %d", memberId.operator v_uint32());

                        dbResult = m_database->getMemberById(memberId);
                        OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, "Unknown error");

                        foundMembers = dbResult->fetch<oatpp::Vector<oatpp::Object<MemberDto>>>();

                        retMember = foundMembers[0];
                    }
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    return createDtoResponse(memberId == 0 ? Status::CODE_200 : Status::CODE_201, retMember);
                }

                ENDPOINT("PUT", "/api/member", updateMember,
                    BODY_DTO(Object<MemberDto>, member))
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to update member with id: %d", member->id.operator v_uint32());

                    {
                        auto dbResult = m_database->getMemberById(member->id);
                        OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
                        auto memberArray = dbResult->fetch<oatpp::Vector<oatpp::Object<MemberDto>>>();
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

                ENDPOINT("GET", "/api/member/count/{attribute}", getMemberCount, PATH(oatpp::String, attribute))
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);

                    std::shared_ptr<oatpp::orm::QueryResult> dbResult;

                    if (attribute == oatpp::String("all"))
                    {
                        dbResult = m_database->getMemberCountAll();
                    }
                    else if (attribute == oatpp::String("active"))
                    {
                        dbResult = m_database->getMemberCountActive();
                    }
                    else if (attribute == oatpp::String("inactive"))
                    {
                        dbResult = m_database->getMemberCountInactive();
                    }
                    else 
                    {
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received count request for members with attribute %s, which is not an available attribute", attribute->c_str());
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Returning CODE 500: Bad Request. Available options:");
                        return createResponse(Status::CODE_500, "BAD REQUEST. Use all, active or inactive");
                    }

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get count of %s members", attribute->c_str());
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

                    auto count = dbResult->fetch<oatpp::Vector<oatpp::Object<UInt32Dto>>>();

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Processed request to get count of %s members. Total count: %d", attribute->c_str(), count[0]->value.operator v_uint32());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    return createDtoResponse(Status::CODE_200, count[0]);
                }

                ENDPOINT("POST", "/api/member/{memberId}/department/add/{departmentId}", createMemberDepartmentAssociation, PATH(oatpp::UInt32, memberId), PATH(oatpp::UInt32, departmentId))
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to add member with id %d to department with id %d", memberId.operator v_uint32(), departmentId.operator v_uint32());

                    std::shared_ptr<OutgoingResponse>           ret;
                    oatpp::Vector<oatpp::Object<DepartmentDto>> departments;
                    oatpp::Vector<oatpp::Object<MemberDto>>     member;
                    std::shared_ptr<oatpp::orm::QueryResult>    dbResult;


                    dbResult = m_database->getDepartmentById(departmentId);
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
                    departments = dbResult->fetch<oatpp::Vector<oatpp::Object<DepartmentDto>>>();
                    OATPP_ASSERT_HTTP(departments->size() != 0, Status::CODE_404, "Department not found");
                    OATPP_ASSERT_HTTP(!(departments->size() > 1), Status::CODE_404, "Critical database error: More than 1 department with id %d", departmentId.operator v_uint32());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Department found: %d | %s", departments[0]->id.operator v_uint32(), departments[0]->name->c_str());

                    dbResult = m_database->getMemberById(memberId);
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
                    member = dbResult->fetch<oatpp::Vector<oatpp::Object<MemberDto>>>();
                    OATPP_ASSERT_HTTP(member->size() != 0, Status::CODE_404, "Member not found");
                    OATPP_ASSERT_HTTP(!(member->size() > 1), Status::CODE_404, "Critical database error: More than 1 member with id %d", memberId.operator v_uint32());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Member found: %d | %s | %s", member[0]->id.operator v_uint32(), member[0]->firstName->c_str(), member[0]->lastName->c_str());

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Creating member-department association");
                    dbResult = m_database->associateDepartmentWithMember(departmentId, memberId);
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "member-department association successfully created");

                    return createResponse(Status::CODE_200, "member-department association successfully created");
                }

                ENDPOINT("DELETE", "/api/member/{memberId}/department/remove/{departmentId}", deleteMemberDepartmentDisassociation, PATH(oatpp::UInt32, memberId), PATH(oatpp::UInt32, departmentId))
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to remove member with id %d from department with id %d", memberId.operator v_uint32(), departmentId.operator v_uint32());

                    std::shared_ptr<OutgoingResponse>           ret;
                    oatpp::Vector<oatpp::Object<DepartmentDto>> departments;
                    oatpp::Vector<oatpp::Object<MemberDto>>     member;
                    std::shared_ptr<oatpp::orm::QueryResult>    dbResult;


                    dbResult = m_database->getDepartmentById(departmentId);
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
                    departments = dbResult->fetch<oatpp::Vector<oatpp::Object<DepartmentDto>>>();
                    OATPP_ASSERT_HTTP(departments->size() != 0, Status::CODE_404, "Department not found");
                    OATPP_ASSERT_HTTP(!(departments->size() > 1), Status::CODE_404, "Critical database error: More than 1 department with id %d", departmentId.operator v_uint32());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Department found: %d | %s", departments[0]->id.operator v_uint32(), departments[0]->name->c_str());

                    dbResult = m_database->getMemberById(memberId);
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
                    member = dbResult->fetch<oatpp::Vector<oatpp::Object<MemberDto>>>();
                    OATPP_ASSERT_HTTP(member->size() != 0, Status::CODE_404, "Member not found");
                    OATPP_ASSERT_HTTP(!(member->size() > 1), Status::CODE_404, "Critical database error: More than 1 member with id %d", memberId.operator v_uint32());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Member found: %d | %s | %s", member[0]->id.operator v_uint32(), member[0]->firstName->c_str(), member[0]->lastName->c_str());

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Disassociating member and department");
                    dbResult = m_database->disassociateDepartmentFromMember(departmentId, memberId);
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "member and department successfully disassociated");

                    return createResponse(Status::CODE_200, "member and department successfully disassociated");
                }

                ENDPOINT("POST", "/api/member/{memberId}/address/add", createMemberAddressAssociation, PATH(oatpp::UInt32, memberId), BODY_DTO(oatpp::Object<AddressDto>, address))
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to set address for member with id %d", memberId.operator v_uint32());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Address data:");
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "- Street: %s"         , address->street->c_str());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "- City: %s"           , address->city->c_str());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "- Postal code: %s"    , address->postalCode->c_str());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "- Country: %s"        , address->country->c_str());

                    std::shared_ptr<oatpp::orm::QueryResult> dbResult = m_database->createAddress(address);

                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

                    oatpp::UInt32 addressId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

                    oatpp::Vector<oatpp::Object<AddressDto>> foundAddresses;
                    oatpp::Object<AddressDto> retAddress;

                    if (addressId == 0)
                    {
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Address already exists. Proceeding to return existing id");

                        dbResult = m_database->findAddressByDetails(address->street, address->city, address->postalCode, address->country);
                    }
                    else
                    {
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Address created with id %d", addressId.operator v_uint32());

                        dbResult = m_database->getAddressById(addressId);
                    }
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, "Unknown Error");

                    foundAddresses = dbResult->fetch<oatpp::Vector<oatpp::Object<AddressDto>>>();
                    retAddress = foundAddresses[0];

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Creating member-address association");
                    dbResult = m_database->associateAddressWithMember(retAddress->id, memberId);
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, "Unknown Error");
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "member-address association was successfully created");

                    return createDtoResponse(addressId == 0 ? Status::CODE_200 : Status::CODE_201, retAddress);
                }

                ENDPOINT("DELETE", "/api/member/{memberId}/address/remove/{addressId}", deleteMemberAddressDisassociation, PATH(oatpp::UInt32, memberId), PATH(oatpp::UInt32, addressId))
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to remove member with id %d from address with id %d", memberId.operator v_uint32(), addressId.operator v_uint32());

                    std::shared_ptr<OutgoingResponse>           ret;
                    oatpp::Vector<oatpp::Object<AddressDto>>    addresses;
                    oatpp::Vector<oatpp::Object<MemberDto>>     member;
                    std::shared_ptr<oatpp::orm::QueryResult>    dbResult;


                    dbResult = m_database->getAddressById(addressId);
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
                    addresses = dbResult->fetch<oatpp::Vector<oatpp::Object<AddressDto>>>();
                    OATPP_ASSERT_HTTP(addresses->size() != 0, Status::CODE_404, "address not found");
                    OATPP_ASSERT_HTTP(!(addresses->size() > 1), Status::CODE_404, "Critical database error: More than 1 address with id %d", departmentId.operator v_uint32());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Address found");

                    dbResult = m_database->getMemberById(memberId);
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
                    member = dbResult->fetch<oatpp::Vector<oatpp::Object<MemberDto>>>();
                    OATPP_ASSERT_HTTP(member->size() != 0, Status::CODE_404, "Member not found");
                    OATPP_ASSERT_HTTP(!(member->size() > 1), Status::CODE_404, "Critical database error: More than 1 member with id %d", memberId.operator v_uint32());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Member found: %d | %s | %s", member[0]->id.operator v_uint32(), member[0]->firstName->c_str(), member[0]->lastName->c_str());

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Disassociating member and address");
                    dbResult = m_database->disassociateAddressFromMember(addressId, memberId);
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "member and department successfully disassociated");

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Checking for other members using the address...");
                    dbResult = m_database->getMembersByAddress(addressId);
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

                    member = dbResult->fetch<oatpp::Vector<oatpp::Object<MemberDto>>>();


                    if (member->size() == 0)
                    {
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "No other member using the address.");
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Proceeding with deletion of address");

                        dbResult = m_database->deleteAddress(addressId);
                        OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Address has been deleted");
                    }
                    else
                    {
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Other members are associated with address");
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "keeping address in database");
                    }
                    return createResponse(Status::CODE_200, "member and department successfully disassociated");
                }

                ENDPOINT("GET", "/api/member/{memberId}/list/{attribute}", getMemberList,
                    PATH(oatpp::UInt32, memberId), PATH(oatpp::String, attribute), QUERY(oatpp::UInt32, limit), QUERY(oatpp::UInt32, offset))
                {
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);

                    std::shared_ptr<oatpp::orm::QueryResult> dbResult;

                    std::shared_ptr<OutgoingResponse> ret;

                    if (attribute == oatpp::String("addresses"))
                    {
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get a list addresses associated with member id %d. Limit: %d, Offset: %d", memberId.operator v_uint32(), limit.operator v_uint32(),offset.operator v_uint32());

                        dbResult = m_database->getMemberAddresses(memberId, limit, offset);
                        OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

                        auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<AddressDto>>>();

                        auto page = PageDto<oatpp::Object<AddressDto>>::createShared();

                        page->offset = offset;
                        page->limit = limit;
                        page->count = items->size();
                        page->items = items;

                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Processed request to get a list of members with %s. Limit: %d, Offset: %d. Returned %d items", attribute->c_str(), limit.operator v_uint32(), offset.operator v_uint32(), page->count.operator v_uint32());

                        ret = createDtoResponse(Status::CODE_200, page);
                    }
                    else if (attribute == oatpp::String("departments"))
                    {
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get a list departments associated with member id %d. Limit: %d, Offset: %d", memberId.operator v_uint32(), limit.operator v_uint32(), offset.operator v_uint32());

                        dbResult = m_database->getMemberDepartments(memberId, limit, offset);
                        OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

                        auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<DepartmentDto>>>();


                        auto page = PageDto<oatpp::Object<DepartmentDto>>::createShared();

                        page->offset = offset;
                        page->limit = limit;
                        page->count = items->size();
                        page->items = items;

                        ret = createDtoResponse(Status::CODE_200, page);
                    }
                    else if (attribute == oatpp::String("trainings"))
                    {
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get a list trainings associated with member id %d. Limit: %d, Offset: %d", memberId.operator v_uint32(), limit.operator v_uint32(), offset.operator v_uint32());
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "ERROR: this feature is not implemented yet");

                        ret = createResponse(Status::CODE_500, "INTERNAL SERVER ERROR");
                    }
                    else
                    {
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get a list of members with %s, which is not an available attribute", attribute->c_str());
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Returning CODE 500: Bad Request. Available options: addresses");

                        ret = createResponse(Status::CODE_500, "BAD REQUEST");
                    }

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);

                    return ret;
                }


                // Endpoint Infos

                
            };

#include OATPP_CODEGEN_END(ApiController) // End API Controller codegen

        } // namespace member_endpoint
    } // apicontroller
} // namespace namespace primus

#endif // MEMBERCONTROLLER_HPP
