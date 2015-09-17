add_library(template_header header.c)
target_link_libraries(template_header html_reader)

add_library(template_footer footer.c)
target_link_libraries(template_header html_reader)
