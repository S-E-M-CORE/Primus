#include "AppComponent.hpp"

// Controller includes
#include "controller/StaticController.hpp"
#include "controller/MemberController.hpp"

#include "oatpp-swagger/Controller.hpp"

#include "oatpp/network/Server.hpp"

#include <iostream>

namespace primus {
    namespace main {
        void run(void) {
            typedef primus::apicontroller::static_endpoint::StaticController    StaticController;
            typedef primus::apicontroller::member_endpoint::MemberController    MemberController;
            typedef primus::component::AppComponent                             AppComponent;
            typedef primus::component::DatabaseClient                           DatabaseClient;
            typedef primus::component::DatabaseComponent                        DatabaseComponent;
            typedef primus::component::SwaggerComponent                         SwaggerComponent;

            OATPP_LOGI(primus::constants::main::logName, primus::constants::main::logSeperation);
            OATPP_LOGI(primus::constants::main::logName, "Initializing AppComponents");

            /* Register Components in scope of run() method */
            AppComponent components;

            OATPP_LOGI(primus::constants::main::logName, "AppComponents have been initialized");
            OATPP_LOGI(primus::constants::main::logName, "Creating additional component router (oatpp::web::server::HttpRouter)");

            /* Get router component */
            OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

            OATPP_LOGI(primus::constants::main::logName, "router (oatpp::web::server::HttpRouter) has been initialized");
            OATPP_LOGI(primus::constants::main::logName, "Adding Endpoints of StaticController to router");

            /* Create StaticController and add all of its endpoints to router */
            router->addController(std::make_shared<StaticController>());

            OATPP_LOGI(primus::constants::main::logName, "Endpoints of StaticController successfully added");
            OATPP_LOGI(primus::constants::main::logName, "Adding Endpoints of MemberController to router");

            /* Create MemberController and add all of its endpoints to router */
            router->addController(std::make_shared<MemberController>());

            OATPP_LOGI(primus::constants::main::logName, "Endpoints of MemberController successfully added");
            OATPP_LOGI(primus::constants::main::logName, "Endpoints of MemberController successfully added");
            OATPP_LOGI(primus::constants::main::logName, "Collecting Endpoints for swagger-ui...");

            /* Swagger UI Endpoint documentation */
            oatpp::web::server::api::Endpoints docEndpoints;

            docEndpoints.append(router->addController(StaticController::createShared())->getEndpoints());
            OATPP_LOGI(primus::constants::main::logName, "Collected Endpoints of StaticController");

            docEndpoints.append(router->addController(MemberController::createShared())->getEndpoints());                     // Add the endpoints of MemberController to the swagger ui documentation
            OATPP_LOGI(primus::constants::main::logName, "Collected Endpoints of MemberController");

            OATPP_LOGI(primus::constants::main::logName, "Initializing Swagger Endpoint-Controller (oatpp::swagger::Controller) with collected endpoints");
            router->addController(oatpp::swagger::Controller::createShared(docEndpoints));

            OATPP_LOGI(primus::constants::main::logName, "Creating additional component connectionHandler (oatpp::network::ConnectionHandler)");

            /* Get connection handler component */
            OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

            OATPP_LOGI(primus::constants::main::logName, "connectionHandler(oatpp::network::ConnectionHandler) successfully initialized");

            OATPP_LOGI(primus::constants::main::logName, "Creating additional component ServerConnectionProvider (oatpp::network::ServerConnectionProvider)");

            /* Get connection provider component */
            OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

            OATPP_LOGI(primus::constants::main::logName, "ServerConnectionProvider (oatpp::network::ServerConnectionProvider) successfully initialized");
            OATPP_LOGI(primus::constants::main::logName, "Initializing server (oatpp::network::Server) with connectionProvider and connectionHandler");

            /* Create server which takes provided TCP connections and passes them to HTTP connection handler */
            oatpp::network::Server server(connectionProvider, connectionHandler);

            OATPP_LOGI(primus::constants::main::logName, "Server has been initialized");

            OATPP_LOGI(primus::constants::main::logName, "Starting server");
            OATPP_LOGI(primus::constants::main::logName, "Host: %s", connectionProvider->getProperty("host").getData());
            OATPP_LOGI(primus::constants::main::logName, "Port: %s", connectionProvider->getProperty("port").getData());
            OATPP_LOGI(primus::constants::main::logName, primus::constants::main::logSeperation);

            /* Run server */
            server.run();

        } // run()
    } // namespace main
} // namespace primus

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