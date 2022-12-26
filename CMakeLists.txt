cmake_minimum_required(VERSION 3.10)

project(MyRSA)

set(DEP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)

file(GLOB sources src/*.cpp)
file(GLOB includes src/*.h)

option(BUILD_STATIC TRUE)

if(NOT BUILD_STATIC)
message("Building dll")
add_library(MyRSA SHARED ${sources})
else()
message("Building static library")
add_library(MyRSA STATIC ${sources})
endif()

add_library(MyRSA::MyRSA ALIAS MyRSA)

target_include_directories(MyRSA PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)
target_include_directories(MyRSA PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/dependencies>)
target_include_directories(MyRSA PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>)

#PACKAGING#
include(GNUInstallDirs)


install(TARGETS MyRSA
        EXPORT MyRSA-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY ${MyRSA_Includes} DESTINATION include)

install(
    EXPORT MyRSA-targets
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MyRSA
    FILE MyRSA-targets.cmake
    NAMESPACE MyRSA::
)

include(CMakePackageConfigHelpers)

configure_package_config_file( 
  cmake/MyRSAConfig.cmake.in 
  "MyRSAConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MyRSA
  )

write_basic_package_version_file(MyRSAConfigVersion.cmake
VERSION 1.0
COMPATIBILITY AnyNewerVersion)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/MyRSAConfig.cmake
            ${CMAKE_CURRENT_BINARY_DIR}/MyRSAConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MyRSA
)

export(
    EXPORT MyRSA-targets
    NAMESPACE MyRSA::
    FILE ${CMAKE_CURRENT_BINARY_DIR}/MyRSA-targets.cmake
    )

