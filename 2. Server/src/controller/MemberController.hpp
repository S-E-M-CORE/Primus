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


            using primus::dto::PageDto;

            class MemberController : public oatpp::web::server::api::ApiController
            {
                typedef primus::dto::database::MemberDto MemberDto;
                typedef primus::dto::database::DepartmentDto DepartmentDto;
                typedef primus::dto::database::TrainingDto TrainingDto;
                typedef primus::dto::database::AddressDto AddressDto;
                typedef primus::dto::MemberPageDto MemberPageDto;
                typedef primus::dto::CountDto CountDto;
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

                ENDPOINT("GET", "/api/member/list/{attribute}", getMemberList,
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
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get a list of all members with active=1. Limit: %d, Offset: %d", limit.operator v_uint32(), offset.operator v_uint32());

                        dbResult = m_database->getActiveMembers(limit, offset);
                    }
                    else if (attribute == oatpp::String("inactive"))
                    {
                        OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get a list of all members with active=0. Limit: %d, Offset: %d", limit.operator v_uint32(), offset.operator v_uint32());

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

                    auto dbResult = m_database->createMember(member);
                    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, "Bad Request");

                    auto memberId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Created member with id: %d", memberId);
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    return getMemberById(memberId);
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

                    auto count = dbResult->fetch<oatpp::Vector<oatpp::Object<CountDto>>>();

                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Processed request to get count of %s members. Total count: %d", attribute->c_str(), count[0]->count.operator v_uint32());
                    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, primus::constants::apicontroller::member_endpoint::logSeperation);
                    return createDtoResponse(Status::CODE_200, count[0]);
                }



                // Endpoint Infos

                ENDPOINT_INFO(getMemberList) {
                    info->name = "getMemberList";
                    info->summary = "Get member list";
                    info->description = "Retrieves a list of members based on the specified attribute.";
                    info->path = "/api/members/list/{attribute}";
                    info->method = "GET";
                    info->tags = { "Members" };
                    info->consumes = {};
                    info->pathParams["attribute"].description = "Attribute to filter the member list ('all', 'active', or 'inactive')";
                    info->queryParams["limit"].description = "Limit the number of results to fetch";
                    info->queryParams["offset"].description = "Offset the starting position of results";
                    info->addResponse<oatpp::Object<PageDto<oatpp::Object<MemberDto>>>>(
                        Status::CODE_200, "application/json", "List of members"
                    );
                    info->addResponse<String>(Status::CODE_500, "text/plain", "Internal server error");
                }

                ENDPOINT_INFO(getMemberCount) {
                    info->name = "getMemberCount";
                    info->summary = "Get member count";
                    info->description = "Retrieves the count of members based on the specified attribute.";
                    info->path = "/api/members/count/{attribute}";
                    info->method = "GET";
                    info->tags = { "Members" };
                    info->consumes = {};
                    info->pathParams["attribute"].description = "Attribute to filter the member count ('all', 'active', or 'inactive')";
                    info->addResponse<oatpp::Object<CountDto>>(
                        Status::CODE_200, "application/json", "Count of members"
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
                    info->addResponse<oatpp::Object<MemberDto>>(
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
                    info->addConsumes<oatpp::Object<MemberDto>>("application/json", "Input data as JSON");
                    info->pathParams = {};
                    info->queryParams = {};
                    info->addResponse<oatpp::Object<MemberDto>>(
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
                    info->addConsumes<oatpp::Object<MemberDto>>("application/json", "Input data as JSON");
                    info->pathParams = {};
                    info->queryParams = {};
                    info->addResponse<oatpp::Object<MemberDto>>(
                        Status::CODE_200, "application/json", "Updated member details"
                    );
                    info->addResponse<String>(Status::CODE_404, "text/plain", "User was not found");
                }
            };

#include OATPP_CODEGEN_END(ApiController) // End API Controller codegen

        } // namespace member_endpoint
    } // apicontroller
} // namespace namespace primus

#endif // MEMBERCONTROLLER_HPP
