add_library(mongoose mongoose.c)
add_library(sqlite3 sqlite3.h sqlite3.c)

target_link_libraries(sqlite3 ${CMAKE_DL_LIBS})
