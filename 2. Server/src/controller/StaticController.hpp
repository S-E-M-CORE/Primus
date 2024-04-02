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
    ENDPOINT("GET", "/", root) {
        auto html = readFile(WEB_CONTENT_DIRECTORY "/index.html");
        auto response = createResponse(Status::CODE_200, html);
        response->putHeader(Header::CONTENT_TYPE, "text/html");
        return response;
    }

    // Endpunkt für eine andere HTML-Datei
    ENDPOINT("GET", "/other-page", otherPage) {
        auto html = readFile(WEB_CONTENT_DIRECTORY "/other-page.html");
        auto response = createResponse(Status::CODE_200, html);
        response->putHeader(Header::CONTENT_TYPE, "text/html");
        return response;
    }
};

#include OATPP_CODEGEN_END(ApiController)
