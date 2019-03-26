file(GLOB HEADERS "include/surf/follow/*.hpp")

add_library( surf_follow
             follow_plugin.cpp
             follow_api.cpp
             follow_operations.cpp
             follow_evaluators.cpp
           )

target_link_libraries( surf_follow surf_chain surf_protocol surf_app )
target_include_directories( surf_follow
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   surf_follow

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
