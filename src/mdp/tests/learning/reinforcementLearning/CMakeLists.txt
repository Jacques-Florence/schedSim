#add_executable(reinforcedLearningTest reinforcedLearningTest.cpp)
#target_link_libraries(reinforcedLearningTest mdp utils doublefann glpk gtest gtest_main)
#add_test(reinforcedLearningTest reinforcedLearningTest)

add_executable(reinforcementPerformanceTest reinforcementPerformanceTest.cpp)
target_link_libraries(reinforcementPerformanceTest mdp utils doublefann glpk gtest gtest_main)

configure_file(configuration.conf ./ COPYONLY)
