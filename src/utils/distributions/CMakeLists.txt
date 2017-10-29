target_sources(utils
	PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/diracOneDistribution.cpp
	${CMAKE_CURRENT_LIST_DIR}/uniformDistribution.cpp
	${CMAKE_CURRENT_LIST_DIR}/bernoulli.cpp
	PUBLIC
	)



install(
	FILES
	${CMAKE_CURRENT_LIST_DIR}/boundedRandomDistribution.h
	${CMAKE_CURRENT_LIST_DIR}/diracOneDistribution.h
	${CMAKE_CURRENT_LIST_DIR}/uniformDistribution.h
	DESTINATION include/utils/distributions
	)
