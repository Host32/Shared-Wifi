find_package(Threads)

add_definitions(-Wall -g -pedantic -ggdb -lpthread -lcppdb_sqlite3)

add_executable(SharedWifi main.c)

add_library(routes routes.c)

add_library(resources resources.c)

target_link_libraries(SharedWifi mongoose)

target_link_libraries(SharedWifi sqlite3)

target_link_libraries (SharedWifi ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(SharedWifi routes)

target_link_libraries(SharedWifi resources)

set(CMAKE_C_FLAGS "-std=c99")

