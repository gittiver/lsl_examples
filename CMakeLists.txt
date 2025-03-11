cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    lsl_examples
    VERSION 0.1.0
    DESCRIPTION "some examples for using lsl (LabStreamLayer)"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)
include(cmake/CPM.cmake)

CPMAddPackage(lsl
        VERSION 1.16.2
        GITHUB_REPOSITORY sccn/liblsl
)


# ---- Declare library ----

#add_library(
#    lsl_examples_lib OBJECT
#    src/lib.cpp
#)

#target_include_directories(
#    lsl_examples_lib ${warning_guard}
#    PUBLIC
#    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
#)

#target_compile_features(lsl_examples_lib PUBLIC cxx_std_17)

# ---- Declare executable ----

add_executable(lsl_ostream src/ostream.cpp)

target_compile_features(lsl_ostream PRIVATE cxx_std_17)
target_include_directories(lsl_ostream PRIVATE ${liblsl_SOURCE_DIR}/include)
target_link_libraries(lsl_ostream PRIVATE lsl)

add_executable(lsl_markers src/markers.cpp)
target_compile_features(lsl_markers PRIVATE cxx_std_17)
target_include_directories(lsl_markers PRIVATE ${liblsl_SOURCE_DIR}/include)
target_link_libraries(lsl_markers PRIVATE lsl)

#
add_executable(lsl_istream src/istream.cpp)
target_compile_features(lsl_istream PRIVATE cxx_std_17)
target_include_directories(lsl_istream PRIVATE ${liblsl_SOURCE_DIR}/include)
target_link_libraries(lsl_istream PRIVATE lsl)

#
add_executable(lsl_pipe src/pipe.cpp)
target_compile_features(lsl_pipe PRIVATE cxx_std_17)
target_include_directories(lsl_pipe PRIVATE ${liblsl_SOURCE_DIR}/include)
target_link_libraries(lsl_pipe PRIVATE lsl)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  install(
    TARGETS lsl_istream lsl_ostream lsl_pipe
    RUNTIME COMPONENT lsl_examples_Runtime
  )
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT lsl_examples_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of lsl_examples"
  )
endif()

include(cmake/dev-mode.cmake)
