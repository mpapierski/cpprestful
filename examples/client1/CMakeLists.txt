CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (client1)

ADD_EXECUTABLE (client
	main.cpp)

TARGET_LINK_LIBRARIES (client
	cpprestful)
