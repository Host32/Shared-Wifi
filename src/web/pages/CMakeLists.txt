add_library(page_index index.c)
target_link_libraries(page_index html_reader)

add_library(page_teste teste.c)
target_link_libraries(page_teste html_reader)
