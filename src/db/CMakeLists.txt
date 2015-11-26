add_library(database database.c)

target_link_libraries(database sqlite3)
