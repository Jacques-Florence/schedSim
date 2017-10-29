
add_executable(processTest processTest.cpp)
target_link_libraries(processTest scheduler utils gtest gtest_main)
add_test(processTest processTest)

add_executable(xmlTaskSetTest xmlTaskSetTest.cpp)
target_link_libraries(xmlTaskSetTest scheduler utils tinyxml2 gtest gtest_main)
add_test(xmlTaskSetTest xmlTaskSetTest)
configure_file(taskset.xml ./ COPYONLY)




