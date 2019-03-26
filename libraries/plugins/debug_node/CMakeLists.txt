file(GLOB HEADERS "include/surf/plugins/debug_node/*.hpp")

add_library( surf_debug_node
             ${HEADERS}
             debug_node_plugin.cpp
             debug_node_api.cpp
           )

target_link_libraries( surf_debug_node surf_app surf_chain surf_protocol fc )
target_include_directories( surf_debug_node
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS surf_debug_node
         RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib
       )
INSTALL( FILES ${HEADERS} DESTINATION "include/surf/plugins/debug_node" )
