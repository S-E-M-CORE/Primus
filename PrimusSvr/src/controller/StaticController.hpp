#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/protocol/http/outgoing/BufferBody.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

#include "general/constants.hpp"

namespace primus {
    namespace apicontroller {
        namespace static_endpoint {

#include OATPP_CODEGEN_BEGIN(ApiController)
            //  ____  _        _   _       ____            _             _ _           
            // / ___|| |_ __ _| |_(_) ___ / ___|___  _ __ | |_ _ __ ___ | | | ___ _ __ 
            // \___ \| __/ _` | __| |/ __| |   / _ \| '_ \| __| '__/ _ \| | |/ _ \ '__|
            //  ___) | || (_| | |_| | (__| |__| (_) | | | | |_| | | (_) | | |  __/ |   
            // |____/ \__\__,_|\__|_|\___|\____\___/|_| |_|\__|_|  \___/|_|_|\___|_|   
            class StaticController : public oatpp::web::server::api::ApiController
            {
            public:
                StaticController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
                    : oatpp::web::server::api::ApiController(objectMapper)
                {
                    
                    OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "StaticController (oatpp::web::server::api::ApiController) initialized");
                    OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "WEB_CONTENT_DIRECTORY: %s", WEB_CONTENT_DIRECTORY);
                    
                }

            public:
                static std::shared_ptr<StaticController> createShared(
                    OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
                )
                {
                    return std::make_shared<StaticController>(objectMapper);
                }

                ENDPOINT("GET", "/web/*", files,
                    REQUEST(std::shared_ptr<IncomingRequest>, request))
                {
                    
                    OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "Received request to serve file: %s", request->getPathTail()->c_str());

                    std::string filePath(WEB_CONTENT_DIRECTORY);
                    filePath.append("/");

                    if (request->getPathTail() == "")
                        filePath.append("index.html");
                    else
                        filePath.append(request->getPathTail());

                    OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "Serving file: %s", filePath.c_str());

                    std::ifstream file(filePath, std::ios::binary);
                    if (file.good())
                    {
                        OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "File at %s found", filePath.c_str());

                        std::ostringstream content;
                        content << file.rdbuf();

                        file.close();

                        OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "Processed request to serve file: %s", request->getPathTail()->c_str());
                        

                        return createResponse(Status::CODE_200, content.str());
                    }
                    else
                    {
                        OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "File at %s was not found", filePath.c_str());

                        auto status = primus::dto::StatusDto::createShared();

                        std::string verboseMessage = "File at \"";
                        verboseMessage.append(filePath.c_str());
                        verboseMessage.append("\" could not be found");

                        status->code = 404;
                        status->message = verboseMessage;
                        status->status = "NOT FOUND";
                        return createDtoResponse(Status::CODE_404, status);
                    }
                }

                ENDPOINT("GET", "/", root,
                    REQUEST(std::shared_ptr<IncomingRequest>, request))
                {
                    
                    OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "Received request for root");

                    auto response = createResponse(Status::CODE_302, "Redirect");
                    response->putHeader("Location", "/web/");

                    OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "Redirecting to /web/");
                    

                    return response;
                }

                ENDPOINT("GET", "/api/member/{memberId}/assets/profilepicture", getAvatar, PATH(oatpp::String, memberId))
                {
                    
                    OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "Received request to serve profile picture for member with id  %s", memberId->c_str());

                    std::string filePath(USER_ASSETS);
                    std::string finalPath; filePath.append("/");
                    std::ostringstream content;
                    int choice;

                    {
                        auto now = std::chrono::system_clock::now();
                        auto since_epoch = now.time_since_epoch();
                        auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch).count();
                        choice = millis % 2;
                    }

                    auto userStatus = primus::assert::assertMemberExists(oatpp::utils::conversion::strToUInt32(memberId->c_str()));

                    if (userStatus->code != 200)
                    {
                        OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "User does not exist. Returning default profile picture");

                        filePath.append(choice == 1 ? "default-avatar-1.jpg" : "default-avatar-2.jpg");

                    }
                    else
                    {
                        OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "User found. Looking for profile picture within directory");
                        filePath.append(memberId);
                        filePath.append(".jpg");
                    }

                    finalPath = filePath;

                    OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "Serving file: %s", filePath.c_str());

                    std::ifstream file(filePath, std::ios::binary);
                    if (!file.good())
                    {
                        OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "File at %s was not found", filePath.c_str());

                        std::string filePath2(USER_ASSETS);
                        filePath2.append(choice == 1 ? "/default-avatar-1.jpg" : "/default-avatar-2.jpg");

                        finalPath = filePath2;

                        std::ifstream file2(filePath2, std::ios::binary);

                        OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "Proceeding to serve file %s", filePath2.c_str());

                        if (!file2.good())
                        {
                            OATPP_LOGE(primus::constants::apicontroller::static_endpoint::logName, "Default profile picture not found at %s", filePath2.c_str());

                            auto status = primus::dto::StatusDto::createShared();

                            oatpp::String verboseMessage = "No picture to serve. Looked at given paths: ";
                            verboseMessage->append(filePath);
                            verboseMessage->append("   |   ");
                            verboseMessage->append(filePath2);

                            status->code = 404;
                            status->message = verboseMessage;
                            status->status = "NOT FOUND";
                            return createDtoResponse(Status::CODE_404, status);
                        }
                        content << file2.rdbuf();
                    }
                    else
                    {
                        content << file.rdbuf();
                    }

                    OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "File at %s found", finalPath.c_str());

                    file.close();

                    

                    return createResponse(Status::CODE_200, content.str());
                }

                // Endpoint Infos

                ENDPOINT_INFO(getAvatar) {
                    info->summary = "Get profile picture for a member";
                    info->path = "/api/member/{memberId}/assets/profilepicture";
                    info->pathParams.add("memberId", oatpp::String::Class::getType());
                    info->addResponse<String>(Status::CODE_200, "image/jpeg");
                    info->addResponse<Object<primus::dto::StatusDto>>(Status::CODE_404, "application/json");
                    info->addTag("Member");
                    info->addTag("Static File");
                }


                ENDPOINT_INFO(files)
                {
                    info->name = "files";
                    info->summary = "Serve static files";
                    info->description = "This endpoint serves static files from the '/web' directory.";
                    info->path = "/web/*";
                    info->method = "GET";
                    info->addTag("Static File");
                    info->pathParams["*"].description = "File path relative to the '/web' directory";
                    info->addResponse<String>(Status::CODE_200, "text/html");
                    info->addResponse<Object<primus::dto::StatusDto>>(Status::CODE_404, "application/json");
                }

                ENDPOINT_INFO(root)
                {
                    info->name = "root";
                    info->summary = "Redirect to web directory";
                    info->description = "This endpoint redirects requests to the root URL to the '/web' directory.";
                    info->path = "/";
                    info->addTag("Static File");
                    info->method = "GET";
                    info->addResponse<String>(Status::CODE_302, "text/html");
                }
            };

#include OATPP_CODEGEN_END(ApiController)

        } // namespace static_endpoint
    } // namespace apicontroller
} // namespace primus
