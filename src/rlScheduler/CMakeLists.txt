add_library(rlScheduler
	rlDiscipline.cpp
	rlDisciplineBuilder.cpp
	rlDisciplineBuilderHelper.cpp
	actions.cpp
	configuration.cpp
	domainModel.cpp
	)
include(stateDimensions/CMakeLists.txt)
include(maxTempEstimator/CMakeLists.txt)
install(FILES
	rlDiscipline.h
	configuration.h
	DESTINATION include/rlScheduler)
add_subdirectory(tests)
