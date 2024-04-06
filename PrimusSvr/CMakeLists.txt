cmake_minimum_required(VERSION 3.1)

project(PrimusSvr)

set(SOURCES
    src/controller/MemberController.hpp
    src/controller/StaticController.hpp
    src/database/DatabaseClient.hpp
    src/database/DatabaseComponent.hpp
    src/dto/BooleanDto.hpp
    src/dto/Int32Dto.hpp
    src/dto/PageDto.hpp
    src/dto/StatusDto.hpp
    src/swagger-ui/SwaggerComponent.hpp
    src/AppComponent.hpp
    src/App.cpp
)
# Create a library target
add_library(PrimusSvrLibrary ${SOURCES})

# Find required packages
find_package(oatpp 1.3.0 REQUIRED)
find_package(oatpp-swagger 1.3.0 REQUIRED)
find_package(oatpp-sqlite 1.3.0 REQUIRED)

target_link_libraries(PrimusSvrLibrary
    oatpp::oatpp
    oatpp::oatpp-swagger
    oatpp::oatpp-sqlite
    )

target_compile_definitions(PrimusSvrLibrary
    PUBLIC OATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"
    PUBLIC DATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/bin/database/database.sqlite"
    PUBLIC DATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/bin/sql"
    PUBLIC WEB_CONTENT_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}/bin/web"
)

if(CMAKE_SYSTEM_NAME MATCHES Linux)
    find_package(Threads REQUIRED)
    target_link_libraries(crud-lib INTERFACE Threads::Threads ${CMAKE_DL_LIBS})
endif()

target_include_directories(PrimusSvrLibrary PUBLIC src)

# Create an executable target
add_executable(PrimusSvr src/App.cpp)

# Erstelle die Verzeichnisse
file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/database/")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/sql")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/web")

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets/sql/" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/bin/sql/")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets/web/" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/bin/web/")

target_compile_definitions(PrimusSvr
    PUBLIC OATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"
    PUBLIC DATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/bin/database/database.sqlite"
    PUBLIC DATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/bin/sql"
    PUBLIC WEB_CONTENT_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}/bin/web"
)

target_link_libraries(PrimusSvr PrimusSvrLibrary)
add_dependencies(PrimusSvr PrimusSvrLibrary)

# Set output directory for the executable
set_target_properties(PrimusSvr PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

set_target_properties(PrimusSvr PrimusSvrLibrary PROPERTIES
        CXX_STANDARD 11
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)

# Set output directory for the executable
set_target_properties(PrimusSvr PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

# Set output directory for the library
set_target_properties(PrimusSvrLibrary PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

# Setze das Ausgabeverzeichnis für alle Konfigurationen (Debug, Release, etc.)
set_property(TARGET PrimusSvr PROPERTY
    VS_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

# Setze das Ausgabeverzeichnis für die Bibliothek
set_property(TARGET PrimusSvrLibrary PROPERTY
    VS_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)