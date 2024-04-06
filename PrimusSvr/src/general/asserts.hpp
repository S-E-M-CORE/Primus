#ifndef PRIMUSASSERTS_HPP
#define PRIMUSASSERTS_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/component.hpp"

#include "dto/StatusDto.hpp"
#include "dto/PageDto.hpp"
#include "dto/Int32Dto.hpp"
#include "dto/BooleanDto.hpp"
#include "general/constants.hpp"
#include "dto/DatabaseDtos.hpp"

namespace primus
{
    namespace assert
    {
        oatpp::Object<primus::dto::StatusDto> assertMemberExists(const oatpp::UInt32 memberId)
        {
            OATPP_COMPONENT(std::shared_ptr<primus::component::DatabaseClient>, m_database);

            oatpp::Object<primus::dto::StatusDto> ret = primus::dto::StatusDto::createShared();

            auto dbResult = m_database->getMemberById(memberId);

            ret->code = 500;
            ret->message = "Unknown error";
            ret->status = "During check for wheather or not a member exists an unknown error accourd";

            if (!dbResult->isSuccess())
            {
                ret->code = 500;
                ret->message = dbResult->getErrorMessage();
                ret->status = "Failed to ask for member at database";
            } 
            else
            {
                auto member = dbResult->fetch<oatpp::Vector<oatpp::Object<primus::dto::database::MemberDto>>>();

                if (member->size() == 0)
                {
                    ret->code = 404;
                    ret->message = "Database request was successfully executed. The retrieved data did not include a member";
                    ret->status = "Member could not be found";
                }
                else if(member->size() > 1)
                {
                    OATPP_LOGE("Primus Assertion: ", "CRITICAL DATABASE ERROR: MORE THAN ONE USER WITH ID %d", memberId.operator v_uint32());
                    ret->code = 500;
                    ret->message = "During check for wheather a user exists, the retrieved data contained 2 seperate MemberDtos";
                    ret->status = "CRITICAL DATABASE ERROR: MORE THAN ONE USER";
                }
                else
                {
                    ret->code = 200;
                    ret->message = "OK";
                    ret->status = "Member was found";
                }
            }
            return ret;
        }
    }   // Namespace asserts
}   // Namespace primus

#endif // PRIMUSASSERTS_HPP