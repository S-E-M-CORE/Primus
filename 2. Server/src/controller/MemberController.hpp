#ifndef MEMBERCONTROLLER_HPP
#define MEMBERCONTROLLER_HPP

//  __  __                _                      
// |  \/  | ___ _ __ ___ | |__   ___ _ __        
// | |\/| |/ _ \ '_ ` _ \| '_ \ / _ \ '__|       
// | |  | |  __/ | | | | | |_) |  __/ |          
// |_|__|_|\___|_| |_| |_|_.__/ \___|_|          
//  / ___|___  _ __ | |_ _ __ ___ | | | ___ _ __ 
// | |   / _ \| '_ \| __| '__/ _ \| | |/ _ \ '__|
// | |__| (_) | | | | |_| | | (_) | | |  __/ |   
//  \____\___/|_| |_|\__|_|  \___/|_|_|\___|_|   

// Controller to handle Member related requests.

// Oatpp includes
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

// App includes
#include "dto/databaseDTOs/MemberDTO.hpp"
#include "service/MemberService.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen

class MemberController : public oatpp::web::server::api::ApiController {
public:
    /**
     * Constructor.
     * @param objectMapper - object mapper used to serialize/deserialize DTOs.
     */
    MemberController(OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper)
    {}



};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif // MEMBERCONTROLLER_HPP
