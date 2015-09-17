find_package(Threads)

add_definitions(-Wall -g -pedantic -ggdb -lpthread -lcppdb_sqlite3)

add_subdirectory(web)

add_executable(SharedWifi main.c)

target_link_libraries(SharedWifi mongoose)

target_link_libraries(SharedWifi sqlite3)

target_link_libraries (SharedWifi ${CMAKE_THREAD_LIBS_INIT})

# Template
target_link_libraries(SharedWifi template_header)
target_link_libraries(SharedWifi template_footer)

# Web pages
target_link_libraries(SharedWifi page_index)
target_link_libraries(SharedWifi page_teste)

# Web resources
add_custom_command(TARGET SharedWifi POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/src/web/html $<TARGET_FILE_DIR:SharedWifi>/web/html)

