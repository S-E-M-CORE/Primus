#ifndef PRIMUSCONSTANTS_HPP
#define PRIMUSCONSTANTS_HPP

namespace primus
{
	namespace constants
	{
		const bool useSwagger = true;
		const std::size_t logNameLength = 20;

		namespace errorManagement
		{
			enum Errorcode : unsigned int
			{
				NotFound,
				InternalError,
			};
		}

		namespace main				  {	const char logName[logNameLength] = "Startup            ";} // Namespace main
									  
		namespace databaseclient	  {	const char logName[logNameLength] = "DatabaseClient     ";} // Namespace databaseclient

		namespace apicontroller { 
			namespace static_endpoint {	const char logName[logNameLength] = "StaticController   ";} // Namespace static_endpoint

			namespace member_endpoint { const char logName[logNameLength] = "MemberController   ";} // Namespace member_endpoint
		} // Namespace apicontroller

	} // Namespace constants
} // Namespace Primus
#endif // PRIMUSCONSTANTS_HPP