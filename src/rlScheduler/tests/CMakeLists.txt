add_executable(rlDisciplineBuilderHelper rlDisciplineBuilderHelperTest.cpp)
target_link_libraries(rlDisciplineBuilderHelper rlScheduler scheduler mdp glpk doublefann utils gtest_main)
add_test(rlDisciplineBuilderHelper rlDisciplineBuilderHelper)







