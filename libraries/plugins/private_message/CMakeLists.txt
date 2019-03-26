file(GLOB HEADERS "include/surf/private_message/*.hpp")

add_library( surf_private_message
             private_message_plugin.cpp
           )

target_link_libraries( surf_private_message surf_chain surf_protocol surf_app )
target_include_directories( surf_private_message
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   surf_private_message

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
