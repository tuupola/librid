add_executable(test_runner
    unit.c
    test_message.c
    test_basic_id.c
    test_operator_id.c
    test_location.c
    test_self_id.c
    test_system.c
    test_message_pack.c
    test_auth_page.c
    test_auth.c
    test_transport.c
)

target_include_directories(test_runner PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(test_runner rid)

add_test(NAME unit_tests COMMAND test_runner)
