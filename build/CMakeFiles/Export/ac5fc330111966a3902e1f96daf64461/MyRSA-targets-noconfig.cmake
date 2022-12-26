#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MyRSA::MyRSA" for configuration ""
set_property(TARGET MyRSA::MyRSA APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(MyRSA::MyRSA PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libMyRSA.a"
  )

list(APPEND _cmake_import_check_targets MyRSA::MyRSA )
list(APPEND _cmake_import_check_files_for_MyRSA::MyRSA "${_IMPORT_PREFIX}/lib/libMyRSA.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
