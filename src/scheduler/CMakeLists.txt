add_library(scheduler
	process.cpp
	processor.cpp
	queue.cpp
	schedulerConfiguration.cpp
	schedulingSimulator.cpp
	system.cpp
	taskScheduler.cpp
	taskSetGenerator.cpp
	time.cpp
	xmlTaskSet.cpp
	specialMailbox.cpp
	)

add_subdirectory(governor)
add_subdirectory(discipline)
add_subdirectory(temperatureModel)

install(FILES
	schedulerConfiguration.h
	schedulingSimulator.h
	taskSetGenerator.h
	specialMailbox.h
	DESTINATION include/scheduler)

add_subdirectory(events)
add_subdirectory(tests)




