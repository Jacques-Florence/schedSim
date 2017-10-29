target_sources(scheduler
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/conservativeGovernor.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/maxGovernor.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/minGovernor.cpp
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/freqGovernor.h
	${CMAKE_CURRENT_SOURCE_DIR}/conservativeGovernor.h
	${CMAKE_CURRENT_SOURCE_DIR}/maxGovernor.h
	${CMAKE_CURRENT_SOURCE_DIR}/minGovernor.h
	)
install(FILES
	${CMAKE_CURRENT_SOURCE_DIR}/freqGovernor.h
	DESTINATION include/scheduler/governor)
