cmake_minimum_required(VERSION 3.1)

set(project_name PrimusServer)

project(${project_name})

set(CMAKE_CXX_STANDARD 11)

add_library(${project_name}-lib
        src/database/DatabaseComponent.hpp
        src/swagger-ui/SwaggerComponent.hpp
        src/AppComponent.hpp
        src/controller/StaticController.hpp
        src/controller/MemberController.hpp
        src/database/DatabaseClient.hpp
        src/service/MemberService.cpp
        src/service/MemberService.hpp
        src/dto/DatabaseDtos.hpp
)

## link libs

find_package(oatpp          1.3.0 REQUIRED)
find_package(oatpp-swagger  1.3.0 REQUIRED)
find_package(oatpp-sqlite   1.3.0 REQUIRED)

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-test
        PUBLIC oatpp::oatpp-swagger
        PUBLIC oatpp::oatpp-sqlite
)

# Create directory for database file
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/database)

# Create directory for database content
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/database/db_content)

# Create directory for profile images of members
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/database/db_content/profile_images)

# Create directory for profile images of members
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/web/)

add_definitions(
        ## define path to swagger-ui static resources folder
        -DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"

        ## SQLite database file
        -DDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/database/database.sqlite"

        ## SQLite database test file
        -DTESTDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/database/test-db.sqlite"

        ## Path to database migration scripts
        -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql"

        ## Directory for additional database contents
        -DDB_CONTENT_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}/database/db_content"

        ## Special folder for profile images
        -DPROFILE_IMAGES_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}/database/db_content/profile_images"

        ## Folder for html sites that may be requested
        -DWEB_CONTENT_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}/web"
)

if(CMAKE_SYSTEM_NAME MATCHES Linux)
    find_package(Threads REQUIRED)
    target_link_libraries(crud-lib INTERFACE Threads::Threads ${CMAKE_DL_LIBS})
endif()

target_include_directories(${project_name}-lib PUBLIC src)

## add executables

add_executable(${project_name}-exe src/App.cpp


)

target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)

add_executable(${project_name}-test
        test/tests.cpp
        test/app/TestComponent.hpp
        test/app/MyApiTestClient.hpp
        "test/StaticControllerTest.cpp"
        test/StaticControllerTest.hpp
)

target_link_libraries(${project_name}-test ${project_name}-lib)
add_dependencies(${project_name}-test ${project_name}-lib)

set_target_properties(${project_name}-lib ${project_name}-exe ${project_name}-test PROPERTIES
        CXX_STANDARD 11
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)

enable_testing()
add_test(project-tests ${project_name}-test)
