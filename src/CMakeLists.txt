find_package(Threads)

add_definitions(-Wall -g -pedantic -ggdb -std=c99 -pthread -DSQLITE_THREADSAFE=0 -ldl)

add_subdirectory(db)

add_subdirectory(network)

add_executable(SharedWifi main.c)

add_library(routes routes.c)

add_library(resources resources.c)

add_library(post_request post_request.c)

target_link_libraries(SharedWifi mongoose)

target_link_libraries(SharedWifi sqlite3)

target_link_libraries(SharedWifi ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(SharedWifi routes)

target_link_libraries(SharedWifi resources)

target_link_libraries(SharedWifi iptables)

target_link_libraries(SharedWifi ap)

target_link_libraries(SharedWifi dhcp)

target_link_libraries(SharedWifi post_request)

set(CMAKE_C_FLAGS "-std=c99")

