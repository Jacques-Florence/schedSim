target_sources(mdp
	PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/rlTestDimensions.cpp
	${CMAKE_CURRENT_LIST_DIR}/rlTestDomainModel.cpp
	${CMAKE_CURRENT_LIST_DIR}/testRL.cpp
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/rlTestActions.h
	${CMAKE_CURRENT_LIST_DIR}/rlTestDimensions.h
	${CMAKE_CURRENT_LIST_DIR}/rlTestDomainModel.h
	)


install(FILES ${CMAKE_CURRENT_LIST_DIR}/configuration.conf DESTINATION mdp/tests)
