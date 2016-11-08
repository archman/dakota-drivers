cmake_minimum_required(VERSION 3.5)

set (BOOST_ROOT "/opt/boost161")
set (BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include")
set (BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")
set (OPT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cpp")
set (EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

include_directories(
  ${BOOST_INCLUDE_DIRS}
  #${CMAKE_CURRENT_SOURCE_DIR}/../src
)

#link_directories(
#)

add_executable(flamedriver_oc
    ${OPT_SOURCE_DIR}/main.cpp
    ${OPT_SOURCE_DIR}/misc.cpp
    ${OPT_SOURCE_DIR}/parser.cpp
)

add_executable(test_parser
  ${OPT_SOURCE_DIR}/test_parser.cpp
  ${OPT_SOURCE_DIR}/parser.cpp
)

target_link_libraries(flamedriver_oc
  flame_core
)
