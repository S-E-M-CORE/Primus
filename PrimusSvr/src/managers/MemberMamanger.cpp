#include "MemberManager.hpp"

using MemberManager = primus::managers::Members::MemberManager;

std::shared_ptr<MemberManager> MemberManager::createShared(void)
{
    static MemberManager instance;

    return std::make_shared<MemberManager>(instance);
}

void MemberManager::getListAll(ObjMemberPageDto& page, const UInt32& limit, const UInt32& offset)
{
    OATPP_LOGD(primus::constants::apicontroller::member_endpoint::logName, "Received request to get a list of all members. Limit: %d, Offset: %d", limit.operator v_uint32(), offset.operator v_uint32());

    std::shared_ptr<oatpp::orm::QueryResult> dbResult;

    dbResult = m_database->getAllMembers(limit, offset);

    PRIMUS_ASSERT_HTTP(dbResult->isSuccess(), 500, "Database request error", dbResult->getErrorMessage());

    MemberManager::fillMemberPage
    (
        page,
        dbResult,
        limit,
        offset
    );
}
void MemberManager::getListActive(ObjMemberPageDto& page, const UInt32& limit, const UInt32& offset)
{
    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get a list of all active members. Limit: %d, Offset: %d", limit.operator v_uint32(), offset.operator v_uint32());

    std::shared_ptr<oatpp::orm::QueryResult> dbResult;

    dbResult = m_database->getActiveMembers(limit, offset);

    PRIMUS_ASSERT_HTTP(dbResult->isSuccess(), 500, "Database request error", dbResult->getErrorMessage());

    MemberManager::fillMemberPage
    (
        page,
        dbResult,
        limit,
        offset
    );
}
void MemberManager::getListInactive(ObjMemberPageDto& page, const UInt32& limit, const UInt32& offset)
{
    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get a list of all inactive members. Limit: %d, Offset: %d", limit.operator v_uint32(), offset.operator v_uint32());

    std::shared_ptr<oatpp::orm::QueryResult> dbResult;

    dbResult = m_database->getInactiveMembers(limit, offset);

    PRIMUS_ASSERT_HTTP(dbResult->isSuccess(), 500, "Database request error", dbResult->getErrorMessage());

    MemberManager::fillMemberPage
    (
        page,
        dbResult,
        limit,
        offset
    );
}
void MemberManager::getListBirthdayNext(ObjMemberPageDto& page, const UInt32& limit, const UInt32& offset)
{
    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get a list of all members with upcomming birthdays. Limit: %d, Offset: %d", limit.operator v_uint32(), offset.operator v_uint32());

    std::shared_ptr<oatpp::orm::QueryResult> dbResult;

    dbResult = m_database->getMembersWithUpcomingBirthday(limit, offset);

    PRIMUS_ASSERT_HTTP(dbResult->isSuccess(), 500, "Database request error", dbResult->getErrorMessage());

    MemberManager::fillMemberPage
    (
        page,
        dbResult,
        limit,
        offset
    );
}
void MemberManager::getListAttendanceMost(ObjMemberPageDto& page, const UInt32& limit, const UInt32& offset)
{
    OATPP_LOGI(primus::constants::apicontroller::member_endpoint::logName, "Received request to get a list of all members with most training. Limit: %d, Offset: %d", limit.operator v_uint32(), offset.operator v_uint32());

    std::shared_ptr<oatpp::orm::QueryResult> dbResult;

    dbResult = m_database->getMembersByMostTraining(limit, offset);

    PRIMUS_ASSERT_HTTP(dbResult->isSuccess(), 500, "Database request error", dbResult->getErrorMessage());

    MemberManager::fillMemberPage
    (
        page,
        dbResult,
        limit,
        offset
    );
}

void MemberManager::getList(ObjMemberPageDto& list, const String& attribute, const UInt32& limit, const UInt32& offset)
{
    switch (stringToMembersList(attribute))
    {
        case MembersLists::all:         return getListAll               (list, limit, offset);
        case MembersLists::active:      return getListActive            (list, limit, offset);
        case MembersLists::inactive:    return getListInactive          (list, limit, offset);
        case MembersLists::birthday:    return getListBirthdayNext      (list, limit, offset);
        case MembersLists::attendance:  return getListAttendanceMost    (list, limit, offset);
        default:
        {
            char errorMsg[256];
            sprintf_s(errorMsg, "Received request to get a list of members with %s, which is not an available attribute", attribute->c_str());
            OATPP_LOGD(MemberManager::logName, errorMsg);

            PRIMUS_THROW_STATUS_EXCEP(400, "ATTRIBUTE NOT FOUND", "Received request to get a list of members with invalid attribute. Available options: birthday, all, active or inactive");
        }
    }
}

void MemberManager::activateMember(const UInt32& memberId)
{
    
}

void MemberManager::deactivateMember(const UInt32& memberId)
{
    
}

void MemberManager::getMemberById(ObjMemberDto& dto, const UInt32& memberId)
{
    
}

MemberManager::UInt32 MemberManager::createMember(const ObjMemberDto& member)
{
    return MemberManager::UInt32(static_cast<uint32_t>(0));
}

void MemberManager::updateMember(const ObjMemberDto& member)
{

}

MemberManager::UInt32 MemberManager::countMembers(const String& attribute)
{
    return MemberManager::UInt32(static_cast<uint32_t>(0));
}

MemberManager::UInt32 MemberManager::countAttribute(const UInt32& memberId, String& attribute)
{
    
    return MemberManager::UInt32(static_cast<uint32_t>(0));
}

void MemberManager::addMemberToDepartment(const UInt32& memberId, const UInt32& departmentId)
{
    
}

void MemberManager::RemoveMemberFromDepartment(const UInt32& memberId, const UInt32& departmentId)
{
    
}

void MemberManager::addAddressToMember(const UInt32& memberId, const ObjAddressDto& address)
{
    
}

void MemberManager::addAddressToMember(const UInt32& memberId, const UInt32& addressId)
{
    
}

void MemberManager::removeAddressFromMember(const UInt32& memberId, const UInt32& addressId)
{
    
}

void MemberManager::removeAddressFromMember(const UInt32& memberId, const ObjAddressDto& addressId)
{
    
}

void MemberManager::addMemberAttendance(const UInt32& memberId, const String& date)
{
    
}

void MemberManager::removeMemberAttendance(const UInt32& memberId, const String& date)
{
    
}

MemberManager::UInt32 MemberManager::getFeeOfMember(const UInt32& memberId)
{
    
    return MemberManager::UInt32(static_cast<uint32_t>(0));
}

void MemberManager::getMemberList(const String& attribute, const UInt32& memberId, const UInt32& limit, const UInt32& offset)
{
    
}

void MemberManager::getMemberAddresses(const UInt32& memberId, const UInt32& limit, const UInt32& offset)
{
    
}

void MemberManager::getMemberDepartments(const UInt32& memberId, const UInt32& limit, const UInt32& offset)
{
    
}

void MemberManager::getMemberAttendances(const UInt32& memberId, const UInt32& limit, const UInt32& offset)
{
    
}

bool MemberManager::checkFirearmPurchasePermission(const UInt32& memberId)
{
    
    return false;
}
