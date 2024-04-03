#include "AppComponent.hpp"

// Controller includes
#include "controller/StaticController.hpp"
#include "controller/MemberController.hpp"

#include "oatpp-swagger/Controller.hpp"

#include "oatpp/network/Server.hpp"

#include <iostream>

void run(void) {

  /* Register Components in scope of run() method */
  AppComponent components;

  /* Get router component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);


  /* Create StaticController and add all of its endpoints to router */
  router->addController(std::make_shared<StaticController>());

  /* Create MemberController and add all of its endpoints to router */
  router->addController(std::make_shared<MemberController>());


  /* Swagger UI Endpoint documentation */
  oatpp::web::server::api::Endpoints docEndpoints;
  docEndpoints.append(router->addController(StaticController::createShared())->getEndpoints());
  docEndpoints.append(router->addController(MemberController::createShared())->getEndpoints());                     // Add the endpoints of MemberController to the swagger ui documentation

  router->addController(oatpp::swagger::Controller::createShared(docEndpoints));

  /* Get connection handler component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

  /* Get connection provider component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

  /* Create server which takes provided TCP connections and passes them to HTTP connection handler */
  oatpp::network::Server server(connectionProvider, connectionHandler);

  /* Print info about server port */
  OATPP_LOGI("PrimusServer", "Server running on port %s", connectionProvider->getProperty("port").getData());

  /* Run server */
  server.run();
  
}

/**
 *  main
 */
int main(int argc, const char * argv[])
{
  oatpp::base::Environment::init();

  run();
  
  /* Print how much objects were created during app running, and what have left-probably leaked */
  /* Disable object counting for release builds using '-D OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag for better performance */
  std::cout << "\nEnvironment:\n";
  std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
  std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";
  
  oatpp::base::Environment::destroy();
  
  return 0;
}
