# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(lsl_examplesTests LANGUAGES CXX)

# ---- Tests ----

add_executable(lsl_examples_test source/lsl_examples_test.cpp)
target_link_libraries(lsl_examples_test PRIVATE lsl)
target_compile_features(lsl_examples_test PRIVATE cxx_std_17)

add_test(NAME lsl_examples_test COMMAND lsl_examples_test)

# ---- End-of-file commands ----

add_folders(Test)
