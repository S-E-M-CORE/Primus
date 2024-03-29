#ifndef STATICCONTROLLER_HPP
#define STATICCONTROLLER_HPP

//  ____  _        _   _         ____            _             _ _           
// / ___|| |_ __ _| |_(_) ___   / ___|___  _ __ | |_ _ __ ___ | | | ___ _ __ 
// \___ \| __/ _` | __| |/ __| | |   / _ \| '_ \| __| '__/ _ \| | |/ _ \ '__|
//  ___) | || (_| | |_| | (__  | |__| (_) | | | | |_| | | (_) | | |  __/ |   
// |____/ \__\__,_|\__|_|\___|  \____\___/|_| |_|\__|_|  \___/|_|_|\___|_|   

// An endpoint controller for providing prewritten, static websites

// Oatpp includes
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

// App includes
#include "dto/DTOs.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen

class StaticController : public oatpp::web::server::api::ApiController {
public:
    StaticController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
public:
  
  // ENDPOINT("GET", "/", root) {
  //   auto dto = MyDto::createShared();
  //   dto->statusCode = 200;
  //   dto->message = "Hello World!";
  //   return createDtoResponse(Status::CODE_200, dto);
  // }
  
  // TODO Insert Your endpoints here !!!
  
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif // STATICCONTROLLER_HPP
