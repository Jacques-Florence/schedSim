add_executable(stringUtilsTest stringUtilsTest.cpp)
target_link_libraries(stringUtilsTest utils gtest gtest_main)
add_test(stringUtilsTest stringUtilsTest)

add_executable(mathTest mathTest.cpp)
target_link_libraries(mathTest utils gtest gtest_main)
add_test(mathTest mathTest)

file(COPY configurationTest.conf DESTINATION ./)
add_executable(configurationTest configurationTest.cpp)
target_link_libraries(configurationTest utils gtest gtest_main)
add_test(configurationTest configurationTest)


add_executable(countingWheelTest countingWheelTest.cpp)
target_link_libraries(countingWheelTest utils gtest gtest_main)
add_test(countingWheelTest countingWheelTest)

add_executable(counterTest counterTest.cpp)
target_link_libraries(counterTest utils gtest gtest_main)
add_test(counterTest counterTest)



add_subdirectory(distributions)



















