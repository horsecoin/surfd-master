file(GLOB HEADERS "include/surf/account_history/*.hpp")

add_library( surf_account_history
             account_history_plugin.cpp
           )

target_link_libraries( surf_account_history surf_chain surf_protocol surf_app )
target_include_directories( surf_account_history
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   surf_account_history

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
