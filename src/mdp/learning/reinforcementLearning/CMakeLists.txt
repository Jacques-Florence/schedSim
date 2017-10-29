
target_sources(mdp
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/reinforcedLearning.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/actionValuesRecord.cpp
	)

add_subdirectory(rlBackupAlgo)
add_subdirectory(actionValuesFunction)
add_subdirectory(actionSelection)

