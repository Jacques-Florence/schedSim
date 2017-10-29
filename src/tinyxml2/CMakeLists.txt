add_library(tinyxml2
	tinyxml2.cpp
	)

install(TARGETS tinyxml2 DESTINATION bin)
install(FILES tinyxml2.h DESTINATION include/tinyxml2)









