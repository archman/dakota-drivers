cmake_minimum_required(VERSION 3.0)

# set BOOST lib path, if already has, comment out the following three lines
#set (Boost_ROOT "/opt/boost161")
#set (Boost_INCLUDE_DIRS "${Boost_ROOT}/include")
#set (Boost_LIBRARY_DIRS "${Boost_ROOT}/lib")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")
set (OPT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cpp")
set (EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

# if needed, set FLAME_SRC and FLAME_LIB path
#set (FLAME_SRC "")
#set (FLAME_LIB "")

include_directories(
  ${Boost_INCLUDE_DIRS}
  # uncomment out the following line if FLAME_SRC is defined
  #${FLAME_SRC}
)

# uncomment out the following three lines if FLAME_LIB is defined
#link_directories(
#    ${FLAME_LIB}
#)

add_executable(flamedriver_oc
    ${OPT_SOURCE_DIR}/main.cpp
    ${OPT_SOURCE_DIR}/misc.cpp
    ${OPT_SOURCE_DIR}/parser.cpp
)

target_link_libraries(flamedriver_oc
  flame_core
)

install(TARGETS flamedriver_oc 
    DESTINATION /usr/local/bin)
