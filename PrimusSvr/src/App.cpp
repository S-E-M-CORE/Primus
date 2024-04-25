#include "AppComponent.hpp"

// Controller includes
#include "general/asserts.hpp"
#include "controller/StaticController.hpp"
#include "controller/MemberController.hpp"
#include "oatpp-swagger/Controller.hpp"
#include "oatpp/network/Server.hpp"
#include <iostream>

// __| |__________________________________| |__
// __   __________________________________   __
//   | |                                  | |  
//   | | ____       _                     | |  
//   | ||  _ \ _ __(_)_ __ ___  _   _ ___ | |  
//   | || |_) | '__| | '_ ` _ \| | | / __|| |  
//   | ||  __/| |  | | | | | | | |_| \__ \| |  
//   | ||_|   |_|  |_|_| |_| |_|\__,_|___/| |  
// __| |__________________________________| |__
// __   __________________________________   __
//   | |                                  | |  
namespace primus {
    namespace main {
        void run(void) {
            using StaticController     =    primus::apicontroller::static_endpoint::StaticController;
            using MemberController     =    primus::apicontroller::member_endpoint::MemberController;
            using AppComponent         =    primus::component::AppComponent                         ;
            using DatabaseClient       =    primus::component::DatabaseClient                       ;
            using DatabaseComponent    =    primus::component::DatabaseComponent                    ;
            using SwaggerComponent     =    primus::component::SwaggerComponent                     ;
            
            const char* const logName = primus::constants::main::logName;

            OATPP_LOGI(logName, "Initializing AppComponents");

            /* Register Components in scope of run() method */
            AppComponent components{};

            OATPP_LOGI(logName, "Creating HttpRouter");

            /* Get router component */
            OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

            OATPP_LOGI(logName, "Adding static endpoints...");

            /* Create StaticController and add all of its endpoints to router */
            router->addController(std::make_shared<StaticController>());

            OATPP_LOGI(logName, "Adding member endpoints...");

            /* Create MemberController and add all of its endpoints to router */
            router->addController(std::make_shared<MemberController>());

            if (primus::constants::useSwagger)
            {
                OATPP_LOGI(logName, "Collecting endpoints for swagger-ui");

                /* Swagger UI Endpoint documentation */
                oatpp::web::server::api::Endpoints docEndpoints;

                docEndpoints.append(router->addController(StaticController::createShared())->getEndpoints());
                OATPP_LOGI(logName, "Collected static endpoints");

                docEndpoints.append(router->addController(MemberController::createShared())->getEndpoints());                     // Add the endpoints of MemberController to the swagger ui documentation
                OATPP_LOGI(logName, "Collected member endpoints");

                OATPP_LOGI(logName, "Initializing Swagger");
                router->addController(oatpp::swagger::Controller::createShared(docEndpoints));

            }

            OATPP_LOGI(logName, "Creating additional component connectionHandler (oatpp::network::ConnectionHandler)");

            /* Get connection handler component */
            OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

            OATPP_LOGI(logName, "Creating additional component ServerConnectionProvider (oatpp::network::ServerConnectionProvider)");

            /* Get connection provider component */
            OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

            OATPP_LOGI(logName, "Initializing server (oatpp::network::Server) with connectionProvider and connectionHandler");

            /* Create server which takes provided TCP connections and passes them to HTTP connection handler */
            oatpp::network::Server server(connectionProvider, connectionHandler);

            OATPP_LOGI(logName, "Server has been initialized");

            OATPP_LOGI(logName, "Starting server");

            {
                const char* host{static_cast<const char*>(connectionProvider->getProperty("host").getData())};
                const char* port{ static_cast<const char*>(connectionProvider->getProperty("port").getData()) };

                host = host[0] == 48 && host[1] == 46 ? "localhost" : host;

                OATPP_LOGI(logName, "Primus server at http://%s:%s/web/", host, port);

                if(primus::constants::useSwagger)
                    OATPP_LOGI(logName, "Swagger-ui at http://%s:%s/swagger/ui", host, port);
            }

            OATPP_LOGI(logName, "__| |__________________________________| |__ ");
            OATPP_LOGI(logName, " __   __________________________________   __");
            OATPP_LOGI(logName, "   | |                                  | |  ");
            OATPP_LOGI(logName, "   | | ____       _                     | |  ");
            OATPP_LOGI(logName, "   | ||  _ \\ _ __(_)_ __ ___  _   _ ___ | |  ");
            OATPP_LOGI(logName, "   | || |_) | '__| | '_ ` _ \\| | | / __|| |  ");
            OATPP_LOGI(logName, "   | ||  __/| |  | | | | | | | |_| \\__ \\| |  ");
            OATPP_LOGI(logName, "   | ||_|   |_|  |_|_| |_| |_|\\__,_|___/| |  ");
            OATPP_LOGI(logName, " __| |__________________________________| |__");
            OATPP_LOGI(logName, " __   __________________________________   __");
            OATPP_LOGI(logName, "   | |                                  | |  ");

            /* Run server */
            server.run();

        } // run()
    } // namespace main
} // namespace primus

//  __  __       _       
// |  \/  | __ _(_)_ __  
// | |\/| |/ _` | | '_ \ 
// | |  | | (_| | | | | |
// |_|  |_|\__,_|_|_| |_|
/**
*  main
*/
int main(int argc, const char* argv[])
{
    oatpp::base::Environment::init();

    primus::main::run();

    /* Print how much objects were created during app running, and what have left-probably leaked */
    /* Disable object counting for release builds using '-D OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag for better performance */
    std::cout << "\nEnvironment:\n";
    std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
    std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";

    oatpp::base::Environment::destroy();

    return 0;
}