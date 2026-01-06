if(ESP_PLATFORM)
    idf_component_register(
        SRCS "src/basic_id.c"
             "src/location.c"
             "src/message.c"
             "src/system.c"
             "src/message_pack.c"
             "src/header.c"
             "src/auth.c"
             "src/auth_page.c"
             "src/operator_id.c"
             "src/self_id.c"
        INCLUDE_DIRS "include"
    )
else()
    cmake_minimum_required(VERSION 3.10)
    project(librid VERSION 0.0.0 LANGUAGES C)

    set(CMAKE_C_STANDARD 99)
    set(CMAKE_C_STANDARD_REQUIRED ON)

    option(RID_BUILD_EXAMPLES "Build example programs" OFF)
    option(RID_BUILD_TESTS "Build unit tests" OFF)

    add_library(rid
        src/basic_id.c
        src/location.c
        src/message.c
        src/system.c
        src/message_pack.c
        src/header.c
        src/auth.c
        src/auth_page.c
        src/operator_id.c
        src/self_id.c
    )

    target_include_directories(rid PUBLIC include)

    if(RID_BUILD_EXAMPLES)
        add_subdirectory(examples)
    endif()

    if(RID_BUILD_TESTS)
        enable_testing()
        add_subdirectory(tests)
    endif()
endif()
