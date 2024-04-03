#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/protocol/http/outgoing/BufferBody.hpp"
#include <fstream>

#include OATPP_CODEGEN_BEGIN(ApiController)

class StaticController : public oatpp::web::server::api::ApiController {
public:
    StaticController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper)
    {}

public:
    static std::shared_ptr<StaticController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
    )
    {
        return std::make_shared<StaticController>(objectMapper);
    }

    // Funktion zum Lesen von Dateien
    oatpp::String readFile(const char* filename) {
        std::ifstream file(filename);
        if (file) {
            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            return oatpp::String(content.c_str(), content.size());
        }
        else {
            return "File not found!";
        }
    }

    // Endpunkt für die Indexseite
<<<<<<< HEAD
    ENDPOINT("GET", "/web/*", files,
=======
    ENDPOINT("GET", "*", files, 
>>>>>>> db1965b318089d88d214892967e8600fa806f9c6
        REQUEST(std::shared_ptr<IncomingRequest>, request))
    {
        std::string filePath(WEB_CONTENT_DIRECTORY);
        filePath.append("/");
<<<<<<< HEAD

        if (request->getPathTail() == "")
            filePath.append("index.html");
        else
            filePath.append(request->getPathTail());

        oatpp::String buffer = readFile(filePath.c_str());
        return createResponse(Status::CODE_200, buffer);
    }

    // Endpunkt für die Indexseite
    ENDPOINT("GET", "/", root,
        REQUEST(std::shared_ptr<IncomingRequest>, request))
    {
        auto response = createResponse(Status::CODE_302, "Redirect");
        response->putHeader("Location", "/web/");
        return response;
=======

        if (request->getPathTail() == "")
            filePath.append("index.html");
        else
            filePath.append(request->getPathTail());

        oatpp::String buffer = readFile(filePath.c_str());
        return createResponse(Status::CODE_200, buffer);
>>>>>>> db1965b318089d88d214892967e8600fa806f9c6
    }
};

#include OATPP_CODEGEN_END(ApiController)
