#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MyRSA::MyRSA" for configuration "Debug"
set_property(TARGET MyRSA::MyRSA APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MyRSA::MyRSA PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libMyRSA.a"
  )

list(APPEND _cmake_import_check_targets MyRSA::MyRSA )
list(APPEND _cmake_import_check_files_for_MyRSA::MyRSA "${_IMPORT_PREFIX}/lib/libMyRSA.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
