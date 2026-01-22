add_executable(example_basic_id basic_id/example_basic_id.c)
target_link_libraries(example_basic_id rid)

add_executable(example_version version/example_version.c)
target_link_libraries(example_version rid)

add_executable(example_json json/example_json.c)
target_link_libraries(example_json rid)

add_executable(example_location location/example_location.c)
target_link_libraries(example_location rid)

add_executable(example_message message/example_message.c)
target_link_libraries(example_message rid)

add_executable(example_message_pack message_pack/example_message_pack.c)
target_link_libraries(example_message_pack rid)

add_executable(example_operator_id operator_id/example_operator_id.c)
target_link_libraries(example_operator_id rid)

add_executable(example_self_id self_id/example_self_id.c)
target_link_libraries(example_self_id rid)

add_executable(example_system system/example_system.c)
target_link_libraries(example_system rid)

add_executable(example_validate validate/example_validate.c)
target_link_libraries(example_validate rid)

add_executable(rid_cli cli/example_cli.c)
target_link_libraries(rid_cli rid)
set_target_properties(rid_cli PROPERTIES OUTPUT_NAME rid)

add_executable(example_auth_page auth_page/example_auth_page.c)
target_link_libraries(example_auth_page rid)

find_package(PkgConfig)
if(PkgConfig_FOUND)
    pkg_check_modules(SODIUM libsodium)
    if(SODIUM_FOUND)
        add_executable(example_auth auth/example_auth.c)
        target_link_libraries(example_auth rid ${SODIUM_LIBRARIES})
        target_include_directories(example_auth PRIVATE ${SODIUM_INCLUDE_DIRS})
    endif()
endif()
