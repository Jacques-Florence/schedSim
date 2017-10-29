target_sources(rlScheduler
	PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/envelopeDetector.cpp
	${CMAKE_CURRENT_LIST_DIR}/exponentialMaxTempEstimator.cpp
	${CMAKE_CURRENT_LIST_DIR}/squareMaxTempEstimator.cpp
	${CMAKE_CURRENT_LIST_DIR}/monomialMaxTempEstimator.cpp
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/maxTempEstimator.h
	)
install(FILES 
	${CMAKE_CURRENT_LIST_DIR}/maxTempEstimator.h
	DESTINATION include/rlScheduler/maxTempEstimator)
