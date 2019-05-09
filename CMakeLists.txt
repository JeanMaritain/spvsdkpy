cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 11)
set(PYBIND11_CPP_STANDARD -std=c++11)

#set(CMAKE_VERBOSE_MAKEFILE ON)

project(spvsdkpy)

add_subdirectory(pybind11) # or find_package(pybind11 REQUIRED)
option(BUILD_SHARED_LIBS "SPV build shared library." OFF)
add_subdirectory(Elastos.ELA.SPV.Cpp)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/Elastos.ELA.SPV.Cpp/Interface
)

file(GLOB_RECURSE SPVSDKPY_SOURCE_FILES
        "interface/*.cpp")
pybind11_add_module(spvsdkpy SHARED ${SPVSDKPY_SOURCE_FILES})
target_link_libraries(spvsdkpy PRIVATE spvsdk)
add_dependencies(spvsdkpy spvsdk)

add_subdirectory(test)
