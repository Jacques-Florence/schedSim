target_sources(scheduler
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/coreEvents.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/startProc.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/newProcess.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/newInteractiveProcess.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/newJob.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/missedDeadline.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ready.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/waiting.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/terminates.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/stopSimulation.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/event.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eventList.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/timeoutEvent.cpp
	)

install(FILES
	event.h
	DESTINATION include/scheduler
)




