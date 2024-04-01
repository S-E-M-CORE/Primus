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
        src/dto/database/AddressDTO.hpp
        src/dto/database/DepartmentDTO.hpp
        src/dto/database/EmailDTO.hpp
        src/dto/database/MemberDTO.hpp
        src/dto/database/MembershipDTO.hpp
        src/dto/database/PhoneNumberDTO.hpp
        src/dto/database/TrainingDTO.hpp
        src/dto/database/relations/DepartmentTrainingRelDTO.hpp
        src/dto/database/relations/MemberAddressRelDTO.hpp
        src/dto/database/relations/MemberEmailRelDTO.hpp
        src/dto/database/relations/MemberMembershipRelDTO.hpp
        src/dto/database/relations/MemberPhoneRelDTO.hpp
        src/dto/database/relations/MembershipDepartmentRelDTO.hpp
        src/dto/database/relations/MemberTrainingRelDTO.hpp
        src/service/MemberService.cpp
        src/service/MemberService.hpp
        "src/service/AddressService.cpp"
        "src/service/DepartmentService.cpp"
        "src/service/EmailService.cpp"
        "src/service/MembershipService.cpp"
        "src/service/PhoneNumberService.cpp"
        "src/service/TrainingService.cpp"
        "src/service/relations/MemberAddressRelService.cpp"
        "src/service/relations/MemberEmailRelService.cpp"
        "src/service/relations/MemberPhoneRelService.cpp"
        "src/service/relations/MembershipDepartmentRelService.cpp" "src/service/relations/MemberTrainingRelService.cpp" "src/service/relations/DepartmentTrainingRelService.cpp" "src/service/relations/MemberMembershipRelService.cpp")

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

add_definitions(
        ## define path to swagger-ui static resources folder
        -DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"

        ## SQLite database file
        -DDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/database.sqlite"

        ## SQLite database test file
        -DTESTDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/test-db.sqlite"

        ## Path to database migration scripts
        -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql"
)

if(CMAKE_SYSTEM_NAME MATCHES Linux)
    find_package(Threads REQUIRED)
    target_link_libraries(crud-lib INTERFACE Threads::Threads ${CMAKE_DL_LIBS})
endif()

target_include_directories(${project_name}-lib PUBLIC src)

## add executables

add_executable(${project_name}-exe src/App.cpp "src/service/AddressService.cpp" "src/service/DepartmentService.cpp" "src/service/EmailService.cpp" "src/service/MembershipService.cpp" "src/service/PhoneNumberService.cpp" "src/service/TrainingService.cpp" "src/service/relations/MemberAddressRelService.cpp" "src/service/relations/MemberEmailRelService.cpp" "src/service/relations/MemberPhoneRelService.cpp" "src/service/relations/MembershipDepartmentRelService.cpp" "src/service/relations/MemberTrainingRelService.cpp" "src/service/relations/DepartmentTrainingRelService.cpp" "src/service/relations/MemberMembershipRelService.cpp")

target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)

add_executable(${project_name}-test
        test/tests.cpp
        test/app/TestComponent.hpp
        test/app/MyApiTestClient.hpp
        "test/StaticControllerTest.cpp"
        test/StaticControllerTest.hpp
 "src/service/AddressService.cpp" "src/service/DepartmentService.cpp" "src/service/EmailService.cpp" "src/service/MembershipService.cpp" "src/service/PhoneNumberService.cpp" "src/service/TrainingService.cpp" "src/service/relations/MemberAddressRelService.cpp" "src/service/relations/MemberEmailRelService.cpp" "src/service/relations/MemberPhoneRelService.cpp" "src/service/relations/MembershipDepartmentRelService.cpp" "src/service/relations/MemberTrainingRelService.cpp" "src/service/relations/DepartmentTrainingRelService.cpp" "src/service/relations/MemberMembershipRelService.cpp")

target_link_libraries(${project_name}-test ${project_name}-lib)
add_dependencies(${project_name}-test ${project_name}-lib)

set_target_properties(${project_name}-lib ${project_name}-exe ${project_name}-test PROPERTIES
        CXX_STANDARD 11
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)

enable_testing()
add_test(project-tests ${project_name}-test)
