file(GLOB HEADERS "include/surf/account_statistics/*.hpp")

add_library( surf_account_statistics
             account_statistics_plugin.cpp
             account_statistics_api.cpp
           )

target_link_libraries( surf_account_statistics surf_chain surf_protocol surf_app )
target_include_directories( surf_account_statistics
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   surf_account_statistics

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)