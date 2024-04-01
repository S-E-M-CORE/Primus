#include "AppComponent.hpp"

// Controller includes
#include "controller/StaticController.hpp"
#include "controller/MemberController.hpp"
#include "controller/AddressController.hpp"
#include "controller/DepartmentController.hpp"
#include "controller/MembershipController.hpp"
#include "controller/TrainingController.hpp"

#include "controller/relations/MemberAddressRelController.hpp"
#include "controller/relations/MembershipDepartmentRelController.hpp"
#include "controller/relations/MemberTrainingRelController.hpp"
#include "controller/relations/DepartmentTrainingRelController.hpp"
#include "controller/relations/MemberMembershipRelController.hpp"

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

  /* Create AddressController and add all of its endpoints to router */
  router->addController(std::make_shared<AddressController>());

  /* Create DepartmentController and add all of its endpoints to router */
  router->addController(std::make_shared<DepartmentController>());

  /* Create MembershipController and add all of its endpoints to router */
  router->addController(std::make_shared<MembershipController>());

  /* Create TrainingController and add all of its endpoints to router */
  router->addController(std::make_shared<TrainingController>());

  /* Create MemberAddressRelController and add all of its endpoints to router */
  router->addController(std::make_shared<MemberAddressRelController>());
  
  /* Create MembershipDepartmentRelController and add all of its endpoints to router */
  router->addController(std::make_shared<MembershipDepartmentRelController>());

  /* Create MemberTrainingRelController and add all of its endpoints to router */
  router->addController(std::make_shared<MemberTrainingRelController>());

  /* Create DepartmentTrainingRelController and add all of its endpoints to router */
  router->addController(std::make_shared<DepartmentTrainingRelController>());
  
  /* Create MemberMembershipRelController and add all of its endpoints to router */
  router->addController(std::make_shared<MemberMembershipRelController>());


  /* Swagger UI Endpoint documentation */
  oatpp::web::server::api::Endpoints docEndpoints;
  docEndpoints.append(router->addController(MemberController::createShared())->getEndpoints());                     // Add the endpoints of MemberController to the swagger ui documentation
  docEndpoints.append(router->addController(AddressController::createShared())->getEndpoints());                    // Add the endpoints of AddressController to the swagger ui documentation
  docEndpoints.append(router->addController(DepartmentController::createShared())->getEndpoints());                 // Add the endpoints of DepartmentController to the swagger ui documentation
  docEndpoints.append(router->addController(MembershipController::createShared())->getEndpoints());                 // Add the endpoints of MembershipController to the swagger ui documentation
  docEndpoints.append(router->addController(TrainingController::createShared())->getEndpoints());                   // Add the endpoints of TrainingController to the swagger ui documentation
  docEndpoints.append(router->addController(MemberAddressRelController::createShared())->getEndpoints());           // Add the endpoints of MemberAddressRelController to the swagger ui documentation
  docEndpoints.append(router->addController(MembershipDepartmentRelController::createShared())->getEndpoints());    // Add the endpoints of MembershipDepartmentRelController to the swagger ui documentation
  docEndpoints.append(router->addController(MemberTrainingRelController::createShared())->getEndpoints());          // Add the endpoints of MemberTrainingRelController to the swagger ui documentation
  docEndpoints.append(router->addController(DepartmentTrainingRelController::createShared())->getEndpoints());      // Add the endpoints of DepartmentTrainingRelController to the swagger ui documentation
  docEndpoints.append(router->addController(MemberMembershipRelController::createShared())->getEndpoints());        // Add the endpoints of MemberMembershipRelController to the swagger ui documentation

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
