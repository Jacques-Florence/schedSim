add_library(mdpGovernor
	mdpGovernor.cpp
	mdpGovernorConfiguration.cpp
	schedulerActions.cpp
	schedulerDimensions.cpp
	schedulerDomainModel.cpp)
install(FILES mdpGovernor.h mdpGovernorConfiguration.h DESTINATION include/mdpGovernor)
