

cmake_minimum_required(VERSION 3.15.4)

# set the project name and version
project(Tutorial VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)


# create a library with custom configuration. 
# then we can link to this library to have that configuration in the targets
add_library(tutorial_compiler_flags INTERFACE)
target_compile_features(tutorial_compiler_flags INTERFACE cxx_std_17)
target_include_directories(tutorial_compiler_flags 
    INTERFACE "${PROJECT_SOURCE_DIR}/RxCpp-master/Rx/v2/src"
)

# configure_file(TutorialConfig.h.in TutorialConfig.h)

add_executable(using using.cpp)


target_link_libraries(using PUBLIC tutorial_compiler_flags)
