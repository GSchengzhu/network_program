cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_FLAGS "-g") 
add_executable(thread_pool_test thread_pool_test.cpp ${PROJECT_SOURCE_DIR}/../server_/thread_pool.h ${PROJECT_SOURCE_DIR}/../server_/thread_pool.cpp)
target_link_libraries(thread_pool_test -lpthread)