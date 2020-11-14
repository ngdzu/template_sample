

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
add_executable(nondependent_base nondependent_base.cpp)
add_executable(dependent_base dependent_base.cpp)
add_executable(compound_type compound_type.cpp)
add_executable(static_check static_check.cpp)


target_link_libraries(using PUBLIC tutorial_compiler_flags)
target_link_libraries(nondependent_base PUBLIC tutorial_compiler_flags)
target_link_libraries(dependent_base PUBLIC tutorial_compiler_flags)
target_link_libraries(compound_type PUBLIC tutorial_compiler_flags)
target_link_libraries(static_check PUBLIC tutorial_compiler_flags)
