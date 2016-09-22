ADD_EXECUTABLE(net_engine_server main.cpp)
find_package(Threads)
TARGET_LINK_LIBRARIES(net_engine_server tcpserver ${CMAKE_THREAD_LIBS_INIT})
