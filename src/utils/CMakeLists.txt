add_library(utils
	configuration.cpp
	counter.cpp
	countingWheel.cpp
	log.cpp
	math.cpp
	randomGenerator.cpp
	record.cpp
	stringUtils.cpp
	programTime.cpp
	)


install(TARGETS utils DESTINATION bin)
install(
	FILES
	configuration.h
	counter.h
	countingWheel.h
	log.h
	math.h
	randomGenerator.h
	record.h
	stringUtils.h
	programTime.h
	DESTINATION include/utils)

add_subdirectory(tests)
add_subdirectory(distributions)
#add_subdirectory(xml)
