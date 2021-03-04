set(src main.cpp
        MatrixTests.cpp
        VectorTests.cpp
        BuffetTests.cpp
        SubstitutionTests.cpp
        CholeskyTests.cpp)

add_executable(tests ${src})
target_link_libraries(tests gtest gtest_main pthread)

add_test(UnitTests tests)
