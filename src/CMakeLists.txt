find_package(Threads)

add_definitions(-Wall -g -pedantic -ggdb -lpthread -lcppdb_sqlite3)

add_executable(SharedWifi main.c)

target_link_libraries(SharedWifi mongoose)

target_link_libraries(SharedWifi sqlite3)

target_link_libraries (SharedWifi ${CMAKE_THREAD_LIBS_INIT})
