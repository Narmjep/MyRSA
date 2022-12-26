# BUILD

## CMake Project
This project can be built directly using ```cmake . && make```.

## CMake Package
It can also be installed by using ```make install``` instead of ```make```
Additionally, the package can also be added directly to the build tree by using
```cmake
find_package(MyRSA PATHS path/to/MyRSA/)
#Include headers
get_target_property(MyRSA_INCLUDE_DIRS MyRSA::MyRSA INTERFACE_INCLUDE_DIRECTORIES)
message("Include dirs: "${MyRSA_INCLUDE_DIRS})
target_include_directories(MyProject PRIVATE ${MyRSA_INCLUDE_DIRS})
#Link Library
target_link_libraries(Main MyRSA::MyRSA)
```

When building with CMake, the option "BUILD_STATIC can be set to FALSE by passing the argument: ```cmake -DBUILD_STATIC=FALSE .```
