if(CMAKE_BUILD_TYPE STREQUAL "Testing")
    # Enable testing
    enable_testing()

    # Function to add a test executable
    function(add_test_executable name source)
        add_executable(${name} ${source})
        target_link_libraries(${name} cmocka ${CMAKE_DL_LIBS} evo_lib)
        target_include_directories(${name} PRIVATE ${CMAKE_SOURCE_DIR}/src)
        add_test(NAME ${name} COMMAND ${name})
    endfunction()

    # List of test names
    set(TEST_NAMES
        config_tests
        file_tests
        mutations_tests
        config_cli_tests
        config_mod_tests
        file_input_processing_tests
        file_mod_tests
        fn_1_tests
        fn_2_tests
        fn_3_tests
        fn_4_tests
        fn_5_tests
        fn_6_tests
        fn_7_tests
        fn_8_tests
        fn_9_tests
        fn_ampersand_tests
        fn_asterisk_tests
    )

    # List of test sources
    set(TEST_SOURCES
        "src/config/utils.unit.c"
        "src/file/utils.unit.c"
        "src/mutations/mod.unit.c"
        "src/config/cli.unit.c"
        "src/config/mod.unit.c"
        "src/file/input_processing.unit.c"
        "src/file/mod.unit.c"
        "src/mutations/functions/fn_1.unit.c"
        "src/mutations/functions/fn_2.unit.c"
        "src/mutations/functions/fn_3.unit.c"
        "src/mutations/functions/fn_4.unit.c"
        "src/mutations/functions/fn_5.unit.c"
        "src/mutations/functions/fn_6.unit.c"
        "src/mutations/functions/fn_7.unit.c"
        "src/mutations/functions/fn_8.unit.c"
        "src/mutations/functions/fn_9.unit.c"
        "src/mutations/functions/fn_ampersand.unit.c"
        "src/mutations/functions/fn_asterisk.unit.c"
    )

    # Loop through the test names and sources to add the test executables
    set(TEST_INDEX 0)
    foreach(TEST_NAME ${TEST_NAMES})
        list(GET TEST_SOURCES ${TEST_INDEX} TEST_SOURCE)
        add_test_executable(${TEST_NAME} ${TEST_SOURCE})
        math(EXPR TEST_INDEX "${TEST_INDEX} + 1")
    endforeach()

    # Add the test targets to the default build
    add_custom_target(tests DEPENDS ${TEST_NAMES})

    # Set coverage options for the test executables
    foreach(TEST_NAME ${TEST_NAMES})
        set_coverage_options(${TEST_NAME})
    endforeach()

    # Special compile and link options for specific tests
    target_compile_options(mutations_tests PRIVATE -fno-builtin)
    target_link_options(mutations_tests PRIVATE -Wl,--wrap=apply_mutation_up -Wl,--wrap=apply_mutation_down -Wl,--wrap=reverse_generations)

    target_compile_options(file_input_processing_tests PRIVATE -fno-builtin)
    target_link_options(file_input_processing_tests PRIVATE -Wl,--wrap=apply_mutations_to_chunk)

    target_compile_options(file_mod_tests PRIVATE -fno-builtin)
    target_link_options(file_mod_tests PRIVATE -Wl,--wrap=process_input_single_thread -Wl,--wrap=process_input_multi_thread)

    message(STATUS "Enabling debug/coverage build")

    # Include CTest module for coverage reporting
    include(CTest)

    # Set coverage options for the library
    set_coverage_options(evo_lib)

    # Set coverage options for the executable
    set_coverage_options(evo)
endif()
