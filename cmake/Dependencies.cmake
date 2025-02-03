# Find pthreads
find_package(Threads REQUIRED)

# Find cmocka (only if building tests)
if(CMAKE_BUILD_TYPE STREQUAL "Testing")
    find_package(cmocka REQUIRED)

    if(NOT cmocka_FOUND)
        message(FATAL_ERROR "cmocka not found. Please install it manually.")
    endif()
endif()
