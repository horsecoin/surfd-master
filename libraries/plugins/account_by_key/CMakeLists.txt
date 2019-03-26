file(GLOB HEADERS "include/surf/account_by_key/*.hpp")

add_library( surf_account_by_key
             account_by_key_plugin.cpp
             account_by_key_api.cpp
           )

target_link_libraries( surf_account_by_key surf_chain surf_protocol surf_app )
target_include_directories( surf_account_by_key
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   surf_account_by_key

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
