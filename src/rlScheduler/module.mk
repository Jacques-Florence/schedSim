LIBNAME := rlScheduler
local_lib := $(addprefix $(subdirectory)/,lib$(LIBNAME).a) 

local_src := rlDiscipline.cpp
local_src += rlSchedulerConfiguration.cpp
local_src += rlSchedulerDomainModel.cpp
local_src += rlSchedulerActions.cpp
local_src += rlSchedulerDimensions.cpp
local_src += rlSchedulerTimeDimension.cpp

local_src += maxTempEstimator/envelopeDetector.cpp
local_src += maxTempEstimator/exponentialMaxTempEstimator.cpp
local_src += maxTempEstimator/squareMaxTempEstimator.cpp
local_src += maxTempEstimator/monomialMaxTempEstimator.cpp

local_objs := $(subst .cpp,.o,$(local_src))

sources   += $(addprefix $(subdirectory)/,$(local_src))
libraries += $(local_lib)

local_dir := $(subdirectory)
LDFLAGS += -L./$(local_dir)

$(local_lib): $(addprefix $(subdirectory)/,$(local_objs))
	ar rv $@ $^








