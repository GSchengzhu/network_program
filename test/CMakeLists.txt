cmake_minimum_required(VERSION 3.10.2)

# add_executable(thread_pool_test thread_pool_test.cpp ${PROJECT_SOURCE_DIR}/../server_/thread_pool.h ${PROJECT_SOURCE_DIR}/../server_/thread_pool.cpp)

set(THREAD_POOL_SRC)
list(APPEND THREAD_POOL_SRC ./thread_pool_test.cpp)
list(APPEND THREAD_POOL_SRC ./../server_/thread_pool.h)
list(APPEND THREAD_POOL_SRC ./../server_/thread_pool.cpp)

# add_executable(thread_pool_test ${THREAD_POOL_SRC})
# target_link_libraries(thread_pool_test pthread)

set(MESSAGE_SRC)
list(APPEND MESSAGE_SRC ./message_test.cpp)
list(APPEND MESSAGE_SRC ../common/message.cpp)
list(APPEND MESSAGE_SRC ../common/message.h)
add_executable(message_test ${MESSAGE_SRC})