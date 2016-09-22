ADD_EXECUTABLE(net_engine main.cpp)
SET(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")
find_package(Threads)
TARGET_LINK_LIBRARIES(net_engine tcpserver ${CMAKE_THREAD_LIBS_INIT})
