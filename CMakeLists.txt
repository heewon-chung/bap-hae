cmake_minimum_required (VERSION 3.6)
project (BAP-HAE)

set (CMAKE_CXX_STANDARD 11)
set (SOURCE_FILES src/bapTools.cpp src/timeUtils.cpp src/crt.cpp src/hae.cpp src/matching.cpp)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Configuration Profile
set (CMAKE_CXX_FLAGS_PROFILE "${CMAKE_CXX_FLAGS} -pg")
set (CMAKE_EXE_LINKER_FLAGS_PROFILE "${CMAKE_EXE_LINKER_FLAGS} -pg")
set (OpenMP_CXX_FLAGS "-fopenmp")

# Enable OpenMP if available
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

include_directories(include)
include_directories(lib)

add_subdirectory(lib)

add_library(BAPHAE ${SOURCE_FILES})
target_link_libraries(BAPHAE NTL GMP GF2X -lm -O2)

add_executable(test_HAE test/haeTest.cpp)
target_link_libraries(test_HAE BAPHAE -pthread)
add_executable(test_Matching test/matchingTest.cpp)
target_link_libraries(test_Matching BAPHAE -pthread)