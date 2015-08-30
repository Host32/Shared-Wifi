add_executable(SharedWifi main.c)

target_link_libraries(SharedWifi mongoose)

target_link_libraries(SharedWifi sqlite3)