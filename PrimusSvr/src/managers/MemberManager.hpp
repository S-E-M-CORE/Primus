#ifndef MEMBER_MANAGER_HPP
#define MEMBER_MANAGER_HPP

#include <map>
#include <string>
#include <memory>

#include "oatpp/core/Types.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/component.hpp"
#include "database/DatabaseClient.hpp"

#include "general/constants.hpp"
#include "dto/DatabaseDtos.hpp"
#include "dto/Int32Dto.hpp"
#include "dto/PageDto.hpp"
#include "general/exceptions.hpp"

namespace primus {
    namespace managers {
        namespace Members {

            enum class MembersLists
            {
                all,
                active,
                inactive,
                birthday,
                attendance,
                null
            };

            static MembersLists stringToMembersList(const std::string& str)
            {
                static const std::map<std::string, MembersLists> enumMap =
                {
                    {"all"       , MembersLists::all},
                    {"active"    , MembersLists::active},
                    {"inactive"  , MembersLists::inactive},
                    {"birthday"  , MembersLists::birthday},
                    {"attendance", MembersLists::attendance},
                    {"null"      , MembersLists::null}
                };

                auto it = enumMap.find(str);
                if (it != enumMap.end()) {
                    return it->second;
                }
                return MembersLists::null; // Default value for unknown strings
            }

            /**
             * @brief Manages members and provides functionality related to the member endpoints
             */
            class MemberManager
            {
                using UInt32 = oatpp::UInt32;
                using String = oatpp::String;

                using MemberDto = primus::dto::database::MemberDto;
                using AddressDto = primus::dto::database::AddressDto;
                using MemberPageDto = primus::dto::MemberPageDto;
                using UInt32Dto = primus::dto::UInt32Dto;
                using Int32Dto = primus::dto::Int32Dto;

                using ObjMemberDto  = oatpp::Object<MemberDto>;
                using ObjAddressDto = oatpp::Object <AddressDto>;
                using ObjMemberPageDto = oatpp::Object<MemberPageDto>;

                static constexpr const char* logName = primus::constants::managers::manager_member::logName;

            private:
                OATPP_COMPONENT(std::shared_ptr<primus::component::DatabaseClient>, m_database);


            private:
                /**
                 * @brief Default constructor for the MemberManager class.
                 */
                MemberManager(void) = default;

            public:
                /**
                 * @brief Destructor for the MemberManager class.
                 */
                virtual ~MemberManager(void) = default;

                /**
                 * @brief Creates a shared pointer to the MemberManager instance.
                 * @return Shared pointer to the MemberManager instance.
                 */
                static std::shared_ptr<MemberManager> createShared(void);

                /**
                 * @brief Retrieves a list of members based on a specified attribute.
                 * @param attribute The attribute to filter the list by.
                 * @param limit The maximum number of members to retrieve.
                 * @param offset The offset for pagination.
                 */
                void getList(ObjMemberPageDto& page, const String& attribute, const UInt32& limit, const UInt32& offset);
            private:
                void getListAll(ObjMemberPageDto& page, const UInt32& limit, const UInt32& offset);
                void getListActive(ObjMemberPageDto& page, const UInt32& limit, const UInt32& offset);
                void getListInactive(ObjMemberPageDto& page, const UInt32& limit, const UInt32& offset);
                void getListBirthdayNext(ObjMemberPageDto& page, const UInt32& limit, const UInt32& offset);
                void getListAttendanceMost(ObjMemberPageDto& page, const UInt32& limit, const UInt32& offset);

            public:


                /**
                 * @brief Activates a member with the specified ID.
                 * @param memberId The ID of the member to activate.
                 */
                void activateMember(const UInt32& memberId);

                /**
                 * @brief Deactivates a member with the specified ID.
                 * @param memberId The ID of the member to deactivate.
                 */
                void deactivateMember(const UInt32& memberId);

                /**
                 * @brief Retrieves a member by their ID.
                 * @param dto Reference to the MemberDto object to store the retrieved member.
                 * @param memberId The ID of the member to retrieve.
                 */
                void getMemberById(ObjMemberDto& dto, const UInt32& memberId);

                /**
                 * @brief Creates a new member.
                 * @param member The MemberDto object representing the new member.
                 * @return The id of the new member
                 */
                UInt32 createMember(const ObjMemberDto& member);

                /**
                 * @brief Updates an existing member.
                 * @param member The MemberDto object representing the member to update.
                 */
                void updateMember(const ObjMemberDto& member);

                /**
                 * @brief Counts the total number of members based on specified attribute.
                 * @param attribute The attribute to count members by.
                 * @return The count of members
                 */
                UInt32 countMembers(const String& attribute);

                /**
                 * @brief Counts the specified attribute of a specific member.
                 * @param memberId The ID of the member to count the attribute for.
                 * @param attribute The attribute to count.
                 * @return The count of the specified attribute for the given member
                 */
                UInt32 countAttribute(const UInt32& memberId, String& attribute);

                /**
                 * @brief Adds a member to a department.
                 * @param memberId The ID of the member to add to the department.
                 * @param departmentId The ID of the department to add the member to.
                 */
                void addMemberToDepartment(const UInt32& memberId, const UInt32& departmentId);

                /**
                 * @brief Removes a member from a department.
                 * @param memberId The ID of the member to remove from the department.
                 * @param departmentId The ID of the department to remove the member from.
                 */
                void RemoveMemberFromDepartment(const UInt32& memberId, const UInt32& departmentId);

                /**
                 * @brief Adds an address to a member.
                 * @param memberId The ID of the member to add the address to.
                 * @param address The AddressDto object representing the address to add.
                 */
                void addAddressToMember(const UInt32& memberId, const ObjAddressDto& address);
                /**
                 * @overload
                 * @brief Adds an address to a member.
                 * @param memberId The ID of the member to add the address to.
                 * @param addressId The ID of the address to add.
                 */
                void addAddressToMember(const UInt32& memberId, const UInt32& addressId);

                /**
                 * @brief Removes an address from a member.
                 * @param memberId The ID of the member to remove the address from.
                 * @param addressId The ID of the address to remove.
                 */
                void removeAddressFromMember(const UInt32& memberId, const UInt32& addressId);
                /**
                 * @overload
                 * @brief Removes an address from a member.
                 * @param memberId The ID of the member to remove the address from.
                 * @param addressId The AddressDto object representing the address to remove.
                 */
                void removeAddressFromMember(const UInt32& memberId, const ObjAddressDto& addressId);

                /**
                 * @brief Adds attendance for a member on a specific date.
                 * @param memberId The ID of the member to add attendance for.
                 * @param date The date of attendance.
                 */
                void addMemberAttendance(const UInt32& memberId, const String& date);

                /**
                 * @brief Removes attendance for a member on a specific date.
                 * @param memberId The ID of the member to remove attendance for.
                 * @param date The date of attendance to remove.
                 */
                void removeMemberAttendance(const UInt32& memberId, const String& date);

                /**
                 * @brief Retrieves the fee of a member.
                 * @param memberId The ID of the member to retrieve the fee for.
                 * @return The fee of the member
                 */
                UInt32 getFeeOfMember(const UInt32& memberId);

                /**
                 * @brief Retrieves a list of members based on specified attribute.
                 * @param attribute The attribute to filter the list by.
                 * @param memberId The ID of the member to start the list from.
                 * @param limit The maximum number of members to retrieve.
                 * @param offset The offset for pagination.
                 */
                void getMemberList(const String& attribute, const UInt32& memberId, const UInt32& limit, const UInt32& offset);

                /**
                 * @brief Retrieves a list of addresses for a member based on the specified member ID, limit, and offset.
                 * @param memberId The ID of the member to retrieve addresses for.
                 * @param limit The maximum number of addresses to retrieve.
                 * @param offset The offset for pagination.
                 */
                void getMemberAddresses(const UInt32& memberId, const UInt32& limit, const UInt32& offset);

                /**
                 * @brief Retrieves a list of departments that a member belongs to based on the specified member ID, limit, and offset.
                 * @param memberId The ID of the member to retrieve departments for.
                 * @param limit The maximum number of departments to retrieve.
                 * @param offset The offset for pagination.
                 */
                void getMemberDepartments(const UInt32& memberId, const UInt32& limit, const UInt32& offset);

                /**
                 * @brief Retrieves a list of attendances for a member based on the specified member ID, limit, and offset.
                 * @param memberId The ID of the member to retrieve attendances for.
                 * @param limit The maximum number of attendances to retrieve.
                 * @param offset The offset for pagination.
                 */
                void getMemberAttendances(const UInt32& memberId, const UInt32& limit, const UInt32& offset);

                /**
                 * @brief Checks if a member has permission to purchase a firearm.
                 * @param memberId The ID of the member to check for permission.
                 * @return True if the member has permission, false otherwise.
                 */
                bool checkFirearmPurchasePermission(const UInt32& memberId);

            private:
                static inline void fillMemberPage(ObjMemberPageDto& page, const std::shared_ptr<oatpp::orm::QueryResult> dbResult, const UInt32& limit, const UInt32& offset)
                {
                    page->items = std::move(dbResult->fetch<oatpp::Vector<ObjMemberDto>>());
                    page->count  = std::move(static_cast<uint32_t>(page->items->size()));
                    page->limit  = limit;
                    page->offset = offset;
                }
            };

        } // namespace Members
    } // namespace managers
} // namespace primus



#endif // MEMBER_MANAGER_HPP