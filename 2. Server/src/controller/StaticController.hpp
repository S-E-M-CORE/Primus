#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/protocol/http/outgoing/BufferBody.hpp"
#include <fstream>

#include "general/constants.hpp"

namespace primus {
    namespace apicontroller {
        namespace static_endpoint {

#include OATPP_CODEGEN_BEGIN(ApiController)

            class StaticController : public oatpp::web::server::api::ApiController
            {
            public:
                StaticController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
                    : oatpp::web::server::api::ApiController(objectMapper)
                {
                    OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, primus::constants::apicontroller::static_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "StaticController (oatpp::web::server::api::ApiController) initialized");
                    OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "WEB_CONTENT_DIRECTORY: %s", WEB_CONTENT_DIRECTORY);
                    OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, primus::constants::apicontroller::static_endpoint::logSeperation);
                }

            public:
                static std::shared_ptr<StaticController> createShared(
                    OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
                )
                {
                    return std::make_shared<StaticController>(objectMapper);
                }

                // Funktion zum Lesen von Dateien
                oatpp::String readFile(const char* filename)
                {
                    std::ifstream file(filename);
                    if (file)
                    {
                        OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "File at %s found", filename);
                        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

                        return oatpp::String(content.c_str(), content.size());
                    }
                    else
                    {
                        OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "File at %s was not found", filename);

                        return "File not found!";
                    }
                }

                ENDPOINT("GET", "/web/*", files,
                    REQUEST(std::shared_ptr<IncomingRequest>, request))
                {
                    OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, primus::constants::apicontroller::static_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "Received request to serve file: %s", request->getPathTail()->c_str());

                    std::string filePath(WEB_CONTENT_DIRECTORY);
                    filePath.append("/");

                    if (request->getPathTail() == "")
                        filePath.append("index.html");
                    else
                        filePath.append(request->getPathTail());

                    OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "Serving file: %s", filePath.c_str());

                    oatpp::String buffer = readFile(filePath.c_str());

                    OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "Processed request to serve file: %s", request->getPathTail()->c_str());
                    OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, primus::constants::apicontroller::static_endpoint::logSeperation);

                    return createResponse(Status::CODE_200, buffer);
                }

                // Endpunkt f�r die Indexseite
                ENDPOINT("GET", "/", root,
                    REQUEST(std::shared_ptr<IncomingRequest>, request))
                {
                    OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, primus::constants::apicontroller::static_endpoint::logSeperation);
                    OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "Received request for root");

                    auto response = createResponse(Status::CODE_302, "Redirect");
                    response->putHeader("Location", "/web/");

                    OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, "Redirecting to /web/");
                    OATPP_LOGI(primus::constants::apicontroller::static_endpoint::logName, primus::constants::apicontroller::static_endpoint::logSeperation);

                    return response;
                }

                // Endpoint Infos

                ENDPOINT_INFO(files) {
                    info->name = "files";
                    info->summary = "Serve static files";
                    info->description = "Serves static files from the specified directory.";
                    info->path = "/web/*";
                    info->method = "GET";
                    info->tags = { "Static" };
                    info->addResponse<String>(Status::CODE_200, "text/html", "Content of the requested file");
                    info->addResponse<String>(Status::CODE_404, "text/plain", "File not found");
                    info->addResponse<String>(Status::CODE_500, "text/plain", "Internal Server Error");
                }

                ENDPOINT_INFO(root) {
                    info->name = "root";
                    info->summary = "Redirect to web directory";
                    info->description = "Redirects requests to the root path to the web directory.";
                    info->path = "/";
                    info->method = "GET";
                    info->tags = { "Static" };
                    info->addResponse<String>(Status::CODE_302, "text/plain", "Redirects to /web/");
                }

            };

#include OATPP_CODEGEN_END(ApiController)

        } // namespace static_endpoint
    } // namespace apicontroller
} // namespace primus
