project(server)

set(SERVER_SRC)

list(APPEND SERVER_SRC ./main.cpp)
list(APPEND SERVER_SRC ./buffer.cpp)
list(APPEND SERVER_SRC ./buffer.h)
list(APPEND SERVER_SRC ./connection.cpp)
list(APPEND SERVER_SRC ./connection.h)
list(APPEND SERVER_SRC ./thread_pool.cpp)
list(APPEND SERVER_SRC ./thread_pool.h)

add_executable(server ${SERVER_SRC})