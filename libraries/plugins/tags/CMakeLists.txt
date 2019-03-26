file(GLOB HEADERS "include/surf/tags/*.hpp")

add_library( surf_tags
             tags_plugin.cpp )

target_link_libraries( surf_tags surf_chain surf_protocol surf_app )
target_include_directories( surf_tags
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
        surf_tags

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
