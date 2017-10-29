target_sources(mdp
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/epsilonGreedy.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gibbsActionSelection.cpp
	#${CMAKE_CURRENT_SOURCE_DIR}/fromFileActionSelection.cpp
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/actionSelectionStrategy.h
	)
