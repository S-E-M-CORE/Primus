#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>

#include "dto/StatusDto.hpp"


namespace primus {
    namespace exceptions {
        //  ____  _        _             _____                    _   _             
        // / ___|| |_ __ _| |_ _   _ ___| ____|_  _____ ___ _ __ | |_(_) ___  _ __  
        // \___ \| __/ _` | __| | | / __|  _| \ \/ / __/ _ \ '_ \| __| |/ _ \| '_ \ 
        //  ___) | || (_| | |_| |_| \__ \ |___ >  < (_|  __/ |_) | |_| | (_) | | | |
        // |____/ \__\__,_|\__|\__,_|___/_____/_/\_\___\___| .__/ \__|_|\___/|_| |_|
        //                                                 |_|                      
        /**
        * @brief Custom exception class for representing status exceptions.
        */
        class StatusException : public std::exception
        {
            using StatusDto = primus::dto::StatusDto;

            oatpp::Object<StatusDto> m_status{}; /**< StatusDto object to store exception details. */
        public:
            /**
             * @brief Constructs a StatusException object with the provided code, status, and message.
             * @param code The html error code.
             * @param status Short status message.
             * @param message Detailed description of the error (if an error accoured).
             */
            StatusException(uint32_t code, const oatpp::String& status, const oatpp::String& message) throw() :
                m_status(primus::dto::StatusDto::createShared())
            {
                m_status->code = code;
                m_status->status = status;
                m_status->message = message;
            }

            oatpp::Object<StatusDto>& getStatusDtoObject(void)
            {
                return m_status;
            }

            /**
             * @brief Retrieves the status description associated with the exception.
             * @return Short status message.
             */
            virtual char const* what() const throw()
            {
                return m_status->status->c_str();
            }
        };

        /**
        *  @brief Throws a StatusException which will be used in the endpoint controller classes for returning values
         * @param COND - boolean statement. If evaluates to false - throw error.
         * @param CODE - html status code;.
         * @param STATUS - Short description.
         * @param MESSAGE - Verbose message
         */
        #define PRIMUS_THROW_STATUS_EXCEP(CODE, STATUS, MESSAGE) throw primus::exceptions::StatusException(CODE, STATUS, MESSAGE);
        #define PRIMUS_ASSERT_HTTP(COND, CODE, STATUS, MESSAGE) if(!COND) throw primus::exceptions::StatusException(CODE, STATUS, MESSAGE);


    } // Namespace exceptions
} // Namespace primus

#endif //EXCEPTIONS_HPP