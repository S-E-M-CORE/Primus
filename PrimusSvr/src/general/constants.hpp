#ifndef PRIMUSCONSTANTS_HPP
#define PRIMUSCONSTANTS_HPP

namespace primus
{
	namespace constants
	{
		const bool useSwagger = true;
		constexpr std::size_t logNameLength = 20;

		namespace main				  { constexpr char logName[logNameLength] = "Startup            ";} // Namespace main
									  
		namespace databaseclient	  { constexpr char logName[logNameLength] = "DatabaseClient     ";} // Namespace databaseclient

		namespace managers {
			namespace manager_member { constexpr char logName[logNameLength] = "MemberManager      "; } // Namespace manager_member
			namespace manager_static { constexpr char logName[logNameLength] = "StaticManager      "; } // Namespace manager_static
		} // Namespace managers

		namespace apicontroller { 
			namespace static_endpoint { constexpr char logName[logNameLength] = "StaticEndpoint     ";} // Namespace static_endpoint
			namespace member_endpoint { constexpr char logName[logNameLength] = "MemberEndpoint     ";} // Namespace member_endpoint
		} // Namespace apicontroller

	} // Namespace constants
} // Namespace Primus
#endif // PRIMUSCONSTANTS_HPP