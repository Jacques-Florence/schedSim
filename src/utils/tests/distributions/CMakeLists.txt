
add_executable(bernoulliTest bernoulliTest.cpp)
target_link_libraries(bernoulliTest utils gtest gtest_main)
add_test(bernoulliTest bernoulliTest)




