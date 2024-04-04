#ifndef PRIMUSCONSTANTS_HPP
#define PRIMUSCONSTANTS_HPP

#include <cstddef>

namespace primus
{
	namespace constants
	{
		const std::size_t logNameLength = 20;
		const std::size_t logSeperationLength = 60;

		namespace main
		{
			const char logName[logNameLength]			  = "Main initialization";
			const char logSeperation[logSeperationLength] = "-----------------------------";
		} // Namespace main

		namespace databaseclient
		{
			const char logName[logNameLength] = "DatabaseClient     ";
			const char logSeperation[logSeperationLength] = "-----------------------------";
		}

		namespace apicontroller
		{
			namespace static_endpoint
			{
					// Name and seperation while logging
					const char logName[logNameLength]		      = "StaticController   ";
					const char logSeperation[logSeperationLength] = "------------------------";
			} // Namespace static_endpoint

			namespace member_endpoint
			{
					// Name and seperation while logging
					const char logName[logNameLength]		      = "MemberController   ";
					const char logSeperation[logSeperationLength] = "------------------------";
			} // Namespace Member
		} // Namespace ApiController
	} // Namespace constants
} // Namespace Primus
#endif // PRIMUSCONSTANTS_HPP