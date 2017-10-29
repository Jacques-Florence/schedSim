add_library(mdp
	actionDimension.cpp
	actionSpace.cpp
	actionSpaceBuilder.cpp
	builder.cpp
	complexAction.cpp
	mdpConfiguration.cpp
	mdpModel.cpp
	policy.cpp
	rewards.cpp
	stateSpace.cpp
	stateSpaceBuilder.cpp
	stateSpaceDimension.cpp
	transitionMatrix.cpp)
install(FILES
	mdpModel.h
	mdpConfiguration.h
	actionSpaceBuilder.h
	actionDimension.h
	complexAction.h
	stateSpaceBuilder.h
	stateSpaceDimension.h
	DESTINATION include/mdp)

add_subdirectory(learning)
add_subdirectory(tests)
